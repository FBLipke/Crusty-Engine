#pragma once
#include <Crusty.h>

namespace Crusty
{
	namespace Engine
	{
		typedef struct __declspec(dllexport) RendererInfo
		{
			std::string Vendor = "";
			std::string DeviceName = "";
			std::string Version = "";
		} RendererInfo;
		
		class __declspec(dllexport) Common
		{
		public:
			Common();
			static void GetGLError(const GLenum & error);
			static void DrawElements(IndexBuffer * indexBuffer);
			static void DrawElementsInstanced(IndexBuffer* indexBuffer, const int& instanceCount);
			virtual ~Common();

			bool Initialize(const bool& fullScreen, const int& verMajor, const int& verMinor);
			bool Bootstrap();
			int Run();

			Camera* Get_Camera();
			

			std::function<void(const float&)> On_Update;

			std::function<void(const float&, Camera*)> On_BeginRender;
			std::function<void(const float&, Camera*)> On_Render;
			std::function<void(const float&)> On_EndRender;

			std::function<bool(const int&, const int&, const HWND&)> On_Initialized;
			std::function<void()> On_Shutdown;
			
			std::function<void(const int&, Camera*)> On_KeyDown;
			std::function<void(const int&, Camera*)> On_KeyUp;

			std::function<void(const int&, const int&, const int&)> On_MouseButtonDown;
			std::function<void(const int&, const int&, const int&)> On_MouseButtonUp;
			std::function<void(const int&, const int&, const int&)> On_MouseMove;
			LRESULT WndProc(const HWND& hWnd, const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam);

			static Assets AssetsManager;
		private:

			void Update(const float & dt);
			float secoundsperCount;
			float deltaTime;

			void Begin_Render(const float & dt, Camera* camera);
			void Render(const float& dt, Camera* camera);
			void Render_FrameBuffer();
			void End_Render(const float& dt);
			void CalculateFPS(float dt);
			void PerformanceCounter_Init();
			void PerformanceCounter_Start();
			void PerformanceCounter_Stop();
			bool Shutdown();
			bool Get_Running();
			bool fullscreen;

			bool vSync;
			bool SwapBuffer();
			float fps;
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			std::shared_ptr<Camera> camera;
			DEVMODE dmScreenSettings;
			bool isRunning = false;
			int width;
			int height;
			HDC deviceContext;
			ULONG extendedWindowStyle;
			ULONG WindowStyle;
			HGLRC renderContext;
			WNDCLASSEX wc;
			RendererInfo rendererInfo;
			HINSTANCE hInstance;
			HWND hwnd;

			unsigned int quadVAO, quadVBO;
			std::string appName = "Crusty Engine";

			__int64 prevTIme = 0;
			__int64 countsPerSec = 0;
			__int64 curTIme = 0;
		};
	}
}
