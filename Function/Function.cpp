#include "pch.h"
#include "CppUnitTest.h"
#include "../Tanks/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tanks;

namespace Function
{
	class FakeGame : public Game {
	public:
		Clock clock;
		FakeGame() : Game(){
			Instance = this;
		}
		void Update() {
			time = clock.getElapsedTime().asSeconds();
			clock.restart();
			for (int i = 0; i < timers.size(); i++) {//итерация таймеров
				timers[i]->Tick(time);
			}

			for (int i = 0; i < gameObjects.size(); i++) {//обновление состояний игровых объектов
				gameObjects[i]->Update();
			}

			CheckInterspect();

		}
		virtual float GetTime() override {
			return 10;
		}
	};

	TEST_CLASS(Function)
	{
	public:
		TEST_METHOD(endGame)
		{
			auto g = new Game(5, true);
			Assert::IsTrue(Game::result == Result::exite);
		}
		TEST_METHOD(DieEnemy)
		{
			auto game = new FakeGame();
			auto enemy = new Enemy(100, 100);
			auto fire = new Fire(100, 100, playerfire, up);
			game->AddGameObject(enemy);
			game->AddGameObject(fire);
			enemy->Interspect(fire);
			Assert::IsTrue(game->gameObjects.size() == 0);
		}
		TEST_METHOD(DiePlayer)
		{
			auto game = new FakeGame();
			auto player = new Player(100, 100);
			auto fire1 = new Fire(100, 100, enemyFire, up);
			auto fire2 = new Fire(100, 100, enemyFire, up);
			auto fire3 = new Fire(100, 100, enemyFire, up);
			game->AddGameObject(player);
			game->AddGameObject(fire1);
			game->AddGameObject(fire2);
			game->AddGameObject(fire3);
			player->Interspect(fire1);
			player->Interspect(fire2);
			player->Interspect(fire3);
			Assert::IsTrue(game->gameObjects.size() == 1);//так как игрок не удаляет послднюю пулю перед смертью.
		}
		TEST_METHOD(DieComputer)
		{
			auto game = new FakeGame();
			auto player = new Computer(100, 100);
			auto fire1 = new Fire(100, 100, enemyFire, up);
			auto fire2 = new Fire(100, 100, enemyFire, up);
			auto fire3 = new Fire(100, 100, enemyFire, up);
			game->AddGameObject(player);
			game->AddGameObject(fire1);
			game->AddGameObject(fire2);
			game->AddGameObject(fire3);
			player->Interspect(fire1);
			player->Interspect(fire2);
			player->Interspect(fire3);
			Assert::IsTrue(game->gameObjects.size() == 1);//так как игрок не удаляет послднюю пулю перед смертью.
		}
	};
}

