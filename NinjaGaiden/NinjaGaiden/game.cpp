#include "game.h"

Cgame  *Cgame::_instance = NULL;

/*khoi tao device de ve len do*/
void Cgame::Init(HWND hWnd) {

	/*dinh danh cho device*/

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

	/*khoi tao device*/
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

	/* */
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	/*khoi tao ve sprite*/
	D3DXCreateSprite(d3ddv, &spriteHandler);

}
//void Cgame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) {
//	D3DXVECTOR3 p(x, y, 0);
//	spriteHandler->Draw(texture, NULL, NULL, &p, D3DCOLOR_XRGB(255, 163, 177));
//	
//}
void Cgame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom,int vx)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	if (vx<0){

		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);

		// khai báo ma trận mặc định
		D3DXMATRIX matCombined;
		// khởi tạo ma trận mặc định.
		D3DXMatrixIdentity(&matCombined);

		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;

		D3DXMatrixScaling(&matScale, -1.0f, 1.0f, .0f);
		matCombined *= matScale;
		D3DXMatrixTranslation(&matTranslate, x * 2 + (right - left), 0, 0.0f);
		matCombined *= matTranslate;

		//D3DXVECTOR3 center((float)(right-left) / 2,(float)(bottom-top) / 2, 0);
		spriteHandler->SetTransform(&matCombined);
		spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));

		spriteHandler->SetTransform(&oldMatrix);
		return;
	}
	else
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 163, 177));
	
}

Cgame::Cgame()
{
}
void Cgame::Release() {
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}
Cgame *Cgame::GetInstance() {
	if (_instance == NULL) _instance = new Cgame();
	return _instance;
}

Cgame::~Cgame()
{
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backbuffer != NULL)backbuffer->Release();

}
