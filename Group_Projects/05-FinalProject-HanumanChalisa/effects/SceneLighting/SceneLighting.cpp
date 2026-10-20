// 3-Point Phong Lighting

#include "../../include/common.h"
#include "SceneLighting.h"

GLuint gLitShaderProgram = 0;
GLuint gLitModelMatrixUniform = 0;
GLuint gLitViewMatrixUniform = 0;
GLuint gLitProjectionMatrixUniform = 0;
GLuint gLitTextureSamplerUniform = 0;
GLuint gLitClippingPlaneUniform = 0;
GLuint gLitCameraPosUniform = 0;
GLuint gLitEnableLightingUniform = 0;

// per-light uniform locations  [0]=Key [1]=Fill [2]=Back
static GLuint uLightEnable[3] = {};
static GLuint uLightPos[3] = {};
static GLuint uAmbient[3] = {};
static GLuint uDiffuse[3] = {};
static GLuint uSpecular[3] = {};
static GLuint uShininess[3] = {};
static GLuint uIntensity[3] = {};
static GLuint uConstant[3] = {};
static GLuint uLinear[3] = {};
static GLuint uQuadratic[3] = {};

static GLuint slCompile(GLenum type, const GLchar *src, const char *name)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint status = 0;
    GLint logLen = 0;
    GLchar *szLog = NULL;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0)
        {
            szLog = (GLchar *)malloc(logLen + 1);
            if (szLog)
            {
                glGetShaderInfoLog(shader, logLen + 1, NULL, szLog);
                fprintf(gpFILE, "SceneLighting [%s]: %s\n", name, szLog);
                free(szLog);
            }
        }
    }
    return shader;
}

BOOL initializeSceneLighting(void)
{
    // code
    const GLchar *vsSource =
        "#version 460 core\n"
        "in vec4  aPosition;\n"
        "in vec3  aNormal;\n"
        "in vec2  aTexCoord;\n"

        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "uniform vec4 uClippingPlane;\n"

        "out vec2 oTexCoord;\n"
        "out vec3 oNormal;\n"
        "out vec3 oFragPos;\n"

        "void main(void)\n"
        "{\n"
        "   vec4 worldPos    = uModelMatrix * aPosition;\n"
        "   oFragPos         = worldPos.xyz;\n"
        "   oNormal          = normalize(mat3(uModelMatrix) * aNormal);\n"
        "   oTexCoord        = aTexCoord;\n"
        "   gl_ClipDistance[0] = dot(worldPos, uClippingPlane);\n"
        "   gl_Position      = uProjectionMatrix * uViewMatrix * worldPos;\n"
        "}\n";

    const GLchar *fsSource =
        "#version 460 core\n"
        "in vec2 oTexCoord;\n"
        "in vec3 oNormal;\n"
        "in vec3 oFragPos;\n"

        "uniform sampler2D uTextureSampler;\n"
        "uniform vec3      uCameraPos;\n"
        "uniform int       uEnableLighting;\n"

        "struct Light {\n"
        "   int   bEnable;\n"
        "   vec3  position;\n"
        "   vec3  ambient;\n"
        "   vec3  diffuse;\n"
        "   vec3  specular;\n"
        "   float shininess;\n"
        "   float intensity;\n"
        "   float constant;\n"
        "   float linear;\n"
        "   float quadratic;\n"
        "};\n"
        "uniform Light uLights[3];\n"

        "out vec4 FragColor;\n"

        "vec3 CalcLight(Light L, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 texCol)\n"
        "{\n"
        "   if (L.bEnable == 0) return vec3(0.0);\n"

        "   vec3  lightDir = normalize(L.position - fragPos);\n"

        "   float dist     = length(L.position - fragPos);\n"
        "   float att      = 1.0 / (L.constant + L.linear*dist + L.quadratic*dist*dist);\n"

        "   vec3 ambient   = L.ambient * texCol;\n"

        "   float diff     = max(dot(normal, lightDir), 0.0);\n"
        "   vec3 diffuse   = L.diffuse * diff * texCol;\n"

        "   vec3 halfDir   = normalize(lightDir + viewDir);\n"
        "   float spec     = pow(max(dot(normal, halfDir), 0.0), L.shininess);\n"
        "   vec3 specular  = L.specular * spec;\n"

        "   return (ambient + diffuse + specular) * att * L.intensity;\n"
        "}\n"

        "void main(void)\n"
        "{\n"
        "   vec4 texColor = texture(uTextureSampler, oTexCoord);\n"

        "   if(texColor.a < 0.01) discard;\n"

        "   if (uEnableLighting == 0)\n"
        "   {\n"
        "       FragColor = texColor;\n"
        "       return;\n"
        "   }\n"

        "   vec3 norm    = normalize(oNormal);\n"
        "   vec3 viewDir = normalize(uCameraPos - oFragPos);\n"
        "   vec3 texCol  = texColor.rgb;\n"

        "   vec3 result  = vec3(0.0);\n"
        "   result += CalcLight(uLights[0], norm, oFragPos, viewDir, texCol);\n" // Key
        "   result += CalcLight(uLights[1], norm, oFragPos, viewDir, texCol);\n" // Fill
        "   result += CalcLight(uLights[2], norm, oFragPos, viewDir, texCol);\n" // Back

        "   result += texCol * 0.03;\n"

        "   FragColor = vec4(result, texColor.a);\n"
        "}\n";

    GLuint vs = slCompile(GL_VERTEX_SHADER, vsSource, "VS");
    GLuint fs = slCompile(GL_FRAGMENT_SHADER, fsSource, "FS");

    gLitShaderProgram = glCreateProgram();
    glAttachShader(gLitShaderProgram, vs);
    glAttachShader(gLitShaderProgram, fs);

    glBindAttribLocation(gLitShaderProgram, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(gLitShaderProgram, AMC_ATTRIBUTE_NORMAL, "aNormal");
    glBindAttribLocation(gLitShaderProgram, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");

    glLinkProgram(gLitShaderProgram);

    GLint status = 0;
    GLint logLen = 0;
    GLchar *szLog = NULL;
    glGetProgramiv(gLitShaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetProgramiv(gLitShaderProgram, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0)
        {
            szLog = (GLchar *)malloc(logLen + 1);
            if (szLog)
            {
                glGetProgramInfoLog(gLitShaderProgram, logLen + 1, NULL, szLog);
                fprintf(gpFILE, "SceneLighting link error: %s\n", szLog);
                free(szLog);
            }
        }
    }

    glDetachShader(gLitShaderProgram, vs);
    glDeleteShader(vs);
    glDetachShader(gLitShaderProgram, fs);
    glDeleteShader(fs);

    gLitModelMatrixUniform = glGetUniformLocation(gLitShaderProgram, "uModelMatrix");
    gLitViewMatrixUniform = glGetUniformLocation(gLitShaderProgram, "uViewMatrix");
    gLitProjectionMatrixUniform = glGetUniformLocation(gLitShaderProgram, "uProjectionMatrix");
    gLitTextureSamplerUniform = glGetUniformLocation(gLitShaderProgram, "uTextureSampler");
    gLitClippingPlaneUniform = glGetUniformLocation(gLitShaderProgram, "uClippingPlane");
    gLitCameraPosUniform = glGetUniformLocation(gLitShaderProgram, "uCameraPos");
    gLitEnableLightingUniform = glGetUniformLocation(gLitShaderProgram, "uEnableLighting");

    const char *names[3] = {"uLights[0]", "uLights[1]", "uLights[2]"};
    char buf[64];
    for (int i = 0; i < 3; i++)
    {
        sprintf(buf, "%s.bEnable", names[i]);
        uLightEnable[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.position", names[i]);
        uLightPos[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.ambient", names[i]);
        uAmbient[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.diffuse", names[i]);
        uDiffuse[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.specular", names[i]);
        uSpecular[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.shininess", names[i]);
        uShininess[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.intensity", names[i]);
        uIntensity[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.constant", names[i]);
        uConstant[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.linear", names[i]);
        uLinear[i] = glGetUniformLocation(gLitShaderProgram, buf);
        sprintf(buf, "%s.quadratic", names[i]);
        uQuadratic[i] = glGetUniformLocation(gLitShaderProgram, buf);
    }

    fprintf(gpFILE, "SceneLighting initialized — program %u\n", gLitShaderProgram);
    return TRUE;
}

void applySceneLighting(SceneLightParams &params)
{
    glUniform1i(gLitEnableLightingUniform, params.bEnableLighting ? 1 : 0);
    glUniform3fv(gLitCameraPosUniform, 1, params.cameraPos);
    LightSource *lights[3] = {&params.keyLight, &params.fillLight, &params.backLight};

    for (int i = 0; i < 3; i++)
    {
        LightSource &L = *lights[i];
        glUniform1i(uLightEnable[i], L.bEnable ? 1 : 0);
        glUniform3fv(uLightPos[i], 1, L.position);
        glUniform3fv(uAmbient[i], 1, L.ambient);
        glUniform3fv(uDiffuse[i], 1, L.diffuse);
        glUniform3fv(uSpecular[i], 1, L.specular);
        glUniform1f(uShininess[i], L.shininess);
        glUniform1f(uIntensity[i], L.intensity);
        glUniform1f(uConstant[i], L.constant);
        glUniform1f(uLinear[i], L.linear);
        glUniform1f(uQuadratic[i], L.quadratic);
    }
}

void displaySceneLightingImGui(SceneLightParams &params)
{
    if (ImGui::CollapsingHeader("Scene Lighting", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Enable Lighting", (bool *)&params.bEnableLighting);

        if (!params.bEnableLighting)
        {
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1), "Lighting OFF — pure texture mode");
            return;
        }

        const char *lightNames[3] = {"Key Light (Primary)", "Fill Light (Secondary)", "Back Light (Rim)"};
        const ImVec4 lightColors[3] = {
            ImVec4(1.0f, 0.85f, 0.4f, 1), // Key  — warm yellow
            ImVec4(0.4f, 0.6f, 1.0f, 1),  // Fill — cool blue
            ImVec4(0.8f, 0.8f, 1.0f, 1)   // Back — neutral rim
        };

        LightSource *lights[3] = {&params.keyLight, &params.fillLight, &params.backLight};

        for (int i = 0; i < 3; i++)
        {
            ImGui::Separator();
            ImGui::TextColored(lightColors[i], "%s", lightNames[i]);

            LightSource &L = *lights[i];
            char id[32];

            sprintf(id, "Enable##L%d", i);
            ImGui::Checkbox(id, (bool *)&L.bEnable);
            if (!L.bEnable)
                continue;

            sprintf(id, "Position##L%d", i);
            ImGui::DragFloat3(id, &L.position[0], 0.5f);
            sprintf(id, "Intensity##L%d", i);
            ImGui::DragFloat(id, &L.intensity, 0.05f, 0.0f, 5.0f);
            sprintf(id, "Ambient##L%d", i);
            ImGui::ColorEdit3(id, &L.ambient[0]);
            sprintf(id, "Diffuse##L%d", i);
            ImGui::ColorEdit3(id, &L.diffuse[0]);
            sprintf(id, "Specular##L%d", i);
            ImGui::ColorEdit3(id, &L.specular[0]);
            sprintf(id, "Shininess##L%d", i);
            ImGui::DragFloat(id, &L.shininess, 1.0f, 1.0f, 256.0f);

            ImGui::Text("Attenuation:");
            sprintf(id, "Constant##L%d", i);
            ImGui::DragFloat(id, &L.constant, 0.01f, 0.0f, 5.0f);
            sprintf(id, "Linear##L%d", i);
            ImGui::DragFloat(id, &L.linear, 0.001f, 0.0f, 1.0f, "%.4f");
            sprintf(id, "Quadratic##L%d", i);
            ImGui::DragFloat(id, &L.quadratic, 0.0001f, 0.0f, 0.1f, "%.5f");
        }
    }
}

void uninitializeSceneLighting(void)
{
    if (gLitShaderProgram)
    {
        glUseProgram(gLitShaderProgram);
        GLint n = 0;
        glGetProgramiv(gLitShaderProgram, GL_ATTACHED_SHADERS, &n);
        if (n > 0)
        {
            GLuint *sh = (GLuint *)malloc(n * sizeof(GLuint));
            if (sh)
            {
                glGetAttachedShaders(gLitShaderProgram, n, NULL, sh);
                for (GLint i = 0; i < n; i++)
                {
                    glDetachShader(gLitShaderProgram, sh[i]);
                    glDeleteShader(sh[i]);
                }
                free(sh);
            }
        }
        glUseProgram(0);
        glDeleteProgram(gLitShaderProgram);
        gLitShaderProgram = 0;
    }
    fprintf(gpFILE, "SceneLighting uninitialized\n");
}
