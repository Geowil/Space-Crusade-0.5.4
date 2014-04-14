/*FILE HEADER

File Name:

datasystem.h

File Description:

This class is used to interact and obtain data from the database class.  This class acts as a buffer to get the specific data needed.

How it Works:

Functions are called that will try to obtain specific types of data for specific elements.  The neccessary information is sent to the database
class and then when the data is retrieved it is loaded into a vector reference from this class.  That vector is then searched for the information
needed.

Since this class is instance-based the vector must only be created when first accessing this class, all subsequent calls to the class will be when
the class already has the information.  Unless new data is needed refilling the vector is not neccessary.

Created On:

Sunday, April 24, 2011

Version:

1.0 - 04/24/2011
1.1 - 04/25/2011
1.2 - 04/28/2011
1.3 - 05/23/2011
1.4 - 05/24/2011
1.5 - 05/30/2011
1.6 - 07/13/2011
1.7 - 07/19/2011
1.8 - 07/23/2011
1.9 - 08/04/2011
1.10 - 08/10/2011
1.11 - 08/13/2011
1.12 - 09/28/2011
1.13 - 10/19/2011
1.14 - 10/23/2011
1.15 - 02/13/2012
1.16 - 02/14/2012
1.17 - 02/15/2012
1.18 - 02/16/2012
1.19 - 02/18/2012
1.20 - 06/20/2012
1.21 - 06/22/2012
1.22 - 06/28/2012
1.23 - 08/20/2012
1.24 - 08/23/2012
1.25 - 12/26/2012
1.26 - 12/28/2012
1.27 - 01/01/2013
1.28 - 02/05/2013
1.29 - 04/30/2013
1.30 - 06/28/2013
1.31 - 07/01/2013
1.32 - 10/

Changes:

1.0:
-Created the class

1.1:
-Fixed and changed several item descriptions
-Updated the stats of several ships

1.2:
-Fixed and changed several item descriptions
-Updated the stats of several ships

1.3:
-Fixed and changed several item descriptions
-Updated the stats of several ships

1.4:
-Fixed and changed several item descriptions
-Updated the stats of several ships

1.5:
-Fixed and changed several item descriptions
-Updated the stats of several ships
-Added getSName, getSShield, getSArmor, and getSHull

1.6:
-Finished recoding the ship database; replaced 2,425 lines of code with 43

1.7:
-Began work on laserDB matrix
-Fixed and changed several item descriptions
-Updated the stats of several lasers

1.8:
-Fixed and changed several item descriptions
-Updated the stats of several lasers
-Finished laserDB

1.9:
-Began work on missileDB matrix
-Fixed and changed several item descriptions
-Updated the stats of several missiles

1.10:
-Fixed and changed several item descriptions
-Updated the stats of several missiles

1.11:
-Fixed and changed several item descriptions
-Updated the stats of several missiles
-Added Hellstorm Missile

1.12:
-Fixed and changed several item descriptions
-Updated the stats of several missiles
-Finished codeing the missileDB; replaced 4500 lines of code with 74

1.13:
-Started and finished recoding bombDB; replaced 1279 lines of code with 27
-Added a bomb hold to the Rifter design
-Added 'get' functions for obtaining weapon information

1.14:
-Added a missile turret to the Osprey design
-Added 'get' functions for some of the bomb and missile wepaon data

1.15:
-Remade the weapon data martices so that they could be combined into one large weaponDB matrix
-Rewrote all weapon 'get' functions and removed any that were dupicates that were no longer needed
-Added weapon type and weapon damage type fields to the weaponDB matrix along with the functions to get those fields
-Removed optimum range damage from the weapon information as optimum strike damage will be done through calculations

1.16:
-Added new functions to return other ship related data

1.17:
-Added new functions to return other ship related data

1.18:
-Renamed the class to datasystem since all data is now being stored in this class and not just items
-Added planetNames, ranks, raceNames, and pDD arrays
-Coded previously added functions

1.19:
-Added getRace function

1.20:
-Removed all xCode2 = xCode - 1 and replaced these statements with [xCode-1] to cut down on code excess; removed 45 lines of code
-Added class field to shipDB, it was missing
-Added getWClass and doesCMatch functions
-Found problem with Xarn return, lead to noticing that there were many structural problems with the function calls and weaponDB; fixed those

1.21:
-Added getWDesc function

1.22:
-Started adding data casts to function calls so I can remove them from other classes
-Added data, data2 variables for casting

1.23:
-Added data casts to the rest of the functions

1.24:
-Began adding weapon classes to weaponDB, it was missing here as well
-Fixed a mistke I made earlier this month when I changed getWClass to return an integer, fixed it so that it correctly returns a string

1.25:
-Added station names array

1.26:
-Changed mission time limit to days instead of miliseconds
-Added missionDB

1.27:
-Added all of the functions to return mission data
-Added new fields to the missionDB for rewards and also converted any numbered "null" fields to -1

1.28:
-Removed periods from end of descriptions
-Found more problems, structurally, with the class' 'get' functions and the matrices; got the class working properly

1.29:
-Made some major cosmetic changes, partitioned off the matrices by class type and included the IDs around the array lines per ship for easier indentification
-Fixed major issue, class and class requirement fields were not actually what they were supposed to be; fixed all of them
-Removed planetDisposition, rank, and race arrays and replaced then with enums for easier use with switches
-Added new functions to return the enums
-Fixed several ship and weapons that were still missing the correct class field.

1.30:
-Added new function that will get pNames and send them to array in Game

1.31:
-Removed shipDB, weaponDB, and missionDB from the class.  This information is now going to be stored in external databases
-While adding data to the databases I found many major issues that would have cuased crashes, bugs, or other issues with appx. 25 items
-Changed ship armor, shield, and hull values are now represented by floats in the database

*/

#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <string>
#include "data_placeholder.h"
#include "hardPoint.h"
#include "sinv.h"
#include "defenses.h"
#include "mission.h"
#include "relation.h"
#include "ship2.h"
#include "asteroid.h"
#include "abelt.h"

class Game;
class Station;
class Planet;
class Entity;
class Player;
class NPC;


using std::string;

class dataSystem
{

public:

	//Ship Data Search
	string getSName(); //get ship name
	string getSDesc(); //get ship description
	string getSClass(); //get ship class
	float getSShield(); //get ship shield
	float getSArmor(); //get ship armor
	float getSHull(); //get ship hull
	int getSWHP(); //get ship weapon hardpoints
	int getSLB(); //get ship laser banks
	int getSMT(); //get ship missile turrets
	int getSRM(); //get ship rail mounts
	int getSHWB(); //get ship heavy weapon bays
	int getSBH(); //get ship bomb holds
	int getSMInit(); //get ship movement initiative
	float getSSG2(); //get ship space
	float getSCargo(); //get ship cargo size
	int getSTLevel(); //get ship technology level
	int getSXC(); //get ship xarn cost
	int getSRC(); //get ship ruby cost
	int getSDC(); //get ship draconic cost
	int getSDiC(); //get ship diamond cost
	int getSUC(); //get ship uranium cost
	int getSPC(); //get ship plutonium cost
	
	//Weapon Data Search
	int getWID(); //get weapon ID
	string getWName(); //get weapon name
	string getWDesc(); //get weapon description
	float getWDRLow(); //get weapon damage range low
	float getWDRHigh(); //get weapon damage range high
	float getWWeight(); //get weapon weight
	int getWAMin(); //get weapon accuracy minimum (min. target distance)
	int getWAOMin(); //get weapon optimum accuracy low (min. opt. target distance)
	int getWAOMax(); //get weapon optimum accuracy high (max. opt. target distance)
	int getWAMax(); //get weapon accuracy maximum (max. target distance)
	int getWTLevel(); //get weapon tech level
	string getWClass(); //get weapon class
	float getWSG2(); //get weapon space
	int getWMCLength(); //get mining cycle length
	float getWMCAmount(); //get amount of ore mined per cycle
	int getWXC(); //get weapon xarn cost
	int getWRC(); //get weapon ruby cost
	int getWDiC(); //get weapon diamond cost
	int getWDC(); //get weapon draconic cost
	int getWLC(); //get weapon lithium cost
	int getWUC(); //get weapon uranium cost
	int getWPC(); //get weapon plutonium cost
	int getWNWC(); //weapon nuclear waste cost
	string getWType(); //get weapon type
	string getWDType(); //get weapon damage type
	
	//Mission Data Search
	int getMisID(); //get mission id
	string getMName(); //get mission name
	string getMDesc(); //get mission description
	int getMCBEReq(); //get mission CBE level req
	string getMSCReq(); //get mission ship class req
	string getMMWReq(); //get mission equipment req
	int getMTLimit(); //get mission time limit
	string getMDiff(); //get mission difficulty
	string getMSector(); //get mission sector
	string getMSystem(); //get mission system
	string getMTName(); //get mission target name
	string getMTSClass(); //get mission target ship class
	int getMBounty(); //get mission bounty
	string getMType(); //get mission type
	
	//Mission Reward Return Functions
	int getMXR(); //Xarn
	int getMRR(); //Ruby 
	int getMDiR(); //Diamond
	int getMDR(); //Draconic
	int getMLR(); //Lithium
	int getMPlR(); //Platinum
	int getMUR(); //Uranium
	int getMPR(); //Plutonium
	int getMNWR(); //N. Waste
	int getMEXPR(); //EXP
	string getMIR(); //item
	

	//Planet Data Search Functions
	//void dADPlanet();
	//void dAIPlanet();
	//void dACStation();
	string getPName(int pCode); //planet array debugging
	void getPNames(vector<string>& names);

	//Entity Data Search Functions
	string getERace();
	string getERank();

	//Get Message Data
	string getMsg();

	bool doesCMatch(int cCode, int iCode, string iType); //Does required class match item class?


	//Get Equipment Data

	int getEID(); //get equipment id
	string getEName(); //get equipment name
	string getEDesc(); //get equipment description
	string getEType(); //get equipment type
	string getEClass(); //get equipment class
	int getETLevel(); //get equipment tech level
	float getESP(); //get equipment s points
	float getESMP(); //get equipment max s points
	float getESPR(); //get equipment shield regen
	string getEDType(); //get equipment damage type
	float getEMDmg(); //get equipment min damage
	float getEMxDmg(); //get equipment max damage
	int getERng(); //get equipment range
	float getESG2(); //get equip space
	int getEXC(); //get equipment xarn cost
	int getERC(); //get equipment ruby cost
	int getEDiC(); //get equipment diamond cost
	int getEDC(); //get equipment drac cost
	int getELC(); //get equipment lithium cost
	int getEUC(); //get equipment ura cost
	int getEPC(); //get equipment plut cost
	int getENWC(); //get equipment nwaste cost
	string getEEffect(); //get equipment effect
	int getECXP(); //get equipment cxp reward

	//Get Name
	string getRName();

	//Resource Data
	string getResName();
	string getResDesc();
	string getResType();
	float getResSG2();
	int getResXCost();

	//Ore Data
	string getOName();
	string getODesc();
	string getOType();
	float getOSG2();
	int getOStage();
	float getOBSize();
	string getOResource();
	string getOOre();
	float getORUnits();
	int getORProduced();
	int getORCost();
	float getORPLoss();
	int getOXCost();

	//Retrieve Data
	void rData(string table, string operation, int ID);

	//Save Functions

	//Loading
	bool lData(Player& mPlayer, Game* mGame); //Load save data


	//Saving
	bool sData(Player& mPlayer, Game* mGame); //Create new save data

	//For debug
	void problems(string operation);

	//Misc
	int getFlag(string fName); //Return the value of the passed flag
	


private:
	int			i,i2,i3; //For For Loops
	string		data,data3; //For casting
	int			data2; //For casting
	int			wTID; //Weapon type ID

	int lastABID, lastAID; //Last ID for asteroid belts and asteroids for ID congruency between planets

	bool bErrors; //bool: errors were present during operations
	int bECount; //Number of errors thrown

	//Data temp storage
	vector<ship> ships;
	vector<weapon> weapons;
	vector<mission> missions;
	vector<diplomacy> dispositions;
	vector<planetName> pNames;
	vector<ranks> rank;
	vector<race> races;
	vector<message> messages;
	vector<equips> equipment;
	vector<name> names;
	vector<resource> resources;
	vector<ore> ores;

	//Save/Load Vectors
	vector<playerData> pData;
	vector<pShip> plShip;
	vector<pSSpread> plSSpreads;
	vector<pSHPVect> plSHPVectors;
	vector<pSInv> plSCargo;
	vector<pWingmenData> pWMData;
	vector<pWShip> pWMSData;
	vector<pWSSpread> pWMSSpreads;
	vector<pWSHPVect> pWMSHPVectors;
	vector<stationData> stData;
	vector<sPInv> sPInventory;
	vector<planetData> plData;
	vector<pDefData> plDData;
	vector<pSData> plSData;
	vector<pABelts> belts;
	vector<pABRoids> roids;
	vector<missionData> pMData;
	vector<relationData> pRData;
	vector<saveFlag> saveFlags;

	//Misc
	vector<hardPoint> tempHP;
	vector<hardPointL> tempLWV;
	vector<hardPointM> tempMWV;
	vector<hardPointB> tempBWV;
	vector<hardPointR> tempRWV;
	vector<hardPointH> tempHWV;
	vector<sInv> tempInv;
	vector<Defense> tempDData;
	vector<Shield> tempSData;
	vector<aBelt> tempBelts;
	vector<Asteroid> tempRoids;
	vector<Mission> tempMis1;
	vector<Mission> tempMis2;
	vector<Relation> tempR;

	Ship2 tShip;
	Ship2 tempShip;

};
#endif