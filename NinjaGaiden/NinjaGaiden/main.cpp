#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#include "game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Ninja.h"

#define WINDOW_CLASS_NAME L"NinjaGaiden"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 540

#define SCREEN_X GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y GetSystemMetrics(SM_CYSCREEN)

#define TEXTURE_NINJA L"RyuHayabusa.png"
#define TRANSPARENT_COLOR D3DCOLOR_XRGB(255, 163, 177)
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255,0,0)
#define MAX_FRAME_RATE 60
#define ID_TEXT_NINJA 10

Cgame * game;
GameObject *ninja;

class CSampleKeyHandler : public CKeyEventHandler {
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHandler * keyHandler;

void CSampleKeyHandler::OnKeyDown(int keycode) {
	switch (keycode) {
	case DIK_SPACE:
		ninja->SetState(NINJA_STATE_JUMP);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int keycode) {
	
}

void CSampleKeyHandler::KeyState(BYTE *state) {
	if (game->IsKeyDown(DIK_RIGHT))ninja->SetState(NINJA_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))ninja->SetState(NINJA_STATE_WALKING_LEFT);
	else ninja->SetState(NINJA_STATE_IDLE);
}


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

#pragma region LoadResource
void LoadResource() {
	
	CTextures *Textures = CTextures::GetInstance();

	Textures->Add(ID_TEXT_NINJA, TEXTURE_NINJA, TRANSPARENT_COLOR); //them vao danh sach cac texture

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texture_Ninja = Textures->get(ID_TEXT_NINJA);

	/*xac dinh cac frame cua texture*/
#pragma region run
	sprites->add(10001, 339, 6, 359, 37, texture_Ninja);
	sprites->add(10002, 368, 6, 390, 37, texture_Ninja);
	sprites->add(10003, 400, 6, 420, 37, texture_Ninja);
#pragma endregion

	/*sprites->add(10011, 186, 154, 199, 181, texture_Ninja);
	sprites->add(10012, 155, 154, 170, 181, texture_Ninja);
	sprites->add(10013, 125, 154, 140, 181, texture_Ninja);*/

	/*ninja = new GameObject(TEXTURE_NINJA);
	ninja->SetPosition(10.0f, 130.0f);*/
	//add sprite to animations
	LPANIMATION ani;
#pragma region run
	ani = new CAnimation(100);
	ani->add(10001);
	ani->add(10002);
	ani->add(10003);
	animations->Add(500, ani);
#pragma endregion

	ani = new CAnimation(100);
	ani->add(10011);
	ani->add(10012);
	ani->add(10013);
	animations->Add(501, ani);

	ninja = new GameObject(0.07f);
	ninja->AddAnimation(500);
	/*ninja->AddAnimation(501);*/
	//ninja->AddAnimation(510);


	ninja->SetPosition(10.0f, 250.0f);
}
#pragma endregion

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

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight) {
	/* dinh danh cho man hinh*/
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

	/*dang ki cua so*/
	RegisterClassEx(&wc);

	/*Khoi tao cua so*/
	HWND hWnd = CreateWindow(
		WINDOW_CLASS_NAME,	// ten cua so
		MAIN_WINDOW_TITLE,	// ten hien thi
		WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		(SCREEN_X - SCREEN_WIDTH)/2,	//toa do x de cua so nam giua man hinh
		(SCREEN_Y - SCREEN_HEIGHT)/2,	// toa do y de cua so nam giua man hinh
		ScreenWidth,	
		ScreenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	/*kiem tra va ve cua so len*/
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

/*vong lap game*/
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
	game = Cgame::GetInstance(); //mot singleton pattern de dam bao chi co mot game duy nhat
	game->Init(hWnd);
	LoadResource();
	Run();
	
	return 0;
}
