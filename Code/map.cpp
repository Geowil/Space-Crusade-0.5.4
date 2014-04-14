#include "map.h"
#include "entity.h"
#include <cmath>

using std::sqrt;

Map::Map()
{

}

void Map::setPOS(Player& pTeam, NPC& hTeam)
{
	for (i = 0; i < pTeam.getNOWingmen() + 1; i++) //Get number of wingmen then add 1 for player
	{
		if (i == 0)
		{
			x = Random(-50,50);
			y = Random(-50,50);
			z = Random(-50,50);

			pTeam.Ship.setPos(x, y, z);
		}

		else
		{
			//To add some variation in where the allied ships are placed
			xR = Random(1,5);
			yR = Random(1,5);
			zR = Random(1,5);

			pTeam.eWingmen.at(i-1).Ship.setPos(Random(x-xR,x+xR), Random(y-yR,y+yR), Random(z-zR,z+zR)); //Apply a small variation in origination coordinates so that allied/enemy ships are placed near by each other but somewhat randomized
		}
	}

	for (i = 0; i < hTeam.getNOWingmen() + 1; i++) //Get number of wingmen and add 1 for main hostile
	{		
		if (i == 0)
		{
			x = Random(-50,50);
			y = Random(-50,50);
			z = Random(-50,50);

			hTeam.Ship.setPos(x, y, z);
		}

		else
		{
			//To add some variation in where the allied ships are placed
			xR = Random(1,5);
			yR = Random(1,5);
			zR = Random(1,5);

			hTeam.eWingmen.at(i-1).Ship.setPos(Random(x-xR,x+xR), Random(y-yR,y+yR), Random(z-zR,z+zR)); //Apply a small variation in origination coordinates so that allied/enemy ships are placed near by each other but somewhat randomized
		}
	}
}

float Map::getDistance(float x1, float x2, float y1, float y2, float z1, float z2)
{
	mDistance = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) + ((z1 - z2) * (z1 - z2)));

	mDistance = floor((mDistance*100)+0.5)/100.0; //round to two decimal places

	return mDistance;
}

bool Map::shipEncounter(int dist)
{
	encRand1 = Random(1,20);
	encRand2 = Random(1,100);

	if (encRand1 * (dist/2) > 25)
	{
		if (encRand2 * ((dist * encRand1) / 10) < 60)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		if (encRand2 * ((dist * encRand1) / 10) > 60)
		{
			return true;
		}
		
		else
		{
			return false;
		}
	}
}