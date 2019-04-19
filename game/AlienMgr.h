#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include "alien.h"

class MissileMgr;

class AlienMgr
{
private:
	Texture alienTexture;
	list<Alien> alienList;
	list<Alien>::iterator alienListItr;
	int aliensKilled;
	int aliensSpawned;
public:
	AlienMgr()
	{
		loadTexture();
		aliensKilled = 0;
		aliensSpawned = 0;
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
		for (int i = 0; i < 10; i++)
		{
			newAlien(Vector2f(x, 100));
			aliensSpawned++;
			x += 75;
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
	bool checkForHit(FloatRect missileHitbox)
	{
		bool hitAlien = false;
		for (alienListItr = alienList.begin(); alienListItr != alienList.end();)
		{
			if (alienListItr->getHitbox().intersects(missileHitbox))
			{
				alienListItr = alienList.erase(alienListItr);
				aliensKilled++;
				hitAlien = true;
			}
			else
				alienListItr++;
		}
		return hitAlien;
	}
	Alien getAlien(int index)
	{
		alienListItr = alienList.begin();
		advance(alienListItr, index);
		return *alienListItr;
	}
	int getListSize()
	{
		return alienList.size();
	}
	int getAliensKilled()
	{
		return aliensKilled;
	}
	int getAliensSpawned()
	{
		return aliensSpawned;
	}
	void resetKills()
	{
		aliensKilled = 0;
	}
	void resetAliensSpawned()
	{
		aliensSpawned = 0;
	}
};