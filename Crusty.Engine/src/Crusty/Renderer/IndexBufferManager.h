#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) IndexBufferManager
		{
		public:
			void Add(const std::string& name);
			bool Contains(const std::string& name);
			void Set_Data(const std::string& name, const std::vector<unsigned int>& data);
			void Bind(const std::string& name);
			void UnBind(const std::string& name);
			IndexBuffer* Get_Buffer(const std::string& name);
			unsigned int Get_Count(const std::string& name);
			void Clear();

		private:
			std::map<std::string, std::shared_ptr<IndexBuffer>> items;
		};

	}
}
