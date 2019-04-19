#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Bomb.h"


class BombMgr
{
private:
	Texture bombTexture;
	list<Bomb> bombList;
	list<Bomb>::iterator bombListItr;
	int bombSpawnRate = 300;  //Lower number means more bombs
public:
	BombMgr()
	{
		loadTexture();
	}
	void loadTexture()
	{
		if (!bombTexture.loadFromFile("Bomb.jpg"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void drawBombs(RenderWindow& win)
	{
		for (bombListItr = bombList.begin(); bombListItr != bombList.end(); bombListItr++)
		{
			bombListItr->draw(win);
		}
	}
	void newBomb(Vector2f pos)
	{
		bombList.push_back(Bomb(pos, bombTexture));
	}
	void moveBombs()
	{
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			bombListItr->moveBomb();
			if (bombListItr->getYPos() < 0)
			{
				bombListItr = bombList.erase(bombListItr);
			}
			else
				bombListItr++;
		}
	}
	Bomb getBomb(int index)
	{
		bombListItr = bombList.begin();
		advance(bombListItr, index);
		return *bombListItr;
	}
	int getListSize()
	{
		return bombList.size();
	}
	void deleteBomb(int index)
	{
		bombListItr = bombList.begin();
		advance(bombListItr, index);
		bombList.erase(bombListItr);
	}
	void deleteAllBombs()
	{
		bombList.clear();
	}
	bool checkForMissileHit(FloatRect missileHitbox)
	{
		bool hitBomb = false;
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			if (bombListItr->getHitbox().intersects(missileHitbox))
			{
				bombListItr = bombList.erase(bombListItr);
				hitBomb = true;
			}
			else
				bombListItr++;
		}
		return hitBomb;
	}
	bool checkForShipHit(FloatRect shipHitbox)
	{
		bool hitPlayer = false;
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			if (bombListItr->getHitbox().intersects(shipHitbox))
			{
				bombListItr = bombList.erase(bombListItr);
				hitPlayer = true;
			}
			else
				bombListItr++;
		}
		return hitPlayer;
	}
	int getBombSpawnRate()
	{
		return bombSpawnRate;
	}
};
