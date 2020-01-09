#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) VertexBufferManager
		{
		public:
			void Add(const std::string& name);
			void Add(const std::string & name, const std::vector<VertexColor>& data);
			void Add(const std::string & name, const std::vector<VertexTexture>& data);

			bool Contains(const std::string& name);

			void Set_Data(const std::string& name, const std::vector<VertexTexture>& data);
			void Set_Data(const std::string& name, const std::vector<VertexColor>& data);

			void Bind(const std::string& name);
			void UnBind(const std::string& name);
			VertexBuffer* Get_Buffer(const std::string& name);
			void Clear();
		private:
			std::map<std::string, std::shared_ptr<VertexBuffer>> items;
		};

	}
}
