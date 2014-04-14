#include "abelt.h"
#include "random.h"
#include "datasystem.h"

dataSystem ds_a;

aBelt::aBelt()
{

}

aBelt::aBelt(string name, float size, bool full)
{
	aBName = name;
	aBSize = size;
	bIsABFull = full;
}

aBelt::aBelt(string name, float size, int ramount, bool full)
{
	aBName = name;
	aBSize = size;
	numOfAsteroids = ramount;
	bIsABFull = full;
}

void aBelt::createAsteroids()
{
	bIsABFull = false;
	tempSize1 = 0.0f;
	tempSize2 = 0.0f;
	tempSize3 = 0.0f;

	while (!bIsABFull)
	{
		/*
		non-testing ranges:
		small: 75% of random max 1-37.5
		medium: 15% of random max 37.6-45.0
		large: 5% of random max 45.1-50.0

		*/		

		rand5 = fRandom(1.0f,50.0f);

		//Stage 1 Asteroid
		if ((rand5 >= 1.0) && (rand5 <= 16.5))
		{
			aID = Random(31,33); //External value tag: int range

			ds_a.rData("Ore","select from", aID);

			tempSize1 = ds_a.getOBSize();

			//asteroid size calcualtion				
			tempSize1 = tempSize1 * fRandom(0.3,1.68); //External value tag: float range
			tempSize2 = (((tempSize1 * 10) / 4 ) * 1.12); //External value tag: final multiplier
			tempSize3 += tempSize2;

			addAsteroid(ds_a.getOName(), ds_a.getOOre(), aID, ds_a.getODesc(),tempSize2, (tempSize2/ds_a.getOSG2()),Random(-10, 30),Random(-8, 21),Random(-13, 32));
		}

		//Stage 2 Asteroid
		else if ((rand5 >= 16.6) && (rand5 <= 33.0))
		{
			aID = Random(31,33); //External value tag: int range

			ds_a.rData("Ore","select from", aID);

			tempSize1 = ds_a.getOBSize();

			//asteroid size calcualtion				
			tempSize1 = tempSize1 * fRandom(0.2,1.52); //External value tag: float range
			tempSize2 = (((tempSize1 * 10) / 5 ) * 1.03); //External value tag: final multiplier
			tempSize3 += tempSize2;

			addAsteroid(ds_a.getOName(), ds_a.getOOre(), aID, ds_a.getODesc(),tempSize2, (tempSize2/ds_a.getOSG2()),Random(-10, 30),Random(-8, 21),Random(-13, 32));
		}

		//Stage 3 Asteroid
		else if (rand5 >= 33.1)
		{
			aID = Random(31,33); //External value tag: int range

			ds_a.rData("Ore","select from", aID);

			tempSize1 = ds_a.getOBSize();

			//asteroid size calcualtion				
			tempSize1 = tempSize1 * fRandom(0.1,1.18); //External value tag: float range
			tempSize2 = (((tempSize1 * 10) / 6 ) * 0.98); //External value tag: final multiplier
			tempSize3 += tempSize2;

			addAsteroid(ds_a.getOName(), ds_a.getOOre(), aID, ds_a.getODesc(),tempSize2, (tempSize2/ds_a.getOSG2()),Random(-10, 30),Random(-8, 21),Random(-13, 32));
		}

		//Check to see if tempSize2 is greater thean aBSize
		if (tempSize3 > aBSize)
		{
			//If it is then remove last asteroid
			tempSize3 -= tempSize2; //Remove the asteroid's size from the size total
			roids.erase(roids.begin()+roids.size()-1);
		}

		else if (tempSize3 <= aBSize)
		{
			if (numOfAsteroids == roids.size())
			{
				bIsABFull = true;
			}

			else if (tempSize3 == aBSize)
			{
				bIsABFull = true;
			}
		}

		//Check to make sure no other asteroid has the same coords
		if (roids.size() > 1)
		{
			for(i2 = 0; i2 < roids.size(); i2++)
			{
				for (i3 = 0; i3 < roids.size()-1; i3++)
				{
					if ((roids.at(i3).getXPos() == roids.at(i3+1).getXPos()) && (roids.at(i3).getYPos() == roids.at(i3+1).getYPos()) && (roids.at(i3).getZPos() == roids.at(i3+1).getZPos())) //If asteroid is at same coords then
					{
						tempSize3 -= roids.at(i3+1).getASize(); //Remove from total size
						roids.erase(roids.begin()+i3+1); //And then from the vector
					}
				}
			}
		}
	}
}

void aBelt::addAsteroid(string aName, string aOName, int aOID, string aDesc, float aSize, float aOAmount, int x, int y, int z)
{
	roids.push_back(Asteroid(aName, aOName, aOID, aDesc, aSize, aOAmount, x, y, z));
}

string aBelt::getABName()
{
	return aBName;
}

float aBelt::getABSize()
{
	return aBSize;
}

void aBelt::removeAsteroid(int i)
{
	roids.erase(roids.begin()+i);
}

bool aBelt::isFull()
{
	return bIsABFull;
}