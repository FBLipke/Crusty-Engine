#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) Text : public ICrustyClient
		{
		public:
			Text();
			~Text();

			virtual void Update(const float& dt) override;
			virtual void Begin_Render(const float& dt, Camera* camera) override;
			virtual void Render(const float& dt, Camera* camera) override;
			virtual void End_Render(const float& dt) override;
			bool LoadFonts();
			void RenderText(const float& dt, Crusty::Engine::Camera* camera,
				const std::string& text, float x, float y, float scale,
					const glm::vec3& color);
		private:
			unsigned int VAO, VBO;
			std::map<char, Character> Characters;
			FT_Library ft;
			FT_Face face;

			// Geerbt über ICrustyClient
			virtual bool Bootstrap() override;
		};
	}
}
