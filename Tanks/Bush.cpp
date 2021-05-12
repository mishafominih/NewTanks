#include "pch.h"
#include "Game.h"

namespace tanks {
	Bush::Bush(float startX, float startY) : GameObject("Bush.png") {
		x = startX;
		y = startY;
		this->type = bush;
		sprite.setPosition(x, y);
	}

	void Bush::Interspect(GameObject* obj) {

	}
}