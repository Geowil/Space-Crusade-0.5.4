#ifndef MINING_H
#define MINING_H

#include <string>
#include <vector>

#include "entity.h"
#include "planet.h"

using std::string;
using std::vector;

class Mining
{
public:

	Mining();

	void mLoop(Player& mPlayer, aBelt* belt); //Mining loop
	void mSCycle(Player& mPlayer, aBelt* belt); //Starts a mining cycle
	void mECycle(Player& mPlayer, aBelt* belt); //Ends mining cycle
	void mSOre(Player& mPlayer, aBelt* belt); //Begins storage process for mined ore

	void mTAsteroid(Player& mPlayer, aBelt* belt); //Pick an asteroid to target
	void mUAsteroid(); //Untarget targeted asteroid
	void mSAsteroid(aBelt* belt, Player& mPlayer); //Scan asteroids for information - only those within mTRange

	void mPMShip(Player& mPlayer, aBelt* belt);

	vector<int> sAsteroids; //Scanned asteroids, store as an int based on position in belt's vector.  Closets to furtherst order

private:
	bool bDMining; //bool: done mining?
	bool bMCycle; //bool: are we currently in a mining cycle?
	bool bNChange; //bool: while time has not changed (in seconds)
	float mEOre; //Total extracted ore
	int rand1,i,i2,i3,pChoice;

	int mTarget; //Mining Target

	int mCTime_new,mCTime_old,mCTime_left; //For keeping track of how much time as passed in a cycle

	float tempDist,tempDist1,tempDist2; //Store distance between player and asteroid for comparison

	int tempRoid1, tempRoid2; //Storage for sorting

	int mPRPoint; //Player reference point for moving the ship

	//Values from Player ship
	int mTDist; //Max target distance
	float mOPCycle; //Ore mined per cycle
	int pPosX, pPosY, pPosZ; //Player position

	bool bPHMLaser; //bool: player has a mining laser installed?
};
#endif


