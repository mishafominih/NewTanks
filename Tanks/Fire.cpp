#include "pch.h"
#include "Game.h"

namespace tanks {
	Fire::Fire(float startX, float startY, Type type, Direction dir) : GameObject("fire.png") {
		x = startX;
		y = startY;
		this->type = type;
		this->dir = dir;
	}

	void Fire::Update() {
		auto dWidth = sprite.getTextureRect().width / 2;
		auto dHeight = sprite.getTextureRect().height / 2;
		auto move = Game::Instance->GetTime() * speed;
		auto maxW = Game::Instance->WindowWidth - dWidth;
		auto maxH = Game::Instance->WindowHeight - dHeight;
		switch (dir) {
		case(up):
			sprite.setPosition(x - dWidth, y - dHeight);
			sprite.setRotation(0);
			y -= move;
			if (y < dHeight) Game::Instance->DelGameObject(this);
			break;
		case(right):
			sprite.setPosition(x + dWidth, y - dHeight + 7);
			sprite.setRotation(90);
			x += move;
			if (x > maxW) Game::Instance->DelGameObject(this);
			break;
		case(down):
			sprite.setPosition(x + dWidth, y + dHeight);
			sprite.setRotation(180);
			y += move;
			if (y > maxH) Game::Instance->DelGameObject(this);
			break;
		case(left):
			sprite.setPosition(x - dWidth, y + dHeight - 7);
			sprite.setRotation(270);
			x -= move;
			if (x < dWidth) Game::Instance->DelGameObject(this);
			break;
		}
	}

	void Fire::Interspect(GameObject* obj) {
		if (obj->type != playerfire && obj->type != enemyFire) {
			obj->Interspect(this);
		}
	}
}
