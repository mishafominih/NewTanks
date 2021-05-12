
#include "pch.h"
#include "Game.h"

namespace tanks {
	Bricks::Bricks(float startX, float startY) : GameObject("Bricks.png") {
		x = startX;
		y = startY;
		this->type = bricks;
		sprite.setPosition(x, y);
	}

	void Bricks::Interspect(GameObject* obj) {
		if (obj->type == playerfire || obj->type == enemyFire) {
			Game::Instance->DelGameObject(obj);
			Game::Instance->DelGameObject(this);
			return;
		}
		if (obj->type != type) {
			obj->Interspect(this);
		}
	}
}