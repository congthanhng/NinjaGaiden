#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
using namespace std;

class CSprite{
	int id;
	int x_sprite;
	int y_sprite;
	int width_sprite;
	int heigh_sprite;

	LPDIRECT3DTEXTURE9 texture;

public:
	CSprite(int id,int x_sprite, int y_sprite, int width_sprite, int heigh_sprite,LPDIRECT3DTEXTURE9 texture);
	void Draw(float x, float y);

};
typedef CSprite* LPSprite;

/*manage sprite database*/
class CSprites
{
	static CSprites * _Instance;
	unordered_map<int, LPSprite> sprites;

public:

	void add(int id, int x_sprite, int y_sprite, int width_sprite, int heigh_sprite, LPDIRECT3DTEXTURE9 texture);
	LPSprite get(int id);

	static CSprites * GetInstance();
	
};

