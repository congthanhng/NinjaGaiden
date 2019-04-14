#include "Ninja.h"

CNinja::CNinja() :CGameObject::CGameObject()
{
	isHitting = 0;
	isJumping = 0;
	isSitting = 0;
	isClimbing = 0;
	isLatching = 0;
	isJumpWall = 0;
}

void CNinja::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	if (!isLatching)
		vy += SIMON_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
		isJumping = 0;
		isJumpWall = 0;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
	if (y < 0) y = 0;

}

void CNinja::Render()
{
	int ani;
	if (isLatching)
	{
		if (isClimbing)
			ani = SIMON_ANI_CLIMB;
		else
			ani = SIMON_ANI_LATCH;
	}
	else
		if (isJumping)
		{
			if (isHitting>0)
				ani = SIMON_ANI_STAND_HIT;
			else
				ani = SIMON_ANI_JUMP;
		}
		else
			if (isHitting>0)
			{
				if ((this->isSitting) == 0)
					ani = SIMON_ANI_STAND_HIT;
				else
					ani = SIMON_ANI_SIT_HIT;
			}
			else
			{
				if (vx == 0)
				{
					if (this->isSitting == 0) //nhân vật không ngồi
						ani = SIMON_ANI_IDLE;
					else
						ani = SIMON_ANI_SIT;
				}
				else
					ani = SIMON_ANI_WALKING;
			}

	animations[ani]->Render(x, y, isHitting, this->GetDirection());
}

void CNinja::SetState(int state)
{
	if (isHitting>0) return;
	isSitting = 0;
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		isJumping = 1;
		if (y == 100)
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_STAND_HIT:
		isHitting = 1;
		if (!this->isJumping) vx = 0;
		break;
	case SIMON_STATE_SIT:
		isSitting = 1;
		vx = 0;
		break;
	case SIMON_STATE_SIT_HIT:
		isSitting = 1;
		vx = 0;
		isHitting = 1;
		break;
	case SIMON_STATE_LATCH:
		isLatching = 1;
		isClimbing = 0;
		vy = 0;
		vx = 0;
		break;
	case SIMON_STATE_CLIMB_UP:
		vy = -SIMON_CLIMB_SPEED;
		isClimbing = 1;
		break;
	case SIMON_STATE_CLIMB_DOWN:
		vy = SIMON_CLIMB_SPEED;
		isClimbing = 1;
		break;
	case SIMON_STATE_JUMPWALL_RIGHT:
		nx = 1;
		isLatching = 0;
		isClimbing = 0;
		isJumpWall = 1;
		vx = SIMON_WALKING_SPEED;
		break;
	case SIMON_STATE_JUMPWALL_LEFT:
		nx = 0;
		isLatching = 0;
		isClimbing = 0;
		isJumpWall = 1;
		vx = -SIMON_WALKING_SPEED;
		break;
	}
}

