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
void Cgame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom,int nx)
{
	D3DXVECTOR3 p(x, y, 0);
	D3DXVECTOR3 c((float)((right - left) / 2),(float)( (bottom - top) / 2), 0.0f);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	if (nx<0){

		D3DXMATRIX oldMatrix; //trang thai ban dau
		spriteHandler->GetTransform(&oldMatrix);

		// khai báo ma trận mặc định
		D3DXMATRIX matCombined;
		// khởi tạo ma trận mặc định.
		D3DXMatrixIdentity(&matCombined);

		D3DXMATRIX matScale;
		D3DXMATRIX matTranslate;

		D3DXMatrixScaling(&matScale, -1.0f, 1.0f, .0f);	//lat theo truc ox
		matCombined *= matScale;

		D3DXMatrixTranslation(&matTranslate, x*2 + (right - left), 0, 0.0f); //vì hình ảnh sau scale đang nằm trên -ox lên phải x*2+ width để trở về vị trí x ban đầu khi chưa scale
		matCombined *= matTranslate;

		//D3DXVECTOR3 center((float)(right-left) / 2,(float)(bottom-top) / 2, 0);
		spriteHandler->SetTransform(&matCombined);
		spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 163, 177));

		spriteHandler->SetTransform(&oldMatrix); // trở về trang thái ban đầu
		return;
	}
	else
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 163, 177));
	
}

/*check key duoc nhan chua*/
int Cgame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Cgame::InitKeyboard(LPKEYEVENTHANDLER handler) {
	/*khoi tao direct input*/
	HRESULT hr = DirectInput8Create(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), //lay hinstance cua main
		DIRECTINPUT_VERSION, //luon luon dung parameter nay
		IID_IDirectInput8, // version cuar direct input
		(VOID**)&di, // tra ve gia tri cho input object
		NULL); // ko su dung thong so nay nen luon la null

	if (hr != DI_OK) {
		return;
	}
	
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL); // khoi tao keyboard
	if (hr != DI_OK) return;

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.
	hr = didv->SetDataFormat(&c_dfDIKeyboard);
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); /*DISCL_BACKGROUND : Device có thể đọc bất cứ lúc nào, ngay cả khi ứng dụng game không được active 
																				 DISCL_EXCLUSIVE : Ứng dụng yêu cầu truy cập độc quyền, không có ứng dụng khác được truy cập vào device trong khi nó đang được sử dụng.
																				 Tuy nhiên các ứng dụng nonexclusive khác truy cập vào device vẫn được.
																				 DISCL_FOREGROUND : Game yêu càu device khi mà nó đang active, nếu nó mất focus thì device tạm ngưng hoạt động 
																				 DISCL_NONEXCLUSIVE : Ứng dụng này không cần truy cập độc quyền. flag này nói cho các cờ khác đang hoạt động tiếp tục sử dụng device này 
																				 DISCL_NOWINKEY : Flag này thông báo DirectInput vô hiệu hóa các phím Windows trên bàn phím. */

																				 // IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
																				 //
																				 // DirectInput uses unbuffered I/O (buffer size = 0) by default.
																				 // If you want to read buffered data, you need to set a nonzero
																				 // buffer size.
																				 //
																				 // Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
																				 //
																				 // The buffer size is a DWORD property associated with the device.

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		return;
	}

	this->keyHandler = handler;
}

void Cgame::ProcessKeyboard() {
	HRESULT hr;
	//colect all key state first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr)) {
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keyStates);


	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
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
