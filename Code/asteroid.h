#ifndef ASTEROID_H
#define ASTEROID_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class dataSystem;

class Asteroid
{
public:
	Asteroid();
	Asteroid(string name, string oname, int oID, string desc, float size, float oamount, int x, int y, int z); //Constructor to add astroid to vector

	void updateOAmount(float amount, string operation);

	string getAName();
	string getADesc();
	string getOName();

	float getASize();
	float getAOAmount();

	int getXPos();
	int getYPos();
	int getZPos();
	int getAOID();

private:

	string aName; //Asteroid name
	string aOName; //Asteroid ore name
	int aOID; //Asteroid ore id
	string aDesc; //Asteroid description

	float aSize; //Asteroid size
	float aOAmount; //Asteroid ore amount

	int posX,posY,posZ; //For coord system
};
#endif

/*
	Asteroid Belt Size

	Each belt will have a limited amount of space.  Each asteroid added to a specific belt will take up some of that space until the space is completely used up.  A random will determine the number of asteroids
	and this number will be multipiled by a random range times 13 divided by 6.

*/