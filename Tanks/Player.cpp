#include "pch.h"
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
			ControlPosition(x);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			SetDir(right);
			ControlPosition(y);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			SetDir(down);
			ControlPosition(x);
			Move();
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			SetDir(left);
			ControlPosition(y);
			Move();
		}
		if (shootTimer->IsTime()) {
			if (Keyboard::isKeyPressed(Keyboard::F)) {
				CreateFire();
				shootTimer->Restart();
			}
		}
	}

	void Player::CreateFire()
	{
		auto fire = new Fire(x, y, playerfire, dir);
		Game::Instance->AddGameObject(fire);
	}

	void Player::Interspect(GameObject* obj) {
		if (obj->type == bricks || obj->type == wall || obj->type == head || obj->type == enemy) {
			ReverseMove();
		}
		if (obj->type == enemyFire) {
			lives -= 1;
			if (lives == 0) {
				Game::Instance->Exit(lose);
			}
			Game::Instance->DelGameObject(obj);
		}
	}
}

