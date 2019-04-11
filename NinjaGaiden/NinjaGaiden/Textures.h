#pragma once
#include <unordered_map>
#include <d3dx9.h>
using namespace std;

class CTextures
{
	static CTextures *_Instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();

	void Add(int id, LPCWSTR texturePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 get( unsigned int id);
	static CTextures *GetInstance();
	~CTextures();
};

