#ifndef ABELT_H
#define ABELT_H

#include <string>
#include <vector>
#include "asteroid.h"

using std::string;
using std::vector;

//class dataSystem;

class aBelt
{
public:

	aBelt();
	aBelt(string name, float size, bool full);
	aBelt(string name, float size, int ramount, bool full);

	void createAsteroids(); //Create asteroids in a belt
	void addAsteroid(string aName, string aOName, int aID, string aDesc, float aSize, float aOAmount, int x, int y, int z); //Add an asteroid to the belt
	void removeAsteroid(int i);

	string getABName();
	float getABSize();

	bool isFull();

	vector<Asteroid> roids;

private:

	bool bIsABFull; //bool: is asteroid belt full?
	float aBSize; //Asteroid belt size; see below
	string aBName; //Astroid belt name

	float rand1, rand2, rand5, tempSize1, tempSize2, tempSize3;
	int rand3,rand4, numOfAsteroids, aID, randx, randy, randz;
	int i,i2,i3;
};
#endif