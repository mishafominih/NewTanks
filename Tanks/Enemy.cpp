#include "pch.h"
#include "Game.h"

namespace tanks {
	Enemy::Enemy(float startX, float startY) : Tank("Enemy.png") {
		x = startX;
		y = startY;
		this->type = enemy;
		sprite.setPosition(x, y);
		FindObjectATtypeOf(player);
		dir = up;
		speed = 0.06 + 0.04 * Game::Instance->level;
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
		if (rand() % 2000 - 500 * Game::Instance->level == 21) {
			Game::Instance->AddGameObject(new Fire(x, y, enemyFire, dir));
		}
		if (rand() % 400000 - 5000 * Game::Instance->level == 333) {
			ChangeDir();
		}
	}

	void Enemy::ChangeDir()
	{
		if (dir == up || dir == down) {
			ControlPosition(x);
			if(target->x > x)
				rand() % 3 == 0 ? SetDir(left) : SetDir(right);
			else
				rand() % 3 == 0 ? SetDir(right) : SetDir(left);
		}
		else {
			ControlPosition(y);
			if(target->y > y)
				rand() % 3 == 0 ? SetDir(up) : SetDir(down);
			else
				rand() % 3 == 0 ? SetDir(down) : SetDir(up);
		}
	}

	void Enemy::Interspect(GameObject* obj) {
		if (obj->type == player || obj->type == bricks || obj->type == wall || obj->type == head) {
			ReverseMove();
			if (changeDirTimer->IsTime()) {
				ChangeDir();
				changeDirTimer->Restart();
			}
		}
		if (obj->type == playerfire) {
			Game::Instance->DelGameObject(this);
			Game::Instance->DelGameObject(obj);
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