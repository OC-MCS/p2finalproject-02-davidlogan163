#pragma once
#include <SFML/Graphics.hpp>
#include "MissileSettings.h"
#include <iomanip>

class Ship
{
private:
	Sprite ship;
public:

	Ship() {}

	void draw(RenderWindow &canvas){
		canvas.draw(ship);
	}

	void move(){
		if (Keyboard::isKeyPressed(Keyboard::Left) && ship.getPosition().x > 0)
		{
			ship.move(-8, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && ship.getPosition().x < 750)
		{
			ship.move(8, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && ship.getPosition().y > 475)
		{
			ship.move(0, -8);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && ship.getPosition().y < 550) {
			ship.move(0, 8);
		}
	}

	void setPosition(Vector2f pos){
		ship.setPosition(pos);
	}

	bool checkInteraction(BombSettings &bombs){
		list<Projectiles>::iterator obj;
		list<Projectiles> * ptr = bombs.lists();
		bool collision = false; 

		for (obj = ptr->begin(); obj != ptr->end() && !collision; ) {
			if (ship.getGlobalBounds().intersects(obj->sprite().getGlobalBounds())) {
				obj = ptr->erase(obj);
				collision = true;
			}
			else
				obj++;
		}
		return collision;
	}

	void shootMissile(MissileSettings &missiles){
		missiles.addProjectiles(Vector2f(ship.getPosition().x + 12, ship.getPosition().y));
	}

	Vector2f getXPosition() const{
		return ship.getPosition();
	}

	Ship(Vector2f pos, Texture &img)
	{
		ship.setTexture(img);
		ship.setPosition(pos);
	}

};
