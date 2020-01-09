#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) IndexBuffer
		{
		public:
			IndexBuffer();
			virtual ~IndexBuffer();

			void SetData(const std::vector<unsigned int>& data);
			unsigned int Get_Id() const;
			unsigned int Get_Count() const;
			void Bind();
			void UnBind();

			const std::vector<unsigned int>* GetData();
		private:
			bool isBound = false;
			unsigned int id = 0;
			unsigned int count = 0;
			std::vector<unsigned int> data;
		};
	}
}
