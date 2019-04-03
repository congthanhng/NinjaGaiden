#include "game.h"


void Cgame::Init(HWND hWnd) {

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true; // fullscreen if false
	
	RECT r;
	GetClientRect(hWnd, &r);// retrieve wwindow wight and hight	

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	d3dpp.BackBufferHeight = r.bottom+1;
	d3dpp.BackBufferWidth = r.right+1;

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3d == NULL) {
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}
	
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
}
//LPDIRECT3DTEXTURE9 Cgame::CreateImageFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath) {
//	HRESULT result;
//
//	//LPDIRECT3DTEXTURE9 _Image;
//	D3DXIMAGE_INFO info;
//	result = D3DXGetImageInfoFromFile(FilePath, &info);
//	result = D3DXCreateTextureFromFileEx(
//		d3ddv,
//		FilePath,
//		info.Width,
//		info.Height,
//		1,
//		D3DUSAGE_DYNAMIC,
//		D3DFMT_UNKNOWN,
//		D3DPOOL_DEFAULT,
//		D3DX_DEFAULT,
//		D3DX_DEFAULT,
//		D3DCOLOR_XRGB(0, 0, 0),
//		&info,
//		NULL,
//		&d3dtexture
//	);
//		if (result != D3D_OK)return;
//	return d3dtexture;
//}
//void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture)
//{
//	D3DXVECTOR3 p(x, y, 0);
//	spriteHandler->Draw(texture, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
//}
//void Cgame::Clear(D3DCOLOR color) {
//	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
//}
//void Cgame::Begin()
//{
//	d3ddv->BeginScene();
//}
//
//void Cgame::End()
//{
//	d3ddv->EndScene();
//}
//
//void Cgame::Present()
//{
//	//Present our scene to the window.
//	d3ddv->Present(NULL, NULL, NULL, NULL);
//}
Cgame::Cgame()
{
}
void Cgame::Release() {
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

Cgame::~Cgame()
{
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();

}
