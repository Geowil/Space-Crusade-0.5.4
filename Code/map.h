/*FILE HEADER

File Name:

map.h

File Description:

The map class contains functions and variables dealing with the battle space and the locations of the various objects there in

How it Works:

This class sets a default location for each ship in the battle and then each turn the information is updated.  This class will
also be used to calculate the distance between objects in determintion of optiman attacks and AI movements

Created On:

Thursday, October 10, 2013

Version:

1.0 - 10/10/2013
1.1 - 10/12/2013

Changes:

1.0:
-Class created

1.1:
-Changed the parameters for setPOS from vectors to class references

*/

#ifndef MAP_H
#define MAP_H

#include "random.h"
#include "entity.h"
#include <vector>

using std::vector; 

class Map
{
public:
	Map();

	void setPOS(Player& pTeam, NPC& hTeam);
	
	float getDistance(float x1, float x2, float y1, float y2, float z1, float z2);

	//Map events
	bool shipEncounter(int dist); //Determine if we run into a ship while traveling

private:
	float mDistance;
	int i,i2,x,y,z,xR,yR,zR;  //For looping, storing primary location coordinates, and storing randomizer values

	int encRand1,encRand2; //To store randoms for encounter processing
};
#endif

