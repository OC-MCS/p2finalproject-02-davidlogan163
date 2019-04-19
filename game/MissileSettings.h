#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectileSettings.h"


class MissileSettings : public ProjectileSettings {
private: 
public:
	MissileSettings() {

	}
	MissileSettings(Texture &image) : ProjectileSettings(image){
		setSpeed(-8);
	}
	bool isObjectOffCanvas(Projectiles obj) {
		bool out = false;
		if (obj.getXPosition().y < 0){ 
			out = true;
		}
		return out;
	}
};