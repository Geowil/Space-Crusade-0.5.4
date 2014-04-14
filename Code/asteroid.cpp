#include "asteroid.h"

Asteroid::Asteroid()
{

}

Asteroid::Asteroid(string name, string oname, int oID, string desc, float size, float oamount, int x, int y, int z)
{
	aName = name;
	aOName = oname;
	aOID = oID;
	aDesc = desc;
	aSize = size;
	aOAmount = oamount;
	posX = x;
	posY = y;
	posZ = z;
}

void Asteroid::updateOAmount(float amount, string operation)
{
	if (operation == "add")
	{
		aOAmount += amount;
	}

	else if (operation == "sub")
	{
		aOAmount -= amount;
	}

	else if (operation == "set")
	{
		aOAmount = amount;
	}
}


string Asteroid::getAName()
{
	return aName;
}

string Asteroid::getADesc()
{
	return aDesc;
}

string Asteroid::getOName()
{
	return aOName;
}

float  Asteroid::getASize()
{
	return aSize;
}

float  Asteroid::getAOAmount()
{
	return aOAmount;
}

int Asteroid::getXPos()
{
	return posX;
}

int Asteroid::getYPos()
{
	return posY;
}

int Asteroid::getZPos()
{
	return posZ;
}

int Asteroid::getAOID()
{
	return aOID;
}