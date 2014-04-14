#ifndef msgproc_H
#define msgproc_H

#include <iostream>
#include <string>
#include <vector>

#include "entity.h"
#include "bentity.h"
#include "weapon.h"
#include "mission.h"
#include "station.h"
#include "game.h"

using std::string;
using std::vector;

class Planet;

class msgProc
{
public:
	msgProc();

	//Game Menus
	int gTMenu(); //title menu
	bool cClone(int* sID, int* sIID, Game& mGame); //Check for clones
	void gOver();

	//Player Menus
	int pCMenu1(); //player creation menu 1
	int pCMenu2(); //player creation menu 2
	int pCMenu3(); //player creation menu 3
	int pCMenu4(); //player creation menu 4
	void pInfo(Player& mPlayer, Game& mGame); //Player information

	//Battle Menus
	int bMenu1(); //battle menu 1
	int bMenu1A(); //battle menu 1
	int bMenu1B(int hostiles);
	int bMenu1B_PB1();
	int bMenu1B_PB3(int hostiles);
	int bMenu2(); //battle menu 2
	int bMenu2_PB(); //battle menu 2 - PB
	int bPBMenu(); //bombing menu
	void pBAStatus(Player& mPlayer, int allies); //player ally battle status
	void pBStatus(Player& mPlayer); //player battle status
	int hBStatus(NPC& mNPC, int hostiles); //hostile battle status (multiple)
	void hBStatus(NPC& target); //hostile battle status (single)
	int hBStatus_PB(Planet* gPlanet); //hostile battle status (multiple)
	void hBSStatus_PB(Planet* gPlanet, bool shield, int sID, bool defense, int dID, bool planet); //All purpose information display; single target
	int bCSpread(int sWSpreads, Player& mPlayer); //Battle choose weapon spread
	int bCWSystem(Player& mPlayer); //Battle choose weapon system
	int bCWeapon(Player& mPlayer, string* wtype); //Battle choose single weapon
	int bCBomb(Player& mPlayer, string* wtype); //Battle choose bomb
	bool bHail1(string affiliation, string race, int affinity);
	int bHail2(int affinity);
	bool bHail3(int affinity, int pChoice, string race, string affil);
	bool bNHail1(); //Ask player to accept or deny npc hail
	bool bNHDemand(); //NPC demands surrender
	bool bNHSurrender(); //NPC surrenders to player
	void bHInfo(int affinity, string race);
	void bHEnemies(string race);
	void bHSurrender(int affinity, string race); //TODO: create a third parameter to determine enemy strength to also be considered for surrender or not
	int bPSurrender(int ransom[]); //Display ransom that player must pay
	int bHTrade(); //Figure out what will be required for this; might have to wait for station merge for inventories
	void bHNothing();
	void bEMiss_PD(Defense& pDefense);
	void bRewards(Player& mPlayer, int rX, int rR, int rDi, int rD, int rL, int rPl, int rU, int rP, int rNW, int rCXP, int fK, int dK, int cK, int bcK, int bK, int mK, int tK, bool planet);

	//Damage Output
	void dDamage1S(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - shield
	void dDamage1SA(float dam1, float dam2, bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - shield to armor
	void dDamage1A(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - armor
	void dDamage1AH(float dam1, float dam2, bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - armor to hull
	void dDamage1H(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - hull
	void dDamage1H_K(bEntity& bAttacker, bEntity& bTarget, bool defense); //Damage against ship - hull - ship destroyed

	void dDamage2S(float dam, bEntity& bAttacker, bEntity& bTarget, Planet* planet); //Damage against planet - shield
	void dDamage2D(float dam, bEntity& bAttacker, bEntity& bTarget, Planet* planet); //Damage against planet - defense
	void dDamage2D_K(bEntity& bAttacker, bEntity& bTarget, Planet* planet); //Damage against planet - defense - destroyed
	void dDamage2P(float dam, bEntity& bAttacker, bEntity& bTarget); //Damage against planet
	void dDamage2P_K(bEntity& bAttacker, bEntity& bTarget); //Damage against planet - all pop killed

	void dPSDisabled(Planet* planet, bEntity& bTarget, int turns); //notify if planetary shield collapses and is disabled for a number of turns
	void dSDInflicted(bEntity& bAttacker, bEntity& bTarget, string dType, int turns); //Notify when a secondary turn based damage has been inflicted
	void dBonus(float dam1, float dam2, string dType, bEntity& bAttacker); //Alert of increased damage due to bonuses
	void dSDisabled(bEntity& bTarget, int truns); //bTarget ship disabled for turns
	void dSSDisabled(bEntity& bTarget, int turns); //bTarget shields disabled for turns

	void dSDamageS(float dam, string dType, bEntity& bTarget); //Secondary damage - shield
	void dSDamageSA(float dam1, float dam2,  string dType, bEntity& bTarget); //Secondary damage - shield to armor
	void dSDamageA(float dam, string dType, bEntity& bTarget); //Secondary damage - armor
	void dSDamageAH(float dam1, float dam2,  string dType, bEntity& bTarget); //Secondary damage - armor to hull
	void dSDamageH(float dam, string dType, bEntity& bTarget); //Secondary damage - hull


	//Nav Menus
	int nMenu1(); //navigation menu 1
	int gGTPlanet(vector<Planet> planets, Player& mPlayer);
	int gGTStation(vector<Station> tStats, Player& mPlayer, Game* mGame);
	//int nMenu2(); //navigation menu 2
	void nBSPos(Player& mPlayer, NPC& mNPC); //Navigation battle ship positions
	void mTPos(Player& mPlayer, Asteroid roid); //Navigation battle ship positions

	//Station menus
	int sMMenu(Station& stat); //station main menu
	int sMBS(); //station buy/sell menu
	int sMMenu1A(); //market menu - buy
	int sMMenu1B1(); //market menu sell - choose the item type
	int sMMenu1B2(); //market menu sell - indicate the location of item
	int sMMenu1C1(Player& mPlayer, string iType); //Display items in cargohold
	int sMMenu1C2(Station& stat_g, string iType); //Display items in station inventory
	int mSSIAmount(int amount);
	int mSSIConfirm(int amount, int iID, string iType);
	int mSTIConfirm(int amount, int iID, string iType);
	int sMCMenu(Player& mPlayer); //market classification menu
	int sMMenu2(); //market weapons menu
	int sWLMenu(int cCode); //market laser weapons menu - frigates
	int sWMMenu(int cCode); //market missile weapons menu
	int sWBMenu(int cCode); //market bomb weapons menu
	int sWHMenu(int cCode); //market heavy weapons menu
	int sWRMenu(int cCode); //market railgun weapons menu
	int sMMenu8(int cCode); //market ships menu
	int sMMenu9(int cCode); //market mods menu
	int sISItem(); //Install or Store Item?
	int sBSShip(); //Board or Store ship?
	int sKVEquipment(); //Keep valid eqipment installed?
	bool sMIInfo(int iCode, string iType, string iType2, Player& mPlayer, Station& stat, int amount); //Return item info and determine if user can/will buy; if so return true for further processing.
	void sGSData(); //get ship data
	void sGWData(); //get weapon data
	void sGMData(); //get module data
	int sRMenu1(); //repair menu 1
	int sRMenu2(); //repair menu 2
	int sBMenu1(); //bar menu 1
	int sBMenu2(); //bar menu 2
	int sEAOMenu1(); //EA office menu 1
	int sEAOMenu2(); //EA office menu 2
	int sEAOMenu3(); //EA office menu 3
	float sBISPMenu(float cSpace, float mSpace, float nSpace, Player& mPlayer); //add inv space menu
	int sBClone(); //Buy a clone
	int sMOMenu1();
	int sMOMenu2(int* mID, Player& mPlayer);
	int sMOMenu3(Player& mPlayer);
	int sBOMenu1();
	int sBOMenu2(int* mID, Player& mPlayer);
	int sBOMenu3(Player& mPlayer);
	int sEAFOMenu1();
	int sEAFOMenu2(int* mID, Player& mPlayer);
	int sEAFOMenu3(Player& mPlayer);
	bool sSMission(int mID);

	int sInv(Station& stat);
	int sInv_S(Station& stat);

	int sMBRes(); //What resource to buy
	int sMBOre(); //What ore to buy
	int sMBAmount(int iCode, string type, Player& mPlayer, Station& stat); //Select the amount of items to buy
	
	int sMSI1(); //Have the player choose where the item they want to move is coming from
	int sMSI2(); //Have player choose what type of item they want to store
	int sMSI3A(Player& mPlayer); //Choose a stored ship from player ship to store in station
	int sMSI3B(Station* stat); //Choose a stored ship from station to store in ship cargo hold
	int sMSI4A(Station* stat); //Choose an item from station storage to move to ship
	int sMSI4B(Ship* ship); //Choose an item from the ship to store on a station

	bool sMECShip(); //Ask player if they want to exchange their ship for one just bought


	int sDRMenu1(Player& mPlayer);
	bool sDRMenu2(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost);
	bool sDRMenu3(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost);
	bool sDRMenu4(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost);

	//Misc Functions
	string mRMessage(int mCode); //Return message
	void mCScreen(bool pause); //Clear screen + pause

	//Mission Info Functions
	void mInfo(Mission* m, bool bCInfo); //Basic Mission Info

	//Planet Menus
	int plMenu1();
	int gGTABelt(Planet* gPlanet);
	
	//Ship Menus
	int sWSSelection(int lasers, int missiles, int rails, int heavies); //weapon system selection
	char sLWSelection(Laser* weapon); //laser weapon selection
	char sMWSelection(Missile* weapon); //missile weapon selection
	char sRWSelection(Rail* weapon); //rail gun selection
	char sHWSelection(Heavy* weapon); //heavy weapon selection
	char sBWSelection(Bomb* weapon); //bomb weapon selection
	int sSCMenu(); //Weapon Spread Center
	int sDSpread(int sWSpreads, Player& mPlayer); //Delete weapon spread
	int	sCWSpread(); //Create a weapon spread
	int sCEWSpread(int sWSpreads, Player& mPlayer); //Choose empty weapon spread
	char sOWSpread(Player& mPlayer); //Overwrite weapon spread?
	int sMSystem(int sAMInit); //Movement system menu - battle
	int sMSystem2(int sAMInit); //Movement system menu - mining

	//Defenses
	void sSEnabled(Planet* planet, string sname);

	//Mining
	int mMenu1();
	int mMenu2();
	int mCTarget(vector<Asteroid> roids, vector<int> scanned, Player& mPlayer, int mTDist);
	int mGRPoint(vector<int> scanned, vector<Asteroid> roids, Player& mPlayer);
	void mMLInfo(int ctime, int tdist, float mopc);

private:
	int i; //For incrementing For loops
	int i2; //For additional For Loop tracking
	int pChoice, pChoice2; //For returning player menu choices
	char pCChoice; //For player choices; characters
	int dLastValue; //For moving around weapons lists
	bool bContinue; //For market scrolling
	bool bValid; //For menu looping for valid choices where needed
	int totalWeapons, laser, missile, bomb, rail, heavy;
	string type;
	int sCRand,mRand; //Randoms

	float dPerc;
	float dPerc_R;
	int   dPerc_I,dPerc_I2;

	bool bErrors;
	int rCount;

	int pSStat; //Player selected station

	string wName;
	string iType;
	string dbTable;
	int iID;

	int hSRate; //Store random value to determine success or failure for hailing

	bool bCReturn; //bool: Can return a value?
	bool bNTarget; //bool: no target selected yet?
	bool bIsTDest; //bool: is target destroyed?

	//For selling
	int pSCSize, sISize, sSSize, nOShips;

	vector<hardPoint> tempSpread; //Temp spread storage

	//Information Output Variables

	//Player/Wingmen
	string pname;
	string prank;
	string psname;
	string psclass;
	float pssp;
	float psap;
	float pshp;
	float psmsp;
	float psmap;
	float psmhp;
	int psdt;
	string psstatus;

	//NPC/Wingmen
	string hname;
	string hrank;
	string hsname;
	string hsclass;
	float hssp;
	float hsap;
	float hshp;
	float hsmsp;
	float hsmap;
	float hsmhp;
	int hsdt;
	string hsstatus;

	//Planetary Shield
	string mname;
	int mtlevel;
	float msp;
	float mmsp;
	float spr;
	bool mstat;
	string mstats;
	int dtimer;

	//Planetary Defenses
	string dname;
	int dtlevel;
	float dsp;
	float dmsp;
	string dstat;

	//Planet
	string plname;
	float peks;
	float plsize;
	int ndef;
	int nshd;
	float ppop;
	float pmpop;

	//Station Cost Variables
	int xCost;
	int rCost;
	int diCost;
	int dCost;
	int lCost;
	int plaCost;
	int uCost;
	int pluCost;
	int nwCost;
	float sCMulti;
	float sTBuy; //Space to buy

	//For Mining
	int tDist; //Target distance
	int tRoids; //Targetable roids; for checking if there are any roids the player can target
};
#endif