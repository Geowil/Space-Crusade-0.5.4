#include <iostream>
#include <stdlib.h>
#include "planet.h"
#include "random.h"
#include "msgproc.h"
#include <Windows.h>
#include <sstream>
#include <cmath>

using namespace std;

//global variable defines

//Pillage EKS Multipliers

/*
How these work:

Multipliers is actually a misnomer.  These values take away a certain precentage of a planets randomized resource rewards.  As the EKS value gets higher, the more resources that are lost.
It is done this way to simulate the effects of attacking and pillaging the planet.  As planet sizes and EKS values increase the more destruction there has to be to pillage the planet.
This is represented here as a loss of resources when gaining though means of hostile action.

This is a resource balancing feature but will be tweakable by players/modders in future version when I move all of these hard coded defines and some other hard coded values into an ini file.

*/

#define PV_EKS0 0.98
#define PV_EKS1 0.92
#define PV_EKS2 0.85
#define PV_EKS3 0.80
#define PV_EKS4 0.74
#define PV_EKS5	0.68


//Asteroid Roman Numerals
string aRNumerals[10] = {
	"I",
	"II",
	"III",
	"IV",
	"V",
	"VI",
	"VII",
	"VIII",
	"IX",
	"X"
};

msgProc mp_p;

//Planet Functions

Planet::Planet()
{

}

Planet::Planet(int id, string name, string dispo, string affil, string race)
{
	plID = id;
	plName = name;
	plDispo = dispo;
	plAffil = affil;
	plRace = race;
	bIsDest = false;
}

Planet::Planet(int id, string name,  string dispo, string affil, string race, float eks, long long int pop)
{
	plID = id;
	plName = name;
	plDispo = dispo;
	plAffil = affil;
	pEKS = eks;
	pMPop = pop;
	pPop = pMPop;
	plRace = race;
	bIsDest = false;
}

Planet* Planet::getPlanet()
{
	return this;
}

void Planet::addPDefenses(bool defense, int did, bool shield, int mid, bool defender)
{
	if (defense)
	{
		pDef.push_back(Defense());

		pDef.at(pDef.size()-1).dSetup(did);
	}

	else if (shield)
	{
		pShd.push_back(Shield());

		pShd.at(pShd.size()-1).initPS(mid);
	}

	else if (defender)
	{

	}
}

float Planet::getEKS()
{
	return pEKS;
}

long long int Planet::getPop()
{
	return pPop;
}

string Planet::getPopS()
{
	stringstream ss;
	stringstream ss2;

	ss << pPop;
	sStorage = ss.str();

	if ((sStorage.length() >= 4) && (sStorage.length() <= 6))
	{
		trailer = "K";
		popStorage = pPop * 0.0001f;
	}
	
	else if ((sStorage.length() >= 7) && (sStorage.length() <= 9))
	{
		trailer = "M";
		popStorage = pPop * 0.000001f;
	}

	else if ((sStorage.length() >= 10) && (sStorage.length() <= 12))
	{
		trailer = "B";
		popStorage = pPop * 0.000000001f;
	}

	else if ((sStorage.length() >= 13) && (sStorage.length() <= 16))
	{
		trailer = "T";
		popStorage = pPop * 0.000000000001f;
	}

	else
	{
		popStorage = 0.0;
		trailer = " ";
	}

	ss2 << popStorage;
	sPPop = ss2.str();

	return sPPop + " " + trailer;
}

long long int Planet::getMPop()
{
	return pMPop;
}

string Planet::getMPopS()
{
	stringstream ss;
	stringstream ss2;

	ss << pMPop;
	sStorage = ss.str();

	if ((sStorage.length() >= 4) && (sStorage.length() <= 6))
	{
		trailer = "K";
		popStorage = pMPop * 0.0001f;
	}
	
	else if ((sStorage.length() >= 7) && (sStorage.length() <= 9))
	{
		trailer = "M";
		popStorage = pMPop * 0.000001f;
	}

	else if ((sStorage.length() >= 10) && (sStorage.length() <= 12))
	{
		trailer = "B";
		popStorage = pMPop * 0.000000001f;
	}

	else if ((sStorage.length() >= 13) && (sStorage.length() <= 16))
	{
		trailer = "T";
		popStorage = pMPop * 0.000000000001f;
	}

	else
	{
		popStorage = 0.0;
		trailer = " ";
	}

	ss2 << popStorage;
	sPMPop = ss2.str();

	return sPMPop + " " + trailer;
}

string Planet::getName()
{
	return plName;
}

float Planet::getSize()
{
	return pSize;
}

int Planet::getPID()
{
	return plID;
}

bool Planet::bPIsDest()
{
	return bIsDest;
}

void Planet::setSize(float size)
{
	pSize = size;
}

void Planet::updatePop(long long int pop, string operation)
{
	if (operation == "set")
	{
		pPop = pop;
	}

	else if (operation == "add")
	{
		pPop += pop;
	}

	else if (operation == "sub")
	{
		pPop -= pop;
	}
}

void Planet::updateMPop(long long int pop, string operation)
{
	if (operation == "set")
	{
		pMPop = pop;
	}

	else if (operation == "add")
	{
		pMPop += pop;
	}

	else if (operation == "sub")
	{
		pMPop -= pop;
	}
}

void Planet::setAffil(string affil)
{
	plAffil = affil;
}

void Planet::setDispo(string dispo)
{
	plDispo = dispo;
}

void Planet::setPDest(int i)
{
	if (i == 0)
	{
		bIsDest = false;
	}

	else
	{
		bIsDest = true;
	}
}

void Planet::setPPOwned(int i)
{
	if (i == 0)
	{
		bIsPOwned = false;
	}

	else
	{
		bIsPOwned = true;
	}
}

void Planet::setPID(int id)
{
	plID = id;
}

void Planet::setName(string name)
{
	plName = name;
}

void Planet::setEKS(float eks)
{
	pEKS = eks;
}

string Planet::getAffil()
{
	return plAffil;
}

string Planet::getDispo()
{
	return plDispo;
}

string Planet::getStatus()
{
	return pStatus;
}

void Planet::setStatus(string s)
{
	pStatus = s;
}

string Planet::getRace()
{
	return plRace;
}

void Planet::setRace(string s)
{
	plRace = s;
}

void Planet::pillagePlanet(int* rX, int* rR, int* rDi, int* rD, int* rL, int* rPl, int* rU, int* rP, int* rNW)
{
	for (i = 0; i <= 8; i++)
	{
		switch(i)
		{
		case 0:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rX = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rX = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rX = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rX = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rX = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rX = Random(180, 14580) * PV_EKS5;
			}

			break;

		//In 0.6A differentiate the randoms based on the type of resource being given
		case 1:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rR = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rR = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rR = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rR = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rR = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rR = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 2:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rDi = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rDi = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rDi = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rDi = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rDi = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rDi = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 3:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rD = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rD = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rD = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rD = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rD = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rD = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 4:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rL = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rL = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rL = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rL = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rL = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rL = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 5:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rPl = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rPl = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rPl = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rPl = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rPl = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rPl = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 6:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rU = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rU = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rU = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rU = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rU = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rU = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 7:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rP = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rP = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rP = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rP = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rP = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rP = Random(180, 14580) * PV_EKS5;
			}

			break;

		case 8:
			if ((pEKS >= 0.000f) && (pEKS <= 0.999f))
			{
				*rNW = Random(10,4500) * PV_EKS0;
			}

			else if ((pEKS >= 1.000f) && (pEKS <= 1.999f))
			{
				*rNW = Random(50, 6590) * PV_EKS1;
			}

			else if ((pEKS >= 2.000f) && (pEKS <= 2.999f))
			{
				*rNW = Random(86, 7820) * PV_EKS2;
			}

			else if ((pEKS >= 3.000f) && (pEKS <= 3.999f))
			{
				*rNW = Random(110, 8950) * PV_EKS3;
			}

			else if ((pEKS >= 4.000f) && (pEKS <= 4.999f))
			{
				*rNW = Random(136, 9785) * PV_EKS4;
			}

			else if ((pEKS >= 5.000f))
			{
				*rNW = Random(180, 14580) * PV_EKS5;
			}

			break;
		}
	}
}

void Planet::setTDist(int dist)
{
	pTDist = dist;
}

int Planet::getTDist()
{
	return pTDist;
}

void Planet::createBelts()
{
	beltRand = Random(0,10);

	if (beltRand != 0)
	{
		for (i = 1; i <= beltRand; i++)
		{
			ramount = Random(3, 15); //External value tag: int range
			size = ((ramount * fRandom(1000.0,50000.00) * 46) / 2); //External value tag: float range
			name= plName + " Asteroid Belt " + aRNumerals[i-1];

			addBelt(name, size, ramount, false);
		}
	}
}

void Planet::addBelt(string name, float size, int ramount, bool full)
{	
	if (!full)
	{
		belts.push_back(aBelt(name, size, ramount, false));

		cout << mp_p.mRMessage(2047) << " " << name << endl;

		belts.at(belts.size()-1).createAsteroids();

		cout << mp_p.mRMessage(2048) << endl << endl;
		//Sleep(300);
	}

	else
	{
		belts.push_back(aBelt(name, size, true));
	}
}
			