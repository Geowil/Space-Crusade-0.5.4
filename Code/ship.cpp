#include <string>
#include "ship.h"
#include "weapon.h"
#include "random.h"
#include "datasystem.h"
#include "msgproc.h"
#include "map.h"

using namespace std;

dataSystem ds_s;
msgProc mp_s;
Map m_s;


Ship::Ship()
{
	lHPoints = 0;
	mHPoints = 0;
	bHPoints = 0;
	rHPoints = 0;
	hHPoints = 0;

	sWSpreads = 0;

	bIsSDisabled = false;
	bAreSSDisabled = false;
	bContinue = false; 

	sBH = 0; //ship bomb holds
	sHWB = 0; //ship heavy weapon bays
	sLB = 0; //ship laser banks
	sMT = 0; //ship missile turrets
	sRM = 0; //ship rail gun points	
	sWHP = 0; //ship weapon hard points	
	sDTimer = 0; //ship disabled timer
	sXC = 0; //ship xarn cost
	sRC = 0; //ship ruby cost
	sDiC = 0; //ship diamond cost
	sDC = 0; //ship draconic cost
	sLC = 0; //ship lithium cost
	sUC = 0; //ship uranium cost
	sPC = 0; //ship plutonium cost

	pChoice = 0;
	pCChoice = ' ';

	sCWSpread = 0;

	bWIsAUsed = false;

	i = 0;
	i2 = 0;

	sPosX = 0; //ship x pos
	sPosY = 0; //ship y pos
	sPosZ = 0; //ship z pos
}

float Ship::getSArmor()
{
	return sArmor;
}

float Ship::getSHull()
{
	return sHull;
}

float Ship::getSMArmor()
{
	return sMArmor;
}

float Ship::getSMHull()
{
	return sMHull;
}

float Ship::getSMShield()
{
	return sMShield;
}

float Ship::getSShield()
{
	return sShield;
}

string Ship::getSClass()
{
	return sClass;
}

int Ship::getSClassI(string sclass)
{
	if (sclass == "Frigate")
	{
		return 1;
	}

	else if (sclass == "Destroyer")
	{
		return 2;
	}

	else if (sclass == "Cruiser")
	{
		return 3;
	}

	else if (sclass == "Battlecruiser")
	{
		return 4;
	}

	else if (sclass == "Battleship")
	{
		return 5;
	}

	else if (sclass == "Mothership")
	{
		return 6;
	}

	else if (sclass == "Titan")
	{
		return 7;
	}
}

string Ship::getSName()
{
	return sName;
}

int Ship::getSTLevel()
{
	return sTLevel;
}

void Ship::updateSArmor(float f, string operation)
{
	if (operation == "add")
	{
		sArmor += f;
	}

	else if (operation == "sub")
	{
		sArmor -= f;
	}

	else if (operation == "set")
	{
		sArmor = f;
	}
}

void Ship::setSClass(string s)
{
	sClass = s;
}

void Ship::updateSHull(float f, string operation)
{
	if (operation == "add")
	{
		sHull += f;
	}

	else if (operation == "sub")
	{
		sHull -= f;
	}

	else if (operation == "set")
	{
		sHull = f;
	}
}

void Ship::updateSMArmor(float f, string operation)
{
	if (operation == "add")
	{
		sMArmor += f;
	}

	else if (operation == "sub")
	{
		sMArmor -= f;
	}

	else if (operation == "set")
	{
		sMArmor = f;
	}
}

void Ship::updateSMHull(float f, string operation)
{
	if (operation == "add")
	{
		sMHull += f;
	}

	else if (operation == "sub")
	{
		sMHull -= f;
	}

	else if (operation == "set")
	{
		sMHull = f;
	}
}

void Ship::updateSMShield(float f, string operation)
{
	if (operation == "add")
	{
		sMShield += f;
	}

	else if (operation == "sub")
	{
		sMShield -= f;
	}

	else if (operation == "set")
	{
		sMShield = f;
	}
}

void Ship::setSName(string s)
{
	sName = s;
}

void Ship::updateSShield(float f, string operation)
{
	if (operation == "add")
	{
		sShield += f;
	}

	else if (operation == "sub")
	{
		sShield -= f;
	}

	else if (operation == "set")
	{
		sShield = f;
	}
}

void Ship::setSTLevel(int i)
{
	sTLevel = i;
}

int Ship::getLHP()
{
	return sLB;
}

int Ship::getMTP()
{
	return sMT;
}

int Ship::getBH()
{
	return sBH;
}

int Ship::getRM()
{
	return sRM;
}

int Ship::getHWB()
{
	return sHWB;
}

void Ship::initHPoints()
{
	for (i = 0; i < sLB; i++)
	{
		lBanks.push_back(hardPointL(i, "laser"));
	}

	for (i = 0; i < sMT; i++)
	{
		mTurrets.push_back(hardPointM(i, "missile"));
	}

	for (i = 0; i < sBH; i++)
	{
		bHolds.push_back(hardPointB(i, "bomb"));
	}

	for (i = 0; i < sRM; i++)
	{
		rMounts.push_back(hardPointR(i, "rail"));
	}

	for (i = 0; i < sHWB; i++)
	{
		hWBays.push_back(hardPointH(i, "heavy"));
	}
}

bool Ship::isDestroyed()
{
	return sHull <= 0;
}

bool Ship::isDisabled()
{
	return bIsSDisabled;
}

bool Ship::getShieldStatus()
{
	return bAreSSDisabled;
}

void Ship::toggleShields(int time)
{
	if (bAreSSDisabled == false)
	{
		bAreSSDisabled = true;
		sDTimer = time;
	}

	else
	{
		bAreSSDisabled = false;
	}
}

void Ship::toggleSStat(int time)
{
	if (bIsSDisabled == false)
	{
		bIsSDisabled = true;
		sDTimer = time;
	}

	else
	{
		bIsSDisabled = false;
	}
}

void Ship::disableShip(int time)
{
	//Disable shields
	disableShield(time);

	//Disable weapons
	if (sLB > 0)
	{		
		for (i = 0; i < sLB; i++)
		{
			lBanks.at(i).hpWeapon.toggleWeapon(time);
		}
	}

	if (sMT > 0)
	{		
		for (i = 0; i <sMT; i++)
		{
			mTurrets.at(i).hpWeapon.toggleWeapon(time);
		}
	}

	if (sBH > 0)
	{		
		for (i = 0; i <sBH; i++)	
		{
			bHolds.at(i).hpWeapon.toggleWeapon(time);
		}
	}

	if (sRM > 0)
	{
		for (i = 0; i <sRM; i++)
		{
			rMounts.at(i).hpWeapon.toggleWeapon(time);
		}
	}

	if (sHWB > 0)
	{
		for (i = 0; i <sHWB; i++)
		{
			hWBays.at(i).hpWeapon.toggleWeapon(time);
		}
	}

	//Set ship disabled status to true
	bIsSDisabled = true;

	//Set disabled timer
	sDTimer = time;
}

void Ship::disableShield(int time)
{
	sShield = 0;
	sDTimer = time;
}

void Ship::initShip(int sCode)
{	
	ds_s.rData("Ship_Data","select from",sCode);

	sName = ds_s.getSName();	
	sClass = ds_s.getSClass();	
	sTLevel = ds_s.getSTLevel();	
	sShield = ds_s.getSShield(); //get ship shields
	sMShield = sShield;
	sArmor = ds_s.getSArmor(); //get ship armor		
	sMArmor = sArmor;
	sHull = ds_s.getSHull(); //get ship hull		
	sMHull = sHull;
	sMInit = ds_s.getSMInit();
	sWHP = ds_s.getSWHP();	
	sLB = ds_s.getSLB();
	sMT = ds_s.getSMT();	
	sBH = ds_s.getSBH();
	sRM = ds_s.getSRM();
	sHWB = ds_s.getSHWB();
	sUCSpace = 0.0f;
	sMCSpace = ds_s.getSCargo();
	sSG2 = ds_s.getSSG2();
	sID = sCode;
	sSID = -1;
	sSTID = -1;
	sLocal = "none";	

	initHPoints();
}

int Ship::getMInit()
{
	return sMInit;
}

int Ship::getSDTimer()
{
	return sDTimer;
}

bool Ship::iWeapon(string wType, int iCode)
{
	if (wType == "laser")
	{
		//Cycle through availalbe hard points
		for (i = 0; i <= lBanks.size() - 1; i++)
		{
			if (i == lBanks.size()) //If no open hard points return false for further processing
			{
				return false;
			}
		
			else if (lBanks.at(i).hpWeapon.getWName() == "No Weapon Installed") //If no weapon installed, install the passed weapon
			{
				lBanks.at(i).hpWeapon.wSetup(iCode); //Set up data for passed weapon
				lBanks.at(i).hpWeapon.iWeapon(); //Install the passed weapon
				sULB += 1;
				return true; //We can only install one weapon at a time, so break the loop and return
			}			
		}
	}

	else if (wType == "missile")
	{
		for (i = 0; i <= mTurrets.size() - 1; i++)
		{
			if (i == mTurrets.size())
			{
				return false;
			}

			else if (mTurrets.at(i).hpWeapon.getWName() == "No Weapon Installed")
			{
				mTurrets.at(i).hpWeapon.wSetup(iCode);
				mTurrets.at(i).hpWeapon.iWeapon();
				sUMT += 1;
				return true;				
			}			
		}
	}

	else if (wType == "bomb")
	{
		for (i = 0; i <= bHolds.size() - 1; i++)
		{
			if (i == bHolds.size())
			{
				return false;
			}

			else if (bHolds.at(i).hpWeapon.getWName() == "No Weapon Installed")
			{
				bHolds.at(i).hpWeapon.wSetup(iCode);
				bHolds.at(i).hpWeapon.iWeapon();
				sUBH += 1;
				return true;				
			}			
		}
	}

	else if (wType == "rail")
	{		
		for (i = 0; i <= rMounts.size() - 1; i++)
		{
			if (i == rMounts.size())
			{
				return false;
			}

			else if (rMounts.at(i).hpWeapon.getWName() == "No Weapon Installed")
			{
				rMounts.at(i).hpWeapon.wSetup(iCode);
				rMounts.at(i).hpWeapon.iWeapon();
				sURM += 1;
				return true;				
			}			
		}
	}

	else if (wType == "heavy")
	{
		for (i = 0; i <= hWBays.size() - 1; i++)
		{
			if (i == hWBays.size())
			{
				return false;
			}

			else if (hWBays.at(i).hpWeapon.getWName() == "No Weapon Installed")
			{
				hWBays.at(i).hpWeapon.wSetup(iCode);
				hWBays.at(i).hpWeapon.iWeapon();
				sUHWB += 1;
				return true;				
			}			 
		}
	}
}

void Ship::sWSCenter(Player& mPlayer)
{
	if (sUWSpreads == 0)
	{
		cWSpread(mPlayer);
	}

	while (!bContinue)
	{
		pChoice = mp_s.sSCMenu();

		switch(pChoice)
		{
		case 1:

			cWSpread(mPlayer);
			break;

		case 2:
			pChoice = mp_s.sDSpread(sWSpreads, mPlayer);

			if (pChoice != 0)
			{
				clearWSpread(pChoice);
			}

			break;

		case 3:
			pChoice = mp_s.bCSpread(sWSpreads, mPlayer);

			editSpread(pChoice, mPlayer);
		}
	}

}

void Ship::cWSpread(Player& mPlayer)
{
	bContinue = false;
	
	while (!bContinue)
	{
		pChoice = mp_s.sCEWSpread(sWSpreads, mPlayer);

		if ((pChoice == 1) && (sWSpread1.size() == 0))
		{		
			sCWSpread = 1;
			bContinue = true;
		}

		else if ((pChoice == 2) && (sWSpread2.size() > 0))
		{
			sCWSpread = 2;
			bContinue = true;
		}

		else if ((pChoice == 3) && (sWSpread3.size() > 0))
		{
			sCWSpread = 3;
			bContinue = true;
		}

		else if ((pChoice == 4) && (sWSpread4.size() > 0))
		{
			sCWSpread = 4;
			bContinue = true;
		}

		else if ((pChoice == 5) && (sWSpread5.size() > 0))
		{
			sCWSpread = 5;
			bContinue = true;
		}

		else if ((pChoice == 6) && (sWSpread6.size() > 0))
		{
			sCWSpread = 6;
			bContinue = true;
		}

		else if ((pChoice == 7) && (sWSpread7.size() > 0))
		{
			sCWSpread = 7;
			bContinue = true;
		}

		else if ((pChoice == 8) && (sWSpread8.size() > 0))
		{
			sCWSpread = 8;
			bContinue = true;
		}

		//TODO: Check for 0
	}

	bContinue = false;

	if ((lHPoints < 1) && (mHPoints < 1) && (rHPoints < 1) && (hHPoints < 1)) //Check to see if any weapons are installed; if no weapons installed then cancel
	{
		cout << mp_s.mRMessage(27) << endl;
		cout << endl;
		cout << endl;
	}

	else
	{
		while (!bContinue)
		{
			pChoice = mp_s.sWSSelection(getULHP(), getUMTP(), getURM(), getUHWB()); //Get a weapon group to select weapons from

			switch(pChoice)
			{
			case 0:
				{
					cout << "Completing weapon spread creation..." << endl;
					bContinue = true;

					if (sTWSpread.size() == 0) //Extra checking in case player does not add any weapons to the spread; to prevent issues of a player trying to by passs spread creation in certain circumstances where it is required
					{
						sWSpreads = 0;
						sCWSpread = 0;
					}

					break;
				}

			case 1:
				{
					for (i = 0; i < lBanks.size(); i++)
					{
						tempLaser = lBanks.at(i).hpWeapon.getWeapon();

						if (tempLaser->getWName() != "No Weapon Installed") //Only continue if there is a weapon installed.  Since there is no way to distinguish between an installed and non-installed weapon after the initial installation if the player changes the weapon positions, the sUX variables cannot be used here.
						{
							pCChoice = mp_s.sLWSelection(tempLaser);

							for (i2 = 0; i2 < sTWSpread.size(); i2++)
							{
								if ((sTWSpread.at(i2).getHPWType() == "laser") && (sTWSpread.at(i2).getHPSlot() == lBanks.at(i).getHPSlot()))
								{
									cout << "This weapon has already been included in this weapon spread.  Please choose a different weapon." << endl;
									cout << endl;

									bWIsAUsed = true;
									break;
								}
							}

							if ((!bWIsAUsed) && (pCChoice == 'y' || pCChoice == 'Y'))
							{
								sTWSpread.push_back(hardPoint(lBanks.at(i).getHPSlot(),"laser"));
								break;
							}

							bWIsAUsed = false;
						}
					}

					break;
				}

			case 2:
				{
					for (i = 0; i < mTurrets.size(); i++)
					{
						tempMissile = mTurrets.at(i).hpWeapon.getWeapon();

						if (tempMissile->getWName() != "No Weapon Installed")
						{
							for (i2 = 0; i2 < sTWSpread.size(); i2++)
							{
								if ((sTWSpread.at(i2).getHPWType() == "missile") && (sTWSpread.at(i2).getHPSlot() == mTurrets.at(i).getHPSlot()))
								{
									cout << "This weapon has already been included in this weapon spread.  Please choose a different weapon." << endl;
									cout << endl;

									bWIsAUsed = true;
									break;
								}
							}

							if ((!bWIsAUsed) && (pCChoice == 'y' || pCChoice == 'Y'))
							{
								sTWSpread.push_back(hardPoint(mTurrets.at(i).getHPSlot(), "missile"));
								break;
							}

							bWIsAUsed = false;
						}
					}

					break;
				}

			case 3:
				{
					for (i = 0; i < rMounts.size(); i++)
					{
						tempRail = rMounts.at(i).hpWeapon.getWeapon();

						if (tempRail->getWName() != "No Weapon Installed")
						{
							for (i2 = 0; i2 < sTWSpread.size(); i2++)
							{
								if ((sTWSpread.at(i2).getHPWType() == "rail") && (sTWSpread.at(i2).getHPSlot() == rMounts.at(i).getHPSlot()))
								{
									cout << mp_s.mRMessage(41) << endl;
									cout << endl;

									bWIsAUsed = true;
									break;
								}
							}

							if ((!bWIsAUsed) && (pCChoice == 'y' || pCChoice == 'Y'))
							{
								sTWSpread.push_back(hardPoint(rMounts.at(i).getHPSlot(), "rail"));
								break;
							}
							
							bWIsAUsed = false;
						}						
					}

					break;

				}

			case 4:
				{
					for (i = 0; i < hWBays.size(); i++)
					{
						tempHeavy = hWBays.at(i).hpWeapon.getWeapon();

						if (tempHeavy->getWName() != "No Weapon Installed")
						{
							for (i2 = 0; i2 < sTWSpread.size(); i2++)
							{
								if ((sTWSpread.at(i2).getHPWType() == "heavy") && (sTWSpread.at(i2).getHPSlot() == hWBays.at(i).getHPSlot()))
								{
									cout << "This weapon has already been included in this weapon spread.  Please choose a different weapon." << endl;
									cout << endl;

									bWIsAUsed = true;
									break;
								}
							}

							if ((!bWIsAUsed) && (pCChoice == 'y' || pCChoice == 'Y'))
							{
								sTWSpread.push_back(hardPoint(hWBays.at(i).getHPSlot(), "heavy"));
								break;
							}

							bWIsAUsed = false;
						}
					}

					break;
				}
			}			
		}

		if (sCWSpread != 0)
		{
			for (i = 0; i < sTWSpread.size(); i++)
			{
				switch(sCWSpread)
				{
				case 1:
					sWSpread1.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 2:
					sWSpread2.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 3:
					sWSpread3.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 4:
					sWSpread4.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;

				case 5:
					sWSpread5.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 6:
					sWSpread6.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 7:
					sWSpread7.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
					
				case 8:
					sWSpread8.push_back(hardPoint(sTWSpread.at(i).getHPSlot(),sTWSpread.at(i).getHPWType()));
					break;
				}
			}
		}
	}
}

void Ship::clearWSpread(int wSpread)
{
	if (wSpread == 1)
	{
		 sWSpread1.clear();
	}

	else if (wSpread == 2)
	{
		 sWSpread2.clear();
	}
	
	else if (wSpread == 3)
	{
		 sWSpread3.clear();
	}
	
	else if (wSpread == 4)
	{
		 sWSpread4.clear();
	}

	else if (wSpread == 5)
	{
		 sWSpread5.clear();
	}

	else if (wSpread == 6)
	{
		 sWSpread6.clear();
	}

	else if (wSpread == 7)
	{
		 sWSpread7.clear();
	}

	else if (wSpread == 8)
	{
		 sWSpread8.clear();
	}

	else if (wSpread == 9)
	{
		 sWVector.clear();
	}
}

void Ship::editSpread(int wSpread, Player& mPlayer)
{
	cout << mp_s.mRMessage(2001) << endl;
}

void Ship::cWVector()
{
	mp_s.sWSSelection(getULHP(), getUMTP(), getURM(), getUHWB());

	for (i = 0; i < sWSystems.size(); i++)
	{
		if (sWSystems.at(i) == 1)
		{
			aWTVector(1);
		}

		if (sWSystems.at(i) == 2)
		{
			aWTVector(2);
		}

		if (sWSystems.at(i) == 4)
		{
			aWTVector(4);
		}

		if (sWSystems.at(i) == 5)
		{
			aWTVector(5);
		}
	}
}	

void Ship::cRSpread()
{
	for (i = 0; i <= sWSpreads; i++)
	{
		if (i == sWSpreads) //If no spreads are free then force overwrite of the weapon spread
		{
			clearWSpread(9);
			sCWSpread = 9;
		}

		else if (getSSize(i) == 0) //Else select the first empty spread
		{
			sCWSpread = i;
		}
	}
	
	sTIWeapons = sULB + sUMT + sURM + sUHWB; //We need the total number of installed weapons for the sR1 random

	sR1 = Random(1,sTIWeapons); //This determines the number of installed weapons to be used in the spread

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(1); i++)
	{
		if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempLBank.push_back(hardPointL(lBanks.at(i).getHPSlot(),lBanks.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(2); i++)
	{
		if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempMTurret.push_back(hardPointM(mTurrets.at(i).getHPSlot(),mTurrets.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(4); i++)
	{
		if (rMounts.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempRMount.push_back(hardPointR(rMounts.at(i).getHPSlot(),rMounts.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(5); i++)
	{
		if (hWBays.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempHWBay.push_back(hardPointH(hWBays.at(i).getHPSlot(),hWBays.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	for (i = 0; i <= sR1; i++)
	{
		if (i == sR1) //Needed to prevent index out of bounds crashes
		{

		}

		else
		{
			sR2 = Random(1,100); //Thie random will determine which weapon group to add from; the first non-used weapon will be used and if all the weapons have been used from a group then we move on to the next group

			if ((sR2 >= 1) && (sR2 <= 24))
			{
				if (tempLBank.size() == 0) //If all weapons used 
				{
					sR2 = 25; //then set sR2 to 25
				}

				else
				{

					addSVElement(sCWSpread,tempLBank.at(0).getHPWType(),tempLBank.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempLBank.erase(tempLBank.begin());
				}
			}

			//If's instead of else ifs because if a sereis of weapons has been completely used then we want to be able to switch to the next weapon group.

			if ((sR2 >= 25) && (sR2 <= 49))
			{
				if (tempMTurret.size() == 0) //If all weapons used 
				{
					sR2 = 50; //then set sR2 to 50
				}

				else
				{
					addSVElement(sCWSpread,tempMTurret.at(0).getHPWType(),tempMTurret.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempMTurret.erase(tempMTurret.begin());
				}
			}

			if ((sR2 >= 50) && (sR2 <= 74))
			{
				if (tempRMount.size() == 0) //If all weapons used 
				{
					sR2 = 75; //then set sR2 to 75
				}

				else
				{
					addSVElement(sCWSpread,tempRMount.at(0).getHPWType(),tempRMount.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempRMount.erase(tempRMount.begin());
				}
			}

			if (sR2 >= 75)
			{
				if (tempHWBay.size() == 0) //If all weapons used 
				{
					//sR2 = 101; //then set sR2 to 101
				}

				else
				{
					addSVElement(sCWSpread,tempHWBay.at(0).getHPWType(),tempHWBay.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempHWBay.erase(tempHWBay.begin());
				}
			}

			/*if (sR2 > 100) //All weapons have been used
			{
			break; //Just incase something goes wrong and the for loop does not cancel | Commented this block out because if all heavy weaps used it might be called before the first for loops runs out; figure out how to deal with that
			}*/ 
		}
	}
}

void Ship::cRSpread_B()
{
	if (sUBH != 0)
	{
		for (i = 0; i <= sWSpreads; i++)
		{
			if (i == sWSpreads) //If no spreads are free then force overwrite of the weapon spread
			{
				clearWSpread(9);
				sCWSpread = 9;
			}

			else if (getSSize(i) == 0) //Else select the first empty spread
			{
				sCWSpread = i;
			}
		}

		sR1 = Random(1,sUBH); //This determines the number of installed weapons to be used in the spread

		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(3); i++)
		{
			if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				tempBHold.push_back(hardPointB(bHolds.at(i).getHPSlot(),bHolds.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
			}
		}

		for (i = 0; i <= sR1; i++)
		{
			if (tempBHold.size() == 0 || i == sR1) //If all weapons used 
			{
			//	sR2 = 101; //then set sR2 to 101
				break; //and break
			}

			else
			{
				sR2 = Random(1,tempBHold.size()); //Thie random will determine which weapon group to add from; the first non-used weapon will be used and if all the weapons have been used from a group then we move on to the next group
				
				addSVElement(sCWSpread,tempBHold.at(i).getHPWType(),tempBHold.at(i).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
				
				//Now remove the current element from the temp vector as it has been used
				tempBHold.erase(tempBHold.begin()+i);
			}

			/*if (sR2 > 100) //All weapons have been used
			{
				break; //Just incase something goes wrong and the for loop does not cancel
			}*/
		}
	}

	else
	{
		cout << mp_s.mRMessage(2021) << endl;
	}
}

bool Ship::bAWInstalled()
{
	if (sULB > 0 || sUMT > 0 || sURM > 0 || sUHWB > 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Ship::bABInstalled()
{
	return sUBH > 0;
}

void Ship::aWTVector(int wtype)
{
	clearWSpread(9); //Make sure sWVector is clean

	if (wtype == 1)
	{
		for (i = 0; i < lBanks.size(); i++)
		{
			sWVector.push_back(hardPoint(i,"laser"));
		}
	}

	if (wtype == 2)
	{
		for (i = 0; i < mTurrets.size(); i++)
		{
			sWVector.push_back(hardPoint(i,"missile"));
		}
	}

	if (wtype == 4)
	{
		for (i = 0; i < rMounts.size(); i++)
		{
			sWVector.push_back(hardPoint(i,"rail"));
		}
	}

	if (wtype == 5)
	{
		for (i = 0; i < hWBays.size(); i++)
		{
			sWVector.push_back(hardPoint(i,"heavy"));
		}
	}
}

void Ship::cSWArray(int slot, string wtype)
{
	clearWSpread(9); //Make sure sWVector is clean
	sWVector.push_back(hardPoint(slot,wtype));
	sCWSpread = 9;
}

void Ship::sSAVector(bool bombing)
{
	sCWSpread = 9; //The weapon vector will store all out attacks
	clearWSpread(9); //Make sure the vector is empty before we begin

	if (!bombing) //If no bombing then continue
	{
		sTIWeapons = sULB+sUMT+sURM+sUHWB; //Get the total number of installed weapons - bombs

		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(1); i++)
		{
			if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				tempLBank.push_back(hardPointL(lBanks.at(i).getHPSlot(),lBanks.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
			}
		}

		for (i = 0; i < getWHPVSize(2); i++)
		{
			if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				tempMTurret.push_back(hardPointM(mTurrets.at(i).getHPSlot(),mTurrets.at(i).getHPWType()));
			}
		}

		for (i = 0; i < getWHPVSize(4); i++)
		{
			if (rMounts.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				tempRMount.push_back(hardPointR(rMounts.at(i).getHPSlot(),rMounts.at(i).getHPWType()));
			}
		}

		for (i = 0; i < getWHPVSize(5); i++)
		{
			if (hWBays.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				tempHWBay.push_back(hardPointH(hWBays.at(i).getHPSlot(),hWBays.at(i).getHPWType()));
			}
		}

		for (i = 0; i < sTIWeapons-1;) //Now loop for as many times as there are weapons installed with manual iteration
		{	
			sR1 = Random(1,4); //Get a random weapon type

			if (sR1 == 1) //Laser
			{
				if (tempLBank.size() != 0) //Need this so we do not go out of bounds on the index
				{
					addSVElement(sCWSpread,tempLBank.at(0).getHPWType(),tempLBank.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
					
					//Now remove the current element from the temp vector as it has been used
					tempLBank.erase(tempLBank.begin());
					i += 1; //Since we added a weapon, iterate i
				}
			}

			else if (sR1 == 2)
			{
				if (tempMTurret.size() != 0) //Need this so we do not go out of bounds on the index
				{
					addSVElement(sCWSpread,tempMTurret.at(0).getHPWType(),tempMTurret.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
					
					//Now remove the current element from the temp vector as it has been used
					tempMTurret.erase(tempMTurret.begin());
					i += 1; //Since we added a weapon, iterate i
				}
			}

			else if (sR1 == 3)
			{
				if (tempRMount.size() != 0) //Need this so we do not go out of bounds on the index
				{
					addSVElement(sCWSpread,tempRMount.at(0).getHPWType(),tempRMount.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
					
					//Now remove the current element from the temp vector as it has been used
					tempRMount.erase(tempRMount.begin());
					i += 1; //Since we added a weapon, iterate i
				}
			}

			else if (sR1 == 4)
			{
				if (tempHWBay.size() != 0) //Need this so we do not go out of bounds on the index
				{
					addSVElement(sCWSpread,tempHWBay.at(0).getHPWType(),tempHWBay.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
					
					//Now remove the current element from the temp vector as it has been used
					tempHWBay.erase(tempHWBay.begin());
					i += 1; //Since we added a weapon, iterate i
				}
			}
		}
	}

	else if (bombing)
	{
		sTIWeapons = sUBH; //Get the total number of installed weapons only bombs

		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(3); i++)
		{
			if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				tempBHold.push_back(hardPointB(bHolds.at(i).getHPSlot(),bHolds.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
			}
		}

		for (i = 0; i < sTIWeapons;) //Now loop for as many times as there are weapons installed with manual iteration
		{
			if (tempBHold.size() != 0) //Need this so we do not go out of bounds on the index
			{
				addSVElement(sCWSpread,tempBHold.at(0).getHPWType(),tempBHold.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
					
				//Now remove the current element from the temp vector as it has been used
				tempBHold.erase(tempBHold.begin());
				i += 1; //Since we added a weapon, iterate i
			}
		}
	}
}

int Ship::getSWSpreads()
{
	return sWSpreads;
}

void Ship::setMWSpreads(int i)
{
	sWSpreads = i;
}

void Ship::setCWSpread(int cspread)
{
	sCWSpread = cspread;
}

void Ship::setCWSystem(int i)
{
	if (i == 1)
	{
		sCWSystem == "laser";
	}

	else if (i == 2)
	{
		sCWSystem == "missile";
	}

	else if (i == 3)
	{
		sCWSystem == "bomb";
	}

	else if (i == 4)
	{
		sCWSystem == "rail";
	}

	else if (i == 5)
	{
		sCWSystem = "heavy";
	}
}

void Ship::cWSVector()
{
	clearWSpread(9);
	sCWSpread = 9;

	if (sCWSystem == "laser")
	{		
		for (i = 0; i < lBanks.size(); i++)
		{
			if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				addSVElement(sCWSpread, lBanks.at(i).getHPWType(), lBanks.at(i).getHPSlot());
			}
		}
	}

	else if (sCWSystem == "missile")
	{
		for (i = 0; i < mTurrets.size(); i++)
		{
			if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				addSVElement(sCWSpread, mTurrets.at(i).getHPWType(), mTurrets.at(i).getHPSlot());
			}
		}
	}

	else if (sCWSystem == "bomb")
	{
		for (i = 0; i < bHolds.size(); i++)
		{
			if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				addSVElement(sCWSpread, bHolds.at(i).getHPWType(), bHolds.at(i).getHPSlot());
			}
		}
	}

	else if (sCWSystem == "rail")
	{
		for (i = 0; i < rMounts.size(); i++)
		{
			if (rMounts.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				addSVElement(sCWSpread, rMounts.at(i).getHPWType(), rMounts.at(i).getHPSlot());
			}
		}
	}

	else if (sCWSystem == "heavy")
	{
		for (i = 0; i < hWBays.size(); i++)
		{
			if (hWBays.at(i).hpWeapon.getWName() != "No Weapon Installed")
			{
				addSVElement(sCWSpread, hWBays.at(i).getHPWType(), hWBays.at(i).getHPSlot());
			}
		}
	}
}

string Ship::getCWSystem()
{
	return sCWSystem;
}

hardPoint Ship::getSHPoint(int i)
{
	if (sCWSpread == 1)
	{
		placeHolder = sWSpread1.at(i);

		return placeHolder;
	}

	if (sCWSpread == 2)
	{
		placeHolder = sWSpread2.at(i);

		return placeHolder;
	}

	if (sCWSpread == 3)
	{
		placeHolder = sWSpread3.at(i);

		return placeHolder;
	}

	if (sCWSpread == 4)
	{
		placeHolder = sWSpread4.at(i);

		return placeHolder;
	}

	if (sCWSpread == 5)
	{
		placeHolder = sWSpread5.at(i);

		return placeHolder;
	}

	if (sCWSpread == 6)
	{
		placeHolder = sWSpread6.at(i);

		return placeHolder;
	}

	if (sCWSpread == 7)
	{
		placeHolder = sWSpread7.at(i);

		return placeHolder;
	}

	if (sCWSpread == 8)
	{
		placeHolder = sWSpread8.at(i);

		return placeHolder;
	}

	if (sCWSpread == 9)
	{
		placeHolder = sWVector.at(i);

		return placeHolder;
	}
}

hardPoint Ship::getWVHPoint(int i)
{
	placeHolder = sWVector.at(i);

	return placeHolder;
}

int Ship::getSSize(int i)
{
	if (i == 1)
	{
		return sWSpread1.size();
	}

	else if (i == 2)
	{
		return sWSpread2.size();
	}

	else if (i == 3)
	{
		return sWSpread3.size();
	}

	else if (i == 4)
	{
		return sWSpread4.size();
	}

	else if (i == 5)
	{
		return sWSpread5.size();
	}

	else if (i == 6)
	{
		return sWSpread6.size();
	}

	else if (i == 7)
	{
		return sWSpread7.size();
	}

	else if (i == 8)
	{
		return sWSpread8.size();
	}

	else if (i == 9)
	{
		return sWVector.size();
	}
}

int Ship::getWHPVSize(int i)
{
	switch(i)
	{
	case 1:
		return lBanks.size();
		break;
	
	case 2:
		return mTurrets.size();
		break;

	case 3:
		return bHolds.size();
		break;

	case 4:
		return rMounts.size();
		break;

	case 5:
		return hWBays.size();
		break;
	}
}

vector<hardPoint> Ship::getSVect(int i)
{
	if (i == 1)
	{
		return sWSpread1;
	}

	else if (i == 2)
	{
		return sWSpread2;
	}
	
	else if (i == 3)
	{
		return sWSpread3;
	}
	
	else if (i == 4)
	{
		return sWSpread4;
	}

	else if (i == 5)
	{
		return sWSpread5;
	}

	else if (i == 6)
	{
		return sWSpread6;
	}

	else if (i == 7)
	{
		return sWSpread7;
	}

	else if (i == 8)
	{
		return sWSpread8;
	}

	else if (i == 9)
	{
		return sWVector;
	}
}

string Ship::getLWDType(int slot)
{
	return lBanks.at(slot).hpWeapon.getWDType();
}

string Ship::getMWDType(int slot)
{
	return mTurrets.at(slot).hpWeapon.getWDType();
}

string Ship::getBWDType(int slot)
{
	return bHolds.at(slot).hpWeapon.getWDType();
}

string Ship::getRWDType(int slot)
{
	return rMounts.at(slot).hpWeapon.getWDType();
}

string Ship::getHWDType(int slot)
{
	return hWBays.at(slot).hpWeapon.getWDType();
}

Ship* Ship::rShip()
{
	return this;
}

void Ship::addTDamage(float damage, int turns, string type)
{
	cDamage.push_back(tDamage(damage, turns, type));
}

void Ship::checkTDamage()
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

void Ship::removeTDamage(int i)
{
	cDamage.erase(cDamage.begin()+i);
}

void Ship::dTDecrement()
{
	if (sDTimer == 1) //If one turn left enable disabled systems and set timer to 0
	{
		if (bIsSDisabled)
		{
			bIsSDisabled = false;
		}

		if (bAreSSDisabled)
		{
			bAreSSDisabled = false;
		}

		sDTimer = 0;
	}
	
	else if (sDTimer > 1) //If more than one turn left, decrement the timer by one
	{
		sDTimer -= 1;
	}
}

void Ship::setPos(int x, int y, int z)
{
	sPosX = x;
	sPosY = y;
	sPosZ = z;
}

int Ship::getXPos()
{
	return sPosX;
}

int Ship::getYPos()
{
	return sPosY;
}

int Ship::getZPos()
{
	return sPosZ;
}

void Ship::sPMove(Player& mPlayer, NPC& mNPC)
{
	sAMInit = getMInit();
	bIsCAffirmitive = false;
	bIsPDone = false;
	sMSelection1 = 0;
	sMSelection2 = 0;

	while (!bIsPDone)
	{
		if (sAMInit == 0)
		{
			cout << mp_s.mRMessage(40) << endl;
			break; //If no more MIinit, break loop
		}

		//Display location of player and target ship and distance between them
		mp_s.nBSPos(mPlayer,mNPC);

		sMSelection1 = mp_s.sMSystem(sAMInit);

		// Update coordinates based on selection.
		switch( sMSelection1 )
		{
		case 1:
			while (!bIsCAffirmitive)
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosZ += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 2:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosY += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 3:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosY -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 4:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosX -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 5:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosX += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 6:
			while ( !bIsCAffirmitive)
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosZ -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;

		default:
			cout << mp_s.mRMessage(39) << endl;
			bIsPDone = true;
			break;
		}

		//reset for next loop
		bIsCAffirmitive = false;
	}

	cout << endl;
}

void Ship::sPMove_M(Player& mPlayer, Asteroid roid)
{
	sAMInit = getMInit();
	bIsCAffirmitive = false;
	bIsPDone = false;
	sMSelection1 = 0;
	sMSelection2 = 0;

	while (!bIsPDone)
	{
		if (sAMInit == 0)
		{
			cout << mp_s.mRMessage(40) << endl;
			break; //If no more MIinit, break loop
		}

		//Display location of player and target ship and distance between them
		mp_s.mTPos(mPlayer,roid);

		sMSelection1 = mp_s.sMSystem2(sAMInit);

		// Update coordinates based on selection.
		switch( sMSelection1 )
		{
		case 1:
			while (!bIsCAffirmitive)
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosZ += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 2:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosY += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 3:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosY -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 4:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosX -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 5:
			while ( !bIsCAffirmitive )
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;

				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosX += sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;
		
		case 6:
			while ( !bIsCAffirmitive)
			{
				cout << mp_s.mRMessage(36) << endl;
				cout <<"> ";
				cin >> sMSelection2;
				
				if ((sMSelection2 <= sAMInit) || (sMSelection2 >= 0))
				{
					cout << mp_s.mRMessage(37) << endl;
					sPosZ -= sMSelection2;
					sAMInit -= sMSelection2;
					bIsCAffirmitive = true;
				}

				else if ((sMSelection2 > sAMInit) || (sMSelection2 < 0))
				{
					cout << mp_s.mRMessage(38) << endl;
					sMSelection2 = 0;
					bIsCAffirmitive = false;
				}
			}

			break;

		default:
			cout << mp_s.mRMessage(39) << endl;
			bIsPDone = true;
			break;
		}

		//reset for next loop
		bIsCAffirmitive = false;
	}

	cout << endl;
}

void Ship::sAIMove(Player& mPlayer, NPC& mNPC, bool ally)
{
	//
	sMRand1 = Random(1,20);
	sMRand2 = Random(1,10);
	sMRand3 = Random(1,6);

	//Determine if a ship moves towards or away from target
	sMRand4 = Random(1,10);
	sMRand5 = Random(1,20);

	if (ally)
	{
		sEDist = m_s.getDistance(sPosX, mNPC.Ship.getXPos(), sPosY, mNPC.Ship.getYPos(), sPosZ, mNPC.Ship.getZPos());

		if (sEDist > 13.00f)
		{
			sMRand6 = Random(1,3); //Determine which direction to move in

			if (sMRand6 == 1)
			{
				if (mNPC.Ship.getXPos() > sPosX)
				{
					sPosX -= 1;
				}

				else if (mNPC.Ship.getXPos() < sPosX)
				{
					sPosX += 1;
				}
			}

			else if (sMRand6 == 2)
			{
				if (mNPC.Ship.getYPos() > sPosY)
				{
					sPosY -= 1;
				}

				else if (mNPC.Ship.getYPos() < sPosY)
				{
					sPosY += 1;
				}
			}

			else if (sMRand6 == 3)
			{
				if (mNPC.Ship.getZPos() > sPosZ)
				{
					sPosZ -= 1;
				}

				else if (mNPC.Ship.getZPos() < sPosZ)
				{
					sPosZ += 1;
				}
			}
		}
			
		else if((sEDist > 8.00f) && (sEDist <= 13.00f))
		{
			if ((((sMRand4 >= 1) && (sMRand4 < 4)) && ((sMRand5 >= 12) && (sMRand5 < 19)))) //If true, move toward target 
			{
				sMRand6 = Random(1,3);

				if (sMRand6 == 1)
				{
					if (mNPC.Ship.getXPos() > sPosX)
					{
						sPosX -= 1;
					}

					else if (mNPC.Ship.getXPos() < sPosX)
					{
						sPosX += 1;
					}
				}

				else if (sMRand6 == 2)
				{
					if (mNPC.Ship.getYPos() > sPosY)
					{
						sPosY -= 1;
					}

					else if (mNPC.Ship.getYPos() < sPosY)
					{
						sPosY += 1;
					}
				}

				else if (sMRand6 == 3)
				{
					if (mNPC.Ship.getZPos() > sPosZ)
					{
						sPosZ -= 1;
					}

					else if (mNPC.Ship.getZPos() < sPosZ)
					{
						sPosZ += 1;
					}
				}
			}
		
			else //Esle move away from target
			{
				sMRand6 = Random(1,3);

				if (sMRand6 == 1)
				{
					if (mNPC.Ship.getXPos() > sPosX)
					{
						sPosX += 1;
					}

					else if (mNPC.Ship.getXPos() < sPosX)
					{
						sPosX -= 1;
					}
				}

				else if (sMRand6 == 2)
				{
					if (mNPC.Ship.getYPos() > sPosY)
					{
						sPosY += 1;
					}

					else if (mNPC.Ship.getYPos() < sPosY)
					{
						sPosY -= 1;
					}
				}

				else if (sMRand6 == 3)
				{
					if (mNPC.Ship.getZPos() > sPosZ)
					{
						sPosZ += 1;
					}

					else if (mNPC.Ship.getZPos() < sPosZ)
					{
						sPosZ -= 1;
					}
				}
			}
		}

		else if (sEDist < 8.00f)
		{
			sMRand6 = Random(1,3);

			if (sMRand6 == 1)
			{
				if (mNPC.Ship.getXPos() > sPosX)
				{
					sPosX += 1;
				}

				else if (mNPC.Ship.getXPos() < sPosX)
				{
					sPosX -= 1;
				}
			}

			else if (sMRand6 == 2)
			{
				if (mNPC.Ship.getYPos() > sPosY)
				{
					sPosY += 1;
				}

				else if (mNPC.Ship.getYPos() < sPosY)
				{
					sPosY -= 1;
				}
			}

			else if (sMRand6 == 3)
			{
				if (mNPC.Ship.getZPos() > sPosZ)
				{
					sPosZ += 1;
				}
				
				else if (mNPC.Ship.getZPos() < sPosZ)
				{
					sPosZ -= 1;
				}
			}
		}
	}

	else if (!ally)
	{
		sEDist = m_s.getDistance(sPosX, mPlayer.Ship.getXPos(), sPosY, mPlayer.Ship.getYPos(), sPosZ, mPlayer.Ship.getZPos());

		if (sEDist > 13.00f)
		{
			sMRand6 = Random(1,3); //Determine which direction to move in

			if (sMRand6 == 1)
			{
				if (mPlayer.Ship.getXPos() > sPosX)
				{
					sPosX -= 1;
				}

				else if (mPlayer.Ship.getXPos() < sPosX)
				{
					sPosX += 1;
				}
			}

			else if (sMRand6 == 2)
			{
				if (mPlayer.Ship.getYPos() > sPosY)
				{
					sPosY -= 1;
				}

				else if (mPlayer.Ship.getYPos() < sPosY)
				{
					sPosY += 1;
				}
			}

			else if (sMRand6 == 3)
			{
				if (mPlayer.Ship.getZPos() > sPosZ)
				{
					sPosZ -= 1;
				}

				else if (mPlayer.Ship.getZPos() < sPosZ)
				{
					sPosZ += 1;
				}
			}
		}
			
		else if((sEDist > 8.00f) && (sEDist <= 13.00f))
		{
			if ((((sMRand4 >= 1) && (sMRand4 < 4)) && ((sMRand5 >= 12) && (sMRand5 < 19)))) //If true, move toward target 
			{
				sMRand6 = Random(1,3);

				if (sMRand6 == 1)
				{
					if (mPlayer.Ship.getXPos() > sPosX)
					{
						sPosX -= 1;
					}

					else if (mPlayer.Ship.getXPos() < sPosX)
					{
						sPosX += 1;
					}
				}

				else if (sMRand6 == 2)
				{
					if (mPlayer.Ship.getYPos() > sPosY)
					{
						sPosY -= 1;
					}

					else if (mPlayer.Ship.getYPos() < sPosY)
					{
						sPosY += 1;
					}
				}

				else if (sMRand6 == 3)
				{
					if (mPlayer.Ship.getZPos() > sPosZ)
					{
						sPosZ -= 1;
					}

					else if (mPlayer.Ship.getZPos() < sPosZ)
					{
						sPosZ += 1;
					}
				}
			}
		
			else //Esle move away from target
			{
				sMRand6 = Random(1,3);

				if (sMRand6 == 1)
				{
					if (mPlayer.Ship.getXPos() > sPosX)
					{
						sPosX += 1;
					}
					
					else if (mPlayer.Ship.getXPos() < sPosX)
					{
						sPosX -= 1;
					}
				}

				else if (sMRand6 == 2)
				{
					if (mPlayer.Ship.getYPos() > sPosY)
					{
						sPosY += 1;
					}

					else if (mPlayer.Ship.getYPos() < sPosY)
					{
						sPosY -= 1;
					}
				}

				else if (sMRand6 == 3)
				{
					if (mPlayer.Ship.getZPos() > sPosZ)
					{
						sPosZ += 1;
					}

					else if (mPlayer.Ship.getZPos() < sPosZ)
					{
						sPosZ -= 1;
					}
				}
			}
		}

		else if (sEDist < 8.00f)
		{
			sMRand6 = Random(1,3);

			if (sMRand6 == 1)
			{
				if (mPlayer.Ship.getXPos() > sPosX)
				{
					sPosX += 1;
				}

				else if (mPlayer.Ship.getXPos() < sPosX)
				{
					sPosX -= 1;
				}
			}

			else if (sMRand6 == 2)
			{
				if (mPlayer.Ship.getYPos() > sPosY)
				{
					sPosY += 1;
				}

				else if (mPlayer.Ship.getYPos() < sPosY)
				{
					sPosY -= 1;
				}
			}

			else if (sMRand6 == 3)
			{
				if (mPlayer.Ship.getZPos() > sPosZ)
				{
					sPosZ += 1;
				}
				
				else if (mPlayer.Ship.getZPos() < sPosZ)
				{
					sPosZ -= 1;
				}
			}
		}
	}
}

void Ship::clearSData()
{
	sName = " ";	
	sClass = " ";	
	sTLevel = 0;	
	sShield = 0.00f; //get ship shields
	sArmor = 0.00f; //get ship armor		
	sHull = 0.00f; //get ship hull		
	sMInit = 0;
	sWHP = 0;	
	sLB = 0;
	sMT = 0;	
	sBH = 0;
	sRM = 0;
	sHWB = 0;
}

int Ship::getSWHP()
{
	return sWHP;
}

int Ship::getULHP()
{
	return sULB;
}

int Ship::getUMTP()
{
	return sUMT;
}

int Ship::getUBH()
{
	return sUBH;
}

int Ship::getURM()
{
	return sURM;
}

int Ship::getUHWB()
{
	return sUHWB;
}

void Ship::setLHP(int i)
{
	sLB = i;
}

void Ship::setULHP(int i)
{
	sULB = i;
}

void Ship::setMTP(int i)
{
	sMT = i;
}

void Ship::setUMTP(int i)
{
	sUMT = i;
}

void Ship::setBH(int i)
{
	sBH = i;
}

void Ship::setUBH(int i)
{
	sUBH  = i;
}

void Ship::setRM(int i)
{
	sRM = i;
}

void Ship::setURM(int i)
{
	sURM = i;
}

void Ship::setHWB(int i)
{
	sHWB = i;
}

void Ship::setUHWB(int i)
{
	sUHWB = i;
}

void Ship::setSWHP(int i)
{
	sWHP = i;
}

void Ship::setMInit(int i)
{
	sMInit = i;
}

void Ship::addSVElement(int sID, string type, int slot)
{
	if (sID == 1)
	{
		sWSpread1.push_back(hardPoint());

		sWSpread1.at(sWSpread1.size()-1).setHPSlot(slot);
		sWSpread1.at(sWSpread1.size()-1).setHPWType(type);
	}

	else if (sID == 2)
	{
		sWSpread2.push_back(hardPoint());

		sWSpread2.at(sWSpread2.size()-1).setHPSlot(slot);
		sWSpread2.at(sWSpread2.size()-1).setHPWType(type);
	}

	else if (sID == 3)
	{
		sWSpread3.push_back(hardPoint());

		sWSpread3.at(sWSpread3.size()-1).setHPSlot(slot);
		sWSpread3.at(sWSpread3.size()-1).setHPWType(type);
	}

	else if (sID == 4)
	{
		sWSpread4.push_back(hardPoint());

		sWSpread4.at(sWSpread4.size()-1).setHPSlot(slot);
		sWSpread4.at(sWSpread4.size()-1).setHPWType(type);
	}

	else if (sID == 5)
	{
		sWSpread5.push_back(hardPoint());

		sWSpread5.at(sWSpread5.size()-1).setHPSlot(slot);
		sWSpread5.at(sWSpread5.size()-1).setHPWType(type);
	}

	else if (sID == 6)
	{
		sWSpread6.push_back(hardPoint());

		sWSpread6.at(sWSpread6.size()-1).setHPSlot(slot);
		sWSpread6.at(sWSpread6.size()-1).setHPWType(type);
	}

	else if (sID == 7)
	{
		sWSpread7.push_back(hardPoint());

		sWSpread7.at(sWSpread7.size()-1).setHPSlot(slot);
		sWSpread7.at(sWSpread7.size()-1).setHPWType(type);
	}

	else if (sID == 8)
	{
		sWSpread8.push_back(hardPoint());

		sWSpread8.at(sWSpread8.size()-1).setHPSlot(slot);
		sWSpread8.at(sWSpread8.size()-1).setHPWType(type);
	}

	else if (sID == 9)
	{
		sWVector.push_back(hardPoint());

		sWVector.at(sWVector.size()-1).setHPSlot(slot);
		sWVector.at(sWVector.size()-1).setHPWType(type);
	}
}

void Ship::addWHPVElement(int slot, int wID, string type)
{
	if (type == "laser")
	{
		lBanks.push_back(hardPointL(slot, "laser"));

		lBanks.at(lBanks.size()-1).hpWeapon.wSetup(wID);
		lBanks.at(lBanks.size()-1).hpWeapon.iWeapon();
	}

	else if (type == "mining laser")
	{
		lBanks.push_back(hardPointL(slot, "mining laser"));

		lBanks.at(lBanks.size()-1).hpWeapon.wSetup(wID);
		lBanks.at(lBanks.size()-1).hpWeapon.iWeapon();
	}

	else if (type == "missile")
	{
		mTurrets.push_back(hardPointM(slot, "missile"));

		mTurrets.at(mTurrets.size()-1).hpWeapon.wSetup(wID);
		mTurrets.at(mTurrets.size()-1).hpWeapon.iWeapon();
	}

	else if (type == "bomb")
	{
		bHolds.push_back(hardPointB(slot, "bomb"));

		bHolds.at(bHolds.size()-1).hpWeapon.wSetup(wID);
		bHolds.at(bHolds.size()-1).hpWeapon.iWeapon();
	}

	else if (type == "rail")
	{
		rMounts.push_back(hardPointR(slot, "rail"));

		rMounts.at(rMounts.size()-1).hpWeapon.wSetup(wID);
		rMounts.at(rMounts.size()-1).hpWeapon.iWeapon();
	}

	else if (type == "heavy")
	{
		hWBays.push_back(hardPointH(slot, "heavy"));

		hWBays.at(hWBays.size()-1).hpWeapon.wSetup(wID);
		hWBays.at(hWBays.size()-1).hpWeapon.iWeapon();
	}
}

int Ship::getCSVector()
{
	return sCWSpread;
}

void Ship::cWSVector_AI()
{
	clearWSpread(9);
	sCWSpread = 9;

	bContinue = false;
	initLB = 0;
	initMT = 0;

	while (!bContinue)
	{
		sR1 = Random(1,2);

		if (sR1 == 1)
		{
			if (lBanks.size() > 0)
			{
				for (i = 0; i <= lBanks.size(); i++)
				{
					if ((i == lBanks.size()) && (initLB == 0))
					{
						initLB = -1;
						break;
					}

					if ((i == lBanks.size()) && (initLB != 0))
					{
						bContinue = true;
						break;
					}

					else if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed")
					{
						initLB += 1;
					}
				}
			}
		}

		else if (sR1 == 2)
		{
			if (mTurrets.size() > 0)
			{
				for (i = 0; i <= mTurrets.size(); i++)
				{
					if ((i == mTurrets.size()) && (initMT == 0))
					{
						initMT = -1;
						break;
					}

					if ((i == mTurrets.size()) && (initMT != 0))
					{
						bContinue = true;
						break;
					}

					else if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed")
					{
						initMT += 1;
					}
				}
			}
		}

		if ((initLB == -1) && (initMT == -1))
		{
			break;
		}
	}

	if (initLB > 0)
	{
		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(1); i++)
		{
			if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				addSVElement(sCWSpread,lBanks.at(0).getHPWType(),lBanks.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
			}
		}
	}

	else if (initMT > 0)
	{
		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(2); i++)
		{
			if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				addSVElement(sCWSpread,mTurrets.at(0).getHPWType(),mTurrets.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
			}
		}
	}				
}

void Ship::cWVector_AI()
{
	clearWSpread(9);
	sCWSpread = 9;

	sTIWeapons = sULB + sUMT + sURM + sUHWB; //We need the total number of installed weapons for the sR1 random

	sR1 = Random(1,sTIWeapons); //This determines the number of installed weapons to be used in the spread

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(1); i++)
	{
		if (lBanks.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempLBank.push_back(hardPointL(lBanks.at(i).getHPSlot(),lBanks.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(2); i++)
	{
		if (mTurrets.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempMTurret.push_back(hardPointM(mTurrets.at(i).getHPSlot(),mTurrets.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	for (i = 0; i <= sR1; i++)
	{
		if (i == sR1) //Needed to prevent index out of bounds crashes
		{

		}

		else
		{
			sR2 = Random(1,49); //Thie random will determine which weapon group to add from; the first non-used weapon will be used and if all the weapons have been used from a group then we move on to the next group

			if ((sR2 >= 1) && (sR2 <= 24))
			{
				if (tempLBank.size() == 0) //If all weapons used 
				{
					sR2 = 25; //then set sR2 to 25
				}

				else
				{
					addSVElement(sCWSpread,tempLBank.at(0).getHPWType(),tempLBank.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempLBank.erase(tempLBank.begin());
					break;
				}
			}

			//If's instead of else ifs because if a sereis of weapons has been completely used then we want to be able to switch to the next weapon group.

			if ((sR2 >= 25) && (sR2 <= 49))
			{
				if (tempMTurret.size() == 0) //If all weapons used 
				{
					sR2 = 50; //then set sR2 to 50
				}

				else
				{
					addSVElement(sCWSpread,tempMTurret.at(0).getHPWType(),tempMTurret.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

					//Now remove the current element from the temp vector as it has been used
					tempMTurret.erase(tempMTurret.begin());
					break;
				}
			}
		}
	}
}

void Ship::cWSVector_AI_PB()
{
	clearWSpread(9);
	sCWSpread = 9;

	bContinue = false;
	initBH = 0;
	
	while (!bContinue)
	{
		if (bHolds.size() > 0)
		{
			for (i = 0; i <= bHolds.size(); i++)
			{
				if ((i == bHolds.size()) && (initBH == 0))
				{
					initBH = -1;
					break;
				}

				if ((i == bHolds.size()) && (initBH != 0))
				{
					bContinue = true;
					break;
				}

				else if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed")
				{
					initBH += 1;
				}
			}
		}
	}

	if (initBH > 0)
	{
		//Get all installed weapons and load them into tmeporary vectors for use later
		for (i = 0; i < getWHPVSize(1); i++)
		{
			if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
			{
				addSVElement(sCWSpread,bHolds.at(0).getHPWType(),bHolds.at(0).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed
			}
		}
	}
}

void Ship::cWVector_AI_PB()
{
	clearWSpread(9);
	sCWSpread = 9;

	sTIWeapons = sUBH; //We need the total number of installed weapons for the sR1 random

	sR1 = Random(1,sTIWeapons); //This determines the number of installed weapons to be used in the spread

	//Get all installed weapons and load them into tmeporary vectors for use later
	for (i = 0; i < getWHPVSize(3); i++)
	{
		if (bHolds.at(i).hpWeapon.getWName() != "No Weapon Installed") //If there is a weapons installed
		{
			tempBHold.push_back(hardPointB(bHolds.at(i).getHPSlot(),bHolds.at(i).getHPWType())); //then load the slot and weapon type into the temp vector
		}
	}

	addSVElement(sCWSpread,tempBHold.at(sR1-1).getHPWType(),tempBHold.at(sR1-1).getHPSlot()); //Repurpose the add element function used primarily for loading data; this way no extra code or duplicate function is needed

	tempBHold.clear();
}

void Ship::calcCSpace()
{
	tempSpace = 0.0f;

	for (i = 0; i < sCargo.size(); i++)
	{
		tempSpace += sCargo.at(i).getISpace() * sCargo.at(i).getIAmount();
	}

	sUCSpace = tempSpace;
}

float Ship::getCSpace()
{
	calcCSpace();

	return sUCSpace;
}

void Ship::updateMCSpace(float space, string operation)
{
	if (operation == "add")
	{
		sMCSpace += space;
	}

	else if (operation == "sub")
	{
		sMCSpace -= space;
	}

	else if (operation == "set")
	{
		sMCSpace = space;
	}
}

float Ship::getMCSpace()
{
	return sMCSpace;
}

bool Ship::addCItem(int iID, string iType, int amount, bool mining)
{
	if (iType == "Ship")
	{
		ds_s.rData("Ship_Data","select from",iID);

		if (loadCargo(iID, amount, iType, ds_s.getSSG2(), mining, ds_s.getSName()))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else if (iType == "Resource")
	{
		ds_s.rData("Resource","select from",iID);

		for (i = 0; i <= sCargo.size(); i++)
		{
			if (i == sCargo.size())
			{
				if (loadCargo(iID, amount, iType, ds_s.getResSG2(), mining, ds_s.getResName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}

			else if ((iID == sCargo.at(i).getIID()) && (iType == sCargo.at(i).getIType()))
			{
				if (updateCIAmount(i, amount, "add", mining,  ds_s.getResName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
	}

	else if (iType == "Ore")
	{
		ds_s.rData("Ore","select from",iID);

		for (i = 0; i <= sCargo.size(); i++)
		{
			if (i == sCargo.size())
			{
				if (loadCargo(iID, amount, iType, ds_s.getOSG2(), mining,  ds_s.getOName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}

			else if ((iID == sCargo.at(i).getIID()) && (iType == sCargo.at(i).getIType()))
			{
				if (updateCIAmount(i, amount, "add", mining,  ds_s.getOName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
	}

	else if (iType == "Item" || iType == "PShield" || iType == "PDefense" || iType == "Module")
	{
		ds_s.rData("Equipment_Data","select from",iID);

		for (i = 0; i <= sCargo.size(); i++)
		{
			if (i == sCargo.size())
			{
				if (loadCargo(iID, amount, iType, ds_s.getESG2(), mining,  ds_s.getEName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}

			else if ((iID == sCargo.at(i).getIID()) && (iType == sCargo.at(i).getIType()))
			{
				if (updateCIAmount(i, amount, "add", mining, ds_s.getEName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
	}

	else if (iType == "Weapon")
	{
		ds_s.rData("Weapon_Data","select from",iID);

		for (i = 0; i <= sCargo.size(); i++)
		{
			if (i == sCargo.size())
			{
				if (loadCargo(iID, amount, iType, ds_s.getWSG2(), mining,  ds_s.getWName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}

			else if ((iID == sCargo.at(i).getIID()) && (iType == sCargo.at(i).getIType()))
			{
				if (updateCIAmount(i, amount, "add", mining, ds_s.getWName()))
				{
					return true;
				}

				else
				{
					return false;
				}
			}
		}
	}
}

bool Ship::updateCIAmount(int slot, int amount, string operation, bool mining, string name)
{
	if (operation == "add")
	{
		tempISpace = sCargo.at(slot).getISpace();

		if (checkSpace(tempISpace * amount)) //Check to make sure we are not adding too many items
		{
			sCargo.at(slot).updateIAmount(amount, "add");
			return true;
		}

		else //If there are too many items, causing max cargo space to be reached then
		{
			if (!mining) //If not mining we do not store the item(s) at all
			{
				cout << "Items could not be stored.  Not enough space in cargo hold" << endl;

				return false;
			}

			else if (mining) //If mining then
			{
				while (!checkSpace(tempISpace * amount)) //We start removing an item at a time until it can fit
				{
					amount -= 1;
					lostItem += 1;
				}

				if (amount > 0) //Then display the losses or
				{
					cout << "Only " << amount << " units of " << name << " could be stored.  " << lostItem << " units were destroyed." << endl;

					sCargo.at(slot).updateIAmount(amount, "add");
					return true;
				}

				else //If none could be stored display all units lost
				{
					cout << "All units of " << name << " (" << lostItem << ") were destroyed.  Reason: Full cargo hold" << endl;
					return false;
				}
			}
		}
	}

	else if (operation == "sub")
	{
		if (amount >= sCargo.at(slot).getIAmount())
		{
			removeCItem(slot);
			return true;
		}

		else
		{
			sCargo.at(slot).updateIAmount(amount, "sub");
			return true;
		}
	}

	else if (operation == "set")
	{
		sCargo.at(slot).updateIAmount(amount, "set");
		return true;
	}
}

void Ship::removeCItem(int slot)
{
	sCargo.erase(sCargo.begin()+slot);
}

bool Ship::loadCargo(int iID, int iAmount, string itype, float sg2, bool mining, string name)
{
	if (checkSpace(iAmount * sg2))
	{
		sCargo.push_back(sInv(iID, iAmount, itype, sg2, false));
		return true;
	}
	else //If there are too many items, causing max cargo space to be reached then
	{
		if (!mining) //If not mining we do not store the item(s) at all
		{
			cout << "Items could not be stored.  Not enough space in cargo hold" << endl;
			return false;
		}

		else if (mining) //If mining then
		{
			while (!checkSpace(iAmount * sg2)) //We start removing an item at a time until it can fit
			{
				iAmount -= 1;
				lostItem += 1;
			}

			if (iAmount > 0) //Then display the losses or
			{
				cout << "Only " << iAmount << " units of " << name << " could be stored.  " << lostItem << " units were destroyed." << endl;

				sCargo.push_back(sInv(iID, iAmount, itype, sg2, false));
					
				return true;
			}

			else //If none could be stored display all units lost
			{
				cout << "All units of " << name << " (" << lostItem << ") were destroyed.  Reason: Full cargo hold" << endl;
				return false;
			}
		}
	}
}

void Ship::loadSCargo(int amount, string type, Ship2 lShip)
{
	sCargo.push_back(sInv(lShip, true, lShip.getID(), 1));
	sCargo.at(sCargo.size()-1).setIAmount(amount);
	sCargo.at(sCargo.size()-1).setIType(type);
}

float Ship::getSSG2()
{
	return sSG2;
}

void Ship::setSSG2(float sg2)
{
	sSG2 = sg2;
}

bool Ship::getMLInfo(int* cTime, int* mlTDist, float* cMAmount)
{
	//For now we will combine the data from all installed mining lasers.  We get the longest and higher targeting distance and cycle time and then add all of the mining amounts together and then return those values

	hCTime = 0;
	lTDist = 0;
	tMAmount = 0.0f;

	for (i = 0; i < lBanks.size(); i++)
	{
		if (lBanks.at(i).getHPWType() == "mining laser")
		{
			if (lBanks.at(i).hpWeapon.getCLength() > hCTime)
			{
				hCTime = lBanks.at(i).hpWeapon.getCLength();
			}
			
			if (lBanks.at(i).hpWeapon.getWAHigh() > lTDist)
			{
				lTDist = lBanks.at(i).hpWeapon.getWAHigh();
			}

			tMAmount += lBanks.at(i).hpWeapon.getCMAmount();
		}
	}

	if (hCTime == 0)
	{
		return false;
	}

	else
	{
		*cTime = hCTime;
		*mlTDist = lTDist;
		*cMAmount = tMAmount;

		return true;
	}
}

bool Ship::checkSpace(float nSpace)
{
	if (sMCSpace < getCSpace() + nSpace)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void Ship::setSID(int i)
{
	sSID = i;
}

void Ship::setSTID(int i)
{
	sSTID = i;
}

void Ship::setSLocal(string s)
{
	sLocal = s;
}

int	Ship::getSID()
{
	return sSID;
}

int	Ship::getSTID()
{
	return sSTID;
}

string Ship::getSLocal()
{
	return sLocal;
}

int Ship::getID()
{
	return sID;
}

void Ship::setID(int i)
{
	sID = i;
}

void Ship::changeShip(string name, string sclass, float shield, float mshield, float armor, float marmor, float hull, float mhull, int lb, int mt, int bh, int rm, int hwb, int twhp, int minit, int tlevel, float sg2, float mcspace, int sSID, int sSTID, string sLocal)
{
	sName = name;	
	sClass = sclass;	
	sTLevel = tlevel;	
	sShield = shield;
	sMShield = mshield;
	sArmor = armor;
	sMArmor = marmor;
	sHull = hull;
	sMHull = mhull;
	sMInit = minit;
	sWHP = twhp;
	sLB = lb;
	sMT = mt;
	sBH = bh;
	sRM = rm;
	sHWB = hwb;
	sMCSpace = mcspace;
	sSG2 = sg2;

	initHPoints();
}

bool Ship::storeItem(Station& stat, Player& mPlayer)
{
	pChoice = mp_s.sMSI4B(this);

	if (pChoice != -1)
	{
		bDone = false;

		while (!bDone)
		{
			nOItems = mp_s.mSSIAmount(sCargo.at(pChoice).getIAmount());

			if (stat.checkSpace(sCargo.at(pChoice).getISpace()*nOItems))
			{
				//Check to see if the item exists in the cargohold
				for (i = 0; i <= stat.sInventory.size(); i++)
				{
					if (i == stat.sInventory.size()) //Item does not exist
					{
						//Add the item to the station inventory
						stat.sSItem(sCargo.at(pChoice).getIID(), nOItems, sCargo.at(pChoice).getIType(), sCargo.at(pChoice).getISpace());

						//Remove items from ship cargohold
						updateCIAmount(pChoice, nOItems, "sub", false, "");

						bDone = true;
						return true;
					}

					else if ((stat.sInventory.at(i).getIID() == sCargo.at(pChoice).getIID()) && (stat.sInventory.at(i).getIType() == sCargo.at(pChoice).getIType())) //If the item exists in the inventory
					{
						//Add the additional items to station inventory
						stat.sInventory.at(i).updateIAmount(nOItems, "add");

						//Remove items from cargohold
						updateCIAmount(pChoice, nOItems, "sub", false, "");

						bDone = true;
						return true;
					}
				}
			}

			else
			{
				if (!stat.sBISpace(mPlayer, sCargo.at(pChoice).getIAmount()*nOItems))
				{
					cout << "Since you do not have enough room sto store these items, canceling the storage operation..." << endl;

					bDone = true;
					return false;
				}
			}
		}
	}

	else
	{
		cout << "Either no items found or operation was canceled." << endl;
		return false;
	}
}