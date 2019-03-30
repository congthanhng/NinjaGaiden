#include "game.h"


void Cgame::Init(HWND hWnd) {
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true; // fullscreen if false
	/*d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;*/

	/*d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;*/

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	
}
void Cgame::Clear(D3DCOLOR color) {
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}
void Cgame::Begin()
{
	d3ddv->BeginScene();
}

void Cgame::End()
{
	d3ddv->EndScene();
}

void Cgame::Present()
{
	//Present our scene to the window.
	d3ddv->Present(NULL, NULL, NULL, NULL);
}
Cgame::Cgame()
{
}


Cgame::~Cgame()
{
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();

}
