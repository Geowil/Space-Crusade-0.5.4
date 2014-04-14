#include "defenses.h"
#include "datasystem.h"
#include "msgproc.h"

dataSystem ds_de;
msgProc mp_de;

Defense::Defense()
{

}

Defense* Defense::rDefense()
{
	return this;
}

void Defense::updateSPoints(float sp, string operation)
{
	if (operation == "add")
	{
		dSP += sp;
	}

	else if (operation == "sub")
	{
		dSP -= sp;
	}

	else if (operation == "set")
	{
		dSP = sp;
		dMSP = dSP;
	}
}

float Defense::getSPoints()
{
	return dSP;
}
	
int Defense::getID()
{
	return dID;
}

int Defense::getDDRLow()
{
	return dDRange.mLow;
}

int Defense::getDDRHigh()
{
	return dDRange.mHigh;
}

int Defense::getDDROLow()
{
	return dDRange.mOpLow;
}

int Defense::getDDROHigh()
{
	return dDRange.mOpHigh;
}

int Defense::getDALow()
{
	return dAcc.mLow;
}

int Defense::getDAHigh()
{
	return dAcc.mHigh;
}

int Defense::getDAOLow()
{
	return dAcc.mOpLow;
}

int Defense::getDAOHigh()
{
	return dAcc.mOpHigh;
}

int Defense::getDTLevel()
{
	return dTLevel;
}

int Defense::getDType()
{
	return dType;
}

int Defense::getDCXP()
{
	return dCXP;
}

//int Defense::getDASpeed()
//{

//}

string Defense::getDName()
{
	return dName;
}

string Defense::getDDType()
{
	return dDType;
}

void Defense::dSetup(int dCode)
{
	ds_de.rData("Equipment_Data","select from",dCode);

	dName = ds_de.getEName();
	dDType = ds_de.getEDType();
	dTLevel = ds_de.getETLevel();
	dSP = ds_de.getESP();
	dMSP = ds_de.getESMP();
	dDRange.mLow = ds_de.getEMDmg();
	dDRange.mHigh = ds_de.getEMxDmg();
	dAcc.mLow = 0;
	dAcc.mHigh = ds_de.getERng();
	dCXP = ds_de.getECXP();
	dID = dCode;
}

void Defense::addTDamage(float damage, int turns, string type)
{
	cDamage.push_back(tDamage(damage, turns, type));
}

void Defense::checkTDamage()
{
	for (i = 0; i < cDamage.size(); i++)
	{
		if (cDamage.at(i).getTurns() == 0)
		{
			removeTDamage(i); //Pass current vector element numbe to function
			i = 0; //Reset i to zero since the elements will be shifted down after the current on is removed
		}
	}
}

void Defense::removeTDamage(int i)
{
	cDamage.erase(cDamage.begin()+i);
}

float Defense::getMSPoints()
{
	return dMSP;
}

void Defense::setState(string s)
{
	dState = s;
}

string Defense::getState()
{
	return dState;
}



//Shield Functions
Shield::Shield()
{

}

Shield* Shield::rShield()
{
	return this;
}

void Shield::initPS(int mCode)
{
	ds_de.rData("Equipment_Data","select from", mCode);

	mID = mCode;
	sSP = ds_de.getESP();
	sMSP = ds_de.getESMP();
	sRgn = ds_de.getESPR();
	mName = ds_de.getEName();
	mTLevel = ds_de.getETLevel();
	bISDisabled = false;
}

string Shield::getMName()
{
	return mName;
}

int Shield::getID()
{
	return mID;
}

float Shield::getSP()
{
	return sSP;
}

float Shield::getSPRgn()
{
	return sRgn;
}

void Shield::psRegen()
{
	sSP += sRgn; //Might need to be multiplication if sRgn is going to be a percent rather than direct add (preferable)
}

void Shield::updateSP(float sp, string operation)
{
	if (operation == "add")
	{
		sSP += sp;
	}

	else if (operation == "sub")
	{
		sSP -= sp;
	}

	else if (operation == "set")
	{
		sSP = sp;
	}
}

int Shield::getTLevel()
{
	return mTLevel;
}

void Shield::dShield(int turns)
{
	sDTimer = turns;
	bISDisabled = true;
	bDTGPeriod = true;
}

float Shield::getMSP()
{
	return sMSP;
}

void Shield::dTTDown(Planet* planet)
{
	sDTimer -= 1;

	if (sDTimer == 0)
	{
		bISDisabled = false;
		sSP = (sMSP * 0.15f) + sRgn; //If the shield re-enables, set SP to 15% of max and run a regeneration cycle

		mp_de.sSEnabled(planet, mName);
	}
}

bool Shield::isDisabled()
{
	return bISDisabled;
}

int Shield::getSDTimer()
{
	return sDTimer;
}

void Shield::updateDTGrace(bool state)
{
	bDTGPeriod = state;
}

bool Shield::getDTGState()
{
	return bDTGPeriod;
}