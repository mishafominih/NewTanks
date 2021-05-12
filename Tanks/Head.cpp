#include "pch.h"
#include "Game.h"

namespace tanks {
	Head::Head(float startX, float startY) : GameObject("Head.png") {
		x = startX;
		y = startY;
		this->type = head;
		sprite.setPosition(x, y);
	}

	void Head::Interspect(GameObject* obj) {
		if (obj->type == playerfire || obj->type == enemyFire) {
			Game::Instance->Exit(lose);
		}
	}
}