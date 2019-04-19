#pragma once
#include "AlienMgr.h"
#include "MissileMgr.h"
class GameMgr
{
private:
	int playerLivesLeft;
public:
	GameMgr()
	{

	}
	void startGame(AlienMgr& alienMgr)
	{
		playerLivesLeft = 3;
		alienMgr.spawnAliens();
	}
	// Do this every frame to check for any hits and alien position
	void checkGameStatus(AlienMgr& alienMgr, MissileMgr& missileMgr)
	{
		if (alienMgr.aliensReachedPlayer())
		{
			loseALife(alienMgr);
		}
		//alienMgr.checkForHit(missileMgr);
		//missileMgr.checkForHit(alienMgr);
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