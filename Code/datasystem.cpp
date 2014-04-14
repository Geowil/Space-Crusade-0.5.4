#include <iostream>
#include <conio.h>

#include "datasystem.h"
#include "msgproc.h"
#include "database.h"

using namespace std;

Database db_ds;

//Global matrix defines


static string sNames[10] = {"Sol Alpha","Sol Beta","Argon 1203","A'Colt 1","A'Colt 3","Arialt Prime","Rye 1","Rye 2","Rye 3","Saada Delta"}; //station names


//TODO: Merger all of the get functions into functions that fulfill the same function.  Separate out data types by passing a type parameter and then checking off of that type for what is needed

//Ship Data Search	
string dataSystem::getSName()
{	
	return ships.at(0).sName;
}

string dataSystem::getSDesc()
{
	return ships.at(0).sDesc;
}

string dataSystem::getSClass()
{
	return ships.at(0).sClass;
}

float dataSystem::getSShield()
{
	return ships.at(0).sShield;
}

float dataSystem::getSArmor()
{
	return ships.at(0).sArmor;
}

float dataSystem::getSHull()
{
	return ships.at(0).sHull;
}

int dataSystem::getSWHP()
{
	return ships.at(0).sTHPoints;
}

int dataSystem::getSLB()
{
	return ships.at(0).sLBanks;
}

int dataSystem::getSMT()
{
	return ships.at(0).sMTurrets;
}

int dataSystem::getSRM()
{
	return ships.at(0).sRMounts;
}

int dataSystem::getSHWB()
{
	return ships.at(0).sHWBays;
}

int dataSystem::getSBH()
{
	return ships.at(0).sBHolds;
}

int dataSystem::getSMInit()
{
	return ships.at(0).sMInit;
}

float dataSystem::getSSG2()
{
	return ships.at(0).sSG2;
}

float dataSystem::getSCargo()
{
	return ships.at(0).sCargo;
}

int dataSystem::getSTLevel()
{
	return ships.at(0).sTLevel;
}

int dataSystem::getSXC()
{
	return ships.at(0).sXCost;
}

int dataSystem::getSRC()
{
	return ships.at(0).sRCost;
}

int dataSystem::getSDC()
{
	return ships.at(0).sDCost;
}

int dataSystem::getSDiC()
{
	return ships.at(0).sDiCost;
}

int dataSystem::getSUC()
{
	return ships.at(0).sUCost;
}

int dataSystem::getSPC()
{
	return ships.at(0).sPCost;
}

//Weapon Data Search
int dataSystem::getWID()
{
	return weapons.at(0).wID;
}

string dataSystem::getWName()
{
	return weapons.at(0).wName;
}

string dataSystem::getWDesc()
{
	return weapons.at(0).wDesc;
}

float dataSystem::getWDRLow()
{
	return weapons.at(0).wMDamage;
}

float dataSystem::getWDRHigh()
{
	return weapons.at(0).wMxDamage;
}


float dataSystem::getWWeight()
{
	return weapons.at(0).wMass;
}

int dataSystem::getWAMin()
{
	return weapons.at(0).wMTDistance;
}

int dataSystem::getWAOMin()
{
	return weapons.at(0).wMOTDistance;
}

int dataSystem::getWAOMax()
{
	return weapons.at(0).wMxOTDistance;
}

int dataSystem::getWAMax()
{
	return weapons.at(0).wMxTDistance;
}

int dataSystem::getWTLevel()
{
	return weapons.at(0).wTLevel;
}

string dataSystem::getWClass()
{
	return weapons.at(0).wClass;
}

float dataSystem::getWSG2()
{
	return weapons.at(0).wSG2;
}

int dataSystem::getWMCLength()
{
	return weapons.at(0).wMCLength;
}

float dataSystem::getWMCAmount()
{
	return weapons.at(0).wMCAmount;
}

int dataSystem::getWXC()
{
	return weapons.at(0).wXCost;
}

int dataSystem::getWRC()
{
	return weapons.at(0).wRCost;
}

int dataSystem::getWDiC()
{
	return weapons.at(0).wDiCost;
}

int dataSystem::getWDC()
{
	return weapons.at(0).wDCost;
}

int dataSystem::getWLC()
{
	return weapons.at(0).wLCost;
}

int dataSystem::getWUC()
{
	return weapons.at(0).wUCost;
}

int dataSystem:: getWPC()
{
	return weapons.at(0).wPCost;
}

int dataSystem::getWNWC()
{
	return weapons.at(0).wNWCost;
}

string dataSystem::getWType()
{
	wTID = weapons.at(0).wType;

	switch(wTID)
	{
	case 1:
		return "laser";
		break;
		
	case 2:
		return "missile";
		break;

	case 3:
		return "bomb";
		break;

	case 4:
		return "rail";
		break;

	case 5:
		return "heavy";
		break;
	}
}

string dataSystem::getWDType()
{
	return weapons.at(0).wSpecial;
}

//Mission Data Search

int dataSystem::getMisID()
{
	return missions.at(0).mID;
}

string dataSystem::getMName()
{
	return missions.at(0).mName;
}

string dataSystem::getMDesc()
{
	return missions.at(0).mDesc;
}

int dataSystem::getMCBEReq()
{
	return missions.at(0).mCBELevel;
}

string dataSystem::getMSCReq()
{
	return missions.at(0).mSCReq;
}

string dataSystem::getMMWReq()
{
	data = missions.at(0).mMWReq;

	if (data == "Null")
	{
		return "No Information";
	}

	else
	{
		return data;
	}
}

int dataSystem::getMTLimit()
{
	return missions.at(0).mTLimit;
}

string dataSystem::getMDiff()
{
	return missions.at(0).mDifficulty;
}

string dataSystem::getMSector()
{
	data = missions.at(0).mSector;

	if (data == "Null")
	{
		return "No Information";
	}

	else
	{
		return data;
	}
}

string dataSystem::getMSystem()
{
	data = missions.at(0).mSystem;

	if (data == "Null")
	{
		return "No Information";
	}

	else
	{
		return data;
	}
}

string dataSystem::getMTName()
{
	data = missions.at(0).mTName;

	if (data == "Null")
	{
		return "No Information";
	}

	else
	{
		return data;
	}
}

string dataSystem::getMTSClass()
{
	data = missions.at(0).mTSClass;

	if (data == "Null")
	{
		return "No Information";
	}

	else
	{
		return data;
	}
}

int dataSystem::getMBounty()
{
	return missions.at(0).mBounty;
}

int dataSystem::getMXR()
{
	return missions.at(0).mXarn;
}

int dataSystem::getMRR()
{
	return missions.at(0).mRubies;
}

int dataSystem::getMDiR()
{
	return missions.at(0).mDiamonds;
}

int dataSystem::getMDR()
{
	return missions.at(0).mDraconic;
}

int dataSystem::getMLR()
{
	return missions.at(0).mLithium;
}

int dataSystem::getMPlR()
{
	return missions.at(0).mPlatinum;
}

int dataSystem::getMUR()
{
	return missions.at(0).mUranium;
}

int dataSystem::getMPR()
{
	return missions.at(0).mPlutonium;
}

int dataSystem::getMNWR()
{
	return missions.at(0).mNWaste;
}

int dataSystem::getMEXPR()
{
	return missions.at(0).mCEXP;
}

string dataSystem::getMIR()
{
	data = missions.at(0).mItem;

	if (data != "0")
	{
		data3 = data.substr(0,1); //Get item type
		data = data.substr(1); //Get item id
		data2 = atoi(data.c_str()); //Cast string id to an int

		if (data3 == "S")
		{
			rData("Ship_Data","select from",data2);
			data = ships.at(0).sName;
		}

		else if (data3 == "W")
		{
			rData("Weapon_Data","select from",data2);
			data = weapons.at(0).wName;
		}		

		return data;
	}

	else
	{
		return "No Reward";
	}
}

string dataSystem::getMType()
{
	return missions.at(0).mType;
}


//Message Data Search
string dataSystem::getMsg()
{
	return messages.at(0).mes;
}


//Other Functions
string dataSystem::getPName(int pCode)
{
	rData("Planet_Names","select from",pCode);

	return pNames.at(0).pName;
}

void dataSystem::getPNames(vector<string>& names)
{
	rData("Planet_Names","select from",0);

	for (i = 0; i < pNames.size(); i++)
	{
		names.push_back(string());

		names.at(i) = pNames.at(i).pName;
	}
}



/*bool dataSystem::doesCMatch(int cCode, int iCode, string iType)
{
	if (iType == "Ship")
	{

	}

	else if (iType == "Weapon")
	{
		switch (cCode)
		{
		case 1:
			if (weaponDB[iCode-1][11] == "Frigate")
			{
				return true;
			}
			break;

		case 2:
			if (weaponDB[iCode-1][11] == "Destroyer")
			{
				return true;
			}
			break;

		case 3:
			if (weaponDB[iCode-1][11] == "Cruiser")
			{
				return true;
			}
			break;

		case 4:
			if (weaponDB[iCode-1][11] == "Battle Cruiser")
			{
				return true;
			}
			break;
		
		case 5:
			if (weaponDB[iCode-1][11] == "Battleship")
			{
				return true;
			}
			break;

		case 6:
			if (weaponDB[iCode-1][11] == "Commandship")
			{
				return true;
			}
			break;

		case 7:
			if (weaponDB[iCode-1][11] == "Mothership")
			{
				return true;
			}
			break;

		case 8:
			if (weaponDB[iCode-1][11] == "Titan")
			{
				return true;
			}
			break;
		}
	}

	return false;
}*/

string dataSystem::getERace()
{
	return races.at(0).rName;
}

string dataSystem::getERank()
{
	return rank.at(i).rkName;
}

//Get Equipment Data

int dataSystem::getEID()
{
	return equipment.at(0).eID;
}

string dataSystem::getEName()
{
	return equipment.at(0).eName;
}

string dataSystem::getEDesc()
{
	return equipment.at(0).eDesc;
}

string dataSystem::getEType()
{
	return equipment.at(0).eType;
}

string dataSystem::getEClass()
{
	return equipment.at(0).eClass;
}

int dataSystem::getETLevel()
{
	return equipment.at(0).eTLevel;
}

float dataSystem::getESP()
{
	return equipment.at(0).eSPoints;
}

float dataSystem::getESMP()
{
	return equipment.at(0).eSMPoints;
}

float dataSystem::getESPR()
{
	return equipment.at(0).eSPRegen;
}

string dataSystem::getEDType()
{
	return equipment.at(0).eDType;
}

float dataSystem::getEMDmg()
{
	return equipment.at(0).eMDmg;
}

float dataSystem::getEMxDmg()
{
	return equipment.at(0).eMxDmg;
}

int dataSystem::getERng()
{
	return equipment.at(0).eRng;
}

float dataSystem::getESG2()
{
	return equipment.at(0).eSG2;
}

int dataSystem::getEXC()
{
	return equipment.at(0).eXCost;
}

int dataSystem::getERC()
{
	return equipment.at(0).eRCost;
}

int dataSystem::getEDiC()
{
	return equipment.at(0).eDiCost;
}

int dataSystem::getEDC()
{
	return equipment.at(0).eDCost;
}

int dataSystem::getELC()
{
	return equipment.at(0).eLCost;
}

int dataSystem::getEUC()
{
	return equipment.at(0).eUCost;
}

int dataSystem::getEPC()
{
	return equipment.at(0).ePluCost;
}

int dataSystem::getENWC()
{
	return equipment.at(0).eNWCost;
}

string dataSystem::getEEffect()
{
	return equipment.at(0).eEffect;
}

int dataSystem::getECXP()
{
	return equipment.at(0).eCXP;
}

//Name Functions
string dataSystem::getRName()
{
	return names.at(0).name_;
}

//For Database Interaction
void dataSystem::rData(string table, string operation, int ID)
{
	db_ds.openDB(&bErrors);
	db_ds.tableTAccess(table);

	db_ds.createStatement(ID,operation);
	
	if (table == "Ship_Data")
	{
		if (ships.size() > 0)
		{
			ships.clear();
		}

		db_ds.getSResults(&bErrors);
		db_ds.returnSResult(ships);
	}

	else if (table == "Weapon_Data")
	{
		if (weapons.size() > 0)
		{
			weapons.clear();
		}

		db_ds.getWResults(&bErrors);
		db_ds.returnWResult(weapons);
	}

	else if (table == "Mission_Data")
	{
		if (missions.size() > 0)
		{
			missions.clear();
		}

		missions.push_back(mission());

		db_ds.getMResults(&bErrors);
		db_ds.returnMResult(missions);
	}

	else if (table == "Msg_Data")
	{
		if (messages.size() > 0)
		{
			messages.clear();
		}

		db_ds.getMesResults(&bErrors);
		db_ds.returnMesResult(messages);
	}

	else if (table == "Rank_Data")
	{
		if (rank.size() > 0)
		{
			rank.clear();
		}

		db_ds.getRResults(&bErrors);
		db_ds.returnRResult(rank);
	}

	else if (table == "Race_Data")
	{
		if (races.size() > 0)
		{
			races.clear();
		}

		db_ds.getRcResults(&bErrors);
		db_ds.returnRcResult(races);
	}

	else if (table == "Dispo_Data")
	{
		if (dispositions.size() > 0)
		{
			dispositions.clear();
		}

		db_ds.getDResults(&bErrors);
		db_ds.returnDResult(dispositions);
	}

	else if (table == "Planet_Names")
	{
		if (pNames.size() > 0)
		{
			pNames.clear();
		}

		db_ds.getPNResults(&bErrors);
		db_ds.returnPNResult(pNames);
	}

	else if (table == "Equipment_Data")
	{
		if (equipment.size() > 0)
		{
			equipment.clear();
		}

		db_ds.getEResults(&bErrors);
		db_ds.returnEResults(equipment);
	}

	else if (table == "Name_DB")
	{
		if (names.size() > 0)
		{
			names.clear();
		}

		db_ds.getRNResults(&bErrors);
		db_ds.returnRNResults(names);
	}

	else if (table == "Resource")
	{
		db_ds.tableTAccess("Resource_Data");
		db_ds.createStatement(ID,operation);

		if (resources.size() > 0)
		{
			resources.clear();
		}

		db_ds.getRDResults(&bErrors);
		db_ds.returnRDResults(resources);
	}

	else if (table == "Ore")
	{
		db_ds.tableTAccess("Resource_Data");
		db_ds.createStatement(ID,operation);

		if (ores.size() > 0)
		{
			ores.clear();
		}

		db_ds.getOResults(&bErrors);
		db_ds.returnOResults(ores);
	}

	db_ds.closeDB(&bErrors);
}

//Resource Data
string dataSystem::getResName()
{
	return resources.at(0).rName;
}

string dataSystem::getResDesc()
{
	return resources.at(0).rDesc;
}

string dataSystem::getResType()
{
	return resources.at(0).rType;
}

float dataSystem::getResSG2()
{
	return resources.at(0).rSG2;
}

int dataSystem::getResXCost()
{
	return resources.at(0).rXCost;
}

//Ore Data
string dataSystem::getOName()
{
	return ores.at(0).oName;
}

string dataSystem::getODesc()
{
	return ores.at(0).oDesc;
}

string dataSystem::getOType()
{
	return ores.at(0).oType;
}

float dataSystem::getOSG2()
{
	return ores.at(0).oSG2;
}

int dataSystem::getOStage()
{
	return ores.at(0).oStage;
}

float dataSystem::getOBSize()
{
	return ores.at(0).oBSize;
}

string dataSystem::getOResource()
{
	return ores.at(0).oResource;
}

string dataSystem::getOOre()
{
	return ores.at(0).oOre;
}

float dataSystem::getORUnits()
{
	return ores.at(0).oRUnits;
}

int dataSystem::getORProduced()
{
	return ores.at(0).oRProduced;
}

int dataSystem::getORCost()
{
	return ores.at(0).oRCost;
}

float dataSystem::getORPLoss()
{
	return ores.at(0).oRPLoss;
}

int dataSystem::getOXCost()
{
	return ores.at(0).oXCost;
}



//Load & Save Data Functions

bool dataSystem::lData(Player& mPlayer, Game* mGame)
{
	//Reset bECount so that only errors generated from lData on this run through the function are counted
	bECount = 0;
	
	//Open Save File
	db_ds.openSave(&bErrors);

	//Get Flags

	//Create Statement
	db_ds.tableTAccess("Save_Flags");
	db_ds.createStatement(0,"select from");

	//Load Save Flags
	db_ds.getSFlagResults(&bErrors);
	db_ds.returnSFlagResults(saveFlags);

	//Create Statement
	db_ds.tableTAccess("Player_Data");
	db_ds.createStatement(0,"select from");

	//Load Player Data
	db_ds.getPDataResults(&bErrors);
	
	if (!bErrors)
	{		
		cout << "Loading player data";
		db_ds.returnPDataResults(pData);

		mPlayer.setName(pData.at(0).pName);
		mPlayer.setRace("Human"); //Temporary until I can add the race calls/queries to the code
		mPlayer.setRank(pData.at(0).pRank);
		mPlayer.updateCXPLvl(pData.at(0).pCXPLevel, "set");
		mPlayer.updateDPlanets(pData.at(0).pPDestroyed, "set");
		mPlayer.updateFKills(pData.at(0).pFKills, "set");
		mPlayer.updateDKills(pData.at(0).pDKills, "set");
		mPlayer.updateCKills(pData.at(0).pCKills, "set");
		mPlayer.updateBCKills(pData.at(0).pBCKills, "set");
		mPlayer.updateBKills(pData.at(0).pBKills, "set");
		mPlayer.updateMKills(pData.at(0).pMKills, "set");
		mPlayer.updateTKills(pData.at(0).pTKills, "set");
		mPlayer.updateCEXP(pData.at(0).pCEXP, "set");
		mPlayer.setCXPTNL(pData.at(0).pCXPTNL);
		mPlayer.updateXarn(pData.at(0).pXarn, "set");
		mPlayer.updateRubies(pData.at(0).pRubies, "set");
		mPlayer.updateDia(pData.at(0).pDiamonds, "set");
		mPlayer.updateDrac(pData.at(0).pDrac, "set");
		mPlayer.updateLith(pData.at(0).pLith, "set");
		mPlayer.updatePlat(pData.at(0).pPla, "set");
		mPlayer.updateUra(pData.at(0).pUra, "set");
		mPlayer.updatePlut(pData.at(0).pPlu, "set");
		mPlayer.updateNWaste(pData.at(0).pNWaste, "set");
		mPlayer.setAffil(pData.at(0).pAffiliation);

		cout << ".";
		cout << "Done" << endl << endl;


		//Create Statement
		db_ds.tableTAccess("PShip_Data");
		db_ds.createStatement(0,"select from");

		//Player Ship
		db_ds.getPShipResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading player ship data";
			db_ds.returnPShipResults(plShip);

			mPlayer.Ship.setSName(plShip.at(0).sName);
			mPlayer.Ship.setSClass(plShip.at(0).sClass);
			mPlayer.Ship.setSTLevel(plShip.at(0).sTLevel);
			mPlayer.Ship.updateSShield(plShip.at(0).sSP, "set");
			mPlayer.Ship.updateSArmor(plShip.at(0).sAP, "set");
			mPlayer.Ship.updateSHull(plShip.at(0).sHP, "set");
			mPlayer.Ship.updateSMShield(plShip.at(0).sMSP, "set");
			mPlayer.Ship.updateSMArmor(plShip.at(0).sMAP, "set");
			mPlayer.Ship.updateSMHull(plShip.at(0).sMHP, "set");
			mPlayer.Ship.setMInit(plShip.at(0).sMInit);
			mPlayer.Ship.setSSG2(plShip.at(0).sSG2);
			mPlayer.Ship.updateMCSpace(plShip.at(0).sMCSpace, "set");
			mPlayer.Ship.setLHP(plShip.at(0).sLB);
			mPlayer.Ship.setMTP(plShip.at(0).sMT);
			mPlayer.Ship.setBH(plShip.at(0).sBH);
			mPlayer.Ship.setRM(plShip.at(0).sRM);
			mPlayer.Ship.setHWB(plShip.at(0).sHWB);
			mPlayer.Ship.setSWHP(plShip.at(0).sWHP);
			mPlayer.Ship.setULHP(plShip.at(0).sULB);
			mPlayer.Ship.setUMTP(plShip.at(0).sUMT);
			mPlayer.Ship.setUBH(plShip.at(0).sUBH);
			mPlayer.Ship.setURM(plShip.at(0).sURM);
			mPlayer.Ship.setUHWB(plShip.at(0).sUHWB);
			mPlayer.Ship.setMWSpreads(plShip.at(0).sMWSpreads);
			mPlayer.Ship.setID(plShip.at(0).sID);
			mPlayer.Ship.setSID(plShip.at(0).sSID);
			mPlayer.Ship.setSTID(plShip.at(0).sSTID);
			mPlayer.Ship.setSLocal(plShip.at(0).sLocal);

			cout << ".";
			cout << "Done" << endl << endl;
		}

		else 
		{
			problems("loading player ship data");
		}
	}
	
	else
	{
		problems("loading player data");
	}

	if (getFlag("PSWSpreads") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("PShip_WSpreads");
		db_ds.createStatement(0,"select from");

		//Weapon Spreads
		db_ds.getPSSResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading player ship weapon spread data";			
			db_ds.returnPSSResults(plSSpreads);

			//Close Save DB due to conflict in iWeapon/setupWeapon
			db_ds.closeDB(&bErrors);

			for (i = 0; i < plSSpreads.size(); i++)
			{
				mPlayer.Ship.addSVElement(plSSpreads.at(i).sPID, plSSpreads.at(i).sWType, plSSpreads.at(i).sID);
				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading player ship spread data");
		}
	}
		
	

	if (getFlag("PSWHPVect") == 1)
	{
		
		//Create Statement
		db_ds.tableTAccess("PShip_WHPVect");
		db_ds.createStatement(0,"select from");

		//Weapon Hardpoints
		db_ds.getPSHPVResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading player ship weapon hardpoint data";
			db_ds.returnPSHPVResults(plSHPVectors);

			//Close Save DB due to conflict in iWeapon/setupWeapon
			db_ds.closeDB(&bErrors);

			for (i = 0; i < plSHPVectors.size(); i++)
			{
				mPlayer.Ship.addWHPVElement(plSHPVectors.at(i).sID, plSHPVectors.at(i).wID, plSHPVectors.at(i).sWType);
				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading player ship weapon hardpoint data");
		}
	}

	if (getFlag("PSInv") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("PShip_Inv");
		db_ds.createStatement(0,"select from");

		//Ship Cargo
		db_ds.getPSCResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading ship cargo data";
			db_ds.returnPSCResults(plSCargo);

			for (i2 = 0; i2 < plSCargo.size(); i2++)
			{
				if (plSCargo.at(i2).iType == "Ship")
				{

					tShip.setSName(plShip.at(plSCargo.at(i2).iID).sName);
					tShip.setSClass(plShip.at(plSCargo.at(i2).iID).sClass);
					tShip.setSTLevel(plShip.at(plSCargo.at(i2).iID).sTLevel);
					tShip.updateSShield(plShip.at(plSCargo.at(i2).iID).sSP, "set");
					tShip.updateSArmor(plShip.at(plSCargo.at(i2).iID).sAP, "set");
					tShip.updateSHull(plShip.at(plSCargo.at(i2).iID).sHP, "set");
					tShip.updateSMShield(plShip.at(plSCargo.at(i2).iID).sMSP, "set");
					tShip.updateSMArmor(plShip.at(plSCargo.at(i2).iID).sMAP, "set");
					tShip.updateSMHull(plShip.at(plSCargo.at(i2).iID).sMHP, "set");
					tShip.setMInit(plShip.at(plSCargo.at(i2).iID).sMInit);
					tShip.setSSG2(plShip.at(plSCargo.at(i2).iID).sSG2);
					tShip.updateMCSpace(plShip.at(plSCargo.at(i2).iID).sMCSpace, "set");
					tShip.setLHP(plShip.at(plSCargo.at(i2).iID).sLB);
					tShip.setMTP(plShip.at(plSCargo.at(i2).iID).sMT);
					tShip.setBH(plShip.at(plSCargo.at(i2).iID).sBH);
					tShip.setRM(plShip.at(plSCargo.at(i2).iID).sRM);
					tShip.setHWB(plShip.at(plSCargo.at(i2).iID).sHWB);
					tShip.setSWHP(plShip.at(plSCargo.at(i2).iID).sWHP);
					tShip.setULHP(plShip.at(plSCargo.at(i2).iID).sULB);
					tShip.setUMTP(plShip.at(plSCargo.at(i2).iID).sUMT);
					tShip.setUBH(plShip.at(plSCargo.at(i2).iID).sUBH);
					tShip.setURM(plShip.at(plSCargo.at(i2).iID).sURM);
					tShip.setUHWB(plShip.at(plSCargo.at(i2).iID).sUHWB);
					tShip.setSID(plShip.at(plSCargo.at(i2).iID).sSID);
					tShip.setSTID(plShip.at(plSCargo.at(i2).iID).sSTID);
					tShip.setSLocal(plShip.at(plSCargo.at(i2).iID).sLocal);

					//mPlayer.Ship.loadSCargo(1,"Ship", tempShip);

					mPlayer.Ship.loadSCargo(1, "Ship", tShip);
				}

				else
				{
					mPlayer.Ship.loadCargo(plSCargo.at(i2).iID, plSCargo.at(i2).iAmount, plSCargo.at(i2).iType, plSCargo.at(i2).iSG2, false, "");
					cout << ".";
				}
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading player ship cargo data");
		}
	}

	if (getFlag("PWData") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Player_W_Data");
		db_ds.createStatement(0,"select from");

		//Load Player Wingmen Data
		db_ds.getPWMDResults(&bErrors);

		if (!bErrors) //Check for errors at each level so that we are sure that all data is loaded correctly into the vectors; inefficient but required
		{		
			cout << "Loading player wingmen data";
			db_ds.returnPWMDResults(pWMData);

			for (i = 0; i < pWMData.size(); i++)
			{
				mPlayer.addWingman();

				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).setName(pWMData.at(i).pWName);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).setRank(pWMData.at(i).pWRank);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).updateCXPLvl(pWMData.at(i).pWCXPLevel,"set");

				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading wingmen data");
		}
	}

	if (getFlag("PWSData") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("PWShip_Data");
		db_ds.createStatement(0,"select from");

		//Player Wingman Ship
		db_ds.getPWSDResults(&bErrors);

		if (!bErrors)
		{			
			cout << "Loading player wingmen ship data";
			db_ds.returnPWSDResults(pWMSData);

			for (i = 0; i < pWMData.size(); i++)
			{
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setSName(pWMSData.at(0).sName);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setSClass(pWMSData.at(0).sClass);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setSTLevel(pWMSData.at(0).sTLevel);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSShield(pWMSData.at(0).sSP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSArmor(pWMSData.at(0).sAP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSHull(pWMSData.at(0).sHP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSMShield(pWMSData.at(0).sMSP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSMArmor(pWMSData.at(0).sMAP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.updateSMHull(pWMSData.at(0).sMHP, "set");
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setMInit(pWMSData.at(0).sMInit);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setLHP(pWMSData.at(0).sLB);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setMTP(pWMSData.at(0).sMT);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setBH(pWMSData.at(0).sBH);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setRM(pWMSData.at(0).sRM);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setHWB(pWMSData.at(0).sHWB);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setSWHP(pWMSData.at(0).sWHP);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setULHP(pWMSData.at(0).sULB);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setUMTP(pWMSData.at(0).sUMT);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setUBH(pWMSData.at(0).sUBH);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setURM(pWMSData.at(0).sURM);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setUHWB(pWMSData.at(0).sUHWB);
				mPlayer.eWingmen.at(mPlayer.eWingmen.size()-1).Ship.setMWSpreads(pWMSData.at(0).sMWSpreads);

				cout << ".";
			}

			cout << "Done" << endl << endl;
		}

		else 
		{
			problems("loading wingmen ship data");
		}
	}

	if (getFlag("PWSWSpreads") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("PWShip_WSpreads");
		db_ds.createStatement(0,"select from");

		//Weapon Spreads
		db_ds.getPWSSResults(&bErrors);

		if (!bErrors)
		{			
			cout << "Loading player wingmen ship weapon spread data";
			db_ds.returnPWSSResults(pWMSSpreads);

			//Close Save DB due to conflict in iWeapon/setupWeapon
			db_ds.closeDB(&bErrors);
			
			for (i = 0; i < plSSpreads.size(); i++)
			{
				mPlayer.eWingmen.at(pWMSSpreads.at(i).wID-1).Ship.addSVElement(pWMSSpreads.at(i).sPID, pWMSSpreads.at(i).sWType,pWMSSpreads.at(i).sID);
				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading wingmen weapon spreads");
		}
	}

	if (getFlag("PWSWHPVect") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("PWShip_WHPVect");
		db_ds.createStatement(0,"select from");

		//Weapon Hardpoints
		db_ds.getPWSHPVResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading player wingmen ship weapon hardpoint data";
			db_ds.returnPWSHPVResults(pWMSHPVectors);

			//Close Save DB due to conflict in iWeapon/setupWeapon
			db_ds.closeDB(&bErrors);

			for (i = 0; i < plSHPVectors.size(); i++)
			{
				mPlayer.eWingmen.at(pWMSHPVectors.at(i).wID-1).Ship.addWHPVElement(pWMSHPVectors.at(i).sID, pWMSHPVectors.at(i).wep_ID, pWMSHPVectors.at(i).sWType);

				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading wingmen weapon hardpoints");
		}
	}

	if (getFlag("PMData") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Mission_Data");
		db_ds.createStatement(0,"select from");

		//Player Mission Data
		db_ds.getPMDataResults(&bErrors);

		if (!bErrors)
		{		
			cout << "Loading player mission data";
			db_ds.returnPMDataResults(pMData);

			for (i = 0; i < pMData.size(); i++)
			{
				if (pMData.at(i).mState == 0 || pMData.at(i).mState == 1)
				{
					mPlayer.loadMission1(pMData.at(i));
				}

				else
				{
					mPlayer.loadMission2(pMData.at(i));
				}

				cout << ".";
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading player mission data");
		}
	}

	if (getFlag("PRData") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Relationship_Data");
		db_ds.createStatement(0,"select from");

		//Player Relation Data
		db_ds.getPRDataResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading player relationship data";
			db_ds.returnPRDataResults(pRData);

			for (i = 0; i < pRData.size(); i++)
			{
				mPlayer.loadRelation(pRData.at(i));

				cout << ".";
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading player relation data");
		}
	}

	if (getFlag("GStats") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Generated_Stations");
		db_ds.createStatement(0,"select from");

		//Station Data
		db_ds.getSDataResults(&bErrors);

		if (!bErrors)
		{		
			cout << "Loading generated station data";
			db_ds.returnSDataResults(stData);			

			for (i = 0; i < stData.size(); i++)
			{
				mGame->loadStation(stData.at(i));
				cout << ".";
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading station data");
		}
	}

	if (getFlag("GSInv") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Player_Station_Inv");
		db_ds.createStatement(0,"select from");
		
		//Inventory Data
		db_ds.getSPIResults(&bErrors);
	
		if (!bErrors)
		{
			cout << "Loading station inventory data";
			db_ds.returnSPIResults(sPInventory);

			for (i = 0; i < sPInventory.size(); i++)
			{
				if (sPInventory.at(i).iType == "Ship")
				{
					tempShip.setSName(plShip.at(sPInventory.at(i).iID).sName);
					tempShip.setSClass(plShip.at(sPInventory.at(i).iID).sClass);
					tempShip.setSTLevel(plShip.at(sPInventory.at(i).iID).sTLevel);
					tempShip.updateSShield(plShip.at(sPInventory.at(i).iID).sSP, "set");
					tempShip.updateSArmor(plShip.at(sPInventory.at(i).iID).sAP, "set");
					tempShip.updateSHull(plShip.at(sPInventory.at(i).iID).sHP, "set");
					tempShip.updateSMShield(plShip.at(sPInventory.at(i).iID).sMSP, "set");
					tempShip.updateSMArmor(plShip.at(sPInventory.at(i).iID).sMAP, "set");
					tempShip.updateSMHull(plShip.at(sPInventory.at(i).iID).sMHP, "set");
					tempShip.setMInit(plShip.at(sPInventory.at(i).iID).sMInit);
					tempShip.setSSG2(plShip.at(sPInventory.at(i).iID).sSG2);
					tempShip.updateMCSpace(plShip.at(sPInventory.at(i).iID).sMCSpace, "set");
					tempShip.setLHP(plShip.at(sPInventory.at(i).iID).sLB);
					tempShip.setMTP(plShip.at(sPInventory.at(i).iID).sMT);
					tempShip.setBH(plShip.at(sPInventory.at(i).iID).sBH);
					tempShip.setRM(plShip.at(sPInventory.at(i).iID).sRM);
					tempShip.setHWB(plShip.at(sPInventory.at(i).iID).sHWB);
					tempShip.setSWHP(plShip.at(sPInventory.at(i).iID).sWHP);
					tempShip.setULHP(plShip.at(sPInventory.at(i).iID).sULB);
					tempShip.setUMTP(plShip.at(sPInventory.at(i).iID).sUMT);
					tempShip.setUBH(plShip.at(sPInventory.at(i).iID).sUBH);
					tempShip.setURM(plShip.at(sPInventory.at(i).iID).sURM);
					tempShip.setUHWB(plShip.at(sPInventory.at(i).iID).sUHWB);
					tempShip.setID(plShip.at(sPInventory.at(i).iID).sID);
					tempShip.setSID(plShip.at(sPInventory.at(i).iID).sSID);
					tempShip.setSTID(plShip.at(sPInventory.at(i).iID).sSTID);
					tempShip.setSLocal(plShip.at(sPInventory.at(i).iID).sLocal);

					mGame->gStations.at(tempShip.getSTID()).sInventory.push_back(sInv(tempShip, true, tempShip.getID(), 1)); //Add it directly due to ship class; could do it through a station function but that would add extra steps when we have the ship-based constructor
				}

				else
				{
					mGame->gStations.at(sPInventory.at(i2).sID-1).sSItem(sPInventory.at(i2).iID, sPInventory.at(i2).NOI, sPInventory.at(i2).iType, sPInventory.at(i2).iSG2);		
					cout << ".";
				}
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading station inventory data");
		}
	}

	if (getFlag("GPlanets") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Generated_Planets");
		db_ds.createStatement(0,"select from");

		//Planet Data
		db_ds.getPDResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading generated planet data";
			db_ds.returnPDResults(plData);

			for (i = 0; i < plData.size(); i++)
			{
				mGame->loadPlanet(plData.at(i));

				cout << ".";
			}

			cout << "Done" << endl << endl;
		}

		else
		{
			problems("loading planet data");
		}
	}

	if (getFlag("GPDef") == 1)
	{	
		//Create Statement
		db_ds.tableTAccess("Planetary_Defenses");
		db_ds.createStatement(0,"select from");

		db_ds.getPDefResults(&bErrors);
		
		if (!bErrors)
		{
			cout << "Loading planet defense data";
			//Defense Data			
			db_ds.returnPDefResults(plDData);

			//Close Save DB due to conflict in initPS/initPD
			db_ds.closeDB(&bErrors);

			for (i = 0; i < plDData.size(); i++)
			{
				mGame->gPlanets.at(plDData.at(i).pID-1).addPDefenses(true,plDData.at(i).pDID,false,0,false);
				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading planet defense data");
		}
	}

	if (getFlag("GPShd") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("Planetary_Shields");
		db_ds.createStatement(0,"select from");

		//Shield Data
		db_ds.getPSDResults(&bErrors);

		if (!bErrors)
		{
			cout << "Loading planet shield data";
			db_ds.returnPSDResults(plSData);

			//Close Save DB due to conflict in iWeapon/setupWeapon
			db_ds.closeDB(&bErrors);

			for (i = 0; i < plSData.size(); i++)
			{
				mGame->gPlanets.at(plSData.at(i).pID-1).addPDefenses(false,0,true,plSData.at(i).mID,false);

				cout << ".";
			}

			cout << "Done" << endl << endl;

			//Open Save DB
			db_ds.openSave(&bErrors);
		}

		else
		{
			problems("loading planet shield data");
		}	
	}

	if (getFlag("GPBelt") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("GP_Belts");
		db_ds.createStatement(0, "select from");

		//Belt Data
		db_ds.getPABResults(&bErrors);

		if(!bErrors)
		{
			cout << "Loading asteroid belt data";
			db_ds.returnPABResults(belts);

			for (i = 0, i2 = 0; i < belts.size(); i++, i2++)
			{
				mGame->gPlanets.at(belts.at(i).pID-1).addBelt(belts.at(i).bName, belts.at(i).bSize, 0, true);
				
				
				//Only add a . after 10 belts have been added
				if (i2 == 9)
				{
					cout << ".";
					i2 = 0;
				}
			}
		}

		else
		{
			problems("loading planet asteroid belt data");
		}

		cout << "Done" << endl << endl;
	}


	if (getFlag("GPBRoid") == 1)
	{
		//Create Statement
		db_ds.tableTAccess("GPB_Roids");
		db_ds.createStatement(0, "select from");

		//Belt Data
		db_ds.getPABRResults(&bErrors);

		if(!bErrors)
		{
			cout << "Loading asteroid data";
			db_ds.returnPABRResults(roids);

			for (i = 0, i2 = 0; i < roids.size(); i++, i2++)
			{
				mGame->gPlanets.at(roids.at(i).pID-1).belts.at(roids.at(i).bID-1).addAsteroid(roids.at(i).aName, roids.at(i).aOName, roids.at(i).aOID, roids.at(i).aDesc, roids.at(i).aSize, roids.at(i).aOAmount, roids.at(i).xPos, roids.at(i).yPos, roids.at(i).zPos);
				
				//Only add a . after 200 roids have been loaded
				if (i2 == 199)
				{				
					cout << ".";

					i2 = 0;
				}
			}
		}

		else
		{
			problems("loading planet asteroid data");
		}

		cout << "Done" << endl << endl;
	}



	db_ds.closeDB(&bErrors);

	//Reset Vectors
	pData.clear();
	plShip.clear();
	plSSpreads.clear();
	plSHPVectors.clear();
	pWMData.clear();
	pWMSData.clear();
	pWMSSpreads.clear();
	pWMSHPVectors.clear();
	stData.clear();
	sPInventory.clear();
	plData.clear();
	plDData.clear();
	plSData.clear();
	belts.clear();
	roids.clear();
	pMData.clear();
	pRData.clear();
	tempHP.clear();
	tempLWV.clear();
	tempMWV.clear();
	tempBWV.clear();
	tempRWV.clear();
	tempHWV.clear();
	tempInv.clear();
	tempDData.clear();
	tempSData.clear();
	tempMis1.clear();
	tempMis2.clear();
	tempR.clear();
	saveFlags.clear();

	if (bECount > 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool dataSystem::sData(Player& mPlayer, Game* mGame)
{
	db_ds.openSave(&bErrors);

	if (!bErrors) //Only continue if save database could be opened
	{
		db_ds.closeDB(&bErrors); //Close the connection we just opened; debug purposes for now
		
		//Get Player Data
		pData.push_back(playerData());
		pData.at(0).pName = mPlayer.getName();
		pData.at(0).pRank = mPlayer.getRank();
		pData.at(0).pCXPLevel = mPlayer.getCELvl();
		pData.at(0).pPDestroyed = mPlayer.getDPlanets();
		pData.at(0).pFKills = mPlayer.getFKills();
		pData.at(0).pDKills = mPlayer.getDKills();
		pData.at(0).pCKills = mPlayer.getCKills();
		pData.at(0).pBCKills = mPlayer.getBCKills();
		pData.at(0).pBKills = mPlayer.getBKills();
		pData.at(0).pMKills = mPlayer.getMKills();
		pData.at(0).pTKills = mPlayer.getTKills();
		pData.at(0).pCEXP = mPlayer.getCEXP();
		pData.at(0).pCXPTNL = mPlayer.getCXPTNL();
		pData.at(0).pXarn = mPlayer.getXarn();
		pData.at(0).pRubies = mPlayer.getRubies();
		pData.at(0).pDiamonds = mPlayer.getDia();
		pData.at(0).pDrac = mPlayer.getDrac();
		pData.at(0).pLith = mPlayer.getLith();
		pData.at(0).pPla = mPlayer.getPlat();
		pData.at(0).pUra = mPlayer.getUra();
		pData.at(0).pPlu = mPlayer.getPlut();
		pData.at(0).pNWaste = mPlayer.getNWaste();
		pData.at(0).pAffiliation = mPlayer.getAffil();


		//Get Player Ship Data
		plShip.push_back(pShip());
		plShip.at(0).sName = mPlayer.Ship.getSName();
		plShip.at(0).sClass = mPlayer.Ship.getSClass();
		plShip.at(0).sTLevel = mPlayer.Ship.getSTLevel();
		plShip.at(0).sSP = mPlayer.Ship.getSShield();
		plShip.at(0).sAP = mPlayer.Ship.getSArmor();
		plShip.at(0).sHP = mPlayer.Ship.getSHull();
		plShip.at(0).sMSP = mPlayer.Ship.getSMShield();
		plShip.at(0).sMAP = mPlayer.Ship.getSMArmor();
		plShip.at(0).sMHP = mPlayer.Ship.getSMHull();
		plShip.at(0).sMInit = mPlayer.Ship.getMInit();
		plShip.at(0).sSG2 = mPlayer.Ship.getSSG2();
		plShip.at(0).sMCSpace = mPlayer.Ship.getMCSpace();
		plShip.at(0).sLB = mPlayer.Ship.getLHP();
		plShip.at(0).sMT = mPlayer.Ship.getMTP();
		plShip.at(0).sBH = mPlayer.Ship.getBH();
		plShip.at(0).sRM = mPlayer.Ship.getRM();
		plShip.at(0).sHWB = mPlayer.Ship.getHWB();
		plShip.at(0).sWHP = mPlayer.Ship.getSWHP();
		plShip.at(0).sULB = mPlayer.Ship.getULHP();
		plShip.at(0).sUMT = mPlayer.Ship.getUMTP();
		plShip.at(0).sUBH = mPlayer.Ship.getUBH();
		plShip.at(0).sURM = mPlayer.Ship.getURM();
		plShip.at(0).sUHWB = mPlayer.Ship.getUHWB();
		plShip.at(0).sMWSpreads = mPlayer.Ship.getSWSpreads();
		plShip.at(0).sID = mPlayer.Ship.getID();
		plShip.at(0).sSID = -1; //0 means active player ship; -1 means not stored| Ship ID
		plShip.at(0).sSTID = -1; //station ID; -1 means not stored in station, 0-x are the station ID in gStations vector
		plShip.at(0).sLocal = "none"; //Store location; Ship for stored on ship, Station for stored on station, and none for player active ship

		//Not needed for stored ships as weapons are removed as is cargo
		//Get Spread Information
		for (i = 1; i <= mPlayer.Ship.getSWSpreads(); i++)
		{
			if (mPlayer.Ship.getSSize(i) > 0)
			{
				tempHP = mPlayer.Ship.getSVect(i);

				for (i2 = 0; i2 < mPlayer.Ship.getSSize(i); i2++)
				{
					plSSpreads.push_back(pSSpread());

					plSSpreads.at(plSSpreads.size()-1).sID = tempHP.at(i2).getHPSlot();
					plSSpreads.at(plSSpreads.size()-1).sWType = tempHP.at(i2).getHPWType();
					plSSpreads.at(plSSpreads.size()-1).sPID = i;
				}
			}
		}


		//Get Weapon Vector Data
		for (i = 1; i <= 5; i++)
		{
			if (mPlayer.Ship.getWHPVSize(i) > 0)
			{			
				switch(i)
				{
				case 1:
					tempLWV = mPlayer.Ship.lBanks;

					for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(i); i2++)
					{
						plSHPVectors.push_back(pSHPVect());

						plSHPVectors.at(plSHPVectors.size()-1).sID = tempLWV.at(i2).getHPSlot();
						plSHPVectors.at(plSHPVectors.size()-1).wID = tempLWV.at(i2).hpWeapon.getWID();
						plSHPVectors.at(plSHPVectors.size()-1).sWType = tempLWV.at(i2).getHPWType();
					}

					break;

				case 2:
					tempMWV = mPlayer.Ship.mTurrets;

					for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(i); i2++)
					{
						plSHPVectors.push_back(pSHPVect());

						plSHPVectors.at(plSHPVectors.size()-1).sID = tempMWV.at(i2).getHPSlot();
						plSHPVectors.at(plSHPVectors.size()-1).wID = tempMWV.at(i2).hpWeapon.getWID();
						plSHPVectors.at(plSHPVectors.size()-1).sWType = tempMWV.at(i2).getHPWType();
					}

					break;

				case 3:
					tempBWV = mPlayer.Ship.bHolds;

					for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(i); i2++)
					{
						plSHPVectors.push_back(pSHPVect());

						plSHPVectors.at(plSHPVectors.size()-1).sID = tempBWV.at(i2).getHPSlot();
						plSHPVectors.at(plSHPVectors.size()-1).wID = tempBWV.at(i2).hpWeapon.getWID();
						plSHPVectors.at(plSHPVectors.size()-1).sWType = tempBWV.at(i2).getHPWType();
					}

					break;

				case 4:
					tempRWV = mPlayer.Ship.rMounts;

					for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(i); i2++)
					{
						plSHPVectors.push_back(pSHPVect());

						plSHPVectors.at(plSHPVectors.size()-1).sID = tempRWV.at(i2).getHPSlot();
						plSHPVectors.at(plSHPVectors.size()-1).wID = tempRWV.at(i2).hpWeapon.getWID();
						plSHPVectors.at(plSHPVectors.size()-1).sWType = tempRWV.at(i2).getHPWType();
					}

					break;

				case 5:
					tempHWV = mPlayer.Ship.hWBays;

					for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(i); i2++)
					{
						plSHPVectors.push_back(pSHPVect());

						plSHPVectors.at(plSHPVectors.size()-1).sID = tempHWV.at(i2).getHPSlot();
						plSHPVectors.at(plSHPVectors.size()-1).wID = tempHWV.at(i2).hpWeapon.getWID();
						plSHPVectors.at(plSHPVectors.size()-1).sWType = tempHWV.at(i2).getHPWType();
					}

					break;
				}
			}
		}

		//Player Ship Cargo
		for (i2 = 0; i2 < mPlayer.Ship.sCargo.size(); i2++)
		{
			if (mPlayer.Ship.sCargo.at(i2).isShip())
			{
				plShip.push_back(pShip());

				plShip.at(plShip.size()-1).sName = mPlayer.Ship.sCargo.at(i2).sShip.getSName();
				plShip.at(plShip.size()-1).sClass = mPlayer.Ship.sCargo.at(i2).sShip.getSClass();
				plShip.at(plShip.size()-1).sTLevel = mPlayer.Ship.sCargo.at(i2).sShip.getSTLevel();
				plShip.at(plShip.size()-1).sSP = mPlayer.Ship.sCargo.at(i2).sShip.getSShield();
				plShip.at(plShip.size()-1).sAP = mPlayer.Ship.sCargo.at(i2).sShip.getSArmor();
				plShip.at(plShip.size()-1).sHP = mPlayer.Ship.sCargo.at(i2).sShip.getSHull();
				plShip.at(plShip.size()-1).sMSP = mPlayer.Ship.sCargo.at(i2).sShip.getSMShield();
				plShip.at(plShip.size()-1).sMAP = mPlayer.Ship.sCargo.at(i2).sShip.getSMArmor();
				plShip.at(plShip.size()-1).sMHP = mPlayer.Ship.sCargo.at(i2).sShip.getSMHull();
				plShip.at(plShip.size()-1).sMInit = mPlayer.Ship.sCargo.at(i2).sShip.getMInit();
				plShip.at(plShip.size()-1).sSG2 = mPlayer.Ship.sCargo.at(i2).sShip.getSSG2();
				plShip.at(plShip.size()-1).sMCSpace = mPlayer.Ship.sCargo.at(i2).sShip.getMCSpace();
				plShip.at(plShip.size()-1).sLB = mPlayer.Ship.sCargo.at(i2).sShip.getLHP();
				plShip.at(plShip.size()-1).sMT = mPlayer.Ship.sCargo.at(i2).sShip.getMTP();
				plShip.at(plShip.size()-1).sBH = mPlayer.Ship.sCargo.at(i2).sShip.getBH();
				plShip.at(plShip.size()-1).sRM = mPlayer.Ship.sCargo.at(i2).sShip.getRM();
				plShip.at(plShip.size()-1).sHWB = mPlayer.Ship.sCargo.at(i2).sShip.getHWB();
				plShip.at(plShip.size()-1).sWHP = mPlayer.Ship.sCargo.at(i2).sShip.getSWHP();
				plShip.at(plShip.size()-1).sULB = mPlayer.Ship.sCargo.at(i2).sShip.getULHP();
				plShip.at(plShip.size()-1).sUMT = mPlayer.Ship.sCargo.at(i2).sShip.getUMTP();
				plShip.at(plShip.size()-1).sUBH = mPlayer.Ship.sCargo.at(i2).sShip.getUBH();
				plShip.at(plShip.size()-1).sURM = mPlayer.Ship.sCargo.at(i2).sShip.getURM();
				plShip.at(plShip.size()-1).sUHWB = mPlayer.Ship.sCargo.at(i2).sShip.getUHWB();
				plShip.at(plShip.size()-1).sID = mPlayer.Ship.sCargo.at(i2).getIID();
				plShip.at(plShip.size()-1).sSID = mPlayer.Ship.sCargo.at(i2).sShip.getSID(); //1 means active player ship; -1 means not stored| Ship ID
				plShip.at(plShip.size()-1).sSTID = mPlayer.Ship.sCargo.at(i2).sShip.getSTID(); //station ID; -1 means not stored in station, 0-x are the station ID in gStations vector
				plShip.at(plShip.size()-1).sLocal = mPlayer.Ship.sCargo.at(i2).sShip.getSLocal(); //Store location; Ship for stored on ship, Station for stored on station, and none for player active ship

				//Now save an entry in pSInv to tie the ship into the cargo hold vector (for slot ID)
				plSCargo.push_back(pSInv());

				plSCargo.at(i2).sID = mPlayer.Ship.getID();
				plSCargo.at(i2).iID = plShip.size()-1; //This, in this instance, will store the Table ID for the current ship object
				plSCargo.at(i2).iAmount = 1;
				plSCargo.at(i2).iType = "Ship";
				plSCargo.at(i2).iSG2 = 0.0f;
			}

			else
			{
				plSCargo.push_back(pSInv());

				plSCargo.at(i2).sID = mPlayer.Ship.getID();
				plSCargo.at(i2).iID = mPlayer.Ship.sCargo.at(i2).getIID();
				plSCargo.at(i2).iAmount = mPlayer.Ship.sCargo.at(i2).getIAmount();
				plSCargo.at(i2).iType = mPlayer.Ship.sCargo.at(i2).getIType();
				plSCargo.at(i2).iSG2 = mPlayer.Ship.sCargo.at(i2).getISpace();
			}
		}


		//Player Wingmen Data
		if (mPlayer.getNOWingmen() > 0) //Only if the player actually has wingmen else we are just wasting cpu power for nothing and causing crashes due to indecies being out of bounds
		{		
			//Get Player Wingmen Data
			for (i = 1; i <= mPlayer.getNOWingmen(); i++)
			{
				pWMData.push_back(pWingmenData());

				pWMData.at(pWMData.size()-1).pWName = mPlayer.eWingmen.at(i-1).getName();
				pWMData.at(pWMData.size()-1).pWRank = mPlayer.eWingmen.at(i-1).getRank();
				pWMData.at(pWMData.size()-1).pWCXPLevel = mPlayer.eWingmen.at(i-1).getCELvl();


				//Get Player Wingmen Ship Data
				pWMSData.push_back(pWShip());

				pWMSData.at(pWMSData.size()-1).pWID = i;
				pWMSData.at(pWMSData.size()-1).sName = mPlayer.eWingmen.at(i-1).Ship.getSName();
				pWMSData.at(pWMSData.size()-1).sClass = mPlayer.eWingmen.at(i-1).Ship.getSClass();
				pWMSData.at(pWMSData.size()-1).sTLevel = mPlayer.eWingmen.at(i-1).Ship.getSTLevel();
				pWMSData.at(pWMSData.size()-1).sSP = mPlayer.eWingmen.at(i-1).Ship.getSShield();
				pWMSData.at(pWMSData.size()-1).sAP = mPlayer.eWingmen.at(i-1).Ship.getSArmor();
				pWMSData.at(pWMSData.size()-1).sHP = mPlayer.eWingmen.at(i-1).Ship.getSHull();
				pWMSData.at(pWMSData.size()-1).sMSP = mPlayer.eWingmen.at(i-1).Ship.getSMShield();
				pWMSData.at(pWMSData.size()-1).sMAP = mPlayer.eWingmen.at(i-1).Ship.getSMArmor();
				pWMSData.at(pWMSData.size()-1).sMHP = mPlayer.eWingmen.at(i-1).Ship.getSMHull();
				pWMSData.at(pWMSData.size()-1).sMInit = mPlayer.eWingmen.at(i-1).Ship.getMInit();
				pWMSData.at(pWMSData.size()-1).sLB = mPlayer.eWingmen.at(i-1).Ship.getLHP();
				pWMSData.at(pWMSData.size()-1).sMT = mPlayer.eWingmen.at(i-1).Ship.getMTP();
				pWMSData.at(pWMSData.size()-1).sBH = mPlayer.eWingmen.at(i-1).Ship.getBH();
				pWMSData.at(pWMSData.size()-1).sRM = mPlayer.eWingmen.at(i-1).Ship.getRM();
				pWMSData.at(pWMSData.size()-1).sHWB = mPlayer.eWingmen.at(i-1).Ship.getHWB();
				pWMSData.at(pWMSData.size()-1).sWHP = mPlayer.eWingmen.at(i-1).Ship.getSWHP();
				pWMSData.at(pWMSData.size()-1).sULB = mPlayer.eWingmen.at(i-1).Ship.getULHP();
				pWMSData.at(pWMSData.size()-1).sUMT = mPlayer.eWingmen.at(i-1).Ship.getUMTP();
				pWMSData.at(pWMSData.size()-1).sUBH = mPlayer.eWingmen.at(i-1).Ship.getUBH();
				pWMSData.at(pWMSData.size()-1).sURM = mPlayer.eWingmen.at(i-1).Ship.getURM();
				pWMSData.at(pWMSData.size()-1).sUHWB = mPlayer.eWingmen.at(i-1).Ship.getUHWB();


				//Get Spread Information
				for (i2 = 1; i2 <= mPlayer.eWingmen.at(i-1).Ship.getSWSpreads(); i2++)
				{
					if (mPlayer.eWingmen.at(i-1).Ship.getSSize(i2) > 0)
					{
						tempHP = mPlayer.eWingmen.at(i-1).Ship.getSVect(i2);

						for (i3 = 0; i3 < mPlayer.eWingmen.at(i-1).Ship.getSSize(i); i3++)
						{
							pWMSSpreads.push_back(pWSSpread());

							pWMSSpreads.at(pWMSSpreads.size()-1).sID = tempHP.at(i3).getHPSlot();
							pWMSSpreads.at(pWMSSpreads.size()-1).sWType = tempHP.at(i3).getHPWType();
							pWMSSpreads.at(pWMSSpreads.size()-1).wID = i;
							pWMSSpreads.at(pWMSSpreads.size()-1).sPID = i2;
						}
					}
				}


				//Get Weapon Vector Data
				for (i2 = 1; i2 <= 5; i2++)
				{
					if (mPlayer.eWingmen.at(i-1).Ship.getWHPVSize(i2) > 0)
					{			
						switch(i2)
						{
						case 1:
							tempLWV = mPlayer.eWingmen.at(i-1).Ship.lBanks;

							for (i3 = 0; i3 < mPlayer.Ship.getWHPVSize(i2); i3++)
							{
								pWMSHPVectors.push_back(pWSHPVect());

								pWMSHPVectors.at(pWMSHPVectors.size()-1).sID = tempLWV.at(i3).getHPSlot();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wep_ID = tempLWV.at(i3).hpWeapon.getWID();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).sWType = tempLWV.at(i3).getHPWType();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wID = i; 
							}

							break;

						case 2:
							tempMWV = mPlayer.eWingmen.at(i-1).Ship.mTurrets;

							for (i3 = 0; i3 < mPlayer.eWingmen.at(i-1).Ship.getWHPVSize(i2); i3++)
							{
								pWMSHPVectors.push_back(pWSHPVect());

								pWMSHPVectors.at(pWMSHPVectors.size()-1).sID = tempMWV.at(i3).getHPSlot();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wep_ID = tempMWV.at(i3).hpWeapon.getWID();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).sWType = tempMWV.at(i3).getHPWType();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wID = i;
							}

							break;

						case 3:
							tempBWV = mPlayer.eWingmen.at(i-1).Ship.bHolds;

							for (i3 = 0; i3 < mPlayer.eWingmen.at(i-1).Ship.getWHPVSize(i2); i3++)
							{
								pWMSHPVectors.push_back(pWSHPVect());

								pWMSHPVectors.at(pWMSHPVectors.size()-1).sID = tempBWV.at(i3).getHPSlot();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wep_ID = tempBWV.at(i3).hpWeapon.getWID();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).sWType = tempBWV.at(i3).getHPWType();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wID = i;
							}

							break;

						case 4:
							tempRWV = mPlayer.eWingmen.at(i-1).Ship.rMounts;

							for (i3 = 0; i3 < mPlayer.eWingmen.at(i-1).Ship.getWHPVSize(i2); i3++)
							{
								pWMSHPVectors.push_back(pWSHPVect());

								pWMSHPVectors.at(pWMSHPVectors.size()-1).sID = tempRWV.at(i3).getHPSlot();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wep_ID = tempRWV.at(i3).hpWeapon.getWID();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).sWType = tempRWV.at(i3).getHPWType();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wID = i;
							}

							break;

						case 5:
							tempHWV = mPlayer.eWingmen.at(i-1).Ship.hWBays;

							for (i3 = 0; i3 < mPlayer.eWingmen.at(i-1).Ship.getWHPVSize(i2); i3++)
							{
								pWMSHPVectors.push_back(pWSHPVect());

								pWMSHPVectors.at(pWMSHPVectors.size()-1).sID = tempHWV.at(i3).getHPSlot();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wep_ID = tempHWV.at(i3).hpWeapon.getWID();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).sWType = tempHWV.at(i3).getHPWType();
								pWMSHPVectors.at(pWMSHPVectors.size()-1).wID = i;
							}

							break;
						}
					}
				}
			}
		}


		//Player Mission Data
		if (mPlayer.pMissions.size() > 0) //Only continue if player has missions (while this will be true 99% of the time, if a player has completed the story there is a good chance that no missions may be assigned
		{
			tempMis1 = mPlayer.pMissions; //Store mission vector

			for (i = 0; i < tempMis1.size(); i++)
			{
				pMData.push_back(missionData());

				pMData.at(pMData.size()-1).mID = tempMis1.at(i).getMID();
				pMData.at(pMData.size()-1).mName = tempMis1.at(i).getMName();
				pMData.at(pMData.size()-1).mDesc = tempMis1.at(i).getMDesc();
				pMData.at(pMData.size()-1).mType = tempMis1.at(i).getMType();
				pMData.at(pMData.size()-1).mCBEReq = tempMis1.at(i).getMCBEReq();
				pMData.at(pMData.size()-1).mSCReq = tempMis1.at(i).getMSCReq();
				pMData.at(pMData.size()-1).mMWReq = tempMis1.at(i).getMMWReq();
				pMData.at(pMData.size()-1).mDur = tempMis1.at(i).getMDur();
				pMData.at(pMData.size()-1).mDifficulty = tempMis1.at(i).getMDiff();
				pMData.at(pMData.size()-1).mLSector = tempMis1.at(i).getMSector();
				pMData.at(pMData.size()-1).mLSystem = tempMis1.at(i).getMSystem();
				pMData.at(pMData.size()-1).mTName = tempMis1.at(i).getMTName();
				pMData.at(pMData.size()-1).mTSClass = tempMis1.at(i).getMTSClass();
				pMData.at(pMData.size()-1).mBounty = tempMis1.at(i).getMBounty();
				pMData.at(pMData.size()-1).mXR = tempMis1.at(i).getMXR();
				pMData.at(pMData.size()-1).mRR = tempMis1.at(i).getMRR();
				pMData.at(pMData.size()-1).mDiR = tempMis1.at(i).getMDiR();
				pMData.at(pMData.size()-1).mDR = tempMis1.at(i).getMDR();
				pMData.at(pMData.size()-1).mLR = tempMis1.at(i).getMLR();
				pMData.at(pMData.size()-1).mPlR = tempMis1.at(i).getMPlR();
				pMData.at(pMData.size()-1).mUR = tempMis1.at(i).getMUR();
				pMData.at(pMData.size()-1).mPR = tempMis1.at(i).getMPR();
				pMData.at(pMData.size()-1).mNWR = tempMis1.at(i).getMNWR();
				pMData.at(pMData.size()-1).mEXPR = tempMis1.at(i).getMEXPR();
				pMData.at(pMData.size()-1).mIR = tempMis1.at(i).getMIR();
				pMData.at(pMData.size()-1).mState = tempMis1.at(i).getMStateID();
			}
		}
		
		if (mPlayer.pCMissions.size() > 0)
		{
			tempMis2 = mPlayer.pCMissions; //Store closed mission vector

			for (i = 0; i < tempMis2.size(); i++)
			{
				pMData.push_back(missionData());

				pMData.at(pMData.size()-1).mID = tempMis2.at(i).getMID();
				pMData.at(pMData.size()-1).mName = tempMis2.at(i).getMName();
				pMData.at(pMData.size()-1).mDesc = tempMis2.at(i).getMDesc();
				pMData.at(pMData.size()-1).mType = tempMis2.at(i).getMType();
				pMData.at(pMData.size()-1).mCBEReq = tempMis2.at(i).getMCBEReq(); //combat experience requirement
				pMData.at(pMData.size()-1).mSCReq = tempMis2.at(i).getMSCReq(); //ship requirement
				pMData.at(pMData.size()-1).mMWReq = tempMis2.at(i).getMMWReq(); //module/weapon requirement
				pMData.at(pMData.size()-1).mDur = tempMis2.at(i).getMDur(); //duration in days
				pMData.at(pMData.size()-1).mDifficulty = tempMis2.at(i).getMDiff();
				pMData.at(pMData.size()-1).mLSector = tempMis2.at(i).getMSector(); //location; sector
				pMData.at(pMData.size()-1).mLSystem = tempMis2.at(i).getMSystem(); //location; system
				pMData.at(pMData.size()-1).mTName = tempMis2.at(i).getMTName(); //target name
				pMData.at(pMData.size()-1).mTSClass = tempMis2.at(i).getMTSClass(); //target ship class
				pMData.at(pMData.size()-1).mBounty = tempMis2.at(i).getMBounty();
				pMData.at(pMData.size()-1).mXR = tempMis2.at(i).getMXR(); //xarn reward
				pMData.at(pMData.size()-1).mRR = tempMis2.at(i).getMRR(); //ruby reward
				pMData.at(pMData.size()-1).mDiR = tempMis2.at(i).getMDiR(); //diamond reward
				pMData.at(pMData.size()-1).mDR = tempMis2.at(i).getMDR(); //draconic reward
				pMData.at(pMData.size()-1).mLR = tempMis2.at(i).getMLR(); //lithium reward
				pMData.at(pMData.size()-1).mPlR = tempMis2.at(i).getMPlR(); //platinum reward
				pMData.at(pMData.size()-1).mUR = tempMis2.at(i).getMUR(); //uranium reward
				pMData.at(pMData.size()-1).mPR = tempMis2.at(i).getMPR(); //plutonium reward
				pMData.at(pMData.size()-1).mNWR = tempMis2.at(i).getMNWR(); //nuclear waste reward
				pMData.at(pMData.size()-1).mEXPR = tempMis2.at(i).getMEXPR(); //exp reward
				pMData.at(pMData.size()-1).mIR = tempMis2.at(i).getMIR(); //item reward;
				pMData.at(pMData.size()-1).mState = tempMis2.at(i).getMStateID(); //Mission State
			} 
		}

		//Player Relation Data
		if (mPlayer.pRelations.size() > 0) //While this should NEVER be untrue, we check anyway in case of bugs or other weird issues that may cause problems or crashes if we did not check
		{
			tempR = mPlayer.pRelations;

			for (i = 0; i < tempR.size(); i++)
			{
				pRData.push_back(relationData());

				pRData.at(pRData.size()-1).rName = tempR.at(i).getRName();
				pRData.at(pRData.size()-1).rAffinity = tempR.at(i).getAffinity();
			}
		}

		//Station Data
		if (mGame->gStations.size() > 0) //Only continue if stations have been generated
		{
			for (i = 0; i < mGame->gStations.size(); i++)
			{
				stData.push_back(stationData());

				stData.at(stData.size()-1).sID = mGame->gStations.at(i).getSID();
				stData.at(stData.size()-1).sName = mGame->gStations.at(i).getName();
				stData.at(stData.size()-1).sAffiliation = mGame->gStations.at(i).getAffil();
				stData.at(stData.size()-1).sDispo = mGame->gStations.at(i).getDispo();
				stData.at(stData.size()-1).sTLevel = mGame->gStations.at(i).getTLevel();
				stData.at(stData.size()-1).sLevel = mGame->gStations.at(i).getSLevel();
				stData.at(stData.size()-1).sMSpace = mGame->gStations.at(i).getMUSpace();
				stData.at(stData.size()-1).sCMulti = mGame->gStations.at(i).getCMulti();

				if (mGame->gStations.at(i).sInventory.size() > 0)
				{
					sPInventory.push_back(sPInv());

					tempInv = mGame->gStations.at(i).sInventory;
					
					for (i2 = 0; i2 < tempInv.size(); i2++)
					{	
						if (tempInv.at(i2).getIType() == "Ship")
						{
							plShip.push_back(pShip());

							plShip.at(plShip.size()-1).sName = tempInv.at(i2).sShip.getSName();
							plShip.at(plShip.size()-1).sClass = tempInv.at(i2).sShip.getSClass();
							plShip.at(plShip.size()-1).sTLevel = tempInv.at(i2).sShip.getSTLevel();
							plShip.at(plShip.size()-1).sSP = tempInv.at(i2).sShip.getSShield();
							plShip.at(plShip.size()-1).sAP = tempInv.at(i2).sShip.getSArmor();
							plShip.at(plShip.size()-1).sHP = tempInv.at(i2).sShip.getSHull();
							plShip.at(plShip.size()-1).sMSP = tempInv.at(i2).sShip.getSMShield();
							plShip.at(plShip.size()-1).sMAP = tempInv.at(i2).sShip.getSMArmor();
							plShip.at(plShip.size()-1).sMHP = tempInv.at(i2).sShip.getSMHull();
							plShip.at(plShip.size()-1).sMInit = tempInv.at(i2).sShip.getMInit();
							plShip.at(plShip.size()-1).sSG2 = tempInv.at(i2).sShip.getSSG2();
							plShip.at(plShip.size()-1).sMCSpace = tempInv.at(i2).sShip.getMCSpace();
							plShip.at(plShip.size()-1).sLB = tempInv.at(i2).sShip.getLHP();
							plShip.at(plShip.size()-1).sMT = tempInv.at(i2).sShip.getMTP();
							plShip.at(plShip.size()-1).sBH = tempInv.at(i2).sShip.getBH();
							plShip.at(plShip.size()-1).sRM = tempInv.at(i2).sShip.getRM();
							plShip.at(plShip.size()-1).sHWB = tempInv.at(i2).sShip.getHWB();
							plShip.at(plShip.size()-1).sWHP = tempInv.at(i2).sShip.getSWHP();
							plShip.at(plShip.size()-1).sULB = tempInv.at(i2).sShip.getULHP();
							plShip.at(plShip.size()-1).sUMT = tempInv.at(i2).sShip.getUMTP();
							plShip.at(plShip.size()-1).sUBH = tempInv.at(i2).sShip.getUBH();
							plShip.at(plShip.size()-1).sURM = tempInv.at(i2).sShip.getURM();
							plShip.at(plShip.size()-1).sUHWB = tempInv.at(i2).sShip.getUHWB();
							plShip.at(plShip.size()-1).sID = tempInv.at(i2).sShip.getID(); //ship_data id
							plShip.at(plShip.size()-1).sSID = tempInv.at(i2).sShip.getSID(); //0 means active player ship; -1 means not stored| Ship ID
							plShip.at(plShip.size()-1).sSTID = tempInv.at(i2).sShip.getSTID(); //station ID; -1 means not stored in station, 0-x are the station ID in gStations vector
							plShip.at(plShip.size()-1).sLocal = tempInv.at(i2).sShip.getSLocal(); //Store location; Ship for stored on ship, Station for stored on station, and none for player active ship
						}

						else
						{
							sPInventory.at(i).sID = mGame->gStations.at(i).getSID();	
							sPInventory.at(i).iID = tempInv.at(i2).getIID();
							sPInventory.at(i).NOI = tempInv.at(i2).getIAmount();
							sPInventory.at(i).iType = tempInv.at(i2).getIType();
							sPInventory.at(i).iSG2 = tempInv.at(i2).getISpace();
						}
					}
				}
			}
		}


		//Planet Data
		if (mGame->gPlanets.size() > 0)
		{
			lastAID = 0;

			for (i = 0; i < mGame->gPlanets.size(); i++)
			{
				plData.push_back(planetData());

				plData.at(plData.size()-1).pID = mGame->gPlanets.at(i).getPID(); 
				plData.at(plData.size()-1).pName = mGame->gPlanets.at(i).getName();
				plData.at(plData.size()-1).pAffiliation = mGame->gPlanets.at(i).getAffil();
				plData.at(plData.size()-1).pDispo = mGame->gPlanets.at(i).getDispo();

				//if (mGame->gPlanets.at(i).bIsPOwned())
				//{
				//	plData.at(plData.size()-1).bIsPOwned = 1;
				//}

				//else
				//{
				plData.at(plData.size()-1).bIsPOwned = 0;
				//}

				if (mGame->gPlanets.at(i).bPIsDest())
				{
					plData.at(plData.size()-1).bIsDestroyed = 1;
				}

				else
				{
					plData.at(plData.size()-1).bIsDestroyed = 0;
				}

				plData.at(plData.size()-1).pEKS = mGame->gPlanets.at(i).getEKS();
				plData.at(plData.size()-1).pSize = mGame->gPlanets.at(i).getSize();
				plData.at(plData.size()-1).pCPop = mGame->gPlanets.at(i).getPop();
				plData.at(plData.size()-1).pMPop = mGame->gPlanets.at(i).getMPop();


				//Planet Defense Vector Data

				if (mGame->gPlanets.at(i).pDef.size() > 0)
				{
					tempDData = mGame->gPlanets.at(i).pDef;

					for (i2 = 0; i2 <tempDData.size(); i2++)
					{
						plDData.push_back(pDefData());					

						plDData.at(plDData.size()-1).pID = mGame->gPlanets.at(i).getPID();
						plDData.at(plDData.size()-1).pDID = tempDData.at(i2).getID();
					}
				}


				//Planet Shield Vector Data
				if (mGame->gPlanets.at(i).pShd.size() > 0)
				{
					tempSData = mGame->gPlanets.at(i).pShd;

					for (i2 = 0; i2 < tempSData.size(); i2++)
					{
						plSData.push_back(pSData());

						plSData.at(plSData.size()-1).pID = mGame->gPlanets.at(i).getPID();
						plSData.at(plSData.size()-1).mID = tempSData.at(i2).getID();
					}
				}

				tempBelts = mGame->gPlanets.at(i).belts;

				//Planet A. Belts
				for (i2 = 1; i2 <= tempBelts.size(); i2++)
				{
					if (i2 == tempBelts.size())
					{
						break;
					}

					else
					{
						belts.push_back(pABelts());

						//tempBelts.at(i2).getABName(), tempBelts.at(i2).getABSize, tempBelts.at(i2).roids.size(), true
											
						belts.at(belts.size()-1).bID = i2;
						belts.at(belts.size()-1).pID = mGame->gPlanets.at(i).getPID();
						belts.at(belts.size()-1).bName = tempBelts.at(i2-1).getABName();
						belts.at(belts.size()-1).bSize = tempBelts.at(i2-1).getABSize();
						
						if (tempBelts.at(i2-1).isFull())
						{						
							belts.at(belts.size()-1).bBIsFull = 1;
						}

						else
						{
							belts.at(belts.size()-1).bBIsFull = 0;
						}
					}
						

					tempRoids = tempBelts.at(i2-1).roids;

					for (i3 = 1; i3 <= tempRoids.size(); i3++)
					{
						if (i3 == tempRoids.size())
						{
							if (lastAID == 0)
							{
								lastAID = i3-1;
								break;
							}

							else
							{
								lastAID += i3-1;
								break;
							}
						}							

						else
						{
							roids.push_back(pABRoids());

							if (lastAID == 0)
							{
								roids.at(roids.size()-1).aID = i3;
							}

							else
							{
								roids.at(roids.size()-1).aID = lastAID + i3;
							}
														
							roids.at(roids.size()-1).bID = i2;
							roids.at(roids.size()-1).pID = mGame->gPlanets.at(i).getPID();
							roids.at(roids.size()-1).aName = tempRoids.at(i3-1).getAName();
							roids.at(roids.size()-1).aDesc = tempRoids.at(i3-1).getADesc();
							roids.at(roids.size()-1).aSize = tempRoids.at(i3-1).getASize();
							roids.at(roids.size()-1).aOName = tempRoids.at(i3-1).getOName();
							roids.at(roids.size()-1).aOID = tempRoids.at(i3-1).getAOID();
							roids.at(roids.size()-1).aOAmount = tempRoids.at(i3-1).getAOAmount();
							roids.at(roids.size()-1).xPos = tempRoids.at(i3-1).getXPos();
							roids.at(roids.size()-1).yPos = tempRoids.at(i3-1).getYPos();
							roids.at(roids.size()-1).zPos = tempRoids.at(i3-1).getZPos();
						}
					}
				}					
			}
		}		

		db_ds.sData(pData, plShip, plSSpreads, plSHPVectors, plSCargo, pWMData, pWMSData, pWMSSpreads, pWMSHPVectors, stData, sPInventory, plData, plDData, plSData, belts, roids, pMData, pRData, &bErrors);
		return true;
	}

	else
	{
		problems("saving data");
		return false;
	}
}

void dataSystem::problems(string operation)
{
	cout << "A problem occured while " << operation << ".  The operation was not carried out due to errors or no data (note that in certain cases no data is normal).  Check log for more details and information for bug report submission." << endl;
	bECount += 1;
}

int dataSystem::getFlag(string fName)
{
	for (i = 0; i < saveFlags.size(); i++)
	{
		if (saveFlags.at(i).sfName == fName)
		{
			return saveFlags.at(i).sfValue;
		}
	}
}