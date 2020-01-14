#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		typedef struct __declspec(dllexport) VertexElement
		{
			unsigned int Count;
			unsigned int Type;
			bool Normalized;

			VertexElement(unsigned int type, unsigned int count, bool normalized)
			{
				this->Type = type;
				this->Count = count;
				this->Normalized = normalized;
			}

			static unsigned int Get_SizeOfType(unsigned int type)
			{
				switch (type)
				{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
				case GL_UNSIGNED_INT: return 4;
				case GL_BYTE: return 1;
				default: return 0;
				}
			}
		} VertexElement;

		class __declspec(dllexport) VertexLayout
		{
		public:
			VertexLayout();
			~VertexLayout();

			void Push(unsigned int count, bool instanced = false, bool normalized = false, unsigned int type = GL_FLOAT);
			const std::vector<std::shared_ptr<VertexElement>>& Get_Elements() const;
			unsigned int Get_Stride() const;
			bool Get_Instanced() const;

		private:
			std::vector<std::shared_ptr<VertexElement>> elements;
			unsigned int stride;
			bool Instanced;
		};
	}
}
