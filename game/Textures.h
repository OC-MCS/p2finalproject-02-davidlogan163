#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameSettings.h"
#include "Ship.h"
#include "EnemySettings.h"
#include "ProjectileSettings.h"
#include "BombSettings.h"
#include "Menu.h"
#include "Enemies.h"
#include "MissileSettings.h"
using namespace std;
using namespace sf;

void die(string end);

class Textures {
private:
public:
	Textures() {
	}
	Texture enemy2(Texture &enemy2){
		if (!enemy2.loadFromFile("Alien2.jpg")) {
			die("Error opening Alien2.jpg!");
		}
		return enemy2;
	}
	Texture bombTextures(Texture &bombTexture){
		if (!bombTexture.loadFromFile("Bomb.jpg")) {
			die("Error opening Bomb.jpg!");
		}
		return bombTexture;
	}
	Texture missileTexture(Texture &missileTexture) {
		if (!missileTexture.loadFromFile("missile.png")) {
			die("Error opening missile.png!");
		}
		return missileTexture;
	}
	Texture enemy1(Texture &enemy1) {
		if (!enemy1.loadFromFile("Alien1.jpg")) {
			die("Error opening Alien1.jpg!");
		}
		return enemy1;
	}
	Texture space(Texture &space) {

		if (!space.loadFromFile("space3.jpg")) {
			die("Error opening space3.jpg!");
		}
		return space;

	}
	Font font(Font &font) {
		if (!font.loadFromFile("C:\\Windows\\Fonts\\Rage.ttf")) {
			die("Error opening 'Rage' font!");
		}
		return font;
	}

	void shipTxt(Texture &shipTexture) {
		if (!shipTexture.loadFromFile("ship.jpg")) {
			die("Error opening ship.jpg!");
		}
	}
};

void die(string end)
{
	cout << end << endl;
	exit(-1);
}

