#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		IndexBuffer::IndexBuffer()
		{
			glCreateBuffers(1, &this->id);
		}

		IndexBuffer::~IndexBuffer()
		{
			if (this->id == 0)
				return;

			this->UnBind();
			glDeleteBuffers(1, &this->id);
		}

		void IndexBuffer::SetData(const std::vector<unsigned int>& data)
		{
			this->data = data;
			this->count = static_cast<unsigned int>(this->data.size() * sizeof(unsigned int));

			this->Bind();

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count, &this->data.front(), GL_STATIC_DRAW);
		}

		unsigned int IndexBuffer::Get_Id() const
		{
			return this->id;
		}

		unsigned int IndexBuffer::Get_Count() const
		{
			return this->count;
		}

		void IndexBuffer::Bind()
		{
			if (this->isBound)
				return;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			this->isBound = true;
		}

		void IndexBuffer::UnBind()
		{
			if (!this->isBound)
				return;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			this->isBound = false;
		}

		const std::vector<unsigned int>* IndexBuffer::GetData()
		{
			return &this->data;
		}
	}
}
