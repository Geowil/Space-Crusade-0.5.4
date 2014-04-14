#include "hardPoint.h"
#include "weapon.h"


using namespace std;


hardPoint::hardPoint()
{

}

hardPoint::hardPoint(int slot, string wtype)
{
	hpWType = wtype;
	hpSlot = slot;
}

void hardPoint::setHPSlot(int slot)
{
	hpSlot = slot;
}

void hardPoint::setHPWType(string type)
{
	hpWType = type;
}

int hardPoint::getHPSlot()
{
	return hpSlot;
}

string hardPoint::getHPWType()
{
	return hpWType;
}


hardPointL::hardPointL(int slot)
{
	hpSlot = slot;
	hpWeapon.initWeapon();
}

hardPointL::hardPointL(int slot, string type)
{
	hpSlot = slot;
	hpWType = type;
	hpWeapon.initWeapon();
}


hardPointM::hardPointM(int slot)
{
	hpSlot = slot;
	hpWeapon.initWeapon();
}

hardPointM::hardPointM(int slot, string type)
{
	hpSlot = slot;
	hpWType = type;
	hpWeapon.initWeapon();
}

hardPointB::hardPointB(int slot)
{
	hpSlot = slot;
	hpWeapon.initWeapon();
}

hardPointB::hardPointB(int slot, string type)
{
	hpSlot = slot;
	hpWType = type;
	hpWeapon.initWeapon();
}

hardPointR::hardPointR(int slot)
{
	hpSlot = slot;
	hpWeapon.initWeapon();
}

hardPointR::hardPointR(int slot, string type)
{
	hpSlot = slot;
	hpWType = type;
	hpWeapon.initWeapon();
}

hardPointH::hardPointH(int slot)
{
	hpSlot = slot;
	hpWeapon.initWeapon();
}

hardPointH::hardPointH(int slot, string type)
{
	hpSlot = slot;
	hpWType = type;
	hpWeapon.initWeapon();
}
