#ifndef DATABASE_H
#define DATABASE_H

#include "../SQLite3/sqlite3.h"
#include "data_placeholder.h"
#include "debug.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Player;
class NPC;
class Entity;

class Database
{
public:
	Database();

	void openDB(bool* bErrors);
	void openSave(bool* bErrors);

	void tableTAccess(string table);

	void createStatement(int ID, string operation);

	//Get Data

	//Ship
	void getSResults(bool* bErrors);
	void returnSResult(vector<ship>& ships);

	//Weapon
	void getWResults(bool* bErrors);
	void returnWResult(vector<weapon>& weapons);

	//Mission
	void getMResults(bool* bErrors);
	void returnMResult(vector<mission>& missions);

	//Message
	void getMesResults(bool* bErrors);
	void returnMesResult(vector<message>& messages);

	//Ranks
	void getRResults(bool* bErrors);
	void returnRResult(vector<ranks>& rank);

	//Race
	void getRcResults(bool* bErrors);
	void returnRcResult(vector<race>& races);

	//Diplomacy
	void getDResults(bool* bErrors);
	void returnDResult(vector<diplomacy>& dispositions);

	//Planet Name
	void getPNResults(bool* bErrors);
	void returnPNResult(vector<planetName>& pNames);
	
	//Equipment
	void getEResults(bool* bErrors);
	void returnEResults(vector<equips>& equipment);

	//Names
	void getRNResults(bool* bErrors);
	void returnRNResults(vector<name>& names);

	//Resource Data
	void getRDResults(bool* bErrors);
	void returnRDResults(vector<resource>& resorces);

	//Ore Data
	void getOResults(bool* bErrors);
	void returnOResults(vector<ore>& ores);
	
	//Save File

	//Loading

	//Player Data
	void getPDataResults(bool* bErrors);
	void returnPDataResults(vector<playerData>& pData);

	//Player Ship
	void getPShipResults(bool* bErrors);
	void returnPShipResults(vector<pShip>& plShip);

	//Player Ship Cargo
	void getPSCResults(bool *bErrors);
	void returnPSCResults(vector<pSInv>& plSCargo);

	//Ship Spread/Weapon Vector
	void getPSSResults(bool* bErrors);
	void returnPSSResults(vector<pSSpread>& spreads);

	//Ship HP Vectors
	void getPSHPVResults(bool* bErrors);
	void returnPSHPVResults(vector<pSHPVect>& hpvectors);

	//Player Wingmen Data
	void getPWMDResults(bool* bErrors);
	void returnPWMDResults(vector<pWingmenData>& pWingmen);

	//Player Wingmen Ship Data
	void getPWSDResults(bool* bErrors);
	void returnPWSDResults(vector<pWShip>& pWShips);

	//Player Wingmen Ship Spread/Weapon Vector
	void getPWSSResults(bool* bErrors);
	void returnPWSSResults(vector<pWSSpread>& wspreads);

	//Player Wingmen Ship HP Vectors
	void getPWSHPVResults(bool* bErrors);
	void returnPWSHPVResults(vector<pWSHPVect>& whpvectors);

	//Player Mission Data
	void getPMDataResults(bool* bErrors);
	void returnPMDataResults(vector<missionData>& pMData);

	//Player Relationship Data
	void getPRDataResults(bool* bErrors);
	void returnPRDataResults(vector<relationData>& pRData);

	//Station Data
	void getSDataResults(bool* bErrors);
	void returnSDataResults(vector<stationData>& stData);

	//Player Station Inv
	void getSPIResults(bool* bErrors);
	void returnSPIResults(vector<sPInv>& pSInventory);

	//Planet Data
	void getPDResults(bool* bErrors);
	void returnPDResults(vector<planetData>& plData);

	//Planetary Defenses
	void getPDefResults(bool* bErrors);
	void returnPDefResults(vector<pDefData>& pDefenses);

	//Planetary Shield
	void getPSDResults(bool* bErrors);
	void returnPSDResults(vector<pSData>& pShields);

	//Planet A. Belts
	void getPABResults(bool* bErrors);
	void returnPABResults(vector<pABelts>& belts);

	//Planet AB Roids
	void getPABRResults(bool* bErrors);
	void returnPABRResults(vector<pABRoids>& roids);

	//Save Flags
	void getSFlagResults(bool* bErrors);
	void returnSFlagResults(vector<saveFlag>& saveFlags);

	

	//Saving
	void sData(vector<playerData> pData, vector<pShip> plShip, vector<pSSpread> plSSpreads, vector<pSHPVect> plSHPVectors, vector<pSInv> plSCargo, vector<pWingmenData> pWMData, vector<pWShip> pWMSData, vector<pWSSpread> pWMSSpreads, vector<pWSHPVect> pWMSHPVectors, vector<stationData> stData, vector<sPInv> sPInventory, vector<planetData> plData, vector<pDefData> plDData, vector<pSData> plSData, vector<pABelts> belts, vector<pABRoids> roids, vector<missionData> pMData, vector<relationData> pRData, bool* bErrors);
	
	//Update Data
	void dData(string table, bool* bErrors); //Delete the data from a table

	//Misc Functions
	int getCount(string table, bool* bErrors); //Get number of rows in a table; for use with checking for rows for vectors and also for vector-in-vector situations
	void finalize(sqlite3_stmt* stmt, bool* bErrors); //Finalize a statement

	void closeDB(bool* bErrors);


	//For Debugging
	void createBInfo();

private:
	sqlite3 *dBase;
	sqlite3_stmt *statement;
	sqlite3_stmt *statement2;

	string sqlStr,sqlStr2;

	char* error;

	//Query Data Storage
	vector<ship> sResults; //Ship Data
	vector<weapon> wResults; //Weapon Data
	vector<mission> mResults; //Mission Data
	vector<message> mesResults; //Message Data
	vector<ranks> rResults; //Rank Data
	vector<race> rcResults; //Race Data
	vector<diplomacy> dResults; //Disposition Data
	vector<planetName> pNResults; //Planet Name Data
	vector<equips> eResults; //Defenses Data
	vector<name> nResults; //Names
	vector<resource> resResults; //Resource
	vector<ore> oResults; //Ore 

	//Save File (Load)
	vector<planetData> plDataResults;
	vector<pDefData> pDefensesResults;
	vector<pSData> pShieldsResults;
	vector<pABelts> pABResults;
	vector<pABRoids> pABRResults;
	vector<playerData> pDataResults;
	vector<pShip> plShipResults;
	vector<pSSpread> spreadResults;
	vector<pSHPVect> hpvectorResults;
	vector<pSInv> pSCResults;
	vector<pWingmenData> pWingmenResults;
	vector<pWShip> pWShipResults;
	vector<pWSSpread> wspreadResults;
	vector<pWSHPVect> whpvectorResults;
	vector<stationData> stDataResults;
	vector<sPInv> pSInventoryResults;
	vector<missionData> pMDataResults;
	vector<relationData> pRDataResults;
	vector<saveFlag> sFlags;
	vector<saveFlag> sFlags_Temp;


	//Save File (Saving)
	//ints
	int sqlI1;
	int sqlI2;
	int sqlI3;
	int sqlI4;
	int sqlI5;
	int sqlI6;
	int sqlI7;
	int sqlI8;
	int sqlI9;
	int sqlI10;
	int sqlI11;
	int sqlI12;
	int sqlI13;
	int sqlI14;
	int sqlI15;
	int sqlI16;
	int sqlI17;
	int sqlI18;
	int sqlI19;
	int sqlI20;
	int sqlI21;
	int sqlI22;
	
	//long long ints
	long long int	sqlLLI1;
	long long int	sqlLLI2;
	long long int	sqlLLI3;

	//floats
	float sqlF1;
	float sqlF2;
	float sqlF3;
	float sqlF4;
	float sqlF5;
	float sqlF6;
	float sqlF7;
	float sqlF8;
	float sqlF9;
	float sqlF10;

	//strings
	string	sqlS1;
	string	sqlS2;
	string	sqlS3;
	string	sqlS4;
	string	sqlS5;
	string	sqlS6;
	string	sqlS7;
	string	sqlS8;
	string 	sqlS9;
	string	sqlS10;
	string	sqlS11;
	string	sqlS12;	

	//bools
	bool	sqlB1;
	bool	sqlB2;
	bool	sqlB3;



	int cols,rows;
	int i,i2,result,i3;

	string dTable;

	//For Debug
	string file,line,bLocale,time,date,bTDate;

	const char *data;

	//bool bS2Used;
	string find,temp;
	int foundAt;	
};
#endif