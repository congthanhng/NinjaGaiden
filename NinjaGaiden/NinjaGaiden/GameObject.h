#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
using namespace std;

class GameObject
{
	float x;
	float y;

	//vector di chuyen
	float vx;
	float vy;

	int nx; //huong di chuyen, trai or phai ( phai = 1, trai = -1) neu -1 thi lat hinh nguoc lai

	int state; // trang thai hien tai
	 
	static vector<LPANIMATION> animations;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; } //set vi tri nhan vat
	void setSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }

	void SetState(int state) { this->state = state; } // thiet lap trang thai nhan vat
	int GetState() { return this->state; }

	static void AddAnimation(int aniId); //

	GameObject(int nx);

	void Update(DWORD dt);
	void Render();
	~GameObject();
};
