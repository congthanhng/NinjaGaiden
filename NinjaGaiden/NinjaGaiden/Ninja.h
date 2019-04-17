#pragma once
#include "GameObject.h"

#define NINJA_WALKING_SPEED		0.1f
#define NINJA_JUMP_SPEED_Y		0.2f
#define NINJA_GRAVITY			0.01f

#define NINJA_STATE_IDLE			0	
#define NINJA_STATE_WALKING_RIGHT	10
#define NINJA_STATE_WALKING_LEFT	12
#define NINJA_STATE_JUMP			20
#define NINJA_STATE_SIT				30

#define NINJA_ANI_IDLE		0	
#define NINJA_ANI_WALKING	1
#define NINJA_ANI_JUMP		2
#define NINJA_ANI_SIT		3

class CNinja:public GameObject
{
	bool isJumping;
	bool isRunning;
	bool isHitting;
	bool isSitting;
public:
	void SetisJumping(bool isJumping) { this->isJumping = isJumping; }
	bool GetisJumping() { return this->isJumping; }

	void SetisRunning(bool isRunning) { this->isRunning = isRunning; }
	bool GetisJuming() { return this->isRunning; }

	void SetisSitting(bool isSitting) { this->isSitting = isSitting; }
	bool GetisSitting() { return this->isSitting; }

	void SetisHitting(bool isHitting) { this->isHitting = isHitting; }
	bool GetisHiitting() { return this->isHitting; }

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

