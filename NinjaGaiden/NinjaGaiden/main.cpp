/* =============================================================
NINJA GAIDEN
Controls:
Jump: space
Move Right: Right arrow
Move Left: Left arrow
Sit: Down arrow
Attack: S
Sit-Attack: Down arrow + S
Climb up: Up arrow
Climb down: Down arrow
================================================================ */

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Ninja.h"

#define WINDOW_CLASS_NAME L"Ninja"
#define MAIN_WINDOW_TITLE L"Ninja Gaiden"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

#define MAX_FRAME_RATE 100

#define ID_TEX_NINJA 0

CGame *game;
CNinja *ninja;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (!ninja->GetisLatching() && !ninja->GetisJumpWall())
			//if((!ninja->isLatching) &&(!ninja->isJumpWall))
			ninja->SetState(SIMON_STATE_JUMP);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
}

void CSampleKeyHander::KeyState(BYTE *states)
{

#pragma region leo tường
	if (ninja->GetisLatching() && (states[DIK_UP] & 0x80))
		//if ((ninja->isLatching) && (states[DIK_UP] & 0x80))
	{
		ninja->SetState(SIMON_STATE_CLIMB_UP);
		return;
	}
	if (ninja->GetisLatching() && states[DIK_DOWN] & 0x80)
		//if ((ninja->isLatching) && (states[DIK_DOWN] & 0x80))
	{
		ninja->SetState(SIMON_STATE_CLIMB_DOWN);
		return;
	}
#pragma endregion

#pragma region nhảy khỏi tường
	if ((states[DIK_SPACE] & 0x80) && (states[DIK_RIGHT] & 0x80) && (ninja->GetisLatching() && ninja->GetDirection() <= 0))
		//if ((states[DIK_SPACE] & 0x80) && (states[DIK_RIGHT] & 0x80) && (ninja->isLatching)&&(ninja->GetDirection()<=0))
	{
		ninja->SetState(SIMON_STATE_JUMPWALL_RIGHT);
		return;
	}
	if ((states[DIK_SPACE] & 0x80) && (states[DIK_LEFT] & 0x80) && (ninja->GetisLatching()) && (ninja->GetDirection()))
		//if ((states[DIK_SPACE] & 0x80) && (states[DIK_LEFT] & 0x80) && (ninja->isLatching) && (ninja->GetDirection()))
	{
		ninja->SetState(SIMON_STATE_JUMPWALL_LEFT);
		return;
	}
#pragma endregion

#pragma region va chạm tường
	if (((ninja->GetX() == 0) && (ninja->GetDirection() <= 0))
		|| ((ninja->GetX() + 17 >= 305) && (ninja->GetDirection())))
	{
		ninja->SetState(SIMON_STATE_LATCH);
		return;
	}
#pragma endregion
	if (ninja->GetisLatching()) return;
	//if (ninja->isLatching) return;

#pragma region vừa chạy vừa đánh
	if ((states[DIK_S] & 0x80) && (states[DIK_RIGHT] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_RIGHT);
		ninja->SetState(SIMON_STATE_STAND_HIT);
		return;
	}
	if ((states[DIK_S] & 0x80) && (states[DIK_LEFT] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_LEFT);
		ninja->SetState(SIMON_STATE_STAND_HIT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa đánh
	if ((states[DIK_S] & 0x80) && (states[DIK_DOWN] & 0x80))
	{
		ninja->SetState(SIMON_STATE_SIT_HIT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa chạy
	if ((states[DIK_DOWN] & 0x80) && (states[DIK_RIGHT] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_RIGHT);
		return;
	}
	if ((states[DIK_DOWN] & 0x80) && (states[DIK_LEFT] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_LEFT);
		return;
	}
#pragma endregion

#pragma region vừa ngồi vừa đánh
	if ((states[DIK_S] & 0x80) && (states[DIK_DOWN] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_RIGHT);
		ninja->SetState(SIMON_STATE_STAND_HIT);
		return;
	}
	if ((states[DIK_S] & 0x80) && (states[DIK_LEFT] & 0x80))
	{
		ninja->SetState(SIMON_STATE_WALKING_LEFT);
		ninja->SetState(SIMON_STATE_STAND_HIT);
		return;
	}
#pragma endregion
	if ((ninja->GetisHitting() > 0)) return;
	//if ((ninja->isHitting)>0) return;
	if (states[DIK_RIGHT] & 0x80)
		ninja->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (states[DIK_LEFT] & 0x80)
		ninja->SetState(SIMON_STATE_WALKING_LEFT);
	else if (states[DIK_DOWN] & 0x80)
		ninja->SetState(SIMON_STATE_SIT);
	else if (states[DIK_S] & 0x80)
		ninja->SetState(SIMON_STATE_STAND_HIT);
	else ninja->SetState(SIMON_STATE_IDLE);

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
Load all game resources
In this example: load textures, sprites, animations and simon object
*/

void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_NINJA, L"textures\\ninja.png", D3DCOLOR_XRGB(176, 224, 248));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texNinja = textures->Get(ID_TEX_NINJA);

#pragma region create_Sprites_from_texture_for_ninja 
#pragma region idle
	sprites->Add(0, 3, 5, 3 + 17, 5 + 32, texNinja, 0, 0);
#pragma endregion
#pragma region run
	sprites->Add(1, 339, 6, 339 + 20, 6 + 31, texNinja, 0, 0);
	sprites->Add(2, 368, 6, 368 + 22, 6 + 31, texNinja, 0, 0);
	sprites->Add(3, 400, 6, 400 + 20, 6 + 31, texNinja, 0, 0);
#pragma endregion
#pragma region sit
	sprites->Add(4, 3, 52, 3 + 17, 52 + 24, texNinja, 0, 8);
#pragma endregion
#pragma region attack
	sprites->Add(5, 42, 6, 42 + 18, 6 + 31, texNinja, -1, 0);
	sprites->Add(6, 66, 8, 66 + 40, 8 + 29, texNinja, -22, 2);
	sprites->Add(7, 111, 8, 111 + 29, 8 + 29, texNinja, -12, 2);
#pragma endregion
#pragma region sit attack
	sprites->Add(8, 35, 53, 35 + 18, 53 + 23, texNinja, -1, 9);
	sprites->Add(9, 58, 53, 58 + 39, 53 + 23, texNinja, -22, 9);
	sprites->Add(10, 100, 53, 100 + 29, 53 + 23, texNinja, -12, 9);
#pragma endregion
#pragma region jump
	sprites->Add(11, 142, 53, 142 + 16, 53 + 22, texNinja, 0, 0);
	sprites->Add(12, 166, 55, 166 + 22, 55 + 16, texNinja, 0, 0);
	sprites->Add(13, 194, 53, 194 + 16, 53 + 22, texNinja, 0, 0);
	sprites->Add(14, 217, 55, 217 + 22, 55 + 16, texNinja, 0, 0);
#pragma endregion
#pragma region latch+climb
	sprites->Add(15, 267, 6, 267 + 16, 6 + 31, texNinja, 0, 0);
	sprites->Add(16, 289, 6, 289 + 16, 9 + 29, texNinja, 0, 0);
#pragma endregion //bám và leo
#pragma endregion

#pragma region Add sprites to Animations
	LPANIMATION ani;
#pragma region idle
	ani = new CAnimation(100);
	ani->Add(0);
	animations->Add(0, ani);
#pragma endregion
#pragma region run
	ani = new CAnimation(100);
	ani->Add(1);
	ani->Add(2);
	ani->Add(3);
	animations->Add(1, ani);
#pragma endregion
#pragma region sit
	ani = new CAnimation(100);
	ani->Add(4);
	animations->Add(2, ani);
#pragma endregion
#pragma region attack
	ani = new CAnimation(100);
	ani->Add(5);
	ani->Add(6);
	ani->Add(7);
	animations->Add(3, ani);
#pragma endregion
#pragma region sit attack
	ani = new CAnimation(100);
	ani->Add(8);
	ani->Add(9);
	ani->Add(10);
	animations->Add(4, ani);
#pragma endregion
#pragma region jump
	ani = new CAnimation(100);
	ani->Add(11);
	ani->Add(12);
	ani->Add(13);
	ani->Add(14);
	animations->Add(5, ani);
#pragma endregion
#pragma region latch
	ani = new CAnimation(100);
	ani->Add(15);
	animations->Add(6, ani);
#pragma endregion
#pragma region climb
	ani = new CAnimation(100);
	ani->Add(15);
	ani->Add(16);
	animations->Add(7, ani);
#pragma endregion
#pragma endregion

	ninja = new CNinja();
	for (int i = 0; i < 8; i++)
		CNinja::AddAnimation(i);

	ninja->SetPosition(0.0f, 100.0f);
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	ninja->Update(dt);
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		ninja->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
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

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
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
	DWORD tickPerFrame = 100 / MAX_FRAME_RATE;

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}