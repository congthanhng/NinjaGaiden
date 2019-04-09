#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class GameInit
{
	HWND hWnd; 

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;

	LPDIRECT3DSURFACE9 backbuffer;
public:
	GameInit(HINSTANCE hInstance, int nCmtShow, int ScreenWidth, int ScreenHeigh); 
	void CreateGameDevice();
	~GameInit();
};

