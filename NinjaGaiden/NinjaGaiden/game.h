#pragma once
#include "Windows.h"
#include "d3d9.h"
#include "d3dx9.h"

class Cgame
{
private:
	static Cgame *_instance;
	HWND hWnd;

	LPDIRECT3D9 d3d=NULL;
	LPDIRECT3DDEVICE9 d3ddv=NULL;

	LPDIRECT3DSURFACE9 backbuffer; //ve hinh anh len backbuffer
	LPD3DXSPRITE spriteHandler;

public:
	void Init(HWND hWnd); //ham tap va thiet lap device va backbuffer
	static Cgame *GetInstance();
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backbuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	/*void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();*/

	/*void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);*/
	Cgame();
	void Release();
	//LPDIRECT3DTEXTURE9 CreateImageFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);
	~Cgame();
};

