#include <string>
#include "weapon.h"
#include "datasystem.h"

using namespace std;

dataSystem ds_w;

//Weapon Functions
int Weapon::getWDRLow()
{
	return wDRange.mLow;
}

int Weapon::getWDRHigh()
{
	return wDRange.mHigh;
}

int Weapon::getWDROLow()
{
	return wDRange.mOpLow;
}

int Weapon::getWDROHigh()
{
	return wDRange.mOpHigh;
}

int Weapon::getWALow()
{
	return wAcc.mLow;
}

int Weapon::getWAHigh()
{
	return wAcc.mHigh;
}

int Weapon::getWAOLow()
{
	return wAcc.mOpLow;
}

int Weapon::getWAOHigh()
{
	return wAcc.mOpHigh;
}

int Weapon::getWTLevel()
{
	return wTLevel;
}

int Weapon::getWType()
{
	return wType;
}

string Weapon::getWClass()
{
	return wClass;
}

string Weapon::getWName()
{
	return wName;
}

string Weapon::getWDType()
{
	return wDType;
}
	

bool Weapon::isWDisabled()
{
	return wStatus;
}

void Weapon::toggleWeapon(int time)
{
	if (wStatus == false)
	{
		wStatus = true;
		wDTimer = time;
	}

	else
	{
		wStatus = false;
	}
}

void Weapon::initWeapon()
{
	wName = "No Weapon Installed";
	wID = 999999;
	wType = 0;
}

void Weapon::wSetup(int wCode)
{
	ds_w.rData("Weapon_Data","select from",wCode);
}

int Weapon::getWID()
{
	return wID;
}

float Weapon::getSG2()
{
	return wSG2;
}

void Weapon::setSG2(float sg2)
{
	wSG2 = sg2;
}

//Laser Functions
Laser::Laser()
{
	
}

void Laser::iWeapon()
{
	wID = ds_w.getWID();
	wName = ds_w.getWName();	
	wClass = ds_w.getWClass();
	wTLevel = ds_w.getWTLevel();
	wDType =  ds_w.getWDType();		
	wDRange.mLow = ds_w.getWDRLow();
	wDRange.mHigh = ds_w.getWDRHigh();	
	wAcc.mLow = ds_w.getWAMin();
	wAcc.mOpLow = ds_w.getWAOMin();
	wAcc.mOpHigh = ds_w.getWAOMax();
	wAcc.mHigh = ds_w.getWAMax();
	wSG2 = ds_w.getWSG2();
	wMCLength = ds_w.getWMCLength();
	wMCAmount = ds_w.getWMCAmount();
}

Laser* Laser::getWeapon()
{
	return this;
}

int Laser::getCLength()
{
	return wMCLength;
}

float Laser::getCMAmount()
{
	return wMCAmount;
}


//Missile Functions
Missile::Missile()
{

}

void Missile::iWeapon()
{
	wID = ds_w.getWID();
	wName = ds_w.getWName();	
	wClass = ds_w.getWClass();
	wTLevel = ds_w.getWTLevel();
	wDType =  ds_w.getWDType();		
	wDRange.mLow = ds_w.getWDRLow();
	wDRange.mHigh = ds_w.getWDRHigh();	
	wAcc.mHigh = ds_w.getWAMax();
	wSG2 = ds_w.getWSG2();
}

Missile* Missile::getWeapon()
{
	return this;
}

//Bomb Functions
Bomb::Bomb()
{

}

void Bomb::iWeapon()
{
	wID = ds_w.getWID();
	wName = ds_w.getWName();			
	wClass = ds_w.getWClass();
	wTLevel = ds_w.getWTLevel();
	wDType =  ds_w.getWDType();		
	wDRange.mLow = ds_w.getWDRLow();
	wDRange.mHigh = ds_w.getWDRHigh();
	bWeight = ds_w.getWWeight();
	wSG2 = ds_w.getWSG2();
}

int Bomb::getWeight()
{
	return bWeight;
}

Bomb* Bomb::getWeapon()
{
	return this;
}

//Rail Gun Functions
Rail::Rail()
{

}

void Rail::iWeapon()
{
	wID = ds_w.getWID();
	wName = ds_w.getWName();
	wClass = ds_w.getWClass();
	wTLevel = ds_w.getWTLevel();
	wDType =  ds_w.getWDType();		
	wDRange.mLow = ds_w.getWDRLow();
	wDRange.mHigh = ds_w.getWDRHigh();	
	wAcc.mLow = ds_w.getWAMin();
	wAcc.mOpLow = ds_w.getWAOMin();
	wAcc.mOpHigh = ds_w.getWAOMax();
	wAcc.mHigh = ds_w.getWAMax();
	wSG2 = ds_w.getWSG2();
}

Rail* Rail::getWeapon()
{
	return this;
}

//Heavy Weapon Functions
Heavy::Heavy()
{

}

void Heavy::iWeapon()
{
	wID = ds_w.getWID();
	wName = ds_w.getWName();
	wClass = ds_w.getWClass();
	wTLevel = ds_w.getWTLevel();
	wDType =  ds_w.getWDType();		
	wDRange.mLow = ds_w.getWDRLow();
	wDRange.mHigh = ds_w.getWDRHigh();	
	wAcc.mLow = ds_w.getWAMin();
	wAcc.mOpLow = ds_w.getWAOMin();
	wAcc.mOpHigh = ds_w.getWAOMax();
	wAcc.mHigh = ds_w.getWAMax();
	wSG2 = ds_w.getWSG2();
	
	/*
	TODO: Add damage intensity fields to weapon_data table
	
	hDInt.mLow = ds_w.getWDILow();
	hDInt.mOpLow = ds_w.getWDIOLow();
	hDInt.mOpHigh = ds_w.getWDIOHigh();
	hDInt.mHigh = ds_w.getWDIMax();
	*/
}

int Heavy::getDILow()
{
	return hDInt.mLow;
}

int Heavy::getDIOLow()
{
	return hDInt.mOpLow;
}

int Heavy::getDIOHigh()
{
	return hDInt.mOpHigh;
}

int Heavy::getDIHigh()
{
	return hDInt.mHigh;
}

Heavy* Heavy::getWeapon()
{
	return this;
}

