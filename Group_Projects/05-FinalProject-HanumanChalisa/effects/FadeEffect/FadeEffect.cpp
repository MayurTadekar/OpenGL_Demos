#include "FadeEffect.h"

static GLuint vaoFadeQuads = 0;
static GLuint vboFadePos = 0;
static GLuint fadeShaderProgramObject = 0;
static GLuint fadeAlphaUniformLocation = 0;
static float gFadeAlpha = 1.0f;

BOOL initializeFadeSystem(void)
{
    const GLchar *vsSrc =
        "#version 430 core\n"
        "layout(location = 0) in vec2 a_position;\n"
        "void main() {\n"
        "    gl_Position = vec4(a_position, 0.0, 1.0);\n"
        "}\n";

    const GLchar *fsSrc =
        "#version 430 core\n"
        "uniform float u_alpha;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(0.0, 0.0, 0.0, u_alpha);\n"
        "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, NULL);
    glCompileShader(fs);

    fadeShaderProgramObject = glCreateProgram();
    glAttachShader(fadeShaderProgramObject, vs);
    glAttachShader(fadeShaderProgramObject, fs);
    glLinkProgram(fadeShaderProgramObject);

    fadeAlphaUniformLocation = glGetUniformLocation(fadeShaderProgramObject, "u_alpha");

    glDeleteShader(vs);
    glDeleteShader(fs);

    const GLfloat quadVertices[] = {
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f};

    glGenVertexArrays(1, &vaoFadeQuads);
    glBindVertexArray(vaoFadeQuads);

    glGenBuffers(1, &vboFadePos);
    glBindBuffer(GL_ARRAY_BUFFER, vboFadePos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return TRUE;
}

void updateFadeTransitionLogic(float elapsedTime, const float *sceneStartTimes, int totalScenes, float fadeDuration)
{
    int currentSceneIdx = 0;

    for (int i = 0; i < totalScenes - 1; i++)
    {
        if (elapsedTime >= sceneStartTimes[i] && elapsedTime < sceneStartTimes[i + 1])
        {
            currentSceneIdx = i;
            break;
        }
    }

    float currentSceneStart = sceneStartTimes[currentSceneIdx];
    float nextSceneStart = sceneStartTimes[currentSceneIdx + 1];

    if (elapsedTime - currentSceneStart < fadeDuration)
    {
        float progress = (elapsedTime - currentSceneStart) / fadeDuration;
        gFadeAlpha = 1.0f - progress;
    }
    else if (nextSceneStart - elapsedTime < fadeDuration)
    {
        float progress = (nextSceneStart - elapsedTime) / fadeDuration;
        gFadeAlpha = 1.0f - progress;
    }
    else
    {
        gFadeAlpha = 0.0f;
    }

    if (gFadeAlpha < 0.0f)
        gFadeAlpha = 0.0f;
    if (gFadeAlpha > 1.0f)
        gFadeAlpha = 1.0f;
}

void drawFadeOverlay(void)
{
    if (gFadeAlpha <= 0.001f)
        return;

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(fadeShaderProgramObject);
    glUniform1f(fadeAlphaUniformLocation, gFadeAlpha);

    glBindVertexArray(vaoFadeQuads);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
}

void setFadeAlphaManual(float alpha)
{
    gFadeAlpha = alpha;
    if (gFadeAlpha < 0.0f)
        gFadeAlpha = 0.0f;
    if (gFadeAlpha > 1.0f)
        gFadeAlpha = 1.0f;
}

void uninitializeFadeSystem(void)
{
    if (vboFadePos)
    {
        glDeleteBuffers(1, &vboFadePos);
        vboFadePos = 0;
    }
    if (vaoFadeQuads)
    {
        glDeleteVertexArrays(1, &vaoFadeQuads);
        vaoFadeQuads = 0;
    }
    if (fadeShaderProgramObject)
    {
        glDeleteProgram(fadeShaderProgramObject);
        fadeShaderProgramObject = 0;
    }
}
