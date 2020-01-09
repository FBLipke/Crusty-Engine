#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		VertexArray::VertexArray()
		{
			glCreateVertexArrays(1, &this->id);
		}

		VertexArray::~VertexArray()
		{
			this->UnBind();
			glDeleteVertexArrays(1, &this->id);
		}

		void VertexArray::Bind()
		{
			if (this->isBound)
				return;

			glBindVertexArray(this->id);
			this->isBound = true;
		}

		void VertexArray::UnBind()
		{
			if (!this->isBound)
				return;

			glBindVertexArray(0);
			this->isBound = false;
		}

		VertexLayout * VertexArray::Get_Layout() const
		{
			return this->vl.get();
		}

		void VertexArray::AddBuffer(const VertexLayout & layout)
		{
			this->Bind();
			this->vl = std::make_shared<VertexLayout>(layout);

			auto offset = 0U;
			auto elements = this->vl->Get_Elements();

			for (auto i = 0U; i < elements.size(); i++)
			{
				glEnableVertexAttribArray(i);
				switch (elements[i]->Type)
				{
				case GL_FLOAT:
				case GL_HALF_FLOAT:
				case GL_DOUBLE:
				case GL_FIXED:
					elements[i]->Normalized = false;
					break;
				}

				glVertexAttribPointer(i, elements[i]->Count, elements[i]->Type,
					elements[i]->Normalized ? GL_TRUE : GL_FALSE, this->vl->Get_Stride(),
						reinterpret_cast<const void*>(offset));

				offset += elements[i]->Count * elements[i]->Get_SizeOfType(elements[i]->Type);
			}

			this->UnBind();
		}
	}
}
