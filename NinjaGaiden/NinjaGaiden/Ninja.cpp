#include "Ninja.h"



void CNinja::Update(DWORD dt) {

	GameObject::Update(dt);	

	//simple fall down
	
	if(isJumping)
	vy += NINJA_GRAVITY;
	if (y > 250) {
		vy = 0; y = 250.0f;
		isJumping = false;
	}

	//simple sreen egle collision
	if (vx > 0 && x > 290)x = 290;
	if (vx < 0 && x < 0)x = 0;
}

void CNinja::Render() { 
	int ani; 
	if(isHitting)ani= NINJA_ANI_HIT;
	else
	if (isJumping) ani = NINJA_ANI_JUMP;
	else if (isSitting) ani = NINJA_ANI_SIT;
	else if (vx != 0) ani = NINJA_ANI_WALKING;
		else ani = NINJA_ANI_IDLE;
	/*if (vx == 0) {
		if (nx > 0) {
			ani = NINJA_ANI_IDLE_RIGHT;
		}
		else ani = NINJA_ANI_IDLE_LEFT;
	 }
	else if (vx > 0) ani = NINJA_ANI_WALKING_RIGHT;
	else ani = NINJA_ANI_WALKING_LEFT;*/
	
	animations[ani]->Render(x, y,nx);
	
}

void CNinja::SetState(int state) {
	GameObject::SetState(state);
	switch (state) {
	case NINJA_STATE_WALKING_RIGHT:
		vx = NINJA_WALKING_SPEED;
		nx = 1;
		break;
	case NINJA_STATE_WALKING_LEFT:
		vx = -NINJA_WALKING_SPEED;
		nx = -1;
		break;
	case NINJA_STATE_JUMP:
		isJumping = true;
		if (y == 250) vy = -NINJA_JUMP_SPEED_Y;
		break;
	case NINJA_STATE_SIT:
		isSitting = true;
		vx = vy = 0;
		break;
	case NINJA_STATE_HIT:
		isHitting = true;
		break;
	case NINJA_STATE_IDLE:
		
		vx = 0;
		break;

	}
}
