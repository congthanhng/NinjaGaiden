#include "Sprites.h"
#include "Game.h"
#include <chrono>

int CSprite::currentSpriteSizeW = 0;
CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float xx, float yy)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->xx = xx;
	this->yy = yy;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int nx, int xx, int yy)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, nx, xx, yy, currentSpriteSizeW);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, float xx, float yy)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, xx, yy);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int &hit, int nx)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;

			if ((hit == 1) && (frames.size() == currentFrame))
			{
				currentFrame = 0; //đã thực hiện xong chuỗi frame attack
				hit = 0; //hết attack
				return;
			}

			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
	float xx = 0;
	float yy = frames[currentFrame]->GetSprite()->getYY();
	if (nx <= 0)
	{
		xx = frames[currentFrame]->GetSprite()->getXX();
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, nx, xx, yy);

}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}