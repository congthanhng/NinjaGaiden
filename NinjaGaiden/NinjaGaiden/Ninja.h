#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f
#define SIMON_CLIMB_SPEED		0.1f
#define SIMON_JUMP_SPEED_Y		0.3f
#define SIMON_GRAVITY			0.01f
#pragma region state for ninja
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	1
#define SIMON_STATE_WALKING_LEFT	2
#define SIMON_STATE_JUMP			3
#define SIMON_STATE_SIT				4
#define SIMON_STATE_STAND_HIT		6
#define SIMON_STATE_SIT_HIT			8
#define SIMON_STATE_LATCH			9
#define SIMON_STATE_CLIMB_UP		10
#define SIMON_STATE_CLIMB_DOWN		11
#define SIMON_STATE_JUMPWALL_RIGHT	12
#define	SIMON_STATE_JUMPWALL_LEFT	13
#pragma endregion
#pragma region animation ninja
#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_SIT				2
#define SIMON_ANI_STAND_HIT			3
#define SIMON_ANI_SIT_HIT			4
#define SIMON_ANI_JUMP				5
#define SIMON_ANI_LATCH				6
#define SIMON_ANI_CLIMB				7
#pragma endregion


class CNinja :public CGameObject
{
private:
	int isJumping;
	int isSitting;
	int isHitting;
	int isClimbing;
	int isLatching;
	int isJumpWall;


public:

	CNinja();
	void SetisJumping(int j) { this->isJumping = j; }
	int GetisJumping() { return this->isJumping; }
	void SetisSitting(int s) { this->isSitting = s; }
	int GetisSitting() { return this->isSitting; }
	void SetisHitting(int h) { this->isHitting = h; }
	int GetisHitting() { return this->isHitting; }
	void SetisClimbing(int c) { this->isClimbing = c; }
	int GetisClimbing() { return this->isClimbing; }
	void SetisLatching(int l) { this->isLatching = l; }
	int GetisLatching() { return this->isLatching; }
	void SetisJumpWall(int jw) { this->isJumpWall = jw; }
	int GetisJumpWall() { return this->isJumpWall; }

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};