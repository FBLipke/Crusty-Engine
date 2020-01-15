#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) Assets : public ICrustyClient
		{
		public:
			Assets();
			~Assets();

			static std::shared_ptr<ShaderManager> Shaders;
			static std::shared_ptr<VertexArrayManager> VertexArrays;
			static std::shared_ptr<VertexBufferManager> VertexBuffers;
			static std::shared_ptr<IndexBufferManager> IndexBuffers;
			static std::shared_ptr<FrameBuffer> FrameBuffer;
			static std::shared_ptr<Text> TextRenderer;
			static std::shared_ptr<TextureManager> Textures;

			void Load_Indices(const std::string& name, const std::vector<std::string>& order);

			void Load_Layout(const std::string& name, const std::vector<std::string>& order);

			virtual bool Bootstrap() override;
			virtual void Update(const float& dt) override;
			virtual void Begin_Render(const float& dt, Crusty::Engine::Camera* camera) override;
			virtual void Render(const float& dt, Crusty::Engine::Camera* camera) override;
			virtual void End_Render(const float& dt) override;
			void Load_Textures();
			void Load_Shaders();
		private:


			

		};
	}
}
