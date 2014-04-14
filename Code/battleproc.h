#ifndef battleproc_H
#define battleproc_H

#include <string>
#include "entity.h"
#include "bparticipants.h"
#include "planet.h"

#include <vector>

using std::string;
using std::vector;

class battleProc
{

public:
	
	battleProc(); //constructor
	string sBLoop(Player& mPlayer, Planet* Planet, bool defenders, Game& mGame, NPC& mNPC); //battle loop for ship to ship combat
	string pBLoop(Player& mPlayer, Planet* gPlanet, Game& mGame); //battle loop for planet battles
	void bInit(Player& mPlayer, NPC& mNPC); //battle initilization
	void pInit(); //planet initilization
	void endBattle(Player& mPlayer, NPC& mNPC); //run end battle processes
	void endBattle_PB(Player& mPlayer, Planet* gPlanet);
	void resetRewards();
	void bTSetup(Player& mPlayer, bool planet, Planet* gPlanet); //initialize hostile team
	
	//Initialize hostile forces
	void initHR1(NPC& mNPC); //Rank 1
	void initHR2(NPC& mNPC); //Rank 2
	void initHR3(NPC& mNPC); //Rank 3
	void initHR4(NPC& mNPC); //Rank 4
	void initHR5(NPC& mNPC); //Rank 5
	void initHR6(NPC& mNPC); //Rank 6
	void initHR7(NPC& mNPC); //Rank 7
	void initHR8(NPC& mNPC); //Rank 8
	void initHR9(Player& mPlayer, NPC& mNPC); //Rank 9

	bool bRetreat();

	void bAParticipants(Player& mPlayer, NPC& mNPC); //Init and fill bParts vector
	void bAParticipants_PB(Player& mPlayer, Planet* gPlanet); //Init and fill bParts vector

	//Battle Participants Vector
	vector<bParticipants> battleParticipants;

	void getPTarget(NPC& mNPC); //get player to choose target
	void getPTarget_PB(Planet* gPlanet);

	void bPFSolutions(int bPChoice, Player& mPlayer, NPC& mNPC); //determine how and which weapons to fire
	void bPFSolutions_PB(int bPChoice, Player& mPlayer, Planet* gPlanet, bool shield, bool defense, bool planet); //determine how and which weapons to fire
	//void bAIFSolutions(NPC& tNPC, Player& tPlayer); //Send AI attack options to damage

	void bPHail(string race, string affiliation, Player& mPlayer); //Hail messaging system
	

	void aiHTasks(NPC& cNAttacker, Player& mPlayer); //Allow hostiles to take actions; putting this here instead of in the b. loop because it will be much more compact this way.
	void aiHTasks_PB(Defense& pDefense, Player& mPlayer); //Allow hostiles to take actions; putting this here instead of in the b. loop because it will be much more compact this way.
	void aiATasks(Player& cAAttacker, NPC& mNPC); //Allow allies to take actions; putting this here instead of in the b. loop because it will be much more compact this way.
	void aiATasks_PB(Player& cAAttacker,  Planet* gPlanet, bool shield, bool defense, bool planet); //Allow allies to take actions; putting this here instead of in the b. loop because it will be much more compact this way.

	void createBInfo();

private:

	int sCode; //For ship ID
	int rCode; //For race ID
	int wCode; //For weapon ID
	int rkCode; //For rank ID

	int i, i2, i3, i4, i5; //For for loops and other uses
	string data;

	//Ship information
	string sName;
	string sClass;
	string hRace;
	string dtype;
	int pTarget, hTarget;  //Store targets
	int sShield;
	int sArmor;
	int sHull;
	int sTLevel;
	int sMInit;
	int sWHP;
	int sLB;
	int sMT;
	int sBH;
	int sRM;
	int sHWB;
	int banks;
	int iBanks;
	int turrets;
	int iTurrets;
	int bombs;
	int iBombs;
	
	//Rewards
	int rX, rR, rD, rDi, rL, rPl, rU, rP, rNW, rCXP;
	int fK, dK, cK, bcK, bK, mK, tK;
		
	int pChoice,pChoice2;
	bool bEnd;
	bool pGOver;
	bool pWin;
	bool pContinue;
	bool pAttacked;
	bool bDPEscape;
	bool pNTarget;
	int hostiles;
	int allies;
	int hDCounter; //hostile dead counter
	int battleSize; //variable for random during enemy team size selection
	int bPParticipants; //number of player ships
	int bHParticipants; //number of hostile ships
	int bTParticipants; //total number of ships
	
	//sorting variables
	bParticipants storage1, storage2;
	
	//attack type flags
	bool allout, spread, wsystem, single;
	
	//Attack order vriables for battleLoop
	int cAttacker, cTarget;
	string fCAttacker, fCTarget;
	bool bIsCAHostile, bIsCTHostile;
	
	bool bFight; //Chosen to fight in battle
	bool bEMenu; //bool: exit menu? t/f; for menu loops
	
	string wtype;
	
	string hResponse; //hail response
	
	int hNIBattle; //hostiles not in battle
	
	int bRChance;
	
	int pTChoice; //To keep track of player target throughout the damage process so that the entity can be reapplied to the vector
	int hTChoice; //To keep track of hostile target throughout the damage process so that the entity can be reapllied to the vector
	
	//For AI battle detection
	bool bIsPTFighting; //bool: Is Player Team Fighting?
	bool bIsHTFighting; //bool: Is NPC Team Fighitng?
	
	//For Hailing System
	int tAffinity; //Target Affinity
	bool bTResponded; //bool: Did the target respond?
	
	//Prebattle checks
	bool bBStarted; //bool: has the battle started?
	bool bDTSurrender; //bool: did the target surrender?
	bool bDTTrade; //bool: did the target agree to trade?
	bool bITNHostile; //bool: is target non-hostile?
	
	//For AI
	int bAITask1; //Int storage for random value for AI
	int bAITask2; //Int storage for random value for AI
	int bAITask3; //Int storage for random value for AI
	int bAITask4; //Int storage for random value for AI
	int bAITask5; //Int storage for random value for AI
	double bHPPerc1; //Store percent of total hull points remaining for AI task calculation; attacker
	double bHPPerc2; //Store percent of total hull points remaining for AI task calculation; target
	
	int rArray[9]; //Hold values for ransom
	
	
	//Variables for planet battle
	bool bPDBattle; //bool: does the planet enter direct battle with player?
	int pBAShields; //How many active shields does the planet have?
	
	bool bPHShield; //bool: does the planet have a shield? (for damage processing)
	bool bPTIDefense; //bool: is the player target a defensive structure? (for damage processing)
	
	int pBPSTarget, aBPSTarget; //Shield target if the planet has a shield installed and operational
	int pBPDTarget, aBPDTarget; //Defensive structure target
	
	bool bPBattle; //bool: planet battle (t/f)
	
	//For Debug
	string file,line,bLocale,time,date,bTDate;
	
	string bpResult;
};
#endif