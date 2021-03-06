#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		FrameBuffer::FrameBuffer(const int& width, const int& height)
		{
			this->width = width;
			this->height = height;

			glGenFramebuffers(1, &this->id);
			this->FrameBuffer::Bind();
			glGenTextures(1, &this->colorBufferId);
			glBindTexture(GL_TEXTURE_2D, this->colorBufferId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			float fLargest = 0;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest <= Settings.AnistrophFilter
				? fLargest : Settings.AnistrophFilter);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorBufferId, 0);

			glGenRenderbuffers(1, &this->RenderBufferId);
			glBindRenderbuffer(GL_RENDERBUFFER, this->RenderBufferId);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->width, this->height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RenderBufferId);

			assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

			this->FrameBuffer::UnBind();
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteRenderbuffers(1, &this->RenderBufferId);
			glDeleteFramebuffers(1, &this->id);
		}

		void FrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, this->id);
			//glBindRenderbuffer(GL_RENDERBUFFER, this->RenderBufferId);
		}

		void FrameBuffer::UnBind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	}
}
