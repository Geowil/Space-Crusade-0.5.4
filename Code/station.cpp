#include <string>
#include <vector>
#include <iostream>
#include "station.h"
#include "datasystem.h"
#include "msgproc.h"

using namespace std;

dataSystem ds_st;
msgProc mp_st;

Station::Station()
{
	sID = 0;
	sName = "default";
	sTLevel = 0;
	sSLevel = 0;
	sCMulti = 0.0f;
	sDispo = "Default";
		
	//begin station storage definitions
	sUSpace = 0.00f;
	tempSpace = 0.0f;
	sMSSpace = 1000.00f; //max storage space (default)
}

void Station::initStation(int stid, string sname, int stlevel, int sslevel, float cmulti, string dispo, string affil) //pseudo constructor for stationProc array and other story/mission based stations
{
	sID = stid;
	sName = sname;
	sTLevel = stlevel;
	sSLevel = sslevel;
	sCMulti = cmulti;
	sDispo = dispo;
	sAffil = affil;

	//begin station storage definitions
	sUSpace = 0.00f;
	tempSpace = 0.0f;
	sMSSpace = 1000.00f; //max storage space
}

string Station::getName()
{
	return sName;
}

bool Station::bIsEAEnemy()
{
	if (sAffil == "Juslorth" || sAffil == "Sluikan")
	{
		return true;
	}

	else
	{
		return false;
	}
}

string Station::getAffil()
{
	return sAffil;
}

string Station::getDispo()
{
	return sDispo;
}

int Station::getSLevel()
{
	return sSLevel;
}

int Station::getTLevel()
{
	return sTLevel;
}

float Station::getCMulti()
{
	return sCMulti;
}

int Station::getISize()
{
	return sInventory.size();
}

void Station::updateISpace(float f, string operation)
{
	if (operation == "add")
	{
		sMSSpace += f;
	}

	else if (operation == "sub")
	{
		sMSSpace -= f;
	}

	else if (operation == "set")
	{
		sMSSpace = f;
	}
}

int Station::getISItem(int i)
{
	return sInventory.at(i).getIID();
}

int Station::getISIAmount(int i)
{
	return sInventory.at(i).getIAmount();
}

int Station::getSID()
{
	return sID;
}

void Station::setSID(int id)
{
	sID = id;
}

float Station::getCSUsed()
{
	return sUSpace;
}

float Station::getMUSpace()
{
	return sMSSpace;
}

void Station::setName(string name)
{
	sName = name;
}

void Station::setSLevel(int lvl)
{
	sSLevel = lvl;
}

void Station::setTLevel(int lvl)
{
	sTLevel = lvl;
}

void Station::setAffil(string affil)
{
	sAffil = affil;
}

void Station::setDispo(string dispo)
{
	sDispo = dispo;
}

void Station::setCMulti(float cmulti)
{
	sCMulti = cmulti;
}

bool Station::sSItem(int iCode, int amount, string type, float space)
{
	sInventory.push_back(sInv());

	sInventory.at(sInventory.size()-1).setIID(iCode);
	sInventory.at(sInventory.size()-1).setIAmount(amount);
	sInventory.at(sInventory.size()-1).setIType(type);
	sInventory.at(sInventory.size()-1).setISpace(space);

	return true;
}

bool Station::sSShip(int iCode, bool bought, bool exchange, Player& mPlayer, Game* mGame)
{
	ds_st.rData("Ship_Data","select from",iCode);

	//No need to check storage space, should have been checked BEFORE this point and found to be true (that ship could be stored)
	//Player elected to store the new ship
	if (!exchange)
	{
		if (bought)
		{			
			cout << "Storing your purcahse..." << endl;

			tempShip.initShip2(ds_st.getSName(), ds_st.getSClass(), ds_st.getSShield(), ds_st.getSShield(), ds_st.getSArmor(), ds_st.getSArmor(), ds_st.getSHull(), ds_st.getSHull(), ds_st.getSLB(), ds_st.getSMT(), ds_st.getSBH(), ds_st.getSRM(), ds_st.getSHWB(), ds_st.getSWHP(), ds_st.getSMInit(), ds_st.getSTLevel(), ds_st.getSSG2(), ds_st.getSCargo(), -1, sID, "Station");
						
			sInventory.push_back(sInv(tempShip, true, iCode, 1));

			return true;
		}

		else if (!bought)
		{
			cout << "Begining the storage process..." << endl;

			iPChoice = mp_st.sMSI2(); //Get player to tell us where the item they want to move is located (station or ship?)

			if (iPChoice == 0)
			{
				return false;
			}

			else if (iPChoice == 1) //If ship is on station
			{
				sSHSlot = mp_st.sMSI3B(this); //Get the player to pick a ship to move into ship cargo hold from their station storage

				if (sSHSlot != -1)
				{			
					bDone = false;

					while (!bDone)
					{
						//tempShip_C = mPlayer.Ship;
						//tempShip_N = sSHold.at(sSHSlot);

						if (mPlayer.Ship.checkSpace(sInventory.at(sSHSlot).sShip.getSSG2()))
						{
							//Move new to temp
							tempShip.initShip2(sInventory.at(sSHSlot).sShip.getSName(), sInventory.at(sSHSlot).sShip.getSClass(), sInventory.at(sSHSlot).sShip.getSShield(), sInventory.at(sSHSlot).sShip.getSShield(), sInventory.at(sSHSlot).sShip.getSArmor(), sInventory.at(sSHSlot).sShip.getSArmor(), sInventory.at(sSHSlot).sShip.getSHull(), sInventory.at(sSHSlot).sShip.getSHull(), sInventory.at(sSHSlot).sShip.getLHP(), sInventory.at(sSHSlot).sShip.getMTP(), sInventory.at(sSHSlot).sShip.getBH(), sInventory.at(sSHSlot).sShip.getRM(), sInventory.at(sSHSlot).sShip.getHWB(), sInventory.at(sSHSlot).sShip.getSWHP(), sInventory.at(sSHSlot).sShip.getMInit(), sInventory.at(sSHSlot).sShip.getSTLevel(), sInventory.at(sSHSlot).sShip.getSSG2(), sInventory.at(sSHSlot).sShip.getMCSpace(), -1, sID, "Station");

							//Store ship into cargo hold
							mPlayer.Ship.sCargo.push_back(sInv(tempShip, true, sInventory.at(sSHSlot).getIID(), sInventory.at(sSHSlot).getIAmount()));

							//Remove from station
							sInventory.erase(sInventory.begin()+sSHSlot);
							return true;
						}

						else
						{
							cout << "Cannot complete the operation.  Reason: Ship cargohold is full" << endl;
							return false;
						}
					}					
				}

				else
				{
					cout << "No ships available or canceled." << endl;
					return false;
				}
			}

			else if (iPChoice == 2) //If ship is on the player's ship
			{
				sSHSlot = mp_st.sMSI3A(mPlayer); //Get the player to pick a ship to move into station storage from their ship

				if (sSHSlot != -1)
				{			
					bDone = false;

					while (!bDone)
					{
						//tempShip_C = mPlayer.Ship;
						//tempShip_N = sSHold.at(sSHSlot);

						if (checkSpace(mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSSG2()))
						{
							//Move new to temp
							tempShip.initShip2(mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSName(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSClass(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSShield(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSShield(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSArmor(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSArmor(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSHull(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSHull(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getLHP(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getMTP(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getBH(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getRM(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getHWB(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSWHP(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getMInit(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSTLevel(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSSG2(), mPlayer.Ship.sCargo.at(sSHSlot).sShip.getMCSpace(), -1, sID, "Station");

							//Store ship into station
							sInventory.push_back(sInv(tempShip, true, mPlayer.Ship.sCargo.at(sSHSlot).getIID(), mPlayer.Ship.sCargo.at(sSHSlot).getIAmount()));


							//Remove from ship
							mPlayer.Ship.sCargo.erase(mPlayer.Ship.sCargo.begin()+sSHSlot);
							return true;
						}

						else
						{
							if (!sBISpace(mPlayer, mPlayer.Ship.sCargo.at(sSHSlot).sShip.getSSG2()))
							{
								bDone = true;
								return false;
							}
						}
					}					
				}

				else
				{
					cout << "No ships available or canceled." << endl;
					return false;
				}
			}
		}
	}


	//Player elected to switch to the new ship
	else
	{		
		cout << "Beginning exchange process.  Note that all equipped weapons and items in your cargo hold will be stored.  In the event that cargo space becomes an issue, you will be asked to buy more space." << endl;
		cout << "If you choose not to buy more space your purchase will be refunded" << endl << endl;

		if (bought)
		{
			tempShip_C = mPlayer.Ship; //Store player ship in C (current) for use later.

			tempShip_N.setSName(ds_st.getSName());
			tempShip_N.setSClass(ds_st.getSClass());	
			tempShip_N.setSTLevel(ds_st.getSTLevel());	
			tempShip_N.updateSShield(ds_st.getSShield(), "set"); //get ship shields
			tempShip_N.updateSMShield(ds_st.getSShield(), "set");
			tempShip_N.updateSArmor(ds_st.getSArmor(), "set"); //get ship armor		
			tempShip_N.updateSMArmor(ds_st.getSArmor(), "set");
			tempShip_N.updateSHull(ds_st.getSHull(), "set"); //get ship hull		
			tempShip_N.updateSMHull(ds_st.getSHull(), "set");
			tempShip_N.setMInit(ds_st.getSMInit());
			tempShip_N.setSWHP(ds_st.getSWHP());	
			tempShip_N.setLHP(ds_st.getSLB());
			tempShip_N.setMTP( ds_st.getSMT());	
			tempShip_N.setBH(ds_st.getSBH());
			tempShip_N.setRM(ds_st.getSRM());
			tempShip_N.setHWB(ds_st.getSHWB());
			tempShip_N.updateMCSpace(ds_st.getSCargo(), "set");
			tempShip_N.setSSG2(ds_st.getSSG2());
			tempShip_N.setSID(-1);
			tempShip_N.setSTID(-1);
			tempShip_N.setSLocal("none");

			//Lasers
			if (tempShip_C.lBanks.size() > 0) //Make sure we actually have lasers equipped to the ship
			{
				for (i2 = 0; i2 < tempShip_C.lBanks.size(); i2++)
				{
					tempSpace += tempShip_C.lBanks.at(i2).hpWeapon.getSG2();
				}
			}

			//Missiles
			if (tempShip_C.mTurrets.size() > 0) //Make sure we actually have lasers equipped to the ship
			{
				for (i2 = 0; i2 < tempShip_C.mTurrets.size(); i2++)
				{
					tempSpace += tempShip_C.mTurrets.at(i2).hpWeapon.getSG2();
				}
			}

			//Bombs
			if (tempShip_C.bHolds.size() > 0) //Make sure we actually have lasers equipped to the ship
			{
				for (i2 = 0; i2 < tempShip_C.bHolds.size(); i2++)
				{
					tempSpace += tempShip_C.bHolds.at(i2).hpWeapon.getSG2();
				}
			}

			//Rails
			if (tempShip_C.rMounts.size() > 0) //Make sure we actually have lasers equipped to the ship
			{
				for (i2 = 0; i2 < tempShip_C.rMounts.size(); i2++)
				{
					tempSpace += tempShip_C.rMounts.at(i2).hpWeapon.getSG2();
				}
			}

			//Heavy
			if (tempShip_C.hWBays.size() > 0) //Make sure we actually have lasers equipped to the ship
			{
				for (i2 = 0; i2 < tempShip_C.hWBays.size(); i2++)
				{
					tempSpace += tempShip_C.hWBays.at(i2).hpWeapon.getSG2();
				}
			}

			//Cargo
			if (tempShip_C.sCargo.size() > 0)
			{
				for (i2 = 0; i2 < tempShip_C.sCargo.size(); i2++)
				{
					if (tempShip_C.sCargo.at(i2).isShip())
					{
						tempSpace += tempShip_C.sCargo.at(i).sShip.getSSG2();
					}

					else
					{
						tempSpace += tempShip_C.sCargo.at(i).getISpace();
					}
				}
			}

			if (tempSpace > 0.0f)
			{
				bDone = false;
				
				while (!bDone)
				{
					if(!checkSpace(tempSpace))
					{
						bPChoice = sBISpace(mPlayer, tempSpace);

						if (!pChoice)
						{
							return false;
						}
					}

					else
					{
						//Lasers
						if (tempShip_C.lBanks.size() > 0) //Make sure we actually have lasers equipped to the ship
						{
							for (i2 = 0; i2 < tempShip_C.lBanks.size(); i2++)
							{
								for (i3 = 0; i3 <= sInventory.size(); i3++)
								{
									if (i3 == sInventory.size())
									{
										sInventory.push_back(sInv(tempShip_C.lBanks.at(i2).hpWeapon.getWID(), 1, "Weapon", tempShip_C.lBanks.at(i2).hpWeapon.getSG2(), false)); //If weapon does not exist, add it
									}

									else if ((tempShip_C.lBanks.at(i2).hpWeapon.getWID() == sInventory.at(i3).getIID()) && ("Weapon" == sInventory.at(i3).getIType()))
									{
										sInventory.at(i3).updateIAmount(1, "add"); //If the weapon aleady exists in the station inventory, add one to the stack
										break;
									}
								}
							}
						}

						//Missiles
						if (tempShip_C.mTurrets.size() > 0) //Make sure we actually have lasers equipped to the ship
						{
							for (i2 = 0; i2 < tempShip_C.mTurrets.size(); i2++)
							{
								for (i3 = 0; i3 <= sInventory.size(); i3++)
								{
									if (i3 == sInventory.size())
									{
										sInventory.push_back(sInv(tempShip_C.mTurrets.at(i2).hpWeapon.getWID(), 1, "Weapon", tempShip_C.mTurrets.at(i2).hpWeapon.getSG2(), false)); //If weapon does not exist, add it
									}

									else if ((tempShip_C.mTurrets.at(i2).hpWeapon.getWID() == sInventory.at(i3).getIID()) && ("Weapon" == sInventory.at(i3).getIType()))
									{
										sInventory.at(i3).updateIAmount(1, "add"); //If the weapon aleady exists in the station inventory, add one to the stack
										break;
									}
								}
							}
						}

						//Bombs
						if (tempShip_C.bHolds.size() > 0) //Make sure we actually have lasers equipped to the ship
						{
							for (i2 = 0; i2 < tempShip_C.bHolds.size(); i2++)
							{
								for (i3 = 0; i3 <= sInventory.size(); i3++)
								{
									if (i3 == sInventory.size())
									{
										sInventory.push_back(sInv(tempShip_C.bHolds.at(i2).hpWeapon.getWID(), 1, "Weapon", tempShip_C.bHolds.at(i2).hpWeapon.getSG2(), false)); //If weapon does not exist, add it
									}

									else if ((tempShip_C.bHolds.at(i2).hpWeapon.getWID() == sInventory.at(i3).getIID()) && ("Weapon" == sInventory.at(i3).getIType()))
									{
										sInventory.at(i3).updateIAmount(1, "add"); //If the weapon aleady exists in the station inventory, add one to the stack
										break;
									}
								}
							}
						}

						//Rails
						if (tempShip_C.rMounts.size() > 0) //Make sure we actually have lasers equipped to the ship
						{
							for (i2 = 0; i2 < tempShip_C.rMounts.size(); i2++)
							{
								for (i3 = 0; i3 <= sInventory.size(); i3++)
								{
									if (i3 == sInventory.size())
									{
										sInventory.push_back(sInv(tempShip_C.rMounts.at(i2).hpWeapon.getWID(), 1, "Weapon", tempShip_C.rMounts.at(i2).hpWeapon.getSG2(), false)); //If weapon does not exist, add it
									}

									else if ((tempShip_C.rMounts.at(i2).hpWeapon.getWID() == sInventory.at(i3).getIID()) && ("Weapon" == sInventory.at(i3).getIType()))
									{
										sInventory.at(i3).updateIAmount(1, "add"); //If the weapon aleady exists in the station inventory, add one to the stack
										break;
									}
								}
							}
						}

						//Heavy
						if (tempShip_C.hWBays.size() > 0) //Make sure we actually have lasers equipped to the ship
						{
							for (i2 = 0; i2 < tempShip_C.hWBays.size(); i2++)
							{
								for (i3 = 0; i3 <= sInventory.size(); i3++)
								{
									if (i3 == sInventory.size())
									{
										sInventory.push_back(sInv(tempShip_C.hWBays.at(i2).hpWeapon.getWID(), 1, "Weapon", tempShip_C.hWBays.at(i2).hpWeapon.getSG2(), false)); //If weapon does not exist, add it
									}

									else if ((tempShip_C.hWBays.at(i2).hpWeapon.getWID() == sInventory.at(i3).getIID()) && ("Weapon" == sInventory.at(i3).getIType()))
									{
										sInventory.at(i3).updateIAmount(1, "add"); //If the weapon aleady exists in the station inventory, add one to the stack
										break;
									}
								}
							}
						}

						//Cargo
						if (tempShip_C.sCargo.size() > 0)
						{
							for (i2 = 0; i2 < tempShip_C.sCargo.size(); i2++)
							{
								if (tempShip_C.sCargo.at(i2).isShip())
								{
									sInventory.push_back(sInv());

									sInventory.at(sInventory.size()-1).sShip.initShip2(tempShip_N.getSName(), tempShip_N.getSClass(), tempShip_N.getSShield(), tempShip_N.getSShield(), tempShip_N.getSArmor(), tempShip_N.getSArmor(), tempShip_N.getSHull(), tempShip_N.getSHull(), tempShip_N.getLHP(), tempShip_N.getMTP(), tempShip_N.getBH(), tempShip_N.getRM(), tempShip_N.getHWB(), tempShip_N.getSWHP(), tempShip_N.getMInit(), tempShip_N.getSTLevel(), tempShip_N.getSSG2(), tempShip_N.getMCSpace(), -1, sID, "Station");
									mPlayer.Ship.sCargo.erase(mPlayer.Ship.sCargo.begin()+i2);
									i2 = 0;
								}

								else
								{
									sInventory.push_back(sInv(tempShip_C.sCargo.at(i2).getIID(), tempShip_C.sCargo.at(i2).getIAmount(), tempShip_C.sCargo.at(i2).getIType(), tempShip_C.sCargo.at(i2).getISpace(), false));
									mPlayer.Ship.sCargo.erase(mPlayer.Ship.sCargo.begin()+i2);
									i2 = 0;
								}
							}
						}

						//Now that everything is off, exchange the ship data
						mPlayer.Ship.changeShip(tempShip_N.getSName(), tempShip_N.getSClass(), tempShip_N.getSShield(), tempShip_N.getSShield(), tempShip_N.getSArmor(), tempShip_N.getSArmor(), tempShip_N.getSHull(), tempShip_N.getSHull(), tempShip_N.getLHP(), tempShip_N.getMTP(), tempShip_N.getBH(), tempShip_N.getRM(), tempShip_N.getHWB(), tempShip_N.getSWHP(), tempShip_N.getMInit(), tempShip_N.getSTLevel(), tempShip_N.getSSG2(), tempShip_N.getMCSpace(), -1, -1, "none");

						tempShip.initShip2(tempShip_C.getSName(), tempShip_C.getSClass(), tempShip_C.getSShield(), tempShip_C.getSShield(), tempShip_C.getSArmor(), tempShip_C.getSArmor(), tempShip_C.getSHull(), tempShip_C.getSHull(), tempShip_C.getLHP(), tempShip_C.getMTP(), tempShip_C.getBH(), tempShip_C.getRM(), tempShip_C.getHWB(), tempShip_C.getSWHP(), tempShip_C.getMInit(), tempShip_C.getSTLevel(), tempShip_C.getSSG2(), tempShip_C.getMCSpace(), -1, sID, "Station");

						sInventory.push_back(sInv(tempShip, true, tempShip_C.getID(), 1));

						bDone = true;
					}
				}				
			}	
		}
	}
}

bool Station::getItem(Player& mPlayer)
{
	iPChoice = mp_st.sMSI4A(this);

	if (iPChoice != -1)
	{
		bDone = false;

		while (!bDone)
		{
			nOItems = mp_st.mSSIAmount(sInventory.at(iPChoice).getIAmount());

			if (mPlayer.Ship.checkSpace(sInventory.at(iPChoice).getISpace()*nOItems))
			{
				//Check to see if the item exists in the cargohold
				for (i = 0; i <= mPlayer.Ship.sCargo.size(); i++)
				{
					if (i == mPlayer.Ship.sCargo.size()) //Item does not exist
					{
						//Add the item to the cargohold
						mPlayer.Ship.loadCargo(sInventory.at(iPChoice).getIID(), nOItems, sInventory.at(iPChoice).getIType(), sInventory.at(iPChoice).getISpace(), false, "");

						//Remove items from station inventory
						removeItem(iPChoice, nOItems);

						bDone = true;
						return true;
					}

					else if ((mPlayer.Ship.sCargo.at(i).getIID() == sInventory.at(iPChoice).getIID()) && (mPlayer.Ship.sCargo.at(i).getIType() == sInventory.at(iPChoice).getIType())) //If the item exists in the cargohold
					{
						//Add the additional items to the cargohold
						mPlayer.Ship.updateCIAmount(i, nOItems, "add", false, "");

						//Remove items from station inventory
						removeItem(iPChoice, nOItems);

						bDone = true;
						return true;
					}
				}
			}

			else
			{
				cout << "You do not have enough room in your ship cargohold to store that many items" << endl;
				cout << "Canceling storage operation..." << endl;

				bDone = true;
				return false;
			}
		}
	}

	else
	{
		cout << "Either no items found or operation was canceled." << endl;
		return false;
	}
}

void Station::removeItem(int slot, int iAmount)
{
	if (sInventory.at(slot).getIAmount() > iAmount)
	{
		sInventory.at(slot).updateIAmount(iAmount,"sub");
	}

	else
	{
		sInventory.erase(sInventory.begin()+slot);
	}
}

void Station::setTDist(int dist)
{
	sTDist = dist;
}

int Station::getTDist()
{
	return sTDist;
}

void Station::calcUSpace()
{
	for (i = 0; i < sInventory.size(); i++)
	{
		tempSpace += sInventory.at(i).getISpace() * sInventory.at(i).getIAmount(); //Get the amount of space being used for each inventory item, times the number of items, and add it to sUSpace
	}

	sUSpace = tempSpace;
	tempSpace = 0.0f;
}

bool Station::checkSpace(float nSpace)
{
	if (sMSSpace < getCSUsed() + nSpace)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool Station::sBISpace(Player& mPlayer, float space)
{
	pChoice = mp_st.sBISPMenu(getCSUsed(), sMSSpace, space, mPlayer);

	if (pChoice > 0) //If player bought more space
	{
		updateISpace(pChoice, "add");
		return true;
	}

	else if (pChoice == 0) //If player did not buy more space
	{
		return false;
	}
}