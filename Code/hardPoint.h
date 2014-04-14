#ifndef hardPoint_H
#define hardPoint_H

#include <string>
#include "weapon.h"

using std::string;

class hardPoint
{
public:
	hardPoint();
	hardPoint(int slot,string wtype);

	void setHPSlot(int slot); //set slot number
	void setHPWType(string type); //set weapon type

	int getHPSlot(); //get slot number
	string getHPWType(); //get weapon type

protected:
	int hpSlot; //the number of this hard point; corresponds to a slot value in the weapon vector specified in hpWType
	string hpWType; //weapon vector this weapon belongs to	
};


class hardPointL : public hardPoint
{
public:
	hardPointL(int slot);
	hardPointL(int slot, string type);

	Laser hpWeapon; //Reference to store weapon
};

class hardPointM : public hardPoint
{
public:
	hardPointM(int slot);
	hardPointM(int slot, string type);

	Missile hpWeapon; //Reference to store weapon
};

class hardPointB : public hardPoint
{
public:
	hardPointB(int slot);
	hardPointB(int slot, string type);

	Bomb hpWeapon; //Reference to store weapon
};

class hardPointR : public hardPoint
{
public:
	hardPointR(int slot);
	hardPointR(int slot, string type);

	Rail hpWeapon; //Reference to store weapon
};

class hardPointH : public hardPoint
{
public:
	hardPointH(int slot);
	hardPointH(int slot, string type);

	Heavy hpWeapon; //Reference to store weapon
};
#endif