

#pragma	once

#include 	<fstream>
#include	<string>

class Shader
{
private:

	const char* 	m_path;
	GLuint 	m_shaderObject;
	std::string 	m_sourceCode;


public:
	Shader() : m_path(NULL) {}
	Shader(const char* _path, GLuint shader, const char* logFilePath) : m_path(_path) 
	{
		//	Code

		std::ifstream shaderFile(m_path);
		//std::ofstream output(".\\Output.txt");
		std::string line;

		char* sourceCode = NULL;

		while( std::getline(shaderFile, line ))
		{
			m_sourceCode += line;
			m_sourceCode += "\n";//<< m_sourceCode.c_str() << std::endl;
		}

		//output << m_sourceCode;
	
		shaderFile.close();
		//output.close();

		m_shaderObject = glCreateShader(shader);
		
		sourceCode = (char*) malloc( sizeof(char) * strlen(m_sourceCode.c_str()) );

		strcpy(sourceCode, m_sourceCode.c_str());

		glShaderSource(m_shaderObject, 1, (const GLchar**)&sourceCode, NULL);
	
		glCompileShader(m_shaderObject);	

		GLint	infoLength = 0;
		GLint 	shaderCompileStatus = 0;
		char*	szBuffer = NULL;

		glGetShaderiv(	m_shaderObject,
						GL_COMPILE_STATUS,
						&shaderCompileStatus);

		if( GL_FALSE == shaderCompileStatus )
		{
			glGetShaderiv(	m_shaderObject,
							GL_INFO_LOG_LENGTH,
							&infoLength);

			if( 0 < infoLength )
			{
				szBuffer = (char*) malloc(sizeof(char) * infoLength);

				if( NULL != szBuffer)
				{
					GLsizei written;

					glGetShaderInfoLog(	m_shaderObject,
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
		free(sourceCode);
	}

	GLuint 	GetObject() const { return(m_shaderObject); }
	
};

