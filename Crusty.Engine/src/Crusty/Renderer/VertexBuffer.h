#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) VertexBuffer
		{
		public:
			VertexBuffer();
			virtual ~VertexBuffer();

			void Set_Data(const std::vector<VertexTexture>& data);
			void Set_Data(const std::vector<VertexColor>& data);

			void Bind();
			void UnBind();

		private:
			bool isBound = false;
			unsigned int id = 0;

			std::vector<VertexColor> dataC;
			std::vector<VertexTexture> dataT;
		};

	}
}
