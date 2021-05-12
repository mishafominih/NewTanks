#include "pch.h"
#include "Game.h"

namespace tanks {
	Wall::Wall(float startX, float startY) : GameObject("Wall.png") {
		x = startX;
		y = startY;
		this->type = wall;
		sprite.setPosition(x, y);
	}

	void Wall::Interspect(GameObject* obj) {
		if (obj->type == playerfire || obj->type == enemyFire) {
			Game::Instance->DelGameObject(obj);
			return;
		}
		if (obj->type != type) {
			obj->Interspect(this);
		}
	}
}