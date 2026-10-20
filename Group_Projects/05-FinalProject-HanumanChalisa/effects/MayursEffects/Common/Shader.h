

#pragma once

#include <fstream>
#include <string>
#include "common.h"

class Shader
{
private:
	const char *m_path;
	GLuint m_shaderObject;
	std::string m_sourceCode;

public:
	Shader() : m_path(NULL) {}
	Shader(const char *_path, GLuint shader, const char *logFilePath) : m_path(_path)
	{
		//	Code

		std::ifstream shaderFile(m_path);
		// std::ofstream output(".\\Output.txt");
		std::string line;

		char *sourceCode = NULL;

		while (std::getline(shaderFile, line))
		{
			m_sourceCode += line;
			m_sourceCode += "\n"; //<< m_sourceCode.c_str() << std::endl;
								  // LOG_ENTRY("log.txt", line.c_str());
		}

		// output << m_sourceCode;

		shaderFile.close();
		// output.close();

		LOG_ENTRY("log.txt", "MST: Creating Shader");
		m_shaderObject = glCreateShader(shader);

		sourceCode = (char *)malloc(sizeof(char) * strlen(m_sourceCode.c_str()));

		strcpy(sourceCode, m_sourceCode.c_str());

		LOG_ENTRY("log.txt", "MST: Copying Shader Source");
		glShaderSource(m_shaderObject, 1, (const GLchar **)&sourceCode, NULL);

		LOG_ENTRY("log.txt", "MST: Compiling Shader Source");
		glCompileShader(m_shaderObject);
		LOG_ENTRY("log.txt", "MST: Compiling Shader Source Success");

		GLint infoLength = 0;
		GLint shaderCompileStatus = 0;
		char *szBuffer = NULL;

		LOG_ENTRY("log.txt", "MST: Getting Shader Source Status");
		glGetShaderiv(m_shaderObject,
					  GL_COMPILE_STATUS,
					  &shaderCompileStatus);
		LOG_ENTRY("log.txt", "MST: Getting Shader Source Status Success");

		if (GL_FALSE == shaderCompileStatus)
		{
			LOG_ENTRY("log.txt", "MST: Shader Source Status not good");

			glGetShaderiv(m_shaderObject,
						  GL_INFO_LOG_LENGTH,
						  &infoLength);

			LOG_ENTRY("log.txt", "MST: Getting Shader Source Status Success");

			if (0 < infoLength)
			{
				LOG_ENTRY("log.txt", "MST: Got some Info");

				szBuffer = (char *)malloc(sizeof(char) * infoLength);

				if (NULL != szBuffer)
				{
					GLsizei written;

					glGetShaderInfoLog(m_shaderObject,
									   infoLength,
									   &written,
									   szBuffer);

					std::ofstream log(logFilePath);
					log << szBuffer << std::endl;
					log.close();
					free(szBuffer);
					exit(1);
				}
			}
		}

		if (sourceCode)
		{
			free(sourceCode);
			sourceCode = NULL;
		}

		LOG_ENTRY("log.txt", "MST: Creating Shader Source Success");
	}

	GLuint GetObject() const { return (m_shaderObject); }
	GLuint GetShaderObject() const { return (m_shaderObject); }
};
