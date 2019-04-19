#pragma once
#include <SFML/Graphics.hpp>
#include "Display.h"
#include "Ship.h"
#include "EnemySettings.h"
#include <iomanip>

 class GameSettings{
private:
	bool isGameRunning;
public:


	GameSettings()
	{
		isGameRunning = false;
	}
	bool isGameAlive() const
	{
		return isGameRunning;
	}
	// starts level one
	void levelOne(Display &Display, Ship &ship, Vector2f shipPos, MissileSettings &missile, BombSettings &bomb, EnemySettings &enemy, Texture &alien) {
		enemy = EnemySettings(alien);

		resetAll(Display, ship, shipPos, missile, bomb, enemy);

		Display.setKills(0);

		isGameRunning = true;
	}
	// Starts level two
	void levelTwo(Display &Display, Ship &ship, Vector2f shipPos, MissileSettings &missile, BombSettings &bomb, EnemySettings &enemy, Texture &alien) {
		enemy = EnemySettings(alien);
		resetAll(Display, ship, shipPos, missile, bomb, enemy);
	}
	// Resets the game
	void resetAll(Display &Display, Ship &ship, Vector2f shipPos, MissileSettings &missile, BombSettings &bomb, EnemySettings &enemy)
	{
		enemy.removeList();
		bomb.removeProjectiles();
		missile.removeProjectiles();

		for (int i = 0; i < 10; i++)
		{
			enemy.addEnemy(Vector2f(i * 80.0f + 20, 10));
		}
		ship.setPosition(shipPos);
		Display.setLives(3);
	}

	void finish(Display &Display) {
		isGameRunning = false;
		if (Display.getLives() > 0)
		{
			Display.isGameOver(true);
		}
		else
		{
			Display.isGameOver(false);
		}
	}
};
