#include <Crusty.h>


namespace Crusty
{
	namespace Engine
	{

		Assets Common::AssetsManager;
		Common::Common()
		{
		}

#ifdef _DEBUG
		void GLAPIENTRY
			MessageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam)
		{
			if (type == GL_DEBUG_TYPE_ERROR)
				printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
				(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
					type, severity, message);
		}
#endif
		void Common::GetGLError(const GLenum& error)
		{
		}

		void Common::DrawElements(IndexBuffer* indexBuffer)
		{
			glDrawElements(GL_TRIANGLES, indexBuffer->Get_Count(),
				GL_UNSIGNED_INT, &indexBuffer->GetData()->front());
		}

		void Common::DrawElementsInstanced(IndexBuffer* indexBuffer, const int& instanceCount)
		{
			if (indexBuffer == nullptr)
			{
				printf("[E] No or bad Indexbuffer available / passed (NULL)!\n");
				return;
			}

			glDrawElementsInstanced(GL_TRIANGLES, indexBuffer->Get_Count(),
				GL_UNSIGNED_INT, &indexBuffer->GetData()->front(), instanceCount);
		}

		Common::~Common()
			= default;

		LRESULT StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			auto* common = reinterpret_cast<Engine::Common*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			switch (uMsg)
			{
			case WM_CREATE:
				common = static_cast<Engine::Common*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&common));
				common = reinterpret_cast<Engine::Common*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
				break;
			default:;
			}

			return common->WndProc(hWnd, uMsg, wParam, lParam);
		}

		bool Common::Initialize(const bool& fullScreen, const int& verMajor, const int& verMinor)
		{
			this->fullscreen = Settings.Fullscreen;

			this->width = Settings.Width;
			this->height = Settings.Height;

			ZeroMemory(&this->wc, sizeof(WNDCLASSEX));

			this->wc.cbSize = sizeof(WNDCLASSEX);
			this->wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
			this->wc.lpfnWndProc = StaticWndProc;
			this->wc.cbClsExtra = sizeof(Common);
			this->wc.cbWndExtra = sizeof(Common);
			this->wc.hInstance = this->hInstance;
			this->wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			this->wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			this->wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
			this->wc.lpszMenuName = nullptr;
			this->wc.lpszClassName = "MARBLEWINDOW";
			this->wc.hIconSm = this->wc.hIcon;

			if (!RegisterClassEx(&this->wc))
			{
				MessageBox(nullptr, "Failed to register window class", this->appName.c_str(), MB_ICONERROR);
				return false;
			}



			auto x = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
			auto y = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

			if (this->fullscreen)
			{
				this->extendedWindowStyle = WS_EX_APPWINDOW;
				this->WindowStyle = WS_POPUP;
				ShowCursor(FALSE);
			}
			else
			{
				this->extendedWindowStyle = NULL;
				this->WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			}

			this->hwnd = CreateWindowEx(this->extendedWindowStyle, this->wc.lpszClassName, "Crusty",
				this->WindowStyle, 1, 1, this->width, this->height, NULL, NULL, NULL, this);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
			if (!this->hwnd)
			{
				MessageBox(nullptr, "Failed to create the window.", this->appName.c_str(), MB_ICONERROR);
				return false;
			}

			RECT r = { 0 };
			r.top = 0;
			r.left = 0;
			r.bottom = this->height;
			r.right = this->width;

			if (!AdjustWindowRectEx(&r, this->WindowStyle, FALSE, this->extendedWindowStyle))
			{
				MessageBox(nullptr, "Failed to adjust the window.", this->appName.c_str(), MB_ICONERROR);
				return false;
			}

			this->deviceContext = GetDC(this->hwnd);
			if (!this->deviceContext)
			{
				MessageBox(nullptr, "Failed to get GDI context!", this->appName.c_str(), MB_ICONERROR);
				return false;
			}

			{
				PIXELFORMATDESCRIPTOR pfd;
				ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
				pfd.iPixelType = PFD_TYPE_RGBA;
				pfd.cColorBits = 32;
				pfd.cDepthBits = 24;
				pfd.cStencilBits = 8;

				if (!SetPixelFormat(this->deviceContext, ChoosePixelFormat(this->deviceContext, &pfd), &pfd))
				{
					MessageBox(nullptr, "Failed to set PixelFormat", this->appName.c_str(), MB_ICONERROR);
					return false;
				}
			}

			{
				const HGLRC tmpContext = wglCreateContext(this->deviceContext);
				if (!wglMakeCurrent(this->deviceContext, tmpContext))
				{
					MessageBox(nullptr, "Failed to initialize OpenGL", this->appName.c_str(), MB_ICONERROR);
					return false;
				}

				const auto wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
					(wglGetProcAddress("wglCreateContextAttribsARB"));

				if (wglCreateContextAttribsARB == nullptr)
				{
					MessageBox(nullptr, "Failed to initialize OpenGL", this->appName.c_str(), MB_ICONERROR);
					return false;
				}

				{
					const int attribs[] =
					{
						WGL_CONTEXT_MAJOR_VERSION_ARB, verMajor,
						WGL_CONTEXT_MINOR_VERSION_ARB, verMinor,

						WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
					};


					this->renderContext = wglCreateContextAttribsARB(this->deviceContext, nullptr, attribs);
				}

				wglDeleteContext(tmpContext);
			}

			if (!wglMakeCurrent(this->deviceContext, this->renderContext))
			{
				MessageBox(nullptr, "Failed to initialize OpenGL.", this->appName.c_str(), MB_ICONERROR);
				return false;
			}

			glewExperimental = GL_TRUE;
			assert(glewInit() == GLEW_OK);

			if (this->fullscreen)
			{
				memset(&this->dmScreenSettings, 0, sizeof(this->dmScreenSettings));
				this->dmScreenSettings.dmSize = sizeof(this->dmScreenSettings);
				this->dmScreenSettings.dmPelsWidth = this->width; // screen width
				this->dmScreenSettings.dmPelsHeight = this->height; // screen height
				this->dmScreenSettings.dmBitsPerPel = 32; // bits per pixel
				this->dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if (ChangeDisplaySettings(&this->dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					MessageBox(NULL, "Switch to fullscreen failed!", this->appName.c_str(), MB_OK);
					this->fullscreen = false;
				}
			}

			this->rendererInfo.DeviceName = std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
			this->rendererInfo.Vendor = std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
			this->rendererInfo.Version = std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(MessageCallback, 0);
#endif
			const auto error = glGetError();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			float quadVertices[] = {
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f
			};

			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

			glViewport(0, 0, this->width, this->height);


			wglSwapIntervalEXT(1);
			if (!Common::AssetsManager.Bootstrap())
			{
				MessageBox(NULL, "Asset bootstrap failed!", this->appName.c_str(), MB_OK);
				return false;
			}

			Assets::FrameBuffer = std::make_shared<Crusty::Engine::FrameBuffer>(this->width, this->height);
			this->camera = std::make_shared<Camera>(this->width, this->height);

			if (this->On_Initialized != nullptr && error == GL_NO_ERROR)
				if (!this->On_Initialized(width, height, hwnd))
					return false;



			return error == GL_NO_ERROR;
		}

		bool Common::Bootstrap()
		{
			return this->Initialize(false, 4, 3);
		}

		void Common::Update(const float& dt)
		{
			this->camera->Update(dt);

			if (this->On_Update != nullptr)
				this->On_Update(dt);
		}

		void Common::Begin_Render(const float& dt, Camera* camera)
		{
			Assets::FrameBuffer->Bind();
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_STENCIL_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (this->On_BeginRender != nullptr)
				this->On_BeginRender(dt, camera);
		}

		void Common::Render(const float& dt, Camera* camera)
		{
			if (this->On_Render != nullptr)
				this->On_Render(dt, camera);
		}

		void Common::Render_FrameBuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_STENCIL_TEST);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			Assets::Shaders->Load("FrameBuffer");
			glBindVertexArray(quadVAO);

			glBindTexture(GL_TEXTURE_2D, Assets::FrameBuffer->colorBufferId);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			Assets::Shaders->Unload("FrameBuffer");
		}

		void Common::End_Render(const float& dt)
		{
			if (this->On_EndRender != nullptr)
				this->On_EndRender(dt);

			this->Render_FrameBuffer();

		}

		void Common::CalculateFPS(float dt)
		{
			static auto frameCnt = 0;
			static auto elapsed = 0.0f;

			elapsed += dt;
			frameCnt++;

			if (elapsed >= 1.0f)
			{
				fps = static_cast<float>(frameCnt);
				elapsed = 0.0f;
				frameCnt = 0;
			}


		}

		void Common::PerformanceCounter_Init()
		{
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&this->prevTIme));
			QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&this->countsPerSec));
			this->secoundsperCount = 1.0f / static_cast<float>(this->countsPerSec);
		}

		void Common::PerformanceCounter_Start()
		{
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&this->curTIme));
			this->deltaTime = (this->curTIme - this->prevTIme) * this->secoundsperCount;
		}

		void Common::PerformanceCounter_Stop()
		{
			this->CalculateFPS(this->deltaTime);
			this->prevTIme = this->curTIme;
		}

		int Common::Run()
		{
			auto result = ShowWindow(this->hwnd, SW_SHOW);
			this->isRunning = true;

			this->PerformanceCounter_Init();

			MSG msg{};
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					this->PerformanceCounter_Start();

					this->Update(this->deltaTime);

					this->Begin_Render(this->deltaTime, this->Get_Camera());
					this->Render(this->deltaTime, this->Get_Camera());
					this->End_Render(this->deltaTime);

					this->PerformanceCounter_Stop();

					this->SwapBuffer();
				}
			}

			this->Shutdown();

			return static_cast<int>(msg.wParam);
		}

		Camera* Common::Get_Camera()
		{
			return this->camera.get();
		}

		LRESULT Common::WndProc(const HWND& hWnd, const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam)
		{
			const auto common = reinterpret_cast<Common*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			switch (uMsg)
			{
			case WM_CLOSE:
				DestroyWindow(hWnd);
				return 0;
			case WM_DESTROY:
				common->isRunning = false;
				PostQuitMessage(0);
				return 0;
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
				if (wParam == VK_ESCAPE)
				{
					DestroyWindow(hWnd);
					return 0;
				}

				if (common->On_KeyDown != nullptr)
					common->On_KeyDown(static_cast<int>(wParam), common->Get_Camera());
				return 0;
			case WM_SYSKEYUP:
			case WM_KEYUP:
				if (common->On_KeyUp != nullptr)
					common->On_KeyUp(static_cast<int>(wParam), common->Get_Camera());
				return 0;
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
				if (common->On_MouseButtonDown != nullptr)
					common->On_MouseButtonDown(static_cast<int>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
				if (common->On_MouseButtonUp != nullptr)
					common->On_MouseButtonUp(static_cast<int>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			case WM_MOUSEMOVE:
				if (common->On_MouseMove != nullptr)
					common->On_MouseMove(static_cast<int>(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				return 0;
			case WM_SIZE:
				if (!common->isRunning)
					return 0;

				if (wParam != SIZE_MINIMIZED)
					if (LOWORD(lParam) > 10 && HIWORD(lParam) > 10)
						glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));

				return 0;
			default:;
			}

			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		bool Common::Shutdown()
		{
			this->isRunning = false;

			if (this->On_Shutdown != nullptr)
				this->On_Shutdown();

			wglMakeCurrent(this->deviceContext, nullptr);
			wglDeleteContext(this->renderContext);

			if (this->hwnd != nullptr)
				DestroyWindow(this->hwnd);

			DestroyWindow(this->hwnd);
			UnregisterClass(this->wc.lpszClassName, this->hInstance);
			return true;
		}

		bool Common::Get_Running()
		{
			return this->isRunning;
		}

		bool Common::SwapBuffer()
		{
			return SwapBuffers(this->deviceContext);
		}
	}
}


