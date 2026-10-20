// Standart Win32 headers
#include "../include/common.h"
#include "./Dissolve.h"
#include <time.h>


int initializeDissolveShader(void)
{

     // Vertex Shader
    const GLchar *vertexShaderSourceCode =
        "#version 460 core\n"
        "in vec4 aPosition;\n"
        "in vec2 aTexCoord;\n"
        "out vec2 oTexCoord;\n"
        "out vec3 out_worldPos;\n"
        "uniform mat4 uMVP;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = uMVP * aPosition;\n"
        "    oTexCoord = aTexCoord;\n"
        "    out_worldPos = aPosition.xyz;\n"
        "}\n";
    
    // Fragment Shader
    const GLchar *fragmentShaderSourceCode =
        "#version 460 core\n"
        "in vec2 oTexCoord;\n"
        "in vec3 out_worldPos;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2D uTextureSampler;\n"
        "uniform bool uDissolveEnabled;\n"
        "uniform float uProgress;\n"
        "uniform float uEdgeWidth;\n"
        "uniform float uFrequency;\n"
        "uniform float uAmplitude;\n"
        "uniform vec3 uMeshColor;\n"
        "uniform vec3 uEdgeColor;\n"
        "uniform float uTime;\n"
        "uniform bool uReverse;\n"
        "\n"
        "float hash(vec3 p)\n"
        "{\n"
        "    p = fract(p * vec3(127.1, 311.7, 74.7));\n"
        "    p += dot(p, p.yzx + 19.19);\n"
        "    return fract((p.x + p.y) * p.z);\n"
        "}\n"
        "\n"
        "float noise(vec3 p)\n"
        "{\n"
        "    vec3 i = floor(p);\n"
        "    vec3 f = fract(p);\n"
        "    vec3 u = f * f * (3.0 - 2.0 * f);\n"
        "    return mix(\n"
        "        mix(mix(hash(i + vec3(0,0,0)), hash(i + vec3(1,0,0)), u.x),\n"
        "            mix(hash(i + vec3(0,1,0)), hash(i + vec3(1,1,0)), u.x), u.y),\n"
        "        mix(mix(hash(i + vec3(0,0,1)), hash(i + vec3(1,0,1)), u.x),\n"
        "            mix(hash(i + vec3(0,1,1)), hash(i + vec3(1,1,1)), u.x), u.y),\n"
        "        u.z);\n"
        "}\n"
        "\n"
        "float fbm(vec3 p)\n"
        "{\n"
        "    float value = 0.0;\n"
        "    float amplitude = 0.5;\n"
        "    float frequency = 1.0;\n"
        "    for (int i = 0; i < 4; i++)\n"
        "    {\n"
        "        value += amplitude * noise(p * frequency);\n"
        "        frequency *= 2.0;\n"
        "        amplitude *= 0.5;\n"
        "    }\n"
        "    return value;\n"
        "}\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    vec4 texColor = texture(uTextureSampler, oTexCoord);\n"
        "    \n"
        "    if (!uDissolveEnabled)\n"
        "    {\n"
        "        FragColor = texColor;\n"
        "        return;\n"
        "    }\n"
        "\n"
        "    vec3 noiseCoord = out_worldPos * uFrequency  * 0.1;\n" 
        "    float noiseVal = fbm(noiseCoord);\n"

        // Normalize progress from 0-20 to 0-1 range
        "float normalizedProgress = clamp(uProgress / 20.0, 0.0, 1.0);\n"
        "// Map noise to desired range based on direction\n"
        "float threshold;\n"
        "float edgeStart;\n"
        "float edgeEnd;\n"
    
        "if (!uReverse)  // Appear effect: invisible → visible\n"
        "{\n"
            "// When progress = 0:  fully invisible  (need high threshold)\n"
            "// When progress = 20: fully visible    (need low threshold)\n"
            "// Convert progress 0-20 to threshold 1-0\n"
            "threshold =  1.0 - normalizedProgress;\n"
            "threshold = threshold - 0.05;\n"
            "// Edge glow follows the dissolve front\n"
            "edgeStart = threshold;\n"
            "edgeEnd = min(threshold + (uEdgeWidth / 20.0), 1.0);\n"

            "// Discard fragments with noise value below threshold\n"
            "if (noiseVal < threshold)\n"
            "{\n"
                "discard;  // These fragments are dissolved (invisible)\n"
            "}\n"
    
   
            "else if (noiseVal < edgeEnd)\n"
            "{\n"
            "        float edgeFactor = (noiseVal - edgeStart) / (edgeEnd - edgeStart);\n"
            "        float shimmer = 0.7 + 0.3 * sin(uTime * 6.0 + out_worldPos.x * 3.0);\n"
            "        vec3 edgeGlow = uEdgeColor * (1.0 - edgeFactor) * 2.5 * shimmer;\n"
            "        vec3 finalColor = mix(texColor.rgb * uMeshColor, edgeGlow, edgeFactor);\n"
            "        FragColor = vec4(finalColor, 1.0);\n"
            "    }\n"

            "else\n"
            "{\n"
                "FragColor = vec4(texColor.rgb * uMeshColor, 1.0);\n"
            "}\n"

        "}\n"

        "else  // DISAPPEAR effect: visible → invisible\n"
        "{\n"
        "// When normalizedProgress = 0.0 (progress=0): threshold = 0.0 (discard nothing)\n"
        "// When normalizedProgress = 1.0 (progress=20): threshold = 1.0 (discard everything)\n"
        "threshold = normalizedProgress;\n"
        
        "// Edge glow follows the dissolve front\n"
        "edgeStart = threshold - (uEdgeWidth / 20.0);\n"
        "edgeStart = max(edgeStart, 0.0);\n"
        "edgeEnd = threshold;\n"
        
        "// Discard fragments with noise value above threshold\n"
        "if (noiseVal > threshold)\n"
        "{\n"
            "discard;  // These fragments are dissolved (invisible)\n"
        "}\n"
        "else if (noiseVal > edgeStart)\n"
        "{\n"
            "// Edge glow region\n"
            "float edgeFactor = (noiseVal - edgeStart) / (edgeEnd - edgeStart);\n"
            "float shimmer = 0.7 + 0.3 * sin(uTime * 6.0 + out_worldPos.x * 3.0);\n"
            "vec3 edgeGlow = uEdgeColor * (1.0 - edgeFactor) * 2.5 * shimmer;\n"
            "vec3 finalColor = mix(texColor.rgb * uMeshColor, edgeGlow, edgeFactor);\n"
            "FragColor = vec4(finalColor, 1.0);\n"
        "}\n"
        "else\n"
        "{\n"
            "// Fully visible\n"
            "FragColor = vec4(texColor.rgb * uMeshColor, 1.0);\n"
        "}\n"
    "}\n"

    "}\n";
    
    // Compile vertex shader
    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);
    glCompileShader(vertexShaderObject);
    
    // Compile fragment shader
    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);
    glCompileShader(fragmentShaderObject);
    
    // Create shader program
    dissolveShaderProgram = glCreateProgram();
    glAttachShader(dissolveShaderProgram, vertexShaderObject);
    glAttachShader(dissolveShaderProgram, fragmentShaderObject);
    
    glBindAttribLocation(dissolveShaderProgram, AMC_ATTRIBUTE_POSITION, "aPosition");
    glBindAttribLocation(dissolveShaderProgram, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");
    
    glLinkProgram(dissolveShaderProgram);
    
    // Get uniform locations
    dissolveMVPUniform = glGetUniformLocation(dissolveShaderProgram, "uMVP");
    dissolveEnabledUniform = glGetUniformLocation(dissolveShaderProgram, "uDissolveEnabled");
    dissolveProgressUniform = glGetUniformLocation(dissolveShaderProgram, "uProgress");
    dissolveEdgeWidthUniform = glGetUniformLocation(dissolveShaderProgram, "uEdgeWidth");
    dissolveFrequencyUniform = glGetUniformLocation(dissolveShaderProgram, "uFrequency");
    dissolveAmplitudeUniform = glGetUniformLocation(dissolveShaderProgram, "uAmplitude");
    dissolveMeshColorUniform = glGetUniformLocation(dissolveShaderProgram, "uMeshColor");
    dissolveEdgeColorUniform = glGetUniformLocation(dissolveShaderProgram, "uEdgeColor");
    dissolveTimeUniform = glGetUniformLocation(dissolveShaderProgram, "uTime");
    dissolveTextureSamplerUniform = glGetUniformLocation(dissolveShaderProgram, "uTextureSampler");
    dissolveReverseUniform = glGetUniformLocation(dissolveShaderProgram, "uReverse");
    
    // Cleanup
    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);
    
    return 0;
    
}

void renderModelWithDissolve(Model *model, vmath::mat4 modelMatrix,vmath::mat4 viewMatrix,vmath::mat4 projectionMatrix,float progress,float time,BOOL bReverse)
{
    if (!model) return;
    
    static int callCount = 0;
    if (callCount < 20)
    {
        fprintf(gpFILE, "renderModelWithDissolve - Progress: %.2f, Reverse: %d, Time: %.2f\n", 
                progress, bReverse, time);
        fflush(gpFILE);
        callCount++;
    }
    
    glUseProgram(dissolveShaderProgram);
    
    if (!dissolveShaderProgram)
    {
        fprintf(gpFILE, "ERROR: dissolveShaderProgram is NULL!\n");
        fflush(gpFILE);
        return;
    }
    
    // Calculate MVP matrix
    vmath::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(dissolveMVPUniform, 1, GL_FALSE, mvpMatrix);
    
    float finalProgress = progress;
    if (finalProgress < 0.0f) finalProgress = 0.0f;
    if (finalProgress > 20.0f) finalProgress = 20.0f;
    
    // Set uniforms
    glUniform1i(dissolveEnabledUniform, GL_TRUE);
    glUniform1f(dissolveProgressUniform, finalProgress);
    if (dissolveReverseUniform != -1)
        glUniform1i(dissolveReverseUniform, bReverse ? GL_TRUE : GL_FALSE);
    glUniform1f(dissolveEdgeWidthUniform, 0.6f);
    glUniform1f(dissolveFrequencyUniform, 0.35f);
    glUniform1f(dissolveAmplitudeUniform, 20.0f);
    glUniform3f(dissolveMeshColorUniform, 1.0f, 1.0f, 1.0f);
    glUniform3f(dissolveEdgeColorUniform, 1.0f, 0.7f, 0.2f);
    glUniform1f(dissolveTimeUniform, time);
    glUniform1i(dissolveTextureSamplerUniform, 0);
    
    renderModel(model);
    glUseProgram(0);

}


void uninitializeDisslove(void)
{
  
}


