#pragma once
#include <SFML/Graphics.hpp>
#include "BombSettings.h"
#include <string>

using namespace std;

class Display
{
private:
	Text kills, lives, killsNum, livesNum, finish, startBtn, win;
	int livesCount, killsCount;
public:
	Display() {}

	Display(Font &font){
		livesCount = 3;
		killsCount = 0;

		dispStart(font);
		dispLives(font);
		dispKills(font);
		dispEnd(font);
	}

	void ifShipIsHit(){
		livesCount -= 1;
		livesNum.setString(to_string(livesCount));
	}

	void killEnemy(){
		bool playerwins = true;
		killsCount += 1;
		killsNum.setString(to_string(killsCount));
		if (killsCount == 20) {
			isGameOver(playerwins);
		}
	}
	int getKills() const{
		return killsCount;
	}

	int getLives() const{
		return livesCount;
	}

	void setLives(int lives){
		livesCount = lives;
		livesNum.setString(to_string(livesCount));
	}

	void setKills(int kills){
		killsCount = kills;
		killsNum.setString(to_string(killsCount));
	}

	bool Start(Vector2f mousePosition){
		bool isStartClicked = false;
		if (startBtn.getGlobalBounds().contains(mousePosition)){
			isStartClicked = true;
			startBtn.setString("");
			finish.setString("");
		}
		return isStartClicked;
	}

	void dispLives(Font &font) {
		lives = Text("Lives: ", font, 20);
		lives.setPosition(20, 560);
		livesNum = Text(to_string(livesCount), font, 20);
		livesNum.setPosition(80, 560);
	}
	void dispKills(Font &font) {
		kills = Text("Kills: ", font, 20);
		kills.setPosition(725, 560);
		killsNum = Text(to_string(killsCount), font, 20);
		killsNum.setPosition(775, 560);
	}
	void dispStart(Font &font) {
		startBtn = Text("START", font, 50);
		startBtn.setPosition(335, 260);
	}
	void dispEnd(Font &font) {
		finish = Text("", font, 50);
		finish.setPosition(320, 350);
	}

	void isGameOver(bool playerwins){
		startBtn.setString("START");
		if (playerwins) {
			finish.setString("You Win!");
		}
		else 
			finish.setString("You Lose!");
	}
	void draw(RenderWindow &canvas)
	{
		canvas.draw(startBtn);
		canvas.draw(kills);
		canvas.draw(killsNum);
		canvas.draw(lives);
		canvas.draw(livesNum);
		canvas.draw(finish);
	}
};