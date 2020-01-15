#include <Crusty.h>
#include <stb_image/stb_image.h>

namespace Crusty
{
	namespace Engine
	{
		void Texture::UnpackTexture()
		{
			glTexStorage3D(this->textureTarget, this->lveles, GL_RGBA8, this->width, this->height, this->depth);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, this->width);

			for (auto y = 0; y < this->FrameCountY; ++y)
				for (auto x = 0; x < this->FrameCountX; ++x)
				{
					const auto xOffset = x * this->FrameCountX;
					const auto yOffset = y * this->FrameCountY;
					const auto zOffset = y * this->FrameCountX + x;

					glPixelStorei(GL_UNPACK_SKIP_PIXELS, xOffset);
					glPixelStorei(GL_UNPACK_SKIP_ROWS, yOffset);

					glTexSubImage3D(this->textureTarget, this->lveles,
						0, 0, zOffset, this->FrameCountX, this->FrameCountY, 1,
						GL_RGBA, GL_UNSIGNED_BYTE, this->localbuffer);
				}

			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		}

		Texture::Texture(const std::string& name, const std::string & path, const int& frames, const bool& flip)
		{
			this->_name = name;
			this->path = path;
			this->textureTarget = GL_TEXTURE_2D;

			stbi_set_flip_vertically_on_load(flip);
			this->localbuffer = stbi_load(this->path.c_str(), &this->width, &this->height, &this->bpp, 4);
			if (frames > 1)
			{

				this->FrameCountX = this->width / (this->width / frames);
				this->FrameCountY = this->height / (this->height / frames);
			}
			else
			{

				//this->textureTarget = GL_TEXTURE_2D;
				this->FrameCountX = 1;
				this->FrameCountY = 1;
			}

			glGenTextures(1, &this->id);

			this->Bind(0);

			glTexImage2D(this->textureTarget, 0, GL_RGBA8, this->width, this->height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, this->localbuffer);

			glTexParameteri(this->textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(this->textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(this->textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			float fLargest;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
			glTexParameterf(this->textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT,
				fLargest <= Settings.AnistrophFilter ? fLargest : Settings.AnistrophFilter);

			if (Settings.Mipmap)
				glGenerateMipmap(this->textureTarget);

			if (this->localbuffer != nullptr)
				stbi_image_free(this->localbuffer);

			this->localbuffer = nullptr;

			glBindTexture(this->textureTarget, 0);
		}

		Texture::~Texture()
		{
			glDeleteTextures(this->textureTarget, &this->id);
		}

		unsigned int Texture::Get_Id() const
		{
			return this->id;
		}

		void Texture::Bind(const unsigned int& slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(this->textureTarget, this->id);
			this->isActive = true;
		}

		void Texture::Unbind()
		{
			glBindTexture(this->textureTarget, 0);
			this->isActive = false;
		}

		int Texture::Get_Width() const
		{
			return this->width;
		}

		int Texture::Get_Height() const
		{
			return this->height;
		}

		int Texture::Get_FrameCount_Y()
		{
			return this->FrameCountY;
		}

		int Texture::Get_FrameCount_X()
		{
			return this->FrameCountX;
		}
	}
}