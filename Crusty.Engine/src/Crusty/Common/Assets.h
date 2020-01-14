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

			virtual bool Bootstrap() override;
			virtual void Update(const float& dt) override;
			virtual void Begin_Render(const float& dt, Crusty::Engine::Camera* camera) override;
			virtual void Render(const float& dt, Crusty::Engine::Camera* camera) override;
			virtual void End_Render(const float& dt) override;
		private:


			

		};
	}
}
