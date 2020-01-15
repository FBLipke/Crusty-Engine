#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		void VertexBufferManager::Add(const std::string& name)
		{
			if (!this->Contains(name))
				this->items.emplace(name, std::make_shared<VertexBuffer>());
		}

		void VertexBufferManager::Add(const std::string& name, const std::vector<VertexTexture>& data)
		{
			this->Set_Data(name, data);
		}

		bool VertexBufferManager::Contains(const std::string& name)
		{
			return this->items.find(name) != this->items.end();
		}

		void VertexBufferManager::Add(const std::string& name, const std::vector<VertexColor>& data)
		{
			this->Set_Data(name, data);
		}

		void VertexBufferManager::Set_Data(const std::string& name, const std::vector<VertexTexture>& data)
		{
			this->Add(name);
			this->Get_Buffer(name)->Set_Data(data);
		}

		void VertexBufferManager::Set_Data(const std::string& name, const std::vector<VertexColor>& data)
		{
			this->Add(name);
			this->Get_Buffer(name)->Set_Data(data);
		}

		void VertexBufferManager::Bind(const std::string& name)
		{
			if (this->Contains(name))
				this->Get_Buffer(name)->Bind();
		}

		void VertexBufferManager::UnBind(const std::string& name)
		{
			if (this->Contains(name))
				this->Get_Buffer(name)->UnBind();
		}

		VertexBuffer* VertexBufferManager::Get_Buffer(const std::string& name)
		{
			return this->items.at(name).get();
		}

		void VertexBufferManager::Clear()
		{
			this->items.clear();
		}
	}
}
