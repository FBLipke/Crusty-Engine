#pragma once

#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		Text::Text()
		{
			Common::Shaders->Add("Text");

			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);
			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			this->LoadFonts();
		}

		Text::~Text()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);

			for (auto& character : this->Characters)
				glDeleteTextures(1, &character.second.TextureID);

			this->Characters.clear();
		}

		void Text::Update(const float& dt)
		{
		}

		void Text::Begin_Render(const float& dt, Camera* camera)
		{
			Common::Shaders->Load("Text");
			Common::Shaders->Set_Mat4_On_Active_Shader("uProjection", camera->Get_ProjectionViewMatrix());
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(this->VAO);
		}
		
		void Text::Render(const float& dt, Camera* camera)
		{
		}
		
		void Text::End_Render(const float& dt)
		{
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			Common::Shaders->Unload("Text");
		}

		bool Text::LoadFonts()
		{
			if (FT_Init_FreeType(&this->ft))
			{
				MessageBox(nullptr, "Failed to initialize Freetype", "Simplex - FreeType", MB_ICONERROR);
				return false;
			}

			if (FT_New_Face(this->ft, "Data/Assets/Fonts/arial.ttf", 0, &this->face))
			{
				MessageBox(nullptr, "Failed to load Font", "Simplex - FreeType", MB_ICONERROR);
				return false;
			}

			if (FT_Set_Pixel_Sizes(this->face, 0, 48))
			{
				MessageBox(nullptr, "Failed to set font size", "Simplex - FreeType", MB_ICONERROR);
				return false;
			}

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			this->Characters.clear();
			for (unsigned char c = 0; c < 128; c++)
			{
				if (FT_Load_Char(this->face, c, FT_LOAD_RENDER))
					continue;

				unsigned int texture = 0;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows,
					0, GL_RED, GL_UNSIGNED_BYTE, this->face->glyph->bitmap.buffer);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glGenerateMipmap(GL_TEXTURE_2D);
				Character character = {
					texture,
					glm::ivec2(this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows),
					glm::ivec2(this->face->glyph->bitmap_left, this->face->glyph->bitmap_top),
					this->face->glyph->advance.x
				};

				this->Characters.emplace(c, character);
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			FT_Done_Face(this->face);
			FT_Done_FreeType(this->ft);

			return true;
		}

		void Text::RenderText(const float& dt, Camera* camera, const std::string& text, float x, float y, float scale, const glm::vec3& color)
		{
			this->Begin_Render(dt, camera);
			Common::Shaders->Set_Vec3_On_Active_Shader("uTextColor", color);
			
			for (auto c = text.begin(); c != text.end(); c++)
			{
				auto ch = this->Characters[*c];

				auto xpos = x + ch.Bearing.x * scale;
				auto ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

				auto w = ch.Size.x * scale;
				auto h = ch.Size.y * scale;

				float vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};

				glBindTexture(GL_TEXTURE_2D, ch.TextureID);

				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glDrawArrays(GL_TRIANGLES, 0, 6);

				x += (ch.Advance >> 6) * scale;
			}

			this->End_Render(0.0f);
		}
	}
}
