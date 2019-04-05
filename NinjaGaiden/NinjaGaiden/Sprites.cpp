#include "Sprites.h"
#include "Game.h"


CSprite::CSprite(int id, int x_sprite, int y_sprite, int width_sprite, int heigh_sprite, LPDIRECT3DTEXTURE9 texture) {
	this->id = id;
	this->x_sprite = x_sprite;
	this->y_sprite = y_sprite;
	this->width_sprite = width_sprite;
	this->heigh_sprite = heigh_sprite;
	this->texture = texture;
}
void CSprite::Draw(float x,float y){
	Cgame *game = Cgame::GetInstance();
	game->Draw(x, y, texture, x_sprite, y_sprite, width_sprite, heigh_sprite);
}
CSprites *CSprites::_Instance = NULL;


/*manage Csprite database*/
CSprites *CSprites::GetInstance() {

	if (_Instance == NULL)_Instance = new CSprites();
	return _Instance;
}

void CSprites::add(int id, int x_sprite, int y_sprite, int width_sprite, int heigh_sprite, LPDIRECT3DTEXTURE9 texture) {
	LPSprite s = new CSprite(id, x_sprite, y_sprite, width_sprite, heigh_sprite, texture);
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

void CAnimation::Render(float x, float y)
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

	frames[currentFrame]->getSprite()->Draw(x, y);
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


