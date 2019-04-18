#include "Enemies.h"




void CEnemies::Update(DWORD dt) {
	GameObject::Update(dt);
}
void CEnemies::Render() {

	GameObject::Render();
	int ani=ENEMIES_ANI;
	animations[ani]->Render(x, y, nx);
}

