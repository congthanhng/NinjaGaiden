#include "Sprites.h"
#include "Game.h"


CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture,int xx,int yy) {
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;
	this->xx = xx;
	this->yy = yy;
}
void CSprite::Draw(float x,float y,int nx){
	Cgame *game = Cgame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom,nx,xx,yy);
}
CSprites *CSprites::_Instance = NULL;


/*manage Csprite database*/
CSprites *CSprites::GetInstance() {

	if (_Instance == NULL)_Instance = new CSprites();
	return _Instance;
}

void CSprites::add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture,int xx,int yy) {
	LPSprite s = new CSprite(id, left, top, right, bottom, texture,xx,yy);
	sprites[id] = s;
}
LPSprite CSprites::get(int id) {
	return sprites[id];
}

void CAnimation::add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSprite sprite = CSprites::GetInstance()->get(spriteId);
	LPAnimetion_Fame frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y,int nx)
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
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->getSprite()->Draw(x, y,nx);
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


