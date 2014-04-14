#include <string>
#include "tDamage.h"

using namespace std;

tDamage::tDamage(float damage, int turns, string type)
{
	tBDamage = damage;
	tTComplete = turns;
	dType = type;
}

void tDamage::subTurn()
{
	tTComplete -= 1;
}

float tDamage::getDamage()
{
	return tBDamage;
}

int tDamage::getTurns()
{
	return tTComplete;
}

string tDamage::getType()
{
	return dType;
}

string tDamage::getATo()
{
	return appliedTo;
}

void tDamage::setATo(string s)
{
	appliedTo = s;
}