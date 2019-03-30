#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "game.h"

#define WINDOW_CLASS_NAME L"NinjaGaiden"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 540
#define SCREEN_X GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y GetSystemMetrics(SM_CYSCREEN)
void Update(float gameTime);
void Draw(Cgame *gDevice, float gameTime);
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
void run(HWND hWnd) {
	MSG msg;
	Cgame *gDevice = new Cgame();
	gDevice->Init(hWnd);
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
			Update(0.0f);

			Draw(gDevice, 0.0f);
		}
	}
	delete gDevice;

}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpStrCmdLine,int nShowCmd)
{
	HWND hWnd = CreateGameWindow(hInstance, nShowCmd, SCREEN_WIDTH, SCREEN_HEIGHT);
	run(hWnd);
	
	return 0;
}
void Update(float gameTime) {
}
void Draw(Cgame *gDevice, float gameTime) {
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();

	//Draw logic here.

	gDevice->End();
	gDevice->Present();
}