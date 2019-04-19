#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectileSettings.h"
#include <iomanip>
#include <list>
using namespace std;

class BombSettings : public ProjectileSettings {
private:

public:
	BombSettings() {
	}
	BombSettings(Texture &image) : ProjectileSettings(image){
		setSpeed(5);
	}

	bool isObjectOffCanvas(Projectiles obj){
		bool out = false;
		if (obj.getXPosition().y > 600){
			out = true;
		}
		return out;
	}
};



