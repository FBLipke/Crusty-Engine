#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class IniParser
		{
		public:
			IniParser();
			IniParser(const std::string& filename);

			~IniParser();

			std::string GetValue(const std::string& section, const std::string& key);
			std::vector<std::string> GetValue(const std::string& section, const std::string& key, const std::string& delimeter);
		private:
			std::string fileName;
		};
	}
}
