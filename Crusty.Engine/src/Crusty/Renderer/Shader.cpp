#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		Shader::Shader(const std::string& name)
		{
			this->name = name;
		}

		Shader::~Shader()
		{
			this->Shader::UnUse();
			glDeleteProgram(this->id);
		}

		static unsigned int ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;

			if (type == "geometry")
				return GL_GEOMETRY_SHADER;

			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			return 0;
		}

		std::unordered_map<unsigned int, std::string> Shader::PreProcess(const std::string& source)
		{
			std::unordered_map<unsigned int, std::string> shaderSources;

			const char* typeToken = "#type";
			auto typeTokenLength = strlen(typeToken);
			auto pos = source.find(typeToken, 0);

			while (pos != std::string::npos)
			{
				auto eol = source.find_first_of("\r\n", pos);
				if (eol == std::string::npos)
				{
					MessageBox(nullptr, "Syntax Error", "Shader-Compilation", MB_ICONERROR);
					shaderSources.clear();
					return shaderSources;
				}

				auto begin = pos + typeTokenLength + 1;
				auto type = source.substr(begin, eol - begin);

				if (ShaderTypeFromString(type) == 0)
				{
					MessageBox(nullptr, "Invalid shader type specified", "Shader-Compilation", MB_ICONERROR);
					shaderSources.clear();
					return shaderSources;
				}

				auto nextLinePos = source.find_first_not_of("\r\n", eol);

				if (eol == std::string::npos)
				{
					MessageBox(nullptr, "Syntax Error", "Shader-Compilation", MB_ICONERROR);
					shaderSources.clear();
					return shaderSources;
				}

				pos = source.find(typeToken, nextLinePos);

				shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ?
					source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
			}

			return shaderSources;
		}

		void Shader::Get_UniformsFromShader(const std::string& shaderSrc)
		{
			std::stringstream src;
			src << shaderSrc;

			while (!src.eof())
			{
				std::string line = "";
				std::getline(src, line, '\n');

				if (line.empty())
					continue;

				const auto start = line.find_first_of("uniform");
				const auto end = line.find_first_of(";");

				if (start != std::string::npos && end != std::string::npos)
				{
					auto uniformLine = line.substr(start, end);
					line = line.substr(end);
					printf("Out: %s\n", uniformLine.c_str());
				}
				else
					line = "";
			}
		}

		void Shader::Compile(const std::string& filePath)
		{
			auto shaderSources = PreProcess(FileSystem::ReadFile(filePath));

			if (shaderSources.size() == 0)
			{
				MessageBox(nullptr, "No input data", "Shader-Compilation", MB_ICONERROR);
				return;
			}

			auto program = glCreateProgram();
			std::vector<unsigned int> glShaderIDs;

			for (auto& kv : shaderSources)
			{
				auto shader = glCreateShader(kv.first);
				const auto* sourceStr = kv.second.c_str();
				
				const char* uniformToken = "uniform";
				auto typeTokenLength = strlen(uniformToken);
				auto pos = kv.second.find(uniformToken, 0);
				unsigned int location = 0;

				while (pos != std::string::npos)
				{
					auto eol = kv.second.find_first_of("\r\n", pos);
					if (eol == std::string::npos)
						MessageBox(nullptr, "Syntax Error", "Simplex - Shader - Compilation", MB_ICONERROR);

					auto begin = pos + typeTokenLength + 1;
					auto uniform = kv.second.substr(begin, eol - begin);

					if (uniform.size() != 0)
					{
						auto uniformStart = uniform.find_last_of(" ") + 1;
						auto entry = uniform.substr(uniformStart, (uniform.size() - uniformStart) - 1);

						printf("Added Uniform: %s (Location: %ld)\n", entry.c_str(), location);
						uniformLocations.emplace(entry, location);
						location++;
					}

					auto nextLinePos = kv.second.find_first_not_of("\r\n", eol);

					if (eol == std::string::npos)
						MessageBox(nullptr, "Syntax Error", "Simplex - Shader - Compilation", MB_ICONERROR);

					pos = kv.second.find(uniformToken, nextLinePos);
				}
				
				glShaderSource(shader, 1, &sourceStr, 0);
				glCompileShader(shader);

				auto isCompiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

				if (isCompiled == GL_FALSE)
				{
					auto maxLength = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

					std::vector<char> infoLog(maxLength);
					glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
					glDeleteShader(shader);

					std::stringstream ss;
					ss << infoLog.data();
					MessageBox(nullptr, ss.str().c_str(), "Simplex - Shader - Compilation", MB_ICONERROR);
					ss.clear();
					return;
				}

				glAttachShader(program, shader);
				glShaderIDs.emplace_back(shader);
			}

			this->id = program;

			glLinkProgram(program);
			glValidateProgram(program);

			auto isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
			if (isLinked == GL_FALSE)
			{
				auto maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<char> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
				glDeleteProgram(program);

				for (auto id : glShaderIDs)
					glDeleteShader(id);

				std::stringstream ss;
				ss << infoLog.data();
				MessageBox(nullptr, ss.str().c_str(), "Simplex - Shader - Compilation", MB_ICONERROR);
				ss.clear();
				return;
			}

			for (auto id : glShaderIDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}
		}

		void Shader::Use()
		{
			if (this->inUse)
				return;

			glUseProgram(this->id);
			this->inUse = true;
		}

		void Shader::UnUse()
		{
			if (!this->inUse)
				return;

			glUseProgram(0);

			this->inUse = false;
		}

		bool Shader::IsInUse() const
		{
			return this->inUse;
		}

		unsigned int& Shader::Get_Id()
		{
			return this->id;
		}

		const unsigned int& Shader::Get_UniformLocation(const std::string& name)
		{
			if (!this->Has_Uniform(name))
				this->uniformLocations[name] = glGetUniformLocation(this->Get_Id(), name.c_str());

			return this->uniformLocations[name];
		}

		bool Shader::Has_Uniform(const std::string & name)
		{
			return this->uniformLocations.find(name) != this->uniformLocations.end();
		}

		void Shader::setBool(const std::string & name, bool value)
		{
			this->setInt(name, value);
		}

		void Shader::setInt(const std::string & name, int value)
		{
			glUniform1i(this->Get_UniformLocation(name), value);
		}

		void Shader::setFloat(const std::string & name, const float& value)
		{
			glUniform1f(this->Get_UniformLocation(name), value);
		}

		void Shader::setVec2(const std::string & name, const glm::vec2 & value)
		{
			glUniform2fv(this->Get_UniformLocation(name), 1, &value[0]);
		}

		void Shader::setVec2(const std::string & name, const float& x, const float& y)
		{
			glUniform2f(this->Get_UniformLocation(name), x, y);
		}

		void Shader::setVec3(const std::string & name, const glm::vec3 & value)
		{
			glUniform3fv(this->Get_UniformLocation(name), 1, &value[0]);
		}

		void Shader::setVec3(const std::string & name, const float& x, const float& y, const float& z)
		{
			glUniform3f(this->Get_UniformLocation(name), x, y, z);
		}

		void Shader::setVec4(const std::string & name, const glm::vec4 & value)
		{
			glUniform4fv(this->Get_UniformLocation(name), 1, &value[0]);
		}

		void Shader::setVec4(const std::string & name, const float& x, const float& y, const float& z, const float& w)
		{
			glUniform4f(this->Get_UniformLocation(name), x, y, z, w);
		}

		void Shader::setMat2(const std::string & name, const glm::mat2 & mat)
		{
			glUniformMatrix2fv(this->Get_UniformLocation(name), 1, GL_FALSE, value_ptr(mat));
		}

		void Shader::setMat3(const std::string & name, const glm::mat3 & mat)
		{
			glUniformMatrix3fv(this->Get_UniformLocation(name), 1, GL_FALSE, value_ptr(mat));
		}

		void Shader::setMat4(const std::string & name, const glm::mat4 & mat)
		{
			glUniformMatrix4fv(this->Get_UniformLocation(name), 1, GL_FALSE, value_ptr(mat));
		}
	}
}