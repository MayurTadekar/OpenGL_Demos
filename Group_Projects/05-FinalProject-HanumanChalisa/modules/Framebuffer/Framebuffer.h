#pragma once 

// structs
typedef struct Framebuffer
{
	GLuint FramebufferObject;
	GLuint depthRenderbufferObject;
	GLuint depthTexture;
	GLuint *attachedTextureArray;
	int numAttachedTextures;
}Framebuffer;

// function declarations
Framebuffer *createFramebuffer(void);
GLuint createFramebufferTextureAndAttached(Framebuffer *pFramebuffer, GLenum attachment, GLint width, GLint height);
GLuint createFramebufferDepthTextureAndAttached(Framebuffer *pFramebuffer, GLint width, GLint height);
GLuint createFramebufferDepthRenderbuffer(Framebuffer *pFramebuffer, GLint width, GLint height);
void bindFramebuffer(Framebuffer *pFramebuffer, GLint width, GLint height);
void unbindFramebuffer(void);
void destroyFramebuffer(Framebuffer *pFramebuffer);
