#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <list>
using namespace std;
using namespace sf;

class Projectiles
{
private:
	Sprite projectile;
public:
	Projectiles(Vector2f pos, Sprite image){
		projectile = image;
		projectile.setPosition(pos);
	}

	Sprite sprite() const {
		return projectile;
	}

	void draw(RenderWindow &canvas){
		canvas.draw(projectile);
	}

	void move(float dist){
		projectile.move(0, dist);
	}


	Vector2f getXPosition() const{
		return projectile.getPosition();
	}
};

class ProjectileSettings
{
private:
	list<Projectiles> listOfProjectiles;
	Sprite projectile;
	float velocity;
	virtual bool isObjectOffCanvas(Projectiles obj) = 0;
public:
	ProjectileSettings() {}


	void move() {
		list<Projectiles>::iterator obj;
		for (obj = listOfProjectiles.begin(); obj != listOfProjectiles.end(); obj++) {
			obj->move(velocity);
		}
	}

	ProjectileSettings(Texture &image) {
		velocity = 0;
		projectile.setTexture(image);
	}

	// Adds a projectile to the list
	void addProjectiles(Vector2f pos)
	{
		listOfProjectiles.push_back(Projectiles(pos, projectile));
	}

	// Removes projectile from list
	void removeProjectiles(int index)
	{
		list<Projectiles>::iterator obj;
		obj = listOfProjectiles.begin();
		advance(obj, index);
		listOfProjectiles.erase(obj);
	}

	// Change the speed of the projectiles
	void setSpeed(float vel){
		velocity = vel;
	}

	// Clears projectiles from the list
	void removeProjectiles(){
		list<Projectiles>::iterator obj;
		for (obj = listOfProjectiles.begin(); obj != listOfProjectiles.end(); ){
			obj = listOfProjectiles.erase(obj);
		}
	}

	// List of projectiles
	list<Projectiles> * lists(){
		return &listOfProjectiles;
	}

	// Draws projectiles
	void draw(RenderWindow &canvas){
		list<Projectiles>::iterator obj;
		for (obj = listOfProjectiles.begin(); obj != listOfProjectiles.end(); obj++){
			obj->draw(canvas);
		}
	}
	// Removes the projectiles offscreen
	void remove(){
		list<Projectiles>::iterator obj;
		for (obj = listOfProjectiles.begin(); obj != listOfProjectiles.end(); ){
			if (isObjectOffCanvas(*obj)){
				obj = listOfProjectiles.erase(obj);
			}
			else{
				obj++;
			}
		}
	}
};