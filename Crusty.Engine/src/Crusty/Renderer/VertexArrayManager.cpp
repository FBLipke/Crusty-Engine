#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		void VertexArrayManager::Add(const std::string& name)
		{
			this->items.emplace(name, std::make_shared<VertexArray>());
		}

		VertexLayout* VertexArrayManager::Get_Layout(const std::string& name) const
		{
			return this->items.at(name)->Get_Layout();
		}

		bool VertexArrayManager::Contains(const std::string& name)
		{
			return this->items.find(name) != this->items.end();
		}

		void VertexArrayManager::Set_Data(const std::string& name, const VertexLayout& data)
		{
			if (!this->Contains(name))
				this->Add(name);
			
			this->Get_Buffer(name)->AddBuffer(data);
		}

		void VertexArrayManager::Bind(const std::string& name)
		{
			if (this->Contains(name))
				this->Get_Buffer(name)->Bind();
		}

		void VertexArrayManager::UnBind(const std::string& name)
		{
			if (this->Contains(name))
				this->Get_Buffer(name)->UnBind();
		}

		VertexArray* VertexArrayManager::Get_Buffer(const std::string& name)
		{
			if (this->Contains(name))
				return this->items.at(name).get();

			return nullptr;
		}

		void VertexArrayManager::Clear()
		{
			this->items.clear();
		}
	}
}
