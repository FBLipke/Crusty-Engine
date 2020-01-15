#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		IniParser::IniParser()
		{
		}

		IniParser::IniParser(const std::string& filename)
		{
			this->fileName = filename;
		}

		IniParser::~IniParser()
		{
		}

		std::string IniParser::GetValue(const std::string& section, const std::string& key)
		{
			std::stringstream ss;
			char result[1024];
			
			ZeroMemory(&result, sizeof(result));
			
			GetPrivateProfileString(section.c_str(), key.c_str(), nullptr, result, sizeof(result), this->fileName.c_str());

			ss << result;
			return ss.str();
		}

		std::vector<std::string> IniParser::GetValue(const std::string& section, const std::string& key, const std::string& delimeter)
		{
			return Functions::Split(this->GetValue(section,key), delimeter);
		}
	}
}
