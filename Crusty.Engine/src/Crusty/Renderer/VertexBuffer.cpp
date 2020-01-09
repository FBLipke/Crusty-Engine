#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		VertexBuffer::VertexBuffer()
		{
			glCreateBuffers(1, &this->id);
		}

		VertexBuffer::~VertexBuffer()
		{
			this->UnBind();

			glDeleteBuffers(1, &this->id);
		}

		void VertexBuffer::Set_Data(const std::vector<VertexColor>& data)
		{
			this->dataC = data;
			this->Bind();

			glBufferData(GL_ARRAY_BUFFER, sizeof(this->dataC) * this->dataC.size(), &this->dataC.front(), GL_STATIC_DRAW);
		}

		void VertexBuffer::Set_Data(const std::vector<VertexTexture>& data)
		{
			this->dataT = data;
			this->Bind();

			glBufferData(GL_ARRAY_BUFFER, sizeof(this->dataT) * this->dataT.size(), &this->dataT.front(), GL_STATIC_DRAW);
		}

		void VertexBuffer::Bind()
		{
			if (this->isBound)
				return;

			glBindBuffer(GL_ARRAY_BUFFER, this->id);
			this->isBound = true;
		}

		void VertexBuffer::UnBind()
		{
			if (!this->isBound)
				return;

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			this->isBound = false;
		}
	}
}
