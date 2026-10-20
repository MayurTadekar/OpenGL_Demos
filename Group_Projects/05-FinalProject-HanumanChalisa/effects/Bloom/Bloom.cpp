#include "Bloom.h"

static GLuint gShaderProgramObject_Bloom = 0;
static GLuint gVao_Bloom = 0;
static GLuint gVbo_Bloom = 0;

static GLuint gModelMatrixUniform_Bloom = 0;
static GLuint gViewMatrixUniform_Bloom = 0;
static GLuint gProjectionMatrixUniform_Bloom = 0;
static GLuint gColorUniform_Bloom = 0;
static GLuint gIntensityUniform_Bloom = 0;

void initializeBloom(void)
{
    // Vertex Shader
    const GLchar* vertexShaderSourceCode =
        "#version 460 core\n"
        "in vec4 aPosition;\n"
        "in vec2 aTexCoord;\n"
        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "out vec2 oTexCoord;\n"
        "void main(void)\n"
        "{\n"
        "    // Spherical Billboard facing the camera\n"
        "    vec3 cameraRight = vec3(uViewMatrix[0][0], uViewMatrix[1][0], uViewMatrix[2][0]);\n"
        "    vec3 cameraUp = vec3(uViewMatrix[0][1], uViewMatrix[1][1], uViewMatrix[2][1]);\n"
        "    vec3 worldPos = vec3(uModelMatrix[3]) + (cameraRight * aPosition.x * uModelMatrix[0][0]) + (cameraUp * aPosition.y * uModelMatrix[1][1]);\n"
        "    gl_Position = uProjectionMatrix * uViewMatrix * vec4(worldPos, 1.0);\n"
        "    oTexCoord = aTexCoord;\n"
        "}\n";

    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, &vertexShaderSourceCode, NULL);
    glCompileShader(vertexShaderObject);

    // Fragment Shader
    const GLchar* fragmentShaderSourceCode =
        "#version 460 core\n"
        "in vec2 oTexCoord;\n"
        "uniform vec3 uColor;\n"
        "uniform float uIntensity;\n"
        "out vec4 FragColor;\n"
        "void main(void)\n"
        "{\n"
        "    vec2 coord = oTexCoord * 2.0 - 1.0;\n"
        "    float dist = length(coord);\n"
        "    float glow = exp(-dist * 3.0) * uIntensity;\n"
        "    if (dist > 1.0) discard;\n"
        "    FragColor = vec4(uColor * glow, glow);\n"
        "}\n";

    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, &fragmentShaderSourceCode, NULL);
    glCompileShader(fragmentShaderObject);

    // Shader Program
    gShaderProgramObject_Bloom = glCreateProgram();
    glAttachShader(gShaderProgramObject_Bloom, vertexShaderObject);
    glAttachShader(gShaderProgramObject_Bloom, fragmentShaderObject);
    glBindAttribLocation(gShaderProgramObject_Bloom, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(gShaderProgramObject_Bloom, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");
    glLinkProgram(gShaderProgramObject_Bloom);

    gModelMatrixUniform_Bloom = glGetUniformLocation(gShaderProgramObject_Bloom, "uModelMatrix");
    gViewMatrixUniform_Bloom = glGetUniformLocation(gShaderProgramObject_Bloom, "uViewMatrix");
    gProjectionMatrixUniform_Bloom = glGetUniformLocation(gShaderProgramObject_Bloom, "uProjectionMatrix");
    gColorUniform_Bloom = glGetUniformLocation(gShaderProgramObject_Bloom, "uColor");
    gIntensityUniform_Bloom = glGetUniformLocation(gShaderProgramObject_Bloom, "uIntensity");

    glDetachShader(gShaderProgramObject_Bloom, vertexShaderObject);
    glDeleteShader(vertexShaderObject);
    glDetachShader(gShaderProgramObject_Bloom, fragmentShaderObject);
    glDeleteShader(fragmentShaderObject);

    const GLfloat quadVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &gVao_Bloom);
    glBindVertexArray(gVao_Bloom);

    glGenBuffers(1, &gVbo_Bloom);
    glBindBuffer(GL_ARRAY_BUFFER, gVbo_Bloom);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void renderBloom(const BloomParams& params, Camera* pCamera, vmath::mat4 projectionMatrix)
{
    glUseProgram(gShaderProgramObject_Bloom);

    vmath::mat4 modelMatrix = vmath::translate(params.position) * vmath::scale(params.radius);

    glUniformMatrix4fv(gModelMatrixUniform_Bloom, 1, GL_FALSE, modelMatrix);
    glUniformMatrix4fv(gViewMatrixUniform_Bloom, 1, GL_FALSE, pCamera->getLookAtMatrix());
    glUniformMatrix4fv(gProjectionMatrixUniform_Bloom, 1, GL_FALSE, projectionMatrix);

    glUniform3fv(gColorUniform_Bloom, 1, params.color);
    glUniform1f(gIntensityUniform_Bloom, params.intensity);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending for true light/bloom scattering look
    glDepthMask(GL_FALSE);             // Read depth, but don't write to it

    glBindVertexArray(gVao_Bloom);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);              // Reset state
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(0);
}

void uninitializeBloom(void)
{
    if (gVbo_Bloom) {
        glDeleteBuffers(1, &gVbo_Bloom);
        gVbo_Bloom = 0;
    }
    if (gVao_Bloom) {
        glDeleteVertexArrays(1, &gVao_Bloom);
        gVao_Bloom = 0;
    }
    if (gShaderProgramObject_Bloom) {
        glUseProgram(gShaderProgramObject_Bloom);
        GLint numShaders = 0;
        glGetProgramiv(gShaderProgramObject_Bloom, GL_ATTACHED_SHADERS, &numShaders);
        if (numShaders > 0) {
            GLuint* pShaders = new GLuint[numShaders];
            glGetAttachedShaders(gShaderProgramObject_Bloom, numShaders, NULL, pShaders);
            for (GLint i = 0; i < numShaders; i++) {
                glDetachShader(gShaderProgramObject_Bloom, pShaders[i]);
                glDeleteShader(pShaders[i]);
            }
            delete[] pShaders;
        }
        glUseProgram(0);
        glDeleteProgram(gShaderProgramObject_Bloom);
        gShaderProgramObject_Bloom = 0;
    }
}