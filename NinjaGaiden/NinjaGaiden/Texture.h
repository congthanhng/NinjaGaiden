#pragma once
#include <d3dx9.h>

class Texture
{
	LPDIRECT3DTEXTURE9 texture;

	LPD3DXSPRITE spriteHandler;
public:
	Texture(LPCWSTR texturePath);

	~Texture();
};

