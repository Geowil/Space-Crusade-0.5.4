#include "nameGen.h"
#include <cctype>
#include <algorithm> 

using std::transform;

dataSystem ds_ng;

nameGen::nameGen()
{

}

string nameGen::genName(string race)
{
	eRace = race; //Set this here so other functions can use it

	gFName = "";
	gLName = "";
	gCName = "";

	cNRand = Random(-50,50);

	if (((cNRand >= -45) && (cNRand <= -17)) || ((cNRand <= 29) && (cNRand >= 10)) || ((cNRand <= 47) && (cNRand >= 35))) //If any of these value ranges are true
	{ //Then use first and last name

		//Call internal functions to set up the first name
		getPrefix();
		getStem();
		getSuffix();

		if (nPrefix.length() > 0)
		{
			gFName = nPrefix;
			
			//If we have a prefix, we need to lower the case on the first letter of the stem
			transform(nStem.begin(), nStem.end(), nStem.begin(), tolower);
		}

		gFName = gFName + nStem;

		if (nSuffix.length() > 0)
		{
			gFName = gFName + nSuffix;
		}

		//Call the functions again to set up the last name
		getPrefix();
		getStem();
		getSuffix();

		if (nPrefix.length() > 0)
		{
			gLName = nPrefix;

			//If we have a prefix, we need to lower the case on the first letter of the stem
			transform(nStem.begin(), nStem.end(), nStem.begin(), tolower);
		}

		gLName = gLName + nStem;

		if (nSuffix.length() > 0)
		{
			gLName = gLName + nSuffix;
		}

		gCName = gFName + " " + gLName;

		return gCName;
	}

	else //Only use first name
	{
		//Call internal functions to set up the first name
		getPrefix();
		getStem();
		getSuffix();

		if (nPrefix.length() > 0)
		{
			gFName = nPrefix;

			//If we have a prefix, we need to lower the case on the first letter of the stem
			transform(nStem.begin(), nStem.end(), nStem.begin(), tolower);
		}

		gFName = gFName + nStem;

		if (nSuffix.length() > 0)
		{
			gFName = gFName + nSuffix;
		}

		return gFName;
	}
}

void nameGen::getPrefix()
{
	/*if (eRace == "Humanoid")
	{

	}

	else if (eRace == "Sluikan")
	{

	}

	else if (eRace == "Juslorth")
	{

	}

	else if (eRace == "Visar")
	{

	}

	else if (eRace == "Adent")
	{

	}

	else if (eRace == "Prokl")
	{

	}

	else if (eRace == "Groz")
	{

	}*/

	prefRand = Random(-12,8);

	if (prefRand > 0)
	{
		ds_ng.rData("Name_DB","select from", prefRand);
		nPrefix = ds_ng.getRName();
	}
}

void nameGen::getStem()
{
	/*if (eRace == "Humanoid")
	{

	}

	else if (eRace == "Sluikan")
	{

	}

	else if (eRace == "Juslorth")
	{

	}

	else if (eRace == "Visar")
	{

	}

	else if (eRace == "Adent")
	{

	}

	else if (eRace == "Prokl")
	{

	}

	else if (eRace == "Groz")
	{

	*/

	stemRand = Random(42,47);

	ds_ng.rData("Name_DB","select from", stemRand);
	nStem = ds_ng.getRName();	
}

void nameGen::getSuffix()
{
	/*if (eRace == "Humanoid")
	{

	}

	else if (eRace == "Sluikan")
	{

	}

	else if (eRace == "Juslorth")
	{

	}

	else if (eRace == "Visar")
	{

	}

	else if (eRace == "Adent")
	{

	}

	else if (eRace == "Prokl")
	{

	}

	else if (eRace == "Groz")
	{

	}*/

	suffRand = Random(45,95);

	if (suffRand > 85)
	{
		ds_ng.rData("Name_DB","select from", suffRand);
		nSuffix = ds_ng.getRName();
	}
}