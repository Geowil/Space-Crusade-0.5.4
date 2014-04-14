#include "datasystem.h"
#include "database.h"
#include "msgproc.h"
#include "map.h"
#include <Windows.h>

using namespace std;

dataSystem ds_mp;
Database db_mp;
Map m_mp;

msgProc::msgProc()
{

}

//Make new message databases of responses for ship to ship hails.  Make a database for each race you can encounter in a normal battle sitatuion.  For tech merchant see main message database

string msgProc::mRMessage(int mCode)
{
	ds_mp.rData("Msg_Data","select from",mCode);
	return ds_mp.getMsg();
}

int msgProc::gTMenu()
{
	cout << "||===========================||" << endl;
	cout << "||SPACE CRUSADE V0.5A Build 4||" << endl;
	cout << "||===========================||" << endl;
	cout << "1) New Game" << endl;
	cout << "2) Continue Game" << endl;
	cout << "3) Quit" << endl;
	cout << "> ";

	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 3)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::nMenu1()
{
	cout << "1) Show planets within 50LY" << endl;
	cout << "2) Show stations within 200LY" << endl;
	cout << "3) Seach for ships" << endl;
	cout << "4) Ship Status" << endl;
	//cout << "5) Crew Status" << endl; //For crew productivity, moral, and reaction values to be added later
	cout << "6) Save Game" << endl;
	//cout << "7) Load Game" << endl;
	cout << "8) Quit" << endl;
	cout << "> "; 
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 8 || pChoice == 5 || pChoice == 7)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::gGTPlanet(vector<Planet> planets, Player& mPlayer)
{
	cout << "Please choose one of the following planets to travel to:" << endl;
	cout << "0) Cancel" << endl;

	for (i = 1; i <= planets.size(); i++)
	{
		cout << i << ") " << planets.at(i-1).getName() << endl;
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if ((pChoice < 0 || pChoice > planets.size()))
	{
		mRMessage(5);
		pChoice = 0;
	}

	if (pChoice != 0)
	{
		pChoice -= 1;

		cout << "Displaying known information:" << endl;

		cout << "Planet Name:		" << planets.at(pChoice).getName() << endl;
		cout << "Planet EKS Rating:		" << planets.at(pChoice).getEKS() << endl;
		cout << "Planet Population:		" << planets.at(pChoice).getPopS() << "/" << planets.at(pChoice).getMPopS() << endl;
		
		for (i = 0; i <= mPlayer.pRelations.size(); i++)
		{
			if (i == mPlayer.pRelations.size())
			{
				cout << "Affiliation:		Unknown" << endl;
			}
			
			else if (planets.at(pChoice).getAffil() == mPlayer.pRelations.at(i).getRName())
			{
				cout << "Affiliation:		" << planets.at(pChoice).getAffil() << endl;
				cout << "Relation Status:		" << mPlayer.pRelations.at(i).getAffinityS() << endl;
				break;
			}
		}

		cout << "Planet Defenses:" << endl;
		
		if (planets.at(pChoice).pDef.size() > 0)
		{
			for (i = 0; i < planets.at(pChoice).pDef.size(); i++)
			{
				cout << "Defensive Structure " << i << ":		" << endl;
				cout << "Defense Name:		" << planets.at(pChoice).pDef.at(i).getDName() << endl;
				cout << "Defense Integrity:	" << planets.at(pChoice).pDef.at(i).getSPoints() << endl << endl;
			}
		}

		else
		{
			cout << "No defenses detected." << endl << endl;
		}

		cout << "Planet Shields:" << endl;
		if (planets.at(pChoice).pShd.size() > 0)
		{
			for (i = 0; i < planets.at(pChoice).pShd.size(); i++)
			{
				cout << "Planetary Shield " << i << ":		" << endl;
				cout << "Module Name:		" << planets.at(pChoice).pShd.at(i).getMName() << endl;
				cout << "Shield Strength:	" << planets.at(pChoice).pShd.at(i).getSP() << endl << endl;
			}
		}

		else
		{
			cout << "No shields detected." << endl << endl;
		}

		cout << "Are you sure you wish to travel to this planet?" << endl;
		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;

		switch(pCChoice)
		{
		case 'y':
		case 'Y':
			return pChoice;
			break;			

		default:
			pChoice = -1;
			return pChoice;
			break;
		}
	}

	else
	{
		pChoice = -1;
		return pChoice;
	}	
}

int msgProc::gGTStation(vector<Station> tStats, Player& mPlayer, Game* mGame)
{
	cout << "Please choose one of the following stations to travel to:" << endl;
	cout << "0) Cancel" << endl;

	for (i = 1; i <= tStats.size(); i++)
	{
		cout << i << ") " << tStats.at(i-1).getName() << endl;
	}

	cout << ">";
	cin >> pChoice;

	if ((pChoice < 0 || pChoice > tStats.size()))
	{
		mRMessage(5);
		pChoice = 0;
	}

	if (pChoice != 0)
	{
		pChoice -= 1;

		if (mGame->gStations.size() > 0) //To ensure no crashes from trying to get the size of a null vector
		{
			for (i = 0; i <= mGame->gStations.size(); i++)
			{
				if (i == mGame->gStations.size()) //If station does not exist
				{
					mGame->createStation(tStats.at(pChoice).getName(), mPlayer); //Create it
					pSStat = mGame->gStations.size(); //And then assign the size of gStations to pSStat (since the last added element will be the one we want)
					break;
				}

				else if (tStats.at(pChoice).getName() == mGame->gStations.at(i).getName()) //Else if the station does exist
				{
					pSStat = i+1; //Set pSStat to i + 1;  an increase in value because i is on the 0-index while we want pSStat to be on a 1-index.
					break;
				}
			}
		}

		else //If no stations have been created then
		{
			mGame->createStation(tStats.at(pChoice).getName(), mPlayer); //Create the station
			pSStat = mGame->gStations.size(); //And then assign the size of gStations to pSStat (since the last added element will be the one we want)
		}

		//Display station information
		cout << "Displaying known information:" << endl;

		cout << "Station Name:		" << mGame->gStations.at(pSStat-1).getName() << endl;
		cout << "Station Level:		" << mGame->gStations.at(pSStat-1).getSLevel() << endl;
		cout << "Technology Level:	" << mGame->gStations.at(pSStat-1).getTLevel() << endl;
		
		for (i = 0; i <= mPlayer.pRelations.size(); i++)
		{
			if (mGame->gStations.at(pSStat-1).getAffil() == mPlayer.pRelations.at(i).getRName())
			{
				cout << "Affiliation:		" << mGame->gStations.at(pSStat-1).getAffil() << endl;
				cout << "Relation Status:	" << mPlayer.pRelations.at(i).getAffinityS() << endl;
				break;
			}
		}		

		cout << "Cost Multiplier:	" << mGame->gStations.at(pSStat-1).getCMulti() << endl;
		cout << endl;

		cout << "Are you sure you wish to travel to this station?" << endl;
		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;

		switch(pCChoice)
		{
		case 'y':
		case 'Y':
			break;			

		default:
			pChoice = -1;
			break;
		}
	}

	else
	{
		pChoice = -1;
	}

	if (pChoice != -1)
	{
		return pSStat-1;
	}

	else
	{
		return -1;
	}
}


//int msgProc::nMenu2()
//{
//	cout << mRMessage(2) << endl;
//}

int msgProc::bMenu1()
{
	cout << "1) Hail the ship" << endl;
	cout << "2) Prepare to Fire" << endl;	
	cout << "3) Enemy Armament Information" << endl;
	cout << "4) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bMenu1A()
{
	cout << "1) Hail the planet" << endl;
	cout << "2) Prepare to Fire" << endl;	
	cout << "3) Enemy Armament Information" << endl;
	cout << "4) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}


int msgProc::bMenu1B(int hostiles)
{
	cout << "1) Attack Targeted Ship" << endl;
	
	if (hostiles > 1)
	{
		cout << "2) Change Target" << endl;
	}

	cout << "3) Check Ship Status" << endl;
	cout << "4) Check Current Target Status" << endl;
	cout << "5) Move the Ship" << endl;
	cout << "6) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 6 || ((hostiles == 1) && (pChoice == 2)))
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bMenu1B_PB1()
{
	cout << "1) Attack Shield" << endl;
	cout << "2) Check Ship Status" << endl;
	cout << "3) Check Current Target Status" << endl;
	cout << "4) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bMenu1B_PB3(int hostiles)
{
	cout << "1) Attack Targeted Defense" << endl;
	
	if (hostiles > 1)
	{
		cout << "2) Change Target" << endl;
	}

	cout << "3) Check Ship Status" << endl;
	cout << "4) Check Current Target Status" << endl;
	cout << "5) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 5 || ((hostiles == 1) && (pChoice == 2)))
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bMenu2()
{
	cout << "1) Fire all weapons" << endl;
	cout << "2) Fire weapon spread" << endl;
	cout << "3) Fire weapon system" << endl;
	cout << "4) Fire specific weapons" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bMenu2_PB()
{
	cout << "1) Fire all bombs" << endl;
	cout << "2) Fire weapon spread" << endl;
	cout << "3) Fire specific weapon system" << endl;
	cout << "4) Fire specific weapons" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::bPBMenu()
{
	cout << "1) Planetary Information" << endl;
	cout << "2) Launch bombs" << endl;
	cout << "3) Retreat" << endl;
	cout << "> ";
	
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 3)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::pCMenu1()
{
	cout << mRMessage(3) << endl;
	cout << "1) Arcon" << endl;
	cout << "2) Osprey" << endl;
	cout << "3) Rifter" << endl;
	cout << "4) Incurses" << endl;
	cout << "5) Morgul" << endl;
	cout << ">";

	cin >> pChoice; //user menu input
	cout << endl;

	if (pChoice < 1 || pChoice > 5)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1; //If player tries to enter a number not in the list or that is inbValid, set selection to 1
	}

	return pChoice;
}

int msgProc::pCMenu2()
{
	cout << mRMessage(4) << endl;
	cout << "1) Low-Tech Phaser Array" << endl;
	cout << "2) Ion-Particle Blaster" << endl;
	cout << "3) 50mm Suspended Coil Laser Cannon" << endl;
	cout << "4) 50mm Omega Cannon Prototype" << endl;
	cout << "5) 50mm High-Output Ion Blaster" << endl;
	cout << "6) Lightron Blaster" << endl;
	cout << "> ";

	cin >> pChoice; //user menu input
	cout << endl;

	if (pChoice < 1 || pChoice > 6)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1; //If user tries to input inbValid value, default to 1
	}

	return pChoice;
}

int msgProc::pCMenu3()
{
	cout << mRMessage(10) << endl;
	cout << "31) Calamity Lite Standard" << endl;
	cout << "32) Ravager Lite" << endl;
	cout << "33) Cruise Missile" << endl;
	cout << "34) Warhawk Advanced Lite" << endl;
	cout << "35) Bloodhawk Lite" << endl;
	cout << "36) Serpent Lite" << endl;
	cout << ">";

	cin >> pChoice;
	cout << endl;

	if (pChoice < 31 || pChoice > 36)
	{
		cout << mRMessage(5) << endl;
		pChoice = 31; //If user tries to input inbValid value, default to 31
	}

	return pChoice;
}

int msgProc::pCMenu4()
{
	cout << mRMessage(11) << endl;
	cout << "102) Destructor" << endl;
	cout << "103) Neopryte" << endl;
	cout << "104) Lite Gettysburg" << endl;
	cout << "105) Nako Advanced" << endl;
	cout << ">";

	cin >> pChoice; //user menu choice
	cout << endl;

	if (pChoice < 102 || pChoice > 105)
	{
		cout << mRMessage(5) << endl;
		pChoice = 102; //If user tries to input inbValid value, default to 102
	}

	return pChoice;
}

void msgProc::pInfo(Player& mPlayer, Game& mGame)
{
	bContinue = true;

	while(bContinue)
	{
		cout << "Select one of the following options:" << endl;
		cout << "1) Basic Player Information" << endl;
		cout << "2) Basic Player Ship Information" << endl;
		cout << "3) Detailed Player Information" << endl;
		cout << "4) Detailed Ship Information" <<  endl;
		cout << "5) Relationships" << endl;
		cout << "6) Active Missions" << endl;
		cout << "7) Inactive Missions" << endl;
		cout << "8) Player Assets" << endl;
		cout << "9) Leave Information Database" << endl;
		cout << ">";
		cin >> pChoice;

		if (pChoice < 0 || pChoice > 9)
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
		}

		mCScreen(false);

		switch(pChoice)
		{
		case 1:

			cout << "Player Status Information:" << endl;
			cout << "Name:					" << mPlayer.getName() << endl;
			cout << "Rank:					" << mPlayer.getRank() << endl;
			cout << "C.E. Level:				" << mPlayer.getCELvl() << endl;
			cout << "CEXP:					" << mPlayer.getCEXP() << endl;
			cout << "CXP to Next Level:			" << mPlayer.getCXPTNL() << endl;

			mCScreen(true);

			break;

		case 2:

			cout << "Player Ship Information:" << endl;
			cout << "Name:				" << mPlayer.Ship.getSName() << endl;
			cout << "Class:				" << mPlayer.Ship.getSClass() << endl;
			cout << "Shield Strength:		" << ((mPlayer.Ship.getSShield()/mPlayer.Ship.getSMShield())*100) << "% (" << mPlayer.Ship.getSShield() << " / " << mPlayer.Ship.getSMShield() << ")" << endl;
			cout << "Armor Strength:			" << ((mPlayer.Ship.getSArmor()/mPlayer.Ship.getSMArmor())*100) << "% (" << mPlayer.Ship.getSArmor() << " / " << mPlayer.Ship.getSMArmor() << ")" << endl;
			cout << "Hull Strength:			" << ((mPlayer.Ship.getSHull()/mPlayer.Ship.getSMHull())*100) << "% (" << mPlayer.Ship.getSHull() << " / " << mPlayer.Ship.getSMHull() << ")" << endl;
			
			mCScreen(true);

			break;

		case 3:
			
			cout << "Player Status Information:" << endl;
			cout << "Name:					" << mPlayer.getName() << endl;
			cout << "Rank:					" << mPlayer.getRank() << endl;
			cout << "C.E. Level:				" << mPlayer.getCELvl() << endl;
			cout << "CEXP:					" << mPlayer.getCEXP() << endl;
			cout << "CXP to Next Level:			" << mPlayer.getCXPTNL() << endl;
			cout << endl;

			cout << "Player Kill Record:" << endl;
			cout << "Frigate Kills:				" << mPlayer.getFKills() << endl;
			cout << "Destroyer Kills:			" << mPlayer.getDKills() << endl;
			cout << "Cruiser Kills:				" << mPlayer.getCKills() << endl;
			cout << "B. Cruiser Kills:			" << mPlayer.getBCKills() << endl;
			cout << "Battleship Kills:			" << mPlayer.getBKills() << endl;
			cout << "Mothership Kills:			" << mPlayer.getMKills() << endl;
			cout << "Titan Kills:				" << mPlayer.getTKills() << endl;
			cout << endl;

			cout << "Player Resources:" << endl;
			cout << "Xarn:					" << mPlayer.getXarn() << endl;
			cout << "Rubies:					" << mPlayer.getRubies() << endl;
			cout << "Diamonds:				" << mPlayer.getDia() << endl;
			cout << "Draconic:				" << mPlayer.getDrac() << endl;
			cout << "Lithium:				" << mPlayer.getLith() << endl;
			cout << "Platinum:				" << mPlayer.getPlat() << endl;
			cout << "Uranium:				" << mPlayer.getUra() << endl;
			cout << "Plutonium:				" << mPlayer.getPlut() << endl;
			cout << "Nuclear Waste:				" << mPlayer.getNWaste() << endl;	

			mCScreen(true);

			break;

		case 4:
			cout << "Player Ship Information:" << endl;
			cout << "Name:				" << mPlayer.Ship.getSName() << endl;
			cout << "Class:				" << mPlayer.Ship.getSClass() << endl;
			cout << "Shield Strength:		" << ((mPlayer.Ship.getSShield()/mPlayer.Ship.getSMShield())*100) << "% (" << mPlayer.Ship.getSShield() << " / " << mPlayer.Ship.getSMShield() << ")" << endl;
			cout << "Armor Strength:			" << ((mPlayer.Ship.getSArmor()/mPlayer.Ship.getSMArmor())*100) << "% (" << mPlayer.Ship.getSArmor() << " / " << mPlayer.Ship.getSMArmor() << ")" << endl;
			cout << "Hull Strength:			" << ((mPlayer.Ship.getSHull()/mPlayer.Ship.getSMHull())*100) << "% (" << mPlayer.Ship.getSHull() << " / " << mPlayer.Ship.getSMHull() << ")" << endl;
			cout << "Movement Initiative:		" << mPlayer.Ship.getMInit() << endl;
			cout << endl;

			system("Pause");
			
			cout << "Weapon Information: " << endl;
			cout << mPlayer.Ship.getULHP() << " laser banks used out of " << mPlayer.Ship.getLHP() << " used." << endl;
			cout << endl;
			cout << "Installed laser weapons:" << endl;

			for (i = 0; i < mPlayer.Ship.lBanks.size(); i++)
			{
				wName = mPlayer.Ship.lBanks.at(i).hpWeapon.getWName();

				if (wName != "No Weapon Installed")
				{
					cout << "Name:					" << wName << endl;
					cout << "Damage:					" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWDRLow() << "-" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWDRHigh() << endl;
					cout << "Range:					" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWALow() << "(" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWAOLow() << ")-" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWAHigh() << "(" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWAOHigh() << ") KM" << endl;
					cout << "Damage Type:				" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWDType() << endl;
					cout << "Class:					" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWClass() << endl;
					cout << "Technology Level:			" << mPlayer.Ship.lBanks.at(i).hpWeapon.getWTLevel() << endl;
					cout << endl;					
				}				
			}

			mCScreen(true);

			cout << mPlayer.Ship.getUMTP() << " missile turrets used out of " << mPlayer.Ship.getMTP() << " used." << endl;
			cout << endl;
			cout << "Installed missile weapons:" << endl;

			for (i = 0; i < mPlayer.Ship.mTurrets.size(); i++)
			{
				wName = mPlayer.Ship.mTurrets.at(i).hpWeapon.getWName();

				if (wName != "No Weapon Installed")
				{
					cout << "Name:					" << wName << endl;
					cout << "Damage:					" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWDRLow() << "-" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWDRHigh() << endl;
					cout << "Range:					" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWAHigh() << " KM" << endl;
					cout << "Damage Type:				" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWDType() << endl;
					cout << "Class:					" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWClass() << endl;
					cout << "Technology Level:			" << mPlayer.Ship.mTurrets.at(i).hpWeapon.getWTLevel() << endl;
					cout << endl;
				}				
			}
			
			mCScreen(true);

			cout << mPlayer.Ship.getUBH() << " bomb holds used out of " << mPlayer.Ship.getBH() << " used." << endl;
			cout << endl;
			cout << "Installed bomb weapons:" << endl;

			for (i = 0; i < mPlayer.Ship.bHolds.size(); i++)
			{
				wName = mPlayer.Ship.bHolds.at(i).hpWeapon.getWName();

				if (wName != "No Weapon Installed")
				{
					cout << "Name:					" << wName << endl;
					cout << "Damage:					" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWDRLow() << "-" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWDRHigh() << endl;
					cout << "Weight:					" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWeight() << endl;
					cout << "Damage Type:				" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWDType() << endl;
					cout << "Class:					" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWClass() << endl;
					cout << "Technology Level:			" << mPlayer.Ship.bHolds.at(i).hpWeapon.getWTLevel() << endl;
					cout << endl;
				}				
			}
			
			mCScreen(true);

		
			cout << mPlayer.Ship.getURM() << " railgun mounts used out of " << mPlayer.Ship.getRM() << " used." << endl;
			cout << endl;
			cout << "Installed railgun weapons:" << endl;

			for (i = 0; i < mPlayer.Ship.rMounts.size(); i++)
			{
				wName = mPlayer.Ship.rMounts.at(i).hpWeapon.getWName();

				if (wName != "No Weapon Installed")
				{
					cout << "Name:					" << wName << endl;
					cout << "Damage:					" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWDRLow() << "-" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWDRHigh() << endl;
					cout << "Range:					" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWALow() << "(" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWAOLow() << ")-" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWAHigh() << "(" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWAOHigh() << ") KM" << endl;
					cout << "Damage Type:				" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWDType() << endl;
					cout << "Class:					" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWClass() << endl;
					cout << "Technology Level:			" << mPlayer.Ship.rMounts.at(i).hpWeapon.getWTLevel() << endl;
					cout << endl;
				}				
			}
			
			mCScreen(true);

			cout << mPlayer.Ship.getUHWB() << " heavy weapons bays used out of " << mPlayer.Ship.getHWB() << " used." << endl;
			cout << endl;
			cout << "Installed heavy weapons weapons:" << endl;

			for (i = 0; i < mPlayer.Ship.hWBays.size(); i++)
			{
				wName = mPlayer.Ship.rMounts.at(i).hpWeapon.getWName();

				if (wName != "No Weapon Installed")
				{
					cout << "Name:					" << wName << endl;
					cout << "Damage:					" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWDRLow() << "-" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWDRHigh() << endl;
					cout << "Damage Intensity:			" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWALow() << "(" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAOLow() << ")-" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAHigh() << "(" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAOHigh() << ")" << endl;
					cout << "Range:					" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWALow() << "(" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAOLow() << ")-" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAHigh() << "(" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWAOHigh() << ")" << endl;
					cout << "Damage Type:				" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWDType() << endl;
					cout << "Class:					" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWClass() << endl;
					cout << "Technology Level:			" << mPlayer.Ship.hWBays.at(i).hpWeapon.getWTLevel() << endl;
					cout << endl;
				}				
			}
			
			mCScreen(true);

			break;
			
		case 5:
			cout << "Player Relations:" << endl;

			if (mPlayer.pRelations.size() != 0)
			{
				for (i = 0; i < mPlayer.pRelations.size(); i++)
				{
					cout << "Name:		" << mPlayer.pRelations.at(i).getRName() << endl;
					cout << "Affinity:	" << mPlayer.pRelations.at(i).getAffinityS() << " (" << mPlayer.pRelations.at(i).getAffinity() << ")" << endl;
					cout << endl;
				}
			}

			else
			{
				cout << "Player has no relations" << endl;
			}

			mCScreen(true);

			break;

		case 6:
			cout << "Player's Active Missions:" << endl;

			if (mPlayer.pMissions.size() != 0)
			{
				for (i = 0; i < mPlayer.pMissions.size(); i++)
				{
					cout << "Name:				" << mPlayer.pMissions.at(i).getMName() << endl;
					cout << "Type:				" << mPlayer.pMissions.at(i).getMType() << endl;
					cout << "State:				" << mPlayer.pMissions.at(i).getMState() << endl;
					cout << "Duration:			" << mPlayer.pMissions.at(i).getMDur() << endl;
					cout << "Difficulty:			" << mPlayer.pMissions.at(i).getMDiff() << endl;
					cout << endl;

					cout << "Mission Requirements:" << endl;
					cout << "Required Level:			" << mPlayer.pMissions.at(i).getMCBEReq() << endl;
					cout << "Required Ship Class:		" << mPlayer.pMissions.at(i).getMSCReq() << endl;
					cout << "Required Equipment:		" << mPlayer.pMissions.at(i).getMMWReq() << endl;
					cout << endl;

					cout << "Mission Location/Target:" << endl;
					cout << "Sector:				" << mPlayer.pMissions.at(i).getMSector() << endl;
					cout << "System:				" << mPlayer.pMissions.at(i).getMSystem() << endl;
					cout << "Target Name:			" << mPlayer.pMissions.at(i).getMTName() << endl;
					cout << "Target Ship Class:		" << mPlayer.pMissions.at(i).getMTSClass() << endl;
					cout << endl;

					cout << "Mission Rewards:" << endl;

					if (mPlayer.pMissions.at(i).getMType() == "Bounty")
					{
						cout << "Bounty:				" << mPlayer.pMissions.at(i).getMBounty() << endl;
					}

					else
					{
						cout << "Xarn:				" << mPlayer.pMissions.at(i).getMXR() << endl;
					}

					cout << "Rubies:				" << mPlayer.pMissions.at(i).getMRR() << endl;
					cout << "Diamonds:			" << mPlayer.pMissions.at(i).getMDiR() << endl;
					cout << "Draconic:			" << mPlayer.pMissions.at(i).getMDR() << endl;
					cout << "Lithium:			" << mPlayer.pMissions.at(i).getMLR() << endl;
					cout << "Platinum:			" << mPlayer.pMissions.at(i).getMPlR() << endl;
					cout << "Uranium:			" << mPlayer.pMissions.at(i).getMUR() << endl;
					cout << "Plutonium:			" << mPlayer.pMissions.at(i).getMPR() << endl;
					cout << "Nuclear Waste:			" << mPlayer.pMissions.at(i).getMNWR() << endl;
					cout << "Equipment:			" << mPlayer.pMissions.at(i).getMIR() << endl;

					mCScreen(true);
				}
			}

			else
			{
				cout << "Player has no active missions" << endl;
				mCScreen(true);
			}

			break;

		case 7:
			cout << "Player's Inactive Missions:" << endl;

			if (mPlayer.pCMissions.size() != 0)
			{
				for (i = 0; i < mPlayer.pCMissions.size(); i++)
				{
					cout << "Name:				" << mPlayer.pCMissions.at(i).getMName() << endl;
					cout << "Type:				" << mPlayer.pCMissions.at(i).getMType() << endl;
					cout << "State:				" << mPlayer.pCMissions.at(i).getMState() << endl;
					cout << "Duration:			" << mPlayer.pCMissions.at(i).getMDur() << endl;
					cout << "Difficulty:			" << mPlayer.pCMissions.at(i).getMDiff() << endl;
					cout << endl;

					cout << "Mission Requirements:" << endl;
					cout << "Required Level:			" << mPlayer.pCMissions.at(i).getMCBEReq() << endl;
					cout << "Required Ship Class:		" << mPlayer.pCMissions.at(i).getMSCReq() << endl;
					cout << "Required Equipment:		" << mPlayer.pCMissions.at(i).getMMWReq() << endl;
					cout << endl;

					cout << "Mission Location/Target:" << endl;
					cout << "Sector:				" << mPlayer.pCMissions.at(i).getMSector() << endl;
					cout << "System:				" << mPlayer.pCMissions.at(i).getMSystem() << endl;
					cout << "Target Name:			" << mPlayer.pCMissions.at(i).getMTName() << endl;
					cout << "Target Ship Class:		" << mPlayer.pCMissions.at(i).getMTSClass() << endl;
					cout << endl;

					mCScreen(true);
				}
			}

			else
			{
				cout << "Player has no active missions" << endl;
				mCScreen(true);
			}

			break;

		case 8:
			cout << "Player Assets and Location" << endl;

			if (mGame.gStations.size() != 0)
			{
				for (i = 0; i <= mGame.gStations.size(); i++)
				{
					if (i == mGame.gStations.size())
					{
						cout << "Player has no assets stored in any station inventory" << endl;
						mCScreen(true);
					}

					else
					{
						if (mGame.gStations.at(i).getISize() != 0)
						{
							for (i2 = 0; i2 < mGame.gStations.at(i).getISize(); i2++)
							{
								iType = mGame.gStations.at(i).sInventory.at(i2).getIType();
								iID = mGame.gStations.at(i).sInventory.at(i2).getIID();

								//This will be done this way until the function merger TODO from dataSystem has been completed; code line heavy

								cout << mGame.gStations.at(i).getName() << "'s Inventory:" << endl;


								if (iType == "Ship")
								{
									dbTable = "Ship_Data";

									ds_mp.rData(dbTable,"select from",iID);

									cout << "Item Name:				" << ds_mp.getSName() << endl;
									cout << "Number of Items:			" << mGame.gStations.at(i).sInventory.at(i2).getIAmount() << endl;
									cout << endl;
								}

								else if (iType == "Weapon")
								{
									dbTable = "Weapon_Data";

									ds_mp.rData(dbTable,"select from",iID);

									cout << "Item Name:				" << ds_mp.getWName() << endl;
									cout << "Number of Items:			" << mGame.gStations.at(i).sInventory.at(i2).getIAmount() << endl;
									cout << endl;
								}

								else if (iType == "Item" || iType == "PDefense" || iType == "PShield" || iType == "Clone" || iType == "Module")
								{
									dbTable = "Equipment_Data";

									ds_mp.rData(dbTable,"select from",iID);

									cout << "Item Name:				" << ds_mp.getEName() << endl;
									cout << "Number of Items:			" << mGame.gStations.at(i).sInventory.at(i2).getIAmount() << endl;
									cout << endl;
								}

								mCScreen(true);
							}
						}
					}
				}
			}

			else
			{
				cout << "Player has not visited any stations" << endl;
				mCScreen(true);
			}

			break;

		case 9:
			bContinue = false;
			break;
		}
	}
}

void msgProc::pBAStatus(Player& mPlayer, int allies)
{
	for (i = 0; i <= allies - 1; i++)
	{
		if (i == 0)
		{
			//Player information
			pname = mPlayer.getName();
			prank = mPlayer.getRank();
			psname = mPlayer.Ship.getSName();
			psclass = mPlayer.Ship.getSClass();
			pssp = mPlayer.Ship.getSShield();
			psap = mPlayer.Ship.getSArmor();
			pshp = mPlayer.Ship.getSHull();
			psmsp = mPlayer.Ship.getSMShield();
			psmap = mPlayer.Ship.getSMArmor();
			psmhp = mPlayer.Ship.getSMHull();
			psdt = 0;
			psstatus = " ";

			if (mPlayer.Ship.isDisabled())
			{
				psstatus = "Disabled";
				psdt = mPlayer.Ship.getSDTimer();
			}

			else
			{
				psstatus = "Green";
			}
		}

		else
		{
			pname = mPlayer.eWingmen.at(i-1).getName();
			prank = mPlayer.eWingmen.at(i-1).getRank();
			psname = mPlayer.eWingmen.at(i-1).Ship.getSName();
			psclass = mPlayer.eWingmen.at(i-1).Ship.getSClass();
			pssp = mPlayer.eWingmen.at(i-1).Ship.getSShield();
			psap = mPlayer.eWingmen.at(i-1).Ship.getSArmor();
			pshp = mPlayer.eWingmen.at(i-1).Ship.getSHull();
			psmsp = mPlayer.eWingmen.at(i-1).Ship.getSMShield();
			psmap = mPlayer.eWingmen.at(i-1).Ship.getSMArmor();
			psmhp = mPlayer.eWingmen.at(i-1).Ship.getSMHull();
			psdt = 0;
			psstatus = " ";

			if (mPlayer.eWingmen.at(i-1).Ship.isDisabled())
			{
				psstatus = "Disabled";
				psdt = mPlayer.eWingmen.at(i-1).Ship.getSDTimer();
			}

			else
			{
				psstatus = "Green";
			}
		}

		//Player Status
		cout << pname << "'s Status" << endl;
		cout << pname << "'s Rank: " << prank << endl;
		cout << pname << "'s Ship: " << psname << endl;
		cout << psname << "'s Status: " << psstatus << endl;

		if (psstatus == "Disabled")
		{
			cout << psname << "'s Downtime: " << psdt << endl;
		}

		cout << psname << "'s Shield Strength: " << ((pssp/psmsp)*100) << "% (" << pssp << " / " << psmsp << ")" << endl;
		cout << psname << "'s Armor Strength: " << ((psap/psmap)*100) << "% (" << psap << " / " << psmap << ")" << endl;
		cout << psname << "'s Hull Strength: " << ((pshp/psmhp)*100) << "% (" << pshp << " / " << psmhp << ")" << endl;	
	}

	mCScreen(true);
}

void msgProc::pBStatus(Player& mPlayer)
{
	//Player information
	pname = mPlayer.getName();
	prank = mPlayer.getRank();
	psname = mPlayer.Ship.getSName();
	psclass = mPlayer.Ship.getSClass();
	pssp = mPlayer.Ship.getSShield();
	psap = mPlayer.Ship.getSArmor();
	pshp = mPlayer.Ship.getSHull();
	psmsp = mPlayer.Ship.getSMShield();
	psmap = mPlayer.Ship.getSMArmor();
	psmhp = mPlayer.Ship.getSMHull();
	psdt = 0;
	psstatus = " ";

	if (mPlayer.Ship.isDisabled())
	{
		psstatus = "Disabled";
		psdt = mPlayer.Ship.getSDTimer();
	}

	else
	{
		psstatus = "Green";
	}

	//Player Status
	cout << pname << "'s Status" << endl;
	cout << pname << "'s Rank: " << prank << endl;
	cout << pname << "'s Ship: " << psname << endl;
	cout << psname << "'s Status: " << psstatus << endl;

	if (psstatus == "Disabled")
	{
		cout << psname << "'s Downtime: " << psdt << endl;
	}

	cout << psname << "'s Shield Strength: " << ((pssp/psmsp)*100) << "% (" << pssp << " / " << psmsp << ")" << endl;
	cout << psname << "'s Armor Strength: " << ((psap/psmap)*100) << "% (" << psap << " / " << psmap << ")" << endl;
	cout << psname << "'s Hull Strength: " << ((pshp/psmhp)*100) << "% (" << pshp << " / " << psmhp << ")" << endl;
	mCScreen(true);
}

int msgProc::hBStatus(NPC& mNPC, int hostiles)
{
	bNTarget = true; //Set this to true to make sure the loop is entered
	i = 0;

	while (bNTarget)
	{
		if (i == 0)
		{
			if (mNPC.getStatus() == "Destroyed")
			{
				bIsTDest = true;
			}

			else
			{
				bIsTDest = false;
			}

			if (!bIsTDest)
			{
				//NPC information
				hname = mNPC.getName();
				hrank = mNPC.getRank();
				hsname = mNPC.Ship.getSName();
				hsclass = mNPC.Ship.getSClass();
				hssp = mNPC.Ship.getSShield();
				hsap = mNPC.Ship.getSArmor();
				hshp = mNPC.Ship.getSHull();
				hsmsp = mNPC.Ship.getSMShield();
				hsmap = mNPC.Ship.getSMArmor();
				hsmhp = mNPC.Ship.getSMHull();
				hsdt = 0;
				hsstatus = " ";

				if (mNPC.Ship.isDisabled())
				{
					hsstatus = "Disabled";
					hsdt = mNPC.Ship.getSDTimer();
				}

				else
				{
					hsstatus = "Green";
				}	
			}
		}

		else
		{
			if (mNPC.eWingmen.at(i-1).getStatus() == "Destroyed")
			{
				bIsTDest = true;
			}

			else
			{
				bIsTDest = false;
			}

			if (!bIsTDest)
			{
				hname = mNPC.eWingmen.at(i-1).getName();
				hrank = mNPC.eWingmen.at(i-1).getRank();
				hsname = mNPC.eWingmen.at(i-1).Ship.getSName();
				hsclass = mNPC.eWingmen.at(i-1).Ship.getSClass();
				hssp = mNPC.eWingmen.at(i-1).Ship.getSShield();
				hsap = mNPC.eWingmen.at(i-1).Ship.getSArmor();
				hshp = mNPC.eWingmen.at(i-1).Ship.getSHull();
				hsmsp = mNPC.eWingmen.at(i-1).Ship.getSMShield();
				hsmap = mNPC.eWingmen.at(i-1).Ship.getSMArmor();
				hsmhp = mNPC.eWingmen.at(i-1).Ship.getSMHull();
				hsdt = 0;
				hsstatus = " ";

				if (mNPC.eWingmen.at(i-1).Ship.isDisabled())
				{
					hsstatus = "Disabled";
					hsdt = mNPC.eWingmen.at(i-1).Ship.getSDTimer();
				}

				else
				{
					hsstatus = "Green";
				}	
			}
		}

		if (!bIsTDest)
		{
			//NPC Status
			cout << "Target " << i+1 << " of " << mNPC.getNOWingmen()+1 << endl; //Add 1 here to NOWingmen() because we want to treat the main npc as a target even through the rest of the code does not
			cout << hname << "'s Status" << endl;
			cout << hname << "'s Rank: " << hrank << endl;
			cout << hname << "'s Ship: " << hsname << endl;
			cout << hsname << "'s Status: " << hsstatus << endl;

			if (hsstatus == "Disabled")
			{
				cout << hsname << "'s Downtime: " << hsdt << endl;
			}

			cout << hsname << "'s Shield Strength: " << ((hssp/hsmsp)*100) << "% (" << hssp << " / " << hsmsp << ")" << endl;
			cout << hsname << "'s Armor Strength: " << ((hsap/hsmap)*100) << "% (" << hsap << " / " << hsmap << ")" << endl;
			cout << hsname << "'s Hull Strength: " << ((hshp/hsmhp)*100) << "% (" << hshp << " / " << hsmhp << ")" << endl;
			cout << endl << endl;

			cout << "Do you wish to target this vessle?" << endl;
			cout << "(Y/y)es/(N/n)o" << endl;
			cout << "> ";
			cin >> pCChoice;
			cout << endl << endl;

			switch(pCChoice)
			{
			case 'y':
			case 'Y':
				bNTarget = false;
				break;			

			default:

				if (i == hostiles -1) //If player has cycled through all of the hostiles
				{
					for (i2 = 0; i2 <= mNPC.getNOWingmen(); i2++) //Find first attackable ship and return the value
					{
						if (i == 0)
						{
							if (mNPC.getStatus() == "In Battle")
							{
								i = 0;
								bNTarget = false;
							}
						}

						else
						{
							if (mNPC.eWingmen.at(i-1).getStatus() == "In Battle")
							{
								bNTarget = false;
							}
						}
					}
				}

				break;
			}
		}

		else if (i < hostiles)
		{
			i =+ 1;
		}
	}

	return i;
}

void msgProc::hBStatus(NPC& target)
{
	//if (target.getStatus() != "Destroyed"
	//NPC information
	hname = target.getName();
	hrank = target.getRank();
	hsname = target.Ship.getSName();
	hsclass = target.Ship.getSClass();
	hssp = target.Ship.getSShield();
	hsap = target.Ship.getSArmor();
	hshp = target.Ship.getSHull();
	hsmsp = target.Ship.getSMShield();
	hsmap = target.Ship.getSMArmor();
	hsmhp = target.Ship.getSMHull();
	hsdt = 0;
	hsstatus = " ";

	if (target.Ship.isDisabled())
	{
		hsstatus = "Disabled";
		hsdt = target.Ship.getSDTimer();
	}

	else
	{
		hsstatus = "Green";
	}	


	cout << hname << "'s Status" << endl;
	cout << hname << "'s Rank: " << hrank << endl;
	cout << hname << "'s Ship: " << hsname << endl;
	cout << hsname << "'s Status: " << hsstatus << endl;

	if (hsstatus == "Disabled")
	{
		cout << hsname << "'s Downtime: " << hsdt << endl;
	}

	cout << hsname << "'s Shield Strength: " << ((hssp/hsmsp)*100) << "% (" << hssp << " / " << hsmsp << ")" << endl;
	cout << hsname << "'s Armor Strength: " << ((hsap/hsmap)*100) << "% (" << hsap << " / " << hsmap << ")" << endl;
	cout << hsname << "'s Hull Strength: " << ((hshp/hsmhp)*100) << "% (" << hshp << " / " << hsmhp << ")" << endl;
	mCScreen(true);
}

int msgProc::hBStatus_PB(Planet* gPlanet)
{
	for (i = 0; i < gPlanet->pDef.size(); i++)
	{
		if (gPlanet->pDef.at(i).getState() != "Destroyed")
		{
			//Defense information
			dname = gPlanet->pDef.at(i).getDName();
			//dtlevel = gPlanet->pDef.at(i).getDTLevel();
			dsp = gPlanet->pDef.at(i).getSPoints();
			dmsp = gPlanet->pDef.at(i).getMSPoints();
			//ds_mpdt = 0;
			//ds_mpstatus = " ";

			/*if (mNPC.Ship.isDisabled())
			{
				hsstatus = "Disabled";
				hsdt = mNPC.Ship.getSDTimer();
			}

			else
			{
				hsstatus = "Green";
			}
			*/


			//NPC Status
			cout << "Target " << i+1 << " of " << gPlanet->pDef.size() << endl;
			cout << dname << "'s Status" << endl << endl;

			/*if (hsstatus == "Disabled")
			{
			cout << hsname << "'s Downtime: " << hsdt << endl;
			}*/

			float dspp = ((dsp/dmsp)*100.0f);
			cout << dname << "'s Structural Integrity: " << dspp << "% (" << dsp << " / " << dmsp << ")" << endl;

			cout << endl << endl;

			cout << "Do you wish to target this defense?" << endl;
			cout << "(Y/y)es/(N/n)o" << endl;
			cout << "> ";
			cin >> pCChoice;
			cout << endl << endl;

			switch(pCChoice)
			{
			case 'y':
			case 'Y':
				return i;
				break;			

			default:
				if (i == gPlanet->pDef.size()-1) //If player has cycled through all of the defenses
				{
					i = 0; //return to beginning of loop 
				}

				break;
			}
		}
	}
}

void msgProc::hBSStatus_PB(Planet* gPlanet, bool shield, int sID, bool defense, int dID, bool planet)
{
	if (shield)
	{
		//Defense information
		mname = gPlanet->pShd.at(sID).getMName();
		mtlevel = gPlanet->pShd.at(sID).getTLevel();
		msp = gPlanet->pShd.at(sID).getSP();
		mmsp = gPlanet->pShd.at(sID).getMSP();
		spr = gPlanet->pShd.at(sID).getSPRgn();
		mstat = gPlanet->pShd.at(sID).isDisabled();

		if (mstat)
		{
			dtimer = gPlanet->pShd.at(sID).getSDTimer();
			mstats = "Disabled";
		}

		else
		{
			mstats = "Active";
		}

		//NPC Status
		cout << mname << "'s Status" << endl << endl;

		float mspp = ((msp/mmsp)*100.0f);
		cout << mname << "'s Strength Points: " << mspp << "% (" << msp << " / " << mmsp << ")" << endl;
		cout << mname << "'s Technology Level: " << mtlevel << endl;
		cout << mname << "'s Shield Regeneration Rate: " << spr << endl;
		cout << mname << "'s State: " << mstats << endl;

		if (mstat)
		{
			cout << mname << " is disabled for " << dtimer << " turns." << endl;
		}

		mCScreen(true);
	}

	else if (defense)
	{
		//Defense information
		dname = gPlanet->pDef.at(dID).getDName();
		dtlevel = gPlanet->pDef.at(dID).getDTLevel();
		dsp = gPlanet->pDef.at(dID).getSPoints();
		dmsp = gPlanet->pDef.at(dID).getMSPoints();
		dstat = gPlanet->pDef.at(dID).getState();

		//NPC Status
		cout << dname << "'s Status" << endl << endl;

		float dspp = ((dsp/dmsp)*100.0f);
		cout << dname << "'s Structural Integrity: " << dspp << "% (" << dsp << " / " << dmsp << ")" << endl;
		cout << dname << "'s Technology Level: " << dtlevel << endl;
		cout << dname << "'s State: " << dstat << endl;
		mCScreen(true);
	}

	else if (planet)
	{
		plname = gPlanet->getName();
		peks = gPlanet->getEKS();
		plsize = gPlanet->getSize();
		ndef = gPlanet->pDef.size();
		nshd = gPlanet->pShd.size();
		ppop = (float)gPlanet->getPop();
		pmpop = (float)gPlanet->getMPop();

		cout << plname << "'s Status" << endl << endl;

		cout << plname << "'s EKS Rating: " << peks << endl;
		cout << plname << "'s Size: " << plsize << endl;
		cout << plname << " has " << ndef << " defensive structures" << endl;
		cout << plname << " has " << nshd << " planetary shields" << endl;

		float ppopp = ((ppop/pmpop)*100.00f);
		cout << plname << "'s Population: " << ppopp << "% (" << ppop << " / " << pmpop << ")" << endl;

		mCScreen(true);
	}
}

bool msgProc::bHail1(string affiliation, string race, int affinity)
{
	//TODO: create multiple race/affinity messages in order to fit in with dialog choices

	/*if (race == "Humanoid")
	{
		if (affiliation == "Earth Alliance")
		{*/

	hSRate = Random(1,300);

			if (affinity >= 26)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(47,50)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(57,60)) << endl;
						return false;
					}
				}

				else if ((affinity < 25) && (affinity > -22))
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(67,70)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(77,80)) << endl;
						return false;
					}
				}

				else if (affinity <= -23)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(87,90)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(97,100)) << endl;
						return false;
					}
				}
		/*}

		else if (affiliation == "")
		{

		}
	}

	else if (race == "Sluikan")
	{

	}

	else if (race == "Juslorth")
	{

	}

	else if (race == "Visar")
	{

	}

	else if (race == "Adent")
	{

	}

	else if (race == "Prokl")
	{

	}

	else if (race == "Groz")
	{

	}*/
}

int msgProc::bHail2(int affinity)
{
	cout << mRMessage(1) << endl;
	cout << "1) Ask for Information" << endl;
	
	if (affinity >= 78)
	{
		cout << "2) Check for enemies in the area" << endl;
	}

	if (affinity <= -74)
	{
		cout << "3) Demand surrender" << endl;
	}

	cout << "4) Ask for trade" << endl;
	cout << "5) Nothing" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl;
	cout << endl;

	if (pChoice < 1 || pChoice > 5 || ((pChoice == 2) && (affinity < 78)) || ((pChoice == 3) && (affinity > -74)))
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	mCScreen(true);
	return pChoice;
}

bool msgProc::bHail3(int affinity, int pChoice, string race, string affil)
{
	/*if (race == "Human")
	{
		if (affil == "Earth Alliance")
		{*/
			hSRate = Random(1,200);

			switch(pChoice)
			{
			case 1:
				if (affinity >= 26)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(107,109)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(117,118)) << endl;
						return false;
					}
				}

				else if ((affinity < 25) && (affinity > -22))
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(127,128)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(137,139)) << endl;
						return false;
					}
				}

				else if (affinity <= -23)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(147,148)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(157,159)) << endl;
						return false;
					}
				}

				break;

			case 2:
				if (affinity >= 26)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(167,169)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(177,178)) << endl;
						return false;
					}
				}

				else if ((affinity < 25) && (affinity > -22))
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(187,188)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(197,199)) << endl;
						return false;
					}
				}

				else if (affinity <= -23)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(207,208)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(217,219)) << endl;
						return false;
					}
				}

				break;

			case 3:
				if (affinity >= 26)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(227,229)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(237,238)) << endl;
						return false;
					}
				}

				else if ((affinity < 25) && (affinity > -22))
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(247,248)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(257,259)) << endl;
						return false;
					}
				}

				else if (affinity <= -23)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(267,268)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(277,279)) << endl;
						return false;
					}
				}

				break;

			case 4:
				if (affinity >= 26)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(287,289)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(297,298)) << endl;
						return false;
					}
				}

				else if ((affinity < 25) && (affinity > -22))
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(307,308)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(317,319)) << endl;
						return false;
					}
				}

				else if (affinity <= -23)
				{
					if (hSRate * 10 / 5 < 360)
					{
						cout << mRMessage(Random(327,328)) << endl;
						return true;
					}

					else
					{
						cout << mRMessage(Random(337,339)) << endl;
						return false;
					}
				}

				break;

			case 5:
				if (affinity >= 26)
				{
					cout << mRMessage(Random(347,351)) << endl;
					return true;
				}

				else if ((affinity < 25) && (affinity > -22))
				{					
					cout << mRMessage(Random(367,371)) << endl;
					return true;
				}

				else if (affinity <= -23)
				{
					cout << mRMessage(Random(397,401)) << endl;
					return true;
				}

				break;
			}
	/*	}
	}

	else if (race == "Sluikan")
	{

	}

	else if (race == "Juslorth")
	{

	}

	else if (race == "Visar")
	{

	}

	else if (race == "Adent")
	{

	}

	else if (race == "Prokl")
	{

	}

	else if (race == "Groz")
	{

	}*/
}

bool msgProc::bNHail1()
{
	cout << mRMessage(2002) << endl;
	cout << "1) Ignore it" << endl;
	cout << "2) Answer the hail" << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice >= 2)
	{
		cout << mRMessage(5) << endl;
		mCScreen(true);
		return true;
	}

	else if (pChoice == 1)
	{
		mCScreen(true);
		return false;
	}
}

bool msgProc::bNHDemand()
{
	cout << mRMessage(2005) << endl;
	cout << "1) Tell them to go to hell" << endl;
	cout << "2) Accept their terms..." << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice >= 2)
	{
		cout << mRMessage(5) << endl;
		mCScreen(true);
		return true;
	}

	else if (pChoice == 1)
	{
		mCScreen(true);
		return false;
	}
}

bool msgProc::bNHSurrender()
{
	cout << mRMessage(2006) << endl;
	cout << "1) Ask them to retransmit their message" << endl;
	cout << "2) Demand that they cease hostile activities and prepare to be boarded" << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice >= 2)
	{
		cout << mRMessage(5) << endl;
		mCScreen(true);
		return true;
	}

	else if (pChoice == 1)
	{
		mCScreen(true);
		return false;
	}
}

int msgProc::bPSurrender(int ransom[])
{
	cout << mRMessage(1000) << endl;
	cout << "Ransom:" << endl;

	for (i = 0; i < 9; i++)
	{
		if (ransom[i] != 0)
		{
			switch(i)
			{
			case 0:
				cout << "Xarn: " << ransom[i] << endl;
				break;

			case 1:
				cout << "Rubies: " << ransom[i] << endl;
				break;

			case 2:
				cout << "Diamonds: " << ransom[i] << endl;
				break;

			case 3:
				cout << "Draconic: " << ransom[i] << endl;
				break;

			case 4:
				cout << "Lithium: " << ransom[i] << endl;
				break;

			case 5:
				cout << "Platinum: " << ransom[i] << endl;
				break;

			case 6:
				cout << "Uranium: " << ransom[i] << endl;
				break;

			case 7:
				cout << "Plutonium: " << ransom[i] << endl;
				break;

			case 8:
				cout << "Nuclear Waste: " << ransom[i] << endl;
				break;
			}
		}
	}

	cout << endl;
	cout << endl;

	cout << "Pay the ransom?" << endl;
	cout << "(y)es/(n)o:>";
	cin >> pCChoice;

	if (pCChoice == 'y' || pCChoice == 'Y')
	{
		mCScreen(true);
		return 1;
	}

	else
	{
		mCScreen(true);
		return 0;
	}
}


void msgProc::bHInfo(int affinity, string race)
{

}

void msgProc::bHEnemies(string race)
{

}

void msgProc::bHSurrender(int affinity, string race)
{

}

int msgProc::bHTrade()
{
	return 0;
}

void msgProc::bHNothing()
{

}

//Damage Outputs
void msgProc::dDamage1S(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s shields." << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s shields." << endl << endl;
	}
}

void msgProc::dDamage1SA(float dam1, float dam2, bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has done " << dam1 << " damage to " << bTarget.entity->getName() << "'s shields.  " << dam2 << " damage has spilled over onto " << bTarget.entity->getName() << "'s armor." << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has done " << dam1 << " damage to " << bTarget.entity->getName() << "'s shields.  " << dam2 << " damage has spilled over onto " << bTarget.entity->getName() << "'s armor." << endl << endl;
	}
}

void msgProc::dDamage1A(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s armor." << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s armor." << endl << endl;
	}
}

void msgProc::dDamage1AH(float dam1, float dam2, bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has done " << dam1 << " damage to " << bTarget.entity->getName() << "'s armor.  " << dam2 << " damage has spilled over onto " << bTarget.entity->getName() << "'s hull." << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has done " << dam1 << " damage to " << bTarget.entity->getName() << "'s armor.  " << dam2 << " damage has spilled over onto " << bTarget.entity->getName() << "'s hull." << endl << endl;
	}
}

void msgProc::dDamage1H(float dam, bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s hull." << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has done " << dam << " damage to " << bTarget.entity->getName() << "'s hull." << endl << endl;
	}
}

void msgProc::dDamage1H_K(bEntity& bAttacker, bEntity& bTarget, bool defense)
{
	if (!defense)
	{
		cout << bAttacker.entity->getName() << " has destroyed " << bTarget.entity->getName() << "'s ship! " << endl << endl;
	}

	else
	{
		cout << bAttacker.pDefense->getDName() << " has destroyed " << bTarget.entity->getName() << "'s ship! " << endl << endl;
	}
}

void msgProc::dDamage2S(float dam, bEntity& bAttacker, bEntity& bTarget, Planet* planet)
{
	cout << bAttacker.entity->getName() << " has done " << dam << " damage to " << planet->getName() << "'s " << bTarget.pShield->getMName() << " planetary shield system." << endl << endl;
}

void msgProc::dDamage2D(float dam, bEntity& bAttacker, bEntity& bTarget, Planet* planet)
{
	cout << bAttacker.entity->getName() << " has done " << dam << " damage to " << planet->getName() << "'s " << bTarget.pDefense->getDName() << " planetary defense system." << endl << endl;
}

void msgProc::dDamage2D_K(bEntity& bAttacker, bEntity& bTarget, Planet* planet)
{
	cout << bAttacker.entity->getName() << " has destroyed " << planet->getName() << "'s " << bTarget.pDefense->getDName() << " planetary defense system!" << endl << endl;
}

void msgProc::dDamage2P(float dam, bEntity& bAttacker, bEntity& bTarget)
{
	cout << bAttacker.entity->getName() << " has killed " << dam << " of " << bTarget.bPlanet->getName() << "'s " << "population." << endl << endl;
}

void msgProc::dDamage2P_K(bEntity& bAttacker, bEntity& bTarget)
{
	cout << bAttacker.entity->getName() << " has wiped " << bTarget.bPlanet->getName() << " of inhabitants." << endl << endl;
}

void msgProc::dPSDisabled(Planet* planet, bEntity& bTarget, int turns)
{
	cout << planet->getName() << "'s " << bTarget.pShield->getMName() << " planetary shield system has collapsed and will not regenerate for " << turns << " turn(s)." << endl << endl;
}

void msgProc::dSDInflicted(bEntity& bAttacker, bEntity& bTarget, string dType, int turns)
{
	cout << bAttacker.entity->getName() << "  has inflicted " << bTarget.entity->getName() << " with " << dType << " damage for the next " << turns << "turn(s)." << endl << endl;
}

void msgProc::dSDamageS(float dam, string dType, bEntity& bTarget)
{
	cout << bTarget.entity->getName() << " has suffered " << dam << " damage to their shields caused by " << dType << "." << endl << endl;
}

void msgProc::dBonus(float dam1, float dam2, string dType, bEntity& bAttacker)
{
	cout << "ALERT: Damage from " << bAttacker.entity->getName() << " has increased from " << dam1 << "to " << dam1+dam2 << " due to damage bonuses associated with " << dType << " type damage." << endl << endl;
}

void msgProc::dSDisabled(bEntity& bTarget, int turns)
{
	cout << "An EM pulse has disabled " << bTarget.entity->getName() << "'s ship for " << turns << " turn(s)." << endl << endl;
}

void msgProc::dSSDisabled(bEntity& bTarget, int turns)
{
	cout << "An EM pulse has disabled " << bTarget.entity->getName() << "'s shields for " << turns << " turn(s)." << endl << endl;
}

void msgProc::dSDamageSA(float dam1, float dam2, string dType, bEntity& bTarget)
{
	cout << bTarget.entity->getName() << " has suffered " << dam1 << " damage to their shields caused by " << dType << ".  " << dam2 << " damage has spilled over onto their armor." << endl << endl;
}

void msgProc::dSDamageA(float dam, string dType, bEntity& bTarget)
{
	cout << bTarget.entity->getName() << " has suffered " << dam << " damage to their armor caused by " << dType << "." << endl << endl;
}

void msgProc::dSDamageAH(float dam1, float dam2,  string dType, bEntity& bTarget)
{
	cout << bTarget.entity->getName() << " has suffered " << dam1 << " damage to their armor caused by " << dType << ".  " << dam2 << " damage has spilled over onto their hull." << endl << endl;
}

void msgProc::dSDamageH(float dam, string dType, bEntity& bTarget)
{
	cout << bTarget.entity->getName() << " has suffered " << dam << " damage to their hull caused by " << dType << "." << endl << endl;
}


//Station Menus
int msgProc::sMMenu(Station& stat)
{
	
	cout << "Welcome to " << stat.getName() << " Station." << endl;

	sCRand = (1,50);
	mRand = (1,10); //Temporary value range, get real range once we add in the station price change reasons; will be dependent on in-game vents and the value of sCRand in next version
	  
	//if (sCRand >= 10 || sCRand <= 35)
	//{
	//    cout << "Please note that due to " << mRMessage(mRand) << " our prices have been changed.  The current sales rate is " << stat.getCMulti() << "%." << endl;
	//}	

	cout << mRMessage(1) << endl;
	cout << "1) Repair Docks" << endl;
	cout << "2) Station Emporium" << endl;
	cout << "3) Bar" << endl;
	cout << "4) Bounty Office" << endl;	
	if (!stat.bIsEAEnemy())
	{
	cout << "5) Earth Alliance Field Office" << endl;
	}
	cout << "6) E-Med Facility" << endl;
	cout << "7) Casino" << endl;
	cout << "8) Store an item" << endl;
	cout << "9) Get an item from storage" << endl;
	cout << "10) Depart" << endl;
	cout << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	
	if (pChoice < 1 || pChoice > 10)
	{		
		cout << mRMessage(5) << endl << endl;
		pChoice = 1;
	}

	else if (stat.bIsEAEnemy())
	{
		if (pChoice == 5)
		{
			cout << "This station is currently enemies with the Earth Alliance.  Defaulting to the first menu option..." << endl;
			pChoice = 1;
		}
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMCMenu(Player& mPlayer)
{
	psclass = mPlayer.Ship.getSClass();

	bContinue = true;

	while (bContinue)
	{
		cout << mRMessage(2027) << endl << endl;

		cout << "1) Frigate" << endl;
		cout << "2) Destroyer" << endl;
		cout << "3) Cruiser" << endl;
		cout << "4) Battle Cruiser" << endl;
		cout << "5) Battleship" << endl;
		cout << "6) Mothership" << endl;
		cout << "8) Titan" << endl;		
		cout << "9) Back to station menu" << endl;
		cout << ">";
		cin >> pChoice;
		cout << endl;

		if (pChoice < 1 || pChoice > 9)
		{
			cout << mRMessage(2025) << endl;
			pChoice = 9;
			bContinue = false;
		}

		else if (((psclass == "Frigate") && (pChoice >= 2)) || ((psclass == "Destroyer") && (pChoice >= 3)) || ((psclass == "Cruiser") && (pChoice >= 4)) || ((psclass == "Battlecruiser") && (pChoice >= 5)) || ((psclass == "Battleship") && (pChoice >= 6)) || ((psclass == "Mothership") && (pChoice >= 7)))
		{
			cout << mRMessage(2026) << " (Y/y)es or (N/n)o" << endl;
			cout << ">";
			cin >> pCChoice;

			switch(pCChoice)
			{
			case 'y':
			case 'Y':
				bContinue = false;
				break;

			default:
				break;
			}
		}

		else
		{
			bContinue = false;
		}
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMBS()
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl;
	cout << "1) Buy" << endl;
	cout << "2) Sell" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	mCScreen(true);
	return pChoice;
}
	  
int msgProc::sMMenu1A()
{
	cout << mRMessage(1) << endl;
	cout << "1) Weapons" << endl;
	cout << "2) Ships" << endl;
	cout << "3) Modules" << endl;
	cout << "4) Back to station menu" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 5)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMMenu1B1()
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2035) << endl << endl;
	cout << mRMessage(2036) << endl << endl;
	cout << "1) Weapons, equipment, or resources" << endl;
	cout << "2) Ship" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMMenu1B2()
{
	cout << mRMessage(2037) << endl;
	cout << mRMessage(2036) << endl << endl;
	cout << "1) Ship" << endl;
	cout << "2) Station" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMMenu1C1(Player& mPlayer, string iType)
{
	bValid = false;
	nOShips = 0;
	pSCSize = mPlayer.Ship.sCargo.size();

	if (iType == "Ship")
	{
		while (!bValid)
		{
			cout << mRMessage(1) << endl;

			for (i = 0; i <= pSCSize; i++)
			{
				if ((i == pSCSize) && (nOShips == 0))
				{
					cout << "There are no ships in your cargohold.  Ending sell proceedures." << endl;
					pChoice = -1;
					bValid = true;
					break;
				}

				else if ((i == pSCSize) && (nOShips > 0))
				{
					break;
				}

				else if (iType == mPlayer.Ship.sCargo.at(i).getIType())
				{
					ds_mp.rData("Ship_Data","select from",mPlayer.Ship.sCargo.at(i).getIID());

					cout << i+1 << ") " << ds_mp.getSName() << endl;
					nOShips += 1;
				}
			}

			if (!bValid)
			{
				cout << ">";
				cin >> pChoice;
				cout << endl << endl;

				if (mPlayer.Ship.sCargo.at(pChoice-1).getIType() != "Ship")
				{
					cout << mRMessage(2038) << endl;
					mCScreen(true);
				}

				else
				{
					pChoice -= 1;
					bValid = true;
				}
			}			
		}
	}

	else
	{
		while(!bValid)
		{
			cout << mRMessage(1) << endl;

			for (i = 0; i < pSCSize; i++)
			{
				if (mPlayer.Ship.sCargo.at(i).getIType() != "Ship")
				{
					if (mPlayer.Ship.sCargo.at(i).getIType() == "PShield" || mPlayer.Ship.sCargo.at(i).getIType() == "PDefense")
					{
						ds_mp.rData("Equipment_Data","select from",mPlayer.Ship.sCargo.at(i).getIID());

						cout << i+1 << ") " << ds_mp.getEName() << endl;
					}

					else if (mPlayer.Ship.sCargo.at(i).getIType() == "Resource")
					{
						ds_mp.rData("Resource","select from",mPlayer.Ship.sCargo.at(i).getIID());

						cout << i+1 << ") " << ds_mp.getResName() << endl;
					}

					else if (mPlayer.Ship.sCargo.at(i).getIType() == "Ore")
					{
						ds_mp.rData("Ore","select from",mPlayer.Ship.sCargo.at(i).getIID());

						cout << i+1 << ") " << ds_mp.getOName() << endl;
					}

					else if (mPlayer.Ship.sCargo.at(i).getIType() == "Weapon")
					{
						ds_mp.rData("Ore","select from",mPlayer.Ship.sCargo.at(i).getIID());

						cout << i+1 << ") " << ds_mp.getOName() << endl;
					}
				}
			}

			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			if (mPlayer.Ship.sCargo.at(pChoice-1).getIType() == "Ship")
			{
				cout << "You have chosen a ship, please pick a non-ship item or change the item class you are selling." << endl;
				mCScreen(true);
			}

			else
			{
				pChoice -= 1;
				bValid = true;
			}
		}
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::sMMenu1C2(Station& stat_g, string iType)
{
	bValid = false;
	nOShips = 0;
	sISize = stat_g.sInventory.size();

	if (iType == "Ship")
	{
		while (!bValid)
		{
			cout << mRMessage(1) << endl;

			if (sSSize == 0)
			{
				cout << "There are no ships in your station inventory.  Ending sell proceedures." << endl;
				pChoice = -1;
				bValid = true;				
			}

			else
			{
				for (i = 0; i <= sISize; i++)
				{				
					if (stat_g.sInventory.at(i).isShip())
					{
						cout << i+1 << ") " << stat_g.sInventory.at(i).sShip.getSName() << endl;
						nOShips += 1;
					}
				}
			}

			if (!bValid)
			{
				cout << ">";
				cin >> pChoice;
				cout << endl << endl;
				
				pChoice -= 1;
				bValid = true;
			}			
		}
	}

	else
	{
		while(!bValid)
		{
			cout << mRMessage(1) << endl;

			for (i = 0; i < sISize; i++)
			{
				if (stat_g.sInventory.at(i).getIType() == "PShield" || stat_g.sInventory.at(i).getIType() == "PDefense")
				{
					ds_mp.rData("Equipment_Data","select from",stat_g.sInventory.at(i).getIID());

					cout << i+1 << ") " << ds_mp.getEName() << endl;
				}

				else if (stat_g.sInventory.at(i).getIType() == "Resource")
				{
					ds_mp.rData("Resource","select from",stat_g.sInventory.at(i).getIID());
				
					cout << i+1 << ") " << ds_mp.getResName() << endl;					
				}

				else if (stat_g.sInventory.at(i).getIType() == "Ore")
				{
					ds_mp.rData("Ore","select from",stat_g.sInventory.at(i).getIID());
				
					cout << i+1 << ") " << ds_mp.getOName() << endl;					
				}
			}

			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			pChoice -= 1;
			bValid = true;
		}
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::mSSIAmount(int amount)
{
	bValid = false;

	if (amount > 1)
	{
		while (!bValid)
		{
			cout << "Detected stacked item.  Please choose how many items you wish to work with out of a total of " << amount << ":" << endl << endl;
			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			if (pChoice < 1 || pChoice > amount)
			{
				cout << mRMessage(2039) << amount << "." << endl;
				mCScreen(true);
			}

			else
			{
				bValid = true;
			}
		}
	}

	else
	{
		pChoice = 1;
	}

	mCScreen(true);
	return pChoice;
}

int msgProc::mSSIConfirm(int amount, int iID, string iType)
{
	if (iType == "Ship")
	{
		ds_mp.rData("Ship_Data", "select from", iID);

		xCost = ds_mp.getSXC() * 0.25f * amount;
		rCost = ds_mp.getSRC() * 0.25f * amount;
		diCost = ds_mp.getSDiC() * 0.25f * amount;
		dCost = ds_mp.getSDC() * 0.25f * amount;
		uCost = ds_mp.getSUC() * 0.25f * amount;
		pluCost = ds_mp.getSPC() * 0.25f * amount;

		cout << mRMessage(2040) << amount << mRMessage(2041) << ds_mp.getSName() << mRMessage(2042) << endl << endl;
		cout << "You will get:" << endl;
		cout << "Xarn: " << xCost << endl;
		cout << "Rubies: " << rCost << endl;
		cout << "Diamonds: " << diCost << endl;
		cout << "Draconic: " << dCost << endl;
		cout << "Uranium: " << uCost << endl;
		cout << "Plutonium: " << pluCost << endl << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "PShield" || iType == "PDefense")
	{
		ds_mp.rData("Equipment_Data", "select from", iID);

		xCost = ds_mp.getEXC() * 0.25f * amount;
		rCost = ds_mp.getERC() * 0.25f * amount;
		diCost = ds_mp.getEDiC() * 0.25f * amount;
		dCost = ds_mp.getEDC() * 0.25f * amount;
		lCost = ds_mp.getELC() * 0.25f * amount;
		uCost = ds_mp.getEUC() * 0.25f * amount;
		pluCost = ds_mp.getEPC() * 0.25f * amount;

		cout << mRMessage(2040) << amount << mRMessage(2041) << ds_mp.getEName() << mRMessage(2042) << endl << endl;
		cout << "You will get:" << endl;
		cout << "Xarn: " << xCost << endl;
		cout << "Rubies: " << rCost << endl;
		cout << "Diamonds: " << diCost << endl;
		cout << "Draconic: " << dCost << endl;
		cout << "Lithium: " << lCost << endl;
		cout << "Uranium: " << uCost << endl;
		cout << "Plutonium: " << pluCost << endl << endl;


		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Resource")
	{
		ds_mp.rData("Resource", "select from", iID);

		xCost = ds_mp.getResXCost() * 0.25f * amount;

		cout << mRMessage(2040) << amount << mRMessage(2041) << ds_mp.getResName() << mRMessage(2042) << endl << endl;
		cout << "You will get:" << endl;
		cout << "Xarn: " << xCost << endl << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Ore")
	{
		ds_mp.rData("Ore", "select from", iID);

		xCost = ds_mp.getOXCost() * 0.25f * amount;

		cout << mRMessage(2040) << amount << mRMessage(2041) << ds_mp.getOName() << mRMessage(2042) << endl << endl;
		cout << "You will get:" << endl;
		cout << "Xarn: " << xCost << endl << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Weapon")
	{
		ds_mp.rData("Weapon_Data", "select from", iID);

		xCost = ds_mp.getWXC() * 0.25f * amount;
		rCost = ds_mp.getWRC() * 0.25f * amount;
		diCost = ds_mp.getWDiC() * 0.25f * amount;
		dCost = ds_mp.getWDC() * 0.25f * amount;
		lCost = ds_mp.getWLC() * 0.25f * amount;
		uCost = ds_mp.getWUC() * 0.25f * amount;
		pluCost = ds_mp.getWPC() * 0.25f * amount;

		cout << mRMessage(2040) << amount << mRMessage(2041) << ds_mp.getWName() << mRMessage(2042) << endl << endl;
		cout << "You will get:" << endl;
		cout << "Xarn: " << xCost << endl;
		cout << "Rubies: " << rCost << endl;
		cout << "Diamonds: " << diCost << endl;
		cout << "Draconic: " << dCost << endl;
		cout << "Lithium: " << lCost << endl;
		cout << "Uranium: " << uCost << endl;
		cout << "Plutonium: " << pluCost << endl << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	switch(pCChoice)
	{
	case 'Y':
	case 'y':
		mCScreen(true);
		return 1;
		break;

	default:
		mCScreen(true);
		return 0;
		break;
	}
}

int msgProc::mSTIConfirm(int amount, int iID, string iType)
{
	if (iType == "Ship")
	{
		ds_mp.rData("Ship_Data", "select from", iID);

		cout << "Are you sure you want to store " << amount << " of " << ds_mp.getSName() << "?" << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "PShield" || iType == "PDefense")
	{
		ds_mp.rData("Equipment_Data", "select from", iID);

		cout << "Are you sure you want to store " << amount << " of " << ds_mp.getEName() << "?" << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Resource")
	{
		ds_mp.rData("Resource", "select from", iID);

		cout << "Are you sure you want to store " << amount << " of " << ds_mp.getResName() << "?" << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Ore")
	{
		ds_mp.rData("Ore", "select from", iID);

		cout << "Are you sure you want to store " << amount << " of " << ds_mp.getOName() << "?" << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	else if (iType == "Weapon")
	{
		ds_mp.rData("Weapon_Data", "select from", iID);

		cout << "Are you sure you want to store " << amount << " of " << ds_mp.getWName() << "?" << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		cout << endl << endl;
	}

	switch(pCChoice)
	{
	case 'Y':
	case 'y':
		mCScreen(true);
		return 1;
		break;

	default:
		mCScreen(true);
		return 0;
		break;
	}
}

int msgProc::sMMenu2()
{
	cout << mRMessage(1) << endl;
	cout << "1) Lasers" << endl;
	cout << "2) Missiles" << endl;
	cout << "3) Bombs" << endl;
	cout << "4) Heavy Weapons" << endl;
	cout << "5) Railguns" << endl;
	cout << "6) Back to market menu" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl;

	if (pChoice < 1 || pChoice > 6)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::sWLMenu(int cCode)
{
	bContinue = true; //Make sure this is set to true

	i = 1; //Set i to 1 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1)
		{
			cout << "Frigate Class Lasers:" << endl << endl;

			for (; i <= 5; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2)
		{
			cout << "Destroyer Class Lasers:" << endl << endl;

			for (; i <= 12; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3)
		{
			cout << "Cruiser Class Lasers:" << endl << endl;

			for (; i <= 18; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruiser Class Lasers:" << endl << endl;

			for (; i <= 21; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5)
		{
			cout << "Battleship Class Lasers:" << endl << endl;

			for (; i <= 25; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6)
		{
			cout << "Mothership Class Lasers:" << endl << endl;

			for (; i <= 27; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Titan
		if (cCode == 7)
		{
			cout << "Titan Class Lasers:" << endl << endl;

			for (; i <= 30; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}
		}

		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 1 || pChoice > 5)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 1 || pChoice > 12)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 1 || pChoice > 18)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 1 || pChoice > 21)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 1 || pChoice > 25)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 1 || pChoice > 27)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 1 || pChoice > 30)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice;
}

int msgProc::sWMMenu(int cCode)
{
	bContinue = true; //Make sure this is set to true

	i = 31; //Set i to 32 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1)
		{
			cout << "Frigate Class Missiles:" << endl << endl;

			for (; i <= 37; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2)
		{
			cout << "Destroyer Class Missiles:" << endl << endl;

			for (; i <= 44; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3)
		{
			cout << "Cruiser Class Missiles:" << endl << endl;

			for (; i <= 50; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruiser Class Missiles:" << endl << endl;

			for (; i <= 55; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5)
		{
			cout << "Battleship Class Missiles:" << endl << endl;

			for (; i <= 65; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6)
		{
			cout << "Mothership Class Missiles:" << endl << endl;

			for (; i <= 87; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Titan
		if (cCode == 7)
		{
			cout << "Titan Class Missiles:" << endl << endl;

			for (; i <= 101; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}
		}

		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 31 || pChoice > 37)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 31 || pChoice > 44)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 31 || pChoice > 50)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 31 || pChoice > 55)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 31 || pChoice > 65)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 31 || pChoice > 87)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 31 || pChoice > 101)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice;
}

int msgProc::sWBMenu(int cCode)
{
	bContinue = true; //Make sure this is set to true

	i = 102; //Set i to 32 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1)
		{
			cout << "Frigate Class Bombs:" << endl << endl;

			for (; i <= 105; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2)
		{
			cout << "Destroyer Class Bombs:" << endl << endl;

			for (; i <= 110; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3)
		{
			cout << "Cruiser Class Bombs:" << endl << endl;

			for (; i <= 113; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruiser Class Bombs:" << endl << endl;

			for (; i <= 117; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5)
		{
			cout << "Battleship Class Bombs:" << endl << endl;

			for (; i <= 121; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6)
		{
			cout << "No weapons currently available for this class" << endl << endl;
		}

		//Titan
		if (cCode == 7)
		{
			cout << "Titan Class Bombs:" << endl << endl;

			for (; i <= 125; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}
		}

		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 31 || pChoice > 37)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 31 || pChoice > 44)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 31 || pChoice > 50)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 31 || pChoice > 55)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 31 || pChoice > 65)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 31 || pChoice > 87)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 31 || pChoice > 101)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice;
}

int msgProc::sWRMenu(int cCode)
{
	/*bContinue = true; //Make sure this is set to true

	i = 102; //Set i to 32 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1)
		{
			cout << "Frigate Class Bombs:" << endl << endl;

			for (; i <= 105; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2)
		{
			cout << "Destroyer Class Bombs:" << endl << endl;

			for (; i <= 110; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3)
		{
			cout << "Cruiser Class Bombs:" << endl << endl;

			for (; i <= 113; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruiser Class Bombs:" << endl << endl;

			for (; i <= 117; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5)
		{
			cout << "Battleship Class Bombs:" << endl << endl;

			for (; i <= 121; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6)
		{
			cout << "No weapons currently available for this class" << endl << endl;
		}

		//Titan
		if (cCode == 7)
		{
			cout << "Titan Class Bombs:" << endl << endl;

			for (; i <= 125; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}
		}

		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 31 || pChoice > 37)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 31 || pChoice > 44)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 31 || pChoice > 50)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 31 || pChoice > 55)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 31 || pChoice > 65)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 31 || pChoice > 87)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 31 || pChoice > 101)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice;*/

	cout << "We currently do not have any weapons of this type." << endl;

	return 0;
}

int msgProc::sWHMenu(int cCode)
{
	/*bContinue = true; //Make sure this is set to true

	i = 102; //Set i to 32 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1)
		{
			cout << "Frigate Class Bombs:" << endl << endl;

			for (; i <= 105; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2)
		{
			cout << "Destroyer Class Bombs:" << endl << endl;

			for (; i <= 110; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3)
		{
			cout << "Cruiser Class Bombs:" << endl << endl;

			for (; i <= 113; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruiser Class Bombs:" << endl << endl;

			for (; i <= 117; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5)
		{
			cout << "Battleship Class Bombs:" << endl << endl;

			for (; i <= 121; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6)
		{
			cout << "No weapons currently available for this class" << endl << endl;
		}

		//Titan
		if (cCode == 7)
		{
			cout << "Titan Class Bombs:" << endl << endl;

			for (; i <= 125; i++)
			{
				ds_mp.rData("Weapon_Data","select from",i);

				cout << i << ") " << ds_mp.getWName() << endl;
			}
		}

		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 31 || pChoice > 37)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 31 || pChoice > 44)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 31 || pChoice > 50)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 31 || pChoice > 55)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 31 || pChoice > 65)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 31 || pChoice > 87)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 31 || pChoice > 101)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice; */

	cout << "We currently do not have any weapons of this type." << endl;

	return 0;
}

int msgProc::sMMenu8(int cCode)
{
	bContinue = true; //Make sure this is set to true

	i = 1; //Set i to 32 here so that we are using actual item ids.  Part of the all class types into one function approach but very messy

	while (bContinue)
	{
		cout << mRMessage(1) << endl;	
		cout << mRMessage(2036) << endl << endl;

		//Frigate
		if (cCode >= 1) //External value flag: condition value
		{
			cout << "Frigates:" << endl << endl;

			for (; i <= 5; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Destroyer
		if (cCode >= 2) //External value flag: condition value
		{
			cout << "Destroyers:" << endl << endl;

			for (; i <= 10; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Crusier
		if (cCode >= 3) //External value flag: condition value
		{
			cout << "Cruisers:" << endl << endl;

			for (; i <= 16; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Battlecrusier
		if (cCode >= 4)
		{
			cout << "Battlecruisers:" << endl << endl;

			for (; i <= 21; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Battleship
		if (cCode >= 5) //External value flag: condition value
		{
			cout << "Battleships:" << endl << endl;

			for (; i <= 26; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Mothership
		if (cCode >= 6) //External value flag: condition value
		{
			cout << "Command/Motherships:" << endl << endl;

			for (; i <= 35; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}

			cout << endl;
		}

		//Titan
		if (cCode == 7) //External value flag: condition value
		{
			cout << "Titans:" << endl << endl;

			for (; i <= 43; i++) //External value flag: condition value
			{
				ds_mp.rData("Ship_Data","select from",i);

				cout << i << ") " << ds_mp.getSName() << endl;
			}
		}		

		cout << "> ";
		cin >> pChoice;

		cout << endl;
		cout << endl;

		if (pChoice == 0)
		{
			i = 0;
			bContinue = false;
			pChoice = 0;
		}

		else if ((cCode == 1) && ((pChoice < 1 || pChoice > 5)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 2) && ((pChoice < 1 || pChoice > 10)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 3) && ((pChoice < 1 || pChoice > 16)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 4) && ((pChoice < 1 || pChoice > 21)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 5) && ((pChoice < 1 || pChoice > 26)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 6) && ((pChoice < 1 || pChoice > 35)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else if ((cCode == 7) && ((pChoice < 1 || pChoice > 43)))
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
			bContinue = false;
		}

		else
		{
			bContinue = false;
		}
	}

	return pChoice;
}

int msgProc::sMMenu9(int cCode)
{
	cout << "We currently do not have any items of this type." << endl;
	return 0;
}

bool msgProc::sMIInfo(int iCode, string iType, string iType2, Player& mPlayer, Station& stat, int amount)
{
	bValid = false;

	if (iType == "Weapon")
	{
		ds_mp.rData("Weapon_Data","select from",iCode); //Get Weapon Data

		cout << ds_mp.getWName() << endl;
		cout << "Description:" << endl;
		cout << ds_mp.getWDesc() << endl;
		cout << "Required Ship Class: " << ds_mp.getWClass() << endl;
		cout << "Minimum Damage: " << ds_mp.getWDRLow() << endl;
		cout << "Maximum Damage: " << ds_mp.getWDRHigh() << endl;
		
		if (iType2 != "bomb")
		{
			
			if (iType2 != "missile")
			{
				cout << "Minimum Targeting Distance: " << ds_mp.getWAMin() << endl;
			}

			if (iType2 == "laser")
			{
				cout << "Minimum Optimum Targeting Distance: " << ds_mp.getWAOMin() << endl;
				cout << "Maximum Optimum Targeting Distance: " << ds_mp.getWAOMax() << endl;
			}

			cout << "Maximum Targeting Distance: " << ds_mp.getWAMax() << endl;
		}

		else if (iType2 == "bomb")
		{
			cout << "Weight: " << ds_mp.getWWeight() << endl;
		}

		cout << "Technology Level: " << ds_mp.getWTLevel() << endl;
		cout << endl;

		cout << "Resource Cost: " << endl;
		cout << endl;

		//Set Resouece Variables

		sCMulti = stat.getCMulti(); //Get the station cost multiplier

		//Apply the station cost multiplier
		xCost = ds_mp.getWXC()*sCMulti;
		rCost = ds_mp.getWRC()*sCMulti;
		diCost = ds_mp.getWDiC()*sCMulti;
		dCost = ds_mp.getWDC()*sCMulti;
		lCost = ds_mp.getWLC()*sCMulti;
		uCost = ds_mp.getWUC()*sCMulti;
		pluCost = ds_mp.getWPC()*sCMulti;
		nwCost = ds_mp.getWNWC()*sCMulti;


		if (ds_mp.getWXC() != 0)
		{
			cout << "Xarn:			" << xCost << endl;
		}

		if (ds_mp.getWRC() != 0)
		{
			cout << "Rubies:		" << rCost << endl;
		}

		if (ds_mp.getWDiC() != 0)
		{
			cout << "Diamonds:		" << diCost << endl;
		}

		if (ds_mp.getWDC() != 0)
		{
			cout << "Draconic:		" << dCost << endl;
		}

		if (ds_mp.getWLC() != 0)
		{
			cout << "Lithium:		" << lCost << endl;
		}

		if (ds_mp.getWUC() != 0)
		{
			cout << "Uranium:		" << uCost << endl;
		}

		if (ds_mp.getWPC() != 0)
		{
			cout << "Plutonium:		" << pluCost << endl;
		}

		if (ds_mp.getWNWC()  != 0)
		{
			cout << "Nuclear Waste: " << nwCost << endl;
		}

		//Check to make sure player has required resources
		if ((xCost <= mPlayer.getXarn()) && (rCost <= mPlayer.getRubies()) && (diCost <= mPlayer.getDia()) && (dCost <= mPlayer.getDrac()) && (lCost <= mPlayer.getLith()) && (uCost <= mPlayer.getUra()) && (pluCost <= mPlayer.getPlut()) && (nwCost <= mPlayer.getNWaste()))
		{
			while (!bValid)
			{
				
				cout << "Do you want to purchase this weapon?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice;

				cout << endl;
				cout << endl;

				if (pChoice < 1 || pChoice > 2)
				{
					mRMessage(12);
				}

				else
				{
					bValid = true;
				}
			}
		}

		else
		{
			cout << "You do not have enough resources to purchase this item." << endl;

			return false;
		}

		if (pChoice == 2)
		{
			return false;
		}

		else
		{			
			return true;
		}
	}

	else if (iType == "Ship")
	{
		ds_mp.rData("Ship_Data","select from",iCode); //Get Weapon Data

		cout << ds_mp.getSName() << endl;
		cout << "Description:" << endl;
		cout << ds_mp.getSDesc() << endl;
		cout << "Ship Class: " << ds_mp.getSClass() << endl;
		cout << "Maximum Shield Capacity: " << ds_mp.getSShield() << endl;
		cout << "Armor Strength: " << ds_mp.getSArmor() << endl;
		cout << "Maximum Hull Integrity: " << ds_mp.getSHull() << endl;
		cout << "Total Hardpoint Locations: " << ds_mp.getSWHP() << endl;
		cout << "Laser Hardpoint Locations: " << ds_mp.getSLB() << endl;
		cout << "Missile Hardpoint Locations: " << ds_mp.getSMT() << endl;
		cout << "Bomb Holds: " << ds_mp.getSBH() << endl;
		cout << "Railgun Hardpoint Locations: " << ds_mp.getSRM() << endl;
		cout << "Heavy Weapons Bays: " << ds_mp.getSHWB() << endl;
		cout << "Movement Initiative: " << ds_mp.getSMInit() << endl;
		cout << "Technology Level: " << ds_mp.getWTLevel() << endl;
		cout << endl;

		cout << "Resource Cost: " << endl;
		cout << endl;

		//Set Resouece Variables

		sCMulti = stat.getCMulti(); //Get the station cost multiplier

		//Apply the station cost multiplier
		xCost = ds_mp.getWXC()*sCMulti;
		rCost = ds_mp.getWRC()*sCMulti;
		diCost = ds_mp.getWDiC()*sCMulti;
		dCost = ds_mp.getWDC()*sCMulti;
		lCost = ds_mp.getWLC()*sCMulti;
		uCost = ds_mp.getWUC()*sCMulti;
		pluCost = ds_mp.getWPC()*sCMulti;
		nwCost = ds_mp.getWNWC()*sCMulti;

		if (ds_mp.getWXC() != 0)
		{
			cout << "Xarn:			" << xCost << endl;
		}

		if (ds_mp.getWRC() != 0)
		{
			cout << "Rubies:		" << rCost << endl;
		}

		if (ds_mp.getWDiC() != 0)
		{
			cout << "Diamonds:		" << diCost << endl;
		}

		if (ds_mp.getWDC() != 0)
		{
			cout << "Draconic:		" << dCost << endl;
		}

		if (ds_mp.getWLC() != 0)
		{
			cout << "Lithium:		" << lCost << endl;
		}

		if (ds_mp.getWUC() != 0)
		{
			cout << "Uranium:		" << uCost << endl;
		}

		if (ds_mp.getWPC() != 0)
		{
			cout << "Plutonium:		" << pluCost << endl;
		}

		if (ds_mp.getWNWC()  != 0)
		{
			cout << "Nuclear Waste: " << nwCost << endl;
		}

		//Check to make sure player has required resources
		if ((xCost <= mPlayer.getXarn()) && (rCost <= mPlayer.getRubies()) && (diCost <= mPlayer.getDia()) && (dCost <= mPlayer.getDrac()) && (lCost <= mPlayer.getLith()) && (uCost <= mPlayer.getUra()) && (pluCost <= mPlayer.getPlut()) && (nwCost <= mPlayer.getNWaste()))
		{
			while (!bValid)
			{
				
				cout << "Do you want to purchase this weapon?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice;

				cout << endl;
				cout << endl;

				if (pChoice < 1 || pChoice > 2)
				{
					mRMessage(12);
				}

				else
				{
					bValid = true;
				}
			}
		}

		else
		{
			cout << "You do not have enough resources to purchase this item." << endl;

			return false;
		}

		if (pChoice == 2)
		{
			return false;
		}

		return true;
	}

	else if (iType == "Mod")
	{
		//TODO: create mods
	}

	else if (iType == "Equipment")
	{
		ds_mp.rData("Equipment_Data","select from",iCode); //Get Weapon Data

		cout << ds_mp.getEName() << endl;
		cout << "Description:" << endl;
		cout << ds_mp.getEDesc() << endl;
		
		//Set Resouece Variables

		sCMulti = stat.getCMulti(); //Get the station cost multiplier

		//Apply the station cost multiplier
		xCost = ds_mp.getEXC()*sCMulti;
		rCost = ds_mp.getERC()*sCMulti;
		diCost = ds_mp.getEDiC()*sCMulti;
		dCost = ds_mp.getEDC()*sCMulti;
		lCost = ds_mp.getELC()*sCMulti;
		uCost = ds_mp.getEUC()*sCMulti;
		pluCost = ds_mp.getEPC()*sCMulti;
		nwCost = ds_mp.getENWC()*sCMulti;

		//Extra 25% chare for clones
		xCost = xCost + (xCost * 0.25);

		if (ds_mp.getEXC() != 0)
		{
			cout << "Xarn:			" << xCost << endl;
		}

		if (ds_mp.getERC() != 0)
		{
			cout << "Rubies:		" << rCost << endl;
		}

		if (ds_mp.getEDiC() != 0)
		{
			cout << "Diamonds:		" << diCost << endl;
		}

		if (ds_mp.getEDC() != 0)
		{
			cout << "Draconic:		" << dCost << endl;
		}

		if (ds_mp.getELC() != 0)
		{
			cout << "Lithium:		" << lCost << endl;
		}

		if (ds_mp.getEUC() != 0)
		{
			cout << "Uranium:		" << uCost << endl;
		}

		if (ds_mp.getEPC() != 0)
		{
			cout << "Plutonium:		" << pluCost << endl;
		}

		if (ds_mp.getENWC()  != 0)
		{
			cout << "Nuclear Waste: " << nwCost << endl;
		}

		//Check to make sure player has required resources
		if ((xCost <= mPlayer.getXarn()) && (rCost <= mPlayer.getRubies()) && (diCost <= mPlayer.getDia()) && (dCost <= mPlayer.getDrac()) && (lCost <= mPlayer.getLith()) && (uCost <= mPlayer.getUra()) && (pluCost <= mPlayer.getPlut()) && (nwCost <= mPlayer.getNWaste()))
		{
			while (!bValid)
			{
				
				cout << "Do you want to purchase this item?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice;

				cout << endl;
				cout << endl;

				if (pChoice < 1 || pChoice > 2)
				{
					mRMessage(12);
				}

				else
				{
					bValid = true;
				}
			}
		}

		else
		{
			cout << "You do not have enough resources to purchase this item." << endl;

			return false;
		}

		if (pChoice == 2)
		{
			return false;
		}

		return true;
	}

	else if (iType == "Resource")
	{
		ds_mp.rData("Resource","select from", iCode);

		cout << ds_mp.getResName() << endl;
		cout << "Description: " << endl;
		cout << ds_mp.getResDesc() << endl << endl;

		xCost = ((ds_mp.getResXCost() * amount) * stat.getCMulti());

		cout << "Number of items bought: " << amount << endl << endl;
		cout << "Cost per item: " << ds_mp.getResXCost() << "(x" << stat.getCMulti() << ")" << endl;
		cout << "Total cost: " << xCost << endl << endl;

		if (mPlayer.getXarn() < xCost)
		{
			cout << "You do not have enough resources to buy this number of items." << endl;
			return false;
		}

		else
		{
			while (!bValid)
			{				
				cout << "Do you want to purchase these item(s)?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice;

				cout << endl;
				cout << endl;

				if (pChoice < 1 || pChoice > 2)
				{
					mRMessage(12);
				}

				else
				{
					bValid = true;
				}
			}
		}

		if (pChoice == 2)
		{
			return false;
		}

		return true;
	}

	else if (iType == "Ore")
	{
		ds_mp.rData("Ore","select from", iCode);

		cout << ds_mp.getOName() << endl;
		cout << "Description: " << endl;
		cout << ds_mp.getODesc() << endl << endl;

		xCost = ((ds_mp.getOXCost() * amount) * stat.getCMulti());

		cout << "Number of items bought: " << amount << endl << endl;
		cout << "Cost per item: " << ds_mp.getOXCost() << "(x" << stat.getCMulti() << ")" << endl;
		cout << "Total cost: " << xCost << endl << endl;

		if (mPlayer.getXarn() < xCost)
		{
			cout << "You do not have enough resources to buy this number of items." << endl;
			return false;
		}

		else
		{
			while (!bValid)
			{				
				cout << "Do you want to purchase these item(s)?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice;

				cout << endl;
				cout << endl;

				if (pChoice < 1 || pChoice > 2)
				{
					mRMessage(12);
				}

				else
				{
					bValid = true;
				}
			}
		}

		if (pChoice == 2)
		{
			return false;
		}

		return true;
	}
}

int msgProc::sISItem()
{
	bValid = false;
	
	while (!bValid)
	{
		
		cout << "Please choose one of the following options:" << endl;
		cout << "1) Install purchase" << endl;
		cout << "2) Store purchase" << endl;
		cout << ">";
		cin >> pChoice;
		cout << endl;

		if (pChoice < 1 || pChoice > 2)
		{
			cout << "Your choice was not bValid.  Please enter a valid choice." << endl;
			cout << endl;
		}

		else
		{
			bValid = true;
		}
	}

	return pChoice;
}

int msgProc::sBSShip()
{
	bValid = false;

	while(!bValid)
	{
		cout << "Please choose one of the following options:" << endl;
		cout << "1) Assemble and Board Ship" << endl;
		cout << "2) Store Ship" << endl;
		cout << ">";
		cin >> pChoice;

		if (pChoice < 1 || pChoice > 2)
		{
			cout << "Your choice was not bValid.  Please enter a valid choice." << endl;
			cout << endl;
		}

		else
		{
			bValid = true;
		}
	}

	return pChoice;
}

int msgProc::sKVEquipment()
{
	bValid = false;

	while(!bValid)
	{
		cout << "Please choose one of the following options:" << endl;
		cout << "1) Transfer equipment to new ship (non-class compliant equipment will be stored)" << endl;
		cout << "2) Store all equipment" << endl;
		cout << ">";
		cin >> pChoice;

		if (pChoice < 1 || pChoice > 2)
		{
			cout << "Your choice was not bValid.  Please enter a valid choice." << endl;
			cout << endl;
		}

		else
		{
			bValid = true;
		}
	}

	return pChoice;
}

float msgProc::sBISPMenu(float cSpace, float mSpace, float nSpace, Player& mPlayer)
{
	bValid = false;

	while (!bValid)
	{
		sTBuy = (nSpace - (mSpace - cSpace));

		if (sTBuy < 0)
		{
			sTBuy = sTBuy * -1;
		}

		cout << "You currently have " << cSpace << "sg� of " << mSpace << "sg� cargohold space used.  You require at least " << sTBuy << " sg� more cargo space to store your current purchase."  << endl;
		cout << "Cargohold space is sold in 500 sg� increments at 100 Xarn per increment.  Rent for cargohold space, however, is calculated by 1000 sg� increments at 250 Xarn per 1000 sg� of cargohold space used (rounded to highest thousand) up to a max of 1,000,000 sg� per customer." << endl;
		cout << "To learn more about the terms of use of our cargo services please enter '3' into the menu prompt below." << endl;
		cout << endl;
		cout << "The total cost for the required space will be " << 
		cout << "How many units of 500 sg� cargohold space do you want to buy?" << endl;
		cout << ">";
		cin >> pChoice;
		cout << endl;

		while (!bValid)
		{
			if ((pChoice * 500) + cSpace > mSpace)
			{
			
				cout << "We are sorry, you have not selected enough space.  You have " << mSpace - cSpace << "sg� of open space.  You require an additional " << nSpace << "sg� cargo space to store your item(s).  This means you need to buy at least " << sTBuy << "sg� of cargohold space." << endl;
				cout << "Do you want to buy more space?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				cout << ">";
				cin >> pChoice2;
				cout << endl << endl;

				if (pChoice2 > 2 || pChoice2 < 1)
				{					
					cout << mRMessage(11) << endl;
				}

				else if (pChoice2 == 1)
				{
					cout << "How many more units of 500 sg� cargohold space do you want to buy?" << endl;
					cout << ">";
					cin >> pChoice2;
					cout << endl;	

					pChoice += pChoice2;
				}

				else if (pChoice2 == 2)
				{
					cout << "You do not have enough space to store the item.  Returning you to the 'store item' menu." << endl;
					bValid = true;
					return 0;
				}
			}

			else if ((pChoice * 100) > mPlayer.getXarn())
			{
				cout << "We are sorry, you do not have the required " << (100 * pChoice) << " Xarn required to complete your purchase.  Please enter in a lower number of units to purchase." << endl;
				cout << endl;
			}
			
			
			else
			{
				cout << "Thank you for your purchase.  Have a nice day." << endl;
				cout << endl;

				mPlayer.updateXarn((pChoice*100),"sub");
	
				bValid = true;
			}
		}

		bValid = false;	
	}

	return pChoice;
}

//Mission Information
void msgProc::mInfo(Mission* m, bool bCInfo)
{
	//Basic Information
	cout << m->getMName() << "'s Mission Information:" << endl; //name
	cout << "Description: " << m->getMDesc() << endl; //desc
	cout << "Type: " << m->getMType() << endl; //type
	cout << "Duration: " << m->getMDur() << endl; //duration
	cout << "Difficulty: " << m->getMDiff() << endl; //diff
	cout << "Location: " << m->getMSector() << ", " << m->getMSystem() << endl; //location
	cout << "Mission State: " << m->getMState() << endl; //State

	if (bCInfo)
	{
		cout << "CBE Level Requirement: " << m->getMCBEReq() << endl;
		cout << "Ship Class Requirement: " << m->getMSCReq() << endl;
		cout << "Weapon/Module Requirement: " << m->getMMWReq() << endl;
		cout << "Target Name: " << m->getMTName() << endl;
		cout << "Target Ship Class: " << m->getMTSClass() << endl;
		cout << endl;
		cout << endl;
		
		cout << "Rewards: " << endl;
		cout << "Bounty: " << m->getMBounty() << endl;
		cout << "Xarn: " << m->getMXR() << endl;
		cout << "Rubies: " << m->getMRR() << endl;
		cout << "Diamonds: " << m->getMDiR() << endl;
		cout << "Draconic: " << m->getMDR() << endl;
		cout << "Lithium: " << m->getMLR() << endl;
		cout << "Platinum: " << m->getMPlR() << endl;
		cout << "Uranium: " << m->getMUR() << endl;
		cout << "Plutonium: " << m->getMPR() << endl;
		cout << "Nuclear Waste: " << m->getMNWR() << endl;
		cout << "EXP: " << m->getMEXPR() << endl;
		cout << "Gear: " << m->getMIR() << endl;
	}
}



//Ship Weapon Spread Menus

int msgProc::sSCMenu()
{
	cout << "Please choose from the following:" << endl;
	cout << "1) Create a new weapon spread" << endl;
	cout << "2) Delete a weapon spread" << endl;
	cout << "3) Edit an existing weapon spread" << endl;
	cout << "4) Done " << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::sWSSelection(int lasers, int missiles, int rails, int heavies)
{
	cout << "Please choose from the following weapon types: " << endl;
	
	if (lasers > 0)
	{
		cout << "1) Laser" << endl;
	}

	if (missiles > 0)
	{
		cout << "2) Missile" << endl;
	}

	if (rails > 0)
	{
		cout << "3) Rail Gun" << endl;
	}

	if (heavies > 0)
	{
		cout << "4) Heavy Weapon" << endl;
	}

	cout << "0) Done" << endl;

	cout << ">";
	cin >> pChoice;
	cout << endl;
	cout << endl;

	bValid = false;

	while (!bValid) //Make sure the player chose a displayed value
		{
			if ((pChoice == 1) && (lasers < 1)) //If player chose laser group and there are no laser weapons installed then
			{
				cout << mRMessage(5) << endl << endl; //Display error message and 
				pChoice = 2; //set pChoice to 2
			}

			else if (pChoice == 1) //Else if there are laser weapons installed then
			{
				bValid = true; //Set bValid to true and return player choice
			}

			if ((pChoice == 2) && (missiles < 1))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 3;
			}

			else if (pChoice == 2)
			{
				bValid = true;
			}

			if ((pChoice == 3) && (rails < 1))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 4;
			}

			else if (pChoice == 3)
			{
				bValid = true;
			}

			if ((pChoice == 4) && (heavies < 1))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 1;
			}

			else if (pChoice == 4)
			{
				bValid = true;
			}

			else if (pChoice == 0)
			{
				bValid = true;
			}

			else //If player enters a non-valid value, set to 1 and allow the loop to process again
			{
				cout << mRMessage(5) << endl << endl;
				pChoice == 1;
				bValid = false;
			}
		}

	return pChoice;
}

char msgProc::sLWSelection(Laser* weapon)
{
	cout << "Weapon Name: " << weapon->getWName() << endl;
	cout << "Weapon Damage Range: " << weapon->getWDRLow() << "-" << weapon->getWDRHigh() << endl;
	cout << "Weapon Min/Max Range: " << weapon->getWALow() << "KM - " << weapon->getWAHigh() << endl;
	cout << "Weapon Min/Max Optimum Range: " << weapon->getWAOLow() << "KM - " << weapon->getWAOHigh() << endl;
	cout << "Weapon Damage Type: " << weapon->getWDType() << endl;
	cout << endl;
	cout << endl;

	cout << "Do you want to use this weapon in your weapon spread?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return pCChoice;
		break;			

	default:
		mRMessage(27);
		cout << endl;
		return 'n';
		break;
	}
}

char msgProc::sMWSelection(Missile* weapon)
{
	cout << "Weapon Name: " << weapon->getWName() << endl;
	cout << "Weapon Damage Range: " << weapon->getWDRLow() << "-" << weapon->getWDRHigh() << endl;
	cout << "Weapon Min/Max Range: " << weapon->getWALow() << "KM - " << weapon->getWAHigh() << endl;
	cout << "Weapon Damage Type: " << weapon->getWDType() << endl;
	cout << endl;
	cout << endl;

	cout << "Do you want to use this weapon in your weapon spread?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return pCChoice;
		break;			

	default:
		mRMessage(27);
		cout << endl;
		return 'n';
		break;
	}
}

char msgProc::sRWSelection(Rail* weapon)
{
	cout << "Weapon Name: " << weapon->getWName() << endl;
	cout << "Weapon Damage Range: " << weapon->getWDRLow() << "-" << weapon->getWDRHigh() << endl;
	cout << "Weapon Min/Max Range: " << weapon->getWALow() << "KM - " << weapon->getWAHigh() << " KM" << endl;
	cout << "Weapon Min/Max Optimum Range: " << weapon->getWAOLow() << "KM - " << weapon->getWAOHigh() << " KM" << endl;
	cout << "Weapon Damage Type: " << weapon->getWDType() << endl;
	cout << endl;
	cout << endl;

	cout << "Do you want to use this weapon in your weapon spread?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return pCChoice;
		break;			

	default:
		mRMessage(27);
		cout << endl;
		return 'n';
		break;
	}
}

char msgProc::sHWSelection(Heavy* weapon)
{
	cout << "Weapon Name: " << weapon->getWName() << endl;
	cout << "Weapon Damage Range: " << weapon->getWDRLow() << "-" << weapon->getWDRHigh() << endl;
	cout << "Weapon Damage Intensity Min/Max Range: " << weapon->getDILow() << "KM -" << weapon->getDIHigh() << " KM" << endl;
	cout << "Weapon Damage Intensity Min/Max Optium Range: " << weapon->getDIOLow() << "KM -" << weapon->getDIOHigh() << " KM" << endl;
	cout << "Weapon Min/Max Range: " << weapon->getWALow() << "KM - " << weapon->getWAHigh() << " KM" << endl;
	cout << "Weapon Min/Max Optimum Range: " << weapon->getWAOLow() << "KM - " << weapon->getWAOHigh() << " KM" << endl;
	cout << "Weapon Damage Type: " << weapon->getWDType() << endl;
	cout << endl;
	cout << endl;
	cout << "Do you want to use this weapon in your weapon spread?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return pCChoice;
		break;			

	default:
		mRMessage(27);
		cout << endl;
		return 'n';
		break;
	}
}

//TODO: Add a bomb weapon spread function above

int msgProc::sCEWSpread(int sWSpreads, Player& mPlayer)
{
	cout << "Please choose one of the following empty weapon spreads: " << endl;
	cout << endl;

	for (i = 1; i <= sWSpreads; i++)
	{
		if (i == sWSpreads)
		{
			cout << "0) Cancel" << endl;
		}
		
		else if (mPlayer.Ship.getSSize(i2) == 0)
		{
			cout << i << ") Weapon Spread " << i << endl;	
		}
	}

	cout << ">";
	cin >> pChoice;
	cout << endl;
	cout << endl;


	if ((pChoice != 0) && ( mPlayer.Ship.getSSize(pChoice) != 0))
	{
		mRMessage(5);
		pChoice = 0;
	}

	if (pChoice < 0 || pChoice > sWSpreads)
	{
		mRMessage(5);
		pChoice = 0;
	}

	return pChoice;
}

int msgProc::sDSpread(int sWSpreads, Player& mPlayer)
{
	cout << "Please choose a spread to clear:" << endl;

	cout << "0) Cancel" << endl;

	for (i = 1; i < sWSpreads; i++)
	{
		if (mPlayer.Ship.getSSize(i) > 0) //Only display non-empty spreads
		{
			cout << i << ") Weapon Spread " << i << endl;
		}
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if ((pChoice != 0) && ( mPlayer.Ship.getSSize(pChoice) == 0))
	{
		mRMessage(5);
		pChoice = 0;
	}

	if (pChoice < 0 || pChoice > sWSpreads)
	{
		mRMessage(5);
		pChoice = 0;
	}

	if (pChoice == 0)
	{
		cout << "Canceling deletion..." << endl;
	}

	else
	{
		cout << "Are you sure you wish to delete this weapon spread?" << endl << endl;

		cout << "Weapons in this spread: ";

		for (i = 0; i < mPlayer.Ship.getSSize(pChoice); i++)
		{
			tempSpread = mPlayer.Ship.getSVect(pChoice);

			if (tempSpread.at(i).getHPWType() ==  "laser")
			{
				cout << mPlayer.Ship.lBanks.at(tempSpread.at(i).getHPSlot()).hpWeapon.getWName() << ", ";
			}

			else if (tempSpread.at(i).getHPWType() ==  "missile")
			{
				cout << mPlayer.Ship.mTurrets.at(tempSpread.at(i).getHPSlot()).hpWeapon.getWName() << ", ";
			}

			else if (tempSpread.at(i).getHPWType() ==  "bomb")
			{
				cout << mPlayer.Ship.bHolds.at(tempSpread.at(i).getHPSlot()).hpWeapon.getWName() << ", ";
			}

			else if (tempSpread.at(i).getHPWType() ==  "rail")
			{
				cout << mPlayer.Ship.rMounts.at(tempSpread.at(i).getHPSlot()).hpWeapon.getWName() << ", ";
			}

			else if (tempSpread.at(i).getHPWType() ==  "heavy")
			{
				cout << mPlayer.Ship.hWBays.at(tempSpread.at(i).getHPSlot()).hpWeapon.getWName() << ", ";
			}
		}

		cout << endl << endl;

		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;

		switch(pCChoice)
		{
		case 'y':
		case 'Y':
			break;			

		default:
			cout << "Canceling deletion..." << endl << endl;
			pChoice = 0;
			break;
		}
	}

	return pChoice;
}

int msgProc::bCSpread(int sWSpreads, Player& mPlayer)
{
	if (!mPlayer.Ship.bAWInstalled()) //Make sure there are weapons installed on the ship
	{
		cout << mRMessage(2023) << endl;
		return -1;
	}

	else
	{
		if (sWSpreads != 0) //If there are no weapon spreads detected then skip to else
		{
			cout << "Please choose one of the following weapon spreads: " << endl << endl;

			cout << "0) Cancel" << endl;

			for (i = 1; i < sWSpreads; i++)
			{
				if (mPlayer.Ship.getSSize(i) > 0) //Only display non-empty spreads
				{
					cout << i << ") Weapon Spread " << i << endl;
				}
			}

			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			if ((pChoice != 0) && ( mPlayer.Ship.getSSize(pChoice) == 0))
			{
				cout << mRMessage(2019) << endl;
				pChoice = 0;
			}

			if (pChoice < 0 || pChoice > sWSpreads)
			{
				cout << mRMessage(2019) << endl;
				pChoice = 0;
			}
		}

		else
		{
			cout << mRMessage(2020) << endl;
			pChoice = 0;
		}
	}

	return pChoice;
}

char msgProc::sOWSpread(Player& mPlayer)
{
	cout << "Do you want to overwrite this weapon spread?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return pCChoice;
		break;			

	default:
		mRMessage(29);
		cout << endl;
		return 'n';
		break;
	}
}

int msgProc::bCWSystem(Player& mPlayer)
{

	if (!mPlayer.Ship.bAWInstalled())
	{
		cout << mRMessage(2023) << endl;
		return -1;
	}

	else
	{
		cout << "Please choose from the following weapon types: " << endl;

		if (mPlayer.Ship.getULHP() > 0)
		{
			cout << "1) Laser" << endl;
		}

		if (mPlayer.Ship.getUMTP() > 0)
		{
			cout << "2) Missile" << endl;
		}

		if (mPlayer.Ship.getURM() > 0)
		{
			cout << "4) Rail Gun" << endl;
		}

		if (mPlayer.Ship.getUHWB() > 0)
		{
			cout << "5) Heavy Weapon" << endl;
		}

		cout << ">";
		cin >> pChoice;
		cout << endl;
		cout << endl;

		bValid = false;

		while (!bValid)
		{
			if ((pChoice == 1) && (mPlayer.Ship.getULHP() < 1))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 2;
			}

			else if (pChoice == 1)
			{
				bValid = true;
			}

			if ((pChoice == 2) && (mPlayer.Ship.getUMTP() < 1))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 4;
			}

			else if (pChoice == 2)
			{
				bValid = true;
			}

			if (pChoice == 3)
			{
				cout << mRMessage(2022) << endl << endl;;
				pChoice = 1;
			}

			if ((pChoice == 4) && (mPlayer.Ship.getURM() < 4))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 4;
			}

			else if (pChoice == 4)
			{
				bValid = true;
			}

			if ((pChoice == 5) && (mPlayer.Ship.getUHWB() < 5))
			{
				cout << mRMessage(5) << endl << endl;
				pChoice = 1;
			}

			else if (pChoice == 5)
			{
				bValid = true;
			}			
		}
	}

	return pChoice;
}

int msgProc::bCWeapon(Player& mPlayer, string* wtype)
{
	i = 1; //Set this here since it will be used for menu option enumeration

	cout << "Please choose from the following weapons: " << endl;
	
	for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(1); i2++)
	{
		if (mPlayer.Ship.lBanks.at(i2).hpWeapon.getWName() != "No Weapon Installed")
		{
			cout << i << ") " << mPlayer.Ship.lBanks.at(i2).hpWeapon.getWName() << endl;
			i += 1;
		}
	}

	for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(2); i2++)
	{
		if (mPlayer.Ship.mTurrets.at(i2).hpWeapon.getWName() != "No Weapon Installed")
		{
			cout << i << ") " << mPlayer.Ship.mTurrets.at(i2).hpWeapon.getWName() << endl;
			i += 1;
		}
	}

	for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(4); i2++)
	{
		if (mPlayer.Ship.rMounts.at(i2).hpWeapon.getWName() != "No Weapon Installed")
		{
			cout << i << ") " << mPlayer.Ship.rMounts.at(i2).hpWeapon.getWName() << endl;
			i += 1;
		}
	}

	for (i2 = 0; i2 < mPlayer.Ship.getWHPVSize(5); i2++)
	{
		if (mPlayer.Ship.hWBays.at(i2).hpWeapon.getWName() != "No Weapon Installed")
		{
			cout << i << ") " << mPlayer.Ship.hWBays.at(i2).hpWeapon.getWName() << endl;
			i += 1;
		}
	}

	if (i > 1)
	{
		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		//Get the values of used weapons
		laser = mPlayer.Ship.getULHP();
		missile = mPlayer.Ship.getUMTP();
		rail = mPlayer.Ship.getURM();
		heavy = mPlayer.Ship.getUHWB();

		if ((pChoice > 0) && (pChoice <= laser)) //If pChoice is greater than 0 but less than laser then the player has picked a laser weapon
		{
			*wtype = "laser";
			return pChoice;
		}

		else if ((pChoice > laser) && (pChoice <= laser+missile)) //Else if pChoice is greater than laser but less than laser plus missile then the player has chosen a missile weapon...etc.
		{
			*wtype = "missile";
			pChoice -= laser-1; //To get an accurate value, subtract the value of laser.  Example: 2 Laser and 4 Missile.  Player chooses weapon #5.  This is missile #3.  Subtract 2 from 5, get 3.  Subtract 1 because vectors are zero indexed.  Return pChoice as 2.
			return pChoice;
		}

		else if ((pChoice > laser+missile) && (pChoice <= laser+missile+rail))
		{
			*wtype = "rail";
			pChoice -= laser+missile-1;
			return pChoice;
		}

		else if ((pChoice > laser+missile+rail) && (pChoice <= laser+missile+rail+heavy))
		{
			*wtype = "heavy";
			pChoice -= laser+missile+rail-1;
			return pChoice;
		}
	}

	else
	{
		cout << mRMessage(2023) << endl;
		return -1;
	}
}

int msgProc::bCBomb(Player& mPlayer, string* wtype)
{
	cout << "Please choose from the following weapons: " << endl;

	for (i = 1, i2 = 0; i2 < mPlayer.Ship.getWHPVSize(3); i2++)
	{
		if (mPlayer.Ship.bHolds.at(i2).hpWeapon.getWName() != "No Weapon Installed")
		{
			cout << i << ") " << mPlayer.Ship.bHolds.at(i2).hpWeapon.getWName() << endl;
			i += 1;
		}
	}

	if (i > 1)
	{
		cout << ">";
		cin >> pChoice;
		cout << endl;
		cout << endl;

		//Get number of installed bombs
		bomb = mPlayer.Ship.getUBH();

		if ((pChoice > 0) && (pChoice <= bomb))
		{
			*wtype = "bomb";
			return pChoice-1;
		}

		else
		{
			cout << mRMessage(5) << endl;
			return 0;
		}
	}

	else
	{
		cout << mRMessage(2023) << endl;
		return -1;
	}
}

int msgProc::sMSystem(int sAMInit)
{
	cout << "Sir, we have " << sAMInit << " Kilometers left to move before the engines need to be recharged.  Which direction do you want to go?" << endl;
	cout << "1) Up " << endl;
	cout << "2) Forward" << endl;
	cout << "3) Backward" << endl;
	cout << "4) Left" << endl;
	cout << "5) Right" << endl;
	cout << "6) Down" << endl;
	cout << "7) Return to Battle" << endl;
	cout <<"> ";
	cin >> pChoice;

	if ((pChoice < 1) || (pChoice > 7))
	{
		cout << mRMessage(5) << endl;
		pChoice = 7;
	}

	return pChoice;
	mCScreen(false);
}

int msgProc::sMSystem2(int sAMInit)
{
	cout << "Sir, we have " << sAMInit << " Kilometers left to move before the engines need to be recharged.  Which direction do you want to go?" << endl << endl;

	cout << "1) Up " << endl;
	cout << "2) Forward" << endl;
	cout << "3) Backward" << endl;
	cout << "4) Left" << endl;
	cout << "5) Right" << endl;
	cout << "6) Down" << endl;
	cout << "7) Return to menu" << endl;
	cout <<"> ";
	cin >> pChoice;
	cout << endl << endl;

	if ((pChoice < 1) || (pChoice > 7))
	{
		cout << mRMessage(5) << endl;
		pChoice = 7;
	}

	return pChoice;
	mCScreen(false);
}

void msgProc::nBSPos(Player& mPlayer, NPC& mNPC)
{
	cout << "Your position: " << mPlayer.Ship.getXPos() << ", " << mPlayer.Ship.getYPos() << ", " << mPlayer.Ship.getZPos() << endl;
	cout << "Target's position: " << mNPC.Ship.getXPos() << ", " << mNPC.Ship.getYPos() << ", " << mNPC.Ship.getZPos() << endl;
	cout << "Current distance to target: " << m_mp.getDistance(mPlayer.Ship.getXPos(),mNPC.Ship.getXPos(),mPlayer.Ship.getYPos(),mNPC.Ship.getYPos(),mPlayer.Ship.getZPos(),mNPC.Ship.getZPos()) << endl;
}

void msgProc::mTPos(Player& mPlayer, Asteroid roid)
{
	cout << "Your position: " << mPlayer.Ship.getXPos() << ", " << mPlayer.Ship.getYPos() << ", " << mPlayer.Ship.getZPos() << endl;
	cout << "Target's position: " << roid.getXPos() << ", " << roid.getYPos() << ", " << roid.getZPos() << endl;
	cout << "Current distance to target: " << m_mp.getDistance(mPlayer.Ship.getXPos(),roid.getXPos(),mPlayer.Ship.getYPos(),roid.getYPos(),mPlayer.Ship.getZPos(),roid.getZPos()) << endl;
}

bool msgProc::cClone(int* sID, int* sIID, Game& mGame)
{
	for (i = 0; i <= mGame.gStations.size(); i++)
	{
		if (i == mGame.gStations.size())
		{
			return false;
		}

		else
		{
			for (i2 = 0; i2 < mGame.gStations.at(i).sInventory.size(); i2++)
			{			
				if (mGame.gStations.at(i).sInventory.at(i2).getIID() == 1 || mGame.gStations.at(i).sInventory.at(i2).getIID() == 2 || mGame.gStations.at(i).sInventory.at(i2).getIID() == 3)
				{
					*sID = i;
					*sIID = i2;		
					return true;
				}					
			}
		}
	}
}

int msgProc::sBClone()
{
	cout << "Welcome to the Clone procurement facility on this station.  Please note that due to interstellar law set down by the Federation of Intergalactic Empires that the purchase of a clone represents a legally binding contract." << endl;
	cout << "This contract holds you, or your kin if a clone dies with no replacement, personally responsibile for all damages a clone may incure and that the manufacturer of your clone(s) may not be held accountable for their actions." << endl;
	cout << "In the event of the death of a clone you hereby agree that any charges including murder, theft, assault, or espionage will be transfered to your next of kin who will pay the fines or serve the sentence of any crimes comitted by your clone." << endl;
	cout << endl;
	cout << endl;

	cout << "Please also be aware that the Talirath requires a 25% Xarn tax on each clone sale to cover the costs of illegal clone usage.  This tax will be automatically added into the cost report for your item(s)." << endl;
	cout << endl;
	cout << endl;
	
	cout << mRMessage(1) << endl;
	
	for (i = 201; i <= 203; i++)
	{	
		ds_mp.rData("Equipment_Data","select from",i);

		cout << i << ") " << ds_mp.getEName() << endl;

		if (i2 == 203)
		{
			cout << i+1 << ") " << "Return to station menu" << endl;	
		}
	}

	cout << "> ";
	cin >> pChoice;

	cout << endl;
	cout << endl;

	if (pChoice == i+1)
	{
		i = 0;
		bContinue = false;
		pChoice = 0;
	}
	
	else if (pChoice < 201 || pChoice > 203)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	return pChoice;
}

int msgProc::sDRMenu1(Player& mPlayer)
{
	cout << "Please choose how you want to proceed:" << endl;

	if (mPlayer.Ship.getSArmor() < mPlayer.Ship.getSMArmor())
	{
		cout << "1) Repair Armor" << endl;
	}

	if (mPlayer.Ship.getSHull() < mPlayer.Ship.getSMHull())
	{
		cout << "2) Repair Hull" << endl;
	}

	if ((mPlayer.Ship.getSArmor() < mPlayer.Ship.getSMArmor()) && (mPlayer.Ship.getSArmor() < mPlayer.Ship.getSMArmor()))
	{
		cout << "3) Repair Both" << endl;
	}

	cout << "4) Access weapon spread system" << endl;
	cout << "5) Back to station menu" << endl;

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if ((pChoice == 1) && (mPlayer.Ship.getSArmor() == mPlayer.Ship.getSMArmor()))
	{
		cout << mRMessage(2010) << endl;
		return 0;
	}

	else if ((pChoice == 2) && (mPlayer.Ship.getSHull() == mPlayer.Ship.getSMHull()))
	{
		cout << mRMessage(2011) << endl;
		return 0;
	}

	else if ((pChoice == 3) && (mPlayer.Ship.getSArmor() == mPlayer.Ship.getSMArmor() || mPlayer.Ship.getSHull() == mPlayer.Ship.getSMHull()))
	{
		cout << mRMessage(2012) << endl;
		return 0;
	}

	if (pChoice < 1 || pChoice > 5)
	{
		cout << mRMessage(5) << endl;
		pChoice = 5;
	}

	return pChoice;
}

bool msgProc::sDRMenu2(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost)
{
	cout << "Due to your current affinity with the entity that owns this station, " << affin << ", the cost for repairing your armor to full strength will be, per percentage point (rounded):" << endl;
	cout << "Xarn Cost: " << xcost << endl;
	cout << "Ruby Cost: " << rcost << endl;
	cout << "Diamond Cost: " << dicost << endl;
	cout << "Draconic Cost: " << dcost << endl;
	cout << endl;

	//Calculate percent and then round it
	dPerc = (mPlayer.Ship.getSArmor() / mPlayer.Ship.getSMArmor()) * 100;

	dPerc_R = floor(dPerc * 100 + 0.5) / 100;
	dPerc_I = dPerc_R;

	if (dPerc_R >= dPerc_I + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
	{	
		dPerc_I += 1; //then round up
	}

	if (dPerc_I <= 0) //To deal with fully depleted armor; not needed for hull
	{
		dPerc_I = 100;
	}

	cout << "Your armor is damaged by " << dPerc_I << "%.  The total cost to repair will be: " << endl;
	cout << "Xarn Cost: " << xcost * dPerc_I << endl;
	cout << "Ruby Cost: " << rcost * dPerc_I << endl;
	cout << "Diamond Cost: " << dicost * dPerc_I << endl;
	cout << "Draconic Cost: " << dcost * dPerc_I << endl;
	cout << endl;

	cout << "Continue with Repair?" << endl;
	cout << "(Y/y)es, (N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;
	
	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return true;
		break;			

	default:
		mRMessage(29);
		cout << endl;
		return false;
		break;
	}
}

bool msgProc::sDRMenu3(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost)
{
	cout << "Due to your current affinity with the entity that owns this station, " << affin << ", the cost for repairing your hull to full strength will be, per percentage point (rounded):" << endl;
	cout << "Xarn Cost: " << xcost << endl;
	cout << "Ruby Cost: " << rcost << endl;
	cout << "Diamond Cost: " << dicost << endl;
	cout << "Draconic Cost: " << dcost << endl;
	cout << endl;

	//Calculate percent and then round it
	dPerc = (mPlayer.Ship.getSHull() / mPlayer.Ship.getSMHull()) * 100;

	dPerc_R = floor(dPerc * 100 + 0.5) / 100;
	dPerc_I = dPerc_R;

	if (dPerc_R >= dPerc_I + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
	{	
		dPerc_I += 1; //then round up
	}

	cout << "Your hull is damaged by " << dPerc_I << "%.  The total cost to repair will be: " << endl;
	cout << "Xarn Cost: " << xcost * dPerc_I << endl;
	cout << "Ruby Cost: " << rcost * dPerc_I << endl;
	cout << "Diamond Cost: " << dicost * dPerc_I << endl;
	cout << "Draconic Cost: " << dcost * dPerc_I << endl;
	cout << endl;

	cout << "Continue with Repair?" << endl;
	cout << "(Y/y)es, (N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;
	
	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return true;
		break;			

	default:
		mRMessage(29);
		cout << endl;
		return false;
		break;
	}
}

bool msgProc::sDRMenu4(int affin, Player& mPlayer, int xcost, int rcost, int dicost, int dcost)
{
	cout << "Due to your current affinity with the entity that owns this station, " << affin << ", the cost for repairing your armor and hull to full strength will be, per percentage point (rounded):" << endl;
	cout << "Xarn Cost: " << xcost << endl;
	cout << "Ruby Cost: " << rcost << endl;
	cout << "Diamond Cost: " << dicost << endl;
	cout << "Draconic Cost: " << dcost << endl;
	cout << endl;

	//Calc percent of armor damaged then round it
	dPerc = (mPlayer.Ship.getSArmor() / mPlayer.Ship.getSMArmor()) * 100;

	dPerc_R = floor(dPerc * 100 + 0.5) / 100;
	dPerc_I = dPerc_R;

	if (dPerc_R >= dPerc_I + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
	{	
		dPerc_I += 1; //then round up
	}

	if (dPerc_I <= 0 ) //To deal with fully depleted armor; not needed for hull
	{
		dPerc_I = 100;
	}
	
	//Calc percent of hull damaged then round it
	dPerc = (mPlayer.Ship.getSHull() / mPlayer.Ship.getSMHull()) * 100;

	dPerc_R = floor(dPerc * 100 + 0.5) / 100;
	dPerc_I2 = dPerc_R;

	if (dPerc_R >= dPerc_I2 + 0.5) //If the value after the decimal is equal to or greater then truncated dPerc_R +0.5
	{	
		dPerc_I2 += 1; //then round up
	}

	cout << "Your armor is damaged by " << dPerc_I << "%.  The cost to repair will be: " << endl;
	cout << "Xarn Cost: " << xcost * dPerc_I << endl;
	cout << "Ruby Cost: " << rcost * dPerc_I << endl;
	cout << "Diamond Cost: " << dicost * dPerc_I << endl;
	cout << "Draconic Cost: " << dcost * dPerc_I << endl;
	cout << endl;	

	cout << "Your hull is damaged by " << dPerc_I2 << "%.  The cost to repair will be: " << endl;
	cout << "Xarn Cost: " << xcost * dPerc_I2 << endl;
	cout << "Ruby Cost: " << rcost * dPerc_I2 << endl;
	cout << "Diamond Cost: " << dicost * dPerc_I2 << endl;
	cout << "Draconic Cost: " << dcost * dPerc_I2 << endl;
	cout << endl;

	cout << "The total cost to repair will be: " << endl;
	cout << "Xarn Cost: " << xcost * (dPerc_I + dPerc_I2) << endl;
	cout << "Ruby Cost: " << rcost * (dPerc_I + dPerc_I2) << endl;
	cout << "Diamond Cost: " << dicost * (dPerc_I + dPerc_I2) << endl;
	cout << "Draconic Cost: " << dcost * (dPerc_I + dPerc_I2) << endl;
	cout << endl;

	cout << "Continue with Repair?" << endl;
	cout << "(Y/y)es, (N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;
	
	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return true;
		break;			

	default:
		mRMessage(29);
		cout << endl;
		return false;
		break;
	}
}

void msgProc::gOver()
{
	cout << "Your ship has been destroyed and your body lost to the sea of stars." << endl;
	cout << "Gameover..." << endl;
}



int msgProc::sMOMenu1()
{
	cout << "Welcome to the Mission Procurement offices aboard this station.  Here you can undertake missions from any number of entities who will reward you for your valued assisstance in helping them with their needs." << endl;
	cout << "Please note that the mission provider is not responbible for any damages or injuries your ship or crew may sustain during the court of a mission and that under law you have no rights to seek recompense for such events." << endl;
	cout << "Please choose from the following options:" << endl;
	cout << endl;

	cout << "1) Undertake a new mission" << endl;
	cout << "2) Request mission evaluation" << endl;
	cout << "3) Leave the mission office" << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice > 3)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::sMOMenu2(int* mID, Player& mPlayer)
{
	cout << "Here are the currently available missions.  Please choose one from the list:" << endl;
	
	rCount = db_mp.getCount("Mission_Data", &bErrors);

	if (bErrors == true)
	{
		cout << "An error has occured.  Check the log and notify the developer's." << endl;
		bErrors = false;
		rCount = 0;
	}

	if (rCount != 0)
	{
		cout << "0) Cancel" << endl;

		for (i = 1; i <= rCount; i++)
		{
			ds_mp.rData("Mission_Data", "select from", i);

			if ((ds_mp.getMLR() <= mPlayer.getCELvl()) && (ds_mp.getMType() != "Bounty" || ds_mp.getMType() != "Main" || ds_mp.getMType() != "EA"))
			{
				cout << i << ") " << ds_mp.getMName() << endl;
			}
		}

		cout << ">";
		cin >> *mID;
		
		if (mID != 0)
		{
			pChoice = 1;
		}

		else
		{
			pChoice = 0;
		}
	}

	return pChoice;
}

int msgProc::sMOMenu3(Player& mPlayer)
{
	cout << "Please choose one of the following missions to evaluate:" << endl;

	if (mPlayer.pMissions.size() == 0)
	{
		cout << "You have not undertaken any missions yet." << endl;
		return 0;
	}

	else
	{
		cout << "0) Cancel" << endl;

		for (i = 0; i < mPlayer.pMissions.size(); i++)
		{
			cout << i+1 << ") " << mPlayer.pMissions.at(i).getMName() << endl;
		}

		cout << ">";
		cin >> pChoice;

		if (pChoice == 0)
		{
			return 0;
		}

		else
		{
			return pChoice-1;
		}
	}
}

int msgProc::sBOMenu1()
{
	cout << "Welcome to the Bounty Procurement offices aboard this station.  Here you can undertake missions from any number of entities who will reward you for your valued assisstance in helping them with their needs." << endl;
	cout << "Please note that the mission provider is not responbible for any damages or injuries your ship or crew may sustain during the court of a mission and that under law you have no rights to seek recompense for such events." << endl;
	cout << "Please choose from the following options:" << endl;
	cout << endl;

	cout << "1) Undertake a new bounty" << endl;
	cout << "2) Request bounty evaluation" << endl;
	cout << "3) Leave the bounty office" << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice > 3)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::sBOMenu2(int* mID, Player& mPlayer)
{
	cout << "Here are the currently available missions.  Please choose one from the list:" << endl;
	
	rCount = db_mp.getCount("Mission_Data", &bErrors);

	if (bErrors == true)
	{
		cout << "An error has occured.  Check the log and notify the developer's." << endl;
		bErrors = false;
		rCount = 0;
	}

	if (rCount != 0)
	{
		cout << "0) Cancel" << endl;

		for (i = 1; i <= rCount; i++)
		{
			ds_mp.rData("Mission_Data", "select from", i);

			if ((ds_mp.getMLR() <= mPlayer.getCELvl()) && (ds_mp.getMType() == "Bounty"))
			{
				cout << i << ") " << ds_mp.getMName() << endl;
			}
		}

		cout << ">";
		cin >> *mID;
		
		if (mID != 0)
		{
			pChoice = 1;
		}

		else
		{
			pChoice = 0;
		}
	}

	return pChoice;
}

int msgProc::sBOMenu3(Player& mPlayer)
{
	cout << "Please choose one of the following missions to evaluate:" << endl;

	if (mPlayer.pMissions.size() == 0)
	{
		cout << "You have not undertaken any missions yet." << endl;
		return 0;
	}

	else
	{
		cout << "0) Cancel" << endl;

		for (i = 0; i < mPlayer.pMissions.size(); i++)
		{
			cout << i+1 << ") " << mPlayer.pMissions.at(i).getMName() << endl;
		}

		cout << ">";
		cin >> pChoice;

		if (pChoice == 0)
		{
			return 0;
		}

		else
		{
			return pChoice-1;
		}
	}
}

int msgProc::sEAFOMenu1()
{
	cout << "Welcome to the Earth Alliance Field offices aboard this station.  Here you can undertake missions for the Earth Alliance." << endl;
	cout << "Please note that if your ship should be destroyed while undertaking a mission for the Earth Alliance it cannot be replaced due to the current nature of the EA economy due to the attempted coup.  You will, however, be compensated for some of the loss." << endl;
	cout << "Please choose from the following options:" << endl;
	cout << endl;

	cout << "1) Undertake a new mission" << endl;
	cout << "2) Request mission evaluation" << endl;
	cout << "3) Leave the Earth Alliance Field office" << endl;
	cout << ">";
	cin >> pChoice;

	if (pChoice < 1 || pChoice > 3)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::sEAFOMenu2(int* mID, Player& mPlayer)
{
	cout << "Here are the currently available missions.  Please choose one from the list:" << endl;
	
	rCount = db_mp.getCount("Mission_Data", &bErrors);

	if (bErrors == true)
	{
		cout << "An error has occured.  Check the log and notify the developer's." << endl;
		bErrors = false;
		rCount = 0;
	}

	if (rCount != 0)
	{
		cout << "0) Cancel" << endl;

		for (i = 1; i <= rCount; i++)
		{
			ds_mp.rData("Mission_Data", "select from", i);

			if ((ds_mp.getMLR() <= mPlayer.getCELvl()) && (ds_mp.getMType() == "Main" || ds_mp.getMType() == "EA"))
			{
				cout << i << ") " << ds_mp.getMName() << endl;
			}
		}

		cout << ">";
		cin >> *mID;
		
		if (mID != 0)
		{
			pChoice = 1;
		}

		else
		{
			pChoice = 0;
		}
	}

	return pChoice;
}

int msgProc::sEAFOMenu3(Player& mPlayer)
{
	cout << "Please choose one of the following missions to evaluate:" << endl;

	if (mPlayer.pMissions.size() == 0)
	{
		cout << "You have not undertaken any missions yet." << endl;
		return 0;
	}

	else
	{
		cout << "0) Cancel" << endl;

		for (i = 0; i < mPlayer.pMissions.size(); i++)
		{
			cout << i+1 << ") " << mPlayer.pMissions.at(i).getMName() << endl;
		}

		cout << ">";
		cin >> pChoice;

		if (pChoice == 0)
		{
			return 0;
		}

		else
		{
			return pChoice-1;
		}
	}	
}

bool msgProc::sSMission(int mID)
{
	ds_mp.rData("Mission_Data","select from",mID);

	cout << ds_mp.getMName() << "'s Mission Information:" << endl; //name
	cout << "Description: " << ds_mp.getMDesc() << endl; //desc
	cout << "Type: " << ds_mp.getMType() << endl; //type
	cout << "Duration: " << ds_mp.getMTLimit() << endl; //duration
	cout << "Difficulty: " << ds_mp.getMDiff() << endl; //diff
	cout << "Location: " << ds_mp.getMSector() << ", " << ds_mp.getMSystem() << endl; //location

	cout << "CBE Level Requirement: " << ds_mp.getMCBEReq() << endl;
	cout << "Ship Class Requirement: " << ds_mp.getMSCReq() << endl;
	cout << "Weapon/Module Requirement: " << ds_mp.getMMWReq() << endl;
	cout << "Target Name: " << ds_mp.getMTName() << endl;
	cout << "Target Ship Class: " << ds_mp.getMTSClass() << endl;
	cout << endl;
	cout << endl;
		
	cout << "Rewards: " << endl;
	cout << "Bounty: " << ds_mp.getMBounty() << endl;
	cout << "Xarn: " << ds_mp.getMXR() << endl;
	cout << "Rubies: " << ds_mp.getMRR() << endl;
	cout << "Diamonds: " << ds_mp.getMDiR() << endl;
	cout << "Draconic: " << ds_mp.getMDR() << endl;
	cout << "Lithium: " << ds_mp.getMLR() << endl;
	cout << "Platinum: " << ds_mp.getMPlR() << endl;
	cout << "Uranium: " << ds_mp.getMUR() << endl;
	cout << "Plutonium: " << ds_mp.getMPR() << endl;
	cout << "Nuclear Waste: " << ds_mp.getMNWR() << endl;
	cout << "EXP: " << ds_mp.getMEXPR() << endl;
	cout << "Gear: " << ds_mp.getMIR() << endl;
	cout << endl;
	cout << endl;

	cout << "Are you sure you want to undertake this mission?" << endl;
	cout << "(Y/y)es|(N/n)o" << endl;
	cout << ">";
	cin >> pCChoice;

	switch(pCChoice)
	{
	case 'y':
	case 'Y':
		return true;
		break;			

	default:
		mRMessage(29);
		cout << endl;
		return false;
		break;
	}
}

int msgProc::sMBRes()
{
	cout << mRMessage(1) << endl;

	for (i = 1; i < 9; i++) //External value flag: condition value
	{
		ds_mp.rData("Resource","select from", i);

		cout << i << ") " << ds_mp.getResName() << endl;
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 8)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;	
}

int msgProc::sMBOre()
{
	cout << mRMessage(1) << endl;

	for (i = 31; i < 34; i++) //External value flag: condition value
	{
		ds_mp.rData("Ore","select from", i);

		cout << i << ") " << ds_mp.getOName() << endl;
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 31 || pChoice > 33)
	{
		cout << mRMessage(5) << endl;
		pChoice = 31;
	}

	return pChoice;
}

int msgProc::sMBAmount(int iCode, string type, Player& mPlayer, Station& stat)
{
	bValid = false;

	while (!bValid)
	{
		cout << mRMessage(2036) << endl << endl;

		if (type == "Resource")
		{
			ds_mp.rData("Resource","select from",iCode);
			xCost = ds_mp.getResXCost();

			cout << "Enter the number of " << ds_mp.getResName() << " you want to purchase." << endl;
		}

		else if (type == "Ore")
		{
			ds_mp.rData("Ore","select from",iCode);
			xCost = ds_mp.getOXCost();

			cout << "Enter the number of " << ds_mp.getOName() << " you want to purchase." << endl;
		}

		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		if (pChoice == 0)
		{
			bValid = true;
		}

		else if (mPlayer.getXarn() < (xCost*pChoice) * stat.getCMulti())
		{
			cout << "You do not have enough Xarn to buy this many items.  Please lower the number of items your want to purchase or enter '0'." << endl;
			mCScreen(true);
		}

		else if (mPlayer.getXarn() >= (xCost*pChoice) * stat.getCMulti())
		{
			bValid = true;
		}
	}

	return pChoice;
}

void msgProc::mCScreen(bool pause)
{
	if (pause)
	{
		system("Pause");
	}
	
	system("CLS");	
}

void msgProc::sSEnabled(Planet* planet, string sname)
{
	cout << planet->getName() << "'s planetary shield system, " << sname << ", has reactivated." << endl << endl;
}

void msgProc::bEMiss_PD(Defense& pDefense)
{
	cout << pDefense.getDName() << "'s attack missed!" << endl << endl;
}

void msgProc::bRewards(Player& mPlayer, int rX, int rR, int rDi, int rD, int rL, int rPl, int rU, int rP, int rNW, int rCXP, int fK, int dK, int cK, int bcK, int bK, int mK, int tK, bool planet)
{
	cout << "Reward Name:	" << "Current Value	" << "->" << " New Value (Added Value)" << endl;
	Sleep(650);
	cout << "Xarn: " << mPlayer.getXarn() << " -> " << rX+mPlayer.getXarn() << "(+" << rX << ")" << endl;
	Sleep(650);
	cout << "Rubies: " << mPlayer.getRubies() << " -> " << rR+mPlayer.getRubies() << "(+" << rR << ")" << endl;
	Sleep(650);
	cout << "Diamonds: " << mPlayer.getDia() << " -> " << rDi+mPlayer.getDia() << "(+" << rDi << ")" << endl;
	Sleep(650);
	cout << "Draconic: " << mPlayer.getDrac() << " -> " << rD+mPlayer.getDrac() << "(+" << rD << ")" << endl;
	Sleep(650);
	cout << "Lithium: " << mPlayer.getLith() << " -> " << rL+mPlayer.getLith() << "(+" << rL << ")" << endl;
	Sleep(650);
	cout << "Platinum: " << mPlayer.getPlat() << " -> " << rPl+mPlayer.getPlat() << "(+" << rPl << ")" << endl;
	Sleep(650);
	cout << "Uranium: " << mPlayer.getUra() << " -> " << rU+mPlayer.getUra() << "(+" << rU << ")" << endl;
	Sleep(650);
	cout << "Plutonium: " << mPlayer.getPlut() << " -> " << rP+mPlayer.getPlut() << "(+" << rP << ")" << endl;
	Sleep(650);
	cout << "Nuclear Waste: " << mPlayer.getNWaste() << " -> " << rNW+mPlayer.getNWaste() << "(+" << rNW << ")" << endl;
	Sleep(650);
	cout << "Combat EXP: " << mPlayer.getCEXP() << " -> " << rCXP+mPlayer.getCEXP() << "(+" << rCXP << ")" << endl;
	Sleep(850);

	if (!planet)
	{
		cout << "Frigate Kills: " << mPlayer.getFKills() << " -> " << fK+mPlayer.getFKills() << "(+" << fK << ")" << endl;
		Sleep(650);
		cout << "Destroyer Kills: " << mPlayer.getDKills() << " -> " << dK+mPlayer.getDKills() << "(+" << dK << ")" << endl;
		Sleep(650);
		cout << "Cruiser Kills: " << mPlayer.getCKills() << " -> " << cK+mPlayer.getCKills() << "(+" << cK << ")" << endl;
		Sleep(650);
		cout << "Battlecruiser Kills: " << mPlayer.getBCKills() << " -> " << bcK+mPlayer.getBCKills() << "(+" << bcK << ")" << endl;
		Sleep(650);
		cout << "Battleship Kills: " << mPlayer.getBKills() << " -> " << bK+mPlayer.getBKills() << "(+" << bK << ")" << endl;
		Sleep(650);
		cout << "Mothership Kills: " << mPlayer.getMKills() << " -> " << mK+mPlayer.getMKills() << "(+" << mK << ")" << endl;
		Sleep(650);
		cout << "Titan Kills: " << mPlayer.getTKills() << " -> " << tK+mPlayer.getTKills() << "(+" << tK << ")" << endl << endl;
		Sleep(650);
	}
	
	mCScreen(true);
}

int msgProc::sMSI1()
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	cout << "1) Move a ship" << endl;
	cout << "2) Move a non-ship item" << endl;
	cout << ">";
	cin >> pChoice;
	cout <<  endl << endl;

	if (pChoice < 0 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	return pChoice;
}

int msgProc::sMSI2()
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	cout << "1) Stored item is on station" << endl;
	cout << "2) Stored item is in your cargohold" << endl;
	cout << ">";
	cin >> pChoice;
	cout <<  endl << endl;

	if (pChoice < 0 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	return pChoice;
}

int msgProc::sMSI3A(Player& mPlayer)
{
	bValid = false;
	nOShips = 0;

	while (!bValid)
	{
		cout << "Please choose from the following docked ships: " << endl;

		cout << mRMessage(2036) << endl << endl;

		for (i = 1; i <= mPlayer.Ship.sCargo.size(); i++)
		{
			if ((i == mPlayer.Ship.sCargo.size()) && (nOShips == 0))
			{
				cout << "There are no ships in your cargo hold." << endl;
				bValid = true;
				pChoice = 0;
				break;
			}

			else if ((i == mPlayer.Ship.sCargo.size()) && (nOShips != 0))
			{
				break;
			}

			else if (mPlayer.Ship.sCargo.at(i-1).isShip())
			{
				cout << i << ") " << mPlayer.Ship.sCargo.at(i-1).sShip.getSName() << endl;
				nOShips += 1;
			}
		}

		if (!bValid)
		{
			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			if (i == 0)
			{
				pChoice = 0;
				bValid = true;
			}

			else if (pChoice < 0 || pChoice > mPlayer.Ship.sCargo.size())
			{
				cout << mRMessage(5) << endl;
				pChoice = 0;
				bValid = true;
			}

			else if (mPlayer.Ship.sCargo.at(pChoice-1).isShip())
			{
				bValid = true;
			}

			else
			{
				cout << "The item you have chosen is not a ship.  Please choose a ship from your station inventory." << endl;
			}
		}
	}

	return pChoice-1;
}

int msgProc::sMSI3B(Station* stat)
{
	bValid = false;
	nOShips = 0;

	while (!bValid)
	{
		cout << "Please choose from the following stored ships: " << endl;

		cout << mRMessage(2036) << endl << endl;

		for (i = 1; i <= stat->sInventory.size(); i++)
		{
			if ((i == stat->sInventory.size()) && (nOShips == 0))
			{
				cout << "There are no ships in your inventory." << endl;
				bValid = true;
				pChoice = 0;
				break;
			}

			else if ((i == stat->sInventory.size()) && (nOShips != 0))
			{
				break;
			}

			else if (stat->sInventory.at(i-1).isShip())
			{
				cout << i << ") " << stat->sInventory.at(i-1).sShip.getSName() << endl;
				nOShips += 1;
			}
		}

		if (!bValid)
		{
			cout << ">";
			cin >> pChoice;
			cout << endl << endl;

			if (i == 0)
			{
				pChoice = 0;
				bValid = true;
			}

			else if (pChoice < 0 || pChoice > stat->sInventory.size())
			{
				cout << mRMessage(5) << endl;
				pChoice = 0;
				bValid = true;
			}

			else if (stat->sInventory.at(pChoice-1).isShip())
			{
				bValid = true;
			}

			else
			{
				cout << "The item you have chosen is not a ship.  Please choose a ship from your station inventory." << endl;
			}
		}
	}

	return pChoice-1;
}

int msgProc::sMSI4A(Station* stat)
{
	bValid = false;

	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	for (i = 0; i < stat->sInventory.size(); i++)
	{
		//Get data from database
		if (stat->sInventory.at(i-1).getIType() == "Weapon")
		{
			ds_mp.rData("Weapon_Data","select from",stat->sInventory.at(i-1).getIID());

			cout << i+1 << ") " << ds_mp.getWName() << endl;
		}

		else if (stat->sInventory.at(i-1).getIType() == "PDefense" || stat->sInventory.at(i-1).getIType() == "PShield")
		{
			ds_mp.rData("Equipment_Data","select from",stat->sInventory.at(i-1).getIID());

			cout << i+1 << ") " << ds_mp.getEName() << endl;
		}

		else if (stat->sInventory.at(i-1).getIType() == "Resource")
		{
			ds_mp.rData("Resrouce","select from",stat->sInventory.at(i-1).getIID());

			cout << i+1 << ") " << ds_mp.getResName() << endl;
		}

		else if (stat->sInventory.at(i-1).getIType() == "Ore")
		{
			ds_mp.rData("Ore","select from",stat->sInventory.at(i-1).getIID());

			cout << i+1 << ") " << ds_mp.getOName() << endl;
		}
	}

	while (!bValid)
	{
		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		if (pChoice < 0 || pChoice > stat->sInventory.size())
		{
			cout << mRMessage(5) << endl;
			pChoice = 0;
			bValid = true;
		}

		else if (pChoice == 0) //Just to catch the 0 here so we do not try to use -1 in the next conditional statement
		{
			bValid = true;
		}

		else if (stat->sInventory.at(pChoice-1).isShip())
		{
			cout << "You have chosen a stored ship.  Please choose a non-ship item." << endl;
		}

		else
		{
			bValid = true;
		}
	}

	return pChoice-1;
}

int msgProc::sMSI4B(Ship* ship)
{
	bValid = false;

	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	for (i = 0; i < ship->sCargo.size(); i++)
	{
		//Get data from database
		if (ship->sCargo.at(i).getIType() == "Weapon")
		{
			ds_mp.rData("Weapon_Data","select from",ship->sCargo.at(i).getIID());

			cout << i+1 << ") " << ds_mp.getWName() << endl;
		}

		else if (ship->sCargo.at(i).getIType() == "PDefense" || ship->sCargo.at(i).getIType() == "PShield")
		{
			ds_mp.rData("Equipment_Data","select from",ship->sCargo.at(i).getIID());

			cout << i+1 << ") " << ds_mp.getEName() << endl;
		}

		else if (ship->sCargo.at(i).getIType() == "Resource")
		{
			ds_mp.rData("Resrouce","select from",ship->sCargo.at(i).getIID());

			cout << i+1 << ") " << ds_mp.getResName() << endl;
		}

		else if (ship->sCargo.at(i).getIType() == "Ore")
		{
			ds_mp.rData("Ore","select from",ship->sCargo.at(i).getIID());

			cout << i+1 << ") " << ds_mp.getOName() << endl;
		}
	}

	while (!bValid)
	{
		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		if (pChoice < 0 || pChoice > ship->sCargo.size())
		{
			cout << mRMessage(5) << endl;
			pChoice = 0;
			bValid = true;
		}

		else if (pChoice == 0) //Just to catch the 0 here so we do not try to use -1 in the next conditional statement
		{
			bValid = true;
		}

		else if (ship->sCargo.at(pChoice-1).isShip())
		{
			cout << "You have chosen a stored ship.  Please choose a non-ship item." << endl;
		}

		else
		{
			bValid = true;
		}
	}

	return pChoice-1;
}

//Mining Functions
int msgProc::mMenu1()
{
	cout << mRMessage(1) << endl;
	cout << "1) Scan nearby asteroids" << endl;
	cout << "2) Target an asteroid" << endl;
	cout << "3) Move the ship" << endl;
	cout << "4) Leave asteroid belt" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 4)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::mMenu2()
{
	cout << mRMessage(1) << endl;
	cout << "1) Mine targeted asteroid" << endl;
	cout << "2) Stop mining targeted asteroid" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::mCTarget(vector<Asteroid> roids, vector<int> scanned, Player& mPlayer, int mTDist)
{
	bValid = false;
	tRoids = 0;

	while (!bValid)
	{
		cout << mRMessage(1) << endl;

		for (i = 0; i <= scanned.size(); i++)
		{
			if ((i == scanned.size()) && (tRoids == 0))
			{
				cout << mRMessage(2045) << endl;
				return -2;
			}

			else if (i < scanned.size())
			{
				tDist = m_mp.getDistance(mPlayer.Ship.getXPos(),roids.at(scanned.at(i)).getXPos(),mPlayer.Ship.getYPos(),roids.at(scanned.at(i)).getYPos(),mPlayer.Ship.getZPos(),roids.at(scanned.at(i)).getZPos());
			}

			if (tDist <= mTDist)
			{
				cout << i+1 << ") " << roids.at(scanned.at(i)).getAName() << endl;
				tRoids += 1;
			}
		}

		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		if (pChoice < 1 || pChoice > scanned.size())
		{
			cout << mRMessage(5) << endl;
			pChoice = 1;
		}

		mCScreen(false);

		cout << "Details for " << roids.at(scanned.at(pChoice-1)).getAName() << ": " << endl << endl;
		cout << "Distance: " << m_mp.getDistance(mPlayer.Ship.getXPos(),roids.at(scanned.at(pChoice-1)).getXPos(),mPlayer.Ship.getYPos(),roids.at(scanned.at(pChoice-1)).getYPos(),mPlayer.Ship.getZPos(),roids.at(scanned.at(pChoice-1)).getZPos()) << "KM" << endl;
		cout << "Size: " << roids.at(scanned.at(pChoice-1)).getASize() << "sg�" << endl;
		cout << "Ore Name: " << roids.at(scanned.at(pChoice-1)).getOName() << endl;
		cout << "Minable Ore: " << roids.at(scanned.at(pChoice-1)).getAOAmount() << " units" << endl << endl;

		cout << "Do you wish to target this asteroid?" << endl;
		cout << "(Y/y)es|(N/n)o" << endl;
		cout << ">";
		cin >> pCChoice;
		
		switch(pCChoice)
		{
		case 'y':
		case 'Y':
			bValid = true;
			break;			

		default:
			break;
		}
	}

	return pChoice-1;
}

int msgProc::plMenu1()
{
	cout << mRMessage(1) << endl;
	cout << "1) Hail the planet" << endl;
	cout << "2) Search for astroid belts" << endl;
	cout << "3) View planet information" << endl;
	cout << "4) Attack planet" << endl;
	cout << "5) Leave" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 5)
	{
		cout << mRMessage(5) << endl;
		pChoice = 1;
	}

	return pChoice;
}

int msgProc::gGTABelt(Planet* gPlanet)
{
	cout << mRMessage(2034) << endl;
	cout << mRMessage(2036) << endl << endl;

	if (gPlanet->belts.size() > 0)
	{
		for (i = 0; i < gPlanet->belts.size(); i++)
		{
			cout << i+1 << ") " << gPlanet->belts.at(i).getABName() << endl;
		}

		cout << ">";
		cin >> pChoice;
		cout << endl << endl;

		if (pChoice < 0 || pChoice > gPlanet->belts.size())
		{
			cout << mRMessage(5) << endl;
			pChoice = 0;
		}
	}

	else
	{
		pChoice = 0;
	}

	return pChoice-1;
}

int msgProc::mGRPoint(vector<int> scanned, vector<Asteroid> roids, Player& mPlayer)
{
	cout << mRMessage(2046) << endl;
	cout << mRMessage(2036) << endl << endl;

	for (i = 0; i < scanned.size(); i++)
	{
		cout << i+1 << ") " << roids.at(scanned.at(i)).getAName() << " " <<  m_mp.getDistance(mPlayer.Ship.getXPos(),roids.at(scanned.at(i)).getXPos(),mPlayer.Ship.getYPos(),roids.at(scanned.at(i)).getYPos(),mPlayer.Ship.getZPos(),roids.at(scanned.at(i)).getZPos()) << "KM" << " (X:" <<  roids.at(scanned.at(i)).getXPos() << ", Y:" << roids.at(scanned.at(i)).getYPos() << ", Z:" << roids.at(scanned.at(i)).getZPos() << ")" << endl;
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > scanned.size())
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	return pChoice-1;
}

bool msgProc::sMECShip()
{
	cout << mRMessage(1) << endl;
	cout << "1) Use bought ship" << endl;
	cout << "2) Store bought ship" << endl;
	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 1 || pChoice > 2)
	{
		cout << mRMessage(5) << endl;
		return false;
	}

	else if (pChoice == 2)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void msgProc::mMLInfo(int ctime, int tdist, float mopc)
{
	cout << "Detected mining laser statistics: " << endl;
	cout << "Mining cycle length: " << ctime << " seconds" << endl;
	cout << "Maximum targeting distance: " << tdist << "KM" << endl;
	cout << "Ore mined per cycle: " << mopc << 'x\178' << endl;
	mCScreen(true);
}

int msgProc::sInv(Station& stat)
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	for (i = 0; i < stat.sInventory.size(); i++)
	{
		if (!stat.sInventory.at(i).isShip())
		{
			if (stat.sInventory.at(i).getIType() == "Weapon")
			{
				ds_mp.rData("Weapon_Data","select from", stat.sInventory.at(i).getIID());

				cout << i+1 << ") " << ds_mp.getWName() << endl;
			}

			else if (stat.sInventory.at(i).getIType() == "PShield" || stat.sInventory.at(i).getIType() == "PDefense")
			{
				ds_mp.rData("Equipment_Data","select from", stat.sInventory.at(i).getIID());

				cout << i+1 << ") " << ds_mp.getEName() << endl;
			}

			else if (stat.sInventory.at(i).getIType() == "Resource")
			{
				ds_mp.rData("Resource","select from", stat.sInventory.at(i).getIID());

				cout << i+1 << ") " << ds_mp.getResName() << endl;
			}

			else if (stat.sInventory.at(i).getIType() == "Ore")
			{
				ds_mp.rData("Ore","select from", stat.sInventory.at(i).getIID());

				cout << i+1 << ") " << ds_mp.getOName() << endl;
			}
		}
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > stat.sInventory.size())
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	mCScreen(true);
	return pChoice-1;	
}
	
int msgProc::sInv_S(Station& stat)
{
	cout << mRMessage(1) << endl;
	cout << mRMessage(2036) << endl << endl;

	for (i = 0; i < stat.sInventory.size(); i++)
	{
		if (stat.sInventory.at(i).isShip())
		{
			ds_mp.rData("Ship_Data","select from", stat.sInventory.at(i).sShip.getID());

			cout << i+1 << ") " << ds_mp.getSName() << endl;
		}
	}

	cout << ">";
	cin >> pChoice;
	cout << endl << endl;

	if (pChoice < 0 || pChoice > stat.sInventory.size())
	{
		cout << mRMessage(5) << endl;
		pChoice = 0;
	}

	mCScreen(true);
	return pChoice-1;	
}