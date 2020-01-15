#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) VertexArrayManager
		{
		public:
			void Add(const std::string& name);
			VertexLayout* Get_Layout(const std::string& name);
			bool Contains(const std::string & name);
			void Set_Data(const std::string& name, const VertexLayout& data);
			void Bind(const std::string& name);
			void UnBind(const std::string& name);
			VertexArray* Get_Buffer(const std::string& name);
			void Clear();
		private:
			std::map<std::string, std::shared_ptr<VertexArray>> items;
		};

	}
}