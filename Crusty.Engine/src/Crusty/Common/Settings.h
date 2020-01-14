#pragma once

typedef struct __declspec(dllexport) CrustySettings
{
public:
	int AnistrophFilter = 16;
	bool Fullscreen = false;
	int Width = 1280;
	int Height = 729;
	bool Mipmap = true;

} CrustySettings;
