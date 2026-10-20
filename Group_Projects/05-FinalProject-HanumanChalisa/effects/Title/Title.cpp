#include "../include/common.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Title.h"
#include <stdio.h>


// Pipeline Program & Buffer Handles
static GLuint gShaderProgramObject = 0;
static GLuint gVaoQuad = 0;
static GLuint gVboPosition = 0;

// Generated Asset Handles
static GLuint gTextMaskTextureID = 0;
GLuint gCreditsTextureID = 0; // Separate texture handle for end credits

// Shader Uniform Locations
static GLuint gTextMaskTexUniform = 0;
static GLuint gTimeUniform = 0;
static GLuint gResolutionUniform = 0;
GLuint gIsCreditsUniform = 0;      // Controls shader text state
GLuint gScrollOffsetUniform = 0;   // Controls scroll translation offset

// Animation Variables

// End Credits State Tracking
bool g_bShowCredits = false;
float gScrollOffset = 0.95f; // Starts layout off-screen below the viewport

// End Credits Text Content
const char* gCreditsText[] = {
    "Concept and Direction",
    "-----------",
    "Shraddha Deshmukh",
    "(Group Leader)",
    "",
    "",
    "",
    "",
    "Our Valued Team:",
    "----------------",
    "Adesh Pathare",
    "Amol Nandkar",
    "Atharv Ambekar",
    "Gauri Dudhande",
    "Mayur Tadekar",
    "Nivrutti Damdhar",
    "Omkar Jadhav",    
    "Pankaj Hiwrale",
    "Prajwal Warade",
    "Shivkumar Ople",
    "",
    "",
    "",
    "",
    "Technical Specifications",
    "-----------------------------",
    "Rendering - OpenGL Programming",
    "Languages - C/C++",
    "Windowing - Win32 SDK",
    "",
    "",
    "",
    "",
    "References",
    "--------------------",
    "RTR All Assignments",
    "OpenGL Programming Guide (RED BOOK)",
    "OpenGL SuperBible",
    "",
    "",
    "",
    "",
    "OpenGL Graphics Concepts",
    "--------------------",
    "1. Triangulation",
    "2. Culling ",
    "3. Texture Mapping",
    "4. Anti-aliasing",
    "5. Clipping",
    "6. Vertex and Index Buffers",
    "7. Text Rendering Concepts like Glyphs, Bitmaps",
    "",
    "",
    "",
    "",
    "Graphical Effects",
    "--------------------",
    "1. Scene Lighting",
    "2. Fade Effect",
    "3. Fog Effect",
    "4. Lens Flare",
    "5. Water Lens Flare",
    "6. Water Rendering",
    "7. Grass Rendering",
    "8. Skybox",
    "9. Terrain Rendering",
    "10. Ocean Simulation",
    "11. Skydome",
    "12. God Rays (Crepuscular Rays)",
    "13. Snowfall",
    "14. Waterfall",
    "15. Dissolve Effect",
    "16. Title/Text Rendering",
    "17. Lightning with Flash",
    "18. Bloom Effect",
    "19. Fire (Procedural/Raymarching-based)",
    "20. Volumetric Clouds",
    "21. Shadow Mapping",
    "22. Physically Based Rendering (PBR)",
    "23. Boid Simulation",
    "24. Cinematic Scene Transitions",
    "",
    "",
    "",
    "",
    "Background Score",
    "---------------",
    "Song : Hanuman Chalisa",
    "Movie : Hanu-Man (2024)",
    "Singer : Saicharan",
    "Lyrics : Goswami Tulsīdās", 
    "Music Director : GowraHari",
    "",
    "",
    "",
    "",
    "Special Thanks",
    "--------------",
    "Dr. Rama Vijay Gokhale Ma'am",
    "Pradnya Gokhale Ma'am",
    "Yogeshwar Shukla Sir",
    "Radhika Shukla Ma'am",
    "Shailesh Ubhe",
    "Siddhant Kshirsagar",
    "Pratik Jagadale",
    "",
    "",
    "",
    "",
    "Our Inspiration",
    "--------------",
    "Dr. Vijay D. Gokhale Sir",
    "",
    "",
    "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "पवन तनय संकट हरन, मंगल मूरति रूप।",
    // "राम लखन सीता सहित, हृदय बसहु सुर भूप॥",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    ""
};
const int gCreditsLineCount = sizeof(gCreditsText) / sizeof(gCreditsText[0]);


// --- GPU Shader Architecture ---
static const GLchar* vertexShaderSource =
"#version 460 core\n"
"layout(location = 0) in vec2 a_position;\n"
"out vec2 v_texcoord;\n"
"void main(void) {\n"
"   gl_Position = vec4(a_position, 0.0, 1.0);\n"
"   v_texcoord = a_position * 0.5 + 0.5;\n" 
"}\n";

static const GLchar* fragmentShaderSource =
"#version 460 core\n"
"in vec2 v_texcoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D u_textMaskTex;\n"
"uniform float u_time;\n"
"uniform vec2 u_resolution;\n"
"uniform int u_isCredits;\n"
"uniform float u_scrollOffset;\n"
"\n"
"// --- CURVATURE SETTINGS ---\n"
"const float CURVATURE = 0.85;\n"
"\n"
"vec2 getCurvedUV(vec2 uv) {\n"
"    float xOffset = uv.x - 0.5;\n"
"    float yShift = CURVATURE * (xOffset * xOffset) * (uv.y - 0.5) * 2.0;\n"
"    return vec2(uv.x, uv.y - yShift);\n"
"}\n"
"\n"
"float hash(vec2 p) {\n"
"    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);\n"
"}\n"
"\n"
"float noise(vec2 p) {\n"
"    vec2 i = floor(p);\n"
"    vec2 f = fract(p);\n"
"    vec2 u = f * f * (3.0 - 2.0 * f);\n"
"    return mix(mix(hash(i + vec2(0.0,0.0)), hash(i + vec2(1.0,0.0)), u.x),\n"
"               mix(hash(i + vec2(0.0,1.0)), hash(i + vec2(1.0,1.0)), u.x), u.y);\n"
"}\n"
"\n"
"float fbm(vec2 p) {\n"
"    float value = 0.0;\n"
"    float amplitude = 0.5;\n"
"    mat2 rot = mat2(0.866, 0.5, -0.5, 0.866);\n"
"    for (int i = 0; i < 5; i++) {\n"
"        value += amplitude * noise(p);\n"
"        p = rot * p * 2.2 + vec2(23.13);\n"
"        amplitude *= 0.46;\n"
"    }\n"
"    return value;\n"
"}\n"
"\n"
"vec3 getFireSparks(vec2 uv, float time, sampler2D maskTex) {\n"
"    float fireSparks = 0.0;\n"
"    for (int k = 0; k < 8; k++) {\n"
"        float seed = float(k) * 12.9898;\n"
"        float layerOffset = float(k) * 0.04;\n"
"        float progress = fract(0.15 * time + layerOffset);\n"
"        float depth = mix(0.5, 15.0, progress);\n"
"        vec2 randomDir = vec2(hash(vec2(seed, 0.0)), hash(vec2(seed, 1.0))) * 2.0 - 1.0;\n"
"        vec2 centeredUV = uv - 0.5;\n"
"        vec2 projectedSpace = (centeredUV / depth) + (randomDir * progress * 0.3);\n"
"        projectedSpace.x += sin(time * 0.2 + seed) * 0.1;\n"
"        projectedSpace.y += cos(time * 0.15 + seed) * 0.1;\n"
"        float density = 15.0;\n"
"        vec2 pI = floor(projectedSpace * density);\n"
"        vec2 pF = fract(projectedSpace * density);\n"
"        float pRandom = hash(pI + vec2(float(k) * 57.43));\n"
"        \n"
"        if (pRandom > 0.45) {\n"
"            float d = length(pF - 0.5);\n"
"            float particleScale = 0.01 * (1.0 / (depth * 0.2)) * (0.5 + 0.5 * sin(time * 1.0 + seed));\n"
"            particleScale = clamp(particleScale, 0.01, 0.1);\n"
"            float alphaFade = smoothstep(0.0, 0.3, progress) * smoothstep(1.0, 0.5, progress);\n"
"            float proximityWeight = texture(maskTex, (u_isCredits == 1) ? uv : getCurvedUV(uv)).r * 0.3 + 0.7;\n"
"            fireSparks += smoothstep(particleScale, 0.0, d) * alphaFade * proximityWeight;\n"
"        }\n"
"    }\n"
"    vec3 sparkColor = mix(vec3(0.75, 0.18, 0.01), vec3(1.0, 0.6, 0.1), clamp(fireSparks * 2.0, 0.0, 1.0));\n"
"    return sparkColor * fireSparks * 4.0;\n"
"}\n"
"\n"
"float getGoldLeafTexture(vec2 p) {\n"
"    float foilWrinkles = fbm(p * 25.0) * 0.35;\n"
"    float fineGrain = noise(vec2(p.x * 500.0, p.y * 120.0)) * 0.05;\n"
"    float flakes = abs(noise(p * 60.0 + vec2(fbm(p * 12.0))) - 0.5);\n"
"    float edgeFlakes = smoothstep(0.02, 0.0, flakes) * 0.15;\n"
"    return foilWrinkles + fineGrain - edgeFlakes;\n"
"}\n"
"\n"
"float getCombinedHeight(vec2 uv) {\n"
"    vec2 curved = getCurvedUV(uv);\n"
"    float textMask = texture(u_textMaskTex, curved).r;\n"
"    if (textMask < 0.005) return 0.0;\n"
"    float goldRelief = getGoldLeafTexture(curved * 1.5);\n"
"    return textMask * (0.75 + goldRelief * 0.25);\n"
"}\n"
"\n"
"void main(void) {\n"
"    vec2 uv = v_texcoord;\n"
"    vec2 bgUV = uv; // Keep a pure static copy for backdrop vignettes\n"
"    \n"
"    if (u_isCredits == 1) {\n"
"        // Reduced scale from 0.125 to 0.0625 because texture height doubled to 16k\n"
"        uv.y = uv.y * 0.0625 + u_scrollOffset;\n"
"    }\n"
"    \n"
"    vec2 textUV = (u_isCredits == 1) ? uv : getCurvedUV(uv);\n"
"    \n"
"    float mainTextMask = (u_isCredits == 1) ? 0.0 : texture(u_textMaskTex, textUV).r;\n"
"    float subTextMask  = texture(u_textMaskTex, textUV).g;\n"
"    \n"
"    vec3 ambientOrange = vec3(0.55, 0.18, 0.01);\n"
"    float backdropIntensity = 0.0;\n"
"    \n"
"    // Identical horizontal bounds calculation for both layout modes\n"
"float horizontalBounds = 1.0;\n"
"if (u_isCredits == 1) {\n"
"    // Squeezes the edges in from 0.05 to 0.15 for narrower text\n"
"    horizontalBounds = smoothstep(0.15, 0.60, bgUV.x) * smoothstep(0.85, 0.50, bgUV.x);\n"
"} else {\n"
"    // Original wide bounds for HANUMAN\n"
"    horizontalBounds = smoothstep(0.05, 0.50, bgUV.x) * smoothstep(0.95, 0.50, bgUV.x);\n"
"}\n"
"    \n"
"    if (u_isCredits == 1) {\n"
"        // Extracts the perfectly calculated structural gradients injected into channel blue\n"
"        float verticalBounds = texture(u_textMaskTex, textUV).b;\n"
"        backdropIntensity = verticalBounds * horizontalBounds * 0.85;\n"
"    } else {\n"
"        // Original mathematical layout computation\n"
"        float verticalBounds = smoothstep(0.25, 0.60, bgUV.y) * smoothstep(0.72, 0.48, bgUV.y);\n"
"        backdropIntensity = verticalBounds * horizontalBounds * 0.85;\n"
"    }\n"
"    \n"
"    vec3 finalScene = mix(vec3(0.0), ambientOrange, backdropIntensity);\n"
"    \n"
"    // 1. GOLD LEAF PASS\n"
"    if (mainTextMask > 0.001) {\n"
"        vec2 eps = vec2(0.001, 0.0);\n"
"        float hL = getCombinedHeight(uv - eps.xy);\n"
"        float hR = getCombinedHeight(uv + eps.xy);\n"
"        float hD = getCombinedHeight(uv - eps.yx);\n"
"        float hU = getCombinedHeight(uv + eps.yx);\n"
"        vec3 normalVec = normalize(vec3(hL - hR, hD - hU, 0.008));\n"
"        vec3 lightDir = normalize(vec3(0.40, 0.60, 0.70));\n"
"        vec3 halfDir  = normalize(lightDir + vec3(0.0, 0.0, 1.0));\n"
"        float diffuseFactor  = max(0.0, dot(normalVec, lightDir));\n"
"        float specularFactor = pow(max(0.0, dot(normalVec, halfDir)), 50.0);\n"
"        vec3 darkGoldCrevice = vec3(0.32, 0.16, 0.02);\n"
"        vec3 vividGoldBase   = vec3(0.85, 0.58, 0.10);\n"
"        vec3 goldHighlight   = vec3(1.00, 0.84, 0.40);\n"
"        vec3 metallicGlint   = vec3(1.00, 0.95, 0.80);\n"
"        float goldHeightMap = getGoldLeafTexture(textUV * 1.5);\n"
"        vec3 goldSurfaceColor = mix(vividGoldBase, darkGoldCrevice, smoothstep(0.1, -0.4, goldHeightMap));\n"
"        goldSurfaceColor = mix(goldSurfaceColor, goldHighlight, diffuseFactor * 0.65);\n"
"        goldSurfaceColor += goldHighlight * smoothstep(0.02, 0.35, length(vec2(hL - hR, hD - hU))) * 0.45;\n"
"        goldSurfaceColor += metallicGlint * specularFactor * 1.2;\n"
"        finalScene = mix(finalScene, goldSurfaceColor, smoothstep(0.0, 0.02, mainTextMask));\n"
"    }\n"
"    \n"
"    // 2. SUBTEXT PASS (Handles Credits Text Look dynamically via channel green)\n"
"    if (subTextMask > 0.001) {\n"
"        vec3 cleanStoneGrey = vec3(0.85, 0.65, 0.12);\n"
"        float sLeft  = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(-0.001, 0.0)) : getCurvedUV(uv + vec2(-0.001, 0.0))).g;\n"
"        float sRight = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(0.001, 0.0)) : getCurvedUV(uv + vec2(0.001, 0.0))).g;\n"
"        float subSpecular = max(0.0, dot(normalize(vec3((sLeft - sRight), 0.0, 0.4)), normalize(vec3(0.3, 0.0, 0.7))));\n"
"        cleanStoneGrey += vec3(0.2) * subSpecular;\n"
"        finalScene = mix(finalScene, cleanStoneGrey, subTextMask);\n"
"    }\n"
"    \n"
"    // 3. FIRE PASS\n"
"    float fSize = 0.004;\n"
"    float maskN = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(0.0, fSize)) : getCurvedUV(uv + vec2(0.0, fSize))).r;\n"
"    float maskS = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(0.0, -fSize)) : getCurvedUV(uv + vec2(0.0, -fSize))).r;\n"
"    float maskE = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(fSize, 0.0)) : getCurvedUV(uv + vec2(fSize, 0.0))).r;\n"
"    float maskW = texture(u_textMaskTex, (u_isCredits == 1) ? (uv + vec2(-fSize, 0.0)) : getCurvedUV(uv + vec2(-fSize, 0.0))).r;\n"
"    float textEdge = (abs(maskE - maskW) + abs(maskN - maskS)) * 0.5;\n"
"    textEdge = smoothstep(0.05, 0.8, textEdge);\n"
"    if (textEdge > 0.01) {\n"
"        vec2 fireUV = textUV * vec2(4.5, 2.5);\n"
"        fireUV.y -= u_time * 1.6;\n"
"        fireUV.x += fbm(textUV * 6.0 + vec2(0.0, u_time)) * 0.35;\n"
"        float fireNoise = fbm(fireUV);\n"
"        float flameIntensity = textEdge * fireNoise * 2.4;\n"
"        vec3 fireRed    = vec3(0.30, 0.01, 0.00);\n"
"        vec3 fireOrange = vec3(0.42, 0.12, 0.01);\n"
"        vec3 fireYellow = vec3(0.55, 0.28, 0.02);\n"
"        vec3 flameColor = mix(fireRed, fireOrange, smoothstep(0.15, 0.55, flameIntensity));\n"
"        flameColor = mix(flameColor, fireYellow, smoothstep(0.55, 0.90, flameIntensity));\n"
"        finalScene += flameColor * clamp(flameIntensity, 0.0, 1.0);\n"
"    }\n"
"    \n"
"    // 4. PARTICLE ADDITIVE PASS\n"
"    finalScene += getFireSparks(bgUV, u_time, u_textMaskTex);\n"
"    \n"
"    float softVignette = bgUV.x * bgUV.y * (1.0 - bgUV.x) * (1.0 - bgUV.y);\n"
"    finalScene *= clamp(pow(16.0 * softVignette, 0.14), 0.0, 1.0);\n"
"    \n"
"    FragColor = vec4(finalScene, 1.0);\n"
"}\n";

// Mathematical utility replicating GLSL's smoothstep for the DIB matrix
float smoothstep_c(float edge0, float edge1, float x) {
    float t = (x - edge0) / (edge1 - edge0);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return t * t * (3.0f - 2.0f * t);
}

// MULTI-LINE ASSET MASK GENERATION LAYER
GLuint BakeGDIWordMaskTexture(void) {
    int texWidth = 2048; 
    int texHeight = 1024;

    HDC hdcDisplay = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcDisplay);
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = texWidth;
    bmi.bmiHeader.biHeight = texHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    SelectObject(hdcMem, hBmp);

    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, texWidth, texHeight };
    FillRect(hdcMem, &rect, hBlackBrush);
    DeleteObject(hBlackBrush);

    SetBkMode(hdcMem, TRANSPARENT);

    // PASS 1: TEXTURE GROUP (Channel Green)
    HFONT hSubFontTop = CreateFontA(56, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                                    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                                    ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Georgia");
    SelectObject(hdcMem, hSubFontTop);
    SetTextColor(hdcMem, RGB(0, 255, 0));
    RECT textRectTop = { 0, (int)(texHeight * 0.24), texWidth, texHeight };
    DrawTextA(hdcMem, "TEXTURE GROUP", -1, &textRectTop, DT_CENTER | DT_TOP | DT_SINGLELINE);
    DeleteObject(hSubFontTop);

    // PASS 2: PRESENTS (Channel Green)
    HFONT hSubFontMid = CreateFontA(38, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                                    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                                    ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Georgia");
    SelectObject(hdcMem, hSubFontMid);
    RECT textRectMid = { 0, (int)(texHeight * 0.30), texWidth, texHeight };
    DrawTextA(hdcMem, "PRESENTS", -1, &textRectMid, DT_CENTER | DT_TOP | DT_SINGLELINE);
    DeleteObject(hSubFontMid);

    // PASS 3: HANUMAN (Channel Red)
    HFONT hMainFont = CreateFontW(
        235, 0, 0, 0,
        FW_EXTRABOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"Nirmala UI");

    SelectObject(hdcMem, hMainFont);

    SetTextColor(hdcMem, RGB(255, 0, 0));

    RECT textRectMain = { 0, (int)(texHeight * 0.40), texWidth, texHeight};

    // Hindi Title
    DrawTextW(hdcMem,
        L"\u092E\u0939\u093E\u0930\u0941\u0926\u094D\u0930", // महारुद्र - MADAM'S CHANGE
        -1, &textRectMain, DT_CENTER | DT_TOP | DT_SINGLELINE);

    DeleteObject(hMainFont);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    DeleteObject(hBmp);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcDisplay);

    return textureID;
}

// END CREDITS ASSET MASK GENERATION LAYER
GLuint BakeGDICreditsTexture(void) {
    int texWidth = 2048; 
    // Increased height to 16384 to accommodate ~170 lines of text (approx 12,500 pixels)
    int texHeight = 16384; 

    HDC hdcDisplay = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcDisplay);
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = texWidth;
    bmi.bmiHeader.biHeight = texHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    SelectObject(hdcMem, hBmp);

    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, texWidth, texHeight };
    FillRect(hdcMem, &rect, hBlackBrush);
    DeleteObject(hBlackBrush);

    SetBkMode(hdcMem, TRANSPARENT);
    
    int startY = 400;     
    int lineSpacing = 70; 

    // --- PHASE 1: DRAW CREDITS TEXT FIRST (Channel Green) ---
    HFONT hCreditsFont = CreateFontA(56, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                                     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                                     ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Georgia");
    SelectObject(hdcMem, hCreditsFont);
    SetTextColor(hdcMem, RGB(0, 255, 0)); 

    fprintf(gpFILE, "%s : Linecount - %d\n", __func__, gCreditsLineCount);
	fflush(gpFILE);
    
    for (int i = 0; i < gCreditsLineCount; i++) {
        if (gCreditsText[i] && gCreditsText[i][0] != '\0') {
            // Convert UTF-8 to Wide String for GDI to handle Hindi characters
            wchar_t wBuf[1024];
            MultiByteToWideChar(CP_UTF8, 0, gCreditsText[i], -1, wBuf, 1024);

            RECT textRect = { 0, startY + i * lineSpacing, texWidth, startY + (i + 1) * lineSpacing };
            DrawTextW(hdcMem, wBuf, -1, &textRect, DT_CENTER | DT_TOP | DT_SINGLELINE);
        }
    }
    DeleteObject(hCreditsFont);

    GdiFlush();

    // --- PHASE 2: CALCULATE STRUCTURAL GRADIENT (Channel Blue) ---
    float* blueChannel = new float[texHeight];
    for (int y = 0; y < texHeight; y++) blueChannel[y] = 0.0f;

    int sectionStartIdx = 0;
    for (int i = 0; i <= gCreditsLineCount; i++) {
        bool isSectionEnd = (i == gCreditsLineCount) || (gCreditsText[i][0] == '\0');
        if (isSectionEnd) {
            if (i > sectionStartIdx) {
                int textTop = startY + sectionStartIdx * lineSpacing;
                int textBottom = startY + (i - 1) * lineSpacing + 56; 
                
                // *** CHANGED HERE: Reduced from 240 to 150 for a smaller section background ***
                int fadeSize = 150; 
                
                int rectTop = textTop - fadeSize;
                int rectBottom = textBottom + fadeSize;
                
                for (int y = rectTop; y <= rectBottom; y++) {
                    if (y < 0 || y >= texHeight) continue;
                    
                    float intensity = 1.0f;
                    if (y < textTop) {
                        intensity = smoothstep_c((float)rectTop, (float)textTop, (float)y);
                    } else if (y > textBottom) {
                        intensity = smoothstep_c((float)rectBottom, (float)textBottom, (float)y);
                    }
                    
                    if (intensity > blueChannel[y]) {
                        blueChannel[y] = intensity;
                    }
                }
            }
            sectionStartIdx = i + 1;
        }
    }

    // --- PHASE 3: DIRECT MEMORY INJECTION ---
    BYTE* pixels = (BYTE*)pBits;
    for (int y = 0; y < texHeight; y++) {
        int dibY = texHeight - 1 - y;
        BYTE bVal = (BYTE)(blueChannel[y] * 255.0f);
        
        int rowOffset = dibY * texWidth * 4;
        for (int x = 0; x < texWidth; x++) {
            pixels[rowOffset + x * 4 + 0] = bVal; 
        }
    }
    delete[] blueChannel;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pBits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    DeleteObject(hBmp);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcDisplay);

    return textureID;
}

void InitializeTitle(void) {
    
    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderObject);
    
    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderObject);

    gShaderProgramObject = glCreateProgram();
    glAttachShader(gShaderProgramObject, vertexShaderObject);
    glAttachShader(gShaderProgramObject, fragmentShaderObject);
    glLinkProgram(gShaderProgramObject);

    gTextMaskTexUniform = glGetUniformLocation(gShaderProgramObject, "u_textMaskTex");
    gTimeUniform = glGetUniformLocation(gShaderProgramObject, "u_time");
    gResolutionUniform = glGetUniformLocation(gShaderProgramObject, "u_resolution");

    // [FIX] Retrieve uniform locations for the credits state and scrolling offset
    gIsCreditsUniform = glGetUniformLocation(gShaderProgramObject, "u_isCredits");
    gScrollOffsetUniform = glGetUniformLocation(gShaderProgramObject, "u_scrollOffset");

    const GLfloat fullScreenQuadVertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };

    glGenVertexArrays(1, &gVaoQuad);
    glBindVertexArray(gVaoQuad);

    glGenBuffers(1, &gVboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, gVboPosition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullScreenQuadVertices), fullScreenQuadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    gTextMaskTextureID = BakeGDIWordMaskTexture();
    gCreditsTextureID = BakeGDICreditsTexture(); 

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void UpdateTitle(void) {
}

void UpdateEndCredits(void)
{
    if (g_bShowCredits == true) {
        
        const float SCROLL_START_TIME = START_TIME_END_CREDITS;

        if (ELAPSED_TIME >= SCROLL_START_TIME) {
            float creditsRunningTime = ELAPSED_TIME - SCROLL_START_TIME;
            gScrollOffset = 0.95f - (creditsRunningTime * 0.0075f);

            // Adjusted clamp for 16k texture height to stop when the final names are centered
            if (gScrollOffset < 0.32f) {
                gScrollOffset = 0.32f;
            }
        } else {
            gScrollOffset = 0.95f; // Keep it hidden until the delay passes
        }
    } else {
        g_bShowCredits = false;
    }
}

void DisplayTitle(void) {
    
    glUseProgram(gShaderProgramObject);

    float width = g_iWinWidth;
    float height = g_iWinHeight;

    glUniform1f(gTimeUniform, ELAPSED_TIME);
    glUniform2f(gResolutionUniform, width, height);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextMaskTextureID);
    glUniform1i(gTextMaskTexUniform, 0);

    glBindVertexArray(gVaoQuad);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
    UpdateTitle();
   
}

void displayEndCredits(void) {
   glUseProgram(gShaderProgramObject);
    g_bShowCredits = true;
    glUniform1i(gIsCreditsUniform, 1);
    glUniform1f(gScrollOffsetUniform, gScrollOffset);

    // [FIX] Provide the active time and resolution updates needed by the fragment architecture
    float width = g_iWinWidth;
    float height = g_iWinHeight;
    glUniform1f(gTimeUniform, ELAPSED_TIME);
    glUniform2f(gResolutionUniform, width, height);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gCreditsTextureID);
    glUniform1i(gTextMaskTexUniform, 0);

    glBindVertexArray(gVaoQuad);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
    UpdateEndCredits();
}

void UninitializeTitle(void) {
    if (gVaoQuad) glDeleteVertexArrays(1, &gVaoQuad);
    if (gVboPosition) glDeleteBuffers(1, &gVboPosition);
    if (gTextMaskTextureID) glDeleteTextures(1, &gTextMaskTextureID);
    if (gCreditsTextureID) glDeleteTextures(1, &gCreditsTextureID); 
    if (gShaderProgramObject) glDeleteProgram(gShaderProgramObject);
    
}