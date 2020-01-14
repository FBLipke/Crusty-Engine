#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		void IndexBufferManager::Add(const std::string& name)
		{
			this->items.emplace(name, std::make_shared<IndexBuffer>());
		}

		bool IndexBufferManager::Contains(const std::string& name)
		{
			return this->items.find(name) != this->items.end();
		}

		void IndexBufferManager::Set_Data(const std::string& name, const std::vector<unsigned int>& data)
		{
			if (!this->Contains(name))
				this->Add(name);

			this->items.at(name)->SetData(data);
		}

		void IndexBufferManager::Bind(const std::string& name)
		{
			if (this->Contains(name))
				this->items.at(name)->Bind();
		}

		unsigned int IndexBufferManager::Get_Count(const std::string& name)
		{
			return this->items.at(name)->Get_Count();
		}

		void IndexBufferManager::UnBind(const std::string& name)
		{
			if (this->Contains(name))
				this->items.at(name)->UnBind();
		}

		void IndexBufferManager::Clear()
		{
			this->items.clear();
		}

		IndexBuffer* IndexBufferManager::Get_Buffer(const std::string& name)
		{
			return this->Contains(name) ? this->items.at(name).get() : nullptr;
		}
	}
}
