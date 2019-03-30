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


public:
	void Init(HWND hWnd);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();
	Cgame();
	~Cgame();
};

