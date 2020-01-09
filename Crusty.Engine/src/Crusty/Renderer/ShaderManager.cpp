#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		ShaderManager::ShaderManager()
			= default;

		ShaderManager::~ShaderManager()
		{
			this->items.clear();
		}

		bool ShaderManager::Contains(const std::string& name)
		{
			return this->items.find(name) != this->items.end();
		}

		void ShaderManager::Add(const std::string & name)
		{
			if (this->Contains(name))
				return;

			const auto path = FileSystem::Combine("Data/Assets/Shader", name + ".glsl");

			this->items.emplace(name, std::make_shared<Shader>(name));
			this->Get_Shader(name)->Compile(path);
		}

		void ShaderManager::Remove(const std::string & name)
		{
			if (this->Contains(name))
				this->items.erase(name);
		}

		void ShaderManager::Load(const std::string & id)
		{
			if (!this->Contains(id))
			{
				printf("Shader '%s' not found!\n", id.c_str());
				return;
			}

			if (!this->items.at(id)->IsInUse())
				this->items.at(id)->Use();
		}

		void ShaderManager::Unload(const std::string & id)
		{
			if (this->Contains(id))
				if (this->Get_Shader(id)->IsInUse())
					this->Get_Shader(id)->UnUse();
		}

		void ShaderManager::Set_Mat4_On_Active_Shader(const std::string & name, const glm::mat4 & mat)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setMat4(name, mat);
			}
		}

		void ShaderManager::Set_Int_On_Active_Shader(const std::string & name, const int & value)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setInt(name, value);
			}
		}

		void ShaderManager::Set_Float_On_Active_Shader(const std::string & name, const float & value)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setFloat(name, value);
			}
		}

		void ShaderManager::Set_Vec2_On_Active_Shader(const std::string & name, const glm::vec2 & value)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setVec2(name, value);
			}
		}

		void ShaderManager::Set_Vec3_On_Active_Shader(const std::string & name, const glm::vec3 & value)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setVec3(name, value);
			}
		}

		void ShaderManager::Set_Vec4_On_Active_Shader(const std::string & name, const glm::vec4 & value)
		{
			for (auto& shader : this->items)
			{
				if (!shader.second->IsInUse())
					continue;

				shader.second->setVec4(name, value);
			}
		}

		Shader* ShaderManager::Get_Shader(const std::string & name)
		{
			return this->Contains(name) ? this->items.at(name).get() : nullptr;
		}

		void ShaderManager::Clear()
		{
			this->items.clear();
		}
	}
}
