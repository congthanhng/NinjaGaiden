#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class GameInit
{
	HWND hWnd;

public:
	GameInit(HINSTANCE hInstance, int nCmtShow, int ScreenWidth, int ScreenHeigh);
	
	~GameInit();
};

