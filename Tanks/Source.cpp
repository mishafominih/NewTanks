#include "Game.h"
#include "pch.h"

#include <iostream>

using namespace tanks;
using namespace std;

int main() {
	setlocale(0, "");
	cout << "������� 0 ��� �� ������ ������, 1 ��� �� ������ ���������" << endl;
	int input;
	cin >> input;
	int level = 0;
	while (true) {
		new Game(level++, input == 0);
		if (Game::result == lose) level--;
		if (Game::result == win) continue;
		if (Game::result == exite) break;
	}
}