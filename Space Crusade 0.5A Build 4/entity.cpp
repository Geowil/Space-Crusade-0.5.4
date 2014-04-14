#include <string>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <cstdlib>

#include "entity.h"
#include "battleproc.h"
#include "msgproc.h"
#include "datasystem.h"
#include "damage.h"
#include "random.h"
#include "mission.h"
#include "relation.h"
#include "nameGen.h"

using namespace std;

//Class References
dataSystem ds_e;
msgProc mp_e;
Mission m_e;
Relation r_e;
nameGen ng_e;

//NPC Scrap Multipliers
#define Scrap_Level_1 1
#define Scrap_Level_2 0.15
#define Scrap_Level_3 0.25
#define Scrap_Level_4 0.40
#define Scrap_Level_5 0.75

//Entity

Entity::Entity()
{

}

void Entity::applySDamage(float damage) //Shields
{	
	Ship.updateSShield(damage, "sub");
}

void Entity::applyADamage(float damage) //Armor
{
	Ship.updateSArmor(damage, "sub");
}

void Entity::applyHDamage(float damage) //Hull
{	
	Ship.updateSHull(damage, "sub");
}

void Entity::updateXarn(int xarn, string operation)
{
	if (operation == "add")
	{
		eXarn += xarn;
	}

	else if (operation == "sub")
	{
		eXarn -= xarn;
	}

	else if (operation == "set")
	{
		eXarn = xarn;
	}
}

void Entity::updateRubies(int rubies, string operation)
{
	if (operation == "add")
	{
		eRub += rubies;
	}

	else if (operation == "sub")
	{
		eRub -= rubies;
	}

	else if (operation == "set")
	{
		eRub = rubies;
	}
}

void Entity::updateDia(int dia, string operation)
{
	if (operation == "add")
	{
		eDia += dia;
	}

	else if (operation == "sub")
	{
		eDia -= dia;
	}

	else if (operation == "set")
	{
		eDia = dia;
	}
}

void Entity::updateDrac(int drac, string operation)
{
	if (operation == "add")
	{
		eDrac += drac;
	}

	else if (operation == "sub")
	{
		eDrac -= drac;
	}

	else if (operation == "set")
	{
		eDrac = drac;
	}
}

void Entity::updateLith(int lith, string operation)
{
	if (operation == "add")
	{
		eLith += lith;
	}

	else if (operation == "sub")
	{
		eLith -= lith;
	}

	else if (operation == "set")
	{
		eLith = lith;
	}
}

void Entity::updatePlat(int plat, string operation)
{
	if (operation == "add")
	{
		ePlat += plat;
	}

	else if (operation == "sub")
	{
		ePlat -= plat;
	}

	else if (operation == "set")
	{
		ePlat = plat;
	}
}

void Entity::updateUra(int ura, string operation)
{
	if (operation == "add")
	{
		eUra += ura;
	}

	else if (operation == "sub")
	{
		eUra -= ura;
	}

	else if (operation == "set")
	{
		eUra = ura;
	}
}

void Entity::updatePlut(int plut, string operation)
{
	if (operation == "add")
	{
		ePlut += plut;
	}

	else if (operation == "sub")
	{
		ePlut -= plut;
	}

	else if (operation == "set")
	{
		ePlut = plut;
	}
}

void Entity::updateNWaste(int nwaste, string operation)
{
	if (operation == "add")
	{
		eNWaste += nwaste;
	}

	else if (operation == "sub")
	{
		eNWaste -= nwaste;
	}

	else if (operation == "set")
	{
		eNWaste = nwaste;
	}
}

bool Entity::isHostile()
{
	return bIsHostile;
}

string Entity::getDispo()
{
	return eDispo;
}

string Entity::getName()
{
	return eName;
}

void Entity::setName(string name)
{
	eName = name;
}

void Entity::setRace(string race)
{
	eRace = race;
}

void Entity::setRank(string rank)
{
	eRank = rank;
}

void Entity::setDispo(string dispo)
{
	eDispo = dispo;
}

string Entity::getRank()
{
	return eRank;
}

string Entity::getRace()
{
	return eRace;
}

string Entity::getAffil()
{
	return eAffil;
}

void Entity::setAffil(string affil)
{
	eAffil = affil;
}

int Entity::getCELvl()
{
	return eCXPLevel;
}

int Entity::getXarn()
{
	return eXarn;
}

int Entity::getRubies()
{
	return eRub;
}

int Entity::getDia()
{
	return eDia;
}

int Entity::getDrac()
{
	return eDrac;
}

int Entity::getLith()
{
	return eLith;
}

int Entity::getPlat()
{
	return ePlat;
}

int Entity::getUra()
{
	return eUra;
}

int Entity::getPlut()
{
	return ePlut;
}

int Entity::getNWaste()
{
	return eNWaste;
}

void Entity::setStatus(string estat)
{
	eBStatus = estat;
}

string Entity::getStatus()
{
	return eBStatus;
}

Entity* Entity::rEntity()
{
	return this;
}

bool Entity::gOver(Game& mGame, Player& mPlayer)
{
	if (mp_e.cClone(&sID, &sIID, mGame))
	{
		iID = mGame.gStations.at(sID).sInventory.at(sIID).getIID(); //Get the item ID for use in a bit

		mGame.useClone(mPlayer, sID, sIID, iID);

		return false;
	}

	else
	{
		mp_e.gOver();

		return true;
	}
}

void Entity::updateCXPLvl(int lvl, string operation)
{
	if (operation == "add")
	{
		eCXPLevel =+ lvl;
	}

	else if (operation == "sub")
	{
		eCXPLevel -= lvl;
	}

	else if (operation == "set")
	{
		eCXPLevel = lvl;
	}
}


//Player
Player::Player()
{		
	eRank = "Private";
	pPDest = 0;	
	
	//begin resource definition
	eXarn = 0;
	eRub = 0;
	eDia = 0;
	eDrac = 0;
	eLith = 0;
	eUra = 0;
	ePlat = 0;
	ePlut = 0;
	eNWaste = 0;
	
	//begin misc definition
	pCELevel = 0;
	pCXP = 0;
	tNCELevel = 0;
	eAffil = "Earth Alliance";
}

void Player::pSetup()
{
	//begin player definition
	cout << "Please enter your name: " << endl;
	cout << "> ";
	cin >> eName;
	cout << endl;
	cout << endl;
	
	//begin ship definition
	pCShip();
	pCLWeap();
	pCMWeap();
	pCBWeap();

	//Add start resources
	eXarn = 200;
	eRub = 120;
	eDia = 100;
	eDrac = 200;
	eLith = 160;
	eUra = 40;
	ePlut = 25;
	eNWaste = 10;

	//Call CELUp to set up cExp for next level
	cELUp();

	//Init one mission vector element for default mission
	pMissions.push_back(m_e);
	pMissions.at(0).createMission(3); //Create the default mission

	//Init relationship vector elements for default relationships
	for (i = 0; i <= 2; i++)
	{
		pRelations.push_back(r_e);
	}

	pRelations.at(0).createRelation("Earth Alliance",80); //Create the default relationship for EA
	pRelations.at(1).createRelation("Juslorth Empire",-100); //Create the default relationship for Juslorth
	pRelations.at(2).createRelation("Sluikan Imperium",-85); //Create the default relationship for Sluikan
}

void Player::pCShip()
{
	sCode = mp_e.pCMenu1();
	mp_e.mCScreen(false);
	Ship.initShip(sCode);
}


void Player::pCLWeap()
{
	wCode = mp_e.pCMenu2();
	mp_e.mCScreen(false);
	Ship.iWeapon("laser", wCode);
}


void Player::pCMWeap()
{
	wCode = mp_e.pCMenu3();
	mp_e.mCScreen(false);
	Ship.iWeapon("missile", wCode);
}


void Player::pCBWeap()
{
	wCode = mp_e.pCMenu4();
	mp_e.mCScreen(false);
	Ship.iWeapon("bomb", wCode);
}

void Player::rUp()
{
	if ((pCELevel > 102) && (pFKills > 75) && (pDKills > 38) && (pCKills > 25) && (pBCKills > 16) && (pBKills > 20) && (pMKills > 0)) //Add command ships when c. ships are added
	{
		eRank = "Admiral";
	}

	else if ((pCELevel > 80) && (pFKills > 50) && (pDKills > 23) && (pCKills > 18) && (pBCKills > 8) && (pBKills > 6))
	{
		eRank = "Commodore";
	}

	else if ((pCELevel > 62) && (pFKills > 35) && (pDKills > 18) && (pCKills > 10) && (pBCKills > 0) && (pBKills > 0))
	{
		eRank = "Captain";
	}

	else if ((pCELevel > 45) && (pFKills > 25) && (pDKills > 12) && (pCKills > 4))
	{
		eRank = "Commander";
	}

	else if ((pCELevel > 26) && (pFKills > 20) && (pDKills > 8) && (pCKills > 0))
	{
		eRank = "Lieutenant Commander";
	}

	else if ((pCELevel > 18) && (pFKills > 14) && (pDKills > 3))
	{
		eRank = "Lieutenant";
	}

	else if ((pCELevel > 10) && (pFKills > 8) && (pDKills > 0))
	{
		eRank = "Sub Lieutenant";
	}

	else if ((pCELevel > 5) && (pFKills > 5))
	{
		eRank = "Private First Class";
	}
}

void Player::cELUp()
{
	if (pCXP >= tNCELevel)
	{
		pCELevel += 1;
		tNCELevel = (pCELevel * 1250.0) * 1000000.0 * pCELevel / (((1000.0 * (pCELevel * 1250.0)) / 2) / 2.3);
	}
}

void Player::cELDown()
{
	pCELevel -= 1;
}

int Player::calcOCXPTNL(int cLevel)
{
	cLevel -= 1;
	return (cLevel * 1250.0) * 1000000.0 * cLevel / (((1000.0 * (cLevel * 1250.0)) / 2) / 2.3);
}

void Player::updateCEXP(int cExp, string operation)
{
	if (operation == "add")
	{
		pCXP += cExp;
	}

	else if (operation == "sub")
	{
		pCXP -= cExp;
	}

	else if (operation == "set")
	{
		pCXP = cExp;
	}

	cELUp(); //Check if the player can level up
}

int Player::getCEXP()
{
	return pCXP;
}

int Player::getCXPTNL()
{
	return tNCELevel;
}

void Player::setCXPTNL(int cXPTNL)
{
	tNCELevel = cXPTNL;
}

int Player::getCELvl()
{
	return pCELevel;
}

void Player::setBOKills(int i)
{
	pBOKill = i;
}

int Player::getBOKills()
{
	return pBOKill;
}

void Player::addMission(int mCode)
{
	ds_e.rData("Mission_Data","select from",mCode);

	for (i = 0;; i++)
	{
		if (i >= pMissions.size())
		{
			pMissions.push_back(m_e);

			pMissions.at(pMissions.size()-1).createMission(mCode);
			break;
		}
		
		else if (i < pMissions.size())
		{
			if (pMissions.at(i).getMName() == ds_e.getMName())
			{
				cout << mp_e.mRMessage(21) << endl;
				break;
			}			
		}		
	}
}

void Player::updateMission(int mCode, bool bChangeTName, string tname, bool bChangeMLSector, string mlsector, bool bChangeMLSystem, string mlsystem, bool bChangeDur, int duration)
{
	for (i = 0;; i++)
	{		
		ds_e.rData("Mission_Data","select from",mCode);

		if (i >= pMissions.size())
		{
			cout << mp_e.mRMessage(22) << endl;
		}
		
		else if (pMissions.at(i).getMName() == ds_e.getMName())
		{
			pMissions.at(i).updateMission(bChangeTName, tname, bChangeMLSector, mlsector, bChangeMLSystem, mlsystem, bChangeDur, duration);
			break;
		}
	}
}

void Player::removeMission(int mCode)
{
	for (i = 0;;i++)
	{
		ds_e.rData("Mission_Data","select from",mCode);

		if (i >= pMissions.size())
		{
			cout << mp_e.mRMessage(23) << endl;
		}
		
		else if (pMissions.at(i).getMID() == ds_e.getMisID())
		{
			pCMissions.push_back(Mission());

			pCMissions.at(pCMissions.size()-1) = pMissions.at(i); //Save closed mission to the pCMissions vector

			pMissions.erase(pMissions.begin() + i); //Then delete the mission from the pMissions vector
		}		
	}
}

void Player::getMission(int mCode)
{
	for (i = 0;;i++)
	{
		ds_e.rData("Mission_Data","select from",mCode);
		
		if (i >= pMissions.size())
		{
			cout << mp_e.mRMessage(24) << endl;
		}
		
		else if (pMissions.at(i).getMID() == ds_e.getMisID())
		{
			pMissions.at(i).getCMInfo();
		}		
	}
}

void Player::getAMissions()
{
	for (i = 0; i < pMissions.size(); i++)
	{	
		if (pMissions.at(i).getMState() == "In Progress")
		{
			pMissions.at(i).getBMInfo();
		}
	}
}

void Player::completeMission(int mCode)
{
	pMissions.at(mCode).setMState(2); //Set state to completed

	pCMissions.push_back(Mission()); //Push back a new element on completed missions vector

	pCMissions.at(pCMissions.size()-1) = pMissions.at(mCode); //load completed mission into newly created element

	pMissions.erase(pMissions.begin() + mCode); //Remove the completed mission from the missions vector
}

void Player::addRelation(string rName, int rAffinity)
{
	pRelations.push_back(Relation(rName, rAffinity));
}

void Player::updateRelation(string rName, int rAffinity, string operation)
{
	for (i = 0; i < pRelations.size(); i++)
	{
		if (pRelations.at(i).getRName() == rName)
		{
			if (operation == "add")
			{
				pRelations.at(i).setRAffinity((pRelations.at(i).getAffinity() + rAffinity));
			}

			else if (operation == "sub")
			{
				pRelations.at(i).setRAffinity((pRelations.at(i).getAffinity() - rAffinity));
			}

			else if (operation == "set")
			{
				pRelations.at(i).setRAffinity(rAffinity);
			}
		}
	}
}

vector<Relation> Player::getARStatus()
{
	return pRelations;
}

int Player::getRStatus(string rName)
{
	for (i = 0; i <= pRelations.size(); i++)
	{
		if ( i == pRelations.size()) //If relation does not exist create it and return the affinity; this first due to how the if statement is set up
		{
			pRelations.push_back(r_e);
			pRelations.at(i).createRelation(rName,Random(-20,20)); //Create the relation and set the affinity to a value in the range

			return pRelations.at(i).getAffinity();
		}

		else if (i < pRelations.size())
		{
			if (rName == pRelations.at(i).getRName())
			{
				return pRelations.at(i).getAffinity();
			}
		}
	}
}

int Player::getNOWingmen()
{
	return eWingmen.size();
}

void Player::updateDPlanets(int pd, string operation)
{
	if (operation == "add")
	{
		pPDest += pd;
	}

	else if (operation == "sub")
	{
		pPDest -= pd;
	}

	else if (operation == "set")
	{
		pPDest = pd;
	}
}

int Player::getDPlanets()
{
	return pPDest;
}

void Player::updateFKills(int kills, string operation)
{
	if (operation == "add")
	{
		pFKills += kills;
	}

	else if (operation == "sub")
	{
		pFKills -= kills;
	}

	else if (operation == "set")
	{
		pFKills = kills;
	}
}

void Player::updateDKills(int kills, string operation)
{
	if (operation == "add")
	{
		pDKills += kills;
	}

	else if (operation == "sub")
	{
		pDKills -= kills;
	}

	else if (operation == "set")
	{
		pDKills = kills;
	}
}

void Player::updateCKills(int kills, string operation)
{
	if (operation == "add")
	{
		pCKills += kills;
	}

	else if (operation == "sub")
	{
		pCKills -= kills;
	}

	else if (operation == "set")
	{
		pCKills = kills;
	}
}

void Player::updateBCKills(int kills, string operation)
{
	if (operation == "add")
	{
		pBCKills += kills;
	}

	else if (operation == "sub")
	{
		pBCKills -= kills;
	}

	else if (operation == "set")
	{
		pBCKills = kills;
	}
}

void Player::updateBKills(int kills, string operation)
{
	if (operation == "add")
	{
		pBKills += kills;
	}

	else if (operation == "sub")
	{
		pBKills -= kills;
	}

	else if (operation == "set")
	{
		pBKills = kills;
	}
}

void Player::updateMKills(int kills, string operation)
{
	if (operation == "add")
	{
		pMKills += kills;
	}

	else if (operation == "sub")
	{
		pMKills -= kills;
	}

	else if (operation == "set")
	{
		pMKills = kills;
	}
}

void Player::updateTKills(int kills, string operation)
{
	if (operation == "add")
	{
		pTKills += kills;
	}

	else if (operation == "sub")
	{
		pTKills -= kills;
	}

	else if (operation == "set")
	{
		pTKills = kills;
	}
}

int Player::getFKills()
{
	return pFKills;
}

int Player::getDKills()
{
	return pDKills;
}

int Player::getCKills()
{
	return pCKills;
}

int Player::getBCKills()
{
	return pBCKills;
}

int Player::getBKills()
{
	return pBKills;
}

int Player::getMKills()
{
	return pMKills;
}

int Player::getTKills()
{
	return pTKills;
}

void Player::addWingman()
{
	eWingmen.push_back(Player());
}

void Player::loadMission1(missionData mData)
{
	pMissions.push_back(Mission());

	pMissions.at(pMissions.size()-1).setMID(mData.mID);
	pMissions.at(pMissions.size()-1).setMName(mData.mName);
	pMissions.at(pMissions.size()-1).setMDesc(mData.mDesc);
	pMissions.at(pMissions.size()-1).setMType(mData.mType);
	pMissions.at(pMissions.size()-1).setMCBEReq(mData.mCBEReq);
	pMissions.at(pMissions.size()-1).setMSCReq(mData.mSCReq);
	pMissions.at(pMissions.size()-1).setMMWReq(mData.mMWReq);
	pMissions.at(pMissions.size()-1).setMDur(mData.mDur);
	pMissions.at(pMissions.size()-1).setMDiff(mData.mDifficulty);
	pMissions.at(pMissions.size()-1).setMSector(mData.mLSector);
	pMissions.at(pMissions.size()-1).setMSystem(mData.mLSystem);
	pMissions.at(pMissions.size()-1).setMTName(mData.mTName);
	pMissions.at(pMissions.size()-1).setMTSClass(mData.mTSClass);
	pMissions.at(pMissions.size()-1).setMBounty(mData.mBounty);
	pMissions.at(pMissions.size()-1).setMXR(mData.mXR);
	pMissions.at(pMissions.size()-1).setMRR(mData.mRR);
	pMissions.at(pMissions.size()-1).setMDiR(mData.mDiR);
	pMissions.at(pMissions.size()-1).setMDR(mData.mDR);
	pMissions.at(pMissions.size()-1).setMLR(mData.mLR);
	pMissions.at(pMissions.size()-1).setMPlR(mData.mPlR);
	pMissions.at(pMissions.size()-1).setMUR(mData.mUR);
	pMissions.at(pMissions.size()-1).setMPR(mData.mPR);
	pMissions.at(pMissions.size()-1).setMNWR(mData.mNWR);
	pMissions.at(pMissions.size()-1).setMEXPR(mData.mEXPR);
	pMissions.at(pMissions.size()-1).setMIR(mData.mIR);
	pMissions.at(pMissions.size()-1).setMState(mData.mState);
}

void Player::loadMission2(missionData mData)
{
	pCMissions.push_back(Mission());

	pCMissions.at(pCMissions.size()-1).setMID(mData.mID);
	pCMissions.at(pCMissions.size()-1).setMName(mData.mName);
	pCMissions.at(pCMissions.size()-1).setMDesc(mData.mDesc);
	pCMissions.at(pCMissions.size()-1).setMType(mData.mType);
	pCMissions.at(pCMissions.size()-1).setMCBEReq(mData.mCBEReq);
	pCMissions.at(pCMissions.size()-1).setMSCReq(mData.mSCReq);
	pCMissions.at(pCMissions.size()-1).setMMWReq(mData.mMWReq);
	pCMissions.at(pCMissions.size()-1).setMDur(mData.mDur);
	pCMissions.at(pCMissions.size()-1).setMDiff(mData.mDifficulty);
	pCMissions.at(pCMissions.size()-1).setMSector(mData.mLSector);
	pCMissions.at(pCMissions.size()-1).setMSystem(mData.mLSystem);
	pCMissions.at(pCMissions.size()-1).setMTName(mData.mTName);
	pCMissions.at(pCMissions.size()-1).setMTSClass(mData.mTSClass);
	pCMissions.at(pCMissions.size()-1).setMBounty(mData.mBounty);
	pCMissions.at(pCMissions.size()-1).setMXR(mData.mXR);
	pCMissions.at(pCMissions.size()-1).setMRR(mData.mRR);
	pCMissions.at(pCMissions.size()-1).setMDiR(mData.mDiR);
	pCMissions.at(pCMissions.size()-1).setMDR(mData.mDR);
	pCMissions.at(pCMissions.size()-1).setMLR(mData.mLR);
	pCMissions.at(pCMissions.size()-1).setMPlR(mData.mPlR);
	pCMissions.at(pCMissions.size()-1).setMUR(mData.mUR);
	pCMissions.at(pCMissions.size()-1).setMPR(mData.mPR);
	pCMissions.at(pCMissions.size()-1).setMNWR(mData.mNWR);
	pCMissions.at(pCMissions.size()-1).setMEXPR(mData.mEXPR);
	pCMissions.at(pCMissions.size()-1).setMIR(mData.mIR);
	pCMissions.at(pCMissions.size()-1).setMState(mData.mState);
}

void Player::loadRelation(relationData rData)
{
	pRelations.push_back(Relation());

	pRelations.at(pRelations.size()-1).setRName(rData.rName);
	pRelations.at(pRelations.size()-1).setRAffinity(rData.rAffinity);
}

void Player::setPLocale(string s)
{
	pLocale = s;
}

string Player::getPLocale()
{
	return pLocale;
}



//NPC

NPC::NPC()
{
}

NPC::NPC(string name, string race, string rank, int sCode)
{
	eName = name;	
	eRace = race;
	eRank = rank;
	
	Ship.initShip(sCode);
	sCode = nSID;
}

void NPC::hSetup(int rkCode, int rCode, int sCode)
{
	//Set Race
	ds_e.rData("Race_Data","select from",rCode);
	eRace = ds_e.getERace();

	//Set Rank
	ds_e.rData("Rank_Data","select from",rkCode);
	eRank = ds_e.getERank();

	//Initialize Ship
	Ship.initShip(sCode);	

	//Name
	eName = ng_e.genName("Humanoid");

	sCode = nSID;

	//Set resources
	eXarn = 0;
	eRub = 0;
	eDia = 0;
	eDrac = 0;
	eLith = 0;
	ePlat = 0;
	eUra = 0;
	ePlut = 0;
	eNWaste = 0;
	cEXPReward = 0;
}

int NPC::getXarn()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eXarn*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eXarn*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eXarn*Scrap_Level_3;
	}
}

int NPC::getRubies()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eRub*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eRub*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eRub*Scrap_Level_3;
	}
}

int NPC::getDia()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eDia*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eDia*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eDia*Scrap_Level_3;
	}
}

int NPC::getDrac()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eDrac*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eDrac*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eDrac*Scrap_Level_3;
	}
}

int NPC::getLith()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eLith*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eLith*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eLith*Scrap_Level_3;
	}
}

int NPC::getPlat()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return ePlat*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return ePlat*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return ePlat*Scrap_Level_3;
	}
}

int NPC::getUra()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eUra*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eUra*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eUra*Scrap_Level_3;
	}
}

int NPC::getPlut()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return ePlut*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return ePlut*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return ePlut*Scrap_Level_3;
	}
}

int NPC::getNWaste()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return eNWaste*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return eNWaste*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return eNWaste*Scrap_Level_3;
	}
}

int NPC::getCXPReward()
{
	rStorage = Random(1,100);

	if ((rStorage >= 1) && (rStorage <= 40))
	{
		return cEXPReward*Scrap_Level_1;
	}

	else if ((rStorage >= 41) && (rStorage <= 75))
	{
		return cEXPReward*Scrap_Level_2;
	}

	else if ((rStorage >= 76) && (rStorage <= 100))
	{
		return cEXPReward*Scrap_Level_3;
	}
}

void NPC::setCEXP(int cxp)
{

	cEXPReward = cxp;
}

void NPC::initRewards()
{
	ds_e.rData("Ship_Data","select from", nSID);

	eXarn = ds_e.getSXC();
	eRub = ds_e.getSRC();
	eDia = ds_e.getSDiC();
	eDrac = ds_e.getSDC();
	eUra = ds_e.getSUC();
	ePlut = ds_e.getSPC();

	rStorage = Random(1,150);

	if (Ship.getSClass() == "Frigate")
	{
		rand1 = 0;
		rand2 = Random(45,120);
		rand3 = 0;
		rand4 = Random(80,460);
	}

	else if (Ship.getSClass() == "Destroyer")
	{
		rand1 = 0;
		rand2 = Random(260,480);
		rand3 = Random(8, 25);
		rand4 = Random(120,525);
	}

	else if (Ship.getSClass() == "Cruiser")
	{
		rand1 = 0;
		rand2 = Random(345,590);
		rand3 = Random(19, 36);
		rand4 = Random(245,780);
	}

	else if (Ship.getSClass() == "Battle Cruiser")
	{
		rand1 = Random(1,3);
		rand2 = Random(490,680);
		rand3 = Random(34, 75);
		rand4 = Random(470,989);
	}

	else if (Ship.getSClass() == "Battleship")
	{
		rand1 = Random(1,5);
		rand2 = Random(690,800);
		rand3 = Random(58, 120);
		rand4 = Random(525,1020);
	}

	else if (Ship.getSClass() == "Mothership")
	{
		rand1 = Random(1,6);
		rand2 = Random(745,932);
		rand3 = Random(70,145);
		rand4 = Random(635,1345);
	}

	else if (Ship.getSClass() == "Titan")
	{
		rand1 = Random(1,12);
		rand2 = Random(980,1350);
		rand3 = Random(95, 988);
		rand4 = Random(1025,4560);
	}

	if ((rStorage >= 0) && (rStorage <= 25)) //exp only
	{
		cEXPReward = rand4;
	}

	else if ((rStorage >= 26) && (rStorage <= 50)) //exp and lith
	{
		eLith = rand2;
		cEXPReward = rand4;
	}

	else if ((rStorage >= 51) && (rStorage <= 75)) //exp and nwaste
	{
		eNWaste = rand3;
		cEXPReward = rand4;
	}

	else if ((rStorage >= 76) && (rStorage <= 145)) //exp, nwaste, and lith
	{
		eLith = rand2;
		eNWaste = rand3;
		cEXPReward = rand4;
	}

	else if ((rStorage >= 146) && (rStorage <= 150)) //exp, nwaste, lith, and plat
	{
		ePlat = rand1;
		eLith = rand2;
		eNWaste = rand3;
		cEXPReward = rand4;
	}
}


int NPC::getNOWingmen()
{
	return eWingmen.size();
}

//Talirath



//Tech Merchant

