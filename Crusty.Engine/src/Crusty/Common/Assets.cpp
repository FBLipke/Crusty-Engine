#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		std::shared_ptr<ShaderManager> Assets::Shaders;
		std::shared_ptr<VertexArrayManager> Assets::VertexArrays;
		std::shared_ptr<VertexBufferManager> Assets::VertexBuffers;
		std::shared_ptr<IndexBufferManager> Assets::IndexBuffers;
		std::shared_ptr<Crusty::Engine::FrameBuffer> Assets::FrameBuffer;
		std::shared_ptr<Text> Assets::TextRenderer;
		std::shared_ptr<TextureManager> Assets::Textures;

		Assets::Assets()
		{
			this->VertexArrays = std::make_shared<VertexArrayManager>();
			this->VertexBuffers = std::make_shared<VertexBufferManager>();
			this->IndexBuffers = std::make_shared <IndexBufferManager>();
			//this->TextRenderer = std::make_shared<Text>();
		}

		Assets::~Assets()
		{
		}

		void Assets::Update(const float& dt)
		{
		}

		void Assets::Begin_Render(const float& dt, Crusty::Engine::Camera* camera)
		{
		}

		void Assets::Render(const float& dt, Crusty::Engine::Camera* camera)
		{
		}

		void Assets::End_Render(const float& dt)
		{
		}

		void Assets::Load_Textures()
		{
			this->Textures = std::make_shared<TextureManager>();

			IniParser textureini("Data/Assets/Texture/Textures.ini");
			auto textureCount = atoi(textureini.GetValue("Info", "Count").c_str());

			for (auto i = 0; i < textureCount; i++)
			{
				std::stringstream ss;
				ss << "Texture" << i;

				auto name = textureini.GetValue(ss.str(), "Name");
				auto frames = atoi(textureini.GetValue(ss.str(), "Frames").c_str());

				auto filename = Crusty::Engine::FileSystem::Combine(
					"Data/Assets/Texture", textureini.GetValue(ss.str(),
						"File"));

				auto flip = static_cast<bool>(atoi(textureini.GetValue(ss.str(), "Flip").c_str()));
				ss.clear();

				printf("[I] Adding Texture '%s'..\n", name.c_str());
				this->Textures->Add(name, filename, frames, flip);

			}
		}

		void Assets::Load_Shaders()
		{
			this->Shaders = std::make_shared<ShaderManager>();

			IniParser shadersini("Data/Assets/Shader/Shaders.ini");
			auto shaderCount = atoi(shadersini.GetValue("Info", "Count").c_str());

			for (auto i = 0; i < shaderCount; i++)
			{
				std::stringstream ss;
				ss << "Shader" << i;


				auto name = shadersini.GetValue(ss.str(), "Name");
				auto filename = Crusty::Engine::FileSystem::Combine(
					"Data/Assets/Shader/", shadersini.GetValue(ss.str(),
						"File"));

				ss.clear();

				printf("[I] Adding Shader '%s'..\n", name.c_str());
				this->Shaders->Add(name, filename);
			}
		}


		void Assets::Load_Indices(const std::string& name, const std::vector<std::string>& order)
		{
			if (order.size() != 0)
			{
				std::vector<unsigned int> indices;

				for (const auto& index : order)
					indices.emplace_back(static_cast<unsigned int>(atoi(index.c_str())));

				Crusty::Engine::Assets::IndexBuffers->Set_Data(name, indices);
			}
		}

		void Assets::Load_Layout(const std::string& name, const std::vector<std::string>& order)
		{
			if (order.size() != 0)
			{
				Crusty::Engine::VertexLayout vl;
				for (const auto& item : order)
					vl.Push(atoi(item.c_str()));

				Crusty::Engine::Assets::VertexArrays->Set_Data(name, vl);
			}
		}

		bool Assets::Bootstrap()
		{
			this->Load_Shaders();

			this->Load_Textures();

			{
				IniParser meshini("Data/Assets/Mesh/Meshes.ini");
				auto meshCount = atoi(meshini.GetValue("Info", "Count").c_str());

				for (auto im = 0; im < meshCount; im++)
				{
					std::stringstream ss;
					ss << "Mesh" << im;

					auto name = meshini.GetValue(ss.str(), "Name");
					if (static_cast<bool>(atoi(meshini.GetValue(ss.str(), "Indexed").c_str())))
					{
						auto order = meshini.GetValue(ss.str(), "Order", ",");
						if (order.size() == 0)
							return false;

						Load_Indices(name, order);
					}

					auto vertexLayout = meshini.GetValue(ss.str(), "VertexLayout", ";");
					if (vertexLayout.size() == 0)
						return false;

					
					auto vertexCount = atoi(meshini.GetValue(ss.str(), "VertexCount").c_str());
					
					if (vertexCount != 0)
					{
						std::vector<VertexTexture> vertices;
						for (auto iv = 0; iv < vertexCount; iv++)
						{
							std::stringstream ssvl;
							glm::vec3 pos;
							glm::vec2 tex;
							glm::vec3 col;

							ssvl << "Vertex" << iv;
							auto vertexes = meshini.GetValue(ss.str(), ssvl.str(), ";");
							if (vertexes.size() == 0)
								continue;

							auto vlIndex = 0;
							for (auto& ve : vertexes)
							{
								auto layoutEntry = Functions::Split(ve, ",");
								if (layoutEntry.size() == atoi(vertexLayout.at(vlIndex).c_str()))
								{
									printf("[D] Entry Size: %lld\n", layoutEntry.size());

									if (vlIndex == 0)
										pos = glm::vec3(atof(layoutEntry.at(0).c_str()), atof(layoutEntry.at(1).c_str()), atof(layoutEntry.at(2).c_str()));

									if (vlIndex == 1)
										tex = glm::vec2(atof(layoutEntry.at(0).c_str()), atof(layoutEntry.at(1).c_str()));

									if (vlIndex == 2)
										col = glm::vec3(atof(layoutEntry.at(0).c_str()), atof(layoutEntry.at(1).c_str()), atof(layoutEntry.at(2).c_str()));
								}

								vlIndex++;
							}

							printf("Pos: X: %0.1f Y: %0.1f Z: %0.1f\n", pos.x, pos.y, pos.z);
							printf("Tex: X: %0.1f Y: %0.1f\n", tex.x, tex.y);
							printf("Col: R: %0.1f G: %0.1f B: %0.1f\n", col.x, col.y, col.z);

							vertices.emplace_back(pos, tex, col);
						}

						if (vertices.size() != 0)
						{
							printf("[D] Defined %lld vertices for %s\n", vertices.size(), name.c_str());
							Crusty::Engine::Assets::VertexBuffers->Set_Data(name, vertices);
						}
					}
					else
						return false;

					ss.clear();

					printf("[I] Adding Mesh '%s'..\n", name.c_str());

					Load_Layout(name, vertexLayout);
				}
			}



			return true;
		}
	}
}
