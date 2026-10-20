#include "Skybox.h"
#include "../../include/stb/stb_image.h"

namespace
{
    GLuint shaderProgram = 0;
    GLint  viewLoc       = -1;
    GLint  projLoc       = -1;
    GLint  samplerLoc    = -1;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint cubemapID = 0;

    const char *vsSource =
        "#version 460 core\n"
        "layout(location = 0) in vec3 a_position;\n"
        "uniform mat4 u_view;\n"
        "uniform mat4 u_projection;\n"
        "out vec3 v_dir;\n"
        "void main()\n"
        "{\n"
        "    v_dir = a_position;\n"
        "    mat4 viewNoTranslate = mat4(mat3(u_view));\n"
        "    vec4 clip = u_projection * viewNoTranslate * vec4(a_position, 1.0);\n"
        "    gl_Position = clip.xyww;\n"
        "}\n";

    const char *fsSource =
        "#version 460 core\n"
        "in vec3 v_dir;\n"
        "uniform samplerCube u_cubemap;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(u_cubemap, v_dir);\n"
        "}\n";

    const float cubeVertices[] = {
         1, -1, -1,   1, -1,  1,   1,  1,  1,
         1,  1,  1,   1,  1, -1,   1, -1, -1,
        -1, -1,  1,  -1, -1, -1,  -1,  1, -1,
        -1,  1, -1,  -1,  1,  1,  -1, -1,  1,
        -1,  1, -1,   1,  1, -1,   1,  1,  1,
         1,  1,  1,  -1,  1,  1,  -1,  1, -1,
        -1, -1,  1,   1, -1,  1,   1, -1, -1,
         1, -1, -1,  -1, -1, -1,  -1, -1,  1,
         1, -1,  1,  -1, -1,  1,  -1,  1,  1,
        -1,  1,  1,   1,  1,  1,   1, -1,  1,
        -1, -1, -1,   1, -1, -1,   1,  1, -1,
         1,  1, -1,  -1,  1, -1,  -1, -1, -1,
    };

    GLuint compileShader(GLenum type, const char *src)
    {
        GLuint sh = glCreateShader(type);
        glShaderSource(sh, 1, &src, NULL);
        glCompileShader(sh);
        GLint ok = 0;
        glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
        if (!ok)
        {
            GLint len = 0;
            glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> log(len > 1 ? len : 1, 0);
            glGetShaderInfoLog(sh, len, NULL, log.data());
            LOG("Skybox shader compile error (type %u):\n%s\n", type, log.data());
        }
        return sh;
    }

    GLuint linkProgram(GLuint vs, GLuint fs)
    {
        GLuint p = glCreateProgram();
        glAttachShader(p, vs);
        glAttachShader(p, fs);
        glBindAttribLocation(p, ATTR_POSITION, "a_position");
        glLinkProgram(p);
        GLint ok = 0;
        glGetProgramiv(p, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            GLint len = 0;
            glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> log(len > 1 ? len : 1, 0);
            glGetProgramInfoLog(p, len, NULL, log.data());
            LOG("Skybox program link error:\n%s\n", log.data());
        }
        glDetachShader(p, vs);
        glDetachShader(p, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return p;
    }
}

BOOL initializeSkybox(const char *faces[6])
{
    GLuint vs = compileShader(GL_VERTEX_SHADER,   vsSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
    shaderProgram = linkProgram(vs, fs);

    viewLoc    = glGetUniformLocation(shaderProgram, "u_view");
    projLoc    = glGetUniformLocation(shaderProgram, "u_projection");
    samplerLoc = glGetUniformLocation(shaderProgram, "u_cubemap");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &cubemapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

    stbi_set_flip_vertically_on_load(0);
    for (int i = 0; i < 6; ++i)
    {
        int w = 0, h = 0, c = 0;
        unsigned char *data = stbi_load(faces[i], &w, &h, &c, 4);
        if (!data)
        {
            LOG("Skybox: failed to load face %d : %s\n", i, faces[i]);
            return FALSE;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    LOG("Skybox initialized (cubemap id = %u)\n", cubemapID);
    return TRUE;
}

void renderSkybox(const Camera *pCamera, const vmath::mat4 &projectionMatrix)
{
    GLint prevDepthFunc = GL_LESS;
    glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFunc);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(shaderProgram);

    vmath::mat4 view = pCamera->getViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
    glUniform1i(samplerLoc, 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glUseProgram(0);
    glDepthFunc(prevDepthFunc);
}

GLuint getSkyboxCubemapID(void) { return cubemapID; }

void uninitializeSkybox(void)
{
    if (cubemapID)     { glDeleteTextures(1, &cubemapID); cubemapID = 0; }
    if (vbo)           { glDeleteBuffers(1, &vbo);        vbo = 0;       }
    if (vao)           { glDeleteVertexArrays(1, &vao);   vao = 0;       }
    if (shaderProgram) { glDeleteProgram(shaderProgram);  shaderProgram = 0; }
}
