#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <direct.h>
#include <sstream>
#include <fstream>
#include <functional>
#include <time.h>
#include <ctime>
#include <cassert>

#define GLEW_STATIC
#include <glew/include/GL/glew.h>
#include <glew/include/GL/wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN
#include <Windows.h>
#include <windowsx.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Common/Functions.h>
#include <Common/Settings.h>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#pragma once
#include <Lua/src/lua.hpp>
#include <Renderer/Vertex.h>
#include <Common/Interpreters/IniParser.h>
#include <Common/Interpreters/LuaInterpreter.h>
#include <Common/Camera.h>

#include <Common/FileSystem.h>
#include <Renderer/FrameBuffer.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>

#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexLayout.h>
#include <Renderer/VertexArray.h>

#include <Renderer/IndexBufferManager.h>
#include <Renderer/ShaderManager.h>
#include <Renderer/TextureManager.h>
#include <Renderer/VertexArrayManager.h>
#include <Renderer/VertexBufferManager.h>


static CrustySettings Settings;

typedef struct __declspec(dllexport) Character {
	unsigned int TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Horizontal offset to advance to next glyph
} Character;

typedef enum __declspec(dllexport) LayerType
{
	UnderLay,
	Ground,
	Collision,
	Overlay,
	Hidden,
	Dummy
} LayerType;

class ICrustyClient
{
public:
	virtual bool Bootstrap() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Begin_Render(const float & dt, Crusty::Engine::Camera* camera) = 0;
	virtual void Render(const float& dt, Crusty::Engine::Camera* camera) = 0;
	virtual void End_Render(const float& dt) = 0;
};
#include <Renderer/Text.h>
#include <Common/Assets.h>
#include <Common/Common.h>

namespace Crusty
{
}
