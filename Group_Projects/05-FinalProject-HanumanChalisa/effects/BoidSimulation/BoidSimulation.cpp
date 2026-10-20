#include "BoidSimulation.h"
#include "../../OGL.h"

extern Model *gpOceanSceneBirdModel;

BoidSimulation::BoidSimulation() {}
BoidSimulation::~BoidSimulation() { Uninitialize(); }

BOOL BoidSimulation::Initialize() {
    const GLchar* vs = 
        "#version 460 core\n"
        "layout(location = 0) in vec4 aPosition;\n"
        "layout(location = 1) in vec2 aTexCoord;\n"
        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "uniform float uTime;\n"
        "uniform float uWingSpeed;\n"
        "out vec2 oTexCoord;\n"
        "void main(void) {\n"
        "    vec4 pos = aPosition;\n"
        "    float wingFactor = abs(pos.x);\n" // Flap more at wing tips
        "    pos.y += sin(uTime * uWingSpeed) * wingFactor * 0.5;\n"
        "    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * pos;\n"
        "    oTexCoord = aTexCoord;\n"
        "}\n";

    const GLchar* fs = 
        "#version 460 core\n"
        "in vec2 oTexCoord;\n"
        "uniform sampler2D uTextureSampler;\n"
        "out vec4 FragColor;\n"
        "void main(void) {\n"
        "    vec4 texColor = texture(uTextureSampler, oTexCoord);\n"
        "    if(texColor.a < 0.1) discard;\n"
        "    FragColor = vec4(0.0, 0.0, 0.0, texColor.a);\n" // Force birds to be black silhouettes
        "}\n";

    shaderProgramObject = glCreateProgram();
    GLuint v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vs, NULL);
    glCompileShader(v);
    GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &fs, NULL);
    glCompileShader(f);
    glAttachShader(shaderProgramObject, v);
    glAttachShader(shaderProgramObject, f);
    glLinkProgram(shaderProgramObject);
    glDeleteShader(v);
    glDeleteShader(f);

    modelMatrixUniform = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
    viewMatrixUniform = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
    projectionMatrixUniform = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
    timeUniform = glGetUniformLocation(shaderProgramObject, "uTime");
    wingSpeedUniform = glGetUniformLocation(shaderProgramObject, "uWingSpeed");

    return TRUE;
}

void BoidSimulation::Update(float deltaTime, BoidParams& params) {
    if (!params.bEnable) return;
    currentTime += deltaTime;
    
    instanceMatrices.clear();
    if (params.type == BOID_V_SHAPE) {
        int count = 9;
        float spacing = 8.0f * params.scale;
        vmath::vec3 basePos = params.position; // Translation animation removed as requested
        for (int i = 0; i < count; i++) {
            vmath::vec3 offset;
            if (i == 0) offset = vmath::vec3(0, 0, 0); // Leader
            else if (i <= 10) offset = vmath::vec3(-i * spacing, 0, -i * spacing); // Left wing
            else {
                int j = i - 10;
                offset = vmath::vec3(j * spacing, 0, -j * spacing); // Right wing
            }
            
            // Adjusted local rotation: -90 deg on X to lie flat, 90 on Y to align head-first with flight path
            vmath::mat4 mat = vmath::translate(basePos + offset) * 
                             vmath::rotate(90.0f, 0.0f, 1.0f, 0.0f) * 
                             vmath::rotate(-90.0f, 1.0f, 0.0f, 0.0f) * 
                             vmath::scale(params.scale);
            instanceMatrices.push_back(mat);
        }
    } else { // Flock formation (200 birds)
        int count = 9;
        for (int i = 0; i < count; i++) {
            float seed = (float)i * 0.15f;
            // Movement removed, using a fixed noise-based spread around the base position
            vmath::vec3 offset = vmath::vec3(sinf(seed) * 50.0f, cosf(seed * 2.0f) * 15.0f, cosf(seed) * 50.0f);
            
            // Adjusted Y rotation from 180 to 90 to fix sideways flight + maintained X-pitch correction
            vmath::mat4 mat = vmath::translate(params.position + offset) * 
                             vmath::rotate(90.0f + (float)sin(currentTime + seed) * 10.0f, 0.0f, 1.0f, 0.0f) *
                             vmath::rotate(-90.0f, 1.0f, 0.0f, 0.0f) *
                             vmath::scale(params.scale);
            instanceMatrices.push_back(mat);
        }
    }
}

void BoidSimulation::Render(const vmath::mat4& projectionMatrix, const vmath::mat4& viewMatrix, BoidParams& params) {
    if (!params.bEnable || !gpOceanSceneBirdModel) return;

    glUseProgram(shaderProgramObject);
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, viewMatrix);
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);
    glUniform1f(timeUniform, currentTime);
    glUniform1f(wingSpeedUniform, params.wingSpeed);

    for (const auto& modelMat : instanceMatrices) {
        glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, modelMat);
        renderModel(gpOceanSceneBirdModel);
    }

    glUseProgram(0);
}

void BoidSimulation::Uninitialize() {
    if (shaderProgramObject) {
        glDeleteProgram(shaderProgramObject);
        shaderProgramObject = 0;
    }
}
