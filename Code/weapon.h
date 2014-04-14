#ifndef WEAPON_H
#define WEAPON_H

#include "range.h"
#include <string>

using std::string;

/*
	All other weapon types inherit most of their functions and variables from this class.
	Where there are variables and by realtion functions for those variables they will be
	defined within the child classes where these variables and functions are only defined
	within those specific child classes.  If a certain variable/function combination is present
	in more then one child class it should be placed into Weapon to cut down on excess code lines
*/

class Weapon
{
public:

	int getWDRLow(); //get weapon damage range low
	int getWDRHigh(); //get weapon damage range high
	int getWDROLow(); //get weapon damage range optimum low
	int getWDROHigh(); // get weapon damage range optimum high
	int getWALow(); //get weapon accuracy range low
	int getWAHigh(); //get weapon accuracy range high
	int getWAOLow(); //get weapon accuracy range optimum low
	int getWAOHigh(); //get weapon accuracy range optimum high
	int getWTLevel(); //get weapon tech level
	int getWType(); //get weapon damage type
	//int getWASpeed(); //get weapon attack speed
	int getWID(); //Get weapon id

	string getWName(); //get weapon name
	string getWDType(); //get weapon damage type
	string getWClass(); //get weapon class

	void toggleWeapon(int time); //Disable weapon
	bool isWDisabled(); //Is this weapon disabled?

	void initWeapon(); //Set weapon name for checks

	void wSetup(int wCode); //Get weapon data from database
	
	float getSG2();
	void setSG2(float sg2);

	string data; //string data container

protected:
	Range	wAcc; //accuracy
	Range	wDRange; //damage range
	string  wDType; //damage type
	string	wName; //name
	int	wTLevel; //technology level
	string wClass; //weapon class
	int	wType; //weapon type
	//int wASpeed; //weapon attack speed
	bool wStatus; //weapon activity status
	int wDTimer; //weapon disable timer
	int wID; //Weapon ID
	float wSG2; //Amount of space this weapon takes up
};


class Laser : public Weapon
{
public:
	Laser(); //laser constructor

	Laser* getWeapon();

	void iWeapon(); //install weapon

	int getCLength();
	float getCMAmount();

private:

	int wMCLength; //Length of mining cycle
	float wMCAmount; //Amount of ore this laser mines per cycle
};

class Missile : public Weapon
{
public:
	Missile(); //missile contructor

	Missile* getWeapon();

	void iWeapon(); //install weapon

	/*
	For Real Time version of game
	string setAName(string name); //Set ammo name
	string setMLName(string name); //Set missile launcher name
	int setLAAmount(int i); //Set current launcher ammo amount
	int	setLMAmmo(int i); //Set max launcher ammo
	*/


private:
	/*
	For Real Time version of game
	int    mLAmmo; //Current launcher ammo
	int	   mLMAmmo; //Max launcher ammo
	string mAName; //ammo name
	string mLName; //Missile launcher name
	*/
};

class Bomb : public Weapon
{
public:
	Bomb(); //bomb contructor

	Bomb* getWeapon();

	void iWeapon(); //install weapon

	int getWeight(); //get bomb weight

private:
	int     bWeight; //weight
};

class Rail : public Weapon
{
public:
	Rail(); //rail constructor

	Rail* getWeapon();

	void iWeapon(); //install weapon

	/*
	For Real Time version of game
	string setAName(string name); //Set ammo name
	int setAAmount(int i); //Set current ammo amount
	int	setMAmmo(int i); //Set max ammo
	*/

private:
	/*
	For Real Time version of game
	int    rAmmo; //ammo
	int	   rMAmmo; //max ammo
	string rAName; //ammo name
	*/
};	

class Heavy : public Weapon
{
public:
	Heavy(); //heavy constructor

	Heavy* getWeapon();

	void iWeapon(); //install weapon

	int getDILow(); //get weapon damage intensity range low
	int getDIHigh(); //get weapon damage intensity range high
	int getDIOLow(); //get weapon damage intensity range optimum low
	int getDIOHigh(); //get weapon damage intensity range optimum high

private:
	Range  hDInt; //damage intensity
};
#endif




/* Other Weapon's Information */

/*

There are several identifiers used above that need explaining.  Some will be covered multiple times in different files depending on relevency.

Weapon Types:

1: Lasers
2: Missiles
3: Bombs
5: Heavys
6: Rails


*/
