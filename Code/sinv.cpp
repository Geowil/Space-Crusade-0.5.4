#include "sinv.h"
#include "ship.h"

sInv::sInv()
{
	iID = 0;
	iAmount = 0;
	iType = "none";
	iSG2 = 0.0f;
}

sInv::sInv(int item_id, int item_amount, string item_type, float item_size, bool ship)
{
	iID = item_id;
	iAmount = item_amount;
	iType = item_type;
	iSG2 = item_size;
	bIsShip = ship;
}

sInv::sInv(Ship2 nShip, bool ship, int id, int amount)
{
	sShip.setSName(nShip.getSName());
	sShip.setSClass(nShip.getSClass());
	sShip.setSTLevel(nShip.getSTLevel());
	sShip.updateSShield(nShip.getSShield(), "set");
	sShip.updateSArmor(nShip.getSArmor(), "set");
	sShip.updateSHull(nShip.getSHull(), "set");
	sShip.updateSMShield(nShip.getSMShield(), "set");
	sShip.updateSMArmor(nShip.getSMArmor(), "set");
	sShip.updateSMHull(nShip.getSMHull(), "set");
	sShip.setMInit(nShip.getMInit());
	sShip.setSSG2(nShip.getSSG2());
	sShip.setLHP(nShip.getLHP());
	sShip.setMTP(nShip.getMTP());
	sShip.setBH(nShip.getBH());
	sShip.setRM(nShip.getRM());
	sShip.setHWB(nShip.getHWB());
	sShip.setSWHP(nShip.getSWHP());
	sShip.setULHP(nShip.getULHP());
	sShip.setUMTP(nShip.getUMTP());
	sShip.setUBH(nShip.getUBH());
	sShip.setURM(nShip.getURM());
	sShip.setUHWB(nShip.getUHWB());
	sShip.setSID(nShip.getSID());
	sShip.setSTID(nShip.getSTID());
	sShip.setSLocal(nShip.getSLocal());

	bIsShip = ship;
	iID = id;
	iAmount = amount;
}


void sInv::setIID(int item_id)
{
	iID = item_id;
}

void sInv::setIAmount(int item_amount)
{
	iAmount = item_amount;
}

int sInv::getIID()
{
	return iID;
}

int sInv::getIAmount()
{
	return iAmount;
}

void sInv::setISpace(float space)
{
	iSG2 = space;
}

float sInv::getISpace()
{
	return iSG2;
}

void sInv::updateIAmount(int i, string operation)
{
	if (operation == "add")
	{
		iAmount += i;
	}

	else if (operation == "sub")
	{
		iAmount -= i;
	}

	else if (operation == "set")
	{
		iAmount = i;
	}
}

void sInv::setIType(string s)
{
	iType = s;
}

string sInv::getIType()
{
	return iType;
}

bool sInv::isShip()
{
	return bIsShip;
}