#ifndef SHIP2_H
#define SHIP2_H

#include <string>
#include <vector>

using std::string;

class Ship2
{
public:
					Ship2(); //Ship constructor
						
	int 			getAcc(string wName); //Get accuracy
	float 			getSArmor(); //Get ship armor points
	float			getSHull(); //Get ship hull points
	float 			getSMArmor(); //Get ship max armor points
	float			getSMHull(); //Get ship max hull points
	float 			getSMShield(); //Get ship max shield points
	float 			getSShield(); //Get ship shield points
	int 			getSTLevel(); //Get ship technology level
	int 			getLHP(); //Get ship laser hardpoints
	int				getULHP(); //Get number of installed weapons
	int				getMTP(); //Get ship missile turret points
	int				getUMTP();//Get number of installed weapons
	int				getBH(); //Get ship bomb holds
	int				getUBH();//Get number of installed weapons
	int				getRM(); //Get ship rail mounts
	int				getURM();//Get number of installed weapons
	int				getHWB(); //Get ship heavy weapon bays
	int				getUHWB();//Get number of installed weapons
	int				getMInit(); //Get movement initiative
	int				getSWHP(); //Get the total number of hardpoints

	void			initShip2(string name, string sclass, float shield, float mshield, float armor, float marmor, float hull, float mhull, int lb, int mt, int bh, int rm, int hwb, int twhp, int minit, int tlevel, float sg2, float mcspace, int sSID, int sSTID, string sLocal); //Load old ship data into stored ship object

	void 			updateSShield(float f, string operation); //Set ship shield points
	void 			updateSHull(float f, string operation); //Set ship hull points
	void 			updateSArmor(float f, string operation); //Set ship armor points
	void 			updateSMArmor(float f, string operation); //Set ship max armor points
	void 			updateSMHull(float f, string operation); //Set ship max hull points
	void 			updateSMShield(float f, string operation); //Set ship max shield points

	void			updateMCSpace(float space, string opteraion);
	float			getMCSpace();

	string 			getSClass(); //Get ship class
	int				getSClassI(string sclass); //Return int value of ship class
	string 			getSName(); //Get ship name
	void			initAIHPoint(string type); //Initialize AI hard points; needed because player version above returns messages
	void			setName(string s); //Set player name
	void 			setRank(string s); //Set player rank

	void 			setSClass(string s); //Set ship class
	
	void 			setSName(string s); //Set ship name
	
	void 			setSTLevel(int i); //Set ship tech level	

	void 			setLHP(int i); //Get ship laser hardpovoids
	void			setULHP(int i);
	void			setMTP(int i); //Get ship missile turret povoids
	void			setUMTP(int i);
	void			setBH(int i); //Get ship bomb holds
	void			setUBH(int i);
	void			setRM(int i); //Get ship rail mounts
	void			setURM(int i);
	void			setHWB(int i); //Get ship heavy weapon bays
	void			setUHWB(int i);
	void			setSWHP(int i);
	void			setMInit(int i);


	void			setID(int i); //Set ship ID
	void			setSID(int i); //Set sSID
	void			setSTID(int i); //Set sSTID
	void			setSLocal(string s); //Set sLocal

	int				getID();
	int				getSID();
	int				getSTID();
	string			getSLocal();


	
	float			getSSG2();
	void			setSSG2(float sg2);

private:
	
	float				sArmor; //ship armor
	int				sBH; //ship bomb holds
	int				sUBH;
	float				sHull; //ship hull
	int				sHWB; //ship heavy weapon bays
	int				sUHWB;
	int				sLB; //ship laser hardpoints
	int				sULB;
	float				sMArmor; //ship max armor
	int				sMD; //ship move distance ?
	float				sMHull; //ship max hull
	int				sMInit; //ship movement initiative
	float				sMShield; //ship max shield
	int				sMT; //ship missile turrets
	int				sUMT;
	int				sRM; //ship rail gun points
	int				sURM;
	float				sShield; //ship shield	
	int				sTLevel; //ship tech level
	int				sWHP; //ship weapon hard points	
	int				sXC; //ship xarn cost
	int				sRC; //ship ruby cost
	int				sDiC; //ship diamond cost
	int				sDC; //ship draconic cost
	int				sLC; //ship lithium cost
	int				sUC; //ship uranium cost
	int				sPC; //ship plutonium cost
	float			sSG2; //amount of space ship takes up when stored
	
	string			sClass; //ship class
	string			sName; //ship name	
	int sID; //ID of the ship in the ship_data table

	float			sMCSpace; //Max cargo space

	//For storage
	int sSID; //Storage Ship ID
	int sSTID; //Storage Station ID
	string sLocal; //Where is this ship stored?
};
#endif