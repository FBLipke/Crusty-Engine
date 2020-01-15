#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) Texture
		{
		public:
			void UnpackTexture();
			explicit Texture(const std::string& name, const std::string & path, const int& frames = 1, const bool& flip = false);
			~Texture();

			auto Get_Id() const -> unsigned int;

			void Bind(const unsigned int& slot);

			void Unbind();

			int Get_Width() const;
			int Get_Height() const;

			int Get_FrameCount_Y();
			int Get_FrameCount_X();
		private:
			glm::mat4 trans = glm::mat4(1.0f);
			std::string path;
			std::string _name;
			unsigned int id{};
			int width{};
			int height{};
			int bpp{};

			unsigned int textureTarget;

			int lveles = 1;
			int depth;

			bool isActive;
			int FrameCountY;
			int FrameCountX;
			unsigned char* localbuffer = nullptr;
		};
	}
}
