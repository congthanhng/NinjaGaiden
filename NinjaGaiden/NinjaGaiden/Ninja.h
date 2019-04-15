#pragma once
#include "GameObject.h"

#define NINJA_WALKING_SPEED		0.1f
#define NINJA_JUMP_SPEED_Y		0.5f
#define NINJA_GRAVITY			0.1f

#define NINJA_STATE_IDLE			0
#define NINJA_STATE_WALKING_RIGHT	1
#define NINJA_STATE_WALKING_LEFT	2
#define NINJA_STATE_JUMP			3

#define NINJA_ANI_IDLE_RIGHT		0
#define NINJA_ANI_IDLE_LEFT			1
#define NINJA_ANI_WALKING_RIGHT		2
#define NINJA_ANI_WALKING_LEFT		3

class CNinja:public GameObject
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

