#ifndef SINV_H
#define SINV_H

#include <string>
#include "ship2.h"

using std::string;

class sInv
{
public:
	sInv();
	sInv(int item_id, int item_amount, string item_type, float item_size, bool ship); //Seocondary constructor for special occasions (maybe when rewarding items or to use later on in place of the empty constructor for code compating
	sInv(Ship2 nShip, bool ship, int id, int amount); //Constructor to load a ship into this inventory element

	void setIID(int item_id); //Set the item id for this slot
	void setIAmount(int item_amount); //Set the number of items stored in this slot
	void updateIAmount(int i, string operation);
	void setISpace(float space); //Set the amount of space that this inventory slot takes
	void setIType(string s);

	bool isShip(); //Does this element contain an item or a ship?
	int getIID(); //Get the item id for this slot
	int getIAmount(); //Get the number of items stored in this slot
	float getISpace(); //Get the amount of space taken by this inventory slot times the number of items 
	string getIType();

	Ship2 sShip; //Stored ship; takes place of other variables for this specific element of an inventory

private:
	int iID; //Item ID
	int iAmount; //Number of Items
	float iSG2; //Space taken up by the item (singular only, function will calculate total space used by multiple items of the same type) in Setigrams squared (1 SG = 3 tons, 1 SG² equals 9 tons)
	string iType;
	bool bIsShip; //Is this elmeent a ship?
};
#endif