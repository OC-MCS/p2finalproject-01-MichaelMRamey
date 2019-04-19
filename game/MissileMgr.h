#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Missile.h"
class MissileMgr
{
private:
	Texture missileTexture;
	list<Missile> missileList;
	list<Missile>::iterator missileListItr;
public:
	MissileMgr()
	{
		loadTexture();
	}
	void loadTexture()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void drawMissiles(RenderWindow& win)
	{
		for (missileListItr = missileList.begin(); missileListItr != missileList.end(); missileListItr++)
		{
			missileListItr->draw(win);
		}
	}
	void newMissile(Vector2f pos)
	{
		missileList.push_back(Missile(pos, missileTexture));
	}
	void moveMissiles()
	{
		for (missileListItr = missileList.begin(); missileListItr != missileList.end(); missileListItr++)
		{
			missileListItr->moveMissile();
		}
	}
};