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
	float vx;
	int currentState;
	int nx;
	vector<LPANIMATION> animations;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetState(int state) { this->currentState = state; }
	void AddAnimation(int aniId);

	GameObject(int nx);

	void Update(DWORD dt);
	void Render();
	~GameObject();
};
