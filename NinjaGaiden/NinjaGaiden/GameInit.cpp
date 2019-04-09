#include "GameInit.h"

#define WINDOW_CLASS_NAME L"NinjaGaiden"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 540
#define SCREEN_X GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y GetSystemMetrics(SM_CYSCREEN)


//LRESULT  WinProc(HWND hWnd, UINT message, WPARAM wPram, LPARAM lPram) {
//	switch (message) {
//	case WM_QUIT:
//		PostQuitMessage(0);
//		break;
//	default:
//		return WinProc(hWnd, message, wPram, lPram);
//
//	}
//	return 0;
//}
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmtShow, int ScreenWidth, int ScreenHeigh) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(
		WINDOW_CLASS_NAME,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		(SCREEN_X - ScreenWidth) / 2,
		(SCREEN_Y - ScreenHeigh) / 2,
		ScreenWidth,
		ScreenHeigh,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) {
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmtShow);
	UpdateWindow(hWnd);

	return hWnd;

}
void GameInit::CreateGameDevice() {

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = this->hWnd;

	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer); // get backbuffe
}
void run() {
	MSG msg;
	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) break;
		else
		{
			//UPDATE and DRAW our game
		}
	}
}

GameInit::GameInit(HINSTANCE hInstance, int nCmtShow, int ScreenWidth, int ScreenHeigh)
{
	this->hWnd = CreateGameWindow(hInstance, nCmtShow, ScreenWidth, ScreenHeigh); //create window game
	CreateGameDevice(); // create and load 3D lib
	run();
}


GameInit::~GameInit()
{
	if (d3d) d3d->Release();
	if (d3ddv)d3ddv->Release();
	if (backbuffer)backbuffer->Release();
}




