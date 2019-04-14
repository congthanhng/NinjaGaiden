﻿#pragma once
#include "Windows.h"
#include "d3d9.h"
#include "d3dx9.h"
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024
/*cac su kien nhan phim, chia lam 3 giai doan*/
class CKeyEventHandler 
{
	virtual void KeyState(BYTE *state) = 0;   //key dang duoc giu
	virtual void OnKeyDown(int keycode) = 0; //sau khi bat dau nhan xuong
	virtual void OnKeyUP(int keycode) = 0; // sau khi tha ra
};
typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class Cgame
{
private:

	static Cgame *_instance;
	HWND hWnd;

	LPDIRECT3D9 d3d=NULL;
	LPDIRECT3DDEVICE9 d3ddv=NULL;

	LPDIRECT3DSURFACE9 backbuffer; //ve hinh anh len backbuffer
	LPD3DXSPRITE spriteHandler;

	/*keyboard*/
	LPDIRECTINPUT8 di; //The DirectInput object 
	LPDIRECTINPUTDEVICE8 didv; // The keyboard device 

	BYTE keyStates[256]; // DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvent[KEYBOARD_BUFFER_SIZE]; //Buffered keyboard data
	LPKEYEVENTHANDLER keyHandler;

public:

	void Init(HWND hWnd); //ham tao va thiet lap device va backbuffer
	static Cgame *GetInstance();
	
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom,int vt);

	void InitKeyboard(LPKEYEVENTHANDLER handler); //thiet lap va khoi tao Input va Keyboard
	int IsKeyDown(int keycode);		//kiem tra neu key dc nhan
	void ProcessKeyboard(); //qua trinh phim

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backbuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	Cgame();

	void Release();
	~Cgame();
};

