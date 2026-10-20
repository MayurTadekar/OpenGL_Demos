#include "LightningWithFlash.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include "../../modules/imgui/imgui.h"

static GLuint vao_flash = 0;
static GLuint shaderProgram_flash = 0;
static GLint alpha_uniform = 0;
static GLint flash_color_uniform = 0;

static GLuint vao_strike_main = 0;
static GLuint vbo_strike_main = 0;
static GLuint vao_strike_sec = 0;
static GLuint vbo_strike_sec = 0;
static GLuint vao_strike_tert = 0;
static GLuint vbo_strike_tert = 0;

static GLuint shaderProgram_strike = 0;
static GLint strike_color_uniform = 0;

static std::vector<float> main_vertices;
static std::vector<float> sec_vertices;
static std::vector<float> tert_vertices;

// Midpoint displacement - create "wave" fractal patterns
void generateFractalPath(float x1, float y1, float x2, float y2, float displace, int detail, std::vector<float> &out)
{
    if (detail <= 0)
    {
        out.push_back(x1);
        out.push_back(y1);
        out.push_back(x2);
        out.push_back(y2);
    }
    else
    {
        float midX = (x1 + x2) / 2.0f;
        float midY = (y1 + y2) / 2.0f;
        midX += ((float)rand() / (float)RAND_MAX - 0.5f) * displace;
        midY += ((float)rand() / (float)RAND_MAX - 0.5f) * displace;
        generateFractalPath(x1, y1, midX, midY, displace * 0.5f, detail - 1, out);
        generateFractalPath(midX, midY, x2, y2, displace * 0.5f, detail - 1, out);
    }
}

void initializeLightningWithFlash()
{
    const GLchar *vs =
        "#version 460 core\n"
        "void main() {\n"
        "    vec2 pos[4] = vec2[](vec2(-1,-1), vec2(1,-1), vec2(-1,1), vec2(1,1));\n"
        "    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);\n"
        "}\n";
    const GLchar *fs =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "uniform float alpha;\n"
        "uniform vec4 flashColor;\n"
        "void main() {\n"
        "    FragColor = flashColor * alpha;\n"
        "}\n";

    GLuint vso = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vso, 1, &vs, NULL);
    glCompileShader(vso);

    GLuint fso = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fso, 1, &fs, NULL);
    glCompileShader(fso);

    shaderProgram_flash = glCreateProgram();
    glAttachShader(shaderProgram_flash, vso);
    glAttachShader(shaderProgram_flash, fso);
    glLinkProgram(shaderProgram_flash);

    glDeleteShader(vso);
    glDeleteShader(fso);

    // Get uniform locations
    alpha_uniform = glGetUniformLocation(shaderProgram_flash, "alpha");
    flash_color_uniform = glGetUniformLocation(shaderProgram_flash, "flashColor");

    glGenVertexArrays(1, &vao_flash);

    // Initialize Strike Shader
    const GLchar *vs_strike =
        "#version 460 core\n"
        "layout(location = 0) in vec2 aPosition;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "}\n";
    const GLchar *fs_strike =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 strikeColor;\n"
        "void main() {\n"
        "    FragColor = strikeColor;\n"
        "}\n";

    GLuint vso_s = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vso_s, 1, &vs_strike, NULL);
    glCompileShader(vso_s);
    GLuint fso_s = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fso_s, 1, &fs_strike, NULL);
    glCompileShader(fso_s);

    shaderProgram_strike = glCreateProgram();
    glAttachShader(shaderProgram_strike, vso_s);
    glAttachShader(shaderProgram_strike, fso_s);
    glLinkProgram(shaderProgram_strike);
    strike_color_uniform = glGetUniformLocation(shaderProgram_strike, "strikeColor");

    glGenVertexArrays(1, &vao_strike_main);
    glGenBuffers(1, &vbo_strike_main);
    glGenVertexArrays(1, &vao_strike_sec);
    glGenBuffers(1, &vbo_strike_sec);
    glGenVertexArrays(1, &vao_strike_tert);
    glGenBuffers(1, &vbo_strike_tert);
}

void updateLightningWithFlash(float deltaTime) {}

void renderLightningWithFlash(float currentTime, float triggerTime)
{
    // First flash: white, kmi time - Light speeed
    const float flash1_trigger = triggerTime;
    const float flash1_duration = 0.2f;
    const ImVec4 flash1_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White

    // Second flash:  adhi peksha longer, glow
    const float flash2_trigger = triggerTime + 0.2f;
    const float flash2_duration = 3.0f; // 3 sec vij padne
    const ImVec4 flash2_color = ImVec4(0.1f, 0.02f, 0.15f, 1.0f); // Purple-ish flash
    const ImVec4 glow_color = ImVec4(0.6f, 0.0f, 1.0f, 1.0f);      // Deep purple glow
    const ImVec4 core_color = ImVec4(0.9f, 0.8f, 1.0f, 1.0f);      // Light purple core

    static float lastGenerationTime = -1.0f;

    // Render first flash - Vijecha adhicha ujed
    if (currentTime >= flash1_trigger && currentTime <= flash1_trigger + flash1_duration)
    {
        float t = (currentTime - flash1_trigger) / flash1_duration;
        float alpha = 0.0f;

        if (t < 0.2f)
            alpha = t / 0.2f;
        else
            alpha = 1.0f - (t - 0.2f) / 0.8f;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        glUseProgram(shaderProgram_flash);
        glUniform1f(alpha_uniform, alpha);
        glUniform4f(flash_color_uniform, flash1_color.x, flash1_color.y, flash1_color.z, flash1_color.w);

        glBindVertexArray(vao_flash);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        glUseProgram(0);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }

    // Render second flash - Vijecha akar ani light
    if (currentTime >= flash2_trigger && currentTime <= flash2_trigger + flash2_duration)
    {
        // strike lines
        if (lastGenerationTime < flash2_trigger)
        {
            srand((unsigned int)(currentTime * 1000.0f));
            main_vertices.clear();
            sec_vertices.clear();
            tert_vertices.clear();

            float startX = ((float)rand() / RAND_MAX) * 0.5f + 0.3f;
            float endX = startX + ((float)rand() / RAND_MAX) * 0.4f - 0.2f;
            generateFractalPath(startX, 1.0f, endX, -1.1f, 0.6f, 6, main_vertices);

            // 2. Generate Secondary Branches
            for (size_t i = 0; i < main_vertices.size(); i += 8)
            {
                if (((float)rand() / RAND_MAX) > 0.85f)
                {
                    float branchEndX = main_vertices[i] + ((float)rand() / RAND_MAX) * 1.0f - 0.3f; // Lean branches right
                    float branchEndY = main_vertices[i + 1] - 0.4f - ((float)rand() / RAND_MAX) * 0.4f;
                    generateFractalPath(main_vertices[i], main_vertices[i + 1], branchEndX, branchEndY, 0.2f, 4, sec_vertices);
                }
            }

            // 3. Generate Tertiary Filaments
            for (size_t i = 0; i < sec_vertices.size(); i += 12)
            {
                if (((float)rand() / RAND_MAX) > 0.7f)
                {
                    float branchEndX = sec_vertices[i] + ((float)rand() / RAND_MAX) * 0.3f - 0.15f;
                    float branchEndY = sec_vertices[i + 1] - 0.2f;
                    generateFractalPath(sec_vertices[i], sec_vertices[i + 1], branchEndX, branchEndY, 0.1f, 2, tert_vertices);
                }
            }

            // Update Buffers
            glBindVertexArray(vao_strike_main);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_strike_main);
            glBufferData(GL_ARRAY_BUFFER, main_vertices.size() * sizeof(float), main_vertices.data(), GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(0);

            glBindVertexArray(vao_strike_sec);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_strike_sec);
            glBufferData(GL_ARRAY_BUFFER, sec_vertices.size() * sizeof(float), sec_vertices.data(), GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(0);

            glBindVertexArray(vao_strike_tert);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_strike_tert);
            glBufferData(GL_ARRAY_BUFFER, tert_vertices.size() * sizeof(float), tert_vertices.data(), GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(0);

            lastGenerationTime = currentTime;
        }

        float t = (currentTime - flash2_trigger) / flash2_duration;
        float alpha = 0.0f;

        // Electric flicker
        float flicker = (sinf(currentTime * 50.0f) * 0.5f + 0.5f) * 0.3f + 0.7f;
        if (t < 0.05f)
            alpha = t / 0.05f;
        else
            alpha = (1.0f - t) * flicker;

        if (alpha < 0.1f && t < 0.9f)
            alpha = 0.2f;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); // for glow effect
        glDisable(GL_DEPTH_TEST);

        glUseProgram(shaderProgram_flash);
        glUniform1f(alpha_uniform, alpha);
        glUniform4f(flash_color_uniform, flash2_color.x, flash2_color.y, flash2_color.z, flash2_color.w);

        glBindVertexArray(vao_flash);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glUseProgram(shaderProgram_strike);

        // --- LEVEL 1: MAIN TRUNK (Multi-Pass Glow) ---
        glBindVertexArray(vao_strike_main);
        glLineWidth(30.0f); // Thicker glow
        glUniform4f(strike_color_uniform, glow_color.x, glow_color.y, glow_color.z, alpha * 0.5f); // Increased intensity
        glDrawArrays(GL_LINES, 0, (GLsizei)main_vertices.size() / 2);

        glLineWidth(15.0f); // Thicker inner glow
        glUniform4f(strike_color_uniform, glow_color.x * 1.5f, glow_color.y * 1.5f, glow_color.z * 1.8f, alpha * 0.8f); // Increased intensity
        glDrawArrays(GL_LINES, 0, (GLsizei)main_vertices.size() / 2);

        glLineWidth(7.5f);                                                 // Thicker core
        glUniform4f(strike_color_uniform, 1.0f, 1.0f, 1.0f, alpha * 1.0f); // Pure white core for intensity
        glDrawArrays(GL_LINES, 0, (GLsizei)main_vertices.size() / 2);

        // --- LEVEL 2: SECONDARY BRANCHES (Medium Glow) ---
        glBindVertexArray(vao_strike_sec);
        glLineWidth(10.0f);
        glUniform4f(strike_color_uniform, glow_color.x * 0.8f, glow_color.y * 0.8f, glow_color.z * 0.8f, alpha * 0.15f);
        glDrawArrays(GL_LINES, 0, (GLsizei)sec_vertices.size() / 2);

        glLineWidth(2.2f);
        glUniform4f(strike_color_uniform, core_color.x * 0.9f, core_color.y * 0.9f, core_color.z * 0.9f, alpha * 0.5f);
        glDrawArrays(GL_LINES, 0, (GLsizei)sec_vertices.size() / 2);

        // --- LEVEL 3: TERTIARY FILAMENTS (Low Glow) ---
        glBindVertexArray(vao_strike_tert);
        glLineWidth(1.5f);
        glUniform4f(strike_color_uniform, glow_color.x * 0.5f, glow_color.y * 0.5f, glow_color.z * 0.5f, alpha * 0.2f);
        glDrawArrays(GL_LINES, 0, (GLsizei)tert_vertices.size() / 2);

        glBindVertexArray(0);
        glUseProgram(0);
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }
}

void uninitializeLightningWithFlash()
{
    if (shaderProgram_flash)
        glDeleteProgram(shaderProgram_flash);
    if (vao_flash)
        glDeleteVertexArrays(1, &vao_flash);
    if (shaderProgram_strike)
        glDeleteProgram(shaderProgram_strike);
    if (vbo_strike_main)
        glDeleteBuffers(1, &vbo_strike_main);
    if (vao_strike_main)
        glDeleteVertexArrays(1, &vao_strike_main);
    if (vbo_strike_sec)
        glDeleteBuffers(1, &vbo_strike_sec);
    if (vao_strike_sec)
        glDeleteVertexArrays(1, &vao_strike_sec);
    if (vbo_strike_tert)
        glDeleteBuffers(1, &vbo_strike_tert);
    if (vao_strike_tert)
        glDeleteVertexArrays(1, &vao_strike_tert);
}