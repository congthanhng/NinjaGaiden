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
#define BACKGROUND_COLOR D3DCOLOR_XRGB(150,150,150)
#define MAX_FRAME_RATE 100
#define ID_TEXT_NINJA 10

Cgame * game;
CNinja *ninja;

class CSampleKeyHandler : public CKeyEventHandler {

	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHandler * keyHandler;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	OutputDebugString(L"[INFO] KeyDown\n");
	switch (KeyCode) {
	case DIK_X:
		ninja->SetState(NINJA_STATE_JUMP);
		break;
	case DIK_Z:
		if (ninja->GetisSitting())ninja->SetState(NINJA_STATE_SITHIT);
		else ninja->SetState(NINJA_STATE_HIT);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	OutputDebugString(L"[INFO] KeyUp\n");
	switch (KeyCode) {
	case DIK_DOWN:
		ninja->SetisSitting(false);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *state) {
	
	/*if (game->IsKeyDown(DIK_X)) {
		ninja->SetisSitting(false);
		ninja->SetisHitting(false);
		ninja->SetState(NINJA_STATE_JUMP);
		return;
	}*/
	
	if (game->IsKeyDown(DIK_RIGHT)) {
		ninja->SetisSitting(false);
		ninja->SetisHitting(false);
		ninja->SetState(NINJA_STATE_WALKING_RIGHT); 
		return;
	}
	else if (game->IsKeyDown(DIK_LEFT)) { 
		ninja->SetisSitting(false);
		ninja->SetisHitting(false);
		ninja->SetState(NINJA_STATE_WALKING_LEFT); 
		return;
	}
	if (game->IsKeyDown(DIK_DOWN)) {
		if (ninja->GetisJumping()) return;
		ninja->SetisHitting(false);
		ninja->SetState(NINJA_STATE_SIT);
		return;
	}
	
	ninja->SetState(NINJA_STATE_IDLE);
	ninja->SetisSitting(false);
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


#pragma region LoadResource
void LoadResource() {
	
	CTextures *Textures = CTextures::GetInstance();

	Textures->Add(ID_TEXT_NINJA, TEXTURE_NINJA, TRANSPARENT_COLOR); //them vao danh sach cac texture

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texture_Ninja = Textures->get(ID_TEXT_NINJA);


	/*xac dinh cac frame cua texture*/
#pragma region idle
	sprites->add(0, 3, 5, 3+17, 5+32, texture_Ninja,0,0);
#pragma endregion

#pragma region run
	sprites->add(10, 339, 6, 339+20, 6 + 31, texture_Ninja, 0, 0);
	sprites->add(11, 368, 6, 368+22, 6 + 31, texture_Ninja, -2, 0);
	sprites->add(12, 400, 6, 400+20, 6 + 31, texture_Ninja, 0, 0);
#pragma endregion

#pragma region jump
	sprites->add(20, 139, 53, 161, 75, texture_Ninja, 0, 0);
	sprites->add(21, 166, 53, 188, 75, texture_Ninja, 0, 0);
	sprites->add(22, 191, 53, 213, 75, texture_Ninja, 0, 0);
	sprites->add(23, 217, 53, 239, 75, texture_Ninja, 0, 0);
	/*sprites->add(20, 142, 53, 158, 75, texture_Ninja);
	sprites->add(21, 166, 55, 188, 71, texture_Ninja);
	sprites->add(22, 194, 53, 210, 75, texture_Ninja);
	sprites->add(23, 217, 55, 239, 71, texture_Ninja);*/
#pragma endregion

#pragma region sit
	sprites->add(30, 3, 52, 20, 76, texture_Ninja, 0, 0);
#pragma endregion

#pragma region hit
	sprites->add(40, 42, 6, 42 + 18, 31 + 6 , texture_Ninja, -1, 0);
	sprites->add(41, 66, 8, 66 + 40, 8 + 29, texture_Ninja, -23, 0);
	sprites->add(42, 111, 8, 111 + 29 ,8 + 29, texture_Ninja, -12, 0);
#pragma endregion 

#pragma region sithit
	sprites->add(50, 35, 53, 35 + 18, 53+23, texture_Ninja, -1, 0);
	sprites->add(51, 58, 53, 58 + 39, 53+23, texture_Ninja, -22, 0);
	sprites->add(52, 100, 53, 100 + 29, 53 + 23, texture_Ninja, -12, 0);
#pragma endregion
	/*sprites->add(10011, 186, 154, 199, 181, texture_Ninja);
	sprites->add(10012, 155, 154, 170, 181, texture_Ninja);
	sprites->add(10013, 125, 154, 140, 181, texture_Ninja);*/

	/*ninja = new GameObject(TEXTURE_NINJA);
	ninja->SetPosition(10.0f, 130.0f);*/
	//add sprite to animations
	LPANIMATION ani;
#pragma region idle
	ani = new CAnimation(100);
	ani->add(0);
	animations->Add(0, ani);
#pragma endregion

#pragma region run
	ani = new CAnimation(100);
	ani->add(10);
	ani->add(11);
	ani->add(12);
	animations->Add(1, ani);
#pragma endregion

#pragma region jump
	ani = new CAnimation(100);
	ani->add(20);
	ani->add(21);
	ani->add(22);
	ani->add(23);
	animations->Add(2, ani);
#pragma endregion

#pragma region sit
	ani = new CAnimation(100);
	ani->add(30);
	animations->Add(3, ani);
#pragma endregion 

#pragma region hit
	ani = new CAnimation(100);
	ani->add(40);
	ani->add(41);
	ani->add(42);
	animations->Add(4, ani);
#pragma endregion

#pragma region sithit
	ani = new CAnimation(100);
	ani->add(50);
	ani->add(51);
	ani->add(52);
	animations->Add(5, ani);
#pragma endregion
	ninja = new CNinja();
	for (int i = 0; i < 6; i++)
		CNinja::AddAnimation(i);
	/*ninja->AddAnimation(501);*/
	//ninja->AddAnimation(510);


	ninja->SetPosition(10.0f, 250.0f);
}
#pragma endregion

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

			game->ProcessKeyboard();

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

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	LoadResource();
	Run();
	
	return 0;
}
