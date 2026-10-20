#include "WaterLensFlare.h"
#include <math.h>

struct Ghost
{
    float position;
    float radius;
    float r;
    float g;
    float b;
    float alpha;
    float ring;
};

static Ghost ghosts[] =
{
    { 0.35f, 0.130f, 1.00f, 0.88f, 0.70f, 0.50f, 1.0f },
    { 0.44f, 0.050f, 1.00f, 0.95f, 0.82f, 0.90f, 0.0f },
    { 0.53f, 0.240f, 1.00f, 0.84f, 0.64f, 0.15f, 0.0f },
    { 0.62f, 0.080f, 1.00f, 0.90f, 0.72f, 0.50f, 0.0f },
    { 0.71f, 0.105f, 1.00f, 0.86f, 0.68f, 0.45f, 1.0f },
    { 0.80f, 0.190f, 1.00f, 0.82f, 0.60f, 0.22f, 0.0f },
    { 0.89f, 0.045f, 1.00f, 0.96f, 0.84f, 0.90f, 0.0f },
    { 0.98f, 0.150f, 1.00f, 0.88f, 0.70f, 0.28f, 0.0f },
    { 1.07f, 0.220f, 1.00f, 0.83f, 0.62f, 0.17f, 0.0f },
    { 1.16f, 0.058f, 1.00f, 0.95f, 0.82f, 0.80f, 0.0f },
    { 1.25f, 0.095f, 1.00f, 0.85f, 0.66f, 0.45f, 1.0f }
};
static const int ghostCount = (int)(sizeof(ghosts) / sizeof(ghosts[0]));

static GLuint flareProgram = 0;
static GLint uCenter = -1;
static GLint uSize = -1;
static GLint uAspect = -1;
static GLint uColor = -1;
static GLint uTint = -1;
static GLint uAlpha = -1;
static GLint uAlphaScale = -1;
static GLint uRing = -1;
static GLint uIntensity = -1;
static GLint uCamPos = -1;
static GLint uFront = -1;
static GLint uRight = -1;
static GLint uUp = -1;
static GLint uTanHalfV = -1;
static GLint uWaterY = -1;
static GLint uWaterCenter = -1;
static GLint uWaterHalf = -1;
static GLint uViewProj = -1;
static GLint uUseWaterMask = -1;

static GLuint occProgram = 0;
static GLint uOccCenter = -1;
static GLint uOccHalf = -1;
static GLint uOccDepth = -1;

static GLuint quadVao = 0;
static GLuint quadVbo = 0;

static GLuint sunQuery = 0;
static bool queryRunning = false;
static float proxyPixels = 1.0f;
static float visibility = 0.0f;
static float visibilityTarget = 0.0f;

static GLuint buildProgram(const char *vertexSource, const char *fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program, AMC_ATTRIBUTE_POSITION, "aPosition");
    glLinkProgram(program);

    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}

BOOL initializeWaterLensFlare(void)
{
    const char *flareVertex =
        "#version 460 core\n"
        "in vec2 aPosition;\n"
        "uniform vec2 uCenter;\n"
        "uniform float uSize;\n"
        "uniform float uAspect;\n"
        "out vec2 vNdc;\n"
        "void main(void)\n"
        "{\n"
        "   vec2 extent = vec2(uSize / uAspect, uSize) * 1.3;\n"
        "   vec2 ndc = uCenter + aPosition * extent;\n"
        "   vNdc = ndc;\n"
        "   gl_Position = vec4(ndc, 0.0, 1.0);\n"
        "}\n";

    const char *flareFragment =
        "#version 460 core\n"
        "precision highp float;\n"
        "in vec2 vNdc;\n"
        "uniform vec2 uCenter;\n"
        "uniform float uSize;\n"
        "uniform float uAspect;\n"
        "uniform vec3 uColor;\n"
        "uniform vec3 uTint;\n"
        "uniform float uAlpha;\n"
        "uniform float uAlphaScale;\n"
        "uniform float uRing;\n"
        "uniform float uIntensity;\n"
        "uniform vec3 uCamPos;\n"
        "uniform vec3 uFront;\n"
        "uniform vec3 uRight;\n"
        "uniform vec3 uUp;\n"
        "uniform float uTanHalfV;\n"
        "uniform float uWaterY;\n"
        "uniform vec2 uWaterCenter;\n"
        "uniform vec2 uWaterHalf;\n"
        "uniform mat4 uViewProj;\n"
        "uniform int uUseWaterMask;\n"
        "out vec4 FragColor;\n"
        "void main(void)\n"
        "{\n"
        "   if (uUseWaterMask == 1)\n"
        "   {\n"
        "       vec3 dir = normalize(uFront + (vNdc.x * uTanHalfV * uAspect) * uRight + (vNdc.y * uTanHalfV) * uUp);\n"
        "       if (abs(dir.y) < 0.00001)\n"
        "           discard;\n"
        "       float t = (uWaterY - uCamPos.y) / dir.y;\n"
        "       if (t <= 0.0)\n"
        "           discard;\n"
        "       vec3 hit = uCamPos + t * dir;\n"
        "       vec2 lo = uWaterCenter - uWaterHalf;\n"
        "       vec2 hi = uWaterCenter + uWaterHalf;\n"
        "       if (hit.x < lo.x || hit.x > hi.x || hit.z < lo.y || hit.z > hi.y)\n"
        "           discard;\n"
        "       vec4 clip = uViewProj * vec4(hit, 1.0);\n"
        "       gl_FragDepth = (clip.z / clip.w) * 0.5 + 0.5 - 0.0008;\n"
        "   }\n"
        "   else\n"
        "   {\n"
        "       gl_FragDepth = 0.0;\n"
        "   }\n"
        "   vec2 local = (vNdc - uCenter) * vec2(uAspect, 1.0) / uSize;\n"
        "   float rad = length(local);\n"
        "   float a;\n"
        "   if (uRing > 0.5)\n"
        "   {\n"
        "       a = smoothstep(0.16, 0.0, abs(rad - 0.80)) * 0.85;\n"
        "   }\n"
        "   else\n"
        "   {\n"
        "       float core = pow(smoothstep(1.0, 0.0, rad), 1.8);\n"
        "       float edge = smoothstep(1.0, 0.86, rad) * 0.35;\n"
        "       a = core + edge;\n"
        "   }\n"
        "   a *= uAlpha * uAlphaScale;\n"
        "   if (a <= 0.002)\n"
        "       discard;\n"
        "   FragColor = vec4(uColor * uTint * uIntensity * a, a);\n"
        "}\n";

    flareProgram = buildProgram(flareVertex, flareFragment);
    uCenter = glGetUniformLocation(flareProgram, "uCenter");
    uSize = glGetUniformLocation(flareProgram, "uSize");
    uAspect = glGetUniformLocation(flareProgram, "uAspect");
    uColor = glGetUniformLocation(flareProgram, "uColor");
    uTint = glGetUniformLocation(flareProgram, "uTint");
    uAlpha = glGetUniformLocation(flareProgram, "uAlpha");
    uAlphaScale = glGetUniformLocation(flareProgram, "uAlphaScale");
    uRing = glGetUniformLocation(flareProgram, "uRing");
    uIntensity = glGetUniformLocation(flareProgram, "uIntensity");
    uCamPos = glGetUniformLocation(flareProgram, "uCamPos");
    uFront = glGetUniformLocation(flareProgram, "uFront");
    uRight = glGetUniformLocation(flareProgram, "uRight");
    uUp = glGetUniformLocation(flareProgram, "uUp");
    uTanHalfV = glGetUniformLocation(flareProgram, "uTanHalfV");
    uWaterY = glGetUniformLocation(flareProgram, "uWaterY");
    uWaterCenter = glGetUniformLocation(flareProgram, "uWaterCenter");
    uWaterHalf = glGetUniformLocation(flareProgram, "uWaterHalf");
    uViewProj = glGetUniformLocation(flareProgram, "uViewProj");
    uUseWaterMask = glGetUniformLocation(flareProgram, "uUseWaterMask");

    const char *occVertex =
        "#version 460 core\n"
        "in vec2 aPosition;\n"
        "uniform vec2 uCenter;\n"
        "uniform vec2 uHalf;\n"
        "uniform float uDepth;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = vec4(uCenter + aPosition * uHalf, uDepth, 1.0);\n"
        "}\n";

    const char *occFragment =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main(void)\n"
        "{\n"
        "   FragColor = vec4(1.0);\n"
        "}\n";

    occProgram = buildProgram(occVertex, occFragment);
    uOccCenter = glGetUniformLocation(occProgram, "uCenter");
    uOccHalf = glGetUniformLocation(occProgram, "uHalf");
    uOccDepth = glGetUniformLocation(occProgram, "uDepth");

    GLfloat quad[] =
    {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };

    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);
    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenQueries(1, &sunQuery);

    return TRUE;
}

static bool projectPoint(vmath::vec3 worldPoint, vmath::mat4 viewProjectionT, vmath::vec2 &outNdc, float &outDepth)
{
    vmath::vec4 clip = vmath::vec4(worldPoint, 1.0f) * viewProjectionT;
    if (clip[3] <= 0.001f)
        return false;

    float invW = 1.0f / clip[3];
    outNdc = vmath::vec2(clip[0] * invW, clip[1] * invW);
    outDepth = clip[2] * invW;
    return true;
}

void renderWaterLensFlare(const WaterLensFlareParams &params, Camera *pCamera, vmath::mat4 projectionMatrix, WaterParams water, int screenWidth, int screenHeight)
{
    vmath::mat4 viewMatrix = pCamera->getLookAtMatrix();
    vmath::mat4 viewProj = projectionMatrix * viewMatrix;
    vmath::mat4 viewProjectionT = viewProj.transpose();

    vmath::vec2 sunNdc;
    float sunDepth = 0.0f;
    if (!projectPoint(params.sunWorldPosition, viewProjectionT, sunNdc, sunDepth))
    {
        visibilityTarget = 0.0f;
        visibility += (visibilityTarget - visibility) * 0.08f;
        return;
    }

    vmath::vec2 endpointNdc;
    if (params.clipToWater)
    {
        vmath::vec3 reflectedSun = vmath::vec3(params.sunWorldPosition[0], 2.0f * water.translation[1] - params.sunWorldPosition[1], params.sunWorldPosition[2]);
        float reflectedDepth = 0.0f;
        endpointNdc = sunNdc;
        projectPoint(reflectedSun, viewProjectionT, endpointNdc, reflectedDepth);
    }
    else
    {
        endpointNdc = vmath::vec2(-sunNdc[0], -sunNdc[1]);
    }

    float aspect = (float)screenWidth / (float)screenHeight;

    GLint previousDepthFunc = GL_LESS;
    glGetIntegerv(GL_DEPTH_FUNC, &previousDepthFunc);

    if (params.useOcclusion)
    {
        if (queryRunning)
        {
            GLuint available = 0;
            glGetQueryObjectuiv(sunQuery, GL_QUERY_RESULT_AVAILABLE, &available);
            if (available)
            {
                GLuint passed = 0;
                glGetQueryObjectuiv(sunQuery, GL_QUERY_RESULT, &passed);
                float fraction = (float)passed / (proxyPixels > 1.0f ? proxyPixels : 1.0f);
                if (fraction > 1.0f)
                    fraction = 1.0f;
                visibilityTarget = fraction;
                queryRunning = false;
            }
        }

        visibility += (visibilityTarget - visibility) * 0.08f;

        vmath::vec2 proxyHalf = vmath::vec2(0.020f / aspect, 0.020f);
        proxyPixels = (proxyHalf[0] * (float)screenWidth) * (proxyHalf[1] * (float)screenHeight);

        if (!queryRunning && sunNdc[0] > -1.2f && sunNdc[0] < 1.2f && sunNdc[1] > -1.2f && sunNdc[1] < 1.2f)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glDepthMask(GL_FALSE);
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

            glUseProgram(occProgram);
            glUniform2f(uOccCenter, sunNdc[0], sunNdc[1]);
            glUniform2f(uOccHalf, proxyHalf[0], proxyHalf[1]);
            glUniform1f(uOccDepth, sunDepth);

            glBeginQuery(GL_SAMPLES_PASSED, sunQuery);
            glBindVertexArray(quadVao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
            glEndQuery(GL_SAMPLES_PASSED);
            queryRunning = true;

            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
            glDepthMask(GL_TRUE);
        }

        glDepthFunc(previousDepthFunc);
    }
    else
    {
        visibility = params.externalVisibility;
    }

    if (visibility < 0.01f)
    {
        glUseProgram(0);
        return;
    }

    GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
    GLboolean blendWasEnabled = glIsEnabled(GL_BLEND);

    if (params.clipToWater)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glUseProgram(flareProgram);
    glUniform1f(uAspect, aspect);
    glUniform3fv(uCamPos, 1, pCamera->m_position);
    glUniform3fv(uFront, 1, pCamera->m_frontVector);
    glUniform3fv(uRight, 1, pCamera->m_rightVector);
    glUniform3fv(uUp, 1, pCamera->m_upVector);
    glUniform1f(uTanHalfV, tanf(0.5f * 45.0f * (float)M_PI / 180.0f));
    glUniform1f(uWaterY, water.translation[1]);
    glUniform2f(uWaterCenter, water.translation[0], water.translation[2]);
    glUniform2f(uWaterHalf, water.scale[0], water.scale[2]);
    glUniformMatrix4fv(uViewProj, 1, GL_FALSE, viewProj);
    glUniform1i(uUseWaterMask, params.clipToWater ? 1 : 0);
    glUniform3fv(uTint, 1, params.tintColor);
    glUniform1f(uAlphaScale, params.alphaScale);

    glBindVertexArray(quadVao);

    bool customDirection = (params.chainDirection[0] * params.chainDirection[0] + params.chainDirection[1] * params.chainDirection[1]) > 0.000001f;

    for (int i = 0; i < ghostCount; i++)
    {
        float centerX;
        float centerY;
        if (customDirection)
        {
            centerX = sunNdc[0] + params.chainDirection[0] * ghosts[i].position;
            centerY = sunNdc[1] + params.chainDirection[1] * ghosts[i].position;
        }
        else
        {
            centerX = sunNdc[0] + (endpointNdc[0] - sunNdc[0]) * ghosts[i].position + params.slant * ghosts[i].position;
            centerY = sunNdc[1] + (endpointNdc[1] - sunNdc[1]) * ghosts[i].position;
        }

        glUniform2f(uCenter, centerX, centerY);
        glUniform1f(uSize, ghosts[i].radius * params.sizeScale);
        glUniform3f(uColor, ghosts[i].r, ghosts[i].g, ghosts[i].b);
        glUniform1f(uAlpha, ghosts[i].alpha);
        glUniform1f(uRing, ghosts[i].ring);
        glUniform1f(uIntensity, visibility * params.intensity);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
    glUseProgram(0);

    glDepthMask(GL_TRUE);
    glDepthFunc(previousDepthFunc);

    if (!blendWasEnabled)
        glDisable(GL_BLEND);
    if (depthWasEnabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void uninitializeWaterLensFlare(void)
{
    if (sunQuery)
    {
        glDeleteQueries(1, &sunQuery);
        sunQuery = 0;
    }
    if (quadVbo)
    {
        glDeleteBuffers(1, &quadVbo);
        quadVbo = 0;
    }
    if (quadVao)
    {
        glDeleteVertexArrays(1, &quadVao);
        quadVao = 0;
    }
    if (occProgram)
    {
        glDeleteProgram(occProgram);
        occProgram = 0;
    }
    if (flareProgram)
    {
        glDeleteProgram(flareProgram);
        flareProgram = 0;
    }
}
