#include "pch.h"
#include "Game.h"

namespace tanks {
	Tank::Tank(String path) : GameObject(path) {

	}

	void Tank::Draw()
	{
		auto dWidth = sprite.getTextureRect().width / 2;
		auto dHeight = sprite.getTextureRect().height / 2;
		switch (dir) {
		case(up):
			sprite.setPosition(x - dWidth, y - dHeight);
			break;
		case(right):
			sprite.setPosition(x + dWidth, y - dHeight);
			break;
		case(down):
			sprite.setPosition(x + dWidth, y + dHeight);
			break;
		case(left):
			sprite.setPosition(x - dWidth, y + dHeight);
			break;
		}
	}

	void tanks::Tank::ControlPosition(float& coordinate)
	{
		int coord = coordinate - 25;
		auto size = Game::Instance->sizeItem;
		auto surplus = coord % size;
		if (surplus > size / 2) coordinate = ((coord / size) + 1)* size + 25;
		else coordinate = (coord / size)* size + 25;
	}

	void Tank::Move()
	{
		auto dWidth = sprite.getTextureRect().width / 2;
		auto dHeight = sprite.getTextureRect().height / 2;
		auto maxH = Game::Instance->WindowHeight - dHeight;
		auto maxW = Game::Instance->WindowWidth - dWidth;
		switch (dir) {
		case(up):
			y -= Game::Instance->GetTime() * speed;
			if (y < dHeight) {
				y = dHeight;
				End();
			}
			break;
		case(right):
			x += Game::Instance->GetTime() * speed;
			if (x > maxW) {
				x = maxW;
				End();
			}
			break;
		case(down):
			y += Game::Instance->GetTime() * speed;
			if (y > maxH) {
				y = maxH;
				End();
			}
			break;
		case(left):
			x -= Game::Instance->GetTime() * speed;
			if (x < dWidth) {
				x = dWidth;
				End();
			}
			break;
		}
	}

	void Tank::SetDir(Direction newDir)
	{
		dir = newDir;
		sprite.setRotation(dir * 90);
	}

	void Tank::ReverseMove()
	{
		switch (dir) {
		case(up):
			dir = down;
			Move();
			dir = up;
			break;

		case(right):
			dir = left;
			Move();
			dir = right;
			break;

		case(down):
			dir = up;
			Move();
			dir = down;
			break;

		case(left):
			dir = right;
			Move();
			dir = left;
			break;
		}
	}

	void Tank::End()
	{
	}

}