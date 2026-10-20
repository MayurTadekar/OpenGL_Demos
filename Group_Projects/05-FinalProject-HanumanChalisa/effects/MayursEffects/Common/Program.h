

#pragma once

#include <cstdarg>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/GL.h>
#include "common.h"

class Program
{
private:
	GLuint m_programObject;
	char *logFile;

public:
	Program() : m_programObject(0) {}
	Program(int shaderCount, ...)
	{
		//	Code
		m_programObject = glCreateProgram();

		va_list varg;
		va_start(varg, shaderCount);
		for (int i = 0; i < shaderCount; ++i)
		{
			glAttachShader(m_programObject, va_arg(varg, GLuint));
		}
		va_end(varg);
	}

	~Program()
	{
		glUseProgram(m_programObject);

		GLsizei shaderCount = 0;

		glGetProgramiv(m_programObject, GL_ATTACHED_SHADERS, &shaderCount);

		GLuint *pShader = NULL;

		pShader = (GLuint *)malloc(sizeof(GLuint) * shaderCount);

		if (pShader == NULL)
		{
			std::ofstream log(logFile, std::ios_base::app);
			log << "ERROR: Error in pShader" << std::endl;
			log.close();
		}

		glGetAttachedShaders(m_programObject, shaderCount, &shaderCount, pShader);

		for (GLsizei i = 0; i < shaderCount; i++)
		{
			glDetachShader(m_programObject, pShader[i]);
			glDeleteShader(pShader[i]);
			pShader[i] = 0;
		}

		free(pShader);

		glDeleteProgram(m_programObject);

		m_programObject = 0;

		glUseProgram(0);
	}

	void LinkProgram(const char *logFilePath)
	{
		glLinkProgram(m_programObject);

		logFile = (char *)malloc(sizeof(char) * strlen(logFilePath));
		strcpy(logFile, logFilePath);

		GLint infoLength = 0;
		GLint shaderCompileStatus = 0;
		char *szBuffer = NULL;
		GLint shaderProgramLinkStatus = 0;

		glGetProgramiv(m_programObject,
					   GL_LINK_STATUS,
					   &shaderProgramLinkStatus);

		if (GL_FALSE == shaderProgramLinkStatus)
		{
			glGetShaderiv(m_programObject,
						  GL_INFO_LOG_LENGTH,
						  &infoLength);

			if (0 < infoLength)
			{
				szBuffer = (char *)malloc(sizeof(char) * infoLength);
				if (NULL != szBuffer)
				{
					GLint written;
					glGetProgramInfoLog(m_programObject,
										infoLength,
										&written,
										szBuffer);

					std::ofstream log(logFilePath);
					log << szBuffer << std::endl;
					free(szBuffer);
					log.close();
					exit(1);
				}
			}
		}
	}

	GLuint GetObject() const { return (m_programObject); }
	GLuint GetProgramObject() const { return (m_programObject); }
};
