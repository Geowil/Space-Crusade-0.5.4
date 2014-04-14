#include "ship2.h"


using namespace std;



Ship2::Ship2()
{
	
}

float Ship2::getSArmor()
{
	return sArmor;
}

float Ship2::getSHull()
{
	return sHull;
}

float Ship2::getSMArmor()
{
	return sMArmor;
}

float Ship2::getSMHull()
{
	return sMHull;
}

float Ship2::getSMShield()
{
	return sMShield;
}

float Ship2::getSShield()
{
	return sShield;
}

string Ship2::getSClass()
{
	return sClass;
}

int Ship2::getSClassI(string sclass)
{
	if (sclass == "Frigate")
	{
		return 1;
	}

	else if (sclass == "Destroyer")
	{
		return 2;
	}

	else if (sclass == "Cruiser")
	{
		return 3;
	}

	else if (sclass == "Battlecruiser")
	{
		return 4;
	}

	else if (sclass == "Battleship")
	{
		return 5;
	}

	else if (sclass == "Mothership")
	{
		return 6;
	}

	else if (sclass == "Titan")
	{
		return 7;
	}
}

string Ship2::getSName()
{
	return sName;
}

int Ship2::getSTLevel()
{
	return sTLevel;
}



void Ship2::setSClass(string s)
{
	sClass = s;
}



void Ship2::setSName(string s)
{
	sName = s;
}



void Ship2::setSTLevel(int i)
{
	sTLevel = i;
}

int Ship2::getLHP()
{
	return sLB;
}

int Ship2::getMTP()
{
	return sMT;
}

int Ship2::getBH()
{
	return sBH;
}

int Ship2::getRM()
{
	return sRM;
}

int Ship2::getHWB()
{
	return sHWB;
}

void Ship2::initShip2(string name, string sclass, float shield, float mshield, float armor, float marmor, float hull, float mhull, int lb, int mt, int bh, int rm, int hwb, int twhp, int minit, int tlevel, float sg2, float mcspace, int sSID, int sSTID, string sLocal)
{	
	sName = name;	
	sClass = sclass;	
	sTLevel = tlevel;	
	sShield = shield;
	sMShield = mshield;
	sArmor = armor;
	sMArmor = marmor;
	sHull = hull;
	sMHull = mhull;
	sMInit = minit;
	sWHP = twhp;
	sLB = lb;
	sMT = mt;
	sBH = bh;
	sRM = rm;
	sHWB = hwb;
	sMCSpace = mcspace;
	sSG2 = sg2;

}

int Ship2::getMInit()
{
	return sMInit;
}

int Ship2::getSWHP()
{
	return sWHP;
}

int Ship2::getULHP()
{
	return sULB;
}

int Ship2::getUMTP()
{
	return sUMT;
}

int Ship2::getUBH()
{
	return sUBH;
}

int Ship2::getURM()
{
	return sURM;
}

int Ship2::getUHWB()
{
	return sUHWB;
}

void Ship2::setLHP(int i)
{
	sLB = i;
}

void Ship2::setULHP(int i)
{
	sULB = i;
}

void Ship2::setMTP(int i)
{
	sMT = i;
}

void Ship2::setUMTP(int i)
{
	sUMT = i;
}

void Ship2::setBH(int i)
{
	sBH = i;
}

void Ship2::setUBH(int i)
{
	sUBH  = i;
}

void Ship2::setRM(int i)
{
	sRM = i;
}

void Ship2::setURM(int i)
{
	sURM = i;
}

void Ship2::setHWB(int i)
{
	sHWB = i;
}

void Ship2::setUHWB(int i)
{
	sUHWB = i;
}

void Ship2::setSWHP(int i)
{
	sWHP = i;
}

void Ship2::setMInit(int i)
{
	sMInit = i;
}

float Ship2::getSSG2()
{
	return sSG2;
}

void Ship2::setSSG2(float sg2)
{
	sSG2 = sg2;
}

void Ship2::setID(int i)
{
	sID = i;
}

void Ship2::setSID(int i)
{
	sSID = i;
}

void Ship2::setSTID(int i)
{
	sSTID = i;
}

void Ship2::setSLocal(string s)
{
	sLocal = s;
}

int Ship2::getID()
{
	return sID;
}

int	Ship2::getSID()
{
	return sSID;
}

int	Ship2::getSTID()
{
	return sSTID;
}

string Ship2::getSLocal()
{
	return sLocal;
}

void Ship2::updateMCSpace(float space, string operation)
{
	if (operation == "add")
	{
		sMCSpace += space;
	}

	else if (operation == "sub")
	{
		sMCSpace -= space;
	}

	else if (operation == "set")
	{
		sMCSpace = space;
	}
}

float Ship2::getMCSpace()
{
	return sMCSpace;
}

void Ship2::updateSArmor(float f, string operation)
{
	if (operation == "add")
	{
		sArmor += f;
	}

	else if (operation == "sub")
	{
		sArmor -= f;
	}

	else if (operation == "set")
	{
		sArmor = f;
	}
}

void Ship2::updateSHull(float f, string operation)
{
	if (operation == "add")
	{
		sHull += f;
	}

	else if (operation == "sub")
	{
		sHull -= f;
	}

	else if (operation == "set")
	{
		sHull = f;
	}
}

void Ship2::updateSMArmor(float f, string operation)
{
	if (operation == "add")
	{
		sMArmor += f;
	}

	else if (operation == "sub")
	{
		sMArmor -= f;
	}

	else if (operation == "set")
	{
		sMArmor = f;
	}
}

void Ship2::updateSMHull(float f, string operation)
{
	if (operation == "add")
	{
		sMHull += f;
	}

	else if (operation == "sub")
	{
		sMHull -= f;
	}

	else if (operation == "set")
	{
		sMHull = f;
	}
}

void Ship2::updateSMShield(float f, string operation)
{
	if (operation == "add")
	{
		sMShield += f;
	}

	else if (operation == "sub")
	{
		sMShield -= f;
	}

	else if (operation == "set")
	{
		sMShield = f;
	}
}

void Ship2::updateSShield(float f, string operation)
{
	if (operation == "add")
	{
		sShield += f;
	}

	else if (operation == "sub")
	{
		sShield -= f;
	}

	else if (operation == "set")
	{
		sShield = f;
	}
}