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


