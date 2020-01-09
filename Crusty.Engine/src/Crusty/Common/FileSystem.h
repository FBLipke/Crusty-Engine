#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) FileSystem
		{
		public:
			FileSystem();
			virtual ~FileSystem();

			static std::string Combine(const std::string& p1, const std::string& p2);
			static std::string ReadFile(const std::string& path);
			static std::string Get_WorkingDirectory();
		private:

			static std::string __pathSeperatorChar();
			static bool __has_endingslash(const std::string& p);

		};
	}
}
