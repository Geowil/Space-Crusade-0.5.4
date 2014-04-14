//External Headers
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <direct.h>
#include "datasystem.h"
#include "random.h"
#include "msgproc.h"
#include "debug.h"
#include "mining.h"

//Internal Header(s)
#include "game.h"

using namespace std;

//Story gStory;
dataSystem ds_g;
msgProc mp_g;
Station stat_g;
Debug d_g;
Mining mine;

Game::Game()
{
	nSPlanets = 15;
	nTStations = 25;
}

void Game::gSave(Player& mPlayer)
{
	cout << "Beginning saving process..." << endl;

	cout << "Opening save database..." << endl;

	bDSComplete = ds_g.sData(mPlayer, this);
	
	if (bDSComplete)
	{
		cout << "Player data saved successfully!" << endl;
		cout << endl;
		mp_g.mCScreen(true);
	}

	else
	{
		cout << "Saving did not complete successfully.  Check game log for more details" << endl;
		mp_g.mCScreen(true);
	}
}

void Game::gLoad(Player& mPlayer)
{
	cout << "Beginning loading process..." << endl;

	cout << "Opening the save database..." << endl;
	
	bDLComplete = ds_g.lData(mPlayer, this);
	
	if (bDLComplete)
	{
		cout << "Player data loaded successfully!" << endl;
		cout << endl;
		mp_g.mCScreen(true);
	}

	else
	{
		cout << "Loading did not complete successfully.  Check game log for more details" << endl;
		mp_g.mCScreen(true);
	}
}

void Game::getPNames()
{
	pNStorage.push_back(string());
	ds_g.getPNames(pNStorage);
}

void Game::generatePlanets()
{
	for(i = 1; pNStorage.size() > 1; i++) //No condition against i since we want to go until all of the names have been used or until the chosen number of planets has been reached
	{
		pNRand = Random(0,pNStorage.size()-1); //Random to the size of the names vector

		pDisRand = Random(1,4);

		if (pDisRand == 1)
		{
			tempDisp = "Allied";
		}

		else if (pDisRand == 2)
		{
			tempDisp = "Neutral";
		}

		else if (pDisRand == 3)
		{
			tempDisp = "Hostile";
		}
		
		/*else if (pDisRand == 4)
		{
			tempDisp = "Controlled";
		}*/

		pAffRand = Random(1,7);

		if (pAffRand == 1)
		{
			tempAffi = "Earth Alliance";
			tempRace = "Human";
			tempDisp = "Allied"; //Override tempDisp from earlier for story related elements at start of game
		}

		else if (pAffRand == 2)
		{
			tempAffi = "Sluikan Imperium";
			tempRace = "Sluikan";
			tempDisp = "Hostile";
		}

		else if (pAffRand == 3)
		{
			tempAffi = "Juslorth Empire";
			tempRace = "Juslorth";
			tempDisp = "Hostile";
		}

		else if (pAffRand == 4)
		{
			tempAffi = "Visar Collectorate";
			tempRace = "Visar";
		}

		else if (pAffRand == 5)
		{
			tempAffi = "Adent Council";
			tempRace = "Adent";
		}

		else if (pAffRand == 6)
		{
			tempAffi = "Prokl Unity";
			tempRace = "Prokl";
		}

		else if (pAffRand == 7)
		{
			tempAffi = "Groz Hermiteag";
			tempRace = "Groz";
		}


		gPlanets.push_back(Planet(i,pNStorage.at(pNRand),tempDisp,tempAffi, tempRace)); //Create a planet with the choosen name
		
		pNStorage.erase(pNStorage.begin()+pNRand); //Remove the name from the names vector

		//Start Planet Info Setup

		//EKS and Size Range Randomization
		pERand = fRandom(1.0f,5500.0f);
		pSRRand = Random(1,1000);

		pERand = pERand * 0.001; //Convert random EKS value to a proper format

		bPPGen = false; //So while loops will run

		//Type 0
		if ((pERand >= 0.0f) && (pERand <= 0.9f))
		{
			while (!bPPGen) //While planet pop has not been generated
			{
				pSRand = fRandom(1.0f,2.5f); //Randomize the planet size and then get to checking

				if ((pSRRand >= 450) && (pSRRand <= 625)) //If planet size range is within the range of 450 and 625 continue
				{
					if (pSRand < 1.2f || pSRand > 1.8f) //If planet size is outside of the range of 1.2 to 1.8 continue otherwise reroll the size rand on next loop
					{
						pPStore = calcPop(); //Calculate the population and return to pPStore
						pPMax = (long long int)pPStore; //Convert pPStore to a lli and save to pPMax
						bPPGen = true; //Pop has been generated so set to true
					}

				}

				else if (pSRRand < 450 || pSRRand > 625) //If planet size range is outside of the range of 450 to 625 continue
				{
					if ((pSRand >= 1.2f) && (pSRand <= 1.8f)) //If planet size is within the range of 1.2 and 1.8 continue otherwise reroll the size rand on next loop
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}

		//Type 1
		else if ((pERand >= 1.0f) && (pERand <= 1.9f))
		{
			while (!bPPGen)
			{
				pSRand = fRandom(1.9f,3.0f);

				if ((pSRRand >= 450) && (pSRRand <= 625))
				{
					if (pSRand < 2.0f || pSRand > 2.3f)
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}

				}

				else if (pSRRand < 450 || pSRRand > 625)
				{
					if ((pSRand >= 2.0f) && (pSRand <= 2.3f))
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}


		//Type 2
		else if ((pERand >= 2.0f) && (pERand <= 2.9f))
		{
			while (!bPPGen)
			{
				pSRand = fRandom(2.4f,5.3f);

				if ((pSRRand >= 450) && (pSRRand <= 625))
				{
					if (pSRand < 2.8f || pSRand > 4.1f)
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}

				}

				else if (pSRRand < 450 || pSRRand > 625)
				{
					if ((pSRand >= 2.8f) && (pSRand <= 4.1f))
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}

		//Type 3
		else if ((pERand >= 3.0f) && (pERand <= 3.9f))
		{
			while (!bPPGen)
			{
				pSRand = fRandom(4.2f,7.7f);

				if ((pSRRand >= 450) && (pSRRand <= 625))
				{
					if (pSRand < 4.8f || pSRand > 6.9f)
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}

				}

				else if (pSRRand < 450 || pSRRand > 625)
				{
					if ((pSRand >= 4.8f) && (pSRand <= 6.9f))
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}

		//Type 4
		else if ((pERand >= 4.0f) && (pERand <= 4.9f))
		{
			while (!bPPGen)
			{
				pSRand = fRandom(7.0f,8.4f);

				if ((pSRRand >= 450) && (pSRRand <= 625))
				{
					if (pSRand < 7.5f || pSRand > 7.9f)
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}

				}

				else if (pSRRand < 450 || pSRRand > 625)
				{
					if ((pSRand >= 7.5f) && (pSRand <= 7.9f))
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}

		//Type 5
		else if (pERand > 4.9f)
		{
			while (!bPPGen)
			{
				pSRand = fRandom(8.0f,10.0f);

				if ((pSRRand >= 450) && (pSRRand <= 625))
				{
					if (pSRand < 8.8f || pSRand > 9.7f)
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}

				}

				else if (pSRRand < 450 || pSRRand > 625)
				{
					if ((pSRand >= 8.8f) && (pSRand <= 9.7f))
					{
						pPStore = calcPop();
						pPMax = (long long int)pPStore;
						bPPGen = true;
					}
				}
			}
		}

		gPlanets.at(i-1).setEKS(pERand); //Set planet EKS value
		gPlanets.at(i-1).setSize(pSRand); //Set planet size
		gPlanets.at(i-1).updatePop(pPMax,"set"); //Set planet population
		gPlanets.at(i-1).updateMPop(pPMax,"set"); //Set planet max population
		
		getDefenses(Random(1,100), pERand);
		getShields(Random(1,100), pERand);

		if (numODef > 0)
		{
			addDefenses(i-1, pERand);
		}

		if (numOShd > 0)
		{
			addShields(i-1, pERand);		
		}

		gPlanets.at(i-1).createBelts();
	}
}

float Game::calcPop()
{
	//Randomize population rands
	popRand1 = Random(1,60);
	popRand2 = Random(1,100);
	popRand3 = Random(1,260);

	return ((((((8000 * popRand1) * popRand2) * pERand) * pSRand) * popRand3) / 6);
}

void Game::getDefenses(int rand, float eks)
{
	if ((eks > 0.0f) && (eks < 1.0f)) //Type 0 Planet
	{
		if ((rand >= 1) && (rand <= 35)) //36% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 36) && (rand <= 60)) //25% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 61) && (rand <= 78)) //18% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 79) && (rand <= 87)) //7% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 88) && (rand <= 94)) //7% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 95) && (rand <= 98)) //4% chance for 5 defenses
		{
			numODef = 5;
		}

		else if (rand >= 99) //2% Chance for 6 defenses
		{
			numODef = 6;
		}
	}

	else if ((eks >= 1.0f) && (eks < 2.0f)) //Type 1 Planet
	{
		if ((rand >= 1) && (rand <= 28)) //29% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 28) && (rand <= 55)) //28% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 56) && (rand <= 71)) //16% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 72) && (rand <= 82)) //11% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 83) && (rand <= 90)) //8% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 91) && (rand <= 96)) //7% chance for 5 defenses
		{
			numODef = 5;
		}

		else if (rand >= 97) //4% Chance for 6 defenses
		{
			numODef = 6;
		}
	}

	else if ((eks >= 2.0f) && (eks < 3.0f)) //Type 2 Planet
	{
		if ((rand >= 1) && (rand <= 28)) //29% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 29) && (rand <= 56)) //28% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 57) && (rand <= 70)) //14% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 71) && (rand <= 82)) //12% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 83) && (rand <= 91)) //9% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 92) && (rand <= 96)) //5% chance for 5 defenses
		{
			numODef = 5;
		}

		else if (rand >= 97) //4% Chance for 6 defenses
		{
			numODef = 6;
		}
	}

	else if ((eks >= 3.0f) && (eks < 4.0f)) //Type 3 Planet
	{
		if ((rand >= 1) && (rand <= 20)) //21% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 21) && (rand <= 46)) //26% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 47) && (rand <= 68)) //19% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 68) && (rand <= 80)) //13% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 81) && (rand <= 89)) //9% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 90) && (rand <= 95)) //6% chance for 5 defenses
		{
			numODef = 5;
		}

		else if ((rand >= 96) && (rand <= 98)) //3% chance for 6 defenses
		{
			numODef = 6;
		}

		else if (rand >= 99) //2% chance for 7 defenses
		{
			numODef = 7;
		}
	}

	else if ((eks >= 4.0f) && (eks < 5.0f)) //Type 4 Planet
	{
		if ((rand >= 1) && (rand <= 18)) //19% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 19) && (rand <= 35)) //15% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 36) && (rand <= 55)) //20% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 56) && (rand <= 68)) //13% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 69) && (rand <= 80)) //12% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 81) && (rand <= 89)) //9% chance for 5 defenses
		{
			numODef = 5;
		}

		else if ((rand >= 90) && (rand <= 95)) //6% chance for 6 defenses
		{
			numODef = 6;
		}

		else if (rand >= 96) //5% chance for 7 defenses
		{
			numODef = 7;
		}
	}

	else if (eks >= 5.0f) //Type 5 Planet
	{
		if ((rand >= 1) && (rand <= 12)) //13% chance for 0 defenses
		{
			numODef = 0;
		}

		else if ((rand >= 13) && (rand <= 28)) //16% chance for 1 defense
		{
			numODef = 1;
		}

		else if ((rand >= 29) && (rand <= 48)) //20% chance for 2 defenses
		{
			numODef = 2;
		}

		else if ((rand >= 49) && (rand <= 62)) //14% chance for 3 defenses
		{
			numODef = 3;
		}

		else if ((rand >= 63) && (rand <= 74)) //12% chance for 4 defenses
		{
			numODef = 4;
		}

		else if ((rand >= 75) && (rand <= 85)) //11% chance for 5 defenses
		{
			numODef = 5;
		}

		else if ((rand >= 86) && (rand <= 92)) //9% chance for 6 defenses
		{
			numODef = 6;
		}

		else if ((rand >= 93) && (rand <= 97)) //5% chance for 7 defenses
		{
			numODef = 7;
		}

		else if (rand >= 98) //3% chance for 8 defenses
		{
			numODef = 8;
		}
	}
}

void Game::getShields(int rand, float eks)
{
	if ((eks > 0.0f) && (eks < 1.0f)) //Type 0 Planet
	{
		if ((rand >= 1) && (rand <= 60)) //61% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 61) && (rand <= 86)) //26% chance for 1 shields
		{
			numOShd = 1;
		}

		else if (rand >= 86) //17% chance for 2 shields
		{
			numOShd = 2;
		}
	}

	else if ((eks >= 1.0f) && (eks < 2.0f)) //Type 1 Planet
	{
		if ((rand >= 1) && (rand <= 52)) //53% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 53) && (rand <= 84)) //22% chance for 1 shields
		{
			numOShd = 1;
		}

		else if (rand >= 85) //15% chance for 2 shields
		{
			numOShd = 2;
		}
	}

	else if ((eks >= 2.0f) && (eks < 3.0f)) //Type 2 Planet
	{
		if ((rand >= 1) && (rand <= 35)) //36% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 36) && (rand <= 68)) //33% chance for 1 shields
		{
			numOShd = 1;
		}

		else if ((rand >= 69) && (rand <= 87)) //18% chance for 2 shields
		{
			numOShd = 2;
		}

		else if (rand >= 88) //13% chance for 3 shields
		{
			numOShd = 3;
		}
	}

	else if ((eks >= 3.0f) && (eks < 4.0f)) //Type 3 Planet
	{
		if ((rand >= 1) && (rand <= 27)) //28% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 28) && (rand <= 64)) //27% chance for 1 shields
		{
			numOShd = 1;
		}

		else if ((rand >= 64) && (rand <= 84)) //21% chance for 2 shields
		{
			numOShd = 2;
		}

		else if (rand >= 85) //16% chance for 3 shields
		{
			numOShd = 3;
		}
	}

	else if ((eks >= 4.0f) && (eks < 5.0f)) //Type 4 Planet
	{
		if ((rand >= 1) && (rand <= 20)) //21% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 21) && (rand <= 48)) //28% chance for 1 shields
		{
			numOShd = 1;
		}

		else if ((rand >= 49) && (rand <= 74)) //26% chance for 2 shields
		{
			numOShd = 2;
		}

		else if ((rand >= 75) && (rand <= 88)) //14% chance for 3 shields
		{
			numOShd = 3;
		}

		else if (rand >= 89) //12% chance for 4 shields
		{
			numOShd = 4;
		}
	}

	else if (eks >= 5.0f) //Type 5 Planet
	{
		if ((rand >= 1) && (rand <= 18)) //19% chance for 0 shields
		{
			numOShd = 0;
		}

		else if ((rand >= 19) && (rand <= 36)) //18% chance for 1 shields
		{
			numOShd = 1;
		}

		else if ((rand >= 37) && (rand <= 65)) //29% chance for 2 shields
		{
			numOShd = 2;
		}

		else if ((rand >= 66) && (rand <= 84)) //19% chance for 3 shields
		{
			numOShd = 3;
		}

		else if (rand >= 85) //16% chance for 4 shields
		{
			numOShd = 4;
		}
	}
}

void Game::addDefenses(int i, float eks)
{
	if ((eks > 0.0f) && (eks < 1.0f)) //Type 0 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,103),false,0,false);
		}
	}

	else if ((eks >= 1.0f) && (eks < 2.0f)) //Type 1 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,106),false,0,false);
		}
	}

	else if ((eks >= 2.0f) && (eks < 3.0f)) //Type 2 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,109),false,0,false);
		}
	}

	else if ((eks >= 3.0f) && (eks < 4.0f)) //Type 3 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,112),false,0,false);
		}
	}

	else if ((eks >= 4.0f) && (eks < 5.0f)) //Type 4 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,115),false,0,false);
		}
	}

	else if (eks >= 5.0f) //Type 5 Planet
	{
		for (i2 = 0; i2 < numODef; i2++)
		{
			gPlanets.at(i).addPDefenses(true,Random(101,118),false,0,false);
		}
	}
}

void Game::addShields(int i, float eks)
{
	if ((eks > 0.0f) && (eks < 1.0f)) //Type 0 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,3),false);
		}
	}

	else if ((eks >= 1.0f) && (eks < 2.0f)) //Type 1 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,6),false);
		}
	}

	else if ((eks >= 2.0f) && (eks < 3.0f)) //Type 2 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,9),false);
		}
	}

	else if ((eks >= 3.0f) && (eks < 4.0f)) //Type 3 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,12),false);
		}
	}

	else if ((eks >= 4.0f) && (eks < 5.0f)) //Type 4 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,15),false);
		}
	}

	else if (eks >= 5.0f) //Type 5 Planet
	{
		for (i2 = 0; i2 < numOShd; i2++)
		{
			gPlanets.at(i).addPDefenses(false,0,true,Random(1,18),false);
		}
	}
}

bool Game::isDest(int id)
{
	if (gPlanets.at(id).bPIsDest())
	{
		return true;
	}

	else
	{
		return false;
	}
}

void Game::iSPlanets()
{
	for (i = 0; i < nSPlanets; i++)
	{
		sPlanets.push_back(Planet());

		sPlanets.at(i).setName("Default");
	}
}

void Game::rSPlanets()
{
	sPlanets.clear();
}

/*bool Game::isOwned()
{

}*/

void Game::fPlanets()
{
	for (i = 0; i < sPlanets.size();)
	{
		pRID = Random(1, gPlanets.size());

		if (!gPlanets.at(pRID-1).bPIsDest())
		{
			for(i2 = 0; i2 <= sPlanets.size(); i2++)
			{
				if ((i2 == sPlanets.size()) && (sPlanets.at(i).getName() == "Default")) //Only add the planet to sPlanets if no element in sPlanets is the same as gPlanets.at(pRID) and the sPlanets element does not already have a planet in it
				{
					sPlanets.at(i).setPID(gPlanets.at(pRID-1).getPID());
					sPlanets.at(i).setName(gPlanets.at(pRID-1).getName());
					sPlanets.at(i).setEKS(gPlanets.at(pRID-1).getEKS());
					sPlanets.at(i).setAffil(gPlanets.at(pRID-1).getAffil());
					sPlanets.at(i).setDispo(gPlanets.at(pRID-1).getDispo());
					sPlanets.at(i).setRace(gPlanets.at(pRID-1).getRace());
					sPlanets.at(i).setSize(gPlanets.at(pRID-1).getSize());
					sPlanets.at(i).updatePop(gPlanets.at(pRID-1).getPop(), "set");
					sPlanets.at(i).updateMPop(gPlanets.at(pRID-1).getMPop(), "set");
					
					if (gPlanets.at(pRID-1).pDef.size() > 0)
					{
						for (i3 = 0; i3 < gPlanets.at(pRID-1).pDef.size(); i3++)
						{
							sPlanets.at(i).addPDefenses(true, gPlanets.at(pRID-1).pDef.at(i3).getID(), false, 0, false);
						}
					}

					if (gPlanets.at(pRID-1).pShd.size() > 0)
					{
						for (i3 = 0; i3 < gPlanets.at(pRID-1).pShd.size(); i3++)
						{
							sPlanets.at(i).addPDefenses(false, 0, true, gPlanets.at(pRID-1).pShd.at(i3).getID(), false);
						}
					}

					sPlanets.at(i).setTDist(Random(8,50)); //Set the travel distance				

					i += 1; //iterate i in first for loop
					break;
				}

				else if (sPlanets.at(i2).getName() == gPlanets.at(pRID-1).getName()) //If the randomly picked planet already exists in sPlanets then break this loop
				{
					break;
				}

				else if (sPlanets.at(i).getName() != "Default") //If for some reason the current element is NOT default; as a safty precausion in case of weirdness
				{
					i += 1; //Increment the first for loop and break the second
					break;
				}
			}
		}
	}
}

int Game::pPlanets(Player& mPlayer)
{	
	pChoice = mp_g.gGTPlanet(sPlanets, mPlayer);
	mp_g.mCScreen(false);

	if (pChoice != -1)
	{
		return pChoice;
	}

	else
	{
		return -1;
	}
}

void Game::getDList()
{
	cout << "The following planets have been listed as destroyed:" << endl;
	for (i = 0; i < gPlanets.size(); i++)
	{
		if (gPlanets.at(i).bPIsDest())
		{
			cout << gPlanets.at(i).getName() << endl;
		}
	}
}

string Game::getDPlanet(int i)
{
	return pDestPlan.at(i).getName();
}

void Game::setSDPlanet(int i, string name)
{
	pDestPlan.at(i).setName(name);
}

/*void Game::setPOwned(string plname)
{

}

void getOPlanets()
{

}*/

void Game::loadPlanet(planetData plData)
{
	gPlanets.push_back(Planet());

	gPlanets.at(gPlanets.size()-1).setPID(plData.pID); //Planet ID
	gPlanets.at(gPlanets.size()-1).setName(plData.pName);
	gPlanets.at(gPlanets.size()-1).setAffil(plData.pAffiliation);
	gPlanets.at(gPlanets.size()-1).setDispo(plData.pDispo);
	gPlanets.at(gPlanets.size()-1).setRace(plData.pRace);
	gPlanets.at(gPlanets.size()-1).setPPOwned(plData.bIsPOwned);
	gPlanets.at(gPlanets.size()-1).setPDest(plData.bIsDestroyed);
	gPlanets.at(gPlanets.size()-1).setEKS(plData.pEKS);
	gPlanets.at(gPlanets.size()-1).setSize(plData.pSize);
	gPlanets.at(gPlanets.size()-1).updatePop(plData.pCPop, "set");
	gPlanets.at(gPlanets.size()-1).updateMPop(plData.pMPop, "set");
}

void Game::pMenu(Player& mPlayer, Planet* gPlanet, Game& mGame_m, string* eResult, Map& m_m, battleProc& bp_m, NPC& mNPC)
{
	bDone = false;

	if (!m_m.shipEncounter(gPlanet->getTDist())) //If no ships are encountered
	{
		while (!bDone)
		{
			pChoice = mp_g.plMenu1();

			switch(pChoice)
			{
			case 1:
				gPHail1(mPlayer, gPlanet);
				break;

			case 2:
				gFABelts(mPlayer, gPlanet);
				break;

			case 3:
				mp_g.hBSStatus_PB(gPlanet,false,0,false,0,true);
				break;

			case 4:
				*eResult = bp_m.pBLoop(mPlayer,gPlanet, mGame_m); //Then contniue to planet.  -1 because of the way generatePlanets generates the planet ID
				bDone = true;
				break;

			case 5:
				*eResult = "No Battle";
				bDone = true;
				break;
			}
		}
	}

	else //Else if ship is encountered
	{
		*eResult = bp_m.sBLoop(mPlayer,gPlanet, false, mGame_m, mNPC); //Load ship encounter events
		bDone = true;
	}
}

void Game::gPHail1(Player& mPlayer, Planet* gPlanet)
{
	//First we need to determine if the planet will attack the player on intilization.  This only happens for planets that belong to entities that are enemies.  Check affiliation of planet against the affinity of that affil with the player relations; if it does not exist create it
	for (i = 0; i <= mPlayer.pRelations.size(); i++)
	{
		if (i == mPlayer.pRelations.size()) //If the player has not yet met whomever is in control of this planet
		{
			mPlayer.addRelation(gPlanet->getAffil(),Random(-20,20)); //Then create the relation
		}

		if (gPlanet->getAffil() == mPlayer.pRelations.at(i).getRName()) //If the player has met whomever is in control of this planet
		{
			
		}
	}

	string affiliation = gPlanet->getAffil();
	string prace = gPlanet->getRace();

	//Check to see if this target's affiliation has made contact with player before
	int tAffinity = mPlayer.getRStatus(affiliation);
	
	//get hail response from message proc
	bool bTResponded = mp_g.bHail1(affiliation, prace , tAffinity);

	if (bTResponded)
	{
		pChoice = mp_g.bHail2(tAffinity);

		switch (pChoice)
		{
		case 1:
			if (mp_g.bHail3(tAffinity,pChoice,prace,affiliation))
			{
				//mp.bHInfo(tAffinity,race);
				cout << mp_g.mRMessage(2001) << endl;
				//bITNHostile = true;
			}

			//bITNHostile = true;
			break;

		case 2:			
			if (mp_g.bHail3(tAffinity, pChoice, prace, affiliation))
			{
				//mp.bHEnemies(race);
				cout << mp_g.mRMessage(2001) << endl;
				//bITNHostile = true;
			}

			//bITNHostile = true;
			break;

		case 3:
			if (mp_g.bHail3(tAffinity, pChoice, prace, affiliation))
			{
				//mp.bHSurrender(tAffinity,race);
				//bDTSurrender = true;

				cout << mp_g.mRMessage(2001) << endl;
			}

			else
			{
				//bITNHostile = false;
				cout << mp_g.mRMessage(2001) << endl;
			}

			break;

		case 4:
			//pChoice2 = mp.bHTrade();
			//Start trade dialog; created class, start from there after stations re-added
			cout << mp_g.mRMessage(2001) << endl; //Temp until 0.6A
			break;

		case 5:
			
			//mp.bHNothing();
			//bITNHostile = true;
			cout << mp_g.mRMessage(2001) << endl;
			break;

		default:
			if (mp_g.bHail3(tAffinity,1,prace,affiliation))
			{
				//mp.bHInfo(tAffinity,race);
				cout << mp_g.mRMessage(2001) << endl;
				//bITNHostile = true;
			}

			//bITNHostile = true;
			break;
		}
	}
	
	/*else
	{
		cout << mp_g.mRMessage(2000) << endl;
		bITNHostile = true;
	}

	if (bDTSurrender) //If enemy surrenders end the battle and break the while loop
	{
		bEnd = true;
		bpResult = "No Battle";
		break;
	}

	else if ((!bDTSurrender) && (mPlayer.getRStatus(gPlanet->getAffil()) <= -23)) //If enemy does not surrender then the battle starts only if suspicious or higher; deals with this causing the game to bug out with erroneous battle
	{
		bEnd = false; 
		bPBattle = true;
	}

	if (bDTTrade) //If the planet engaged in trade end the battle and break the loop
	{
		bEnd = true;
		bpResult = "No Battle";
		break;
	}

	else if (bITNHostile) //If the planet did not take a hostile act end the battle and break the loop
	{
		bEnd = true;
		bpResult = "No Battle";
		break;
	}

	else if (bEnd) //If player escaped end the battle and break the loop
	{
		bDPEscape = true;
		bpResult = "Escaped";
		break;
	}*/
}

/*void Game::gPHail2(string race, string affiliation, Player& mPlayer)
{
	

	if (bTResponded)
	{
		pChoice = mp.bHail2(tAffinity);

		switch (pChoice)
		{
		case 1:
			if (mp.bHail3(tAffinity,pChoice,race,affiliation))
			{
				//mp.bHInfo(tAffinity,race);
				cout << mp.mRMessage(2001) << endl;
				bITNHostile = true;
			}

			bITNHostile = true;
			break;

		case 2:			
			if (mp.bHail3(tAffinity, pChoice, race, affiliation))
			{
				//mp.bHEnemies(race);
				cout << mp.mRMessage(2001) << endl;
				bITNHostile = true;
			}

			bITNHostile = true;
			break;

		case 3:
			if (mp.bHail3(tAffinity, pChoice, race, affiliation))
			{
				//mp.bHSurrender(tAffinity,race);
				bDTSurrender = true;
			}

			else
			{
				bITNHostile = false;
			}

			break;

		case 4:
			//pChoice2 = mp.bHTrade();
			//Start trade dialog; created class, start from there after stations re-added
			cout << mp.mRMessage(2001) << endl; //Temp until 0.6A
			break;

		case 5:
			mp.bHail3(tAffinity,pChoice,race,affiliation);

			//mp.bHNothing();
			bITNHostile = true;
			break;

		default:
			if (mp.bHail3(tAffinity,1,race,affiliation))
			{
				//mp.bHInfo(tAffinity,race);
				cout << mp.mRMessage(2001) << endl;
				bITNHostile = true;
			}

			bITNHostile = true;
			break;
		}
	}
	
	else
	{
		cout << mp.mRMessage(2000) << endl;
		bITNHostile = true;
	}
	
	//response = hResponse
}*/

void Game::gFABelts(Player& mPlayer, Planet* gPlanet)
{
	pChoice = mp_g.gGTABelt(gPlanet);

	if (pChoice != -1)
	{
		mine.mLoop(mPlayer, &gPlanet->belts.at(pChoice));
	}
}

//Station Processing Functions

void Game::createStation(string name, Player& mPlayer)
{	
	gStations.push_back(Station());

	pAffRand = Random(1,7);

	if (pAffRand == 1)
	{
		tempAffi = "Earth Alliance";
		tempRace = "Human";
	}

	else if (pAffRand == 2)
	{
		tempAffi = "Sluikan Imperium";
		tempRace = "Sluikan";
	}

	else if (pAffRand == 3)
	{               
		tempAffi = "Juslorth Empire";
		tempRace = "Juslorth";
	}

	else if (pAffRand == 4)
	{
		tempAffi = "Visar Collectorate";
		tempRace = "Visar";
	}

	else if (pAffRand == 5)
	{
		tempAffi = "Adent Council";
		tempRace = "Adent";
	}

	else if (pAffRand == 6)
	{
		tempAffi = "Prokl Unity";
		tempRace = "Prokl";
	}

	else if (pAffRand == 7)
	{
		tempAffi = "Groz Hermiteag";
		tempRace = "Groz";
	}

	for (i = 0; i <= mPlayer.pRelations.size(); i++)
	{
		if (i == mPlayer.pRelations.size()) //If relation does not yet exist
		{
			pAffRand = Random(-20, 20); //Create the affinity and then

			mPlayer.addRelation(tempAffi, pAffRand); //Add it

			tempDisp = mPlayer.pRelations.at(i).getAffinityS(); //Get the string version of the affinity
			break;
		}

		else if (tempAffi == mPlayer.pRelations.at(i).getRName()) //Else if the relation does exist
		{
			tempDisp = mPlayer.pRelations.at(i).getAffinityS(); //Get the string version of the affinity
			break;
		}
	}

	stlevel = Random(1,10);

	sslevel = Random(1,20);

	gStations.at(gStations.size()-1).initStation(gStations.size(), name, stlevel, sslevel, 1.0f, tempDisp, tempAffi);
}

void Game::iTStations()
{
	for (i = 0; i < nTStations; i++)
	{
		tStats.push_back(Station());

		tStats.at(i).setName("Default");
	}
}

void Game::rTStations()
{
	tStats.clear();
}

//TODO: Add a way to check gStations to see if the station is already created.

void Game::fStations()
{
	if (tStats.size() == 0)
	{

	}

	else 
	{
		for (i = 0; i < tStats.size();) //Loop this this n times until all elements are filled.  Iteration takes place in the second for loop
		{
			nTSPID = Random(1, gPlanets.size());

			nTSSV = Random(1,5);

			switch(nTSSV)
			{
			case 1:
				nTSSuffix = "Alpha";
				break;

			case 2:
				nTSSuffix = "Beta";
				break;

			case 3:
				nTSSuffix = "Chi";
				break;

			case 4:
				nTSSuffix = "Delta";
				break;

			case 5:
				nTSSuffix = "Epsilon";
				break;
			}


			for (i2 = 0; i2 <= tStats.size(); i2++) //Loop through tStats here in order to determine if iteration of first loop is valid
			{
				if (i2 == 0) //Only on the first time through to save cpu cycles
				{
					for (i3 = 0; i3 < gStations.size();i3++) //Checking gStations for already existing stations
					{
						if (gPlanets.at(nTSPID-1).getName() + " " + nTSSuffix == gStations.at(i3).getName()) //If the randomly selected station exists
						{
							tStats.at(i) = gStations.at(i3); //Then set that station to tStats
							break;
						}
					}
				}

				if ((i2 == tStats.size()) && (tStats.at(i).getName() == "Default")) //Only add the planet to sPlanets if no element in sPlanets is the same as gPlanets.at(pRID) and the sPlanets element does not already have a planet in it
				{
					tStats.at(i).setName(gPlanets.at(nTSPID-1).getName() + " " + nTSSuffix);
					i += 1;
					break;
				}				

				else if (gPlanets.at(nTSPID-1).getName() + " " + nTSSuffix == tStats.at(i2).getName()) //If the randomly picked planet already exists in sPlanets then break this loop
				{
					break;
				}
				
				else if (tStats.at(i).getName() != "Default") //This is here for the result of the third for loop.  Since stuff above this but under the third for loop requires non-modified i value, we need to do it here
				{
					i += 1; //iterate i in first for loop
					break;
				}
			}
		}
	}
}

int Game::pStations(Player& mPlayer)
{	
	pChoice = mp_g.gGTStation(tStats, mPlayer, this);

	if (pChoice != -1)
	{
		return pChoice;
	}

	else
	{
		return -1;
	}
}


void Game::sRepair(Player& mPlayer, Station& stat_g)
{
	cout << mp_g.mRMessage(2009) << endl;
	mp_g.mCScreen(true);
	
	pChoice = mp_g.sDRMenu1(mPlayer);

	if (pChoice != 5)
	{
		for (i = 0; i <= mPlayer.pRelations.size(); i++) //Get affinity
		{
			if (i == mPlayer.pRelations.size()) //Always check to see if a realtion does not already exist first and add it if it does not
			{
				mPlayer.addRelation(stat_g.getAffil(), Random(-20,20));
			
				pAffin = mPlayer.pRelations.at(mPlayer.pRelations.size()-1).getAffinity(); //Do this now
				break;
			}

			else if (mPlayer.pRelations.at(i).getRName() == stat_g.getAffil())
			{
				pAffin = mPlayer.pRelations.at(i).getAffinity();
				break;
			}
		}

		//Set Up CPP Here
		if(pAffin >= 77)
		{
			sRCPPX = 2;
			sRCPPR = 1;
			sRCPPDi = 1;
			sRCPPD = 3;
		}

		else if ((pAffin <= 74) && (pAffin >= 52))
		{
			sRCPPX = 4;
			sRCPPR = 2;
			sRCPPDi = 1;
			sRCPPD = 7;
		}

		else if ((pAffin <= 51) && (pAffin >= 26))
		{
			sRCPPX = 5;
			sRCPPR = 3;
			sRCPPDi = 3;
			sRCPPD = 8;
		}

		else if ((pAffin <= 25) && (pAffin >= 1))
		{
			sRCPPX = 8;
			sRCPPR = 5;
			sRCPPDi = 4;
			sRCPPD = 10;
		}

		else if (pAffin == 0)
		{
			sRCPPX = 10;
			sRCPPR = 6;
			sRCPPDi = 7;
			sRCPPD = 11;
		}

		else if ((pAffin  <= -1) && (pAffin >= -22))
		{
			sRCPPX = 13;
			sRCPPR = 9;
			sRCPPDi = 8;
			sRCPPD = 12;
		}

		else if ((pAffin <= -23) && (pAffin >= -48))
		{
			sRCPPX = 18;
			sRCPPR = 11;
			sRCPPDi = 10;
			sRCPPD = 16;
		}

		else if ((pAffin <= -49) && (pAffin >= -74))
		{
			sRCPPX = 22;
			sRCPPR = 16;
			sRCPPDi = 14;
			sRCPPD = 20;
		}

		else if (pAffin <= -75)
		{
			sRCPPX = 28;
			sRCPPR = 19;
			sRCPPDi = 20;
			sRCPPD = 35;
		}

		if (pChoice == 1)
		{
			bRepair = mp_g.sDRMenu2(pAffin, mPlayer, sRCPPX, sRCPPR, sRCPPDi, sRCPPD);

			if (bRepair)
			{
				//Calc percent of armor damaged then round it
				dPerc = (mPlayer.Ship.getSArmor() / mPlayer.Ship.getSMArmor()) * 100;

				dPerc_R = floor(dPerc * 100 + 0.5) / 100;
				dPerc_I = dPerc_R;

				if (dPerc_R >= dPerc_I + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
				{	
					dPerc_I += 1; //then round up
				}

				if (dPerc_I <= 0) //In case of fully depleted armor
				{
					dPerc_I = 100;
				}

				//Check to see if the player has the resources to repair
				if (mPlayer.getXarn () < sRCPPX*dPerc_I || mPlayer.getRubies () < sRCPPR*dPerc_I || mPlayer.getDia () < sRCPPDi*dPerc_I || mPlayer.getDrac() < sRCPPD*dPerc_I)
				{
					cout << mp_g.mRMessage(2013) << endl;
					cout << endl;
				}

				else
				{
					mPlayer.updateXarn(sRCPPX*dPerc_I, "sub");
					mPlayer.updateRubies(sRCPPR*dPerc_I, "sub");
					mPlayer.updateDia(sRCPPDi*dPerc_I, "sub");
					mPlayer.updateDrac(sRCPPD*dPerc_I, "sub");

					mPlayer.Ship.updateSArmor(mPlayer.Ship.getSMArmor(),"set");
				}
			}
		}

		else if (pChoice == 2)
		{
			bRepair = mp_g.sDRMenu3(pAffin, mPlayer, sRCPPX, sRCPPR, sRCPPDi, sRCPPD);

			if (bRepair)
			{
				//Calc percent of hull damaged then round it
				dPerc = (mPlayer.Ship.getSHull() / mPlayer.Ship.getSMHull()) * 100;

				dPerc_R = floor(dPerc * 100 + 0.5) / 100;
				dPerc_I2 = dPerc_R;

				if (dPerc_R >= dPerc_I2 + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
				{	
					dPerc_I2 += 1; //then round up
				}

				//Check to see if the player has the resources to repair
				if (mPlayer.getXarn () < sRCPPX*dPerc_I2 || mPlayer.getRubies () < sRCPPR*dPerc_I2 || mPlayer.getDia () < sRCPPDi*dPerc_I2 || mPlayer.getDrac() < sRCPPD*dPerc_I2)
				{
					cout << mp_g.mRMessage(2013) << endl;
					cout << endl;
				}

				else
				{
					mPlayer.updateXarn(sRCPPX*dPerc_I2, "sub");
					mPlayer.updateRubies(sRCPPR*dPerc_I2, "sub");
					mPlayer.updateDia(sRCPPDi*dPerc_I2, "sub");
					mPlayer.updateDrac(sRCPPD*dPerc_I2, "sub");

					mPlayer.Ship.updateSHull(mPlayer.Ship.getSMHull(),"set");
				}
			}
		}

		else if (pChoice == 3)
		{
			bRepair = mp_g.sDRMenu4(pAffin, mPlayer, sRCPPX, sRCPPR, sRCPPDi, sRCPPD);

			if (bRepair)
			{
				//Calc percent of armor damaged then round it
				dPerc = (mPlayer.Ship.getSArmor() / mPlayer.Ship.getSMArmor()) * 100;

				dPerc_R = floor(dPerc * 100 + 0.5) / 100;
				dPerc_I = dPerc_R;

				if (dPerc_R >= dPerc_I + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
				{	
					dPerc_I += 1; //then round up
				}

				if (dPerc_I <= 0) //In case of fully depleted armor
				{
					dPerc_I = 100;
				}

				//Calc percent of hull damaged then round it
				dPerc = (mPlayer.Ship.getSHull() / mPlayer.Ship.getSMHull()) * 100;

				dPerc_R = floor(dPerc * 100 + 0.5) / 100;
				dPerc_I2 = dPerc_R;

				if (dPerc_R >= dPerc_I2 + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
				{	
					dPerc_I2 += 1; //then round up
				}

				dPerc_T = dPerc_I + dPerc_I2;

				//Check to see if the player has the resources to repair
				if (mPlayer.getXarn () < sRCPPX*dPerc_T || mPlayer.getRubies () < sRCPPR*dPerc_T || mPlayer.getDia () < sRCPPDi*dPerc_T || mPlayer.getDrac() < sRCPPD*dPerc_T)
				{
					cout << mp_g.mRMessage(2024) << endl;
					cout << endl;
				}

				else
				{
					mPlayer.updateXarn(sRCPPX*dPerc_T, "sub");
					mPlayer.updateRubies(sRCPPR*dPerc_T, "sub");
					mPlayer.updateDia(sRCPPDi*dPerc_T, "sub");
					mPlayer.updateDrac(sRCPPD*dPerc_T, "sub");

					mPlayer.Ship.updateSArmor(mPlayer.Ship.getSMArmor(),"set");
					mPlayer.Ship.updateSHull(mPlayer.Ship.getSMHull(),"set");
				}
			}
		}

		else if (pChoice == 4)
		{
			mPlayer.Ship.sWSCenter(mPlayer);
		}
	}
}

void Game::bClone(Player& mPlayer, Station& stat_g)
{
	pChoice = mp_g.sBClone();

	if (pChoice != 0)
	{
		sMBClone(mPlayer, stat_g, pChoice);
	}
}

void Game::useClone(Player& mPlayer, int sID, int sIID, int iID)
{
	//First remove the clone from the station inventory slot
	gStations.at(sID).removeItem(sIID, 1);

	//Then Remove CEXP; hardcode based now but will as for range in later versions in an ini file
	if (iID == 1) //Most primitive clone; take off 12% of CXP
	{
		oldCXPTNL = mPlayer.calcOCXPTNL(mPlayer.getCELvl());
		mPlayer.updateCEXP(mPlayer.getCEXP()*0.12,"sub");

		if (oldCXPTNL > mPlayer.getCEXP()) //If using the clone cause the player's cEXP to drop below the level required for the player's current level
		{
			mPlayer.cELDown(); //Then de-level the player
			mPlayer.setCXPTNL(oldCXPTNL); //And set cexp to next level to the pervious level's value
		}
	}

	else if (iID == 2) //Most primitive clone; take off 12% of CXP
	{
		oldCXPTNL = mPlayer.calcOCXPTNL(mPlayer.getCELvl());
		mPlayer.updateCEXP(mPlayer.getCEXP()*0.10,"sub");

		if (oldCXPTNL > mPlayer.getCEXP()) //If using the clone cause the player's cEXP to drop below the level required for the player's current level
		{
			mPlayer.cELDown(); //Then de-level the player
			mPlayer.setCXPTNL(oldCXPTNL); //And set cexp to next level to the pervious level's value
		}
	}

	else if (iID == 3) //Most primitive clone; take off 12% of CXP
	{
		oldCXPTNL = mPlayer.calcOCXPTNL(mPlayer.getCELvl());
		mPlayer.updateCEXP(mPlayer.getCEXP()*0.07,"sub");

		if (oldCXPTNL > mPlayer.getCEXP()) //If using the clone cause the player's cEXP to drop below the level required for the player's current level
		{
			mPlayer.cELDown(); //Then de-level the player
			mPlayer.setCXPTNL(oldCXPTNL); //And set cexp to next level to the pervious level's value
		}
	}
}

void Game::sMOffice(Player& mPlayer)
{
	pChoice = mp_g.sMOMenu1();

	switch(pChoice)
	{
	case 1:
		pChoice = mp_g.sMOMenu2(&mID, mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			startMission(mPlayer);
		}
		
		break;

	case 2:
		pChoice = mp_g.sMOMenu3(mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			completeMission(mPlayer);
		}

		break;

	default:
		//Add exit message
		break;
	}
}

void Game::sBOffice(Player& mPlayer)
{
	pChoice = mp_g.sBOMenu1();

	switch(pChoice)
	{
	case 1:
		pChoice = mp_g.sBOMenu2(&mID, mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			startMission(mPlayer);
		}
		
		break;

	case 2:
		pChoice = mp_g.sBOMenu3(mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			completeMission(mPlayer);
		}

		break;

	default:
		//Add exit message
		break;
	}
}

void Game::sEAFOffice(Player& mPlayer)
{
	pChoice = mp_g.sEAFOMenu1();

	switch(pChoice)
	{
	case 1:
		pChoice = mp_g.sEAFOMenu2(&mID, mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			startMission(mPlayer);
		}
		
		break;

	case 2:
		pChoice = mp_g.sEAFOMenu3(mPlayer);

		if ((pChoice != 0) && (mID != 0))
		{
			completeMission(mPlayer);
		}

		break;

	default:
		//Add exit message
		break;
	}
}

void Game::startMission(Player& mPlayer)
{
	gMStart = mp_g.sSMission(mID);

	if (gMStart)
	{
		mPlayer.addMission(mID);
	}
}

void Game::completeMission(Player& mPlayer)
{
	mID = mp_g.sMOMenu3(mPlayer);

	if (mID != 0)
	{
		ds_g.rData("Mission_Data","select from", mPlayer.pMissions.at(mID).getMID());

		if (ds_g.getMType() == "Mining")
		{		
			if ((ds_g.getMRR() <= mPlayer.getRubies()) && (ds_g.getMDiR() <= mPlayer.getDia()) && (ds_g.getMDR() <= mPlayer.getDrac()) && (ds_g.getMLR() <= mPlayer.getLith()) && (ds_g.getMPlR() <= mPlayer.getPlat()) && (ds_g.getMUR() <= mPlayer.getUra()) && (ds_g.getMPR() <= mPlayer.getPlut()))
			{
				cout << mp_g.mRMessage(2013) << endl;

				//These are hardcoded for now but will be based on station values and exchange rates in 0.6a
				xarnMultiplier = Random(1.5,3.5);
				xarnReward = 0;
				
				if (ds_g.getMRR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMRR();
					mPlayer.updateRubies(ds_g.getMRR(), "sub");
				}

				if (ds_g.getMDiR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMDiR();
					mPlayer.updateDia(ds_g.getMDiR(), "sub");
				}

				if (ds_g.getMDR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMDR();
					mPlayer.updateDrac(ds_g.getMDR(), "sub");
				}
				
				if (ds_g.getMLR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMLR();
					mPlayer.updateLith(ds_g.getMLR(), "sub");
				}
				
				if (ds_g.getMPlR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMPlR();
					mPlayer.updatePlat(ds_g.getMPlR(), "sub");
				}

				if (ds_g.getMUR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMUR();
					mPlayer.updateUra(ds_g.getMUR(), "sub");
				}
				
				if (ds_g.getMPR() != 0)
				{
					xarnReward += xarnMultiplier * ds_g.getMPR();
					mPlayer.updatePlut(ds_g.getMPR(), "sub");
				}

				mPlayer.updateXarn(xarnReward, "add");

				mPlayer.completeMission(mID);
			}

			else
			{
				cout << mp_g.mRMessage(2014) << endl;
			}
		}

		else if (ds_g.getMType() == "Transport")
		{

		}

		else if (ds_g.getMType() == "Stock")
		{

		}

		else if (ds_g.getMType() == "Survey")
		{

		}

		else if (ds_g.getMType() == "Bounty")
		{
			if (mPlayer.getBOKills() > 0)
			{
				cout << mp_g.mRMessage(2015) << endl;

				mPlayer.updateXarn(ds_g.getMBounty(), "add");
			}

			else
			{
				cout << mp_g.mRMessage(2016) << endl;
			}
		}

		else if (ds_g.getMType() == "Main")
		{

		}

		else if (ds_g.getMType() == "EA")
		{

		}
	}
}

void Game::sPub(Player& mPlayer)
{
	cout << mp_g.mRMessage(2001) << endl;
}

void Game::sDepart(Player& mPlayer, Station& stat_g)
{
	cout << mp_g.mRMessage(14) << stat_g.getName() << ".  " << mp_g.mRMessage(15) << endl;
	gStations.at(csPos) = stat_g; //Update vector elemment with new data from stat instance
}

void Game::sMenu(Player& mPlayer, Station& stat_g)
{
	if (stat_g.getSID() == 0)
	{
		csPos = 0; //set position in cStations for updating vector element later on
	}

	else
	{
		csPos = stat_g.getSID() - 1; //set position in cStations for updating vector element later on
	}
	
	while (!sLeave) //Start Station Loop
	{
		pChoice = mp_g.sMMenu(stat_g); //Create main station menu

		switch (pChoice) //Start Station Menu
		{
		case 1:
			sRepair(mPlayer, stat_g);
			break;

		case 2: //Classification

			sMLoop1(mPlayer, stat_g); //Start Market Menu
			break;

		case 3: //Pub
			sPub(mPlayer);
			break;

		case 4: //Bounty Office
			sBOffice(mPlayer);
			break;

		case 5: //Earth Alliance Field Office
			sEAFOffice(mPlayer);
			break;

		case 6:
			bClone(mPlayer, stat_g);
			break;

		case 7:
			sCasino(mPlayer);
			break;

		case 8:
			sSItem(mPlayer, stat_g, false);
			break;

		case 9:
			sGItem(mPlayer, stat_g);
			break;

		case 10: //Leave Station
			sDepart(mPlayer,stat_g);
			sLeave = true;
			break;

		default: //Repair Dock
			sRepair(mPlayer,stat_g);
			break;
		} //End Station Menu
	} //End Station Loop

	sLeave = false;
}

void Game::sMLoop1(Player& mPlayer, Station& stat_g)
{
	pChoice = mp_g.sMBS();

	switch(pChoice)
	{
	case 1:
		sMLoop2A1(mPlayer,stat_g);
		break;

	case 2:
		sMLoop2B1(mPlayer,stat_g);
		break;

	default:
		break;
	}
}

//Buy
void Game::sMLoop2A1(Player& mPlayer, Station& stat_g)
{
	sMMenu = true; //Make sure this is true

	while (sMMenu) //Start Market Loop			
	{
		cCode = mp_g.sMCMenu(mPlayer); //Get ship classification
		pChoice = mp_g.sMMenu1A();

		switch (pChoice)
		{
		case 1: //Weapons
			sWMLoopB(mPlayer, stat_g); //Start Weapon Menu
			break;

		case 2: //Ships
			sSMLoopB(mPlayer, stat_g);
			break;

		case 3: //Equipment
			sEMLoopB(mPlayer, stat_g);
			break;

		default: //Back to staion menu
			sMMenu = false;
			break;
		}
	} //End Market Loop
}

void Game::sWMLoopB(Player& mPlayer, Station& stat_g)
{
	iType = "Weapon";
	bContinue = true; //Make sure that this is true

	while (bContinue) //Start Weapon Menu loop
	{
		pChoice = mp_g.sMMenu2();  //Return a weapon type

		switch (pChoice)
		{
		case 1: //Lasers
			iCode = mp_g.sWLMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = getIType(); //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 2:
			iCode = mp_g.sWMMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = getIType(); //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 3:
			iCode = mp_g.sWBMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = getIType(); //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 4:
			iCode = mp_g.sWRMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = getIType(); //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 5:
			iCode = mp_g.sWHMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = getIType(); //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 6:
			bContinue = false;
			break;
		}
	} //End Weapon Menu Loop
}

void Game::sSMLoopB(Player& mPlayer, Station& stat_g)
{
	iType = "Ship";
	bContinue = true; //Make sure that this is true

	while (bContinue) //Start Weapon Menu loop
	{
		iCode = mp_g.sMMenu8(cCode); //Choose a ship

		if (iCode != 0) //Only proceed if a selection was made
		{

			iType2 = ""; //Not needed for this item type

			sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


			if (sMBuy) //If player wants to buy
			{
				sMPurchase(mPlayer, stat_g);
			}
		}

		else
		{
			bContinue = false;
		}
	} //End Weapon Menu Loop
}

void Game::sEMLoopB(Player& mPlayer, Station& stat_g)
{
	iType = "Equipment";
	bContinue = true; //Make sure that this is true

	while (bContinue) //Start Weapon Menu loop
	{
		pChoice = mp_g.sMMenu2();  //Return a weapon type

		switch (pChoice)
		{
		case 1: //Items
			iCode = mp_g.sWLMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = "Item"; //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 2: //Modules
			iCode = mp_g.sMMenu9(cCode); //Choose a module

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = "Module"; //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 3: //Planetary Equipment - split into defense and shield
			iCode = mp_g.sWBMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = "PEquip"; //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;
			
		case 5: //Upgrades
			iCode = mp_g.sWHMenu(cCode); //Choose an item

			if (iCode != 0) //Only proceed if a selection was made
			{
				
				iType2 = "Upgrades"; //Get type of weapon
				
				sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, 1); //Print out item information


				if (sMBuy) //If player wants to buy
				{
					sMPurchase(mPlayer, stat_g);					
				}
			}

			break;

		case 6:
			bContinue = false;
			break;
		}
	} //End Weapon Menu Loop
}

void Game::sMBClone(Player& mPlayer, Station& stat_g, int iID)
{
	iCode = iID; //Set the class member here, no need to pass the value any further

	sMBuy = mp_g.sMIInfo(iCode,"Equipment","Clone", mPlayer, stat_g, 1); //Print out item information

	if (sMBuy)
	{
		//Since the player has already decided to buy the item call sMPurchase
		iType = "Equipment";
		iType2 = "Clone";
		sMPurchase(mPlayer, stat_g);
	}
}

void Game::sRMLoopB(Player& mPlayer, Station& stat_g)
{
	iType = "Resource";
	bContinue = true; //Make sure that this is true

	while (bContinue) //Start Weapon Menu loop
	{
		iCode = mp_g.sMBRes(); //Choose a resource

		if (iCode != 0) //Only proceed if a selection was made
		{

			iType2 = ""; //Not needed for this item type

			amount = mp_g.sMBAmount(iCode, iType, mPlayer, stat_g); //Get player to choose the number of items to buy

			sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, amount); //Print out item information


			if (sMBuy) //If player wants to buy
			{
				sMPurchase(mPlayer, stat_g);
			}
		}

		else
		{
			bContinue = false;
		}
	}
}

void Game::sOMLoopB(Player& mPlayer, Station& stat_g)
{
	iType = "Ore";
	bContinue = true; //Make sure that this is true

	while (bContinue) //Start Weapon Menu loop
	{
		iCode = mp_g.sMBOre(); //Choose an ore

		if (iCode != 0) //Only proceed if a selection was made
		{

			iType2 = ""; //Not needed for this item type

			amount = mp_g.sMBAmount(iCode, iType, mPlayer, stat_g); //Get player to choose the number of items to buy

			sMBuy = mp_g.sMIInfo(iCode,iType,iType2, mPlayer, stat_g, amount); //Print out item information


			if (sMBuy) //If player wants to buy
			{
				sMPurchase(mPlayer, stat_g);
			}
		}

		else
		{
			bContinue = false;
		}
	}
}


void Game::sMPurchase(Player& mPlayer, Station& stat_g)
{
	if (iType == "Weapon")
	{
		ds_g.rData("Weapon_Data","select from",iCode);
	
		//If weapon requires the resource remove that amount of resources from the playuer
		if (ds_g.getWXC() != 0)
		{
			mPlayer.updateXarn(ds_g.getWXC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWRC() != 0)
		{
			mPlayer.updateRubies(ds_g.getWRC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWDiC() != 0)
		{
			mPlayer.updateDia(ds_g.getWDiC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWDC() != 0)
		{
			mPlayer.updateDrac(ds_g.getWDC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWLC() != 0)
		{
			mPlayer.updateLith(ds_g.getWLC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWPC() != 0)
		{
			mPlayer.updatePlut(ds_g.getWPC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWUC() != 0)
		{
			mPlayer.updateUra(ds_g.getWUC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWNWC() != 0)
		{		
			mPlayer.updateNWaste(ds_g.getWNWC()* stat_g.getCMulti(), "sub");
		}		
		
		mp_g.mRMessage(2007);
		sSItem(mPlayer, stat_g, true); //Store the weapon		
	}	

	else if (iType == "Ship")
	{
		ds_g.rData("Ship_Data","select from",iCode);
	
		//If ship requires the resource remove that amount of resources from the player
		if (ds_g.getSXC() != 0)
		{
			mPlayer.updateXarn(ds_g.getSXC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getSRC() != 0)
		{
			mPlayer.updateRubies(ds_g.getSRC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getSDiC() != 0)
		{
			mPlayer.updateDia(ds_g.getSDiC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getSDC() != 0)
		{
			mPlayer.updateDrac(ds_g.getSDC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWPC() != 0)
		{
			mPlayer.updatePlut(ds_g.getSPC()* stat_g.getCMulti(), "sub");
		}

		if (ds_g.getWUC() != 0)
		{
			mPlayer.updateUra(ds_g.getSUC()* stat_g.getCMulti(), "sub");
		}
				
		mp_g.mRMessage(2007);
		sSItem(mPlayer, stat_g, true);
	}

	else if (iType == "Equipment")
	{
		if (iType2 == "PShield" || iType2 == "PDefense" || iType2 == "Clone")
		{
			ds_g.rData("Equipment_Data","select from",iCode);

			//If item requires the resource remove that amount of resources from the playuer

			if (iType2 == "Clone")
			{
				if ((iCode >= 201) && (iCode <= 3)) //If the item is a clone use a different cost calculation
				{	
					sTax = 0.25f; //Clone tax

					sTCost = ds_g.getEXC() * stat_g.getCMulti(); //Calculate CMulti cost
					sPTax = sTCost * sTax; //Calculate additional cost from tax

					sTPCost = sTCost + sPTax; //Calculate total cost

					mPlayer.updateXarn(sTPCost, "sub");
				}
			}

			else
			{			
				if (ds_g.getEXC() != 0)
				{
					mPlayer.updateXarn(ds_g.getEXC() * stat_g.getCMulti(), "sub");
				}
			}

			if (ds_g.getERC() != 0)
			{
				mPlayer.updateRubies(ds_g.getERC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getEDiC() != 0)
			{
				mPlayer.updateDia(ds_g.getEDiC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getEDC() != 0)
			{
				mPlayer.updateDrac(ds_g.getEDC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getELC() != 0)
			{
				mPlayer.updateLith(ds_g.getELC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getEPC() != 0)
			{
				mPlayer.updatePlut(ds_g.getEPC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getEUC() != 0)
			{
				mPlayer.updateUra(ds_g.getEUC()* stat_g.getCMulti(), "sub");
			}

			if (ds_g.getENWC() != 0)
			{

				mPlayer.updateNWaste(ds_g.getENWC()* stat_g.getCMulti(), "sub");
			}

			mp_g.mRMessage(2007);
			sSItem(mPlayer, stat_g, true); //Store the item; temporary and only for now as only items are clones.  Eventually clones will recieve their own storage facilities
		}
	}

	else if (iType2 == "Resource")
	{
		ds_g.rData("Resource", "select from" , iCode);

		if (ds_g.getResXCost() > 0)
		{
			mPlayer.updateXarn(((ds_g.getResXCost() * amount) * stat_g.getCMulti()), "sub");
		}

		//Store resource
		sSItem(mPlayer, stat_g,true);
	}

	else if (iType2 == "Ore")
	{
		ds_g.rData("Ore", "select from" , iCode);

		if (ds_g.getOXCost() > 0)
		{
			mPlayer.updateXarn(((ds_g.getOXCost() * amount) * stat_g.getCMulti()), "sub");
		}

		//Store ore
		sSItem(mPlayer, stat_g, true);
	}
}

//Sell
void Game::sMLoop2B1(Player& mPlayer, Station& stat_g)
{
	sMMenu2 = true;

	while(sMMenu2)
	{
		pChoice = mp_g.sMMenu1B1();

		switch(pChoice)
		{
		case 1:
			iType = "Not Ship";
			sMLoop3A1(mPlayer, stat_g);
			break;

		case 2:
			iType = "Ship";
			sMLoop3A2(mPlayer, stat_g);
			break;

		default:
			sMMenu2 = false;
			break;
		}
	}
}

void Game::sMLoop3A1(Player& mPlayer, Station& stat_g)
{
	pChoice = mp_g.sMMenu1B2();

	switch(pChoice)
	{
	case 1:
		sMLoop4A(mPlayer, stat_g, true, false);
		break;

	case 2:
		sMLoop4A(mPlayer, stat_g, false, true);
		break;
	}
}

void Game::sMLoop3A2(Player& mPlayer, Station& stat_g)
{
	pChoice = mp_g.sMMenu1B2();

	switch(pChoice)
	{
	case 1:
		sMLoop4B(mPlayer, stat_g, true, false);
		break;

	case 2:
		sMLoop4B(mPlayer, stat_g, false, true);
		break;
	}
}

void Game::sMLoop4A(Player& mPlayer, Station& stat_g, bool ship, bool station)
{
	if (ship)
	{
		pChoice = mp_g.sMMenu1C1(mPlayer, iType);

		if (pChoice != -1)
		{
			sSell(mPlayer, stat_g, true, false, false, pChoice);
		}
	}

	else if (station)
	{
		pChoice = mp_g.sMMenu1C2(stat_g,iType);

		if (pChoice != -1)
		{
			sSell(mPlayer, stat_g, false, true, false, pChoice);
		}
	}
}

void Game::sMLoop4B(Player& mPlayer, Station& stat_g, bool ship, bool station)
{
	if (ship)
	{
		pChoice = mp_g.sMMenu1C1(mPlayer, iType);

		if (pChoice != -1)
		{
			sSell(mPlayer, stat_g, true, false, true, pChoice);
		}
	}

	else if (station)
	{
		pChoice = mp_g.sMMenu1C2(stat_g,iType);

		if (pChoice != -1)
		{
			sSell(mPlayer, stat_g, false, true, true, pChoice);
		}
	}
}

void Game::sSell(Player& mPlayer, Station& stat_g, bool bIOShip, bool bIOStation, bool bIsShip, int slot)
{
	if (bIOShip) //Item to sell is on player ship
	{
		if (!bIsShip) //Item to sell is not a ship
		{
			if (mPlayer.Ship.sCargo.at(slot).getIAmount() > 1) //If there is a stack of items in the slot marked for sale, ask player for number of items to sell
			{
				amount = mp_g.mSSIAmount(mPlayer.Ship.sCargo.at(slot).getIAmount());
			}

			else //Else set amount to 1
			{
				amount = 1;
			}
	
			pChoice  = mp_g.mSSIConfirm(amount, mPlayer.Ship.sCargo.at(slot).getIID(), mPlayer.Ship.sCargo.at(slot).getIType()); //Make player confirm that they want to sell item(s)

			if (pChoice == 0)
			{
				cout << mp_g.mRMessage(2043) << endl;
			}

			else
			{
				cout << mp_g.mRMessage(2044) << endl;

				if (mPlayer.Ship.sCargo.at(slot).getIType() == "Weapon")
				{
					ds_g.rData("Weapon_Data", "select from", mPlayer.Ship.sCargo.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getWXC() * 0.25f) * amount), "add");
					mPlayer.updateRubies(((ds_g.getWRC() * 0.25f) * amount), "add");
					mPlayer.updateDia(((ds_g.getWDiC() * 0.25f) * amount), "add");
					mPlayer.updateDrac(((ds_g.getWDC() * 0.25f) * amount), "add");
					mPlayer.updateLith(((ds_g.getWLC() * 0.25f) * amount), "add");
					mPlayer.updateUra(((ds_g.getWUC() * 0.25f) * amount), "add");
					mPlayer.updatePlut(((ds_g.getWPC() * 0.25f) * amount), "add");

					mPlayer.Ship.updateCIAmount(slot, amount, "sub", false, "");

					cout << "Sale of " <<  amount << " units of " << ds_g.getWName() << " completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (mPlayer.Ship.sCargo.at(slot).getIType() == "PShield" || mPlayer.Ship.sCargo.at(slot).getIType() == "PDefense")
				{
					ds_g.rData("Equipment_Data", "select from", mPlayer.Ship.sCargo.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getEXC() * 0.25f) * amount), "add");
					mPlayer.updateRubies(((ds_g.getERC() * 0.25f) * amount), "add");
					mPlayer.updateDia(((ds_g.getEDiC() * 0.25f) * amount), "add");
					mPlayer.updateDrac(((ds_g.getEDC() * 0.25f) * amount), "add");
					mPlayer.updateLith(((ds_g.getELC() * 0.25f) * amount), "add");
					mPlayer.updateUra(((ds_g.getEUC() * 0.25f) * amount), "add");
					mPlayer.updatePlut(((ds_g.getEPC() * 0.25f) * amount), "add");

					mPlayer.Ship.updateCIAmount(slot, amount, "sub", false, "");

					cout << "Sale of " <<  amount << " units of " << ds_g.getEName() << " completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (mPlayer.Ship.sCargo.at(slot).getIType() == "Resource")
				{
					ds_g.rData("Resource", "select from", mPlayer.Ship.sCargo.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getResXCost() * 0.25f) * amount), "add");					

					mPlayer.Ship.updateCIAmount(slot, amount, "sub", false, "");

					cout << "Sale of " <<  amount << " units of " << ds_g.getResName() << " for " << ((ds_g.getOXCost() * 0.25f) * amount) << " Xarn completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (mPlayer.Ship.sCargo.at(slot).getIType() == "Ore")
				{
					ds_g.rData("Ore", "select from", mPlayer.Ship.sCargo.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getOXCost() * 0.25f) * amount), "add");

					mPlayer.Ship.updateCIAmount(slot, amount, "sub", false, "");

					cout << "Sale of " <<  amount << " units of " << ds_g.getOName() << " for " << ((ds_g.getOXCost() * 0.25f) * amount) << " Xarn completed." << endl;
					mp_g.mCScreen(true);
				}
			}
		}

		else if (bIsShip) //Item to sell is a ship
		{
			pChoice  = mp_g.mSSIConfirm(mPlayer.Ship.sCargo.at(slot).getIAmount(), mPlayer.Ship.sCargo.at(slot).sShip.getID(), mPlayer.Ship.sCargo.at(slot).getIType()); //Make player confirm that they want to sell item(s)

			if (pChoice == 1)
			{
				ds_g.rData("Ship_Data", "select from", mPlayer.Ship.sCargo.at(slot).sShip.getID());

				mPlayer.updateXarn(((ds_g.getSXC() * 0.25f) * amount), "add");
				mPlayer.updateRubies(((ds_g.getSRC() * 0.25f) * amount), "add");
				mPlayer.updateDia(((ds_g.getSDiC() * 0.25f) * amount), "add");
				mPlayer.updateDrac(((ds_g.getSDC() * 0.25f) * amount), "add");
				mPlayer.updateUra(((ds_g.getSUC() * 0.25f) * amount), "add");
				mPlayer.updatePlut(((ds_g.getSPC() * 0.25f) * amount), "add");

				mPlayer.Ship.updateCIAmount(slot, amount, "sub", false, "");
				
				cout << "Sale of " << ds_g.getSName() << " completed." << endl;
				mp_g.mCScreen(true);
			}

			else if (pChoice == 0)
			{
				cout << mp_g.mRMessage(2043) << endl;
			}
		}
	}

	else if (bIOStation) //Item to sell is on the station
	{
		if (!bIsShip) //Item to sell is not a ship
		{
			if (stat_g.sInventory.at(slot).getIAmount() > 1) //If there is a stack of items in the slot marked for sale, ask player for number of items to sell
			{
				amount = mp_g.mSSIAmount(stat_g.sInventory.at(slot).getIAmount());
			}

			else //Else set amount to 1
			{
				amount = 1;
			}
	
			pChoice  = mp_g.mSSIConfirm(stat_g.sInventory.at(slot).getIAmount(), stat_g.sInventory.at(slot).getIID(), stat_g.sInventory.at(slot).getIType()); //Make player confirm that they want to sell item(s)

			if (pChoice == 0)
			{
				cout << mp_g.mRMessage(2043) << endl;
			}

			else
			{
				cout << mp_g.mRMessage(2044) << endl;

				if (stat_g.sInventory.at(slot).getIType() == "Weapon")
				{
					ds_g.rData("Weapon_Data", "select from", stat_g.sInventory.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getWXC() * 0.25f) * amount), "add");
					mPlayer.updateRubies(((ds_g.getWRC() * 0.25f) * amount), "add");
					mPlayer.updateDia(((ds_g.getWDiC() * 0.25f) * amount), "add");
					mPlayer.updateDrac(((ds_g.getWDC() * 0.25f) * amount), "add");
					mPlayer.updateLith(((ds_g.getWLC() * 0.25f) * amount), "add");
					mPlayer.updateUra(((ds_g.getWUC() * 0.25f) * amount), "add");
					mPlayer.updatePlut(((ds_g.getWPC() * 0.25f) * amount), "add");

					stat_g.removeItem(slot, amount);

					cout << "Sale of " <<  amount << " units of " << ds_g.getWName() << " completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (stat_g.sInventory.at(slot).getIType() == "PShield" || stat_g.sInventory.at(slot).getIType() == "PDefense")
				{
					ds_g.rData("Equipment_Data", "select from", stat_g.sInventory.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getEXC() * 0.25f) * amount), "add");
					mPlayer.updateRubies(((ds_g.getERC() * 0.25f) * amount), "add");
					mPlayer.updateDia(((ds_g.getEDiC() * 0.25f) * amount), "add");
					mPlayer.updateDrac(((ds_g.getEDC() * 0.25f) * amount), "add");
					mPlayer.updateLith(((ds_g.getELC() * 0.25f) * amount), "add");
					mPlayer.updateUra(((ds_g.getEUC() * 0.25f) * amount), "add");
					mPlayer.updatePlut(((ds_g.getEPC() * 0.25f) * amount), "add");

					stat_g.removeItem(slot, amount);
					
					cout << "Sale of " <<  amount << " units of " << ds_g.getEName() << " completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (stat_g.sInventory.at(slot).getIType() == "Resource")
				{
					ds_g.rData("Resource", "select from", stat_g.sInventory.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getResXCost() * 0.25f) * amount), "add");					

					stat_g.removeItem(slot, amount);

					cout << "Sale of " <<  amount << " units of " << ds_g.getResName() << " for " << ((ds_g.getOXCost() * 0.25f) * amount) << " Xarn completed." << endl;
					mp_g.mCScreen(true);
				}

				else if (stat_g.sInventory.at(slot).getIType() == "Ore")
				{
					ds_g.rData("Ore", "select from", stat_g.sInventory.at(slot).getIID());

					//For now item sales will give 25% of total cost back, hard.  Values will shift in later versions based on the CMulti, affinity, and difficuly

					mPlayer.updateXarn(((ds_g.getOXCost() * 0.25f) * amount), "add");

					stat_g.removeItem(slot, amount);

					cout << "Sale of " <<  amount << " units of " << ds_g.getOName() << " for " << ((ds_g.getOXCost() * 0.25f) * amount) << " Xarn completed." << endl;
					mp_g.mCScreen(true);
				}
			}
		}

		else if (bIsShip) //Item to sell is a ship
		{
			pChoice  = mp_g.mSSIConfirm(stat_g.sInventory.at(slot).getIAmount(), stat_g.sInventory.at(slot).sShip.getID(), stat_g.sInventory.at(slot).getIType()); //Make player confirm that they want to sell item(s)

			if (pChoice == 1)
			{
				ds_g.rData("Ship_Data", "select from", stat_g.sInventory.at(slot).sShip.getID());

				mPlayer.updateXarn(((ds_g.getSXC() * 0.25f) * amount), "add");
				mPlayer.updateRubies(((ds_g.getSRC() * 0.25f) * amount), "add");
				mPlayer.updateDia(((ds_g.getSDiC() * 0.25f) * amount), "add");
				mPlayer.updateDrac(((ds_g.getSDC() * 0.25f) * amount), "add");
				mPlayer.updateUra(((ds_g.getSUC() * 0.25f) * amount), "add");
				mPlayer.updatePlut(((ds_g.getSPC() * 0.25f) * amount), "add");

				stat_g.removeItem(slot, amount);

				cout << "Sale of " << ds_g.getSName() << " completed." << endl;
				mp_g.mCScreen(true);
			}

			else if (pChoice == 0)
			{
				cout << mp_g.mRMessage(2043) << endl;
			}
		}
	}
}

string Game::getIType()
{
	if (iCode >= 1 || iCode <= 31) //External value tag: value range; Add mining laser range here
	{
		return "laser";
	}

	else if (iCode >= 32 || iCode <= 102) //External value tag: value range
	{
		return "missile";
	}

	else if (iCode >= 103 || iCode <= 125) //External value tag: value range
	{
		return "bomb";
	}

	//TODO: Add railgun, heavy weapons
}

/*void Game::sSItem(Player& mPlayer, Station& stat_g)
{
	while (!bDone)
	{
		ds_g.rData("Equipment_Data", "select from", iCode);

		if (stat_g.getCSUsed() + ds_g.getESG2() < stat_g.getMUSpace())
		{
			for (i = 0; i <= stat_g.getISize(); i++)
			{
				if (i == stat_g.getISize())
				{
					stat_g.sSItem(iCode, 1, iType, ds_g.getESG2());
					bDone = true;
					break;
				}

				else if (stat_g.sInventory.at(i).getIID() == iCode)
				{
					stat_g.sInventory.at(i).updateIAmount(1,"add");
					bDone = true;
					break;
				}			
			}
		}

		else
		{
			if (sBISpace(stat_g,mPlayer, ds_g.getESG2()))
			{
				for (i = 0; i <= stat_g.getISize(); i++)
				{
					if (i == stat_g.getISize())
					{
						stat_g.sSItem(iCode, 1, iType, ds_g.getESG2());
						bDone = true;
						break;
					}

					else if (stat_g.sInventory.at(i).getIID() == iCode)
					{
						stat_g.sInventory.at(i).updateIAmount(1,"add");
						bDone = true;
						break;
					}
				}
			}

			else
			{
				sMRefund(mPlayer, stat_g);
				bDone = true;
			}
		}
	}	

	bDone = false; //reset while loop
}*/

void Game::sSItem(Player& mPlayer, Station& stat_g, bool bought)
{
	bDone = false; //reset while loop

	if (bought)
	{
		if (iType == "Ship")
		{
			while (!bDone)
			{
				if (stat_g.checkSpace(ds_g.getESG2()))
				{
					bExchange = mp_g.sMECShip();

					bSSuccess = stat_g.sSShip(iCode, bought, bExchange, mPlayer, this);

					if (bSSuccess)
					{
						bDone = true;
					}

					else if ((!bSSuccess) && (bought))
					{
						sMRefund(mPlayer, stat_g);
						bDone = true;
					}
				}

				else
				{
					if (!stat_g.sBISpace(mPlayer, ds_g.getESG2()))
					{			
						sMRefund(mPlayer, stat_g);
						bDone = true;
					}
				}
			}	
		}

		else if (iType == "Equipment")
		{
			while (!bDone)
			{
				if (iType2 == "PShield" || iType2 == "PDefense" || iType2 == "Clone")
				{
					ds_g.rData("Equipment_Data", "select from", iCode);

					if (stat_g.checkSpace(ds_g.getESG2()))
					{
						for (i = 0; i <= stat_g.getISize(); i++)
						{
							if (i == stat_g.getISize())
							{
								stat_g.sSItem(iCode, 1, iType, ds_g.getESG2());
								bDone = true;
								break;
							}

							else if (stat_g.sInventory.at(i).getIID() == iCode)
							{
								stat_g.sInventory.at(i).updateIAmount(1,"add");
								bDone = true;
								break;
							}			
						}
					}

					else
					{
						if (stat_g.sBISpace(mPlayer, ds_g.getESG2()))
						{
							for (i = 0; i <= stat_g.getISize(); i++)
							{
								if (i == stat_g.getISize())
								{
									stat_g.sSItem(iCode, 1, iType, ds_g.getESG2());
									bDone = true;
									break;
								}

								else if (stat_g.sInventory.at(i).getIID() == iCode)
								{
									stat_g.sInventory.at(i).updateIAmount(1,"add");
									bDone = true;
									break;
								}
							}
						}

						else
						{
							sMRefund(mPlayer, stat_g);
							bDone = true;
						}
					}
				}
			}
		}

		else if (iType == "Resource")
		{
			while (!bDone)
			{
				ds_g.rData("Resource", "select from", iCode);

				if (stat_g.checkSpace(ds_g.getResSG2()))
				{
					for (i = 0; i <= stat_g.getISize(); i++)
					{
						if (i == stat_g.getISize())
						{
							stat_g.sSItem(iCode, amount, iType, ds_g.getResSG2());
							bDone = true;
							break;
						}

						else if (stat_g.sInventory.at(i).getIID() == iCode)
						{
							stat_g.sInventory.at(i).updateIAmount(amount,"add");
							bDone = true;
							break;
						}			
					}
				}

				else
				{
					if (stat_g.sBISpace(mPlayer, ds_g.getResSG2()))
					{
						for (i = 0; i <= stat_g.getISize(); i++)
						{
							if (i == stat_g.getISize())
							{
								stat_g.sSItem(iCode, amount, iType, ds_g.getResSG2());
								bDone = true;
								break;
							}

							else if (stat_g.sInventory.at(i).getIID() == iCode)
							{
								stat_g.sInventory.at(i).updateIAmount(amount,"add");
								bDone = true;
								break;
							}
						}
					}

					else
					{
						sMRefund(mPlayer, stat_g);
						bDone = true;
					}
				}
			}
		}

		else if (iType == "Ore")
		{
			while (!bDone)
			{
				ds_g.rData("Ore", "select from", iCode);

				if (stat_g.checkSpace(ds_g.getOSG2()))
				{
					for (i = 0; i <= stat_g.getISize(); i++)
					{
						if (i == stat_g.getISize())
						{
							stat_g.sSItem(iCode, amount, iType, ds_g.getOSG2());
							bDone = true;
							break;
						}

						else if (stat_g.sInventory.at(i).getIID() == iCode)
						{
							stat_g.sInventory.at(i).updateIAmount(amount,"add");
							bDone = true;
							break;
						}			
					}
				}

				else
				{
					if (stat_g.sBISpace(mPlayer, ds_g.getOSG2()))
					{
						for (i = 0; i <= stat_g.getISize(); i++)
						{
							if (i == stat_g.getISize())
							{
								stat_g.sSItem(iCode, amount, iType, ds_g.getOSG2());
								bDone = true;
								break;
							}

							else if (stat_g.sInventory.at(i).getIID() == iCode)
							{
								stat_g.sInventory.at(i).updateIAmount(amount,"add");
								bDone = true;
								break;
							}
						}
					}

					else
					{
						sMRefund(mPlayer, stat_g);
						bDone = true;
					}
				}
			}
		}
	}

	else
	{
		//Determine if the item is a ship or a non-ship item//Determine where the itme the player wants to move is located
		pChoice = mp_g.sMSI1();

		if (pChoice == 0)
		{
			cout << "Ending storage processing..." << endl;
			bDone = true;
		}

		//Move a ship
		else if (pChoice == 1)
		{
			if (!stat_g.sSShip(0, false, false, mPlayer, this))
			{
				cout << "Storage process failed..." << endl;
				bDone = true;
			}
		}

		//Move a non-ship
		else
		{
			//Determine if the item is located on the station or in the player ship cargohold
			pChoice = mp_g.sMSI2();

			if (pChoice == 1) //Item is located on station - move to player ship
			{
				stat_g.getItem(mPlayer);
				bDone = true;
			}

			else if (pChoice == 2) //Item is located on the player ship - move to the station
			{
				mPlayer.Ship.storeItem(stat_g, mPlayer);
				bDone = true;
			}

			else
			{
				cout << "Ending storage proceedures." << endl;
			}
		}
	}
}

void Game::sGItem(Player& mPlayer, Station& stat_g)
{
	if (stat_g.sInventory.size() == 0)
	{
		cout << "You do not have anything stored on this station." << endl;
	}

	else
	{
		pChoice = mp_g.sMMenu1B1();

		if (pChoice == 0)
		{
			cout << "Ending the retrieval process..." << endl;
		}

		else if (pChoice == 1)
		{
			pChoice = mp_g.sInv(stat_g);

			if (pChoice < 0)
			{
				cout << "Ending the retrieval process..." << endl;
			}

			else
			{
				if (stat_g.sInventory.at(pChoice-1).getIAmount() > 1)
				{
					amount = mp_g.mSSIAmount(stat_g.sInventory.at(pChoice=1).getIAmount());
				}

				else //Else set amount to 1
				{
					amount = 1;
				}

				pChoice  = mp_g.mSTIConfirm(amount, stat_g.sInventory.at(pChoice-1).getIID(), stat_g.sInventory.at(pChoice-1).getIType());

				if (pChoice == 1)
				{
					if (mPlayer.Ship.checkSpace(stat_g.sInventory.at(pChoice-1).getISpace()*amount))
					{
						if (mPlayer.Ship.addCItem(stat_g.sInventory.at(pChoice-1).getIID(), stat_g.sInventory.at(pChoice-1).getIType(),amount, false))
						{
							stat_g.removeItem(pChoice-1, amount);

							cout << "Your selected item(s) were successfully transfered to your ship." << endl;
						}

						else
						{
							cout << "Item transfer to ship failed.  Ending the retrieval process..." << endl;
						}
					}

					else
					{
						cout << "Not enough space on ship for cargo.  Ending the retrieval process..." << endl;
					}
				}

				else
				{
					cout << "Ending the retrieval process..." << endl;
				}
			}
		}

		else if (pChoice == 2)
		{
			cout << mp_g.mRMessage(2001) << endl;
		}
	}
}


void Game::loadStation(stationData& stData)
{
	gStations.push_back(Station());
	
	gStations.at(gStations.size()-1).setSID(stData.sID); //ID from table for dealing with player inventories in various stations
	gStations.at(gStations.size()-1).setName(stData.sName);
	gStations.at(gStations.size()-1).setAffil(stData.sAffiliation);
	gStations.at(gStations.size()-1).setDispo(stData.sDispo);
	gStations.at(gStations.size()-1).setTLevel(stData.sTLevel);
	gStations.at(gStations.size()-1).setSLevel(stData.sLevel); //Station level
	gStations.at(gStations.size()-1).updateISpace(stData.sMSpace, "set"); //Max usable storage space
	gStations.at(gStations.size()-1).setCMulti(stData.sCMulti); //Cost multiplier
}

void Game::sMRefund(Player& mPlayer, Station& stat_g)
{
	cout << mp_g.mRMessage(2008) << endl;
	cout << endl;

	if (iType == "Weapon")
	{
		ds_g.rData("Weapon_Data","select from",iCode);
		
		//If weapon requires the resource remove that amount of resources from the playuer
		if (ds_g.getWXC() != 0)
		{
			mPlayer.updateXarn(ds_g.getWXC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWRC() != 0)
		{
			mPlayer.updateRubies(ds_g.getWRC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWDiC() != 0)
		{
			mPlayer.updateDia(ds_g.getWDiC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWDC() != 0)
		{
			mPlayer.updateDrac(ds_g.getWDC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWLC() != 0)
		{
			mPlayer.updateLith(ds_g.getWLC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWPC() != 0)
		{
			mPlayer.updatePlut(ds_g.getWPC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWUC() != 0)
		{
			mPlayer.updateUra(ds_g.getWUC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWNWC() != 0)
		{		
			mPlayer.updateNWaste(ds_g.getWNWC()* stat_g.getCMulti(), "add");
		}
	}

	else if (iType == "Ship")
	{
		ds_g.rData("Ship_Data","select from",iCode);
	
		//If ship requires the resource remove that amount of resources from the player
		if (ds_g.getSXC() != 0)
		{
			mPlayer.updateXarn(ds_g.getSXC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getSRC() != 0)
		{
			mPlayer.updateRubies(ds_g.getSRC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getSDiC() != 0)
		{
			mPlayer.updateDia(ds_g.getSDiC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getSDC() != 0)
		{
			mPlayer.updateDrac(ds_g.getSDC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWPC() != 0)
		{
			mPlayer.updatePlut(ds_g.getSPC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getWUC() != 0)
		{
			mPlayer.updateUra(ds_g.getSUC()* stat_g.getCMulti(), "add");
		}
	}

	else if (iType == "Equipment")
	{
		ds_g.rData("Equipment_Data","select from",iCode);
		
		//If item requires the resource remove that amount of resources from the player
		
		if (iType2 == "Clone")
		{
			if ((iCode >= 1) && (iCode <= 3)) //If the item is a clone use a different cost calculation
			{	
				sTax = 0.25f; //Clone tax

				sTCost = ds_g.getEXC() * stat_g.getCMulti(); //Calculate CMulti cost
				sPTax = sTCost * sTax; //Calculate additional cost from tax

				sTPCost = sTCost + sPTax; //Calculate total cost

				mPlayer.updateXarn(sTPCost, "add");
			}
		}

		else
		{
			if (ds_g.getEXC() != 0)
			{
				mPlayer.updateXarn(ds_g.getEXC() * stat_g.getCMulti(), "add");
			}
		}

		if (ds_g.getERC() != 0)
		{
			mPlayer.updateRubies(ds_g.getERC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getEDiC() != 0)
		{
			mPlayer.updateDia(ds_g.getEDiC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getEDC() != 0)
		{
			mPlayer.updateDrac(ds_g.getEDC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getELC() != 0)
		{
			mPlayer.updateLith(ds_g.getELC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getEPC() != 0)
		{
			mPlayer.updatePlut(ds_g.getEPC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getEUC() != 0)
		{
			mPlayer.updateUra(ds_g.getEUC()* stat_g.getCMulti(), "add");
		}

		if (ds_g.getENWC() != 0)
		{

			mPlayer.updateNWaste(ds_g.getENWC()* stat_g.getCMulti(), "add");
		}
	}
}

void Game::createBInfo()
{
	file = __FILE__;
	bLocale = "File: " + file + "  Line: ";

	time = __TIME__;
	date = __DATE__;

	bTDate = date + "  " + time;
}

void Game::sCasino(Player& mPlayer)
{
	cout << mp_g.mRMessage(2001) << endl;
}