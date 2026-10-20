
#pragma once

#include <GL/glew.h>

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "macros.h"

class Shader
{
private:

    const char* m_path = nullptr;
    GLuint m_shaderObject = 0;
    std::string m_sourceCode;

public:

    // Default constructor
    Shader() = default;

    // Parameterized constructor
    Shader(
        const char* _path,
        GLuint shaderType,
        const char* logFilePath)
        : m_path(_path)
    {
        const char* actualLogPath =
            (logFilePath != nullptr)
            ? logFilePath
            : "log.txt";

        // ----------------------------------------------------
        // Read shader source file
        // ----------------------------------------------------

        LOG_ENTRY(
            actualLogPath,
            "Reading Shader File: %s",
            m_path ? m_path : "(null)"
        );

        if (m_path == nullptr)
        {
            WriteLog(actualLogPath, "Shader path is null.");
            std::exit(EXIT_FAILURE);
        }

        std::ifstream shaderFile(m_path);

        if (!shaderFile.is_open())
        {
            WriteLog(
                actualLogPath,
                std::string("Failed to open shader file: ") +
                m_path
            );

            std::exit(EXIT_FAILURE);
        }

        m_sourceCode.assign(
            std::istreambuf_iterator<char>(shaderFile),
            std::istreambuf_iterator<char>()
        );

        shaderFile.close();

        if (m_sourceCode.empty())
        {
            WriteLog(
                actualLogPath,
                std::string("Shader source is empty: ") +
                m_path
            );

            std::exit(EXIT_FAILURE);
        }

        // ----------------------------------------------------
        // Create OpenGL shader object
        // ----------------------------------------------------

        m_shaderObject = glCreateShader(shaderType);

        if (m_shaderObject == 0)
        {
            WriteLog(
                actualLogPath,
                "glCreateShader failed."
            );

            std::exit(EXIT_FAILURE);
        }

        // ----------------------------------------------------
        // Submit shader source
        // No manual allocation is necessary.
        // ----------------------------------------------------

        const GLchar* source = m_sourceCode.c_str();

        glShaderSource(
            m_shaderObject,
            1,
            &source,
            nullptr
        );

        // ----------------------------------------------------
        // Compile shader
        // ----------------------------------------------------

        glCompileShader(m_shaderObject);

        GLint compileStatus = GL_FALSE;

        glGetShaderiv(
            m_shaderObject,
            GL_COMPILE_STATUS,
            &compileStatus
        );

        // ----------------------------------------------------
        // Handle compilation failure
        // ----------------------------------------------------

        if (compileStatus != GL_TRUE)
        {
            GLint infoLength = 0;

            glGetShaderiv(
                m_shaderObject,
                GL_INFO_LOG_LENGTH,
                &infoLength
            );

            std::string errorLog;

            if (infoLength > 0)
            {
                std::vector<GLchar> buffer(
                    static_cast<size_t>(infoLength),
                    '\0'
                );

                GLsizei written = 0;

                glGetShaderInfoLog(
                    m_shaderObject,
                    infoLength,
                    &written,
                    buffer.data()
                );

                errorLog.assign(
                    buffer.data(),
                    static_cast<size_t>(written)
                );
            }
            else
            {
                errorLog =
                    "No shader compiler information available.";
            }

            WriteLog(
                actualLogPath,
                std::string("Shader compilation failed: ") +
                m_path + "\n" + errorLog
            );

            std::cerr
                << "Shader compilation failed: "
                << m_path << '\n'
                << errorLog << std::endl;

            glDeleteShader(m_shaderObject);
            m_shaderObject = 0;

            std::exit(EXIT_FAILURE);
        }

        // ----------------------------------------------------
        // Compilation successful
        // ----------------------------------------------------

        LOG_ENTRY(
            actualLogPath,
            "Shader Compilation Successful: %s",
            m_path
        );
    }

    // --------------------------------------------------------
    // Get OpenGL shader object
    // --------------------------------------------------------

    GLuint GetObject() const
    {
        return m_shaderObject;
    }

    // --------------------------------------------------------
    // Destructor
    // --------------------------------------------------------

    ~Shader()
    {
        if (m_shaderObject != 0)
        {
            glDeleteShader(m_shaderObject);
            m_shaderObject = 0;
        }
    }

    // Prevent accidental copying of an OpenGL resource owner.
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

private:

    static void WriteLog(
        const char* logFilePath,
        const std::string& message)
    {
        std::ofstream log(
            logFilePath ? logFilePath : "log.txt",
            std::ios::app
        );

        if (log.is_open())
        {
            log << message << '\n';
        }
    }
};
