#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) VertexArray
		{
		public:
			explicit VertexArray();
			virtual ~VertexArray();

			void Bind();
			void UnBind();
			VertexLayout* Get_Layout() const;
			void AddBuffer(const VertexLayout & layout);
		private:
			std::shared_ptr<VertexLayout> vl;
			unsigned int id = 0;
			bool isBound = false;
		};
	}
}
