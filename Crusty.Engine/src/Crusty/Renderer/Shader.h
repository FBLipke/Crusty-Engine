#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) Shader
		{
		public:
			Shader(const std::string& name);
			virtual ~Shader();

			void Get_UniformsFromShader(const std::string& shaderSrc);

			void Compile(const std::string& filePath);
			std::unordered_map<GLenum, std::string> PreProcess(const std::string & source);

			virtual void Use();
			virtual void UnUse();

			virtual bool IsInUse() const;

			virtual unsigned int& Get_Id();
			const unsigned int & Get_UniformLocation(const std::string & name);
			bool Has_Uniform(const std::string& name);

			void setBool(const std::string & name, bool value);
			void setInt(const std::string & name, int value);
			void setFloat(const std::string & name, const float& value);
			void setVec2(const std::string & name, const glm::vec2 & value);
			void setVec2(const std::string & name, const float& x, const float& y);
			void setVec3(const std::string & name, const glm::vec3 & value);
			void setVec3(const std::string & name, const float& x, const float& y, const float& z);
			void setVec4(const std::string & name, const glm::vec4 & value);
			void setVec4(const std::string & name, const float& x, const float& y, const float& z, const float& w);
			void setMat2(const std::string & name, const glm::mat2 & mat);
			void setMat3(const std::string & name, const glm::mat3 & mat);
			void setMat4(const std::string & name, const glm::mat4 & mat);

		private:
			std::unordered_map<std::string, unsigned int> uniformLocations;
			unsigned int id;
			bool inUse = false;
			std::string name;
		};
	}
}
