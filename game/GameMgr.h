#pragma once
#include "AlienMgr.h"
#include "MissileMgr.h"
class GameMgr
{
private:
	int playerLivesLeft;
	int levelNum;
public:
	void startGame(AlienMgr& alienMgr)
	{
		playerLivesLeft = 3;
		levelNum = 1;
		alienMgr.spawnAliens();
	}
	// Do this every frame to check for collisions and level change


	void checkGameStatus(AlienMgr& alienMgr, MissileMgr& missileMgr)
	{
		if (alienMgr.aliensReachedPlayer())
		{
			loseALife(alienMgr);
		}
		
		for (int i = 0; i < missileMgr.getListSize(); i++)
		{
			if(alienMgr.checkForHit(missileMgr.getMissile(i).getHitbox()))
				missileMgr.deleteMissile(i);
		}

		/*if (alienMgr.aliensKilled() == alienMgr.aliensSpawned())
		{
			levelNum++;
		}	*/	
	}
	void loseALife(AlienMgr& alienMgr)
	{
		playerLivesLeft--;
		alienMgr.deleteAllAliens();
		alienMgr.spawnAliens();
	}
	int livesLeft()
	{
		return playerLivesLeft;
	}
};