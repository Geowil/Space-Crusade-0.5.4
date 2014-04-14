#include "database.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

Debug d;

Database::Database()
{

}

void Database::openDB(bool* bErrors)
{
	if (sqlite3_open("scDatabase.sqlite",&dBase) != SQLITE_OK)
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 1",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	else
	{
		*bErrors = false;
	}
}

void Database::openSave(bool* bErrors)
{
	if (sqlite3_open("scSave.sqlite",&dBase) != SQLITE_OK)
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 1",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	else
	{
		*bErrors = false;
	}
}

void Database::tableTAccess(string table)
{
	dTable = table;
}

void Database::createStatement(int iID, string operation)
{
	stringstream ss;
	ss << iID;
	
	string sID(ss.str());
	
	if ((operation == "select from") && (iID > 0))
	{
		sqlStr = "Select * From " + dTable + " Where ID = " + sID;
	}

	else if ((operation == "select from") && (iID == 0))
	{
		sqlStr = "Select * From " + dTable;
	}	
}

//All comments on function below apply to all other functions in this class; the comments will only be displayed here

void Database::getSResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK) //Check if the statement can be created
	{			
		result = sqlite3_step(statement); //Call sqlite3_step to execute the query

		if (result == SQLITE_ROW) //If sqlite3_step returns a row continue
		{	
			cols = sqlite3_column_count(statement); //Get the number of columns in this row/table

			if (cols != 0) //If the number of columns is greater than zero
			{
				sResults.push_back(ship()); //Push back sResults to make a new element; REQUIRED else index out of bunds error thrown

				for (i = 0; i <= cols; i++) //Iterate through the columns
				{
					switch(i) //Switch better suited to this than an if/then/else if statement; NOTE: SQLite3 column indecies are ZERO INDEXED, start from 0 if you want the first/primary key column
					{
					case 0:
						sResults.at(0).sID = sqlite3_column_int(statement, i);
						break;

					case 1:
						data =  (char*)sqlite3_column_text(statement,i); //Store returned data temporarily for null checking for string returns

						if (data != NULL) //If data is not NULL continue
						{
							sResults.at(0).sName = data; //Save data into the vector element
							*bErrors = false; //Set to false since no errors occurred
						}

						else //Else if data IS NULL
						{
							*bErrors = true; //Set to true
							createBInfo(); //Call bug info creation function
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt"); //Send data to debug to be written to log file
						}

						break;

					case 2:
						data=  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							sResults.at(0).sDesc = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							sResults.at(0).sClass = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 4:
						sResults.at(0).sShield = (float)sqlite3_column_double(statement,i);
						break;

					case 5:
						sResults.at(0).sArmor = (float)sqlite3_column_double(statement,i);
						break;

					case 6:
						sResults.at(0).sHull = (float)sqlite3_column_double(statement,i);
						break;

					case 7:
						sResults.at(0).sTHPoints = sqlite3_column_int(statement,i);
						break;

					case 8:
						sResults.at(0).sLBanks = sqlite3_column_int(statement,i);
						break;

					case 9:
						sResults.at(0).sMTurrets = sqlite3_column_int(statement,i);
						break;

					case 10:
						sResults.at(0).sRMounts = sqlite3_column_int(statement,i);
						break;

					case 11:
						sResults.at(0).sHWBays = sqlite3_column_int(statement,i);
						break;

					case 12:
						sResults.at(0).sBHolds = sqlite3_column_int(statement,i);
						break;

					case 13:
						sResults.at(0).sMInit = sqlite3_column_int(statement,i);
						break;

					case 14:
						sResults.at(0).sSG2 = (float)sqlite3_column_double(statement,i);
						break;

					case 15:
						sResults.at(0).sCargo = (float)sqlite3_column_double(statement,i);
						break;

					case 16:
						sResults.at(0).sTLevel = sqlite3_column_int(statement,i);
						break;

					case 17:
						sResults.at(0).sXCost = sqlite3_column_int(statement,i);
						break;

					case 18:
						sResults.at(0).sRCost = sqlite3_column_int(statement,i);
						break;

					case 19:
						sResults.at(0).sDiCost = sqlite3_column_int(statement,i);
						break;

					case 20:
						sResults.at(0).sDCost = sqlite3_column_int(statement,i);
						break;

					case 21:
						sResults.at(0).sUCost = sqlite3_column_int(statement,i);
						break;

					case 22:
						sResults.at(0).sPCost = sqlite3_column_int(statement,i);
						break;

					default:				
						break;
					}
				}
			}
	
			else //Else if no columns found
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}

		else  //Else if no row returned
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else //Else if statement could not be processed
	{
		*bErrors = true;
		createBInfo();
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnSResult(vector<ship>& ships)
{
	//Iterate through the results vector and save the data to passed dataSystem vector
	for (i = 0; i < sResults.size(); i++)
	{
		ships.push_back(ship());

		ships.at(i).sID = sResults.at(i).sID;
		ships.at(i).sName = sResults.at(i).sName;
		ships.at(i).sDesc = sResults.at(i).sDesc;
		ships.at(i).sClass = sResults.at(i).sClass;
		ships.at(i).sShield = sResults.at(i).sShield;
		ships.at(i).sArmor = sResults.at(i).sArmor;
		ships.at(i).sHull = sResults.at(i).sHull;
		ships.at(i).sTHPoints = sResults.at(i).sTHPoints;
		ships.at(i).sLBanks = sResults.at(i).sLBanks;
		ships.at(i).sMTurrets = sResults.at(i).sMTurrets;
		ships.at(i).sRMounts = sResults.at(i).sRMounts;
		ships.at(i).sHWBays = sResults.at(i).sHWBays;
		ships.at(i).sBHolds = sResults.at(i).sBHolds;
		ships.at(i).sMInit = sResults.at(i).sMInit;
		ships.at(i).sSG2 = sResults.at(i).sSG2;
		ships.at(i).sCargo = sResults.at(i).sCargo;
		ships.at(i).sTLevel = sResults.at(i).sTLevel; 
		ships.at(i).sXCost = sResults.at(i).sXCost;
		ships.at(i).sRCost = sResults.at(i).sRCost;
		ships.at(i).sDiCost = sResults.at(i).sDiCost;
		ships.at(i).sDCost = sResults.at(i).sDCost;
		ships.at(i).sUCost = sResults.at(i).sUCost;
		ships.at(i).sPCost = sResults.at(i).sPCost;
	}

	sResults.clear(); //Clear the results vector for use later
}


void Database::getWResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				wResults.push_back(weapon());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 0:
						wResults.at(0).wID = sqlite3_column_int(statement, i);
						break;

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							wResults.at(0).wName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							wResults.at(0).wDesc = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						wResults.at(0).wMDamage = (float)sqlite3_column_double(statement,i);
						break;

					case 4:
						wResults.at(0).wMxDamage = (float)sqlite3_column_double(statement,i);
						break;

					case 5:
						wResults.at(0).wMass = (float)sqlite3_column_double(statement,i);
						break;

					case 6:
						wResults.at(0).wMTDistance = sqlite3_column_int(statement,i);
						break;

					case 7:
						wResults.at(0).wMOTDistance = sqlite3_column_int(statement,i);
						break;

					case 8:
						wResults.at(0).wMxOTDistance = sqlite3_column_int(statement,i);
						break;

					case 9:
						wResults.at(0).wMxTDistance = sqlite3_column_int(statement,i);
						break;

					case 10:
						wResults.at(0).wTLevel = sqlite3_column_int(statement,i);
						break;

					case 11:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							wResults.at(0).wClass = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 12:
						wResults.at(0).wSG2 = (float)sqlite3_column_double(statement,i);
						break;

					case 13:
						wResults.at(0).wMCLength = sqlite3_column_int(statement,i);
						break;

					case 14:
						wResults.at(0).wMCAmount = (float)sqlite3_column_double(statement,i);
						break;

					case 15:
						wResults.at(0).wXCost = sqlite3_column_int(statement,i);
						break;

					case 16:
						wResults.at(0).wRCost = sqlite3_column_int(statement,i);
						break;

					case 17:
						wResults.at(0).wDiCost = sqlite3_column_int(statement,i);
						break;

					case 18:
						wResults.at(0).wDCost = sqlite3_column_int(statement,i);
						break;

					case 19:
						wResults.at(0).wLCost = sqlite3_column_int(statement,i);
						break;

					case 20:
						wResults.at(0).wUCost = sqlite3_column_int(statement,i);
						break;

					case 21:
						wResults.at(0).wPCost = sqlite3_column_int(statement,i);
						break;

					case 22:
						wResults.at(0).wNWCost = sqlite3_column_int(statement,i);
						break;

					case 23:
						wResults.at(0).wType = sqlite3_column_int(statement,i);
						break;

					case 24:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							wResults.at(0).wSpecial = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:				
						break;
					}
				}
			}
			
			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnWResult(vector<weapon>& weapons)
{
	for (i = 0; i < wResults.size(); i++)
	{
		weapons.push_back(weapon());

		weapons.at(i).wID = wResults.at(i).wID;
		weapons.at(i).wName = wResults.at(i).wName;
		weapons.at(i).wDesc = wResults.at(i).wDesc;
		weapons.at(i).wMDamage = wResults.at(i).wMDamage;
		weapons.at(i).wMxDamage = wResults.at(i).wMxDamage;
		weapons.at(i).wMass = wResults.at(i).wMass;
		weapons.at(i).wMTDistance = wResults.at(i).wMTDistance;
		weapons.at(i).wMOTDistance = wResults.at(i).wMOTDistance;
		weapons.at(i).wMxOTDistance = wResults.at(i).wMxOTDistance;
		weapons.at(i).wMxTDistance = wResults.at(i).wMxTDistance;
		weapons.at(i).wTLevel = wResults.at(i).wTLevel;
		weapons.at(i).wClass = wResults.at(i).wClass;
		weapons.at(i).wSG2 = wResults.at(i).wSG2;
		weapons.at(i).wMCLength = wResults.at(i).wMCLength;
		weapons.at(i).wMCAmount = wResults.at(i).wMCAmount;
		weapons.at(i).wXCost = wResults.at(i).wXCost;
		weapons.at(i).wRCost = wResults.at(i).wRCost;
		weapons.at(i).wDiCost = wResults.at(i).wDiCost;
		weapons.at(i).wDCost = wResults.at(i).wDCost;
		weapons.at(i).wLCost = wResults.at(i).wLCost;
		weapons.at(i).wUCost = wResults.at(i).wUCost;
		weapons.at(i).wPCost = wResults.at(i).wPCost;
		weapons.at(i).wNWCost = wResults.at(i).wNWCost;
		weapons.at(i).wType = wResults.at(i).wType;
		weapons.at(i).wSpecial = wResults.at(i).wSpecial;
	}

	wResults.clear();
}


void Database::getMResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				mResults.push_back(mission());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 0:
						mResults.at(0).mID = sqlite3_column_int(statement,i);
						break;

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mDesc = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						mResults.at(0).mCBELevel = sqlite3_column_int(statement,i);
						break;

					case 4:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mSCReq = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 5:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mMWReq = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 6:
						mResults.at(0).mTLimit = sqlite3_column_int(statement,i);
						break;

					case 7:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mDifficulty = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 8:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mSector = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 9:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mSystem = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;


					case 10:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mTName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 11:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mTSClass = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 12:
						mResults.at(0).mBounty = sqlite3_column_int(statement,i);
						break;

					case 13:
						mResults.at(0).mXarn = sqlite3_column_int(statement,i);
						break;

					case 14:
						mResults.at(0).mRubies = sqlite3_column_int(statement,i);
						break;

					case 15:
						mResults.at(0).mDiamonds = sqlite3_column_int(statement,i);
						break;

					case 16:
						mResults.at(0).mDraconic = sqlite3_column_int(statement,i);
						break;

					case 17:
						mResults.at(0).mLithium = sqlite3_column_int(statement,i);
						break;

					case 18:
						mResults.at(0).mPlatinum = sqlite3_column_int(statement,i);
						break;

					case 19:
						mResults.at(0).mUranium = sqlite3_column_int(statement,i);
						break;

					case 20:
						mResults.at(0).mPlutonium = sqlite3_column_int(statement,i);
						break;

					case 21:
						mResults.at(0).mNWaste = sqlite3_column_int(statement,i);
						break;

					case 22:
						mResults.at(0).mCEXP = sqlite3_column_int(statement,i);
						break;

					case 23:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mItem = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 24:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mResults.at(0).mType = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}
			
			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}
	
	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnMResult(vector<mission>& missions)
{
	for (i = 0; i < mResults.size(); i++)
	{		
		missions.push_back(mission());

		missions.at(i).mID = mResults.at(i).mID;
		missions.at(i).mName = mResults.at(i).mName;
		missions.at(i).mDesc = mResults.at(i).mDesc;
		missions.at(i).mCBELevel = mResults.at(i).mCBELevel;
		missions.at(i).mSCReq = mResults.at(i).mSCReq;
		missions.at(i).mMWReq = mResults.at(i).mMWReq;
		missions.at(i).mTLimit = mResults.at(i).mTLimit;
		missions.at(i).mDifficulty = mResults.at(i).mDifficulty;
		missions.at(i).mSector = mResults.at(i).mSector;
		missions.at(i).mSystem = mResults.at(i).mSystem;
		missions.at(i).mTName = mResults.at(i).mTName;
		missions.at(i).mTSClass = mResults.at(i).mTSClass;
		missions.at(i).mBounty = mResults.at(i).mBounty;
		missions.at(i).mXarn = mResults.at(i).mXarn;
		missions.at(i).mRubies = mResults.at(i).mRubies;
		missions.at(i).mDiamonds = mResults.at(i).mDiamonds;
		missions.at(i).mDraconic = mResults.at(i).mDraconic;
		missions.at(i).mLithium = mResults.at(i).mLithium;
		missions.at(i).mPlatinum = mResults.at(i).mPlatinum;
		missions.at(i).mUranium = mResults.at(i).mUranium;
		missions.at(i).mPlutonium = mResults.at(i).mPlutonium;
		missions.at(i).mNWaste = mResults.at(i).mNWaste;
		missions.at(i).mCEXP = mResults.at(i).mCEXP;
		missions.at(i).mItem = mResults.at(i).mItem;
		missions.at(i).mType = mResults.at(i).mType;
	}

	mResults.clear();
}


void Database::getMesResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{	
		result = sqlite3_step(statement);

		mesResults.push_back(message());

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				mesResults.push_back(message());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							mesResults.at(0).mes = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;		

					default:				
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnMesResult(vector<message>& messages)
{
	for (i = 0; i < mesResults.size(); i++)
	{
		messages.push_back(message());

		messages.at(i).mes = mesResults.at(i).mes;
	}
	
	mesResults.clear();
}


void Database::getPNResults(bool* bErrors)
{	
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		rows = getCount("Planet_Names", bErrors);

		if (rows != 0)
		{
			for (i = 0; i < rows; i++)
			{
				sqlite3_step(statement);
				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pNResults.push_back(planetName());

					for (i2 = 0; i2 <= cols; i2++)
					{ 					
						switch(i2)
						{
						case 1:
							data = (char*)sqlite3_column_text(statement,1);

							if (data != NULL) //Rudementary try/catch scenario to make sure we do not throw an invalid null pointer assert failure
							{
								pNResults.at(i).pName = data;
								*bErrors = false;
							}

							else //If data is NULL then produce an error report
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else
		{
			*bErrors = true;
			createBInfo();
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}
	
	else 
	{
		*bErrors = true;
		createBInfo();
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPNResult(vector<planetName>& pNames)
{
	
	for (i = 0; i < pNResults.size(); i++)
	{
		pNames.push_back(planetName());

		pNames.at(i).pName = pNResults.at(i).pName;
	}

	pNResults.clear();
}


void Database::getDResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{	
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				dResults.push_back(diplomacy());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 1:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							dResults.at(0).dDisposition = data;
							*bErrors = false;
						}

						else //If data is NULL then produce an error report
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnDResult(vector<diplomacy>& dispositions)
{
	for (i = 0; i < dResults.size(); i++)
	{
		dispositions.push_back(diplomacy());
		dispositions.at(i).dDisposition = dResults.at(i).dDisposition;
	}

	dResults.clear();
}


void Database::getRResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{	
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				rResults.push_back(ranks());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 1:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							rResults.at(0).rkName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}
		
	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnRResult(vector<ranks>& rank)
{
	for (i = 0; i < rResults.size(); i++)
	{
		rank.push_back(ranks());

		rank.at(i).rkName = rResults.at(i).rkName;
	}
	
	rResults.clear();
}


void Database::getRcResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{	
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				rcResults.push_back(race());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 1:
						data = (char*)sqlite3_column_text(statement,i);
						
						if (data != NULL)
						{
							rcResults.at(0).rName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}
						
						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnRcResult(vector<race>& races)
{
	for (i = 0; i < rcResults.size(); i++)
	{
		races.push_back(race());
		
		races.at(i).rName = rcResults.at(i).rName;
	}

	rcResults.clear();
}

void Database::getEResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				eResults.push_back(equips());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{
					case 0:
						eResults.at(0).eID = sqlite3_column_int(statement,i);
						break;
						
					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eDesc = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eType = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 4:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eClass = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;


					case 5:
						eResults.at(0).eTLevel = sqlite3_column_int(statement,i);
						break;

					case 6:
						eResults.at(0).eSPoints = (float)sqlite3_column_double(statement,i);
						break;

					case 7:
						eResults.at(0).eSMPoints = (float)sqlite3_column_double(statement,i);
						break;

					case 8:
						eResults.at(0).eSPRegen = (float)sqlite3_column_double(statement,i);
						break;

					case 9:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eDType = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 10:
						eResults.at(0).eMDmg = (float)sqlite3_column_double(statement,i);
						break;

					case 11:
						eResults.at(0).eMxDmg = (float)sqlite3_column_double(statement,i);
						break;

					case 12:
						eResults.at(0).eRng = sqlite3_column_int(statement,i);
						break;

					case 13:
						eResults.at(0).eSG2 = (float)sqlite3_column_double(statement,i);
						break;

					case 14:
						eResults.at(0).eXCost = sqlite3_column_int(statement,i);
						break;

					case 15:
						eResults.at(0).eRCost = sqlite3_column_int(statement,i);
						break;

					case 16:
						eResults.at(0).eDiCost = sqlite3_column_int(statement,i);
						break;

					case 17:
						eResults.at(0).eDCost = sqlite3_column_int(statement,i);
						break;

					case 18:
						eResults.at(0).eLCost = sqlite3_column_int(statement,i);
						break;

					case 19:
						eResults.at(0).eUCost = sqlite3_column_int(statement,i);
						break;

					case 20:
						eResults.at(0).ePluCost = sqlite3_column_int(statement,i);
						break;

					case 21:
						eResults.at(0).eNWCost = sqlite3_column_int(statement,i);
						break;

					case 22:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							eResults.at(0).eEffect = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 23:
						eResults.at(0).eCXP = sqlite3_column_int(statement,i);
						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnEResults(vector<equips>& equipment)
{
	for (i = 0; i < eResults.size(); i++)
	{
		equipment.push_back(equips());

		equipment.at(i).eID = eResults.at(i).eID;
		equipment.at(i).eName = eResults.at(i).eName;
		equipment.at(i).eDesc = eResults.at(i).eDesc;
		equipment.at(i).eType = eResults.at(i).eType;
		equipment.at(i).eClass = eResults.at(i).eClass;
		equipment.at(i).eTLevel = eResults.at(i).eTLevel;
		equipment.at(i).eSPoints = eResults.at(i).eSPoints;
		equipment.at(i).eSMPoints = eResults.at(i).eSMPoints;
		equipment.at(i).eSPRegen = eResults.at(i).eSPRegen;
		equipment.at(i).eDType = eResults.at(i).eDType;
		equipment.at(i).eMDmg = eResults.at(i).eMDmg;
		equipment.at(i).eMxDmg = eResults.at(i).eMxDmg;
		equipment.at(i).eRng = eResults.at(i).eRng;
		equipment.at(i).eSG2 = eResults.at(i).eSG2;
		equipment.at(i).eXCost = eResults.at(i).eXCost;
		equipment.at(i).eRCost = eResults.at(i).eRCost;
		equipment.at(i).eDiCost = eResults.at(i).eDiCost;
		equipment.at(i).eDCost = eResults.at(i).eDCost;
		equipment.at(i).eLCost = eResults.at(i).eLCost;
		equipment.at(i).eUCost = eResults.at(i).eUCost;
		equipment.at(i).ePluCost = eResults.at(i).ePluCost;
		equipment.at(i).eNWCost = eResults.at(i).eNWCost;
		equipment.at(i).eEffect = eResults.at(i).eEffect;
		equipment.at(i).eCXP = eResults.at(i).eCXP;
	}
	
	eResults.clear();
}

//Name
void Database::getRNResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				nResults.push_back(name());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							nResults.at(0).name_ = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnRNResults(vector<name>& names)
{
	for (i = 0; i < nResults.size(); i++)
	{
		names.push_back(name());

		names.at(0).name_ = nResults.at(0).name_;
	}
	
	nResults.clear();
}

//Resource
void Database::getRDResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				resResults.push_back(resource());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							resResults.at(0).rName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							resResults.at(0).rDesc = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						resResults.at(0).rSG2 = (float)sqlite3_column_double(statement,i);
						break;

					case 4:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							resResults.at(0).rType = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnRDResults(vector<resource>& resources)
{
	for (i = 0; i < resResults.size(); i++)
	{
		resources.push_back(resource());

		resources.at(0).rName = resResults.at(0).rName;
		resources.at(0).rDesc = resResults.at(0).rDesc;
		resources.at(0).rSG2 = resResults.at(0).rSG2;
		resources.at(0).rType = resResults.at(0).rType;
	}
	
	resResults.clear();
}

void Database::getOResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				oResults.push_back(ore());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							oResults.at(0).oName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							oResults.at(0).oDesc = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						oResults.at(0).oSG2 = (float)sqlite3_column_double(statement,i);
						break;

					case 4:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							oResults.at(0).oType = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 5:
						oResults.at(0).oStage = sqlite3_column_int(statement,i);
						break;

					case 6:
						oResults.at(0).oBSize = (float)sqlite3_column_double(statement,i);
						break;

					case 7:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							oResults.at(0).oResource = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 8:
						data = (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							oResults.at(0).oOre = data;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 9:
						oResults.at(0).oRUnits = sqlite3_column_int(statement,i);
						break;

					case 10:
						oResults.at(0).oRProduced = sqlite3_column_int(statement,i);
						break;

					case 11:
						oResults.at(0).oRCost = sqlite3_column_int(statement,i);
						break;

					case 12:
						oResults.at(0).oRPLoss = (float)sqlite3_column_double(statement,i);
						break;

					case 13:
						oResults.at(0).oXCost = sqlite3_column_int(statement,i);
						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnOResults(vector<ore>& ores)
{
	for (i = 0; i < oResults.size(); i++)
	{
		ores.push_back(ore());

		ores.at(0).oName = oResults.at(0).oName;
		ores.at(0).oDesc = oResults.at(0).oDesc;
		ores.at(0).oSG2 = oResults.at(0).oSG2;
		ores.at(0).oType = oResults.at(0).oType;
		ores.at(0).oStage = oResults.at(0).oStage;
		ores.at(0).oBSize = oResults.at(0).oBSize;
		ores.at(0).oResource = oResults.at(0).oResource;
		ores.at(0).oOre = oResults.at(0).oOre;
		ores.at(0).oRUnits = oResults.at(0).oRUnits;
		ores.at(0).oRProduced = oResults.at(0).oRProduced;
		ores.at(0).oRCost = oResults.at(0).oRCost;
		ores.at(0).oRPLoss = oResults.at(0).oRPLoss;
		ores.at(0).oXCost = oResults.at(0).oXCost;
	}
	
	oResults.clear();
}



//Save File

//Save/Load Functions

//Loading Functions

//Player Data
void Database::getPDataResults(bool* bErrors)
{
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			cols = sqlite3_column_count(statement);

			if (cols != 0)
			{
				pDataResults.push_back(playerData());

				for (i = 0; i <= cols; i++)
				{
					switch(i)
					{

					case 1:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							pDataResults.at(0).pName = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 2:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							pDataResults.at(0).pRank = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					case 3:
						pDataResults.at(0).pCXPLevel = sqlite3_column_int(statement,i);
						break;

					case 4:
						pDataResults.at(0).pPDestroyed = sqlite3_column_int(statement,i);
						break;

					case 5:
						pDataResults.at(0).pFKills = sqlite3_column_int(statement,i);
						break;

					case 6:
						pDataResults.at(0).pDKills = sqlite3_column_int(statement,i);
						break;

					case 7:
						pDataResults.at(0).pCKills = sqlite3_column_int(statement,i);
						break;

					case 8:
						pDataResults.at(0).pBCKills = sqlite3_column_int(statement,i);
						break;

					case 9:
						pDataResults.at(0).pBKills = sqlite3_column_int(statement,i);
						break;

					case 10:
						pDataResults.at(0).pMKills = sqlite3_column_int(statement,i);
						break;

					case 11:
						pDataResults.at(0).pTKills = sqlite3_column_int(statement,i);
						break;

					case 12:
						pDataResults.at(0).pCEXP = sqlite3_column_int(statement,i);
						break;

					case 13:
						pDataResults.at(0).pCXPTNL = sqlite3_column_int(statement,i);
						break;

					case 14:
						pDataResults.at(0).pXarn = sqlite3_column_int(statement,i);
						break;

					case 15:
						pDataResults.at(0).pRubies = sqlite3_column_int(statement,i);
						break;

					case 16:
						pDataResults.at(0).pDiamonds = sqlite3_column_int(statement,i);
						break;

					case 17:
						pDataResults.at(0).pDrac = sqlite3_column_int(statement,i);
						break;

					case 18:
						pDataResults.at(0).pLith = sqlite3_column_int(statement,i);
						break;

					case 19:
						pDataResults.at(0).pPla = sqlite3_column_int(statement,i);
						break;

					case 20:
						pDataResults.at(0).pUra = sqlite3_column_int(statement,i);
						break;

					case 21:
						pDataResults.at(0).pPlu = sqlite3_column_int(statement,i);
						break;

					case 22:
						pDataResults.at(0).pNWaste = sqlite3_column_int(statement,i);
						break;

					case 23:
						data =  (char*)sqlite3_column_text(statement,i);

						if (data != NULL)
						{
							pDataResults.at(0).pAffiliation = data;
							*bErrors = false;
						}

						else
						{
							*bErrors = true;
							createBInfo();
							d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
						}

						break;

					default:
						break;
					}
				}
			}

			else
			{
				*bErrors = true;
				createBInfo();
				d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			}
		}
	
		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPDataResults(vector<playerData>& pData)
{
	for (i = 0; i < pDataResults.size(); i++)
	{
		pData.push_back(playerData());

		pData.at(i).pName = pDataResults.at(i).pName;
		pData.at(i).pRank = pDataResults.at(i).pRank;
		pData.at(i).pCXPLevel = pDataResults.at(i).pCXPLevel;
		pData.at(i).pPDestroyed = pDataResults.at(i).pPDestroyed;
		pData.at(i).pFKills = pDataResults.at(i).pFKills;
		pData.at(i).pDKills = pDataResults.at(i).pDKills;
		pData.at(i).pCKills = pDataResults.at(i).pCKills;
		pData.at(i).pBCKills = pDataResults.at(i).pBCKills;
		pData.at(i).pBKills = pDataResults.at(i).pBKills;
		pData.at(i).pMKills = pDataResults.at(i).pMKills;
		pData.at(i).pTKills = pDataResults.at(i).pTKills;
		pData.at(i).pCEXP = pDataResults.at(i).pCEXP;
		pData.at(i).pCXPTNL = pDataResults.at(i).pCXPTNL;
		pData.at(i).pXarn = pDataResults.at(i).pXarn;
		pData.at(i).pRubies = pDataResults.at(i).pRubies;
		pData.at(i).pDiamonds = pDataResults.at(i).pDiamonds;
		pData.at(i).pDrac = pDataResults.at(i).pDrac;
		pData.at(i).pLith = pDataResults.at(i).pLith;
		pData.at(i).pPla = pDataResults.at(i).pPla;
		pData.at(i).pUra = pDataResults.at(i).pUra;
		pData.at(i).pPlu = pDataResults.at(i).pPlu;
		pData.at(i).pNWaste = pDataResults.at(i).pNWaste;
		pData.at(i).pAffiliation = pDataResults.at(i).pAffiliation;
	}
	
	pDataResults.clear();
}

//Player Ship
void Database::getPShipResults(bool* bErrors)
{
	rows = getCount("PShip_Data", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{
				sqlite3_step(statement);
			
				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					plShipResults.push_back(pShip());

					for (i = 0; i <= cols; i++)
					{
						switch(i)
						{

						case 1:
							data =  (char*)sqlite3_column_text(statement,i);

							if (data != NULL)
							{
								plShipResults.at(plShipResults.size()-1).sName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i);

							if (data != NULL)
							{
								plShipResults.at(plShipResults.size()-1).sClass = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							plShipResults.at(plShipResults.size()-1).sTLevel = sqlite3_column_int(statement,i);
							break;

						case 4:
							plShipResults.at(plShipResults.size()-1).sSP = (float)sqlite3_column_double(statement,i);
							break;

						case 5:
							plShipResults.at(plShipResults.size()-1).sAP = (float)sqlite3_column_double(statement,i);
							break;

						case 6:
							plShipResults.at(plShipResults.size()-1).sHP = (float)sqlite3_column_double(statement,i);
							break;

						case 7:
							plShipResults.at(plShipResults.size()-1).sMSP = (float)sqlite3_column_double(statement,i);
							break;

						case 8:
							plShipResults.at(plShipResults.size()-1).sMAP = (float)sqlite3_column_double(statement,i);
							break;

						case 9:
							plShipResults.at(plShipResults.size()-1).sMHP = (float)sqlite3_column_double(statement,i);
							break;

						case 10:
							plShipResults.at(plShipResults.size()-1).sMInit = sqlite3_column_int(statement,i);
							break;

						case 11:
							plShipResults.at(plShipResults.size()-1).sSG2 = (float)sqlite3_column_double(statement,i);
							break;

						case 12:
							plShipResults.at(plShipResults.size()-1).sMCSpace = (float)sqlite3_column_double(statement,i);
							break;

						case 13:
							plShipResults.at(plShipResults.size()-1).sLB = sqlite3_column_int(statement,i);
							break;

						case 14:
							plShipResults.at(plShipResults.size()-1).sMT = sqlite3_column_int(statement,i);
							break;

						case 15:
							plShipResults.at(plShipResults.size()-1).sBH = sqlite3_column_int(statement,i);
							break;

						case 16:
							plShipResults.at(plShipResults.size()-1).sRM = sqlite3_column_int(statement,i);
							break;

						case 17:
							plShipResults.at(plShipResults.size()-1).sHWB = sqlite3_column_int(statement,i);
							break;

						case 18:
							plShipResults.at(plShipResults.size()-1).sWHP = sqlite3_column_int(statement,i);
							break;

						case 19:
							plShipResults.at(plShipResults.size()-1).sULB = sqlite3_column_int(statement,i);
							break;

						case 20:
							plShipResults.at(plShipResults.size()-1).sUMT = sqlite3_column_int(statement,i);
							break;

						case 21:
							plShipResults.at(plShipResults.size()-1).sUBH = sqlite3_column_int(statement,i);
							break;

						case 22:
							plShipResults.at(plShipResults.size()-1).sURM = sqlite3_column_int(statement,i);
							break;

						case 23:
							plShipResults.at(plShipResults.size()-1).sUHWB = sqlite3_column_int(statement,i);
							break;

						case 24:
							plShipResults.at(plShipResults.size()-1).sMWSpreads = sqlite3_column_int(statement,i);
							break;

						case 25:
							plShipResults.at(plShipResults.size()-1).sID = sqlite3_column_int(statement,i);
							break;

						case 26:
							plShipResults.at(plShipResults.size()-1).sSID = sqlite3_column_int(statement,i);
							break;

						case 27:
							plShipResults.at(plShipResults.size()-1).sSTID = sqlite3_column_int(statement,i);
							break;

						case 28:
							data =  (char*)sqlite3_column_text(statement,i);

							if (data != NULL)
							{
								plShipResults.at(plShipResults.size()-1).sLocal = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPShipResults(vector<pShip>& plShip)
{
	for (i = 0; i < plShipResults.size(); i++)
	{
		plShip.push_back(pShip());
		
		plShip.at(i).sName = plShipResults.at(i).sName;
		plShip.at(i).sClass = plShipResults.at(i).sClass;
		plShip.at(i).sTLevel = plShipResults.at(i).sTLevel;
		plShip.at(i).sSP = plShipResults.at(i).sSP;
		plShip.at(i).sAP = plShipResults.at(i).sAP;
		plShip.at(i).sHP = plShipResults.at(i).sHP;
		plShip.at(i).sMSP = plShipResults.at(i).sMSP;
		plShip.at(i).sMAP = plShipResults.at(i).sMAP;
		plShip.at(i).sMHP = plShipResults.at(i).sMHP;
		plShip.at(i).sMInit = plShipResults.at(i).sMInit;
		plShip.at(i).sSG2 = plShipResults.at(i).sSG2;
		plShip.at(i).sMCSpace = plShipResults.at(i).sMCSpace;
		plShip.at(i).sLB = plShipResults.at(i).sLB;
		plShip.at(i).sMT = plShipResults.at(i).sMT;
		plShip.at(i).sBH = plShipResults.at(i).sBH;
		plShip.at(i).sRM = plShipResults.at(i).sRM;
		plShip.at(i).sHWB = plShipResults.at(i).sHWB;
		plShip.at(i).sWHP = plShipResults.at(i).sWHP;
		plShip.at(i).sULB = plShipResults.at(i).sULB;
		plShip.at(i).sUMT = plShipResults.at(i).sUMT;
		plShip.at(i).sUBH = plShipResults.at(i).sUBH;
		plShip.at(i).sURM = plShipResults.at(i).sURM;
		plShip.at(i).sUHWB = plShipResults.at(i).sUHWB;
		plShip.at(i).sMWSpreads = plShipResults.at(i).sMWSpreads; //Max number of usable weapon spreads
		plShip.at(i).sID = plShipResults.at(i).sID;
		plShip.at(i).sSID = plShipResults.at(i).sSID; // Ship ID (will only ever be either -1 (not a stored ship; active player ship) or 1 (stored on player active ship) since stored ships cannot store ships)
		plShip.at(i).sSTID = plShipResults.at(i).sSTID; // Station ID
		plShip.at(i).sLocal = plShipResults.at(i).sLocal; // Is this ship located on another ship or station? (none for player active ship)
	}

	plShipResults.clear();
}

//Ship Spread/Weapon Vector
void Database::getPSSResults(bool* bErrors)
{
	rows = getCount("PShip_WSpreads", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{
				sqlite3_step(statement);
			
				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					spreadResults.push_back(pSSpread());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{

						case 0:
							spreadResults.at(spreadResults.size()-1).sID = sqlite3_column_int(statement,i2); //Vector.size()-1 so that we can have multiple vector rows without having to deal with each row with if/elses
							break;

							/*
							HPSlot Number, Weapon Spread Vector, and Weapon Vector Explanation:

							This is not immediatly identifiable and somewhat difficult to graspe from the code.
							Putting this in Database and in Ship because of the nature of the code above these comment blocks.

							In ship weapon spreads are handled in a semi-relationship (in reference to databases) way where the 
							spread vector contains the hardpoint slot number and weapon type for the weapon located in the specified
							weapon vector (weapon type of Laser and HPSlot of 3 indicates that the weapon element currently being worked with
							is located in slot 4 (0 indexed) of the lBanks vector in Ship.

							In the save file database weapon spread vectors are handled in the same way.  ID is the HPSlot in the weapon vector specified
							by the HPWeapType field.  Position in the actual spread vector is handled by the order in which the records are added to the
							table in the database.

							*/

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								spreadResults.at(spreadResults.size()-1).sWType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							spreadResults.at(spreadResults.size()-1).sPID = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

			

void Database::returnPSSResults(vector<pSSpread>& spreads)
{
	for (i = 0; i < spreadResults.size(); i++)
	{
		spreads.push_back(pSSpread());

		spreads.at(i).sID = spreadResults.at(i).sID;
		spreads.at(i).sWType = spreadResults.at(i).sWType;
		spreads.at(i).sPID = spreadResults.at(i).sPID;
	}
	
	spreadResults.clear();
}

//Ship HP Vectors
void Database::getPSHPVResults(bool* bErrors)
{
	rows = getCount("PShip_WHPVect", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{			
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					hpvectorResults.push_back(pSHPVect());
					
					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							hpvectorResults.at(hpvectorResults.size()-1).sID = sqlite3_column_int(statement,i2);
							break;

						case 1:
							hpvectorResults.at(hpvectorResults.size()-1).wID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								hpvectorResults.at(hpvectorResults.size()-1).sWType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPSHPVResults(vector<pSHPVect>& hpvectors)
{
	for (i = 0; i < hpvectorResults.size(); i++)
	{
		hpvectors.push_back(pSHPVect());

		hpvectors.at(i).sID = hpvectorResults.at(i).sID;
		hpvectors.at(i).wID = hpvectorResults.at(i).wID;
		hpvectors.at(i).sWType = hpvectorResults.at(i).sWType;
	}
	
	hpvectorResults.clear();
}

//Player ship cargo
void Database::getPSCResults(bool* bErrors)
{
	rows = getCount("PShip_Inv", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{			
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pSCResults.push_back(pSInv());
					
					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							pSCResults.at(pSCResults.size()-1).sID = sqlite3_column_int(statement,i2);
							break;
							
						case 2:
							pSCResults.at(pSCResults.size()-1).iID = sqlite3_column_int(statement,i2);
							break;

						case 3:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pSCResults.at(pSCResults.size()-1).iType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							pSCResults.at(pSCResults.size()-1).iAmount = sqlite3_column_int(statement,i2);
							break;

						case 5:
							pSCResults.at(pSCResults.size()-1).iSG2 = (float)sqlite3_column_double(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPSCResults(vector<pSInv>& plSCargo)
{
	for (i = 0; i < pSCResults.size(); i++)
	{
		plSCargo.push_back(pSInv());

		plSCargo.at(i).sID = pSCResults.at(i).sID;
		plSCargo.at(i).iID = pSCResults.at(i).iID;
		plSCargo.at(i).iType = pSCResults.at(i).iType;
		plSCargo.at(i).iAmount = pSCResults.at(i).iAmount;
		plSCargo.at(i).iSG2 = pSCResults.at(i).iSG2;
	}

	pSCResults.clear();
}


//Player Wingmen Data
void Database::getPWMDResults(bool* bErrors)
{
	rows = getCount("Player_W_Data", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{			
			for (i = 0; i < rows; i++)
			{
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pWingmenResults.push_back(pWingmenData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pWingmenResults.at(pWingmenResults.size()-1).pWName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pWingmenResults.at(pWingmenResults.size()-1).pWRank = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							pWingmenResults.at(pWingmenResults.size()-1).pWCXPLevel = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPWMDResults(vector<pWingmenData>& pWingmen)
{
	for (i = 0; i < pWingmenResults.size(); i++)
	{
		pWingmen.push_back(pWingmenData());

		pWingmen.at(i).pWName = pWingmenResults.at(i).pWName;
		pWingmen.at(i).pWRank = pWingmenResults.at(i).pWRank;
		pWingmen.at(i).pWCXPLevel = pWingmenResults.at(i).pWCXPLevel;
	}

	pWingmenResults.clear();
}

//Player Wingmen Ship Data
void Database::getPWSDResults(bool* bErrors)
{
	rows = getCount("PWShip_Data", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{			
			for (i2 = 0; i2 < rows; i2++)
			{
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pWShipResults.push_back(pWShip());

					for (i = 0; i <= cols; i++)
					{
						switch(i)
						{
						case 1:
							pWShipResults.at(pWShipResults.size()-1).pWID = sqlite3_column_int(statement,i2);

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pWShipResults.at(pWShipResults.size()-1).sName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pWShipResults.at(pWShipResults.size()-1).sClass = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							pWShipResults.at(pWShipResults.size()-1).sTLevel = sqlite3_column_int(statement,i2);
							break;

						case 5:
							pWShipResults.at(pWShipResults.size()-1).sSP = (float)sqlite3_column_double(statement,i2);
							break;

						case 6:
							pWShipResults.at(pWShipResults.size()-1).sAP = (float)sqlite3_column_double(statement,i2);
							break;

						case 7:
							pWShipResults.at(pWShipResults.size()-1).sHP = (float)sqlite3_column_double(statement,i2);
							break;

						case 8:
							pWShipResults.at(pWShipResults.size()-1).sMSP = (float)sqlite3_column_double(statement,i2);
							break;

						case 9:
							pWShipResults.at(pWShipResults.size()-1).sMAP = (float)sqlite3_column_double(statement,i2);
							break;

						case 10:
							pWShipResults.at(pWShipResults.size()-1).sMHP = (float)sqlite3_column_double(statement,i2);
							break;

						case 11:
							pWShipResults.at(pWShipResults.size()-1).sMInit = sqlite3_column_int(statement,i2);
							break;

						case 12:
							pWShipResults.at(pWShipResults.size()-1).sLB = sqlite3_column_int(statement,i2);
							break;

						case 13:
							pWShipResults.at(pWShipResults.size()-1).sMT = sqlite3_column_int(statement,i2);
							break;

						case 14:
							pWShipResults.at(pWShipResults.size()-1).sBH = sqlite3_column_int(statement,i2);
							break;

						case 15:
							pWShipResults.at(pWShipResults.size()-1).sRM = sqlite3_column_int(statement,i2);
							break;

						case 16:
							pWShipResults.at(pWShipResults.size()-1).sHWB = sqlite3_column_int(statement,i2);
							break;

						case 17:
							pWShipResults.at(pWShipResults.size()-1).sWHP = sqlite3_column_int(statement,i2);
							break;

						case 18:
							pWShipResults.at(pWShipResults.size()-1).sULB = sqlite3_column_int(statement,i2);
							break;

						case 19:
							pWShipResults.at(pWShipResults.size()-1).sUMT = sqlite3_column_int(statement,i2);
							break;

						case 20:
							pWShipResults.at(pWShipResults.size()-1).sUBH = sqlite3_column_int(statement,i2);
							break;

						case 21:
							pWShipResults.at(pWShipResults.size()-1).sURM = sqlite3_column_int(statement,i2);
							break;

						case 22:
							pWShipResults.at(pWShipResults.size()-1).sUHWB = sqlite3_column_int(statement,i2);
							break;

						case 23:
							pWShipResults.at(pWShipResults.size()-1).sMWSpreads = sqlite3_column_int(statement,i2);

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPWSDResults(vector<pWShip>& pWShips)
{
	for (i = 0; i < pWShipResults.size(); i++)
	{
		pWShips.push_back(pWShip());
		
		pWShips.at(i).pWID = pWShipResults.at(i).pWID;
		pWShips.at(i).sName = pWShipResults.at(i).sName;
		pWShips.at(i).sClass = pWShipResults.at(i).sClass;
		pWShips.at(i).sTLevel = pWShipResults.at(i).sTLevel;
		pWShips.at(i).sSP = pWShipResults.at(i).sSP;
		pWShips.at(i).sAP = pWShipResults.at(i).sAP;
		pWShips.at(i).sHP = pWShipResults.at(i).sHP;
		pWShips.at(i).sMSP = pWShipResults.at(i).sMSP;
		pWShips.at(i).sMAP = pWShipResults.at(i).sMAP;
		pWShips.at(i).sMHP = pWShipResults.at(i).sMHP;
		pWShips.at(i).sMInit = pWShipResults.at(i).sMInit;
		pWShips.at(i).sLB = pWShipResults.at(i).sLB;
		pWShips.at(i).sMT = pWShipResults.at(i).sMT;
		pWShips.at(i).sBH = pWShipResults.at(i).sBH;
		pWShips.at(i).sRM = pWShipResults.at(i).sRM;
		pWShips.at(i).sHWB = pWShipResults.at(i).sHWB;
		pWShips.at(i).sWHP = pWShipResults.at(i).sWHP;
		pWShips.at(i).sULB = pWShipResults.at(i).sULB;
		pWShips.at(i).sUMT = pWShipResults.at(i).sUMT;
		pWShips.at(i).sUBH = pWShipResults.at(i).sUBH;
		pWShips.at(i).sURM = pWShipResults.at(i).sURM;
		pWShips.at(i).sUHWB = pWShipResults.at(i).sUHWB;
		pWShips.at(i).sMWSpreads = pWShipResults.at(i).sMWSpreads; //Max number of usable weapon spreads
	}

	pWShipResults.clear();
}

//Player Wingmen Ship Spread/Weapon Vector
void Database::getPWSSResults(bool* bErrors)
{
	rows = getCount("PWShip_WSpreads", bErrors);

	if (rows > 0)
	{				
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{
				sqlite3_step(statement); //Call this each time to call up a new row

				cols = sqlite3_column_count(statement);
	
				if (cols != 0)
				{
					wspreadResults.push_back(pWSSpread());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{

						case 0:
							wspreadResults.at(wspreadResults.size()-1).sID = sqlite3_column_int(statement,i2); //Vector.size()-1 so that we can have multiple vector rows without having to deal with each row with if/elses
							break;

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								wspreadResults.at(wspreadResults.size()-1).sWType  = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							wspreadResults.at(wspreadResults.size()-1).wID = sqlite3_column_int(statement,i2);
							break;

						case 3:
							wspreadResults.at(wspreadResults.size()-1).sPID = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}


void Database::returnPWSSResults(vector<pWSSpread>& wspreads)
{
	for (i = 0; i < wspreadResults.size(); i++)
	{
		wspreads.push_back(pWSSpread());

		wspreads.at(i).sID = wspreadResults.at(i).sID;
		wspreads.at(i).sWType = wspreadResults.at(i).sWType;
		wspreads.at(i).wID = wspreadResults.at(i).wID;
		wspreads.at(i).sPID = wspreadResults.at(i).sPID;
	}

	wspreadResults.clear();
}

//Player Wingmen Ship HP Vectors
void Database::getPWSHPVResults(bool* bErrors)
{
	rows = getCount("PWShip_WHPVect", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					whpvectorResults.push_back(pWSHPVect());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							whpvectorResults.at(whpvectorResults.size()-1).sID = sqlite3_column_int(statement,i2);
							break;

						case 1:
							whpvectorResults.at(whpvectorResults.size()-1).wep_ID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								whpvectorResults.at(whpvectorResults.size()-1).sWType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							whpvectorResults.at(whpvectorResults.size()-1).wID = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPWSHPVResults(vector<pWSHPVect>& whpvectors)
{
	for (i = 0; i < whpvectorResults.size(); i++)
	{
		whpvectors.push_back(pWSHPVect());

		whpvectors.at(i).sID = whpvectorResults.at(i).sID; //HPSlot value in the weapon vector indicated by the below variable
		whpvectors.at(i).wep_ID = whpvectorResults.at(i).wep_ID; //Weapon ID
		whpvectors.at(i).sWType = whpvectorResults.at(i).sWType; //What type of weapon was stored in the slot
		whpvectors.at(i).wID = whpvectorResults.at(i).wID; //ID of wingmen this spread belongs to		
	}
	
	whpvectorResults.clear();
}

//Mission Data
void Database::getPMDataResults(bool* bErrors)
{
	rows = getCount("Mission_Data", bErrors);

	if (rows > 0)
	{		
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows;  i++)
			{
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pMDataResults.push_back(missionData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							pMDataResults.at(pMDataResults.size()-1).mID = sqlite3_column_int(statement, i2);
							break;

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mDesc = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							pMDataResults.at(pMDataResults.size()-1).mCBEReq = sqlite3_column_int(statement, i2);
							break;

						case 5:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mSCReq = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 6:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mMWReq = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 7:
							pMDataResults.at(pMDataResults.size()-1).mDur = sqlite3_column_int(statement, i2);
							break;

						case 8:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mDifficulty = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 9:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mLSector = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 10:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mLSystem = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 11:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mTName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 12:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mTSClass = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 13:
							pMDataResults.at(pMDataResults.size()-1).mBounty = sqlite3_column_int(statement, i2);
							break;

						case 14:
							pMDataResults.at(pMDataResults.size()-1).mXR = sqlite3_column_int(statement, i2);
							break;

						case 15:
							pMDataResults.at(pMDataResults.size()-1).mRR = sqlite3_column_int(statement, i2);
							break;

						case 16:
							pMDataResults.at(pMDataResults.size()-1).mDiR = sqlite3_column_int(statement, i2);
							break;

						case 17:
							pMDataResults.at(pMDataResults.size()-1).mDR = sqlite3_column_int(statement, i2);
							break;

						case 18:
							pMDataResults.at(pMDataResults.size()-1).mLR = sqlite3_column_int(statement, i2);
							break;

						case 19:
							pMDataResults.at(pMDataResults.size()-1).mPlR = sqlite3_column_int(statement, i2);
							break;

						case 20:
							pMDataResults.at(pMDataResults.size()-1).mUR = sqlite3_column_int(statement, i2);
							break;

						case 21:
							pMDataResults.at(pMDataResults.size()-1).mPR = sqlite3_column_int(statement, i2);
							break;

						case 22:
							pMDataResults.at(pMDataResults.size()-1).mNWR = sqlite3_column_int(statement, i2);
							break;

						case 23:
							pMDataResults.at(pMDataResults.size()-1).mEXPR = sqlite3_column_int(statement, i2);
							break;

						case 24:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pMDataResults.at(pMDataResults.size()-1).mIR = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 25:
							pMDataResults.at(pMDataResults.size()-1).mState = sqlite3_column_int(statement, i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPMDataResults(vector<missionData>& pMData)
{
	for (i = 0; i < pMDataResults.size(); i++)
	{
		pMData.push_back(missionData());

		pMData.at(i).mID = pMDataResults.at(i).mID;
		pMData.at(i).mName = pMDataResults.at(i).mName;
		pMData.at(i).mDesc = pMDataResults.at(i).mDesc;
		pMData.at(i).mType = pMDataResults.at(i).mType;
		pMData.at(i).mCBEReq = pMDataResults.at(i).mCBEReq;
		pMData.at(i).mSCReq = pMDataResults.at(i).mSCReq;
		pMData.at(i).mMWReq = pMDataResults.at(i).mMWReq;
		pMData.at(i).mDur = pMDataResults.at(i).mDur;
		pMData.at(i).mDifficulty = pMDataResults.at(i).mDifficulty;
		pMData.at(i).mLSector = pMDataResults.at(i).mLSector;
		pMData.at(i).mLSystem = pMDataResults.at(i).mLSystem;
		pMData.at(i).mTName = pMDataResults.at(i).mTName;
		pMData.at(i).mTSClass = pMDataResults.at(i).mTSClass;
		pMData.at(i).mBounty = pMDataResults.at(i).mBounty;
		pMData.at(i).mXR = pMDataResults.at(i).mXR;
		pMData.at(i).mRR = pMDataResults.at(i).mRR;
		pMData.at(i).mDiR = pMDataResults.at(i).mDiR;
		pMData.at(i).mDR = pMDataResults.at(i).mDR;
		pMData.at(i).mLR = pMDataResults.at(i).mLR;
		pMData.at(i).mPlR = pMDataResults.at(i).mPlR;
		pMData.at(i).mUR = pMDataResults.at(i).mUR;
		pMData.at(i).mPR = pMDataResults.at(i).mPR;
		pMData.at(i).mNWR = pMDataResults.at(i).mNWR;
		pMData.at(i).mEXPR = pMDataResults.at(i).mEXPR;
		pMData.at(i).mIR = pMDataResults.at(i).mIR;
		pMData.at(i).mState = pMDataResults.at(i).mState;
	}

	pMDataResults.clear();
}

//Relationship Data
void Database::getPRDataResults(bool* bErrors)
{
	rows = getCount("Relationship_Data", bErrors);

	if (rows > 0)
	{		
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows;  i++)
			{
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pRDataResults.push_back(relationData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pRDataResults.at(pRDataResults.size()-1).rName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							pRDataResults.at(pRDataResults.size()-1).rAffinity = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPRDataResults(vector<relationData>& pRData)
{
	for (i = 0; i < pRDataResults.size(); i++)
	{
		pRData.push_back(relationData());

		pRData.at(i).rName = pRDataResults.at(i).rName;
		pRData.at(i).rAffinity = pRDataResults.at(i).rAffinity;
	}

	pRDataResults.clear();
}

//Station Data
void Database::getSDataResults(bool* bErrors)
{
	rows = getCount("Generated_Stations", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					stDataResults.push_back(stationData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							stDataResults.at(stDataResults.size()-1).sID = sqlite3_column_int(statement,i2);
							break;

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								stDataResults.at(stDataResults.size()-1).sName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								stDataResults.at(stDataResults.size()-1).sAffiliation = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								stDataResults.at(stDataResults.size()-1).sDispo = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							stDataResults.at(stDataResults.size()-1).sTLevel = sqlite3_column_int(statement,i2);
							break;

						case 5:
							stDataResults.at(stDataResults.size()-1).sLevel = sqlite3_column_int(statement,i2);
							break;

						case 6:
							stDataResults.at(stDataResults.size()-1).sMSpace = (float)sqlite3_column_double(statement,i);
							break;

						case 7:
							stDataResults.at(stDataResults.size()-1).sCMulti = (float)sqlite3_column_double(statement,i);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnSDataResults(vector<stationData>& stData)
{
	for (i = 0; i < stDataResults.size(); i++)
	{
		stData.push_back(stationData());

		stData.at(i).sID = stDataResults.at(i).sID;
		stData.at(i).sName = stDataResults.at(i).sName;
		stData.at(i).sAffiliation = stDataResults.at(i).sAffiliation;
		stData.at(i).sDispo = stDataResults.at(i).sDispo;
		stData.at(i).sTLevel = stDataResults.at(i).sTLevel;
		stData.at(i).sLevel = stDataResults.at(i).sLevel;
		stData.at(i).sMSpace = stDataResults.at(i).sMSpace;
		stData.at(i).sCMulti = stDataResults.at(i).sCMulti;
	}

	stDataResults.clear();
}

//Player Station Inv
void Database::getSPIResults(bool* bErrors)
{
	rows = getCount("Player_Station_Inv", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pSInventoryResults.push_back(sPInv());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							pSInventoryResults.at(pSInventoryResults.size()-1).sID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							pSInventoryResults.at(pSInventoryResults.size()-1).iID = sqlite3_column_int(statement,i2);
							break;

						case 3:
							pSInventoryResults.at(pSInventoryResults.size()-1).NOI = sqlite3_column_int(statement,i2);
							break;

						case 4:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pSInventoryResults.at(pSInventoryResults.size()-1).iType = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 5:
							pSInventoryResults.at(pSInventoryResults.size()-1).iSG2 = (float)sqlite3_column_double(statement,i);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnSPIResults(vector<sPInv>& pSInventory)
{
	for (i = 0; i < pSInventoryResults.size(); i++)
	{
		pSInventory.push_back(sPInv());
		
		pSInventory.at(i).sID = pSInventoryResults.at(i).sID;
		pSInventory.at(i).iID = pSInventoryResults.at(i).iID;
		pSInventory.at(i).NOI = pSInventoryResults.at(i).NOI;
		pSInventory.at(i).iType = pSInventoryResults.at(i).iType;
		pSInventory.at(i).iSG2 = pSInventoryResults.at(i).iSG2;
	}

	pSInventoryResults.clear();
}

//Planet Data
void Database::getPDResults(bool* bErrors)
{
	rows = getCount("Generated_Planets", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					plDataResults.push_back(planetData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							plDataResults.at(plDataResults.size()-1).pID = sqlite3_column_int(statement,i2);
							break;

						case 1:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								plDataResults.at(plDataResults.size()-1).pName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2: 
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								plDataResults.at(plDataResults.size()-1).pAffiliation = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 3:
							data =  (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								plDataResults.at(plDataResults.size()-1).pDispo = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								plDataResults.at(plDataResults.size()-1).pRace = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 5:
							plDataResults.at(plDataResults.size()-1).bIsPOwned = sqlite3_column_int(statement,i2);
							break;

						case 6:
							plDataResults.at(plDataResults.size()-1).bIsDestroyed = sqlite3_column_int(statement,i2);
							break;

						case 7:
							plDataResults.at(plDataResults.size()-1).pEKS = (float)sqlite3_column_double(statement,i2);
							break;

						case 8:
							plDataResults.at(plDataResults.size()-1).pSize = (float)sqlite3_column_double(statement,i2);
							break;

						case 9:
							plDataResults.at(plDataResults.size()-1).pCPop = sqlite3_column_int64(statement,i2);
							break;

						case 10:
							plDataResults.at(plDataResults.size()-1).pMPop = sqlite3_column_int64(statement,i2);
							break;						

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPDResults(vector<planetData>& plData)
{
	for (i = 0; i < plDataResults.size(); i++)
	{
		plData.push_back(planetData());

		plData.at(i).pID = plDataResults.at(i).pID;
		plData.at(i).pName = plDataResults.at(i).pName;
		plData.at(i).pAffiliation = plDataResults.at(i).pAffiliation;
		plData.at(i).pDispo = plDataResults.at(i).pDispo;
		plData.at(i).pRace = plDataResults.at(i).pRace;
		plData.at(i).bIsPOwned = plDataResults.at(i).bIsPOwned;
		plData.at(i).bIsDestroyed = plDataResults.at(i).bIsDestroyed;
		plData.at(i).pEKS = plDataResults.at(i).pEKS;
		plData.at(i).pSize = plDataResults.at(i).pSize;
		plData.at(i).pCPop = plDataResults.at(i).pCPop;
		plData.at(i).pMPop = plDataResults.at(i).pMPop;

		find = "\"";
		temp = "'";

		foundAt = plData.at(i).pName.find(find);
			
		if (foundAt != string::npos)
		{
			 plData.at(i).pName.replace(foundAt,1,temp);
		}
	}

	plDataResults.clear();
}

//Planetary Defenses
void Database::getPDefResults(bool* bErrors)
{
	rows = getCount("Planetary_Defenses", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pDefensesResults.push_back(pDefData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							pDefensesResults.at(pDefensesResults.size()-1).pID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							pDefensesResults.at(pDefensesResults.size()-1).pDID = sqlite3_column_int(statement,i2);
							break;	
						
						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnPDefResults(vector<pDefData>& pDefenses)
{
	for (i = 0; i < pDefensesResults.size(); i++)
	{
		pDefenses.push_back(pDefData());

		pDefenses.at(i).pID = pDefensesResults.at(i).pID;
		pDefenses.at(i).pDID = pDefensesResults.at(i).pDID;
	}

	pDefensesResults.clear();
}

//Planetary Shield
void Database::getPSDResults(bool* bErrors)
{
	rows = getCount("Planetary_Shields", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pShieldsResults.push_back(pSData());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							pShieldsResults.at(pShieldsResults.size()-1).pID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							pShieldsResults.at(pShieldsResults.size()-1).mID = sqlite3_column_int(statement,i2);
							break;							

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}

			finalize(statement, bErrors);
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}
}

void Database::returnPSDResults(vector<pSData>& pShields)
{
	for (i = 0; i < pShieldsResults.size(); i++)
	{
		pShields.push_back(pSData());

		pShields.at(i).pID = pShieldsResults.at(i).pID;
		pShields.at(i).mID = pShieldsResults.at(i).mID;
	}
	
	pShieldsResults.clear();
}

//Planet A. Belts
void Database::getPABResults(bool* bErrors)
{
	rows = getCount("GP_Belts", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pABResults.push_back(pABelts());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							pABResults.at(pABResults.size()-1).bID = sqlite3_column_int(statement,i2);
							break;

						case 2:
							pABResults.at(pABResults.size()-1).pID = sqlite3_column_int(statement,i2);
							break;							

						case 3:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pABResults.at(pABResults.size()-1).bName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							pABResults.at(pABResults.size()-1).bSize = (float)sqlite3_column_double(statement,i2);
							break;

						case 5:
							pABResults.at(pABResults.size()-1).bBIsFull = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}

			finalize(statement, bErrors);
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}
}

void Database::returnPABResults(vector<pABelts>& belts)
{
	for (i = 0; i < pABResults.size(); i++)
	{
		belts.push_back(pABelts());

		belts.at(i).bID = pABResults.at(i).bID;
		belts.at(i).pID = pABResults.at(i).pID;
		belts.at(i).bName = pABResults.at(i).bName;
		belts.at(i).bSize = pABResults.at(i).bSize;
		belts.at(i).bBIsFull = pABResults.at(i).bBIsFull;		
	}

	pABResults.clear();
}

//Planet AB Roids
void Database::getPABRResults(bool* bErrors)
{
	rows = getCount("GPB_Roids", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					pABRResults.push_back(pABRoids());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 0:
							pABRResults.at(pABRResults.size()-1).aID = sqlite3_column_int(statement,i2);
							break;

						case 1:
							pABRResults.at(pABRResults.size()-1).bID = sqlite3_column_int(statement,i2);
							break;		

						case 2:
							pABRResults.at(pABRResults.size()-1).pID = sqlite3_column_int(statement,i2);

						case 3:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pABRResults.at(pABRResults.size()-1).aName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 4:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pABRResults.at(pABRResults.size()-1).aDesc = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 5:
							pABRResults.at(pABRResults.size()-1).aSize = (float)sqlite3_column_double(statement,i2);
							break;

						case 6:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								pABRResults.at(pABRResults.size()-1).aOName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 7:
							pABRResults.at(pABRResults.size()-1).aOID = sqlite3_column_int(statement,i2);
							break;

						case 8:
							pABRResults.at(pABRResults.size()-1).aOAmount = (float)sqlite3_column_double(statement,i2);
							break;

						case 9:
							pABRResults.at(pABRResults.size()-1).xPos = sqlite3_column_int(statement,i2);
							break;

						case 10:
							pABRResults.at(pABRResults.size()-1).yPos = sqlite3_column_int(statement,i2);
							break;

						case 11:
							pABRResults.at(pABRResults.size()-1).zPos = sqlite3_column_int(statement,i2);
							break;

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}

			finalize(statement, bErrors);
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}
}

void Database::returnPABRResults(vector<pABRoids>& roids)
{
	for (i = 0; i < pABRResults.size(); i++)
	{
		roids.push_back(pABRoids());

		roids.at(i).aID = pABRResults.at(i).aID;
		roids.at(i).bID = pABRResults.at(i).bID;
		roids.at(i).pID = pABRResults.at(i).pID;
		roids.at(i).aName = pABRResults.at(i).aName;
		roids.at(i).aDesc = pABRResults.at(i).aDesc;
		roids.at(i).aSize = pABRResults.at(i).aSize;
		roids.at(i).aOName = pABRResults.at(i).aOName;
		roids.at(i).aOID = pABRResults.at(i).aOID;
		roids.at(i).aOAmount = pABRResults.at(i).aOAmount;
		roids.at(i).xPos = pABRResults.at(i).xPos;
		roids.at(i).yPos = pABRResults.at(i).yPos;
		roids.at(i).zPos = pABRResults.at(i).zPos;
	}

	pABRResults.clear();
}

//Save Flags
void Database::getSFlagResults(bool* bErrors)
{	
	rows = getCount("Save_Flags", bErrors);

	if (rows > 0)
	{
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < rows; i++)
			{		
				sqlite3_step(statement);

				cols = sqlite3_column_count(statement);

				if (cols != 0)
				{
					sFlags.push_back(saveFlag());

					for (i2 = 0; i2 <= cols; i2++)
					{
						switch(i2)
						{
						case 1:
							data = (char*)sqlite3_column_text(statement,i2);

							if (data != NULL)
							{
								sFlags.at(sFlags.size()-1).sfName = data;
								*bErrors = false;
							}

							else
							{
								*bErrors = true;
								createBInfo();
								d.createBReport("SQL Code 6","Data returned equals NULL",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
							}

							break;

						case 2:
							sFlags.at(sFlags.size()-1).sfValue = sqlite3_column_int(statement,i2);
							break;							

						default:
							break;
						}
					}
				}

				else
				{
					*bErrors = true;
					createBInfo();
					d.createBReport("SQL Code 7","No column queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
				}
			}
		}

		else 
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	}

	else 
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 8","No row queried",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
}

void Database::returnSFlagResults(vector<saveFlag>& saveFlags)
{
	for (i = 0; i < sFlags.size(); i++)
	{
		saveFlags.push_back(saveFlag());

		saveFlags.at(i).sfName = sFlags.at(i).sfName;
		saveFlags.at(i).sfValue = sFlags.at(i).sfValue;
	}

	sFlags.clear();
}

//Save Data
void Database::sData(vector<playerData> pData, vector<pShip> plShip, vector<pSSpread> plSSpreads, vector<pSHPVect> plSHPVectors, vector<pSInv> plSCargo, vector<pWingmenData> pWMData, vector<pWShip> pWMSData, vector<pWSSpread> pWMSSpreads, vector<pWSHPVect> pWMSHPVectors, vector<stationData> stData, vector<sPInv> sPInventory, vector<planetData> plData, vector<pDefData> plDData, vector<pSData> plSData, vector<pABelts> belts, vector<pABRoids> roids, vector<missionData> pMData, vector<relationData> pRData, bool* bErrors)
{
	//Set bErrors to false so that we do not trip the message in dataSystem by accident
	*bErrors = false;

	//Part of debugging to try and fix database locked error
	openSave(bErrors); //Open saveDB here for now; part of debugging
	
	//Player Data
		
	cout << "Saving player data";
	//Delete previous save data
	dData("Player_Data", bErrors);
	
	sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL,NULL, &error);	
	
	sqlStr = "Insert Into Player_Data (ID, Name, Rank, CEXPLvl, Planets_Destroyed, FKills, DKills, CKills, BCKills, BKills, MKills, TKills, CEXP, CEXPTNL, Xarn, Rubies, Diamonds, Draconic, Lithium, Platinum, Uranium, Plutonium, Nuclear_Waste, Affiliated) Values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
	
	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		//Save new data
		sqlS1 = pData.at(0).pName;
		sqlS2 = pData.at(0).pRank;
		sqlI1 = pData.at(0).pCXPLevel;
		sqlI2 = pData.at(0).pPDestroyed;
		sqlI3 = pData.at(0).pFKills;
		sqlI4 = pData.at(0).pDKills;
		sqlI5 = pData.at(0).pCKills;
		sqlI6 = pData.at(0).pBCKills;
		sqlI7 = pData.at(0).pBKills;
		sqlI8 = pData.at(0).pMKills;
		sqlI9 = pData.at(0).pTKills;
		sqlI10 = pData.at(0).pCEXP;
		sqlI11 = pData.at(0).pCXPTNL;
		sqlI12 = pData.at(0).pXarn;
		sqlI13 = pData.at(0).pRubies;
		sqlI14 = pData.at(0).pDiamonds;
		sqlI15 = pData.at(0).pDrac;
		sqlI16 = pData.at(0).pLith;
		sqlI17 = pData.at(0).pPla;
		sqlI18 = pData.at(0).pUra;
		sqlI19 = pData.at(0).pPlu;
		sqlI20 = pData.at(0).pNWaste;
		sqlS3 = pData.at(0).pAffiliation;

		//Bind parameters
		sqlite3_bind_int(statement,1,1);
		sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
		sqlite3_bind_text(statement,3,sqlS2.c_str(),sqlS2.size(),SQLITE_TRANSIENT);
		sqlite3_bind_int(statement,4,sqlI1);
		sqlite3_bind_int(statement,5,sqlI2);
		sqlite3_bind_int(statement,6,sqlI3);
		sqlite3_bind_int(statement,7,sqlI4);
		sqlite3_bind_int(statement,8,sqlI5);
		sqlite3_bind_int(statement,9,sqlI6);
		sqlite3_bind_int(statement,10,sqlI7);
		sqlite3_bind_int(statement,11,sqlI8);
		sqlite3_bind_int(statement,12,sqlI9);
		sqlite3_bind_int(statement,13,sqlI10);
		sqlite3_bind_int(statement,14,sqlI11);
		sqlite3_bind_int(statement,15,sqlI12);
		sqlite3_bind_int(statement,16,sqlI13);
		sqlite3_bind_int(statement,17,sqlI14);
		sqlite3_bind_int(statement,18,sqlI15);
		sqlite3_bind_int(statement,19,sqlI16);
		sqlite3_bind_int(statement,20,sqlI17);
		sqlite3_bind_int(statement,21,sqlI18);
		sqlite3_bind_int(statement,22,sqlI19);
		sqlite3_bind_int(statement,23,sqlI20);
		sqlite3_bind_text(statement,24,sqlS3.c_str(),sqlS3.size(),SQLITE_TRANSIENT);

		sqlite3_step(statement);

		cout << ".";
	}

	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	sqlite3_finalize(statement);
	sqlite3_exec(dBase,"END TRANSACTION",NULL,NULL,&error);

	cout << " Done" << endl << endl;

	//Ship Data

	cout << "Saving ship data";

	//Delete previous save data
	dData("PShip_Data", bErrors);

	sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL,NULL,&error);
	sqlStr = "Insert Into PShip_Data (ID, Name, Class, TLevel, SPoints, APoints, HPoints, MSPoints, MAPoints, MHPoints, MInit, SG2, MCSpace, LB, MT, BH, RM, HWB, WHP, ULB, UMT, UBH, URM, UHWB, Max_Weapon_Spreads, SID, SSID, STID, Location) Values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		for (i = 0; i < plShip.size(); i++)
		{
			//Save new data
			sqlS1 = plShip.at(i).sName;
			sqlS2 = plShip.at(i).sClass;
			sqlI1 = plShip.at(i).sTLevel;
			sqlF1 = plShip.at(i).sSP;
			sqlF2 = plShip.at(i).sAP;
			sqlF3 = plShip.at(i).sHP;
			sqlF4 = plShip.at(i).sMSP;
			sqlF5 = plShip.at(i).sMAP;
			sqlF6 = plShip.at(i).sMHP;
			sqlI2 = plShip.at(i).sMInit;
			sqlF7 = plShip.at(i).sSG2;
			sqlF8 = plShip.at(i).sMCSpace;
			sqlI3 = plShip.at(i).sLB;
			sqlI4 = plShip.at(i).sMT;
			sqlI5 = plShip.at(i).sBH;
			sqlI6 = plShip.at(i).sRM;
			sqlI7 = plShip.at(i).sHWB;
			sqlI8 = plShip.at(i).sWHP;
			sqlI9 = plShip.at(i).sULB;
			sqlI10 = plShip.at(i).sUMT;
			sqlI11 = plShip.at(i).sUBH;
			sqlI12 = plShip.at(i).sURM;
			sqlI13 = plShip.at(i).sUHWB;
			sqlI14 = plShip.at(i).sMWSpreads;
			sqlI15 = plShip.at(i).sID;
			sqlI16 = plShip.at(i).sSID;
			sqlI17 = plShip.at(i).sSTID;
			sqlS3 = plShip.at(i).sLocal;

			sqlite3_bind_int(statement,1,1);
			sqlite3_bind_text(statement,2,sqlS1.c_str(), sqlS1.size(),SQLITE_TRANSIENT);
			sqlite3_bind_text(statement,3,sqlS2.c_str(), sqlS2.size(),SQLITE_TRANSIENT);
			sqlite3_bind_int(statement,4,sqlI1);
			sqlite3_bind_double(statement,5,sqlF1);
			sqlite3_bind_double(statement,6,sqlF2);
			sqlite3_bind_double(statement,7,sqlF3);
			sqlite3_bind_double(statement,8,sqlF4);
			sqlite3_bind_double(statement,9,sqlF5);
			sqlite3_bind_double(statement,10,sqlF6);
			sqlite3_bind_int(statement,11,sqlI2);
			sqlite3_bind_double(statement,12,sqlF7);
			sqlite3_bind_double(statement,13,sqlF8);
			sqlite3_bind_int(statement,14,sqlI3);
			sqlite3_bind_int(statement,15,sqlI4);
			sqlite3_bind_int(statement,16,sqlI5);
			sqlite3_bind_int(statement,17,sqlI6);
			sqlite3_bind_int(statement,18,sqlI7);
			sqlite3_bind_int(statement,19,sqlI8);
			sqlite3_bind_int(statement,20,sqlI9);
			sqlite3_bind_int(statement,21,sqlI10);
			sqlite3_bind_int(statement,22,sqlI11);
			sqlite3_bind_int(statement,23,sqlI12);
			sqlite3_bind_int(statement,24,sqlI13);
			sqlite3_bind_int(statement,25,sqlI14);
			sqlite3_bind_int(statement,26,sqlI15);
			sqlite3_bind_int(statement,27,sqlI16);
			sqlite3_bind_int(statement,28,sqlI17);
			sqlite3_bind_text(statement,29,sqlS3.c_str(), sqlS3.size(),SQLITE_TRANSIENT);
		}

		sqlite3_step(statement);
		sqlite3_reset(statement);

		cout << ".";
	}

	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}
	
	finalize(statement, bErrors);
	sqlite3_exec(dBase,"END TRANSACTION",NULL,NULL,&error);
	cout << "Done" << endl << endl;

	//Ship Spreads	

	//Delete previous save data
	dData("PShip_WSpreads", bErrors);

	if (plSSpreads.size() > 0)
	{
		cout << "Saving ship weapon spread data";

		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PShip_WSpreads (ID, HPWeapType, Spread_ID) Values (?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plSSpreads.size(); i++)
			{
				sqlI1 = plSSpreads.at(i).sID;
				sqlS1 = plSSpreads.at(i).sWType;
				sqlI2 = plSSpreads.at(i).sPID;

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_text(statement,2,sqlS1.c_str(), sqlS1.size(), SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,3,sqlI3);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}
		}

		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}

		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSWSpreads";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;

		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSWSpreads";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Ship HP Vectors

	//Delete previous save data
	dData("PShip_WHPVect", bErrors);

	if (plSHPVectors.size() > 0)
	{
		cout << "Saving ship weapon data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PShip_WHPVect (ID, Weap_ID, Weap_Type) Values (?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plSHPVectors.size(); i++)
			{
				sqlI2 = plSHPVectors.at(i).sID;
				sqlI3 = plSHPVectors.at(i).wID;
				sqlS1 = plSHPVectors.at(i).sWType;

				sqlite3_bind_int(statement,1,sqlI2);
				sqlite3_bind_int(statement,2,sqlI3);
				sqlite3_bind_text(statement,3,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSWHPVect";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSWHPVect";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Ship Cargo

	//Delete previous save data
	dData("PShip_Inv", bErrors);

	if (plSCargo.size() > 0)
	{
		cout << "Saving ship cargo data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PShip_Inv (TID, SID, IID, IType, IAmount, ISG2) Values (?,?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plSCargo.size(); i++)
			{
				sqlI1 = i; //Table ID
				sqlI2 = plSCargo.at(i).sID; //Ship ID
				sqlI3 = plSCargo.at(i).iID; //Item ID
				sqlS1 = plSCargo.at(i).iType; //Item Type
				sqlI4 = plSCargo.at(i).iAmount; //Item Amount
				sqlF1 = plSCargo.at(i).iSG2; //Item SG2

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_int(statement,2,sqlI2);
				sqlite3_bind_int(statement,3,sqlI3);
				sqlite3_bind_text(statement,4,sqlS1.c_str(),sqlS3.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,5,sqlI4);
				sqlite3_bind_double(statement,6,sqlF1);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSInv";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PSInv";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}

	//Player Wingmen Data

	//Delete previous save data
	dData("Player_W_Data", bErrors);

	if (pWMData.size() > 0)
	{
		cout << "Saving player wingmen data";

		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
	
		sqlStr = "Insert Into Player_W_Data (ID, Name, Rank, CEXPLvl) Values (?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < pWMData.size(); i++)
			{
				sqlS1 = pWMData.at(i).pWName;
				sqlS2 = pWMData.at(i).pWRank;
				sqlI1 = pWMData.at(i).pWCXPLevel;

				sqlite3_bind_int(statement,1,i);
				sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,3,sqlS2.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,4,sqlI1);

				sqlite3_step(statement);
				sqlite3_reset(statement);				

				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//W. Ship Data

	//Delete previous save data
	dData("PWShip_Data", bErrors);

	if (pWMSData.size() > 0)
	{
		cout << "Saving player wingmen ship data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PWShip_Data (TID, WID, Name, Class, TLevel, SPoints, APoints, HPoints, MSPoints, MAPoints, MHPoints, MInit, LB, MT, BH, RM, HWB, WHP, ULB, UMT, UBH, URM, UHWB, Max_Weapon_Spreads) Values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			sqlI14 = pWMSData.at(i).pWID;
			sqlS1 = pWMSData.at(i).sName;
			sqlS2 = pWMSData.at(i).sClass;
			sqlI1 = pWMSData.at(i).sTLevel;
			sqlF1 = pWMSData.at(i).sSP;
			sqlF2 = pWMSData.at(i).sAP;
			sqlF3 = pWMSData.at(i).sHP;
			sqlF4 = pWMSData.at(i).sMSP;
			sqlF5 = pWMSData.at(i).sMAP;
			sqlF6 = pWMSData.at(i).sMHP;
			sqlI2 = pWMSData.at(i).sMInit;
			sqlI3 = pWMSData.at(i).sLB;
			sqlI4 = pWMSData.at(i).sMT;
			sqlI5 = pWMSData.at(i).sBH;
			sqlI6 = pWMSData.at(i).sRM;
			sqlI7 = pWMSData.at(i).sHWB;
			sqlI8 = pWMSData.at(i).sWHP;
			sqlI9 = pWMSData.at(i).sULB;
			sqlI10 = pWMSData.at(i).sUMT;
			sqlI11 = pWMSData.at(i).sUBH;
			sqlI12 = pWMSData.at(i).sURM;
			sqlI13 = pWMSData.at(i).sUHWB;
			sqlI15 = pWMSData.at(i).sMWSpreads;

			sqlite3_bind_int(statement,1,sqlI14);
			sqlite3_bind_text(statement,2,sqlS1.c_str(), sqlS1.size(),SQLITE_TRANSIENT);
			sqlite3_bind_text(statement,3,sqlS2.c_str(), sqlS2.size(),SQLITE_TRANSIENT);
			sqlite3_bind_int(statement,4,sqlI1);
			sqlite3_bind_double(statement,5,sqlF1);
			sqlite3_bind_double(statement,6,sqlF2);
			sqlite3_bind_double(statement,7,sqlF3);
			sqlite3_bind_double(statement,8,sqlF4);
			sqlite3_bind_double(statement,9,sqlF5);
			sqlite3_bind_double(statement,10,sqlF6);
			sqlite3_bind_int(statement,11,sqlI2);
			sqlite3_bind_int(statement,12,sqlI3);
			sqlite3_bind_int(statement,13,sqlI4);
			sqlite3_bind_int(statement,14,sqlI5);
			sqlite3_bind_int(statement,15,sqlI6);
			sqlite3_bind_int(statement,16,sqlI7);
			sqlite3_bind_int(statement,17,sqlI8);
			sqlite3_bind_int(statement,18,sqlI9);
			sqlite3_bind_int(statement,19,sqlI10);
			sqlite3_bind_int(statement,20,sqlI11);
			sqlite3_bind_int(statement,21,sqlI12);
			sqlite3_bind_int(statement,22,sqlI13);
			sqlite3_bind_int(statement,23,sqlI14);
		
			sqlite3_step(statement);
			sqlite3_reset(statement);
			
			cout << ".";
		}

		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}

		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Ship Spreads

	//Delete previous save data
	dData("PWShip_WSpreads", bErrors);

	if (pWMSSpreads.size() > 0)
	{
		cout << "Saving player wingmen ship weapon spread data";
	
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PWShip_WSpreads (ID, HPWeapType, WID, Spread_ID) Values (?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < pWMSSpreads.size(); i++)
			{
				sqlI1 = pWMSSpreads.at(i).sID;
				sqlS1 = pWMSSpreads.at(i).sWType;
				sqlI2 = pWMSSpreads.at(i).wID;
				sqlI3 = pWMSSpreads.at(i).sPID;

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,3,sqlI2);
				sqlite3_bind_int(statement,4,sqlI3);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}	
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSWSpreads";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSWSpreads";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//W. Ship HP Vectors

	//Delete previous save data
	dData("PWShip_WHPVect", bErrors);

	if (pWMSHPVectors.size() > 0)
	{
		cout << "Saving player wingmen ship weapon data";
	
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into PWShip_WHPVect (ID, Weap_ID, Weap_Type, WID) Values (?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < pWMSHPVectors.size(); i++)
			{
				sqlI1 = pWMSHPVectors.at(i).sID;
				sqlI2 = pWMSHPVectors.at(i).wID;
				sqlS1 = pWMSHPVectors.at(i).sWType;
				sqlI3 = pWMSHPVectors.at(i).wID;

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_int(statement,2,sqlI2);
				sqlite3_bind_text(statement,3,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,4,sqlI3);

				sqlite3_step(statement);
				sqlite3_reset(statement);

				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSWHPVect";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PWSWHPVect";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Player Mission Data

	//Delete previous save data
	dData("Mission_Data", bErrors);

	if (pMData.size() > 0)
	{
		cout << "Saving player mission data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into Mission_Data (ID, Name, Description, Type, CBE_Lvl_Req, Ship_Class_Req, Item_Req, Duration, Difficulty, Locale_Sector, Locale_System, Target_Name, Target_Ship_Class, Bounty, Xarn_Reward, Ruby_Reward, Diamond_Reward, Draconic_Reward, Lithium_Reward, Platinum_Reward, Uranium_Reward, Plutonium_Reward, Nuclear_Waste_Reward, CEXP_Reward, Item_Reward, Mission_State) Values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < pMData.size(); i++)
			{
				sqlI1 = pMData.at(i).mID;
				sqlS1 = pMData.at(i).mName;
				sqlS2 = pMData.at(i).mDesc;
				sqlS3 = pMData.at(i).mType;
				sqlI2 = pMData.at(i).mCBEReq;
				sqlS4 = pMData.at(i).mSCReq; //ship requirement
				sqlS5 = pMData.at(i).mMWReq; //module/weapon requirement
				sqlI3 = pMData.at(i).mDur; //duration in days
				sqlS6 = pMData.at(i).mDifficulty;
				sqlS7 = pMData.at(i).mLSector; //location; sector
				sqlS8 = pMData.at(i).mLSystem; //location; system
				sqlS9 = pMData.at(i).mTName; //target name
				sqlS10 = pMData.at(i).mTSClass; //target ship class
				sqlI4 = pMData.at(i).mBounty;
				sqlI5 = pMData.at(i).mXR; //xarn reward
				sqlI6 = pMData.at(i).mRR; //ruby reward
				sqlI7 = pMData.at(i).mDiR; //diamond reward
				sqlI8 = pMData.at(i).mDR; //draconic reward
				sqlI9 = pMData.at(i).mLR; //lithium reward
				sqlI10 = pMData.at(i).mPlR; //platinum reward
				sqlI11 = pMData.at(i).mUR; //uranium reward
				sqlI12 = pMData.at(i).mPR; //plutonium reward
				sqlI13 = pMData.at(i).mNWR; //nuclear waste reward
				sqlI14 = pMData.at(i).mEXPR; //exp reward
				sqlS11 = pMData.at(i).mIR; //item reward;
				sqlI15 = pMData.at(i).mState; //Mission State

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_text(statement,2,sqlS1.c_str(), sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,3,sqlS2.c_str(), sqlS2.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,4,sqlS3.c_str(), sqlS3.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,5,sqlI2);
				sqlite3_bind_text(statement,6,sqlS4.c_str(), sqlS4.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,7,sqlS5.c_str(), sqlS5.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,8,sqlI3);
				sqlite3_bind_text(statement,9,sqlS6.c_str(), sqlS6.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,10,sqlS7.c_str(), sqlS7.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,11,sqlS8.c_str(), sqlS8.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,12,sqlS9.c_str(), sqlS9.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,13,sqlS10.c_str(), sqlS10.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,14,sqlI4);
				sqlite3_bind_int(statement,15,sqlI5);
				sqlite3_bind_int(statement,16,sqlI6);
				sqlite3_bind_int(statement,17,sqlI7);
				sqlite3_bind_int(statement,18,sqlI8);
				sqlite3_bind_int(statement,19,sqlI9);
				sqlite3_bind_int(statement,20,sqlI10);
				sqlite3_bind_int(statement,21,sqlI11);
				sqlite3_bind_int(statement,22,sqlI12);
				sqlite3_bind_int(statement,23,sqlI13);
				sqlite3_bind_int(statement,24,sqlI14);
				sqlite3_bind_text(statement,25,sqlS11.c_str(), sqlS11.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,26,sqlI15);

				sqlite3_step(statement);
				sqlite3_reset(statement);

				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
				
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PMData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PMData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Player Relation Data

	//Delete previous save data
	dData("Relationship_Data", bErrors);

	if (pRData.size() > 0)
	{
		cout << "Saving player relationship data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into Relationship_Data (RID, Relation_Name, Relation_Affinity) Values (?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < pRData.size(); i++)
			{
				sqlS1 = pRData.at(i).rName;
				sqlI1 = pRData.at(i).rAffinity;

				sqlite3_bind_int(statement,1,i);
				sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,3,sqlI1);
			
				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
	
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PRData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "PRData";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Station Data

	//Delete previous save data
	dData("Generated_Stations", bErrors);

	if (stData.size() > 0)
	{
		cout << "Saving station data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sqlStr = "Insert Into Generated_Stations (ID, Name, Affiliation, Disposition, TLevel, SLevel, Max_Player_Storage_Space, Cost_Multiplier) Values (?,?,?,?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			for (i = 0; i < stData.size(); i++)
			{
				sqlI1 = stData.at(i).sID;
				sqlS1 = stData.at(i).sName;
				sqlS2 = stData.at(i).sAffiliation;
				sqlS3 = stData.at(i).sDispo;
				sqlI2 = stData.at(i).sTLevel;
				sqlI3 = stData.at(i).sLevel;
				sqlF2 = stData.at(i).sMSpace;
				sqlF3 = stData.at(i).sCMulti;

				sqlite3_bind_int(statement,1,sqlI1);
				sqlite3_bind_text(statement,2,sqlS1.c_str(), sqlS1.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,3,sqlS2.c_str(), sqlS2.size(),SQLITE_TRANSIENT);
				sqlite3_bind_text(statement,4,sqlS3.c_str(), sqlS3.size(),SQLITE_TRANSIENT);
				sqlite3_bind_int(statement,5,sqlI2);
				sqlite3_bind_int(statement,6,sqlI3);
				sqlite3_bind_double(statement,7,sqlF2);
				sqlite3_bind_double(statement,8,sqlF3);
			
				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GStats";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GStats";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Player Station Inventory

	//Delete previous save data
	dData("Player_Station_Inv", bErrors);

	if (sPInventory.size() > 0)
	{
		cout << "Saving station inventory data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into Player_Station_Inv (TID, SID, IID, Number_Of_Items, Type) Values (?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < sPInventory.size(); i++)
			{
				sqlI1 = sPInventory.at(i).sID;
				sqlI2 = sPInventory.at(i).iID;
				sqlI3 = sPInventory.at(i).NOI;
				sqlS1 = sPInventory.at(i).iType;

				sqlite3_bind_int(statement,1,i);
				sqlite3_bind_int(statement,2,sqlI1);
				sqlite3_bind_int(statement,3,sqlI2);
				sqlite3_bind_int(statement,4,sqlI3);
				sqlite3_bind_text(statement,5,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");	
		}
		
		finalize(statement, bErrors);\
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GSInv";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GSInv";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Planet Data

	//Delete previous save data
	dData("Generated_Planets", bErrors);

	if (plData.size() > 0)
	{
		cout << "Saving planet data";
		
		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sqlStr = "Insert Into Generated_Planets (ID, Name, Affiliation, Disposition, Race, Player_Owned, Is_Destroyed, EKS, Planet_Size, Current_Pop, Max_Pop) Values (?,?,?,?,?,?,?,?,?,?,?);";

		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plData.size(); i++)
			{
				sqlI1 = plData.at(i).pID;
				sqlS1 = plData.at(i).pName;
				sqlS2 = plData.at(i).pAffiliation;
				sqlS3 = plData.at(i).pDispo;
				sqlS4 = plData.at(i).pRace;
				sqlI2 = plData.at(i).bIsPOwned;
				sqlI3 = plData.at(i).bIsDestroyed;
				sqlF1 = plData.at(i).pEKS;
				sqlF2 = plData.at(i).pSize;
				sqlLLI1 = plData.at(i).pCPop;
				sqlLLI2 = plData.at(i).pMPop;

				find = "'";
				temp = "\"";

				foundAt = sqlS1.find(find);

				if (foundAt != string::npos)
				{
					sqlS1.replace(foundAt,1,temp);
				}

				//Bind parameters
                sqlite3_bind_int(statement,1,sqlI1);
                sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
                sqlite3_bind_text(statement,3,sqlS2.c_str(),sqlS2.size(),SQLITE_TRANSIENT);
                sqlite3_bind_text(statement,4,sqlS3.c_str(),sqlS3.size(),SQLITE_TRANSIENT);
                sqlite3_bind_text(statement,5,sqlS4.c_str(),sqlS4.size(),SQLITE_TRANSIENT);
                sqlite3_bind_int(statement,6,sqlI2);
                sqlite3_bind_int(statement,7,sqlI3);
                sqlite3_bind_double(statement,8,sqlF1);
                sqlite3_bind_double(statement,9,sqlF2);
                sqlite3_bind_int64(statement,10,sqlLLI1);
                sqlite3_bind_int64(statement,11,sqlLLI2);
				
				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}
		}

		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");	
		}

		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION", NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPlanets";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPlanets";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}


	//Planet Defenses

	//Delete previous save data
	dData("Planetary_Defenses", bErrors);

	if (plDData.size() > 0)
	{
		cout << "Saving planetary defense data";

		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);

		sqlStr = "Insert Into Planetary_Defenses (TID, PID, PDID) Values (?,?,?);";
		
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plDData.size(); i++)
			{
				sqlI1 = plDData.at(i).pID;
				sqlI2 = plDData.at(i).pDID;

				sqlite3_bind_int(statement,1,i);
				sqlite3_bind_int(statement,2,sqlI1);
				sqlite3_bind_int(statement,3,sqlI2);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPDef";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPDef";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}

	//Planet Shields

	//Delete previous save data
	dData("Planetary_Shields", bErrors);

	if (plSData.size() > 0)
	{
		cout << "Saving planetary shield data";

		sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
		
		sqlStr = "Insert Into Planetary_Shields (TID, PID, MID) Values (?,?,?);";
		
		if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
		{
			//Save new data
			for (i = 0; i < plSData.size(); i++)
			{
				sqlI1 = plSData.at(i).pID;
				sqlI2 = plSData.at(i).mID;
			
				sqlite3_bind_int(statement,1,i);
				sqlite3_bind_int(statement,2,sqlI1);
				sqlite3_bind_int(statement,3,sqlI2);

				sqlite3_step(statement);
				sqlite3_reset(statement);
				
				cout << ".";
			}			
		}
		
		else
		{
			*bErrors = true;
			createBInfo();		
			d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		}
		
		finalize(statement, bErrors);
		sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPShd";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
		cout << "Done" << endl << endl;
	}

	else
	{
		sFlags_Temp.push_back(saveFlag());
		sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPShd";
		sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 0;
	}

	//Planet ABelts
	//Delete old data
	dData("GP_Belts", bErrors);

	cout << "Saving astroid belts";

	sqlite3_exec(dBase,"BEGIN TRANSACTION", NULL, NULL, &error);

	sqlStr = "Insert Into GP_Belts (TID, BID, PID, BName, BSize, BFull) Values (?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		//Save new data
		for (i = 0, i2 = 0; i < belts.size(); i++, i2++)
		{
			sqlI1 = i;
			sqlI2 = belts.at(i).bID;
			sqlI3 = belts.at(i).pID;
			sqlS1 = belts.at(i).bName;
			sqlF1 = belts.at(i).bSize;			
			sqlI4 = belts.at(i).bBIsFull;

			sqlite3_bind_int(statement,1,sqlI1);
			sqlite3_bind_int(statement,2,sqlI2);
			sqlite3_bind_int(statement,3,sqlI3);
			sqlite3_bind_text(statement,4,sqlS1.c_str(), sqlS1.size(), SQLITE_TRANSIENT);
			sqlite3_bind_double(statement, 5, sqlF1);
			sqlite3_bind_int(statement, 6, sqlI4);

			sqlite3_step(statement);
			sqlite3_reset(statement);

			//Only print a . for every ten belts saved
			if (i2 == 9)
			{
				cout << ".";
				i2 = 0;
			}
		}			
	}

	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
	sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

	sFlags_Temp.push_back(saveFlag());
	sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPBelt";
	sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
	cout << "Done" << endl << endl;


	//Planet AB Rpods
	//Delete old data
	dData("GPB_Roids", bErrors);

	cout << "Saving astroid belts";

	sqlite3_exec(dBase,"BEGIN TRANSACTION", NULL, NULL, &error);

	sqlStr = "Insert Into GPB_Roids (AID, BID, PID, AName, ADesc, ASize, OName, AOID, OAmount, XPos, YPos, ZPos) Values (?,?,?,?,?,?,?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		//Save new data
		for (i = 0, i2 = 0; i < roids.size(); i++, i2++)
		{
			sqlI1 = roids.at(i).aID;
			sqlI2 = roids.at(i).bID;
			sqlI3 = roids.at(i).pID;
			sqlS1 = roids.at(i).aName;
			sqlS2 = roids.at(i).aDesc;
			sqlF1 = roids.at(i).aSize;
			sqlS3 = roids.at(i).aOName;
			sqlI4 = roids.at(i).aOID;
			sqlF2 = roids.at(i).aOAmount;
			sqlI5 = roids.at(i).xPos;
			sqlI6 = roids.at(i).yPos;
			sqlI7 = roids.at(i).zPos;

			sqlite3_bind_int(statement,1,sqlI1);
			sqlite3_bind_int(statement,2,sqlI2);
			sqlite3_bind_int(statement,3,sqlI3);
			sqlite3_bind_text(statement,4,sqlS1.c_str(), sqlS1.size(), SQLITE_TRANSIENT);
			sqlite3_bind_text(statement,5,sqlS2.c_str(), sqlS2.size(), SQLITE_TRANSIENT);
			sqlite3_bind_double(statement, 6, sqlF1);
			sqlite3_bind_text(statement,7,sqlS3.c_str(), sqlS3.size(), SQLITE_TRANSIENT);
			sqlite3_bind_int(statement, 8, sqlI4);
			sqlite3_bind_double(statement, 9, sqlF2);
			sqlite3_bind_int(statement, 10, sqlI5);
			sqlite3_bind_int(statement, 11, sqlI6);
			sqlite3_bind_int(statement, 12, sqlI7);

			sqlite3_step(statement);
			sqlite3_reset(statement);

			//Only add a . for every 200 asteroids saved
			if (i2 == 199)
			{
				cout << ".";

				i2 = 0;
			}
		}			
	}

	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	finalize(statement, bErrors);
	sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

	sFlags_Temp.push_back(saveFlag());
	sFlags_Temp.at(sFlags_Temp.size()-1).sfName = "GPBRoid";
	sFlags_Temp.at(sFlags_Temp.size()-1).sfValue = 1;
	cout << "Done" << endl << endl;

	//Delete Previous Save Data
	dData("Save_Flags",bErrors);

	cout << "Saving save flags";

	sqlite3_exec(dBase,"BEGIN TRANSACTION",NULL, NULL, &error);
	
	sqlStr = "Insert Into Save_Flags (ID, Flag_Name, Flag_Value) Values (?,?,?);";

	if (sqlite3_prepare_v2(dBase, sqlStr.c_str(), sqlStr.size(), &statement, 0) == SQLITE_OK)
	{
		for (i = 0; i < sFlags_Temp.size(); i++)
		{
			sqlI1 = i+1;
			sqlS1 = sFlags_Temp.at(i).sfName;
			sqlI2 = sFlags_Temp.at(i).sfValue;

			sqlite3_bind_int(statement,1,i);
			sqlite3_bind_text(statement,2,sqlS1.c_str(),sqlS1.size(),SQLITE_TRANSIENT);
			sqlite3_bind_int(statement,3,sqlI2);

			sqlite3_step(statement);
			sqlite3_reset(statement);
			
			cout << ".";
		}		
	}
	
	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 2",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");	
	}

	finalize(statement, bErrors);
	sqlite3_exec(dBase,"END TRANSACTION",NULL, NULL, &error);

	if (sqlite3_close(dBase) != SQLITE_OK)
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	else
	{
		*bErrors = false;
	}
	
	cout << "Done" << endl << endl;
}

void Database::dData(string table, bool* bErrors)
{
    sqlStr2 = "Delete From " + table;

    if (sqlite3_prepare_v2(dBase, sqlStr2.c_str(), sqlStr2.size(), &statement2, 0) == SQLITE_OK)
    {           
        sqlite3_step(statement2);
        *bErrors = false;
    }

    else
    {
        *bErrors = true;
        createBInfo();      
        d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
    }

	finalize(statement2, bErrors);
}

int Database::getCount(string table, bool* bErrors)
{
	sqlStr2 = "Select Count(*) From " + table;

	if (sqlite3_prepare_v2(dBase, sqlStr2.c_str(), sqlStr2.size(), &statement2, 0) == SQLITE_OK)
	{			
		result = sqlite3_step(statement2);
		
		if (result == SQLITE_ROW)
		{
			*bErrors = false;
			int nRows = sqlite3_column_int(statement2,0);

			finalize(statement2, bErrors);

			return nRows;
		}

		else
		{
			createBInfo();		
			d.createBReport("SQL Code 5","No row(s) returned, check for problems",bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
			finalize(statement2, bErrors);
			return 0;
		}
	}

	else
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
		finalize(statement2, bErrors);
		return 0;
	}

	finalize(statement2, bErrors);
}

void Database::finalize(sqlite3_stmt* stmt, bool* bErrors)
{
	if (sqlite3_finalize(stmt) != SQLITE_OK)
	{
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}
	
	else
	{
		*bErrors = false;
	}
}

void Database::closeDB(bool* bErrors)
{
	if (sqlite3_close(dBase) != SQLITE_OK)
	{		
		*bErrors = true;
		createBInfo();		
		d.createBReport("SQL Code 3",sqlite3_errmsg(dBase),bLocale + to_string(__LINE__),bTDate,"./SC_Log.txt");
	}

	else
	{
		*bErrors = false;
	}
}

void Database::createBInfo()
{
	file = __FILE__;
	bLocale = "File: " + file + "  Line: ";

	time = __TIME__;
	date = __DATE__;

	bTDate = date + "  " + time;
}