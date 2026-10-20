/***************************************************************************
 * S.G.M.P - Frame Buffer Object
 * @file: FrameBufferObjectWithDepth.h
 * @brief: Modular framebuffer object management
 * @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 * @copyright ©2020-2025 MarshallingVoid
 * @date: February 2026
 ***************************************************************************/

#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "./../../../include/vmath.h"
#include <vector>
#include "../common/macros.h"
#include "../common/common.h"

class FrameBufferObjectWithDepth
{
private:
	GLuint fbo;
	std::vector<GLuint> textureAttachments;
	// GLuint depthRBO;	 //	Depth renderbuffer attachment
	GLuint depthTexture; //	Depth renderbuffer attachment
	int width;
	int height;
	GLenum colorFormat; // GL_RGBA16F, GL_RGBA, etc.
	GLenum depthFormat; // GL_DEPTH_COMPONENT32F, etc.
	bool initialized;

	void CreateTextureAttachments()
	{

		for (size_t i = 0; i < textureAttachments.size(); ++i)
		{
			GLuint colorAttachment = 0;
			glGenTextures(1, &colorAttachment);
			textureAttachments[i] = colorAttachment;
			glBindTexture(GL_TEXTURE_2D, textureAttachments[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureAttachments[i], 0);
		}
	}

	void CreateDepthTexture()
	{
		glGenTextures(1, &depthTexture);

		glBindTexture(GL_TEXTURE_2D, depthTexture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT,
			width,
			height,
			0,
			GL_DEPTH_COMPONENT,
			GL_FLOAT,
			NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D,
			depthTexture,
			0);
	}

	void CreateDepthRenderBuffer()
	{
		// glGenRenderbuffers(1, &depthRBO);
		// glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
		// glRenderbufferStorage(GL_RENDERBUFFER, depthFormat, width, height);
		// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
	}

	void ValidateFramebuffer()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ENTRY("log.txt", "ERROR: FrameBufferObjectWithDepth not complete!");
		}
	}

public:
	// Constructor
	FrameBufferObjectWithDepth(int w, int h, GLenum colFormat = GL_RGBA32F, GLenum depFormat = GL_DEPTH_COMPONENT32F, int numAttachments = 1)
		: fbo(0), // depthRBO(0),
		  width(w), height(h),
		  colorFormat(colFormat), depthFormat(depFormat),
		  initialized(false)
	{
		LOG_ENTRY_WITH_PARAM("log.txt", "Number of Color Attachments: %d", numAttachments);
		textureAttachments.clear();
		textureAttachments.resize(numAttachments, 0);
	}

	// Destructor
	~FrameBufferObjectWithDepth()
	{
		Uninitialize();
	}

	// Initialize the framebuffer
	void Initialize()
	{
		if (initialized)
			return;

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		CreateTextureAttachments();
		// CreateDepthRenderBuffer();
		CreateDepthTexture();

		// Set up draw buffers based on number of attachments
		std::vector<GLenum> attachments;
		for (size_t i = 0; i < textureAttachments.size(); ++i)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(attachments.size(), attachments.data());

		ValidateFramebuffer();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		initialized = true;

		LOG_ENTRY("log.txt", "FrameBufferObjectWithDepth initialized");
	}

	// Bind framebuffer for rendering
	void Bind() const
	{
		if (initialized)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glViewport(0, 0, width, height);
		}
	}

	// Unbind framebuffer
	void Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Bind color texture for sampling
	void BindColorTexture(GLuint textureUnit = 0, GLuint attachmentIndex = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, textureAttachments[attachmentIndex]);
	}

	void BindDepthTexture(GLuint textureUnit = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
	}

	void UnBindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Uninitialize and cleanup
	void Uninitialize()
	{
		if (!initialized)
			return;

		for (size_t i = 0; i < textureAttachments.size(); ++i)
		{
			if (textureAttachments[i] != 0)
			{
				glDeleteTextures(1, &textureAttachments[i]);
				textureAttachments[i] = 0;
			}
		}

		// if (depthRBO != 0)
		// {
		// 	glDeleteRenderbuffers(1, &depthRBO);
		// 	depthRBO = 0;
		// }

		if (fbo != 0)
		{
			glDeleteFramebuffers(1, &fbo);
			fbo = 0;
		}

		initialized = false;

		LOG_ENTRY("log.txt", "FrameBufferObjectWithDepth uninitialized");
	}

	// Getters
	GLuint GetFBO() const { return fbo; }
	GLuint GetTexture(GLuint attachmentIndex = 0) const { return textureAttachments[attachmentIndex]; }
	// GLuint GetDepthRBO() const { return depthRBO; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	bool IsInitialized() const { return initialized; }

	// Resize framebuffer
	void Resize(int newWidth, int newHeight)
	{
		if (newWidth == width && newHeight == height)
			return;

		width = newWidth;
		height = newHeight;

		Uninitialize();
		Initialize();
	}

	// Clear framebuffer
	void Clear(GLfloat r = 0.2f, GLfloat g = 0.2f, GLfloat b = 0.2f, GLfloat a = 0.0f)
	{
		Bind();
		glClearColor(r, g, b, a);
		glClear(GL_DEPTH_BUFFER_BIT);
		Unbind();
	}
};
