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

	static GameInit *_Instance;
public:
	GameInit(); 
	
	HWND CreateGameWindow(HINSTANCE hInstance, int nCmtShow, int ScreenWidth, int ScreenHeigh);
	void CreateGameDevice(HWND hWnd);

	LPDIRECT3DDEVICE9 GetDirectxDevice();
	static GameInit *GetInstance();
	~GameInit();
};

