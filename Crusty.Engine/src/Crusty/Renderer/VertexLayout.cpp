#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		VertexLayout::VertexLayout()
		{
			this->Instanced = false;
			this->stride = 0;
		}

		VertexLayout::~VertexLayout()
		{
			this->elements.clear();
		}

		void VertexLayout::Push(unsigned int count, bool instanced, bool normalized, unsigned int type)
		{
			this->Instanced = instanced;
			this->elements.emplace_back(std::make_shared<VertexElement>(type, count, type == GL_FLOAT ? false : normalized));
			this->stride += count * VertexElement::Get_SizeOfType(GL_FLOAT);
		}

		const std::vector<std::shared_ptr<VertexElement>>& VertexLayout::Get_Elements() const
		{
			return this->elements;
		}

		unsigned int VertexLayout::Get_Stride() const
		{
			return this->stride;
		}
		bool VertexLayout::Get_Instanced() const
		{
			return this->Instanced;
		}
	}
}