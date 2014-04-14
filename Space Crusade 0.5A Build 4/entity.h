#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "ship.h"
#include "mission.h"
#include "relation.h"
#include "data_placeholder.h"

class Game;
class Map;

using std::string;

class Entity
{
public:

	Entity();

	bool isHostile(); //Is this class hostile?

	int getDia(); //get diamonds
	int getDrac(); //get draconic
	int getXarn(); //get xarn
	int getLith(); //get lithium
	int getNWaste(); //get nuclear waste
	int getPlat(); //get platinum
	int getPlut(); //get plutonium
	int getRubies(); //get rubies
	int getUra(); //get uranium

	int getCELvl();

	string getAffil(); //Get entity affiliation

	//Set resource functions for resource changes
	void updateXarn(int xarn, string operation);
	void updateRubies(int rubies, string operation);
	void updateDia(int dia, string operation);
	void updateDrac(int drac, string operation);
	void updateLith(int lith, string operation);
	void updatePlat(int plat, string operation);
	void updateUra(int ura, string operation);
	void updatePlut(int plut, string operation);
	void updateNWaste(int nWaste, string operation);

	void updateCXPLvl(int lvl, string operation);

	void setAffil(string afil); //Set entity affiliation

	string getName(); //get name
	string getRank(); //get rank
	string getRace(); //get race
	string getDispo(); //get disposition
	string getStatus(); //get entity status

	void setName(string name);
	void setRank(string rank);
	void setRace(string race);
	void setDispo(string dispo);
	void setStatus(string estat);

	void applySDamage(float damage); //apply shield damage
	void applyADamage(float damage); //apply armor damage
	void applyHDamage(float damage); //apply hull damage

	void dSStat(); //Battle ship status
	void dPStat(); //Show ship status
	bool gOver(Game& mGame, Player& mPlayer); //game over

	int getCXPReward(); //get cexp reward

	Entity* rEntity(); //return this class

	void bAttack(bool allout, bool spread, bool wsystem, bool single, Entity& entity);

	Ship Ship; //ship

protected:
	string eName; //Entity Name
	string eRace; //Entity Race
	string eRank; //Entity Rank
	string eDispo; //Entity disposition
	string eAffil; //What group the entity is affiliated with
	string eBStatus; //Entity Battle Status (ie: Destroyed or Retreated)

	int eCXPLevel;
	
	/*
		0.6A resource plan:

		In 0.6 modding support will be added to the game.  To accomodate this large changes need to be made to resources.  Resources must be exploded out into their own
		class.  Any object that uses resources will then have a vector of resource objects that will contain a value and a name.

		For saving the vector can be placed into two '-' delimited strings, RName and RValue, and stored in the database.  This allows for custom resources to be added and used within the game.

		Make sure resource names are loaded from ini/cfg file.
	*/

	//Entity Resources
	int	eXarn;
	int eRub;
	int eDia;
	int eDrac;
	int eLith;
	int eUra;
	int ePlut;
	int ePlat;
	int eNWaste;

	float damage; //primary damage
	float damage2; //run over damage
	bool bIsHostile; //Is this entity a hostile class (any other sub-class except player)?
	int sID, sIID, iID; //Station Id for identifying station that has clones and the inventory slot they are in
};


class Player : public Entity
{
public:
	Player(); //Player constructor

	void pSetup(); //Set up the player class
		
	int getFKills(); //get frigate kills
	int getDKills(); //get destroyer kills
	int getCKills(); //get cruiser kills
	int getBCKills(); //get battle crusier kills
	int getBKills(); //get battleship kills
	int getCSKills(); //get command ship kills
	int getMKills(); //get mothership kills
	int getTKills(); //get titan kills

	void updateFKills(int kills, string operation); //update frigate kills
	void updateDKills(int kills, string operation); //update destroyer kills
	void updateCKills(int kills, string operation); //update cruiser kills
	void updateBCKills(int kills, string operation); //update battle crusier kills
	void updateBKills(int kills, string operation); //update battleship kills
	void updateCSKills(int kills, string operation); //update command ship kills
	void updateMKills(int kills, string operation); //update mothership kills
	void updateTKills(int kills, string operation); //update titan kills

	void setBOKills(int i);
	int getBOKills();

	int getCELvl(); //get combat experience level
	int getCEXP(); //Get current amount of combat exp
	int getCXPTNL(); //Get combat exp till next level

	void pCShip(); //choose starting ship
	void pCBWeap(); //choose starting ship bomb armaments 
	void pCMWeap(); //choose starting ship missile armaments
	void pCLWeap(); //choose starting ship laser armaments
	void cELUp(); //check if player combat experience meets level requiments
	void cELDown();
	int calcOCXPTNL(int cLevel); //Calculate the CEXP to next level for the previous level and then return it; for clone system
	void rUp(); //increase players rank

	//Set CEXP
	void updateCEXP(int cExp, string operation);
	void setCXPTNL(int cXPTNL);

	
	//Mission handling
	vector<Mission> pMissions; //Vector to hold player missions
	vector<Mission> pCMissions; //Player closed missions; contains missions that are completed, closed due to non-completion or outright failure
	void addMission(int mCode); //Add a mission
	void updateMission(int mCode, bool bChangeTName, string tname, bool bChangeMLSector, string mlsector, bool bChangeMLSystem, string mlsystem, bool bChangeDur, int duration); //Update a mission
	void removeMission(int mCode); //Remove a mission and add it to pCM vector
 	void getMission(int mCode); //Get mission information
	void getAMissions(); //Get all active missions w/ basic info
	void completeMission(int mCode); //Complete mission and give rewards
	void loadMission1(missionData mData);
	void loadMission2(missionData mData);


	//Relation Handling
	vector<Relation> pRelations; //Vector to hold player relationships
	void addRelation(string rName, int rAffinity); //add a new relationship
	void updateRelation(string rName, int rAffinity, string operation); //update a relationship
	int getRStatus(string rName); //get status of specific relationship
	vector<Relation> getARStatus(); //get status of all relationships
	void loadRelation(relationData rData);

	//Wingmen
	vector<Player> eWingmen;
	void addWingman(); //Create a new element in the eWingmen vector
	int getNOWingmen();

	void updateDPlanets(int dp, string operation);
	int getDPlanets();

	void setPLocale(string s);
	string getPLocale();



private:

	int pPDest; //number of destroyed planets
	int pFKills; //player frigate kills
	int pDKills; //player destroyer kills
	int pCKills; //player cruiser kills
	int pBCKills; //player battle cruiser kills
	int pBKills; //player battleship kills
	int pMKills; //player mothership kills
	int pTKills; //player titan kills
	int pCELevel; //player combat experience level
	int pCXP; //Entity CEXP
	int tNCELevel; //to next combat experience level

	int pBOKill; //To track bounty kills in the new few versions of SC

	string pLocale;
	
	int sCode; //ship code
	int wCode; //weapon code
	int i; //for for loops

	int pChoice;
	string data;
	int data2;
};

class NPC : public Entity
{
public:
	NPC(); //definiton constructor
	NPC(string name, string race, string rank, int sCode); //story/mission battle constructor

	void hSetup(int rkCode, int rCode, int sCode); //set up hostile
	
	int getDia(); //get diamonds
	int getDrac(); //get draconic
	int getXarn(); //get xarn
	int getLith(); //get lithium
	int getNWaste(); //get nuclear waste
	int getPlat(); //get platinum
	int getPlut(); //get plutonium
	int getRubies(); //get rubies
	int getUra(); //get uranium

	void setCEXP(int cxp); //Set CEXP reward for this entity

	void initRewards();

	int getCXPReward(); //get CEXP reward

	//Wingmen
	vector<NPC> eWingmen;
	int getNOWingmen();

private:

	int cEXPReward; //CEXP rewarded for destroying this hostile
	int rStorage; //storage variable for random
	int nSID; //NPC ship ID
	int rand1, rand2, rand3, rand4, rand5; //Misc randoms
};

class talirath : public Entity
{
};

class techMerchant : public Entity
{
};
#endif


/*

=============================
=Player Ranks & Requirements=
=============================

Private-
Requirements:
	None, starting rank


Private First Class-
Requirments:
	Combat Experience Level > 5
	Ship Kills:
		Frigate > 5

Unlocks:
	Weapons:
		All 6-10


Sub-Lieutenant-
Requirments:
	Combat Experience Level > 10
	Ship Kills:
		Frigate > 8
		Destoyer > 0

Unlocks:
	Weapons:
		All 11-15

	Ships:
		Destroyers


Lieutenant-
Requriment:
	Combat Experience Level > 18
	Ship Kills:
		Frigate > 14
		Destroyer > 3

Unlocks:
	Weapons:
		All 16-24


Lieutenant Commander-
Requirements:
	Combat Experience Level > 26
	Ship Kills:
		Frigate > 20
		Destroyer > 8
		Cruiser > 0

Unlocks:
	Weapons:
		All 25-28

	Ships:
		Cruisers


Commander-
Requirements:
	Combat Experience Level > 45
	Ship Kills:
		Frigate > 25
		Destroyer > 12
		Cruiser > 4

Unlocks:
	Weapons:
		All 29-38


Captain-
Requirements:
	Combat Experience Level > 62
	Ship Kills:
		Frigate > 35
		Destroyer > 18
		Cruiser > 10
		Battlecruiser > 0
		Battleship > 0

Unlocks:
	Weapons:
		All 39-45

	Ships:
		Battlecruisers
		Battleships


Commodore-
Requirements:
	Combat Experience Level > 80
	Ship Kills:
		Frigate > 50
		Destroyer > 23
		Cruiser > 18
		Battlecruiser > 8
		Battleship > 6

Unlocks:
	Weapons: 
		All 46-55


Admiral-
Requirments:
	Combat Experience Level > 102
	Ship Kills:
		Frigate > 75
		Destoyer > 38
		Cruiser > 25
		Battlecruiser > 16
		Battleship > 20
		Command Ship > 0
		Mothership > 0

Unlocks:
	Weapons:
		All 56-73

	Ships:
		Command Ships
		Motherships
		Titans

*/