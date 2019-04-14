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
	float vx; //vector di chuyen
	int currentState; // trang thai hien tai
	int nx; //huong di chuyen, trai or phai ( phai = 1, trai = -1) neu -1 thi lat hinh nguoc lai
	vector<LPANIMATION> animations;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; } //set vi tri nhan vat
	void SetState(int state) { this->currentState = state; } // thiet lap trang thai nhan vat
	void AddAnimation(int aniId); //

	GameObject(int nx);

	void Update(DWORD dt);
	void Render();
	~GameObject();
};
