#pragma once
#include "GameObject.h"

#define ENEMIES_ANI 6
class CEnemies :public GameObject
{

public:

	void Update(DWORD dt);
	void Render();
};

