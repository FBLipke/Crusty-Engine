#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		FileSystem::FileSystem()
			= default;

		FileSystem::~FileSystem()
			= default;

		std::string FileSystem::Get_WorkingDirectory()
		{
			char cCurrentPath[260];
			memset(cCurrentPath, 0, sizeof cCurrentPath);

			_getcwd(cCurrentPath, sizeof cCurrentPath);

			auto _path = std::string(cCurrentPath);
			return _path;
		}

		std::string FileSystem::__pathSeperatorChar()
		{
			std::string slash = "/";
			return slash;
		}

		bool FileSystem::__has_endingslash(const std::string& p)
		{
			return p.find_last_of(__pathSeperatorChar(), p.size()) == p.size();
		}

		std::string FileSystem::Combine(const std::string& p1, const std::string& p2)
		{
			std::string _path = p1;

			if (p1.empty())
				return p2;

			if (!__has_endingslash(_path))
				_path = _path + __pathSeperatorChar();

			if (!p2.empty())
				return _path + p2;

			return _path;
		}

		std::string FileSystem::ReadFile(const std::string& path)
		{
			std::string result;
			std::ifstream in(path, std::ios::in | std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				auto size = static_cast<size_t>(in.tellg());
				if (size != -1)
				{
					result.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(&result[0], size);
					in.close();
				}
				else
				{
					printf("Could not read from file '%s'\n", path.c_str());
				}
			}
			else
			{
				printf("Could not open file '%s'\n", path.c_str());
			}

			return result;
		}
	}
}
