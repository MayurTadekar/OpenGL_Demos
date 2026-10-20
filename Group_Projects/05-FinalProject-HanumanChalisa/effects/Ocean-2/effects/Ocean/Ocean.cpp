#include "Ocean.h"
#include "../../../../modules/Camera/Camera.h"

#include "../../include/stb/stb_image.h"

namespace
{
    GLuint program  = 0;
    GLuint vao      = 0;
    GLuint vbo      = 0;
    GLuint ebo      = 0;
    GLsizei indexCount = 0;

    GLuint dudvTexture = 0;

    struct ULocs
    {
        GLint model, view, projection, time;
        GLint tiling, waveStrength;
        GLint cameraPos, sky, dudv;
        GLint numWaves, waveDir, waveAmp, waveWavelength, waveSpeed, waveSteepness;
        GLint shallowColor, deepColor, foamColor;
        GLint foamThreshold, foamSoftness, foamChoppinessGain;
        GLint sunDir, sunColor, sunShininess, sunIntensity;
        GLint fresnelStrength, reflectionStrength;
        GLint horizonFog, fogDensity;
    } u;

    bool readFile(const char *path, std::vector<char> &out)
    {
        FILE *f = NULL;
        if (fopen_s(&f, path, "rb") != 0 || !f) return false;
        fseek(f, 0, SEEK_END);
        long n = ftell(f);
        fseek(f, 0, SEEK_SET);
        out.resize(n + 1, 0);
        fread(out.data(), 1, n, f);
        out[n] = 0;
        fclose(f);
        return true;
    }

    GLuint compileShader(GLenum type, const char *src, const char *tag)
    {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, NULL);
        glCompileShader(s);
        GLint ok = 0;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok)
        {
            GLint len = 0;
            glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> log(len > 1 ? len : 1, 0);
            glGetShaderInfoLog(s, len, NULL, log.data());
            LOG("Ocean shader compile error (%s):\n%s\n", tag, log.data());
        }
        return s;
    }

    bool linkProgram(const char *vsPath, const char *fsPath)
    {
        std::vector<char> vsSrc, fsSrc;
        if (!readFile(vsPath, vsSrc)) { LOG("Ocean: cannot read %s\n", vsPath); return false; }
        if (!readFile(fsPath, fsSrc)) { LOG("Ocean: cannot read %s\n", fsPath); return false; }

        GLuint vs = compileShader(GL_VERTEX_SHADER,   vsSrc.data(), "Ocean.vert");
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc.data(), "Ocean.frag");

        program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glBindAttribLocation(program, ATTR_POSITION, "a_position");
        glLinkProgram(program);

        GLint ok = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            GLint len = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> log(len > 1 ? len : 1, 0);
            glGetProgramInfoLog(program, len, NULL, log.data());
            LOG("Ocean program link error:\n%s\n", log.data());
            return false;
        }

        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return true;
    }

    void cacheUniforms()
    {
        u.model              = glGetUniformLocation(program, "u_model");
        u.view               = glGetUniformLocation(program, "u_view");
        u.projection         = glGetUniformLocation(program, "u_projection");
        u.time               = glGetUniformLocation(program, "u_time");
        u.cameraPos          = glGetUniformLocation(program, "u_cameraPos");
        u.sky                = glGetUniformLocation(program, "u_sky");
        u.dudv               = glGetUniformLocation(program, "u_dudv");
        u.tiling             = glGetUniformLocation(program, "u_tiling");
		u.waveStrength       = glGetUniformLocation(program, "u_waveStrength");
        u.numWaves           = glGetUniformLocation(program, "u_numWaves");
        u.waveDir            = glGetUniformLocation(program, "u_waveDir");
        u.waveAmp            = glGetUniformLocation(program, "u_waveAmp");
        u.waveWavelength     = glGetUniformLocation(program, "u_waveWavelength");
        u.waveSpeed          = glGetUniformLocation(program, "u_waveSpeed");
        u.waveSteepness      = glGetUniformLocation(program, "u_waveSteepness");
        u.shallowColor       = glGetUniformLocation(program, "u_shallowColor");
        u.deepColor          = glGetUniformLocation(program, "u_deepColor");
        u.foamColor          = glGetUniformLocation(program, "u_foamColor");
        u.foamThreshold      = glGetUniformLocation(program, "u_foamThreshold");
        u.foamSoftness       = glGetUniformLocation(program, "u_foamSoftness");
        u.foamChoppinessGain = glGetUniformLocation(program, "u_foamChoppinessGain");
        u.sunDir             = glGetUniformLocation(program, "u_sunDir");
        u.sunColor           = glGetUniformLocation(program, "u_sunColor");
        u.sunShininess       = glGetUniformLocation(program, "u_sunShininess");
        u.sunIntensity       = glGetUniformLocation(program, "u_sunIntensity");
        u.fresnelStrength    = glGetUniformLocation(program, "u_fresnelStrength");
        u.reflectionStrength = glGetUniformLocation(program, "u_reflectionStrength");
        u.horizonFog         = glGetUniformLocation(program, "u_horizonFog");
        u.fogDensity         = glGetUniformLocation(program, "u_fogDensity");
    }

    void buildGrid(int resolution, float halfExtent)
    {
        std::vector<float>        positions;
        std::vector<unsigned int> indices;
        positions.reserve((resolution + 1) * (resolution + 1) * 3);
        indices.reserve(resolution * resolution * 6);

        float step = (2.0f * halfExtent) / (float)resolution;

        for (int z = 0; z <= resolution; ++z)
        {
            for (int x = 0; x <= resolution; ++x)
            {
                float fx = -halfExtent + (float)x * step;
                float fz = -halfExtent + (float)z * step;
                positions.push_back(fx);
                positions.push_back(0.0f);
                positions.push_back(fz);
            }
        }

        for (int z = 0; z < resolution; ++z)
        {
            for (int x = 0; x < resolution; ++x)
            {
                unsigned int i0 = (unsigned int)( z      * (resolution + 1) + x);
                unsigned int i1 = (unsigned int)( z      * (resolution + 1) + x + 1);
                unsigned int i2 = (unsigned int)((z + 1) * (resolution + 1) + x);
                unsigned int i3 = (unsigned int)((z + 1) * (resolution + 1) + x + 1);

                indices.push_back(i0); indices.push_back(i2); indices.push_back(i1);
                indices.push_back(i1); indices.push_back(i2); indices.push_back(i3);
            }
        }

        indexCount = (GLsizei)indices.size();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(ATTR_POSITION);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    GLuint loadTexture2D(const char *path)
    {
        stbi_set_flip_vertically_on_load(1);
        int w = 0, h = 0, c = 0;
        unsigned char *data = stbi_load(path, &w, &h, &c, 4);
        if (!data)
        {
            LOG("Ocean: failed to load texture %s\n", path);
            return 0;
        }
        GLuint tex = 0;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        stbi_image_free(data);
        return tex;
    }
}

BOOL initializeOcean(GLuint /*skyboxCubemapID*/)
{
    if (!linkProgram("./effects/Ocean-2/effects/Ocean/Ocean.vert", "./effects/Ocean-2/effects/Ocean/Ocean.frag"))
        return FALSE;
    cacheUniforms();

    buildGrid(300, 0.5f);

    dudvTexture = loadTexture2D("./resources/Texture/waterDUDV.png");
    if (!dudvTexture)
    {
        LOG("Ocean: missing waterDUDV.png\n");
        return FALSE;
    }

    LOG("Ocean initialized (indexCount=%d)\n", indexCount);
    return TRUE;
}

void renderOcean(OceanParams &params, Camera *pCamera, const vmath::mat4 &projectionMatrix, float elapsedTime)
{
    if (!program) return;

    glUseProgram(program);

    vmath::mat4 model = vmath::translate(params.translation) * vmath::scale(vmath::vec3(params.extent, 1.0f, params.extent));
    glUniformMatrix4fv(u.model,      1, GL_FALSE, model);
    glUniformMatrix4fv(u.view,       1, GL_FALSE, pCamera->getLookAtMatrix());
    glUniformMatrix4fv(u.projection, 1, GL_FALSE, projectionMatrix);
    glUniform1f       (u.time, elapsedTime);

    glUniform3fv(u.cameraPos, 1, pCamera->m_position);

    glUniform1i(u.sky,  0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, dudvTexture);
    glUniform1i(u.dudv, 1);

    int n = params.numWaves;
    if (n < 1) n = 1;
    if (n > OCEAN_MAX_WAVES) n = OCEAN_MAX_WAVES;

    float dirs[OCEAN_MAX_WAVES * 2];
    float amps[OCEAN_MAX_WAVES];
    float lens[OCEAN_MAX_WAVES];
    float spds[OCEAN_MAX_WAVES];
    float stps[OCEAN_MAX_WAVES];
    for (int i = 0; i < n; ++i)
    {
        dirs[i * 2 + 0] = params.waves[i].direction[0];
        dirs[i * 2 + 1] = params.waves[i].direction[1];
        amps[i]         = params.waves[i].amplitude;
        lens[i]         = params.waves[i].wavelength;
        spds[i]         = params.waves[i].speed;
        stps[i]         = params.waves[i].steepness;
    }

    glUniform1i (u.numWaves,       n);
    glUniform2fv(u.waveDir,        n, dirs);
    glUniform1fv(u.waveAmp,        n, amps);
    glUniform1fv(u.waveWavelength, n, lens);
    glUniform1fv(u.waveSpeed,      n, spds);
    glUniform1fv(u.waveSteepness,  n, stps);

    glUniform3fv(u.shallowColor,       1, params.shallowColor);
    glUniform3fv(u.deepColor,          1, params.deepColor);
    glUniform3fv(u.foamColor,          1, params.foamColor);
    glUniform1f (u.foamThreshold,         params.foamThreshold);
    glUniform1f (u.foamSoftness,          params.foamSoftness);
    glUniform1f (u.foamChoppinessGain,    params.foamChoppinessGain);

    glUniform3fv(u.sunDir,            1,  params.sunDirection);
    glUniform3fv(u.sunColor,          1,  params.sunColor);
    glUniform1f (u.sunShininess,          params.sunShininess);
    glUniform1f (u.sunIntensity,          params.sunIntensity);

    glUniform1f (u.tiling,                9.5f);
	glUniform1f (u.waveStrength,          0.0f);

    glUniform1f (u.fresnelStrength,       params.fresnelStrength);
    glUniform1f (u.reflectionStrength,    params.reflectionStrength);
    glUniform3fv(u.horizonFog,        1,  params.horizonFogColor);
    glUniform1f (u.fogDensity,            params.fogDensity);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void uninitializeOcean(void)
{
    if (ebo)         { glDeleteBuffers(1, &ebo);          ebo = 0; }
    if (vbo)         { glDeleteBuffers(1, &vbo);          vbo = 0; }
    if (vao)         { glDeleteVertexArrays(1, &vao);     vao = 0; }
    if (dudvTexture) { glDeleteTextures(1, &dudvTexture); dudvTexture = 0; }
    if (program)     { glDeleteProgram(program);          program = 0; }
}
void getDefaultStormPreset(OceanParams &p)
{
    p.translation = vmath::vec3(0.0f, 0.0f, 0.0f);
    p.extent      = 1000.0f;
    p.resolution  = 300;

    p.numWaves = 6;
    p.waves[0] = { vmath::vec2( 1.0f,  0.510f),  1.870f,  62.40f,  3.20f, 0.92f };
    p.waves[1] = { vmath::vec2( 0.85f, 1.090f),  1.496f,  78.4f,   2.85f, 0.85f };
    p.waves[2] = { vmath::vec2( 0.40f,-1.180f),  0.855f,  28.0f,   2.40f, 0.75f };
    p.waves[3] = { vmath::vec2(-0.610f, 0.560f), 1.129f,  18.4f,   2.10f, 0.65f };
    p.waves[4] = { vmath::vec2(-0.830f,-0.010f), 0.293f,  10.0f,   1.80f, 0.55f };
    p.waves[5] = { vmath::vec2( 0.10f, -0.010f), 0.876f,  24.40f,  1.55f, 0.45f };

    // Only colors changed
    p.shallowColor    = vmath::vec3(92.0f/255.0f, 190.0f/255.0f, 204.0f/255.0f);
    p.deepColor       = vmath::vec3(20.0f/255.0f, 48.0f/255.0f, 72.0f/255.0f);
    p.foamColor       = vmath::vec3(0.96f, 0.98f, 1.00f);

    p.foamThreshold      = 3.00f;
    p.foamSoftness       = 0.80f;
    p.foamChoppinessGain = 1.50f;

    p.sunDirection  = vmath::normalize(vmath::vec3(-0.4f, 0.55f, -0.7f));
    p.sunColor      = vmath::vec3(1.00f, 0.90f, 0.72f);
    p.sunShininess  = 220.0f;
    p.sunIntensity  = 6.0f;

    p.fresnelStrength    = 1.0f;
    p.reflectionStrength = 1.0f;

    p.horizonFogColor = vmath::vec3(180.0f/255.0f, 198.0f/255.0f, 214.0f/255.0f);
    p.fogDensity      = 0.0027f;
}
