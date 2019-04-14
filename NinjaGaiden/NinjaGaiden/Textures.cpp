#include "Textures.h"

#include <Windows.h>
#include "game.h"
#include <d3d9.h>
#include <d3dx9.h>

CTextures *CTextures::_Instance = NULL;

CTextures::CTextures()
{
}
void CTextures::Add(int id,LPCWSTR TexturePath, D3DCOLOR transparentColor){

	D3DXIMAGE_INFO image_info; //lay thong tin texture

	HRESULT result = D3DXGetImageInfoFromFile(TexturePath, &image_info); //lay duong dan texture va gan thong tin vao image_info

	if (result != D3D_OK)return;

	LPDIRECT3DDEVICE9 d3ddv = Cgame::GetInstance()->GetDirect3DDevice(); //singleton pattern chi 1 Cgame duoc tao trong suot qua trinh chay
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		TexturePath,
		image_info.Width,
		image_info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&image_info,
		NULL,
		&texture		//create texture
	);

	if (result != D3D_OK)return;

	textures[id] = texture; //gan vao danh sach cac texture
}
LPDIRECT3DTEXTURE9 CTextures::get(unsigned int id) {
	return textures[id];
}
CTextures *CTextures::GetInstance() {
	if (_Instance == NULL) _Instance = new CTextures();
	return _Instance;
}
CTextures::~CTextures()
{
}
