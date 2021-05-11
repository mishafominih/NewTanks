#include "pch.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.h"
#include <iostream>

using namespace std;
namespace tanks {

	Game* Game::Instance;
	Result Game::result;

	Game::Game() {
		Instance = this;
		RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Tanks");

		AddGameObject(new Bricks(150, 200));
		AddGameObject(new Wall(350, 150));
		AddGameObject(new Player(100, 100));
		AddGameObject(new Enemy(350, 500));
		AddGameObject(new Bush(250, 200));
		//AddGameObject(new Head(50, 50));

		Clock clock;
		srand(std::time(NULL));

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

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					Exit(Result::exite);
				}
			}
			window.clear();

			//CheckPlayerWin();

			for (auto obj : gameObjects) {//отрисовка всех игровых объектов
				window.draw(obj->sprite);
			}
			window.display();
			if (exit) {
				window.close();
			}
		}
	}

	void Game::CheckPlayerWin()
	{
		int count = 0;
		for (auto obj : gameObjects) {
			if (obj->type == Type::enemy) {
				count++;
			}
		}
		if (count == 0)
			Exit(win);
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