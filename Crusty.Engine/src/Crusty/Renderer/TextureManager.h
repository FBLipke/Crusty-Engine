#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) TextureManager
		{
		public:
			TextureManager();
			virtual ~TextureManager();

			void Add(const std::string & name, const std::string & path, const int& frames, const bool& flip = false);
			bool Contains(const std::string& name);
			void Remove(const std::string& name);

			void Load(const std::string& name, const unsigned int& slot);
			Texture* Get_Texture(const std::string & name);
			void Unload(const std::string& name);

			void Clear();
		private:
			std::map<std::string, std::shared_ptr<Texture>> items;


		};
	}
}
