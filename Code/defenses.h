#ifndef DEFENSES_H
#define DEFENSES_H

#include <string>
#include <vector>
#include "range.h"
#include "tDamage.h"

using std::string;
using std::vector;

//Temporary
class Planet;

class Defense
{
public:
	Defense(); //defense contructor

	Defense* rDefense();

	void updateSPoints(float sp, string operation); //set structural points

	float getSPoints(); //get structural points
	float getMSPoints(); //get max SP
	
	int getID(); //Get defense ID
	string getState(); //Get state of defense
	void setState(string s);

	int getDDRLow(); //get weapon damage range low
	int getDDRHigh(); //get weapon damage range high
	int getDDROLow(); //get weapon damage range optimum low
	int getDDROHigh(); // get weapon damage range optimum high
	int getDALow(); //get weapon accuracy range low
	int getDAHigh(); //get weapon accuracy range high
	int getDAOLow(); //get weapon accuracy range optimum low
	int getDAOHigh(); //get weapon accuracy range optimum high
	int getDTLevel(); //get weapon tech level
	int getDType(); //get weapon type
	int getDCXP();
	//int getDASpeed(); //get weapon attack speed

	string getDName(); //get weapon name
	string getDDType(); //get weapon damage type
	

	void dSetup(int dCode);

	string data; //string data container


	void			addTDamage(float damage, int turns, string type); //Add a new turn based damage to the vector
	void			checkTDamage(); //Check the vector for zero turn damage and remove those that are found
	void			removeTDamage(int i); //Remove a turn based damage from the vector

	//store turn based damage
	vector<tDamage> cDamage;

private:
	int		dID; //Defense ID
	float	    dSP; //structural points
	float		dMSP; //max SP
	Range	dAcc; //accuracy
	Range	dDRange; //damage range
	string  dDType; //damage type
	string	dName; //name
	int	dTLevel; //technology level
	int	dType; //weapon type
	//int dASpeed; //weapon attack speed
	int dCXP;

	int i; //For for loops
	string dState; //Store the battle state of this defesne
};


class Shield
{
public:
	Shield();

	Shield* rShield();

	void initPS(int mCode); //Init planetary shield

	int getID(); //Get shield ID

	float getSP(); //Get spoints
	float getSPRgn(); //Get spoint regen rate
	string getMName();

	void dShield(int turns); //Disable shields for value of turns
	void dTTDown(Planet* planet); //Disable timer tick down
	bool isDisabled(); //Are the shield disabled?
	int getSDTimer(); //Get ticks left on timer

	void updateDTGrace(bool state);
	bool getDTGState();

	

	float getMSP();

	void psRegen(); //Regen shield points

	void updateSP(float sp, string operation); //Update shield points

	int getTLevel();

private:
	int		mID; //Module ID
	string	mName;
	float	sSP; //Shield points
	float	sMSP; //Max shield points; for now set it from updateSP set.
	float	sRgn; //Shield regen rate
	int		mTLevel;

	int sDTimer; //Turns left for shield disable
	bool bISDisabled; //bool: is shield disabled?
	bool bDTGPeriod; //bool: is disable timer in a grace period? (meaning it will not tick down)
};
#endif