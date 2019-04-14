#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

GameObject::GameObject(int nx)
{
	x = y = 0;
	vx = 0.07f;
	nx = 1;
};
void GameObject::Update(DWORD dt) {
	x += vx * dt;
	if (vx > 0 && x > 290) {
		vx = -vx;
		nx = -1;
		return;
	}
	if (vx < 0 && x < 0) {
		vx = -vx;
		nx = 1;
		return;
	}
	/*if ((vx>0 && x > 290) || (x < 0 && vx<0)) vx = -vx;*/
}
void GameObject::Render() {
	LPANIMATION ani=animations[0];
	/*if (vx > 0) {
		ani = animations[0];
	}
	else ani = animations[1];*/
	//ani = animations[0];
	ani->Render(x, y,nx);
}
void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}
GameObject::~GameObject()
{
	
};
