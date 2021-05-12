#include "pch.h"
#include "CppUnitTest.h"
//#include "../Tanks/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//using namespace tanks;

namespace Function
{
	//class FakeGame : public Game {
	//public:
	//	Clock clock;
	//	FakeGame() : Game(){
	//		Instance = this;
	//	}
	//	void Update() {
	//		time = clock.getElapsedTime().asSeconds();
	//		clock.restart();
	//		for (int i = 0; i < timers.size(); i++) {//итерация таймеров
	//			timers[i]->Tick(time);
	//		}

	//		for (int i = 0; i < gameObjects.size(); i++) {//обновление состояний игровых объектов
	//			gameObjects[i]->Update();
	//		}

	//		CheckInterspect();

	//	}
	//	virtual float GetTime() override {
	//		return 10;
	//	}
	//};

	TEST_CLASS(Function)
	{
	public:
		TEST_METHOD(endGame)
		{
			//auto g = new Game(5, true);
			//Assert::IsTrue(Game::result == Result::exite);
		}
		//TEST_METHOD(DieEnemy)
		//{
		//	/*auto game = new FakeGame(100);
		//	auto enemy = new Enemy(100, 100);
		//	auto fire = new Fire(100, 100, 1, 1, playerfire);
		//	game->AddGameObject(enemy);
		//	game->AddGameObject(fire);
		//	enemy->Interspect(fire);
		//	Assert::IsTrue(game->gameObjects.size() == 0);*/
		//}
		//TEST_METHOD(moveLeftAI)
		//{

		//}
		//TEST_METHOD(moveRightAI)
		//{

		//}
		//TEST_METHOD(shootAI)
		//{

		//}
	};
}

