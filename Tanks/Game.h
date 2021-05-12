#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace tanks {
	class Timer;
	using namespace std;
	using namespace sf;

	enum Type { player, playerfire, enemyFire, enemy, wall, nothing, bricks, head, bush };
	enum Result { win, lose, exite };
	enum Direction { up, right, down, left };

	class GameObject {//базовый класс, который наследуют все игровые объекты
	public:
		Type type;
		int index;
		Image image;
		Texture texture;
		Sprite sprite;
		float x;
		float y;
		GameObject(String imagePath);
		virtual ~GameObject();
		virtual void Update() { }
		virtual void Interspect(GameObject* obj) { }
	};

	class Game {
	protected:
		void CheckInterspect();
		bool exit = false;
	public:
		int level;
		static Result result;//исход игры
		float time;
		float speedShoot;
		int sizeItem = 50;
		static Game* Instance;//ссылка на объект
		vector<GameObject*> gameObjects;//список всех игровых объектов, дл€ которых обновл€етс€ логика и провер€ютс€ столкновени€
		vector<Timer*> timers;
		int WindowWidth = 1200;
		int WindowHeight = 800;
		Game(int level, bool isPlayer);
		Game();
		void SpawnEnemy(tanks::Timer* spawn, int* positions, int& indexPos, int& count);
		void CreateLevel(bool isPlayer);
		void CreateHead();
		void CheckPlayerWin(int& count);
		void Exit(Result res);//выход
		void AddGameObject(GameObject* obj);//регистраци€ игрового объекта
		void DelGameObject(GameObject* obj);
		void AddTimer(Timer* timer);//регистраци€ таймера
		void DelTimer(Timer* timer);
		virtual float GetTime();
	};

	class Timer
	{
		float time;
		float timer;
	public:
		float index;
		Timer(float time);
		void Tick(float time);
		bool IsTime();
		void Restart();
	};

	class Tank : public GameObject{
	public:
		float speed = 0.2f;
		Direction dir;

		Tank(String path);
		void ControlPosition(float& coordinate);
		void Draw();
		void Move();
		void SetDir(Direction newDir);
		void ReverseMove();
		virtual void End();
	};

	class Player : public Tank {
	protected:
		virtual void Control();
		void CreateFire();
		Timer* shootTimer;
	public:
		int lives = 3;
		Player(float startX, float startY);
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
	};

	class Fire : public GameObject {
	public:
		float speed = 0.3f;
		Direction dir;
		Fire(float startX, float startY, Type type, Direction dir);
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
	};

	class Bricks : public GameObject {
	private:
	public:
		Bricks(float startX, float startY);
		virtual void Interspect(GameObject* obj) override;
	};
	
	class Wall : public GameObject {
	private:
	public:
		Wall(float startX, float startY);
		virtual void Interspect(GameObject* obj) override;
	};

	class Bush : public GameObject {
	private:
	public:
		Bush(float startX, float startY);
		virtual void Interspect(GameObject* obj) override;
	};

	class Head : public GameObject {
	private:
	public:
		Head(float startX, float startY);
		virtual void Interspect(GameObject* obj) override;
	};

	class Enemy : public Tank {
	private:
		Timer* targetTimer = new Timer(8);
		Timer* changeDirTimer = new Timer(0.5);
		GameObject* target;
	public:
		Enemy(float startX, float startY);
		void logic();
		void ChangeDir();
		void FindObjectATtypeOf(Type type);
		virtual void Update() override;
		virtual void Interspect(GameObject* obj) override;
		virtual void End() override;
	};

	class Computer : public Player{
	protected:
		Timer* rightTimer = new Timer(0.3);
		Timer* leftTimer = new Timer(0.3);
		virtual void Control() override;
	public:
		Computer(int startX, int startY);
	};
}
#endif
