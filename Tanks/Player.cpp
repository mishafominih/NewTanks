#include "Game.h"

namespace tanks {
	Player::Player(float startX, float startY) : Tank("Player.png"){
		x = startX;
		y = startY;
		sprite.setPosition(x, y);
		type = player;
		dir = up;
		shootTimer = new Timer(0.1);
	}

	void Player::Update() {
		Control();
		Draw();
	}

	void Player::Control()
	{
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			SetDir(up);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			SetDir(right);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			SetDir(down);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			SetDir(left);
			Move();
		}
		if (shootTimer->IsTime()) {
			if (Keyboard::isKeyPressed(Keyboard::F)) {
				Game::Instance->AddGameObject(
					new Fire(x, y, playerfire, dir)
				);
				shootTimer->Restart();
			}
		}
	}

	void Player::Interspect(GameObject* obj) {
		if (obj->type == bricks || obj->type == wall || obj->type == head || obj->type == enemy) {
			ReverseMove();
		}
		if (obj->type == enemyFire) {
			Game::Instance->Exit(lose);
		}
	}
}

