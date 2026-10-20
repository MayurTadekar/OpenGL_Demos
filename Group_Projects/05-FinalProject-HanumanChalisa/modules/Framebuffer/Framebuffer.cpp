// header files
#include"../include/common.h"
#include"./Framebuffer.h"

// function declarations
Framebuffer *createFramebuffer(void)
{
	// local variable 
	Framebuffer *pFramebuffer = NULL;

	// code 
	pFramebuffer = (Framebuffer *)malloc(sizeof(Framebuffer));

	ZeroMemory((void *)pFramebuffer, sizeof(Framebuffer));

	glGenFramebuffers(1, &pFramebuffer->FramebufferObject);

	return(pFramebuffer);
}

GLuint createFramebufferTextureAndAttached(Framebuffer *pFramebuffer, GLenum attachment, GLint width, GLint height)
{
	// local variables
	GLuint texture = 0;
	
	//code
	glGenTextures(1, &texture);

	//add the created texture to the textures array
	(pFramebuffer->numAttachedTextures)++;

	pFramebuffer->attachedTextureArray = (GLuint *)realloc(pFramebuffer->attachedTextureArray, sizeof(GLuint) * pFramebuffer->numAttachedTextures);
	pFramebuffer->attachedTextureArray[pFramebuffer->numAttachedTextures - 1] = texture;

	glBindFramebuffer(GL_FRAMEBUFFER, pFramebuffer->FramebufferObject);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG("createFramebufferTextureAndAttached(): Framebuffer status is incomplete\n");
		exit(EXIT_FAILURE);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return(texture);
}

GLuint createFramebufferDepthTextureAndAttached(Framebuffer *pFramebuffer, GLint width, GLint height)
{
	//code
	glGenTextures(1, &pFramebuffer->depthTexture);

	glBindFramebuffer(GL_FRAMEBUFFER, pFramebuffer->FramebufferObject);

	glBindTexture(GL_TEXTURE_2D, pFramebuffer->depthTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pFramebuffer->depthTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG("createFramebufferDepthTextureAndAttached(): Framebuffer status is incomplete\n");
		exit(EXIT_FAILURE);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return(pFramebuffer->depthTexture);
}

GLuint createFramebufferDepthRenderbuffer(Framebuffer *pFramebuffer, GLint width, GLint height)
{
	// local variables
	GLint maxRenderbufferSize = 0;

	//code
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE,&maxRenderbufferSize);

	if (maxRenderbufferSize < width || maxRenderbufferSize < height)
	{
		return(0);
	}

	glGenRenderbuffers(1, &pFramebuffer->depthRenderbufferObject);

	glBindFramebuffer(GL_FRAMEBUFFER, pFramebuffer->FramebufferObject);

	glBindRenderbuffer(GL_RENDERBUFFER, pFramebuffer->depthRenderbufferObject);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pFramebuffer->depthRenderbufferObject);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG("createFramebufferDepthRenderbuffer(): Framebuffer status is incomplete\n");
		exit(EXIT_FAILURE);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return(pFramebuffer->depthTexture);
}

void bindFramebuffer(Framebuffer *pFramebuffer, GLint width, GLint height)
{
	// code
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, pFramebuffer->FramebufferObject);
	glViewport(0, 0, width, height);
}

void unbindFramebuffer(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void destroyFramebuffer(Framebuffer *pFramebuffer)
{
	//  code
	if (pFramebuffer)
	{
		if (pFramebuffer->attachedTextureArray)
		{
			glDeleteTextures(pFramebuffer->numAttachedTextures, pFramebuffer->attachedTextureArray);
			free(pFramebuffer->attachedTextureArray);
			pFramebuffer->attachedTextureArray = NULL;
		}

		if (pFramebuffer->depthTexture)
		{
			glDeleteTextures(1, &pFramebuffer->depthTexture);
			pFramebuffer->depthTexture = 0;
		}

		if (pFramebuffer->depthRenderbufferObject)
		{
			glDeleteRenderbuffers(1, &pFramebuffer->depthRenderbufferObject);
			pFramebuffer->depthRenderbufferObject = 0;
		}

		if (pFramebuffer->FramebufferObject)
		{
			glDeleteFramebuffers(1, &pFramebuffer->FramebufferObject);
			pFramebuffer->FramebufferObject = 0;
		}

		if (pFramebuffer)
		{
			free(pFramebuffer);
		}
	}
}
