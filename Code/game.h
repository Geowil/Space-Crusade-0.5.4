#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "entity.h"
#include "planet.h"
#include "station.h"
#include "data_placeholder.h"
#include "battleproc.h"
#include "map.h"

using std::string;
using std::vector;

class Game
{
public:
	Game();

	//Misc Game Functions

	//Save & Load Game Functions
	void gSave(Player& mPlayer);
	void gLoad(Player& mPlayer);


	//Planet Functions

	//Planet Generation
	void getPNames();
	void generatePlanets();
	float calcPop();
	void getDefenses(int rand, float eks);
	void getShields(int rand, float eks);
	void addDefenses(int i, float eks);
	void addShields(int i, float eks);



	bool isDest(int id); //check if planet already destroyed by player
	//bool isOwned(int id); //check if planet already counqured by player
	void fPlanets(); //find planets
	int pPlanets(Player& mPlayer); //print list of found planets

	void initPVector(); //Initialize planet vectors

	void iSPlanets(); //Init the scanned planets vector
	void rSPlanets(); //Reset scanned planets vector

	void getDList(); //get list destroyed planets
	string getDPlanet(int i); //get destroyed planet
	void setSDPlanet(int i, string name); //set specific destroyed planet (for name encryption)
	void loadPlanet(planetData plData);
	//void setPOwned(string plname); //set planet as owned by player
	//void getOPlanets(); //get list of planets owned by player

	void pMenu(Player& mPlayer, Planet* gPlanet, Game& mGame_m, string* eResult, Map& m_m, battleProc& bp_m, NPC& mNPC); //Planet interact menu
	void gPHail1(Player& mPlayer, Planet* gPlanet);
	//void gPHail2(string race, string affiliation, Player& mPlayer);
	void gFABelts(Player& mPlayer, Planet* gPlanet);


	//Station Functions

	//Station getStation(string name); //return station

	void iTStations(); //Init the scanned planets vector
	void rTStations(); //Reset scanned planets vector
	void fStations(); //Find Stations and create them if they do not exist
	int pStations(Player& mPlayer);

	void sSItem(Player& mPlayer, Station& stat_g, bool bought); //Store item in inventory
	void sGItem(Player& mPlayer, Station& stat_g); //Get an item from this station

	void createStation(string name, Player& mPlayer); //Create station reference for menu operations AND create the actual station and place it into gStations if it does not already exist

	void sMenu(Player& mPlayer, Station& stat_g); //station menu
	void sSBuyW(); //buy weapon
	void sSBuyS(); //buy ship
	void sSBuyM(); //buy mod

	void sMLoop1(Player& mPlayer, Station& stat_g); //station market loop

	//Buy market
	void sMLoop2A1(Player& mPlayer, Station& stat_g); //Start buy market
	void sWMLoopB(Player& mPlayer, Station& stat_g); //station weapon menu loop
	void sSMLoopB(Player& mPlayer, Station& stat_g); //station ship menu loop
	void sEMLoopB(Player& mPlayer, Station& stat_g); //station equipment menu loop
	void sRMLoopB(Player& mPlayer, Station& stat_g); //station resource buy menu
	void sOMLoopB(Player& mPlayer, Station& stat_g); //station ore buy menu

	//Sell market
	void sMLoop2B1(Player& mPlayer, Station& stat_g); //Start sell market
	void sMLoop3A1(Player& mPlayer, Station& stat_g); //Where is it located - non-ship
	void sMLoop3A2(Player& mPlayer, Station& stat_g); //Where is it located - ship
	void sMLoop4A(Player& mPlayer, Station& stat_g, bool ship, bool station); //Choose what to sell (non-ship)
	void sMLoop4B(Player& mPlayer, Station& stat_g, bool ship, bool station); //Choose what to sell (ship)
	
	/*
	void sWMLoopS(Player& mPlayer, Station& stat_g); //station weapon menu loop
	void sSMLoopS(Player& mPlayer, Station& stat_g); //station ship menu loop
	void sEMLoopS(Player& mPlayer, Station& stat_g); //station equipment menu loop
	void sRMLoopS(Player& mPlayer, Station& stat_g); //station resource menu loop
	*/

	void sSell(Player& mPlayer, Station& stat_g, bool bIOShip, bool bIOStation, bool bIsShip, int slot); //Sell chosen item

	void sMBClone(Player& mPlayer, Station& stat_g, int iID); //Buy clone
	void sMRefund(Player& mPlayer, Station& stat_g); //Refund a purchase as a last resort

	string getIType(); //get specific item type for special weapon stat values

	void sMPurchase(Player& mPlayer, Station& stat_g); //station market purchase
	
	void sRepair(Player& mPlayer, Station& stat_g);
	void bClone(Player& mPlayer, Station& stat_g);
	void useClone(Player& mPlayer, int sID, int sIID, int iID);
	void sShop(Player& mPlayer);
	void sMOffice(Player& mPlayer);
	void sBOffice(Player& mPlayer);
	void sEAFOffice(Player& mPlayer);
	void sPub(Player& mPlayer);
	void sCasino(Player& mPlayer);

	void sDepart(Player& mPlayer, Station& stat_g);

	void loadStation(stationData& stData);

	void startMission(Player& mPlayer);
	void completeMission(Player& mPlayer);

	void createBInfo();

	//Planet Public Vectors
	vector<Planet> gPlanets; //Generated planets
	vector<Planet> sPlanets; //scanned planets vector, max of 15 planets found at anytime
	vector<Planet> pDestPlan; //destroyed planets name vector
	//vector<Planet> oPlanets; //player owned planets


	//Station Public Vectors
	vector<Station> gStations; //Generated stations
	vector<Station> tStats; //Temp Stations used while finding stations


private:

	//Misc Game Variables

	//Save/Load Variables
	string storage1;
	string storage3;
	float storage2;
	int storage4;

	bool bDSComplete, bDLComplete; //bools: did save/load copmplete successfully?

	//Global Use
	int i,i2,i3;


	//Planet Variables

	//Randoms
	int pNRand; //Name
	float pERand; //EKS
	float pSRand; //planet size
	int pSRRand; //planet size range
	int pDRand; //Defense Point(s)
	int popRand1, popRand2, popRand3; //population randoms
	int pDisRand;
	int pAffRand;

	int pRID; //random planet id for scanning

	string tempDisp;
	string tempAffi;
	string tempRace;

	//Constants (const as in non-random)
	long long int pPMax; //planet max sustainable pop
	float pPStore; //store planet pop so we can cast to lli
	string sName; //store planet name for duplicate checking
	int nCode; //planet name code

	//Vectors
	vector<string> pNStorage; //Planet name storage

	//Bools
	bool bUPName; //bool: does planet have a non-used (unique) name
	bool bPPGen; //bool: has planet population been generated
	
	bool		replaced; //Has array element been replaced?
	int			nSPlanets; //number of scannable planets, will vary based on equipped modules in future; for now hard capped at 15
	int			nTStations; //number of scannable stations, will vary based on equipped modules in future; for now hard capped at 25
	int			nTSPID; //store id for planet whose name is used for the station
	int			nTSSV; //store random value to determine the suffix of the station name
	string		nTSSuffix; //Store the suffix here until it is ready to use

	int numODef, numOShd, rRange;

	/*
		Planet Scanning:

		Factory ships under Cruiser class can only scan a maximum of 5 planets at a time.
		Upgrades available to increase this.  Ships at or above Cruiser can scan up to 10.
		Upgrade required for the extra five slots on those ship classes.
	*/


	//Station Variables
	int			pChoice; //Player Choice
	bool		sLeave; //Leave station?
	bool		sMMenu, sMMenu2, sMMenu3, sMMenu4; //Stay at market menu?
	bool		sWMenu; //Stay at weapon menu?
	bool		sSMenu; //Stay at ship menu?
	bool		sMDMenu; //Stay at mod menu?
	int			cCode; //For ship classification
	string		cCode2; //For ship classification
	int			iCode; //To obtain information on item
	string		iType; //To determine the type of item that was purchased
	string		iType2; //To determine the specific item type
	bool		sMBuy; //Check if player decided to purchase item
	int			csPos; //for cStations position
	string			wType; //To store name of specific weapon type for weapon installation
	string			wClass; //Weapon class, used in weapon installation

	//For selling
	int amount;

	int sTCost, sPTax, sTPCost; //Store cost values for clone buying; will likely be applied to everything in future
	float sTax; //Store tax percentage for clone sales

	bool		bDASlot; //Player bought storage slot?
	bool		bDASpace; //Player bought storage space?
	bool		bDone;	//Item Store is Done?
	bool		bContinue; //For station menu looping
	bool		bRepair; //bool: Repair your ship?
	bool		bSSuccess; //bool: was storage successful?

	int			pAffin; //Store player affinity for later use
	int			sRCPPX; //cost per percentage point to repair; Xarn
	int			sRCPPR; //cost per percentage point to repair; Rubies
	int			sRCPPDi; //cost per percentage point to repair; Diamonds
	int			sRCPPD; //cost per percentage point to repair; Draconic

	bool bExchange; //bool: did player say to exchange their current ship for the new one?

	float dPerc;
	float dPerc_R;
	int   dPerc_I,dPerc_I2,dPerc_T;

	int oldCXPTNL; //For clone system

	int mID; //Hold mission ID
	bool gMStart; //Did player choose to undertake the mission?
	float xarnMultiplier;
	int xarnReward;

	string		sname;
	string		dispo;
	string		affil;
	int			stlevel;
	int			sslevel;

	vector<int> tWStorage; //Store non-compliant weapon ids here temporarily when changing ships

	//Temp storage for ship weapon vectors
	vector<hardPointL> tLBanks;
	vector<hardPointM> tMTurrets;
	vector<hardPointB> tBHolds;
	vector<hardPointR> tRMounts;
	vector<hardPointH> tHWBays;

	/*
	Tech Level & Station Level

	The technology level is the advanced state of the station.  It will determine several things:

	1. Can the station support cloning operations
	2. Can the station repair your ship
	3. Can you or how much you can store at the station
	4. Prices ontop of the multiplier
	5. What type and how many missions are available
	6. What items are sold at the station

	The list of how these break down is under development currently and is not yet finalized.

	*/

	//For Debug
	string file,line,bLocale,time,date,bTDate;
};
#endif



