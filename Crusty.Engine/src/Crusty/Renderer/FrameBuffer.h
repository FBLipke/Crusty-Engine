#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) FrameBuffer
		{
		public:
			explicit FrameBuffer(const int& width, const int& height);
			virtual ~FrameBuffer();

			virtual void Bind();
			virtual void UnBind();
int width;
			int height;
			unsigned int id{};
			unsigned int colorBufferId{};
			unsigned int RenderBufferId{};
		private:
			
		};
	}
}
