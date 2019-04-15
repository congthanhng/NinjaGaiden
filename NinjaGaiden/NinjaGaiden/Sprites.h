#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <vector>
using namespace std;

class CSprite{
	int id;

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;

public:
	CSprite(int id,int left, int top, int right, int bottom,LPDIRECT3DTEXTURE9 texture);
	void Draw(float x, float y,int nx);

};
typedef CSprite* LPSprite;

/*manage sprite database*/
class CSprites
{
	static CSprites * _Instance;
	unordered_map<int, LPSprite> sprites;

public:

	void add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	LPSprite get(int id);

	static CSprites * GetInstance();
	
};
/*sprite animation*/
class CAnimationFrame {
	LPSprite sprite;
	DWORD time;

public:

	CAnimationFrame(LPSprite sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSprite getSprite() { return sprite; }
};
typedef CAnimationFrame* LPAnimetion_Fame;

class CAnimation {
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPAnimetion_Fame> frames;

public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void add(int spriteId, DWORD time = 0);
	void Render(float x, float y,int nx);
};
typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};