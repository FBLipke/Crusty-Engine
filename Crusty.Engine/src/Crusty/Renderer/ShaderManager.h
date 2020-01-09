#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) ShaderManager
		{
		public:
			ShaderManager();
			~ShaderManager();

			bool Contains(const std::string & name);

			void Add(const std::string & name);
			void Remove(const std::string& name);

			void Load(const std::string& id);
			void Unload(const std::string& id);
			void Set_Mat4_On_Active_Shader(const std::string & name, const glm::mat4 & mat);
			void Set_Int_On_Active_Shader(const std::string& name, const int& value);
			void Set_Float_On_Active_Shader(const std::string & name, const float & value);
			void Set_Vec2_On_Active_Shader(const std::string & name, const glm::vec2 & value);
			void Set_Vec3_On_Active_Shader(const std::string & name, const glm::vec3 & value);
			void Set_Vec4_On_Active_Shader(const std::string & name, const glm::vec4 & value);
			Shader* Get_Shader(const std::string & name);

			void Clear();
		private:
			std::map<std::string, std::shared_ptr<Shader>> items;
		};
	}
}
