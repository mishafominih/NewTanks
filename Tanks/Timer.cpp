#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;
namespace tanks {

	Timer::Timer(float time) {
		timer = 0;
		this->time = time;
		Game::Instance->AddTimer(this);
	}

	void Timer::Tick(float time) {
		timer += time;
	}

	bool Timer::IsTime() {
		return timer >= time;
	}

	void Timer::Restart() {
		timer = 0;
	}
}