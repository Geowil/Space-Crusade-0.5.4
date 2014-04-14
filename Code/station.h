#ifndef STATION_H
#define STATION_H

#include <string>
#include <vector>
#include "sinv.h"
#include "data_placeholder.h"
#include "entity.h"
#include "ship.h"

using std::string;
using std::vector;

class Game;

class Station
{
public:
	Station();
	
	
	void initStation(int stid, string sname, int stlevel, int sslevel, float cmulti, string dispo, string afil);

	string getName();
	string getDispo();
	string getAffil();
	int getSLevel();
	int getTLevel();
	float getCMulti();

	void setName(string name);
	void setSLevel(int lvl);
	void setTLevel(int lvl);
	void setAffil(string affil);
	void setDispo(string dispo);
	void setCMulti(float cmulti);
	int getISize(); //get inventory size
	void updateISpace(float f, string operation); //Add space to inventory
	
	int getSID(); //Get station ID

	void setSID(int id);	

	bool bIsEAEnemy(); //Specifically for player option for EA field offices on stations

	int getISItem(int i); //Get item in specific space of inventory
	int getISIAmount(int i); //Get number of items in a specific space of inventory

	float getCSUsed(); //Get current space used
	float getMUSpace(); //Get maximum usable space

	bool sBISpace(Player& mPlayer, float space); //buy inventory space

	bool sSItem(int iCode, int amount, string type, float size); //store item
	bool sSShip(int iCode, bool bought, bool exchange, Player& mPlayer, Game* mGame); //Store Ship

	bool getItem(Player& mPlayer); //Get an item to move to player ship
	void removeItem(int slot, int iAmount); //Remove item from the specified slot

	void calcUSpace(); //Calculate used space
	bool checkSpace(float nSpace); //Check if an item/ship can be stored successfully

	void setTDist(int dist); //Set travel distance to this station
	int getTDist(); //Get travel distance to this station
	
	
	vector<sInv> sInventory; //Player station inventory

private:
	int sID; //Station ID
	string		sName; //Name
	string		sDispo; //Disposition
	string		sAffil; //Affiliation
	int			sTLevel; //Tech Level
	int			sSLevel; //Station Level
	float		sCMulti; //Cost Multiplier
	int			i,i2,i3,i4; //for for loops

	float sUSpace, tempSpace; //Store used space here for returning
	float sMSSpace; //max usable station storage space
	int	  sSHSlot; //Store element number for chosen ship

	int sTDist; //Store the distance needed to travel to reach this station; for calculating if a ship is encountered
	int nOItems; //Store the number of items the player wants to operate with in various functions

	Ship tempShip_C;
	Ship tempShip_N;
	Ship2 tempShip; //Use to transfer stuff between ships; _C = current player ship, _N = new player ship

	float pChoice;
	int iPChoice;
	bool bPChoice;
	bool bDone;

};
#endif