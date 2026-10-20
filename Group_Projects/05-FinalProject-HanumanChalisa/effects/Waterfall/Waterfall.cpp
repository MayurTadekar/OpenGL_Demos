#include "../include/common.h"
#include "Waterfall.h"
#include "../../modules/Texture/Texture.h"
#include "../modules/Camera/Camera.h"

#include <time.h>
#include <math.h>

// Number of quads that act as particles
const int NUM_WATER_PIECES = 3500;

// OpenGL Related Global Variables
HDC NRD_ghdc = NULL; // Global Handle to Device Context

// Shader related Global variables
static GLuint NRD_shaderProgramObject = 0;

static GLuint vao = 0;
static GLuint vbo_position = 0;
static GLuint vbo_texcoord = 0;
static GLuint vbo_phase = 0;
static GLuint mvpMatrixUniform = 0;

// Waterfall-specific uniforms
static GLuint g_uWaterSampler = 0;
static GLuint g_uNoiseSampler = 0;
static GLuint g_uTime = 0;

// Waterfall world placement
static float g_waterPosX = 0.0f;
static float g_waterPosY = 0.0f;
static float g_waterPosZ = -6.0f;

static float g_waterScaleX = 1.0f;
static float g_waterScaleY = 1.0f;
static float g_waterScaleZ = 1.0f;

// Textures
static GLuint g_textureWater = 0;
static GLuint g_textureNoise = 0;
Texture watertexture;
Texture noisetexture;

// Waterfall particle representation: each is a quad
struct WaterPiece
{
    float x;           // center X in local space
    float y;           // top Y position in local space
    float speed;       // falling speed
    float halfSizeX;   // half width of quad
    float halfSizeY;   // half height of quad
    float phase;       // per-particle phase for jitter & UV
    float zOffsetBase; // per-particle static Z offset
};

// Particle array
static WaterPiece g_pieces[NUM_WATER_PIECES];

// Geometry buffers (CPU-side arrays)
static GLfloat* g_waterPositions = NULL; // 3 floats per vertex
static GLfloat* g_waterTexcoords = NULL; // 2 floats per vertex
static GLfloat* g_waterPhases    = NULL; // 1 float per vertex
static int      g_numWaterVertices = 0;  // NUM_WATER_PIECES * 4

static mat4 perpectiveProjectionMatrix;

// Animation time
static GLfloat g_time = 0.0f;

// Function Declarations
void renderWaterfall(WaterfallParams params,
                     const vmath::mat4 &viewMatrix,
                     const vmath::mat4 &projectionMatrix);
void updateWaterfall(void);
static void initWaterParticles(void);
static void rebuildWaterPositions(void);
static void updateWaterParticles(float dt);

// Helper: random float in [minVal,maxVal]
float randRange(float minVal, float maxVal)
{
    return minVal + (maxVal - minVal) * ((float)rand() / (float)RAND_MAX);
}

int initializeWaterfall()
{
    /************* VERTEX SHADER *************/
    const GLchar* vertexShaderSourceCode =
        "#version 460 core\n"
        "in vec4 aPosition;\n"
        "in vec2 aTexCoord;\n"
        "in float aPhase;\n"
        "out vec2 vTexCoord;\n"
        "out float vPhase;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vTexCoord = aTexCoord;\n"
        "    vPhase = aPhase;\n"
        "}\n";

    GLuint NRD_vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(NRD_vertexShaderObject, 1, &vertexShaderSourceCode, NULL);
    glCompileShader(NRD_vertexShaderObject);

    GLint  NRD_status = 0;
    GLint  NRD_infoLogLength = 0;
    GLchar* NRD_szInfoLog = NULL;

    glGetShaderiv(NRD_vertexShaderObject, GL_COMPILE_STATUS, &NRD_status);
    if (NRD_status == GL_FALSE)
    {
        glGetShaderiv(NRD_vertexShaderObject, GL_INFO_LOG_LENGTH, &NRD_infoLogLength);
        if (NRD_infoLogLength > 0)
        {
            NRD_szInfoLog = (GLchar*)malloc(NRD_infoLogLength * sizeof(GLchar));
            if (NRD_szInfoLog != NULL)
            {
                glGetShaderInfoLog(NRD_vertexShaderObject, NRD_infoLogLength, NULL, NRD_szInfoLog);
                fprintf(gpFILE, "NRD: Vertex Shader compilation log = %s\n", NRD_szInfoLog);
                free(NRD_szInfoLog);
                NRD_szInfoLog = NULL;
            }
        }
        uninitializeWaterfall();
    }

    /************* FRAGMENT SHADER *************/
    const GLchar* NRD_fragmentShaderSourceCode =
        "#version 460 core\n"
        "in vec2 vTexCoord;\n"
        "in float vPhase;\n"
        "uniform sampler2D uWaterTex;\n"
        "uniform sampler2D uNoiseTex;\n"
        "uniform float uTime;\n"
        "out vec4 FragColor;\n"
        "void main(void)\n"
        "{\n"
        "    float timePhase = uTime + vPhase;\n"
        "\n"
        "    // 1) Base UV flow: move texture downward over time\n"
        "    float flowSpeed = 0.7;\n"
        "    vec2 flowUV = vec2(vTexCoord.x, vTexCoord.y + timePhase * flowSpeed);\n"
        "\n"
        "    // 2) Noise UV for distortion of the water texture\n"
        "    float noiseScale = 7.0;\n"
        "    float noiseScrollSpeed = 0.35;\n"
        "    vec2 noiseUV = vTexCoord * noiseScale + vec2(0.0, timePhase * noiseScrollSpeed);\n"
        "    vec2 noiseSample = texture(uNoiseTex, noiseUV).rg * 2.0 - 1.0;\n"
        "    float distortionStrength = 0.08;\n"
        "    vec2 distortedUV = flowUV + noiseSample * distortionStrength;\n"
        "\n"
        "    vec4 waterColor = texture(uWaterTex, distortedUV);\n"
        "\n"
        "    // 3) Vertical fades for top/bottom blending in each particle\n"
        "    float t = vTexCoord.y;\n"
        "    float topFadeStart = 0.0;\n"
        "    float topFadeEnd   = 0.18;\n"
        "    float bottomFadeStart = 0.8;\n"
        "    float bottomFadeEnd   = 1.0;\n"
        "\n"
        "    float fadeTop = clamp((t - topFadeStart) / (topFadeEnd - topFadeStart), 0.0, 1.0);\n"
        "    float fadeBottom = clamp((bottomFadeEnd - t) / (bottomFadeEnd - bottomFadeStart), 0.0, 1.0);\n"
        "    float fade = min(fadeTop, fadeBottom);\n"
        "\n"
        "    float foamFactor = smoothstep(bottomFadeStart, bottomFadeEnd, t);\n"
        "    vec3 finalColor = mix(waterColor.rgb, vec3(1.0), foamFactor * 0.35);\n"
        "\n"
        "    // 4) Shape mask: thin, noisy vertical streak\n"
        "    float u = vTexCoord.x;\n"
        "    float v = vTexCoord.y;\n"
        "\n"
        "    // Narrow vertical band\n"
        "    float center = 0.5;\n"
        "    float halfWidth = 0.18;\n"
        "    float xDist = abs(u - center);\n"
        "    float bandMask = smoothstep(halfWidth, halfWidth * 0.7, xDist);\n"
        "\n"
        "    // Vertical breakup\n"
        "    float stripeFreq = 9.0;\n"
        "    float stripes = 0.5 + 0.5 * sin(v * stripeFreq + timePhase * 4.5);\n"
        "\n"
        "    // Edge noise to erode the shape\n"
        "    vec2 edgeNoiseUV = vec2(u * 9.0, v * 18.0 + timePhase * 2.0);\n"
        "    float edgeNoise = texture(uNoiseTex, edgeNoiseUV).r;\n"
        "    float noiseInfluence = 0.85;\n"
        "    float noisy = mix(1.0, edgeNoise, noiseInfluence);\n"
        "\n"
        "    float mask = bandMask * stripes * noisy;\n"
        "\n"
        "    float alpha = waterColor.a * fade * mask;\n"
        "    if(alpha < 0.15)\n"
        "        discard;\n"
        "\n"
        "    FragColor = vec4(finalColor, alpha);\n"
        "}\n";

    GLuint NRD_fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(NRD_fragmentShaderObject, 1, &NRD_fragmentShaderSourceCode, NULL);
    glCompileShader(NRD_fragmentShaderObject);

    NRD_status = 0;
    NRD_infoLogLength = 0;
    NRD_szInfoLog = NULL;

    glGetShaderiv(NRD_fragmentShaderObject, GL_COMPILE_STATUS, &NRD_status);
    if (NRD_status == GL_FALSE)
    {
        glGetShaderiv(NRD_fragmentShaderObject, GL_INFO_LOG_LENGTH, &NRD_infoLogLength);
        if (NRD_infoLogLength > 0)
        {
            NRD_szInfoLog = (GLchar*)malloc(NRD_infoLogLength * sizeof(GLchar));
            if (NRD_szInfoLog != NULL)
            {
                glGetShaderInfoLog(NRD_fragmentShaderObject, NRD_infoLogLength, NULL, NRD_szInfoLog);
                fprintf(gpFILE, "NRD: Fragment shader compilation log is '%s'\n", NRD_szInfoLog);
                free(NRD_szInfoLog);
                NRD_szInfoLog = NULL;
            }
        }
        uninitializeWaterfall();
    }

    // Create / Attach / Link shader program
    NRD_shaderProgramObject = glCreateProgram();
    glAttachShader(NRD_shaderProgramObject, NRD_vertexShaderObject);
    glAttachShader(NRD_shaderProgramObject, NRD_fragmentShaderObject);

    glBindAttribLocation(NRD_shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(NRD_shaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");
    glBindAttribLocation(NRD_shaderProgramObject, AMC_ATTRIBUTE_COLOR, "aPhase");

    glLinkProgram(NRD_shaderProgramObject);

    NRD_status = 0;
    NRD_infoLogLength = 0;
    NRD_szInfoLog = NULL;

    glGetProgramiv(NRD_shaderProgramObject, GL_LINK_STATUS, &NRD_status);
    if (NRD_status == GL_FALSE)
    {
        glGetProgramiv(NRD_shaderProgramObject, GL_INFO_LOG_LENGTH, &NRD_infoLogLength);
        if (NRD_infoLogLength > 0)
        {
            NRD_szInfoLog = (GLchar*)malloc(NRD_infoLogLength * sizeof(GLchar));
            if (NRD_szInfoLog != NULL)
            {
                glGetProgramInfoLog(NRD_shaderProgramObject, NRD_infoLogLength, NULL, NRD_szInfoLog);
                fprintf(gpFILE, "NRD: Shader program link log : %s\n", NRD_szInfoLog);
                free(NRD_szInfoLog);
                NRD_szInfoLog = NULL;
            }
        }
        uninitializeWaterfall();
    }

    // Get uniforms
    mvpMatrixUniform = glGetUniformLocation(NRD_shaderProgramObject, "uMVPMatrix");
    g_uWaterSampler  = glGetUniformLocation(NRD_shaderProgramObject, "uWaterTex");
    g_uNoiseSampler  = glGetUniformLocation(NRD_shaderProgramObject, "uNoiseTex");
    g_uTime          = glGetUniformLocation(NRD_shaderProgramObject, "uTime");

    // Seed random for particles
    srand((unsigned int)time(NULL));

    // Initialize particle data and CPU-side arrays
    initWaterParticles();
    rebuildWaterPositions();

    // pre-simulate
    // How long to pre-run the simulation (seconds)
    float preSimTime = 4.0f;      // 2–5 seconds
    float preDt      = 0.016f * 1.2f; // same as runtime dt
    int   steps      = (int)(preSimTime / preDt);

    for (int i = 0; i < steps; ++i)
    {
        // update particles without drawing
        updateWaterParticles(preDt);
        g_time += preDt;
    }

    // VAO + VBOs
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Position VBO (dynamic)
    glGenBuffers(1, &vbo_position);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * g_numWaterVertices * 3,
                 g_waterPositions,
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Texcoord VBO (static)
    glGenBuffers(1, &vbo_texcoord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoord);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * g_numWaterVertices * 2,
                 g_waterTexcoords,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Phase VBO (static)
    glGenBuffers(1, &vbo_phase);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_phase);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * g_numWaterVertices,
                 g_waterPhases,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(AMC_ATTRIBUTE_COLOR, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(AMC_ATTRIBUTE_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    watertexture = loadTexture("./resources/Texture/waterfall.bmp", FALSE);
    noisetexture = loadTexture("./resources/Texture/waterfallnoise.bmp", FALSE);

    g_textureWater = watertexture.id;
    g_textureNoise = noisetexture.id;

    perpectiveProjectionMatrix = mat4::identity();

    fprintf(gpFILE, "NRD: Waterfall Initialization Successful! with %d, %d\n", g_textureWater, g_textureNoise);

    return 0;
}

// Initialize particle attributes and static arrays
static void initWaterParticles(void)
{
    float topY    = 2.0f;
    float bottomY = -1.0f;

    g_numWaterVertices = NUM_WATER_PIECES * 4;

    if (g_waterPositions) free(g_waterPositions);
    if (g_waterTexcoords) free(g_waterTexcoords);
    if (g_waterPhases)    free(g_waterPhases);

    g_waterPositions = (GLfloat*)malloc(sizeof(GLfloat) * g_numWaterVertices * 3);
    g_waterTexcoords = (GLfloat*)malloc(sizeof(GLfloat) * g_numWaterVertices * 2);
    g_waterPhases    = (GLfloat*)malloc(sizeof(GLfloat) * g_numWaterVertices);

    int t  = 0;
    int ph = 0;

    for (int i = 0; i < NUM_WATER_PIECES; ++i)
    {
        // Height
        g_pieces[i].y = randRange(bottomY, topY);

        float h = (g_pieces[i].y - bottomY) / (topY - bottomY);
        if (h < 0.0f) h = 0.0f;
        if (h > 1.0f) h = 1.0f;

        float maxHalfWidthTop    = 0.15f;
        float maxHalfWidthBottom = 0.6f;

        float maxHalfWidth = maxHalfWidthTop +
                             (1.0f - h) * (maxHalfWidthBottom - maxHalfWidthTop);

        float u = randRange(-1.0f, 1.0f);
        float sign = (u < 0.0f) ? -1.0f : 1.0f;
        float bias = sign * (u * u);

        g_pieces[i].x = bias * maxHalfWidth;

        // Faster falling speed
        g_pieces[i].speed = randRange(0.9f, 2.5f);

        // More varied quad sizes (less tiling)
        g_pieces[i].halfSizeX = randRange(0.03f, 0.10f);
        g_pieces[i].halfSizeY = randRange(0.12f, 0.28f);

        // Phase
        g_pieces[i].phase = randRange(0.0f, 6.28318f);

        // Per-particle base Z offset
        g_pieces[i].zOffsetBase = randRange(-0.18f, 0.18f);

        // Static UVs
        g_waterTexcoords[t++] = 1.0f; g_waterTexcoords[t++] = 1.0f;
        g_waterTexcoords[t++] = 0.0f; g_waterTexcoords[t++] = 1.0f;
        g_waterTexcoords[t++] = 0.0f; g_waterTexcoords[t++] = 0.0f;
        g_waterTexcoords[t++] = 1.0f; g_waterTexcoords[t++] = 0.0f;

        // Phase attribute
        g_waterPhases[ph++] = g_pieces[i].phase;
        g_waterPhases[ph++] = g_pieces[i].phase;
        g_waterPhases[ph++] = g_pieces[i].phase;
        g_waterPhases[ph++] = g_pieces[i].phase;
    }
}

// Rebuild CPU-side positions using cone, quadratic Bezier X, sine Z
static void rebuildWaterPositions(void)
{
    int p = 0;

    float jitterAmp  = 0.05f;
    float jitterFreq = 3.0f;

    float topY    = 2.0f;
    float bottomY = -2.2f;
    float maxHalfWidthTop    = 0.2f;
    float maxHalfWidthBottom = 0.6f;

    // Sine motion in Z
    float sineAmplitude = 0.35f;
    float sineFreq      = 2.0f;
    float sineSpeed     = 1.8f;

    // Quadratic Bezier control for X offset (bottom, mid, top)
    float P0 = -0.15f; // bottom bend
    float P1 =  0.00f; // mid
    float P2 =  0.18f; // top bend

    for (int i = 0; i < NUM_WATER_PIECES; ++i)
    {
        WaterPiece &w = g_pieces[i];

        float h = (w.y - bottomY) / (topY - bottomY);
        if (h < 0.0f) h = 0.0f;
        if (h > 1.0f) h = 1.0f;

        float jitter = jitterAmp * sinf(jitterFreq * g_time + w.phase);
        float baseX  = w.x + jitter;

        float maxHalfWidth = maxHalfWidthTop +
                             (1.0f - h) * (maxHalfWidthBottom - maxHalfWidthTop);

        float baseXClamped = baseX;
        if (baseXClamped < -maxHalfWidth) baseXClamped = -maxHalfWidth;
        if (baseXClamped >  maxHalfWidth) baseXClamped =  maxHalfWidth;

        // Quadratic Bezier X offset
        float oneMinusH = 1.0f - h;
        float bezierOffset =
            oneMinusH * oneMinusH * P0 +
            2.0f * oneMinusH * h * P1 +
            h * h * P2;

        float curvedX = baseXClamped + bezierOffset;
        if (curvedX < -maxHalfWidth) curvedX = -maxHalfWidth;
        if (curvedX >  maxHalfWidth) curvedX =  maxHalfWidth;

        // Sine + per-particle base Z
        float zOffset = w.zOffsetBase +
                        sineAmplitude * sinf(sineFreq * w.y + sineSpeed * g_time + w.phase);

        float left   = curvedX - w.halfSizeX;
        float right  = curvedX + w.halfSizeX;
        float top    = w.y;
        float bottom = w.y - (2.0f * w.halfSizeY);

        g_waterPositions[p++] = right; g_waterPositions[p++] = top;    g_waterPositions[p++] = zOffset;
        g_waterPositions[p++] = left;  g_waterPositions[p++] = top;    g_waterPositions[p++] = zOffset;
        g_waterPositions[p++] = left;  g_waterPositions[p++] = bottom; g_waterPositions[p++] = zOffset;
        g_waterPositions[p++] = right; g_waterPositions[p++] = bottom; g_waterPositions[p++] = zOffset;
    }
}

// Update particles and stream positions to VBO
static void updateWaterParticles(float dt)
{
    const float bottomLimit = -2.2f;
    const float topRespawn  =  2.2f;

    for (int i = 0; i < NUM_WATER_PIECES; ++i)
    {
        WaterPiece &w = g_pieces[i];
        w.y -= w.speed * dt;

        if (w.y < bottomLimit)
        {
            w.y     = topRespawn + randRange(0.0f, 1.0f);
            w.x     = randRange(-0.5f, 0.5f);
            w.speed = randRange(0.9f, 2.5f);
            w.phase = randRange(0.0f, 6.28318f);
            w.zOffsetBase = randRange(-0.18f, 0.18f);
        }
    }

    rebuildWaterPositions();

    glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    sizeof(GLfloat) * g_numWaterVertices * 3,
                    g_waterPositions);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void renderWaterfall(WaterfallParams params,
                     const vmath::mat4 &viewMatrix,
                     const vmath::mat4 &projectionMatrix)
{
    glUseProgram(NRD_shaderProgramObject);

    mat4 modelMatrix = mat4::identity();

    mat4 S = vmath::scale(
        params.scale[0],
        params.scale[1],
        params.scale[2]);

    mat4 T = vmath::translate(
        params.translation[0],
        params.translation[1],
        params.translation[2]);

    mat4 Rx = vmath::rotate(
        params.rotationAngle[0],
        params.rotationAxis[0][0],
        params.rotationAxis[0][1],
        params.rotationAxis[0][2]);

    mat4 Ry = vmath::rotate(
        params.rotationAngle[1],
        params.rotationAxis[1][0],
        params.rotationAxis[1][1],
        params.rotationAxis[1][2]);

    mat4 Rz = vmath::rotate(
        params.rotationAngle[2],
        params.rotationAxis[2][0],
        params.rotationAxis[2][1],
        params.rotationAxis[2][2]);

    mat4 R = Ry * Rx * Rz;

    modelMatrix = T * R * S;

    mat4 modelViewMatrix           = viewMatrix * modelMatrix;
    mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

    glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelViewProjectionMatrix);
    glUniform1f(g_uTime, g_time);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_textureWater);
    glUniform1i(g_uWaterSampler, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, g_textureNoise);
    glUniform1i(g_uNoiseSampler, 1);

    glBindVertexArray(vao);
    for (int i = 0; i < NUM_WATER_PIECES; ++i)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);

    glUseProgram(0);

    updateWaterfall();
}

void updateWaterfall(void)
{
    float dt = 0.016f * 1.2f; // slightly faster than 60fps baseline
    g_time += dt;
    updateWaterParticles(dt);
}

void uninitializeWaterfall(void)
{
    if (g_waterPositions)
    {
        free(g_waterPositions);
        g_waterPositions = NULL;
    }

    if (g_waterTexcoords)
    {
        free(g_waterTexcoords);
        g_waterTexcoords = NULL;
    }

    if (g_waterPhases)
    {
        free(g_waterPhases);
        g_waterPhases = NULL;
    }

    if (g_textureNoise)
    {
        glDeleteTextures(1, &g_textureNoise);
        g_textureNoise = 0;
    }

    if (g_textureWater)
    {
        glDeleteTextures(1, &g_textureWater);
        g_textureWater = 0;
    }

    if (vbo_phase)
    {
        glDeleteBuffers(1, &vbo_phase);
        vbo_phase = 0;
    }

    if (vbo_texcoord)
    {
        glDeleteBuffers(1, &vbo_texcoord);
        vbo_texcoord = 0;
    }

    if (vbo_position)
    {
        glDeleteBuffers(1, &vbo_position);
        vbo_position = 0;
    }

    if (vao)
    {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    if (NRD_shaderProgramObject)
    {
        glUseProgram(NRD_shaderProgramObject);
        GLint NRD_numShaders;
        glGetProgramiv(NRD_shaderProgramObject, GL_ATTACHED_SHADERS, &NRD_numShaders);
        if (NRD_numShaders > 0)
        {
            GLuint* NRD_pShaders = (GLuint*)malloc(NRD_numShaders * sizeof(GLuint));
            if (NRD_pShaders != NULL)
            {
                glGetAttachedShaders(NRD_shaderProgramObject, NRD_numShaders, NULL, NRD_pShaders);
                for (GLint i = 0; i < NRD_numShaders; i++)
                {
                    glDetachShader(NRD_shaderProgramObject, NRD_pShaders[i]);
                    glDeleteShader(NRD_pShaders[i]);
                    NRD_pShaders[i] = 0;
                }
                free(NRD_pShaders);
                NRD_pShaders = NULL;
            }
        }
        glUseProgram(0);
        glDeleteProgram(NRD_shaderProgramObject);
        NRD_shaderProgramObject = 0;
    }
}
