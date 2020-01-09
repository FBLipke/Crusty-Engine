#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		TextureManager::TextureManager()
			= default;

		TextureManager::~TextureManager()
		{
			this->items.clear();
		}

		void TextureManager::Add(const std::string & name, const std::string & path, const int& frames)
		{
			if (!Contains(name))
				this->items.emplace(name, std::make_shared<Texture>(name, path, frames));
		}

		bool TextureManager::Contains(const std::string& name)
		{
			return this->items.find(name) != items.end();
		}

		void TextureManager::Remove(const std::string & name)
		{
			if (Contains(name))
				this->items.erase(name);
		}

		void TextureManager::Load(const std::string & name, const unsigned int& slot)
		{
			if (Contains(name))
				this->items.at(name)->Bind(slot);
		}

		Texture* TextureManager::Get_Texture(const std::string & name)
		{
			return this->items.at(name).get();
		}

		void TextureManager::Unload(const std::string & name)
		{
			if (Contains(name))
				this->items.at(name)->Unbind();
		}

		void TextureManager::Clear()
		{
			this->items.clear();
		}
	}
}