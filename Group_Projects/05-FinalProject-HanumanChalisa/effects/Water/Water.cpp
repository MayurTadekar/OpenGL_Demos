// header files
#include "../include/common.h"
#include "../modules/Camera/Camera.h"
#include "Water.h"

// global variables
static GLuint shaderProgramObject = 0;
static GLuint modelMatrixUniform = 0;
static GLuint viewMatrixUniform = 0;
static GLuint projectionMatrixUniform = 0;
static GLuint reflectionTextureSamplerUniform = 0;
static GLuint refractionTextureSamplerUniform = 0;

static GLuint dudvMapTextureSamplerUniform = 0;
static GLuint tilingUniform = 0;
static GLuint waveStrengthUniform = 0;
static GLuint moveFactorUniform = 0;
static GLuint tintColorUniform = 0;
static GLuint tintFactorUniform = 0;

// new uniforms
static GLuint waterDirectionUniform = 0;
static GLuint movementModeUniform = 0;

static GLuint vao = 0;
static GLuint vbo = 0;
static GLuint ebo = 0;

static GLuint g_reflectionTexture = 0;
static GLuint g_refractionDepthTexture = 0;
static GLuint g_refractionTexture = 0;
static GLuint g_dudvMapTexture = 0;

extern WaterParams waterParams[2];


BOOL initializeWater(GLuint reflectionTexture, GLuint refractionTexture, GLuint refractionDepthTexture, GLuint dudvMapTexture)
{
    // Vertex Shader
    const GLchar *vertexShaderSourceCode =
        "#version 460 core" \
        "\n" \
        "in vec4 aPosition;" \
        "in vec2 aTexCoord;" \
        "uniform mat4 uModelMatrix;" \
        "uniform mat4 uViewMatrix;" \
        "uniform mat4 uProjectionMatrix;" \
        "uniform float uTiling;" \
        "out vec2 oTexCoord;" \
        "out vec4 oClipSpacePosition;" \
        "void main(void)" \
        "{" \
        "oClipSpacePosition = uProjectionMatrix * uViewMatrix * uModelMatrix * aPosition;" \
        "gl_Position = oClipSpacePosition;" \
        "oTexCoord = aTexCoord * uTiling;" \
        "}";

    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);
    glCompileShader(vertexShaderObject);

    GLint status = 0;
    GLint infoLogLength = 0;
    GLchar *szInfoLog = NULL;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(vertexShaderObject, infoLogLength + 1, NULL, szInfoLog);
                fprintf(gpFILE, "Vertex shader compilation error log : %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        uninitialize();
    }

    // Fragment Shader
    const GLchar *fragmentShaderCode =
        "#version 460 core" \
        "\n" \
        "in vec2 oTexCoord;" \
        "in vec4 oClipSpacePosition;" \
        "uniform sampler2D uReflectionTextureSampler;" \
        "uniform sampler2D uRefractionTextureSampler;" \
        "uniform sampler2D uDuDvMapTextureSampler;" \
        "uniform float uWaveStrength;" \
        "uniform float uMoveFactor;" \
        "uniform vec3 uTintColor;" \
        "uniform float uTintFactor;" \
        "uniform vec2 uWaterDirection;" \
        "uniform int uMovementMode;" \
        "out vec4 FragColor;" \
        "void main(void)" \
        "{" \
        "vec2 normalizeDeviceCoordinates = (oClipSpacePosition.xy / oClipSpacePosition.w) / 2.0 + 0.5;" \
        "vec2 refractionTexcoord = vec2(normalizeDeviceCoordinates.x, normalizeDeviceCoordinates.y);" \
        "vec2 reflectionTexcoord = vec2(normalizeDeviceCoordinates.x, -normalizeDeviceCoordinates.y);" \
        "vec2 distortionVector1;" \
        "vec2 distortionVector2;" \
        "if(uMovementMode == 0)" \
        "{" \
        "distortionVector1 = (texture(uDuDvMapTextureSampler, vec2(oTexCoord.x + uMoveFactor, oTexCoord.y)).rg * 2.0 - 1.0) * uWaveStrength;" \
        "distortionVector2 = (texture(uDuDvMapTextureSampler, vec2(oTexCoord.x + uMoveFactor, oTexCoord.y + uMoveFactor)).rg * 2.0 - 1.0) * uWaveStrength;" \
        "}" \
        "else" \
        "{" \
        "vec2 flowOffset = uWaterDirection * uMoveFactor;" \
        "distortionVector1 = (texture(uDuDvMapTextureSampler, oTexCoord + flowOffset).rg * 2.0 - 1.0) * uWaveStrength;" \
        "distortionVector2 = (texture(uDuDvMapTextureSampler, vec2(oTexCoord.x + flowOffset.x, oTexCoord.y + flowOffset.y + uMoveFactor)).rg * 2.0 - 1.0) * uWaveStrength;" \
        "}" \
        "vec2 totalDistortion = distortionVector1 + distortionVector2;" \
        "refractionTexcoord = refractionTexcoord + totalDistortion;" \
        "refractionTexcoord = clamp(refractionTexcoord, 0.001, 0.999);" \
        "reflectionTexcoord = reflectionTexcoord + totalDistortion;" \
        "reflectionTexcoord.x = clamp(reflectionTexcoord.x, 0.001, 0.999);" \
        "reflectionTexcoord.y = clamp(reflectionTexcoord.y, -0.999, -0.001);" \
        "vec4 reflectionColor = texture(uReflectionTextureSampler, reflectionTexcoord);" \
        "vec4 refractionColor = texture(uRefractionTextureSampler, refractionTexcoord);" \
        "FragColor = mix(refractionColor, reflectionColor, 0.5);" \
        "FragColor = mix(FragColor, vec4(uTintColor, 1.0), uTintFactor);" \
        "}";

    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderObject);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
            if (szInfoLog != NULL)
            {
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength + 1, NULL, szInfoLog);
                fprintf(gpFILE, "Fragment shader compilation log : %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        uninitialize();
    }

    // Shader program
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");

    glLinkProgram(shaderProgramObject);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(sizeof(GLchar) * (infoLogLength + 1));
            if (szInfoLog != NULL)
            {
                glGetProgramInfoLog(shaderProgramObject, infoLogLength + 1, NULL, szInfoLog);
                fprintf(gpFILE, "Shader program linking error log : %s\n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        uninitialize();
    }

    // Uniforms
    modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");

    reflectionTextureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uReflectionTextureSampler");
    refractionTextureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uRefractionTextureSampler");
    dudvMapTextureSamplerUniform = glGetUniformLocation(shaderProgramObject, "uDuDvMapTextureSampler");

    tilingUniform = glGetUniformLocation(shaderProgramObject, "uTiling");
    waveStrengthUniform = glGetUniformLocation(shaderProgramObject, "uWaveStrength");
    moveFactorUniform = glGetUniformLocation(shaderProgramObject, "uMoveFactor");
    tintColorUniform = glGetUniformLocation(shaderProgramObject, "uTintColor");
    tintFactorUniform = glGetUniformLocation(shaderProgramObject, "uTintFactor");

    waterDirectionUniform = glGetUniformLocation(shaderProgramObject, "uWaterDirection");
    movementModeUniform = glGetUniformLocation(shaderProgramObject, "uMovementMode");

    // Quad vertices
    GLfloat quadVertices[] =
    {
         1.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         1.0f, 0.0f,  1.0f, 1.0f, 0.0f
    };

    GLushort quadIndices[] =
    {
        0, 1, 3,
        3, 1, 2
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const void *)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    g_reflectionTexture = reflectionTexture;
    g_refractionTexture = refractionTexture;
    g_refractionDepthTexture = refractionDepthTexture;
    g_dudvMapTexture = dudvMapTexture;

    return(TRUE);
}

void renderWater(WaterParams params, Camera *pCamera, vmath::mat4 projectionMatrix)
{
    glUseProgram(shaderProgramObject);

    // model matrix
    vmath::mat4 modelMatrix = vmath::translate(params.translation) * vmath::scale(params.scale);

    glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMatrix);
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, pCamera->getLookAtMatrix());
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

    glUniform1i(reflectionTextureSamplerUniform, 0);
    glUniform1i(refractionTextureSamplerUniform, 1);
    glUniform1i(dudvMapTextureSamplerUniform, 2);

    glUniform1f(tilingUniform, params.titling);
    glUniform1f(waveStrengthUniform, params.waveStrength);
    glUniform1f(moveFactorUniform, params.moveFactor);
    glUniform1f(tintFactorUniform, params.tintFactor);
    glUniform3fv(tintColorUniform, 1, params.tintColor);

    glUniform2f(waterDirectionUniform, params.waterDirection[0], params.waterDirection[1]);
    glUniform1i(movementModeUniform, params.movementMode);

    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_reflectionTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, g_refractionTexture);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, g_dudvMapTexture);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, g_refractionDepthTexture);

    glBindVertexArray(vao);
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    glUseProgram(0);
	updateWater();

}

void updateWater()
{
    waterParams[1].moveFactor += 0.001f;
    if (waterParams[1].moveFactor >= 10.0f)
        waterParams[1].moveFactor -= 10.0f;
}

void uninitializeWater(void)
{
    if (ebo)
    {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }

    if (vbo)
    {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (vao)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    if (shaderProgramObject)
    {
        glUseProgram(shaderProgramObject);

        GLint numShader = 0;
        glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);

        if (numShader > 0)
        {
            GLuint *pShader = (GLuint *)malloc(numShader * sizeof(GLuint));
            if (pShader != NULL)
            {
                glGetAttachedShaders(shaderProgramObject, numShader, NULL, pShader);

                for (GLint i = 0; i < numShader; i++)
                {
                    glDetachShader(shaderProgramObject, pShader[i]);
                    glDeleteShader(pShader[i]);
                    pShader[i] = 0;
                }

                free(pShader);
                pShader = NULL;
            }
        }

        glUseProgram(0);

        glDeleteProgram(shaderProgramObject);
        shaderProgramObject = 0;
    }
}
