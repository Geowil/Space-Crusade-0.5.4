#include "mining.h"
#include "msgproc.h"
#include "map.h"
#include <Windows.h>

msgProc mp_mn;
Map	m_mn;

using namespace std;

Mining::Mining()
{

}

void Mining::mLoop(Player& mPlayer, aBelt* belt)
{
	bDMining = false;
	mTarget = -1;

	//Get some basic values from player ship
	bPHMLaser = mPlayer.Ship.getMLInfo(&mCTime_left, &mTDist, &mOPCycle);

	if (bPHMLaser)
	{
		//Temp for now, only one mining laser can be used so call this
		mp_mn.mMLInfo(mCTime_left, mTDist, mOPCycle);

		while (!bDMining)
		{
			if (mTarget < 0)
			{
				pChoice = mp_mn.mMenu1();

				switch(pChoice)
				{
				case 1:
					mSAsteroid(belt, mPlayer);
					break;

				case 2:
					mTAsteroid(mPlayer,belt);
					break;

				case 3:
					mPMShip(mPlayer, belt);
					break;

				case 4:
					bDMining = true;
					break;

				default:
					mSAsteroid(belt, mPlayer);
					break;
				}
			}

			else if (mTarget >= 0)
			{
				pChoice = mp_mn.mMenu2();

				switch(pChoice)
				{
				case 1:
					mSCycle(mPlayer, belt);
					break;

				case 2:
					mUAsteroid();
					break;

				default:
					//Mine assteroid
					break;
				}
			}
		}
	}

	else
	{
		cout << mp_mn.mRMessage(2049) << endl;
	}
}

void Mining::mSAsteroid(aBelt* belt, Player& mPlayer)
{
	pPosX = mPlayer.Ship.getXPos();
	pPosY = mPlayer.Ship.getYPos();
	pPosZ = mPlayer.Ship.getZPos();

	//Clear sAsteroids before using it again if it is not empty
	if (sAsteroids.size() > 0)
	{
		sAsteroids.clear();
	}

	for (i2 = 0; i2 < belt->roids.size(); i2++)
	{
		sAsteroids.push_back(i2);
	}

	//Arrange based on distance from player; closest to furthest
	for (i2 = 0; i2 < sAsteroids.size(); i2++)
	{
		for (i3 = 0; i3 < sAsteroids.size()-1; i3++)
		{
			tempDist1 = m_mn.getDistance(mPlayer.Ship.getXPos(),belt->roids.at(sAsteroids.at(i3)).getXPos(),mPlayer.Ship.getYPos(),belt->roids.at(sAsteroids.at(i3)).getYPos(),mPlayer.Ship.getZPos(),belt->roids.at(sAsteroids.at(i3)).getZPos());
			tempDist2 = m_mn.getDistance(mPlayer.Ship.getXPos(),belt->roids.at(sAsteroids.at(i3+1)).getXPos(),mPlayer.Ship.getYPos(),belt->roids.at(sAsteroids.at(i3+1)).getYPos(),mPlayer.Ship.getZPos(),belt->roids.at(sAsteroids.at(i3+1)).getZPos());

			if (tempDist2 < tempDist1)
			{
				tempRoid1 = sAsteroids.at(i3+1);
				tempRoid2 = sAsteroids.at(i3);

				sAsteroids.at(i3) = tempRoid1;
				sAsteroids.at(i3+1) = tempRoid2;
			}
		}
	}

	cout << mp_mn.mRMessage(2032) << endl;
	mp_mn.mCScreen(true);
}

void Mining::mTAsteroid(Player& mPlayer, aBelt* belt)
{
	if (sAsteroids.size() > 0)
	{
		mTarget = mp_mn.mCTarget(belt->roids, sAsteroids, mPlayer, mTDist);

		if (mTarget == -2)
		{
			mPMShip(mPlayer, belt);
		}
	}

	else
	{
		cout << mp_mn.mRMessage(2028) << endl;
		mSAsteroid(belt, mPlayer);
	}
}

void Mining::mSCycle(Player& mPlayer, aBelt* belt)
{
	cout << mp_mn.mRMessage(2029) << endl;

	/*
		This will have to be multi-threaded with one thread for each mining laser; do this in 0.6A, for now only use the higher quality laser
	*/

	bMCycle = true;
	
	mCTime_left = mCTime_left * 1000; //Since we get the time from database in seconds we need to multiply by 1000 for miliseconds
	mCTime_new = GetTickCount(); //Get cycle start time
	mCTime_old = ((mCTime_new + 500) / 1000);

	cout << mp_mn.mRMessage(2030) << endl;
	
	while(bMCycle)
	{		
		cout << ((mCTime_left +500) / 1000) << " seconds";
		
		bNChange = true;

		while(bNChange)
		{			
			mCTime_new = GetTickCount();

			if (mCTime_old != ((mCTime_new+500)/1000))
			{
				mCTime_old = ((mCTime_new+500)/1000);
				mCTime_left -= 1000;
				bNChange = false;
			}
		}
		
		cout << " \r" << flush;

		if (mCTime_left == 0)
		{
			bMCycle = false;
		}
	}

	cout << mp_mn.mRMessage(2031) << endl;

	mECycle(mPlayer, belt);
}

void Mining::mECycle(Player& mPlayer, aBelt* belt)
{
	if (belt->roids.at(mTarget).getAOAmount() <= mOPCycle)
	{
		mSOre(mPlayer, belt);
		belt->removeAsteroid(mTarget);
		cout << mp_mn.mRMessage(2033) << endl;
		mTarget = -1;
	}

	else
	{
		belt->roids.at(mTarget).updateOAmount(mOPCycle, "sub");
		mSOre(mPlayer, belt);
	}	
}

void Mining::mSOre(Player& mPlayer, aBelt* belt)
{
	mPlayer.Ship.addCItem(belt->roids.at(mTarget).getAOID(), "Ore", mOPCycle, true);
}

void Mining::mUAsteroid()
{
	mTarget = -1;
}

void Mining::mPMShip(Player& mPlayer, aBelt* belt)
{
	mPRPoint = mp_mn.mGRPoint(sAsteroids, belt->roids, mPlayer);

	if (mPRPoint != -1)
	{
		mPlayer.Ship.sPMove_M(mPlayer, belt->roids.at(sAsteroids.at(mPRPoint)));
	}
}