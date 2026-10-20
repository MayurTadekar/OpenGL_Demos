// header files
#include "Grass.h"

#define LERP(X,X0,X1,Y0,Y1) ((( X - X0 ) / ( X1 - X0)) * ( Y1 - Y0) + Y0 )
#define RNUM(begin,end) ( LERP ( (float)rand(), 0.0f, (float)RAND_MAX, begin, end )) 

static GLuint vertexShaderObject = 0;
static GLuint geometryShaderObject = 0;
static GLuint fragmentShaderObject = 0;
static GLuint shaderProgramObject = 0;

enum
{
    GRASS_ATTRIBUTE_POSITION = 0,
    GRASS_ATTRIBUTE_TIME
};

// // OpenCL related globals

//     extern cl_device_id oclDeviceID;
//     extern cl_context oclContext;
//     extern cl_command_queue oclCommandQueue; 
    
// 	cl_program oclProgram = NULL;
// 	cl_kernel oclKernel = NULL;
// 	//cl_platform_id oclPlatformID = NULL;

// 	cl_mem ocl_graphics_resource = NULL;	// OpenCL sathi
// 	// CUDA stathi = struct cudaGraphicsResource * cuda_graphics_resource = NULL;

//     static cl_int oclResult;

GLuint getGrassUniform(const char * name);

// implementation of class Grass
Grass::Grass(void)
{
    // function declarations
    char* readFileAsString(const char *szFilename, int *pFileSize, bool bRemoveCRLFs);

    // code
    
	// Vertex Shader
	const GLchar* vertexShaderSourceCode = readFileAsString("./effects/Grass/GrassShader.vert", NULL, true);
    // vertex shader string ends here
    // shader mdhla mat4 ha vmath.h mdhla NAHI, shader mdhla mat4 ha GLSL cha inbuild datatype ahe

    vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

    glCompileShader(vertexShaderObject);

    GLint status = 0;
    GLint infoLogLength = 0;
    GLchar* szInfoLog = NULL;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
        
            if(szInfoLog != NULL)
            {
                glGetShaderInfoLog(vertexShaderObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Vertex shader compilation error log : %s \n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }
        uninitialize();
    }

    // Geometry Shader
    const GLchar* geometryShaderSourceCode = readFileAsString("./effects/Grass/GrassShader.geom", NULL, true);
        // Geometry shader string ends here

    geometryShaderObject = glCreateShader(GL_GEOMETRY_SHADER);

    glShaderSource(geometryShaderObject, 1, (const GLchar**)&geometryShaderSourceCode, NULL);

    glCompileShader(geometryShaderObject);	

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(geometryShaderObject, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        glGetShaderiv(geometryShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
        
            if(szInfoLog != NULL)
            {
                glGetShaderInfoLog(geometryShaderObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Geometry shader compilation error log : %s \n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }
        
        uninitialize();
    }



    // Fragment Shader
    const GLchar* fragmentShaderSourceCode =readFileAsString("./effects/Grass/GrassShader.frag", NULL, true);
    // fragment shader string ends here

    fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);

    glCompileShader(fragmentShaderObject);	

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
        
            if(szInfoLog != NULL)
            {
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Fragment shader compilation error log : %s \n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }
        
        uninitialize();
    }

    // Shader Program
    shaderProgramObject = glCreateProgram();
    glAttachShader(shaderProgramObject, vertexShaderObject);
    glAttachShader(shaderProgramObject, geometryShaderObject);
    glAttachShader(shaderProgramObject, fragmentShaderObject);

    glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");

    glLinkProgram(shaderProgramObject);

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        glGetProgramiv(shaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar*)malloc(infoLogLength);
        
            if(szInfoLog != NULL)
            {
                glGetProgramInfoLog(shaderProgramObject, infoLogLength, NULL, szInfoLog);
                fprintf(gpFILE, "Shader program linking error log : %s \n", szInfoLog);
                free(szInfoLog);
                szInfoLog = NULL;
            }
        }
        uninitialize();
    }


    // load textures
    m_grassTexture = loadTexture("./resources/Texture/Grass.png", TRUE);
    m_flowTexture  = loadTexture("./resources/Texture/Flowmap.png", TRUE);

    GrassVertex vertex;
    vertex.position = vmath::vec3(0.0f, 0.0f, 0.0f);
    vertex.animationTime = RNUM( 0.0f, 1.0f);

    m_positions.push_back(vertex);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    
    // // OpenCL Kernel related 
    //     // Declare OpenCL Kernel code
    //     const char * oclKernelSourceCode = 
    //     "struct GrassVertex" \
    //     "{ " \
    //     "   float position[3]; " \
    //     "   float animationTime; " \
    //     "};" \
    //     "__kernel void GrassAnimationKernel (__global struct GrassVertex* vertices)" \
    //     "{" \
    //     "int  x = get_global_id(0);" \
    //     "vertices[x].animationTime = vertices[x].animationTime + 0.01;" \
    //     "}";

    //     // from above kernel code create OpenCL program
    //     oclProgram = clCreateProgramWithSource(oclContext, 1, (const char **)&oclKernelSourceCode, NULL, &oclResult);
    //     if (oclResult != CL_SUCCESS)
    //     {
    //         fprintf(gpFILE, "clCreateProgramWithSource() Failed...!\n");
    //         uninitialize();
    //         exit(0);
    //     }

    //     // build OpenCL program
    //     oclResult = clBuildProgram(oclProgram, 0, NULL, "-cl-fast-relaxed-math", NULL, NULL);
    //     if (oclResult != CL_SUCCESS)
    //     {
    //         fprintf(gpFILE, "clBuildProgram() Failed...!\n");

    //         // get prgram build error
    //         cl_int oclBuildResult;
    //         char szBuffer[1024];
    //         oclBuildResult = clGetProgramBuildInfo(oclProgram, oclDeviceID, CL_PROGRAM_BUILD_LOG, sizeof(szBuffer), szBuffer, NULL);
    //         if (oclBuildResult != CL_SUCCESS)
    //         {
    //             fprintf(gpFILE, "clGetProgramBuildInfo() Failed...!\n");
    //         }
    //         else{
    //             fprintf(gpFILE, "OpenCl Program Build error : %s", szBuffer);
    //         }

    //         uninitialize();
    //         exit(0);
    //     }

    //     // create OpenCL kernel by passing kernel function name that we usedin .cl file
    //     oclKernel = clCreateKernel(oclProgram, "GrassAnimationKernel", &oclResult);
    //     if (oclResult != CL_SUCCESS)
    //     {
    //         fprintf(gpFILE, "clCreateKernel() Failed...!\n");
    //         uninitialize();
    //         exit(0);
    //     }
}

void Grass::generateGrass(void)
{
    // code

    for(int i = 0; i < m_numGrassBladesToGenerate; i++)
    {
        GrassVertex vertex;
        vertex.position = vmath::vec3(RNUM(m_generationVectorStart[0], m_generationVectorEnd[0]), 0.0f, RNUM(m_generationVectorStart[1], m_generationVectorEnd[1]));
        vertex.animationTime = RNUM( 0.0f, 1.0f);

        m_positions.push_back(vertex);
    }

    // create VAO and VBO
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    {
        glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(GrassVertex), m_positions.data(), GL_DYNAMIC_DRAW);

        glVertexAttribPointer(GRASS_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GrassVertex), nullptr);
        glEnableVertexAttribArray(GRASS_ATTRIBUTE_POSITION);

        glVertexAttribPointer(GRASS_ATTRIBUTE_TIME, 1, GL_FLOAT, GL_FALSE, sizeof(GrassVertex), (const void *) (sizeof(vmath::vec3)));
        glEnableVertexAttribArray(GRASS_ATTRIBUTE_TIME);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);    

    // // VIMP : Prepare or register OpenGLbuffer to OpenCL Graphics resource for interoperabiity 
    // ocl_graphics_resource = clCreateFromGLBuffer(oclContext, CL_MEM_WRITE_ONLY, m_vbo, &oclResult);
    
    // if (oclResult != CL_SUCCESS)
    // {
    //     fprintf(gpFILE, "clCreateFromGLBuffer() Failed...!\n");
    //     uninitialize();
    //     exit(0);
    // }
}

void Grass::render(vmath::mat4 viewMatrix, vmath::mat4 projectionMatrix, vmath::vec3 cameraPosition)
{
    // code
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(shaderProgramObject);
    {
        // load values into shader uniforms
        // m_shader.loadMatrix("uModelMatrix", vmath::mat4::identity());
        glUniformMatrix4fv( getGrassUniform("u_model"), 1, GL_FALSE, vmath::translate(0.0f, m_grassY, 0.0f) * vmath::scale(m_scale));
        glUniformMatrix4fv( getGrassUniform("u_view"), 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv( getGrassUniform("u_projection"), 1, GL_FALSE, projectionMatrix);
        glUniform1f( getGrassUniform("u_time"), m_animationTime);
        glUniform3fv( getGrassUniform("u_cameraPosition"), 1, cameraPosition);
        glUniform1i( getGrassUniform("u_wind"), 0);
        glUniform1i( getGrassUniform("u_textgrass"), 1);

        // bind the flowmap texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_flowTexture.id);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_grassTexture.id);

        glBindVertexArray(m_vao);
        {
            glDrawArrays(GL_POINTS, 0, m_positions.size());
        }
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glUseProgram(0);
    glDisable(GL_BLEND);
}

void Grass::update(void)
{
    size_t roundGlobalSizeToNearestMultipleOfLocalSize(int local_size, unsigned int global_size);

    // code
    for( int i = 0; i<m_positions.size(); i++ )
    {
        (m_positions.data()[i]).animationTime += 1.0f;
    }

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    {
        glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(GrassVertex), m_positions.data(), GL_DYNAMIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
   


}

Grass::~Grass(void)
{
    // code
	if(shaderProgramObject)
	{
		glUseProgram(shaderProgramObject);

		GLint numShaders = 0;
		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShaders);

		if(numShaders > 0)
		{
			GLuint* pShaders = (GLuint*)malloc(numShaders * sizeof(GLuint));
			if(pShaders != NULL)
			{
				glGetAttachedShaders(shaderProgramObject, numShaders, NULL, pShaders);
				for(GLint i = 0; i < numShaders; i++)
				{
					glDetachShader(shaderProgramObject, pShaders[i]);
					glDeleteShader(pShaders[i]);
					pShaders[i] = 0;
				}
				free(pShaders);
				pShaders = NULL;
			}
		}

		glUseProgram(0);
		glDeleteProgram(shaderProgramObject);
		shaderProgramObject = 0;
	}

	if(m_vbo)
	{
		// if(ocl_graphics_resource)
		// {
		// 	clReleaseMemObject(ocl_graphics_resource);
		// 	ocl_graphics_resource = NULL;
		// }
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}

	// // Release OpenCl kernel 
	// if(oclKernel)
    // {
    //     clReleaseKernel(oclKernel);
    //     oclKernel = NULL;
    // }

	// // Release OpenCl Program 
	// if(oclProgram)
    // {
    //     clReleaseProgram(oclProgram);
    //     oclProgram = NULL;
    // }

    // delete vao
    if(m_vao)
    {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }    
}

GLuint getGrassUniform(const char * name) 
{
    return (glGetUniformLocation(shaderProgramObject, name));
}

char* readFileAsString(const char *szFilename, int *pFileSize, bool bRemoveCRLFs) // CRLFs == Carriage Return Line Feeds (\r\n)
{
    // local variables
    char *szString      = nullptr;
    FILE *pFile         = nullptr;
    int fileSizeInBytes = 0;

    // code
    // open the file
    if(fopen_s(&pFile, szFilename, "r") != 0)
    {
        LOG("%s() : fopen_s() failed to open the file \"%s\".\n", __FUNCTION__, szFilename);
        exit(EXIT_FAILURE);
    }

    // seek to the end of the file
    fseek(pFile, 0, SEEK_END);

    // get the current byte offset of the file
    fileSizeInBytes = ftell(pFile);

    // save the file into the out parameter
    if(pFileSize)
    {
        *pFileSize = fileSizeInBytes;
    }

    // seek back to the start of file
    fseek(pFile, 0, SEEK_SET);

    // allocate memory for the string
    szString = (char *)malloc(sizeof(char) * (fileSizeInBytes + 1));
    if(szString == nullptr)
    {
        // close the file
        fclose(pFile);
        pFile = nullptr;

        LOG("%s() : malloc() failed to allocate memory for szString.\n", __FUNCTION__);
        exit(EXIT_FAILURE);
    }

    // read the file
    // remove CRLFs
    if(bRemoveCRLFs)
    {
        for(int i = 0; i < fileSizeInBytes; i++)
        {
            char c = fgetc(pFile);
            if(c == '\r')
            {
                c = ' ';
            }
            else if(c == EOF)
            {
                szString[i] = '\0';
                break;
            }
            
            szString[i] = c;
        }
    }
    else // read data normally
    {
        fread(szString, sizeof(char), fileSizeInBytes, pFile);
    }

#ifdef IO_DEBUG
    LOG(BORDER);
    LOG("PRINTING SHADER SOURCE\n\n");
    LOG("%s", szString);
    LOG(BORDER);
#endif // IO_DEBUG

    // set the null terminator in the string
    szString[fileSizeInBytes] = '\0';

    // close the file
    fclose(pFile);
    pFile = nullptr;

    return(szString);
}

size_t roundGlobalSizeToNearestMultipleOfLocalSize(int local_size, unsigned int global_size)
{
    int r = global_size % local_size;
    if(r == 0)
    {
        return(global_size);
    }
    else
    {
        return(global_size + local_size - r);
    }
}
