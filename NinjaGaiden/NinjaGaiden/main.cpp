#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "game.h"
#include "GameObject.h"

#define WINDOW_CLASS_NAME L"NinjaGaiden"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 540

#define SCREEN_X GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y GetSystemMetrics(SM_CYSCREEN)

#define TEXTURE_NINJA L"frame.png"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 0, 0)
#define MAX_FRAME_RATE 10

Cgame * game;
GameObject *ninja;



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
void Update(DWORD dt) {
	ninja->Update(dt);
}
void Render() {

	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backbuffer = game->GetBackBuffer();
	LPD3DXSPRITE spritehandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(backbuffer, NULL, BACKGROUND_COLOR);
		spritehandler->Begin(D3DXSPRITE_ALPHABLEND);

		ninja->Render();

		spritehandler->End();
		d3ddv->EndScene();
	}
	d3ddv->Present(NULL, NULL, NULL, NULL);
}
void LoadResource() {
	ninja = new GameObject(TEXTURE_NINJA);
	ninja->SetPosition(10.0f, 130.0f);
}
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight) {
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
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		(SCREEN_X - SCREEN_WIDTH)/2,
		(SCREEN_Y - SCREEN_HEIGHT)/2,
		ScreenWidth,
		ScreenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}
int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpStrCmdLine,int nShowCmd)
{
	HWND hWnd = CreateGameWindow(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = Cgame::GetInstance();
	game->Init(hWnd);
	LoadResource();
	Run();
	
	return 0;
}
//void Update(float gameTime) {
//}
//void Draw(Cgame *gDevice, float gameTime) {
//	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
//	gDevice->Begin();
//
//	//Draw logic here.
//
//	gDevice->End();
//	gDevice->Present();
//}