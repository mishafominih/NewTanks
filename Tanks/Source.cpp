#include "Game.h"

using namespace tanks;

int main() {
	setlocale(0, "");
	int level = 0;
	while (true) {
		new Game(level++);
		if (Game::result == lose) level--;
		if (Game::result == win) continue;
		if (Game::result == exite) break;
	}
}