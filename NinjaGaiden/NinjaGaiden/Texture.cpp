#include "Texture.h"
#include "GameInit.h"




Texture::Texture(LPCWSTR texturePath) {

	D3DXIMAGE_INFO image_info;
	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &image_info);

	if(result !=D3D_OK){
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = GameInit::GetInstance()->GetDirectxDevice();
}



Texture::~Texture()
{
}
