/******************************************* Header Files *******************************************/
#include "Terrain.h"

/******************************************* Variable Declaration *******************************************/

/******************************************* Class Function Defination *******************************************/
Terrain::Terrain()
{
    // Shader Related variables
    this->ShaderProgramObject = 0;
    this->VAO = 0;
    this->VBO = 0;

    // Transformations related uniforms
    this->ModelMatrixUniform = 0;
    this->ViewMatrixUniform = 0;
    this->ProjectionMatrixUniform = 0;

    this->PerspectiveProjectionMatrix = vmath::mat4::identity();

    this->TerrainResolution = 1024;
    this->TerrainLength = 1024.0f;
    this->TerrainHeightScale = 500.0f;

    this->TerrainWorldSizeUniform = 0;
    this->HeightScaleUniform = 0;

    // Light related variables
    const GLfloat pitchRad = ToRad(-60.0f);
    const GLfloat headingRad = ToRad(145.0f);

    LightDirection[0] = cosf(pitchRad) * sinf(headingRad);
    LightDirection[1] = sinf(pitchRad);
    LightDirection[2] = cosf(pitchRad) * cosf(headingRad);

    // Setting Light Colors
    LightColor[0] = 5.0f;
    LightColor[1] = 5.0f;
    LightColor[2] = 5.0f;

    this->LightColorUniform = 0; 
    this->LightDirectionUniform = 0;
    this->CameraPositionUniform = 0;

    this->HeightMapTexture = 0;
    this->AlbedoMapTexture = 0;
    this->NormalMapTexture = 0;
    this->RoughnessMapTexture = 0;
    this->AmbientOcclusionMapTexture = 0;

    this->HeightMapSamplerUniform = 0;
    this->AlbedoMapSamplerUniform = 0;
    this->NormalMapSamplerUniform = 0;
    this->RoughnessMapSamplerUniform = 0;
    this->AmbientOcclusionMapSamplerUniform = 0;
}

int Terrain::initialize(const char * HeightMapPath, const char * AlbedoMapPath, const char * NormalMapPath, const char * RoughnessMapPath, const char * AOMapPath)
{
    /////////////////////////////////////////// VERTEX SHADER ///////////////////////////////////////////
    const GLchar * vertexShaderSourcecode = LoadShaderSource("./effects/Terrain/Terrain.vert");
    if(vertexShaderSourcecode == NULL)
    {
        LOG("Failed to get Vertex shader code from Terrain file!!\n");
        return(-1);
    }

    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	// This function creates a shader object according to shader type

    glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourcecode, NULL);
    // This function gives shader sourcecode to shader object
	// 1st parameter = to which object
	// 2nd parameter = no of shaders (Array size)
	// 3rd parameter = Address of shader array
	// 4th parameter = array of sizes of shader in array

    glCompileShader(vertexShaderObject);
    // This function Compiles the shader

    GLint status = 0;
    GLint infoLogLength = 0;
    GLchar * szInfoLog = NULL;

    glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &status);
    // This function fills the status variable with state of compilation
	// 1st parameter = Shader object
	// 2nd parameter = what info you want
	// 3rd parameter = out parameter

    if(status == GL_FALSE)
    {
        glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
         // This function fills the status variable with state of compilation
        // 1st parameter = Shader object
        // 2nd parameter = what info you want
        // 3rd parameter = out parameter

        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(infoLogLength * sizeof(GLchar));
            if(szInfoLog != NULL)
            {
                glGetShaderInfoLog(vertexShaderObject, infoLogLength, NULL, szInfoLog);
                // This function fills error in szInfoLog
				// 1st parameter = which shader 
				// 2nd parameter = length of log
				// 3rd parameter = Actual returned length of string of error
				// 4th paramter = out parameter

                LOG("Terrain : Vertex Shader Compilation Log : %s\n", szInfoLog);

                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        return(-1);
    }

    /////////////////////////////////////////// FRAGMENT SHADER ///////////////////////////////////////////
    const GLchar * fragmentShaderSourcecode = LoadShaderSource("./effects/Terrain/Terrain.frag");
    if(fragmentShaderSourcecode == NULL)
    {
        LOG("Failed to get Fragment shader code from Terrain file!!\n");
        return(-1);
    }

    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    // This function creates a shader object according to shader type

    glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderSourcecode, NULL);
    // This function gives shader sourcecode to shader object
	// 1st parameter = to which object
	// 2nd parameter = no of shaders (Array size)
	// 3rd parameter = Address of shader array
	// 4th parameter = array of sizes of shader in array

    glCompileShader(fragmentShaderObject);
    // This function Compiles the shader

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &status);
    // This function fills the status variable with state of compilation
	// 1st parameter = Shader object
	// 2nd parameter = what info you want
	// 3rd parameter = out parameter

    if(status == GL_FALSE)
    {
        glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        // This function fills the status variable with state of compilation
        // 1st parameter = Shader object
        // 2nd parameter = what info you want
        // 3rd parameter = out parameter

        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(infoLogLength * sizeof(GLchar));
            if(szInfoLog != NULL)
            {
                glGetShaderInfoLog(fragmentShaderObject, infoLogLength, NULL, szInfoLog);
                // This function fills error in szInfoLog
				// 1st parameter = which shader 
				// 2nd parameter = length of log
				// 3rd parameter = Actual returned length of string of error
				// 4th paramter = out parameter

                LOG("Terrain : Fragment Shader Compilation Log : %s\n", szInfoLog);

                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        return(-1);
    }

    // Create, Link, Attach Shader Program Object
    this->ShaderProgramObject = glCreateProgram();
    // Here we create Shader Program Object

    glAttachShader(this->ShaderProgramObject, vertexShaderObject);
    glAttachShader(this->ShaderProgramObject, fragmentShaderObject);

    glBindAttribLocation(this->ShaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
    // Bind Shader Attribute at a certain index in shader to same index in host program
    // 1st parameter = Shader Program object
	// 2nd parameter = Host memory index (CPU memory index)
	// 3rd parameter = Guest memory position

    glBindAttribLocation(this->ShaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexcoord");
    // Bind Shader Attribute at a certain index in shader to same index in host program
    // 1st parameter = Shader Program object
	// 2nd parameter = Host memory index (CPU memory index)
	// 3rd parameter = Guest memory position

    glLinkProgram(this->ShaderProgramObject);
    // Linking the Shader Program Object

    status = 0;
    infoLogLength = 0;
    szInfoLog = NULL;

    glGetProgramiv(this->ShaderProgramObject, GL_LINK_STATUS, &status);
    // This function fills the status variable with state of linking
	// 1st parameter = Shader Program object
	// 2nd parameter = what info you want
	// 3rd parameter = out parameter

    if(status == GL_FALSE)
    {
        glGetProgramiv(this->ShaderProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        // This function fills the status variable with log length
		// 1st parameter = Shader Program object
		// 2nd parameter = what info you want
		// 3rd parameter = out parameter

        if(infoLogLength > 0)
        {
            szInfoLog = (GLchar *)malloc(infoLogLength * sizeof(GLchar));
            if(szInfoLog != NULL)
            {
                glGetProgramInfoLog(this->ShaderProgramObject, infoLogLength, NULL, szInfoLog);
                // This function fills error in szInfoLog
				// 1st parameter = which program
				// 2nd parameter = length of log
				// 3rd parameter = Actual returned length of string of error
				// 4th paramter = out parameter

                LOG("Terrain :Shader Program Link Log : %s\n", szInfoLog);

                free(szInfoLog);
                szInfoLog = NULL;
            }
        }

        return(-1);
    }

    // Getting Uniform Locations
    this->ModelMatrixUniform = glGetUniformLocation(this->ShaderProgramObject, "uModelMatrix");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position 

    this->ViewMatrixUniform = glGetUniformLocation(this->ShaderProgramObject, "uViewMatrix");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position 

    this->ProjectionMatrixUniform = glGetUniformLocation(this->ShaderProgramObject, "uProjectionMatrix");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->LightColorUniform = glGetUniformLocation(this->ShaderProgramObject, "uLightColor");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position
 
    this->LightDirectionUniform = glGetUniformLocation(this->ShaderProgramObject, "uLightDirection");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->CameraPositionUniform = glGetUniformLocation(this->ShaderProgramObject, "uCamPosition");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->HeightMapSamplerUniform = glGetUniformLocation(this->ShaderProgramObject, "uHeightMap");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->AlbedoMapSamplerUniform = glGetUniformLocation(this->ShaderProgramObject, "uAlbedoMap");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->NormalMapSamplerUniform = glGetUniformLocation(this->ShaderProgramObject, "uNormalMap");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->RoughnessMapSamplerUniform = glGetUniformLocation(this->ShaderProgramObject, "uRoughnessMap");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->AmbientOcclusionMapSamplerUniform = glGetUniformLocation(this->ShaderProgramObject, "uAmbientOcclusionMap");
    // 1st parameter = Shader Program Object
	// 2nd parameter = uniform location position

    this->TerrainWorldSizeUniform = glGetUniformLocation(this->ShaderProgramObject, "uTerrainWorldSize");
    this->HeightScaleUniform = glGetUniformLocation(this->ShaderProgramObject, "uHeightScale");

    // Generate Data
    this->GenerateTerrainData(  this->TerrainResolution, this->TerrainResolution,
                                ((this->TerrainLength * 3.0f)/4.0f), this->TerrainLength, 
                                &(this->MeshVertexdata), &(this->MeshVertexDataCount),
                                &(this->IndexData), &(this->IndexCount));

    glGenVertexArrays(1, &(this->VAO));
    // Generated Vertex array object for passing arrays of attributes related to vertex data
    // 1st paarmeter = number of arrays
	// 2nd parameter = out paarmeter to store vertex array object

    glBindVertexArray(this->VAO);
    // This function initiate the casset to start recording all the array and associate them with vertex array object.
	// By associating them with vertex array object, array become available for runtime changes 

    glGenBuffers(1, &(this->VBO));
    // this function creates Buffer on GPU side for storing input
	// 1st parameter = no of buffers
	// 2nd parameter = out parameter storing memory location id where this buffer is created

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // This function binds the GPU Buffer location with vbo_position
	// 1st parameter = this is Array Buffer (Binding Point)
	// 2nd parameter = to which it should bind on host side

    glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * this->MeshVertexDataCount), this->MeshVertexdata, GL_STATIC_DRAW);
    // Adding Data to the buffer
	// 1st parameter = Binding point
	// 2nd parameter = Size of data in bytes
	// 3rd parameter = actual data
	// 4th parameter = Data should be changed or not 

    // POSITION
    glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void *)(0 * sizeof(float)));
    // Tell Gpu how to use this data in that buffer
	// 1st parameter = Where i have binded this data in shader (at which index) (that location is binded at AMC_ATTR... on host)
	// 2nd paarmeter = Split data in group of 3-3
	// 3rd parameter = Tell me data type of data so i can hop between 3 elements to next 3 elements
	// 4th parameter = Are these values normalize (even if they are, GL_FALSE re normalize them)
	// 5th parameter = If you have stores all the data (position data, vertex data, etc) in 1 buffer , how much big my stride(Dhanga) must be to separate this data
	//                 as we are not combing all data in 1 buffer this value is 0 here
	// 6th parameter = Decribes the values after we take that stride, here it is NULL 

    glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
    // This enables the Binding point and is transfered from Host to Guest

    // TEXCOORDS
    glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void *)(3 * sizeof(float)));
    // Tell Gpu how to use this data in that buffer
	// 1st parameter = Where i have binded this data in shader (at which index) (that location is binded at AMC_ATTR... on host)
	// 2nd paarmeter = Split data in group of 3-3
	// 3rd parameter = Tell me data type of data so i can hop between 3 elements to next 3 elements
	// 4th parameter = Are these values normalize (even if they are, GL_FALSE re normalize them)
	// 5th parameter = If you have stores all the data (position data, vertex data, etc) in 1 buffer , how much big my stride(Dhanga) must be to separate this data
	//                 as we are not combing all data in 1 buffer this value is 0 here
	// 6th parameter = Decribes the values after we take that stride, here it is NULL 

    glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);
    // This enables the Binding point and is transfered from Host to Guest

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind VBO_Position
    
    glGenBuffers(1, &(this->EBO));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLuint) * this->IndexCount), this->IndexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    // Unbind VAO

    if(loadTerrainTexture(&(this->HeightMapTexture), HeightMapPath) == GL_FALSE)
    {
        LOG("Terrain : Failed to load HeightMap Texture!!\n");
        return(-1);
    }

    if(loadTerrainTexture(&(this->AlbedoMapTexture), AlbedoMapPath) == GL_FALSE)
    {
        LOG("Terrain : Failed to load AlbedoMap Texture!!\n");
        return(-2);
    }

    if(loadTerrainTexture(&(this->NormalMapTexture), NormalMapPath) == GL_FALSE)
    {
        LOG("Terrain : Failed to load NormalMap Texture!!\n");
        return(-3);
    }

    if(loadTerrainTexture(&(this->RoughnessMapTexture), RoughnessMapPath) == GL_FALSE)
    {
        LOG("Terrain : Failed to load RoughnessMap Texture!!\n");
        return(-4);
    }

    if(loadTerrainTexture(&(this->AmbientOcclusionMapTexture), AOMapPath) == GL_FALSE)
    {
        LOG("Terrain : Failed to load AmbientOcclusion Texture!!\n");
        return(-5);
    }

    return(0);
}

void Terrain::GenerateTerrainData(  int resX, int resZ,
                                    GLfloat sizeX, GLfloat sizeZ,
                                    GLfloat** MeshData, int* MeshDataCount,
                                    GLuint** Indices, int* IndexCount)
{
    // 1. Vertex count (ONLY grid points)
    int vertexCount = resX * resZ;

    // Each vertex = 3 pos + 2 texcoord
    int totalDataCount = vertexCount * 5;

    GLfloat* VertexData = (GLfloat*)malloc(sizeof(GLfloat) * totalDataCount);

    int index = 0;

    // Step sizes
    GLfloat stepX = sizeX / (resX - 1);
    GLfloat stepZ = sizeZ / (resZ - 1);

    // 2. Generate vertices (GRID, not quads)
    for (int z = 0; z < resZ; z++)
    {
        for (int x = 0; x < resX; x++)
        {
            // Center the terrain around origin
            GLfloat posX = (x * stepX) - (sizeX * 0.5f);
            GLfloat posZ = (z * stepZ) - (sizeZ * 0.5f);

            // Position
            VertexData[index++] = posX;
            VertexData[index++] = 0.0f;
            VertexData[index++] = posZ;

            // Texcoords (0 → 1)
            VertexData[index++] = (GLfloat)x / (resX - 1);
            VertexData[index++] = (GLfloat)z / (resZ - 1);
        }
    }

    // 3. Generate indices
    int quadCount = (resX - 1) * (resZ - 1);
    int indexCount = quadCount * 6;

    GLuint* indices = (GLuint*)malloc(sizeof(GLuint) * indexCount);

    int idx = 0;

    for (int z = 0; z < resZ - 1; z++)
    {
        for (int x = 0; x < resX - 1; x++)
        {
            int topLeft     = z * resX + x;
            int topRight    = topLeft + 1;
            int bottomLeft  = (z + 1) * resX + x;
            int bottomRight = bottomLeft + 1;

            // Triangle 1
            indices[idx++] = topLeft;
            indices[idx++] = bottomLeft;
            indices[idx++] = topRight;

            // Triangle 2
            indices[idx++] = topRight;
            indices[idx++] = bottomLeft;
            indices[idx++] = bottomRight;
        }
    }

    // Output
    *MeshData = VertexData;
    *MeshDataCount = totalDataCount;

    *Indices = indices;
    *IndexCount = indexCount;
}


void Terrain::render(Camera *pCamera, vmath::mat4 projectionMatrix)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glUseProgram(this->ShaderProgramObject);

    // Transformation
    vmath::mat4 ModelMatrix = vmath::mat4::identity();
    vmath::mat4 ViewMatrix = vmath::mat4::identity();
    vmath::mat4 ProjectionMatrix = vmath::mat4::identity();

    vmath::mat4 TranslationMatrix = vmath::mat4::identity();

    TranslationMatrix = vmath::translate(0.0f, -180.0f, 0.0f);
    
    ModelMatrix = TranslationMatrix;

    ProjectionMatrix = projectionMatrix;

    ViewMatrix = pCamera->getLookAtMatrix();

    // Transfering Uniforms
    glUniformMatrix4fv(this->ModelMatrixUniform, 1, GL_FALSE, ModelMatrix);
    // This function Sends this matrix to vertex shader in uniform
	// 1st parameter = location of uniform taken at host side
	// 2nd parameter = number of matrices , here 1
	// 3rd paarmeter = need to transform this matrix or not ?
	// 4th parameter = that matrix

    glUniformMatrix4fv(this->ViewMatrixUniform, 1, GL_FALSE, ViewMatrix);
    // This function Sends this matrix to vertex shader in uniform
	// 1st parameter = location of uniform taken at host side
	// 2nd parameter = number of matrices , here 1
	// 3rd paarmeter = need to transform this matrix or not ?
	// 4th parameter = that matrix

    glUniformMatrix4fv(this->ProjectionMatrixUniform, 1, GL_FALSE, ProjectionMatrix);
    // This function Sends this matrix to vertex shader in uniform
	// 1st parameter = location of uniform taken at host side
	// 2nd parameter = number of matrices , here 1
	// 3rd paarmeter = need to transform this matrix or not ?
	// 4th parameter = that matrix

    // Light Related Uniforms
    glUniform3fv(this->LightColorUniform, 1, LightColor);
    glUniform3fv(this->LightDirectionUniform, 1, LightDirection);
    glUniform3fv(this->CameraPositionUniform, 1, pCamera->m_position);

    glUniform2f(this->TerrainWorldSizeUniform, this->TerrainLength, this->TerrainLength);
    glUniform1f(this->HeightScaleUniform, this->TerrainHeightScale);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->HeightMapTexture);
    glUniform1i(this->HeightMapSamplerUniform, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->AlbedoMapTexture);
    glUniform1i(this->AlbedoMapSamplerUniform, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, this->NormalMapTexture);
    glUniform1i(this->NormalMapSamplerUniform, 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, this->RoughnessMapTexture);
    glUniform1i(this->RoughnessMapSamplerUniform, 3);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, this->AmbientOcclusionMapTexture);
    glUniform1i(this->AmbientOcclusionMapSamplerUniform, 4);

    // Bind VAO
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

    glDrawElements(GL_TRIANGLES, this->IndexCount, GL_UNSIGNED_INT, 0);
    // Draw the vertex Arrays
	// 1st parameter = Which Geometry
	// 2nd Parameter = From which index to start
	// 3rd Parameter = How mant time Shader should run (How many threads shader should create to Draw)

    glBindVertexArray(0);

    glUseProgram(0);

    glDisable(GL_CULL_FACE);
}

void Terrain::update(void)
{
	// code
}

void Terrain::uninitialize(void)
{
    if(this->VBO)
    {
        glDeleteBuffers(1, &(this->VBO));
        this->VBO = 0;
    }

    if(this->VAO)
    {
        glDeleteVertexArrays(1, &(this->VAO));
        this->VAO = 0;
    }

    // Detach, Delete Shader objects and Delete Shader Program Object
    if(this->ShaderProgramObject)
    {
        glUseProgram(this->ShaderProgramObject);

        GLint numShaders = 0;

        glGetProgramiv(this->ShaderProgramObject, GL_ATTACHED_SHADERS, &numShaders);
        // This function fills the number of shaders in numShader
		// 1st parameter = Shader Program object
		// 2nd parameter = what info you want
		// 3rd parameter = out parameter

        if(numShaders > 0)
        {
            GLuint * pShader = (GLuint *)malloc(sizeof(GLuint) * numShaders);
            if(pShader != NULL)
            {
                glGetAttachedShaders(this->ShaderProgramObject, numShaders, NULL, pShader);
                // This function stores attached shader objects to a shader program object into array pShader
				// 1st parameter = Shader Program object
				// 2nd parameter = number of shader objects attached
				// 3rd parameter = Actual number of attached shader objects (out parameter)
				// 4th parameter = Out Parameter

                for (GLint i = 0; i < numShaders; i++)
                {
                    glDetachShader(this->ShaderProgramObject, pShader[i]);
                    // Detach those Shader objects from Shader Program object

                    glDeleteShader(pShader[i]);
                    // Delete those Shader Program Object

                    pShader[i] = 0;
                }
            }

            free(pShader);
            pShader = NULL;
        }

        glUseProgram(0);

        glDeleteProgram(this->ShaderProgramObject);
    }
}

GLchar* Terrain::LoadShaderSource(const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (!fp)
    {
        LOG("Failed to open file: %s\n", filename);
        return(NULL);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char* source = (char*)malloc((size + 1) * sizeof(char));
    if (!source)
    {
        fclose(fp);
        return(NULL);
    }

    fread(source, 1, size, fp);
    source[size] = '\0';

    fclose(fp);
    return(source);
}
