#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include "alien.h"
class AlienMgr
{
private:
	Texture alienTexture;
	list<Alien> alienList;
	list<Alien>::iterator alienListItr;
public:
	AlienMgr()
	{
		loadTexture();
	}
	void loadTexture()
	{
		if (!alienTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void drawAliens(RenderWindow& win)
	{
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			alienListItr->draw(win);
		}
	}
	void newAlien(Vector2f pos)
	{
		alienList.push_back(Alien(pos, alienTexture));
	}
	void spawnAliens()
	{
		float x = 40;
		for (int i=0; i < 10; i++)
		{
			newAlien(Vector2f(x,100));
			x += 100;
		}
	}
	void moveAliens()
	{
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			alienListItr->moveAlien();
		}
	}
	void deleteAllAliens()
	{
		alienList.clear();
	}
	bool aliensReachedPlayer()
	{
		bool result = 0;
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			if (alienListItr->getYPos() > 550)
			{
				result = true;
			}
			else
				result = false;
		}
		return result;
	}
	/*void checkForHit(MissileMgr& missileMgr)
	{
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			if (alienListItr->getHitbox().intersects(missileMgr.missileListItr->getHitbox())
			{
				alienList.erase(alienListItr);
			}
		}
	}*/
};