
// Cinematic Scene Transitions render with FBOs

#include "Transitions.h"
#include <stdio.h>
#include <math.h>

TransitionState gTransition = {FALSE, -1.0f, 2.0f, TRANSITION_NONE, 0, 0};
static float g_uProgress = 0.0f;

GLuint fboTransition = 0;
GLuint rboDepth = 0;
GLuint textureSceneA = 0;
GLuint textureSceneB = 0;

static GLuint shaderProgramTransition = 0;
static GLuint vaoQuad = 0;
static GLuint vboQuadPos = 0;
static GLuint vboQuadTex = 0;

static GLuint uProgressUniform = 0;
static GLuint uTransitionTypeUniform = 0;
static GLuint uSceneATextureUniform = 0;
static GLuint uSceneBTextureUniform = 0;

static int currentWidth = 1920;
static int currentHeight = 1080;

BOOL initializeTransitions(int width, int height)
{
    currentWidth = width;
    currentHeight = height;

    // ---- FBO ----
    glGenFramebuffers(1, &fboTransition);
    glBindFramebuffer(GL_FRAMEBUFFER, fboTransition);

    glGenTextures(1, &textureSceneA);
    glBindTexture(GL_TEXTURE_2D, textureSceneA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &textureSceneB);
    glBindTexture(GL_TEXTURE_2D, textureSceneB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("[Transitions] FBO incomplete\n");
        return FALSE;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ============================================================
    // TRANSITION FRAGMENT SHADER
    // All effects in one shader, selected by u_type uniform.
    // u_type == 1  FADE        : black-through crossfade
    // u_type == 2  DISSOLVE    : sand/dust grain dissolve
    // u_type == 3  RIPPLE      : water ripple warp
    // u_type == 4  BURN        : fire burn from bottom
    // u_type == 5  SPIN        : smooth spin
    // ============================================================

    const GLchar *vertexShaderSource =
        "#version 460 core\n"
        "in vec2 a_position;\n"
        "in vec2 a_texCoord;\n"
        "out vec2 v_texCoord;\n"
        "void main() {\n"
        "   v_texCoord  = a_texCoord;\n"
        "   gl_Position = vec4(a_position, 0.0, 1.0);\n"
        "}\n";

    const GLchar *fragmentShaderSource =
        "#version 460 core\n"
        "precision highp float;\n"
        "in  vec2 v_texCoord;\n"
        "out vec4 fragColor;\n"
        "\n"
        "uniform sampler2D u_sceneA;\n"   // outgoing (from)
        "uniform sampler2D u_sceneB;\n"   // incoming (to)
        "uniform float     u_progress;\n" // 0.0 → 1.0
        "uniform int       u_type;\n"
        "\n"

        // ---- Noise helpers ----
        // Hash — used by dissolve and shatter
        "float hash(vec2 p) {\n"
        "   p = fract(p * vec2(127.1, 311.7));\n"
        "   p += dot(p, p + 19.19);\n"
        "   return fract(p.x * p.y);\n"
        "}\n"
        // Value noise — smooth hash interpolation
        "float noise(vec2 p) {\n"
        "   vec2 i = floor(p);\n"
        "   vec2 f = fract(p);\n"
        "   f = f*f*(3.0-2.0*f);\n" // smoothstep
        "   return mix(mix(hash(i),          hash(i+vec2(1,0)), f.x),\n"
        "              mix(hash(i+vec2(0,1)), hash(i+vec2(1,1)), f.x), f.y);\n"
        "}\n"
        // Fractal noise — 4 octaves for organic texture
        "float fbm(vec2 p) {\n"
        "   float v = 0.0, a = 0.5;\n"
        "   for(int i=0;i<4;i++){ v += a*noise(p); p*=2.1; a*=0.5; }\n"
        "   return v;\n"
        "}\n"
        "\n"

        "void main() {\n"
        "   vec2 uv = v_texCoord;\n"
        "   float p = clamp(u_progress, 0.0, 1.0);\n"
        "\n"

        // ================================================================
        // TYPE 1 — CINEMATIC BLACK FADE
        // ================================================================
        // Scene A fades to black in first half (p 0→0.5)
        // Scene B fades in from black in second half (p 0.5→1.0)
        // Result: clean professional film cut through black.
        // ================================================================
        "   if (u_type == 1) {\n"
        "       vec4 A = texture(u_sceneA, uv);\n"
        "       vec4 B = texture(u_sceneB, uv);\n"
        "       float fadeA = 1.0 - smoothstep(0.0, 0.5, p);\n"
        "       float fadeB = smoothstep(0.5, 1.0, p);\n"
        "       vec3 col = A.rgb * fadeA + B.rgb * fadeB;\n"
        "       fragColor = vec4(col, 1.0);\n"
        "\n"

        // ================================================================
        // TYPE 2 — SAND / DUST DISSOLVE - After Effects "CC Pixel Polly" / sand particle effect.
        // ================================================================
        "   } else if (u_type == 2) {\n"
        "       vec4 A = texture(u_sceneA, uv);\n"
        "       vec4 B = texture(u_sceneB, uv);\n"
        // Multi-scale noise for organic grain — fine grain + coarse clumps
        "       float grain  = fbm(uv * 18.0) * 0.65\n"
        "                    + fbm(uv * 6.0 + vec2(3.7, 1.3)) * 0.35;\n"
        // Horizontal sweep — sand blows left to right
        "       float sweep  = uv.x * 0.35;\n"
        // Luminance delay — bright pixels dissolve last (divine glow)
        "       float luma   = dot(A.rgb, vec3(0.299, 0.587, 0.114));\n"
        "       float delay  = luma * 0.12;\n"
        // Final threshold per pixel
        "       float thresh = grain + sweep + delay;\n"
        // Soft edge band ±0.03 — avoids hard pixel-pop
        "       float edge   = smoothstep(thresh - 0.03, thresh + 0.03, p);\n"
        // Sparkle at the dissolve edge — gold particle shimmer
        "       float sparkle = (1.0 - abs(edge - 0.5) * 2.0);\n"
        "       sparkle = pow(sparkle, 6.0) * hash(uv * 91.3 + p) * 2.5;\n"
        "       vec3  goldSpark = vec3(1.0, 0.82, 0.3) * sparkle;\n"
        "       vec3  col = mix(A.rgb, B.rgb, edge) + goldSpark;\n"
        "       fragColor = vec4(col, 1.0);\n"
        "\n"

        // ================================================================
        // TYPE 3 — WATER RIPPLE WARP- After Effects "CC Ripple Pulse" / stone-in-pond.
        // ================================================================
        "   } else if (u_type == 3) {\n"
        "       vec2  center    = vec2(0.5, 0.5);\n"
        "       float dist      = length(uv - center);\n"
        // Wave parameters
        "       float waveFreq  = 22.0;\n" // rings — more = tighter ripples
        "       float waveSpeed = 3.5;\n"  // expansion speed
        // Bell curve amplitude — peaks at p=0.5, zero at p=0 and p=1
        "       float bellCurve = sin(p * 3.14159);\n"
        "       float amplitude = bellCurve * 0.028;\n"
        // Ripple phase — outward expansion
        "       float phase     = dist * waveFreq - p * waveSpeed * 6.28;\n"
        "       float ripple    = sin(phase) * amplitude;\n"
        // Apply radial UV warp to scene A
        "       vec2  dir       = normalize(uv - center + vec2(0.001));\n"
        "       vec2  warpedUV  = uv + dir * ripple;\n"
        "       warpedUV        = clamp(warpedUV, 0.001, 0.999);\n"
        "       vec4  A         = texture(u_sceneA, warpedUV);\n"
        "       vec4  B         = texture(u_sceneB, uv);\n"
        // Radial reveal — scene B appears from center outward
        // The reveal front tracks slightly ahead of the wave
        "       float revealFront = p * 1.3 - dist;\n"
        "       float blend       = smoothstep(0.0, 0.35, revealFront);\n"
        // Water caustic shimmer at the wave edge
        "       float shimmer     = pow(max(0.0, sin(phase + 1.57)), 4.0)\n"
        "                         * bellCurve * 0.4;\n"
        "       vec3  caustic     = vec3(0.55, 0.82, 1.0) * shimmer;\n"
        "       vec3  col         = mix(A.rgb, B.rgb, blend) + caustic;\n"
        "       fragColor         = vec4(col, 1.0);\n"
        "\n"

        // ================================================================
        // TYPE 4 — FIRE BURN (bottom to top)
        // ================================================================
        "   } else if (u_type == 4) {\n"
        "       vec4 A = texture(u_sceneA, uv);\n"
        "       vec4 B = texture(u_sceneB, uv);\n"
        // Flame front rises from 0 (bottom) to 1 (top) as p increases
        "       float flameFront = p * 1.3;\n"
        // Turbulent flame edge using fbm noise
        "       float turbulence = fbm(vec2(uv.x * 4.0, uv.y * 2.0 - p * 3.0)) * 0.25;\n"
        "       float edge       = smoothstep(flameFront - 0.08, flameFront + 0.08,\n"
        "                                     uv.y + turbulence);\n"
        // Heat distortion above the flame front — wavy UV offset
        "       float heat       = fbm(vec2(uv.x * 8.0, uv.y * 4.0 + p * 5.0)) * 0.012 * edge;\n"
        "       vec2  distUV     = vec2(uv.x + heat, uv.y);\n"
        "       vec4  Adist      = texture(u_sceneA, clamp(distUV, 0.001, 0.999));\n"
        // Fire glow at the front edge
        "       float glowBand = pow(max(0.0, 1.0 - abs(edge - 0.5) * 6.0), 2.0);\n"
        "       float flameNoise = fbm(vec2(uv.x * 20.0, uv.y * 10.0 - p * 8.0));\n"
        "       float flameBand = smoothstep(0.35, 0.9, glowBand + flameNoise * 0.5);\n"
        "       vec3 fireCore = vec3(1.0, 0.95, 0.3);\n"
        "       vec3 fireMid  = vec3(1.0, 0.45, 0.0);\n"
        "       vec3 fireDark = vec3(0.7, 0.05, 0.0);\n"
        "       vec3 fireColor = mix(fireDark, fireMid, flameBand);\n"
        "       fireColor = mix(fireColor, fireCore, glowBand);\n"
        "       vec3  col        = mix(B.rgb, Adist.rgb, edge);\n"
        "       col             += fireColor * glowBand * 1.8;\n"
        "       fragColor        = vec4(col, 1.0);\n"
        "\n"

        // ================================================================
        // TYPE 5 — Smooth Spin Transition
        // ================================================================
        "   } else if (u_type == 5) {\n"

        "       vec2 center = vec2(0.5, 0.5);\n"

        "       float angleA = p * 2.2;\n"
        "       float angleB = (1.0 - p) * -2.2;\n"

        "       float zoomA = mix(1.0, 0.6, p);\n"
        "       float zoomB = mix(1.4, 1.0, p);\n"

        "       vec2 uvA = uv - center;\n"
        "       vec2 uvB = uv - center;\n"

        "       mat2 rotA = mat2(\n"
        "           cos(angleA), -sin(angleA),\n"
        "           sin(angleA),  cos(angleA));\n"

        "       mat2 rotB = mat2(\n"
        "           cos(angleB), -sin(angleB),\n"
        "           sin(angleB),  cos(angleB));\n"

        "       uvA = rotA * uvA;\n"
        "       uvB = rotB * uvB;\n"

        "       uvA *= zoomA;\n"
        "       uvB *= zoomB;\n"

        "       uvA += center;\n"
        "       uvB += center;\n"

        "       vec4 A = texture(\n"
        "           u_sceneA,\n"
        "           clamp(uvA, 0.001, 0.999));\n"

        "       vec4 B = texture(\n"
        "           u_sceneB,\n"
        "           clamp(uvB, 0.001, 0.999));\n"

        "       float blend = smoothstep(\n"
        "           0.0,\n"
        "           1.0,\n"
        "           p);\n"

        "       fragColor = mix(A, B, blend);\n"

        "   } else {\n"
        "       fragColor = texture(u_sceneA, uv);\n"
        "   }\n"
        "}\n";

    // ---- Compile ----
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);
    GLint ok;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char b[1024];
        glGetShaderInfoLog(vs, 1024, NULL, b);
        printf("[Trans VS] %s\n", b);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char b[1024];
        glGetShaderInfoLog(fs, 1024, NULL, b);
        printf("[Trans FS] %s\n", b);
    }

    shaderProgramTransition = glCreateProgram();
    glAttachShader(shaderProgramTransition, vs);
    glAttachShader(shaderProgramTransition, fs);

    // Bind attribute locations
    glBindAttribLocation(shaderProgramTransition, 0, "a_position");
    glBindAttribLocation(shaderProgramTransition, 1, "a_texCoord");

    glLinkProgram(shaderProgramTransition);
    glGetProgramiv(shaderProgramTransition, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char b[1024];
        glGetProgramInfoLog(shaderProgramTransition, 1024, NULL, b);
        printf("[Trans Link] %s\n", b);
    }

    glDetachShader(shaderProgramTransition, vs);
    glDeleteShader(vs);
    glDetachShader(shaderProgramTransition, fs);
    glDeleteShader(fs);

    uProgressUniform = glGetUniformLocation(shaderProgramTransition, "u_progress");
    uTransitionTypeUniform = glGetUniformLocation(shaderProgramTransition, "u_type");
    uSceneATextureUniform = glGetUniformLocation(shaderProgramTransition, "u_sceneA");
    uSceneBTextureUniform = glGetUniformLocation(shaderProgramTransition, "u_sceneB");

    // ---- Fullscreen quad ----
    const GLfloat quadPos[] = {
        -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
    const GLfloat quadTex[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};

    glGenVertexArrays(1, &vaoQuad);
    glBindVertexArray(vaoQuad);

    glGenBuffers(1, &vboQuadPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuadPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadPos), quadPos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboQuadTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboQuadTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadTex), quadTex, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    printf("[Transitions] initialized %dx%d\n", width, height);
    return TRUE;
}

void resizeTransitions(int width, int height)
{
    currentWidth = width;
    currentHeight = height;
    if (!fboTransition)
        return;
    glBindTexture(GL_TEXTURE_2D, textureSceneA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, textureSceneB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
}

void startSceneTransition(TransitionType type, int fromScene, int toScene, float duration)
{
    if (gTransition.isTransitioning)
        return;
    gTransition.isTransitioning = TRUE;
    gTransition.type = type;
    gTransition.fromSceneID = fromScene;
    gTransition.toSceneID = toScene;
    gTransition.duration = duration;
    gTransition.startTime = -1.0f;
    g_uProgress = 0.0f;
}

void updateTransitionProgress(float currentTime)
{
    if (!gTransition.isTransitioning)
        return;
    if (gTransition.startTime < 0.0f)
        gTransition.startTime = currentTime;
    float elapsed = currentTime - gTransition.startTime;
    g_uProgress = elapsed / gTransition.duration;
    if (g_uProgress >= 1.0f)
    {
        g_uProgress = 1.0f;
        gTransition.isTransitioning = FALSE;
    }
}

void bindTransitionFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, fboTransition); }
void unbindTransitionFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void renderTransitionOutput()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, currentWidth, currentHeight);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramTransition);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureSceneA);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureSceneB);

    glUniform1f(uProgressUniform, g_uProgress);
    glUniform1i(uTransitionTypeUniform, (int)gTransition.type);
    glUniform1i(uSceneATextureUniform, 0);
    glUniform1i(uSceneBTextureUniform, 1);

    glBindVertexArray(vaoQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(0);
}

void uninitializeTransitions()
{
    if (fboTransition)
    {
        glDeleteFramebuffers(1, &fboTransition);
        fboTransition = 0;
    }
    if (textureSceneA)
    {
        glDeleteTextures(1, &textureSceneA);
        textureSceneA = 0;
    }
    if (textureSceneB)
    {
        glDeleteTextures(1, &textureSceneB);
        textureSceneB = 0;
    }
    if (rboDepth)
    {
        glDeleteRenderbuffers(1, &rboDepth);
        rboDepth = 0;
    }
    if (vboQuadPos)
    {
        glDeleteBuffers(1, &vboQuadPos);
        vboQuadPos = 0;
    }
    if (vboQuadTex)
    {
        glDeleteBuffers(1, &vboQuadTex);
        vboQuadTex = 0;
    }
    if (vaoQuad)
    {
        glDeleteVertexArrays(1, &vaoQuad);
        vaoQuad = 0;
    }
    if (shaderProgramTransition)
    {
        glDeleteProgram(shaderProgramTransition);
        shaderProgramTransition = 0;
    }
}
