#include "pch.h"
#include "Game.h"

namespace tanks {
	Computer::Computer(int startX, int startY) :Player(startX, startY){
		rightTimer->Tick(0.15);
	}

	void Computer::Control() {
		for (int i = 0; i < Game::Instance->gameObjects.size(); i++) {
			auto obj = Game::Instance->gameObjects[i];
			if (obj->type == enemy) {
				if (rightTimer->IsTime()) {
					if (obj->x > x && abs(obj->y - y) < 250) {
						SetDir(right);
						CreateFire();
					}
				}
				if (leftTimer->IsTime()) {
					if (obj->x < x && abs(obj->y - y) < 250) {
						SetDir(left);
						CreateFire();
					}
				}
			}
		}

		if (rightTimer->IsTime()) {
			rightTimer->Restart();
		}
		if (leftTimer->IsTime()) {
			leftTimer->Restart();
		}
	}
}