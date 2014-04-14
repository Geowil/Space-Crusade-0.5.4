#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>
#include "weapon.h"
#include "defenses.h"
#include "entity.h"
#include "abelt.h"

using std::string;
using std::vector;

class Planet
{
public:
	Planet();  //constructor
	Planet(int id, string name, string dispo, string affil, string race); //constructor 2
	Planet(int id, string name, string dispo, string affil, string race, float eks, long long int pop); //constructor 3
	
	Planet* getPlanet(); //Return this
	
	void addPDefenses(bool defense, int did, bool shield, int mid, bool defender); //Initailize planetray defenses

	string getName(); //Get planet name
	string getAffil(); //Get planet affiliation
	string getDispo(); //get planet disposition
	string getStatus(); //get planet status
	string getRace();
	long long int getPop(); //Get planet population
	string getPopS();
	long long int getMPop(); //Get planet max population
	string getMPopS();
	float getSize(); //Ger planet size
	float getEKS(); //Get EKS rating
	int getPID(); //Get planet ID

	void createBelts();
	void addBelt(string name, float size, int ramount, bool full); //Load a saved asteroid belt

	bool bPIsDest();
	//bool bPIsPOwned();

	void setPID(int id);
	void setName(string name);
	void updatePop(long long int pop, string operation);
	void updateMPop(long long int pop, string operation);
	void setSize(float size);
	void setEKS(float eks);
	void setAffil(string affil);
	void setDispo(string dispo);
	void setPDest(int i);
	void setPPOwned(int i);
	void setStatus (string s); //set planet status
	void setRace(string s);

	void pillagePlanet(int* rX, int* rR, int* rDi, int* rD, int* rL, int* rPl, int* rU, int* rP, int* rNW);

	void setTDist(int dist);
	int getTDist();

	//Defenses
	vector<Defense> pDef; //planetary defense vector
	vector<Shield> pShd; //planetary shield vector
	vector<NPC> pDefenders; //planetary defense ships

	//A. Belts
	vector<aBelt> belts;


private:

	int plID; //Planet ID
	string plName; //planet name
	string plDispo; //Planet Disposition
	string plAffil; //Planet Affiliation
	string plRace;
	float pEKS; //planet enhanced kardasev scale value
	float pSize; //planet size, determines the total population possible
	long long int pPop,pMPop; //planet population/max population
	bool bIsPOwned; //bool: is this planet owned by the player?
	bool bIsDest; //bool: is this planet destroyed (has it been attacked and laid barren)?
	string pStatus; //Planet status, for battle processing

	string name;
	int ramount;
	float size;
	bool full;

	int i; //For for loops

	int pTDist; //Store the distance needed to travel to reach this planet; for calculating if a ship is encountered
	
	string trailer,sStorage,sPPop,sPMPop; //Strings for simplified planet population returns
	float popStorage;

	int beltRand; //Rand for belt creation


	/*
	Livability Variables

	These variables control how fast a population will grow based on the planets enviornment.
	Variables will include level of biodiversity, level of atmosphere, landmass, water, breathable gasses present,
	gravity, and radiation.  Each will have an effect on the rate of population growth for a conqured planet.  Teraforming
	can be done on most planets to bring them closer to the habitable zone for Humans, at a price.
	*/

	/*
	float pGrav; //planet gravity
	float pRad; //yearly planetary radiation
	float pOxy; //oxygen composition of atmosphere
	float pNit; //nitrogen composition of atmosphere
	float pCarb; //carbon composition of atmosphere
	float pHel; //helum composition of atmosphere
	float pALevel; //planet atmosphere thickness
	float pLMass; //precentage of landmass
	float pWMass; //precentage of watermass
	float pBDivers; //level if ecological diversity
	float pM<insert resource type>; //TODO: add in mineral desposite values for mining
	*/
	
	/*float pRFProduction; //How many units of foor are produced per turn
	float pRFConsumption; //How many units of food are consumed per turn
	float pRFSupply; //How much food the planet current has available
	float pRWProduction; //How many units of water are produced per turn
	float pRWConsumption; //How many units of water are consumed per turn
	float pRWSupply; //How much drinkable water the planet currently has availalble*/
};
#endif


	/*============================
	  ==Enhanced Kardashev Scale==
	  ============================

	  0-0.9 = Class 0
	  
	  Clas 0 planets are planets with a low tecnological advancment, low amounts
	  of resources can be found but the more exotic resources will not be present.  These
	  planets, when conqured, do not produce much income, resources when mines,
	  or forces.  They are generally small and varying in habitiablity, many have
	  little to no population and need some level of terraforming to sustain a stable
	  population.


	  1-1.9 = Class 1
	  
	  Class 1 planets are more advanced then 0's, but not by much.  Slightly higher technological level than
	  21st Century Earth.  Less exotic resources can be plentiful and even some exotic resources can be found in quantity on these
	  planets.  Generally great planets for colonization, they will produce stable, yet small, income streams and can support moderate
	  levels of population, leading to increased troop output.

	  
	  2-2.9 = Class 2

	  Class 2 planets are kind of in the middle between very profitable planets and very unprofitable.  They can go either way however
	  they usually have large amounts of resources on the surface.  Exotics in lesser quanities but still present.  Will provide with a,
	  moderate, yet unstable, stream of income and troops.  Planetary defenses of these planet classes start to pick up some bite.


	  3-3.9 = Class 3

	  Class 3 planets are of average technological level for the current age.  Many resource types can be found in abundance and the exotics
	  are more common on these worlds.  Populations on these worlds are large and can be highly advanced.  Planetary defenses will present
	  unprepared attackers with significant trouble.  These planets will provide a stead stream of income, resources, and troops.  Terraforming
	  will have less effect on these worlds.


	  4-4.9 = Class 4
	  
	  Class 4 planets are above average in technological advancement.  64th century Earth was of this class.  Class 4's have significant populations
	  and are more advanced then Class 3's.  Defenses can be quite powerful and will block most raiders and pirates from doing any damage; they usually combine
	  offensive towers with a shield matrix.  These planets present a large source of income, both in Xarn and resources.  They can support huge populations and are
	  good worlds to use for troop recruitment.


	  4.9<  = Class 5

	  Class 5 planets are the most highly advanced planets in the galaxy.  As there is no Class 6 defined as of yet these planets can be impregnable to anything but large fleets.
	  These planets can sustain massive populations and will provide the rulers with a large stream of income and resources.  Due to populations sizes, population growth will be
	  limited so over recruiting can lead to a large population die off or even extinction.  Terraforming has no effect on these worlds.
	 
	 Planet class will be determined by randomization of a number between 1 and 5,500.

	 1-1999 = Class 1
	 2000-2999 = Class 2
	 3000-3999 = Class 3
	 4000-4999 = Class 4
	 5000-5500 = Class 5

	 */