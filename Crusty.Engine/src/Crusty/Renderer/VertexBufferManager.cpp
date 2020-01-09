﻿#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		void VertexBufferManager::Add(const std::string& name)
		{
			this->items.emplace(name, std::make_shared<VertexBuffer>());
		}

		void VertexBufferManager::Add(const std::string& name, const std::vector<VertexTexture>& data)
		{
			this->items.emplace(name, std::make_shared<VertexBuffer>());
			this->Get_Buffer(name)->Set_Data(data);
		}

		bool VertexBufferManager::Contains(const std::string& name)
		{
			return this->items.find(name) != items.end();
		}

		void VertexBufferManager::Add(const std::string& name, const std::vector<VertexColor>& data)
		{
			this->items.emplace(name, std::make_shared<VertexBuffer>());
			this->Get_Buffer(name)->Set_Data(data);
		}

		void VertexBufferManager::Set_Data(const std::string& name, const std::vector<VertexTexture>& data)
		{
			if (!Contains(name))
				this->Add(name);

			this->Get_Buffer(name)->Set_Data(data);
		}

		void VertexBufferManager::Set_Data(const std::string& name, const std::vector<VertexColor>& data)
		{
			if (!Contains(name))
				this->Add(name);

			this->Get_Buffer(name)->Set_Data(data);
		}

		void VertexBufferManager::Bind(const std::string& name)
		{
			if (Contains(name))
				this->Get_Buffer(name)->Bind();
		}

		void VertexBufferManager::UnBind(const std::string& name)
		{
			if (Contains(name))
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