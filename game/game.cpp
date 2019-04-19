//===============================
// David Logan
// 4/19/19
// Programming Assignment 8
// Description: Space Invaders
//===============================

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Ship.h"
#include "EnemySettings.h"
#include "ProjectileSettings.h"
#include "BombSettings.h"
#include "Display.h"
#include "Enemies.h"
#include "MissileSettings.h"

using namespace std;

void die(string end);
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float SHIPX = WINDOW_WIDTH / 2.2f;
const float SHIPY = WINDOW_HEIGHT / 1.2f;
RenderWindow canvas(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders in C++!");

int main()
{
	GameSettings game;

	canvas.setFramerateLimit(60);
	//==========================================================================================================
	//Load the textures and initialize settings

	Font Font;
	if (!Font.loadFromFile("C:\\Windows\\Fonts\\Rage.ttf")) {
		die("Error opening Arial font!");
	}
	Display display(Font);

	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.jpg")) {
		die("Error opening ship.jpg!");
	}
	Ship ship(Vector2f(SHIPX, SHIPY), shipTexture);
	Clock shipShootTimer;

	Texture space;
	if (!space.loadFromFile("space3.jpg")) {
		die("Error opening space3.jpg!");
	}
	Sprite bkgrd;
	bkgrd.setTexture(space);
	bkgrd.setScale(.5, .5);
	Texture enemy1;
	if (!enemy1.loadFromFile("Alien1.jpg")) {
		die("Error opening Alien1.jpg!");
	}
	EnemySettings enemies(enemy1);
	Clock enemyDownTimer;

	Texture enemy2;
	if (!enemy2.loadFromFile("Alien2.jpg")) {
		die("Error opening Alien2.jpg!");
	}
	Texture bombTexture;
	if (!bombTexture.loadFromFile("Bomb.jpg")) {
		die("Error opening Bomb.jpg!");
	}
	BombSettings bombs(bombTexture);
	Clock bombDropTimer;

	Texture missileTexture;
	if (!missileTexture.loadFromFile("missile.png")) {
		die("Error opening missile.png!");
	}
	MissileSettings missiles(missileTexture);

	// Game is running
	while (canvas.isOpen())
	{
		Event event;
		unsigned seed = time(0);
		srand(time(0));
		double bombDescendDelay = 0.2;
		int bombDropDelay = 2;
		int delay = (rand() % bombDropDelay) + 1;

		while (canvas.pollEvent(event)){ 
			if (event.type == Event::MouseButtonReleased) {
				Vector2f mousePos = canvas.mapPixelToCoords(Mouse::getPosition(canvas));
				if (display.Start(mousePos)){
					game.levelOne(display, ship, Vector2f(SHIPX, SHIPY), missiles, bombs, enemies, enemy1);
					bombDescendDelay = 0.2;
					bombDropDelay = 2;
					bombDropTimer.restart();
				}
			}

			 if (event.type == Event::KeyPressed){ 
				if (event.key.code == Keyboard::Space && shipShootTimer.getElapsedTime().asSeconds() >= 0.1) {
					ship.shootMissile(missiles);
					shipShootTimer.restart();
				}
			}

			 if (event.type == Event::Closed) {
				 canvas.close();
			 }

		}

		if (game.isGameAlive()){
			if (enemyDownTimer.getElapsedTime().asSeconds() >= bombDescendDelay){
				enemies.down();
				enemyDownTimer.restart();
			}

			if (bombDropTimer.getElapsedTime().asSeconds() >= delay){
				enemies.bombDrop(bombs);
				bombDropTimer.restart();
				delay = (rand() % bombDropDelay) + 1;
			}

			if (enemies.checkInteraction(missiles)){
				display.killEnemy();
			}

			if (ship.checkInteraction(bombs) || enemies.checkPos(ship)) {
				display.ifShipIsHit();
				enemies.resetPos();
			}

			if (enemies.getEnemyNumber() <= 0) {
				if (bombDropDelay == 2) {
					game.levelTwo(display, ship, Vector2f(SHIPX, SHIPY), missiles, bombs, enemies, enemy2);
					bombDropDelay = 2;
					bombDescendDelay = 0.2;
				}
				else
					game.finish(display);
			}
			if (display.getLives() <= 0) {
				game.finish(display);
			}
		}

		canvas.draw(bkgrd);
		display.draw(canvas);
		ship.draw(canvas);
		missiles.draw(canvas);
		bombs.draw(canvas);
		enemies.draw(canvas);
		canvas.display();

		ship.move();
		missiles.move();
		missiles.remove();
		bombs.remove();
		bombs.move();
	}

	return 0;
}

void die(string end)
{
	cout << end << endl;
	exit(-1);
}