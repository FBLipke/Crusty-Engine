#include <Crusty.h>

namespace Crusty
{
	std::vector<std::string> Functions::Split(const std::string& str, const std::string& token)
	{
		std::string tmp = str;
		std::vector<std::string> result;

		while (tmp.size())
		{
			auto index = tmp.find(token);
			if (index != std::string::npos)
			{
				result.push_back(tmp.substr(0, index));
				tmp = tmp.substr(index + token.size());

				if (tmp.size() == 0)
					result.push_back(tmp);
			}
			else
			{
				result.push_back(tmp);
				tmp = "";
			}
		}

		return result;
	}
}
