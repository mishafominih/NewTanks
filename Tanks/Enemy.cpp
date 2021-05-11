#include "Game.h"

namespace tanks {
	Enemy::Enemy(float startX, float startY) : Tank("Enemy.png") {
		x = startX;
		y = startY;
		this->type = enemy;
		sprite.setPosition(x, y);
		FindObjectATtypeOf(player);
		dir = up;
		speed = 0.06;
	}

	void Enemy::FindObjectATtypeOf(Type type)
	{
		for (int i = 0; i < Game::Instance->gameObjects.size(); i++) {
			if (Game::Instance->gameObjects[i]->type == type) {
				target = Game::Instance->gameObjects[i];
			}
		}
	}

	void Enemy::Update() {
		if (targetTimer->IsTime()) {
			if (target->type == player) FindObjectATtypeOf(head);
			else FindObjectATtypeOf(player);
			targetTimer->Restart();
		}
		logic();
		Draw();
	}

	void tanks::Enemy::logic()
	{
		Move();
		if (rand() % 11000 == 333) {
			Game::Instance->AddGameObject(new Fire(x, y, enemyFire, dir));
		}
		if (rand() % 400000 == 333) {
			ChangeDir();
		}
	}

	void Enemy::ChangeDir()
	{
		if (dir == up || dir == down) {
			if(target->x > x)
				rand() % 3 == 0 ? SetDir(left) : SetDir(right);
			else
				rand() % 3 == 0 ? SetDir(right) : SetDir(left);
		}
		else {
			if(target->y > y)
				rand() % 3 == 0 ? SetDir(up) : SetDir(down);
			else
				rand() % 3 == 0 ? SetDir(down) : SetDir(up);
		}
	}

	void Enemy::Interspect(GameObject* obj) {
		if (obj->type == playerfire) {
			Game::Instance->DelGameObject(obj);
			Game::Instance->DelGameObject(this);
		}
		if (obj->type == player || obj->type == bricks || obj->type == wall || obj->type == head) {
			ReverseMove();
			if (changeDirTimer->IsTime()) {
				ChangeDir();
				changeDirTimer->Restart();
			}
		}
	}

	void tanks::Enemy::End()
	{
		if (changeDirTimer->IsTime()) {
			ChangeDir();
			changeDirTimer->Restart();
		}
	}
}