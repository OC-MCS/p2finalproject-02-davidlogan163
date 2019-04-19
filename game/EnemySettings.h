#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <list>
#include <iomanip>
using namespace std;

class Enemies
{
private:
	Sprite alien;
public:

	Enemies(Vector2f pos, Sprite sprite){
		alien = sprite;
		alien.setPosition(pos);
	}

	void draw(RenderWindow &canvas){
		canvas.draw(alien);
	}

	void descend(){
		alien.move(0, 3);
	}

	void reset(){
		alien.setPosition(alien.getPosition().x, 10);
	}

	bool checkInteraction(MissileSettings &missiles){
		list<Projectiles>::iterator obj;
		list<Projectiles> * ptr = missiles.lists();
		bool checkHit = false;
		for (obj = ptr->begin(); obj != ptr->end() && !checkHit; ){
			if (alien.getGlobalBounds().intersects(obj->sprite().getGlobalBounds())){
				obj = ptr->erase(obj);
				checkHit = true;
			}
			else
				obj++;
		}
		return checkHit;
	}

	void dropBomb(BombSettings &bombs){
		bombs.addProjectiles(Vector2f(alien.getPosition().x + 10, alien.getPosition().y));
	}

	Vector2f getPosition() const
	{
		return alien.getPosition();
	}
};

class EnemySettings
{
private:
	list<Enemies> listOfEnemies;
	Sprite enemy;
public:
	EnemySettings(){
	}
	EnemySettings(Texture &image) {
		enemy.setTexture(image);
	}

	void down(){
		list<Enemies>::iterator obj;

		for (obj = listOfEnemies.begin(); obj != listOfEnemies.end(); obj++)
		{
			obj->descend();
		}
	}

	void resetPos(){
		list<Enemies>::iterator obj;
			for (obj = listOfEnemies.begin(); obj != listOfEnemies.end(); obj++){
			obj->reset();
		}
	}

	bool checkInteraction(MissileSettings &missiles){
		list<Enemies>::iterator obj;
		bool checkHit = false;
		for (obj = listOfEnemies.begin(); obj != listOfEnemies.end(); ){
			if (obj->checkInteraction(missiles)){
				obj = listOfEnemies.erase(obj);
				checkHit = true;
			}
			else
				obj++;
		}
		return checkHit;
	}

	void addEnemy(Vector2f pos){
		listOfEnemies.push_back(Enemies(pos, enemy));
	}

	void bombDrop(BombSettings &bombs){
		if (listOfEnemies.size() > 0) {
			int target = (rand() % (listOfEnemies.size()));

			list<Enemies>::iterator obj;
			obj = listOfEnemies.begin();
			advance(obj, target);
			obj->dropBomb(bombs);
		}
	}

	void draw(RenderWindow &canvas){
		list<Enemies>::iterator obj;
		for (obj = listOfEnemies.begin(); obj != listOfEnemies.end(); obj++){
			obj->draw(canvas);
		}
	}
	int getEnemyNumber() const {
		return listOfEnemies.size();
	}
	void removeList(){
		list<Enemies>::iterator obj;
		for (obj = listOfEnemies.begin(); obj != listOfEnemies.end(); ) {
			obj = listOfEnemies.erase(obj);
		}
	}

	bool checkPos(Ship &ship){
		list<Enemies>::iterator obj;
		bool bottom = false;
		for (obj = listOfEnemies.begin(); obj != listOfEnemies.end() && !bottom; obj++){
			if (obj->getPosition().y >= ship.getXPosition().y){
				obj = listOfEnemies.erase(obj);
				bottom = true;
			}
		}
		return bottom;
	}
};

