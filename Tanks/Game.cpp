#include "pch.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"
#include <iostream>

using namespace std;

namespace tanks {

	Game* Game::Instance;
	Result Game::result;

	Game::Game(int level, bool isPlayer) {
		this->level = level;
		if (level >= 4 || level < 0) {
			Exit(exite);
			cout << "Вы выиграли!!!" << endl;
		}
		Instance = this;
		RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Tanks");

		CreateLevel(isPlayer);

		Clock clock;
		srand(std::time(NULL));

		Timer* spawn = new Timer(4);
		AddTimer(spawn);
		int count = 20;
		int* positions = new int[3] { 75, WindowWidth / 2 - 25, WindowWidth - 25};
		int indexPos = 0;
		while (window.isOpen())//основной игровой цикл
		{
			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			for (auto timer : timers) {//итерация таймеров
				timer->Tick(time);
			}

			for (int i = 0; i < gameObjects.size(); i++) {//обновление состояний игровых объектов
				gameObjects[i]->Update();
			}

			CheckInterspect();//проверка столкновений

			SpawnEnemy(spawn, positions, indexPos, count);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					Exit(Result::exite);
				}
			}
			window.clear();

			CheckPlayerWin(count);

			for (auto obj : gameObjects) {//отрисовка всех игровых объектов
				window.draw(obj->sprite);
			}
			window.display();
			if (exit) {
				window.close();
			}
		}
	}

	Game::Game()
	{
	}

	void Game::SpawnEnemy(tanks::Timer* spawn, int* positions, int& indexPos, int& count)
	{
		if (spawn->IsTime()) {
			if (count-- <= 0) return;
			auto position = positions[indexPos++];
			if (indexPos >= 3) indexPos = 0;
			AddGameObject(new Enemy(position, 25));
			spawn->Restart();
		}
	}

	void Game::CreateLevel(bool isPlayer)
	{
		for (int i = 0; i < WindowWidth; i += 50) {
			for (int j = 0; j < WindowHeight; j += 50) {
				if(i % 100 == 0 && j % 100 == 0 && j < WindowHeight - 200)
					AddGameObject(new Bricks(i, j));

			}
		}
		AddGameObject(new Bricks(WindowWidth - 100, WindowHeight - 100));
		AddGameObject(new Bricks(WindowWidth - 50, WindowHeight - 100));
		AddGameObject(new Bricks(WindowWidth - 100, WindowHeight - 50));
		AddGameObject(new Bricks(WindowWidth - 50, WindowHeight - 50));
		AddGameObject(new Bricks(WindowWidth - 50, WindowHeight - 150));

		AddGameObject(new Bricks(200, WindowHeight - 200));
		AddGameObject(new Bricks(200, WindowHeight - 150));
		AddGameObject(new Bricks(200, WindowHeight - 100));
		AddGameObject(new Bricks(200, WindowHeight - 50));


		CreateHead();


		AddGameObject(new Wall(50, 50));
		AddGameObject(new Wall(50, 100));
		AddGameObject(new Wall(50, 150));
		AddGameObject(new Wall(100, 150));

		AddGameObject(new Wall(500, 250));
		AddGameObject(new Wall(550, 250));
		AddGameObject(new Wall(600, 250));

		AddGameObject(new Wall(950, 100));
		AddGameObject(new Wall(950, 150));
		AddGameObject(new Wall(950, 200));
		AddGameObject(new Wall(950, 250));
		AddGameObject(new Wall(950, 300));

		AddGameObject(new Wall(50, 700));
		AddGameObject(new Wall(550, 550));
		AddGameObject(new Wall(650, 0));

		if(isPlayer) AddGameObject(new Player(WindowWidth / 2 - 125, WindowHeight - 25));
		else AddGameObject(new Computer(WindowWidth / 2 - 25, WindowHeight - 125));


		AddGameObject(new Bush(WindowWidth / 2 + 300, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 250, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 200, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 150, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 100, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 50, WindowHeight - 150));
		AddGameObject(new Bush(WindowWidth / 2 + 300, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 250, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 200, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 150, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 100, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 50, WindowHeight - 100));
		AddGameObject(new Bush(WindowWidth / 2 + 300, WindowHeight - 50));
		AddGameObject(new Bush(WindowWidth / 2 + 250, WindowHeight - 50));
		AddGameObject(new Bush(WindowWidth / 2 + 200, WindowHeight - 50));
		AddGameObject(new Bush(WindowWidth / 2 + 150, WindowHeight - 50));
		AddGameObject(new Bush(WindowWidth / 2 + 100, WindowHeight - 50));
		AddGameObject(new Bush(WindowWidth / 2 + 50, WindowHeight - 50));
		for (int i = 0; i < WindowWidth; i += 50) {
			for (int j = 0; j < WindowHeight; j += 50) {
				if (i % 50 == 0 && i % 100 != 0 && j % 50 == 0 && j % 100 != 0 && j < WindowHeight - 200)
					AddGameObject(new Bush(i, j));

			}
		}
	}

	void Game::CreateHead()
	{
		AddGameObject(new Bricks(WindowWidth / 2 - 100, WindowHeight - 100));
		AddGameObject(new Bricks(WindowWidth / 2 - 50, WindowHeight - 100));
		AddGameObject(new Bricks(WindowWidth / 2, WindowHeight - 100));
		AddGameObject(new Bricks(WindowWidth / 2 - 100, WindowHeight - 50));
		AddGameObject(new Head(WindowWidth / 2 - 50, WindowHeight - 50));
		AddGameObject(new Bricks(WindowWidth / 2, WindowHeight - 50));
	}

	void Game::CheckPlayerWin(int& count)
	{
		if (count <= 0) {
			int countObj = 0;
			for (auto obj : gameObjects) {
				if (obj->type == Type::enemy) {
					countObj++;
				}
			}
			if (countObj == 0)
				Exit(win);
		}
	}

	void Game::Exit(Result res)
	{
		result = res;
		exit = true;
	}

	void Game::CheckInterspect()
	{
		for (int i = 0; i < gameObjects.size(); i++) {
			for (int j = i + 1; j < gameObjects.size(); j++) {
				auto first = gameObjects[i];
				auto second = gameObjects[j];
				auto interspect = first->sprite.getGlobalBounds().intersects(second->sprite.getGlobalBounds());
				if (interspect) {
					first->Interspect(second);
				}
			}
		}
	}

	void Game::AddGameObject(GameObject* obj) {
		obj->index = gameObjects.size();
		gameObjects.push_back(obj);
	}

	void Game::DelGameObject(GameObject* obj) {
		auto iter = gameObjects.cbegin(); // указатель на удаляемый элемент
		for (int i = obj->index + 1; i < gameObjects.size(); i++) {
			gameObjects[i]->index--;
		}
		gameObjects.erase(iter + obj->index);   // удаляем третий элемент
		delete obj;
	}

	void Game::AddTimer(Timer* timer)
	{
		timer->index = timers.size();
		timers.push_back(timer);
	}

	void Game::DelTimer(Timer* timer)
	{
		auto iter = timers.cbegin(); // указатель на удаляемый элемент
		for (int i = timer->index + 1; i < timers.size(); i++) {
			timers[i]->index--;
		}
		timers.erase(iter + timer->index);   // удаляем третий элемент
		delete timer;
	}

	float Game::GetTime()
	{
		return time * 1400;
	}
}