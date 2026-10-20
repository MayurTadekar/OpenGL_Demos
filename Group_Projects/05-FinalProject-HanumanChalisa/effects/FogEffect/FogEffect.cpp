#include "FogEffect.h"
#include "../../include/common.h"

// Defaults
FogParameters gRamWorshipSceneFogParams = {TRUE,  0.0142f, 2.0f, vmath::vec3(0.85f, 0.88f, 0.95f)};
FogParameters gYuddhaScene1FogParams = {TRUE, 0.025f, 2.0f, vmath::vec3(0.85f, 0.88f, 0.95f)};
FogParameters gMountainExteriorSceneFogParams = {TRUE, 0.025f, 2.0f, vmath::vec3(0.710, 0.737, 0.804)};

static GLuint fogShaderProg = 0;
static GLuint vaoFogQuad = 0;
static GLuint vboFogPos = 0;

// Uniforms
static GLuint uEnableLoc = 0;
static GLuint uDensityLoc = 0;
static GLuint uGradientLoc = 0;
static GLuint uColorLoc = 0;
static GLuint uProjMatrixLoc = 0;

BOOL initializeFogSystem(void)
{
    // Vertex Shader
    const GLchar *vsSrc =
        "#version 430 core\n"
        "layout(location = 0) in vec2 a_position;\n"
        "out vec2 texCoords;\n"
        "void main() {\n"
        "    texCoords = a_position * 0.5 + 0.5;\n"
        "    gl_Position = vec4(a_position, 0.0, 1.0);\n"
        "}\n";

    // Fragment Shader
    const GLchar *fsSrc =
        "#version 430 core\n"
        "in vec2 texCoords;\n"
        "out vec4 fragColor;\n"
        "uniform sampler2D u_depthTexture;\n"
        "uniform mat4 u_projectionMatrix;\n"
        "struct FogParams {\n"
        "    bool bEnable;\n"
        "    float density;\n"
        "    float gradient;\n"
        "    vec3 color;\n"
        "};\n"
        "uniform FogParams u_fog;\n"
        "void main() {\n"
        "    if (!u_fog.bEnable) discard;\n"
        "    float depth = texture(u_depthTexture, texCoords).r;\n"
        "    // Reconstruct linear camera depth from non-linear projection map\n"
        "    float zNear = 0.1;\n"
        "    float zFar = 1000.0;\n"
        "    float linearDepth = (2.0 * zNear * zFar) / (zFar + zNear - (depth * 2.0 - 1.0) * (zFar - zNear));\n"
        "    if (depth >= 0.99999) linearDepth = zFar; // Don't blend skybox out aggressively\n"
        "    float fogFactor = 1.0 - exp(-pow((linearDepth * u_fog.density), u_fog.gradient));\n"
        "    fogFactor = clamp(fogFactor, 0.0, 1.0);\n"
        "    fragColor = vec4(u_fog.color, fogFactor);\n"
        "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, NULL);
    glCompileShader(fs);

    fogShaderProg = glCreateProgram();
    glAttachShader(fogShaderProg, vs);
    glAttachShader(fogShaderProg, fs);
    glLinkProgram(fogShaderProg);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // Retrieve uniform target params
    uEnableLoc = glGetUniformLocation(fogShaderProg, "u_fog.bEnable");
    uDensityLoc = glGetUniformLocation(fogShaderProg, "u_fog.density");
    uGradientLoc = glGetUniformLocation(fogShaderProg, "u_fog.gradient");
    uColorLoc = glGetUniformLocation(fogShaderProg, "u_fog.color");
    uProjMatrixLoc = glGetUniformLocation(fogShaderProg, "u_projectionMatrix");

    const GLfloat quadVertices[] = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    glGenVertexArrays(1, &vaoFogQuad);
    glBindVertexArray(vaoFogQuad);
    glGenBuffers(1, &vboFogPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboFogPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return TRUE;
}

void drawFogVolumeLayer(const FogParameters &params, GLuint sceneDepthTexture, vmath::mat4 projectionMatrix)
{
    if (!params.bEnable || fogShaderProg == 0)
        return;

    glUseProgram(fogShaderProg);

    glUniform1i(uEnableLoc, params.bEnable);
    glUniform1f(uDensityLoc, params.fogDensity);
    glUniform1f(uGradientLoc, params.fogGradient);
    glUniform3fv(uColorLoc, 1, params.fogColor);
    glUniformMatrix4fv(uProjMatrixLoc, 1, GL_FALSE, projectionMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sceneDepthTexture);
    glUniform1i(glGetUniformLocation(fogShaderProg, "u_depthTexture"), 0);

    glBindVertexArray(vaoFogQuad);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
}

void renderFogImGuiControls(void)
{
    if (ImGui::CollapsingHeader("Atmospheric Fog Controls"))
    {
        if (ImGui::TreeNode("Mountain Exterior FOG"))
        {
            ImGui::Checkbox("Enable Dust Fog", (bool *)&gMountainExteriorSceneFogParams.bEnable);
            ImGui::SliderFloat("Dust Density", &gMountainExteriorSceneFogParams.fogDensity, 0.1f, 0.095f, "%.4f");
            ImGui::SliderFloat("Falloff Power", &gMountainExteriorSceneFogParams.fogGradient, 0.5f, 4.0f, "%.2f");
            ImGui::ColorEdit3("Dust Shroud Tint", (float *)&gMountainExteriorSceneFogParams.fogColor);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Yuddha Scene 1 FOG"))
        {
            ImGui::Checkbox("Enable Dust Fog", (bool *)&gYuddhaScene1FogParams.bEnable);
            ImGui::SliderFloat("Dust Density", &gYuddhaScene1FogParams.fogDensity, 0.1f, 0.095f, "%.4f");
            ImGui::SliderFloat("Falloff Power", &gYuddhaScene1FogParams.fogGradient, 0.5f, 4.0f, "%.2f");
            ImGui::ColorEdit3("Dust Shroud Tint", (float *)&gYuddhaScene1FogParams.fogColor);
            ImGui::TreePop();
        }
        ImGui::Separator();
        if (ImGui::TreeNode("Ram Worship Scene FOG"))
        {
            ImGui::Checkbox("Enable Snow Fog", (bool *)&gRamWorshipSceneFogParams.bEnable);
            ImGui::SliderFloat("Snow Density", &gRamWorshipSceneFogParams.fogDensity, 0.001f, 0.1f, "%.4f");
            ImGui::SliderFloat("Falloff Power", &gRamWorshipSceneFogParams.fogGradient, 0.5f, 4.0f, "%.2f");
            ImGui::ColorEdit3("Snow Shroud Tint", (float *)&gRamWorshipSceneFogParams.fogColor);
            ImGui::TreePop();
        }
    }
}

void uninitializeFogSystem(void)
{
    if (vboFogPos)
    {
        glDeleteBuffers(1, &vboFogPos);
        vboFogPos = 0;
    }
    if (vaoFogQuad)
    {
        glDeleteVertexArrays(1, &vaoFogQuad);
        vaoFogQuad = 0;
    }
    if (fogShaderProg)
    {
        glDeleteProgram(fogShaderProg);
        fogShaderProg = 0;
    }
}
