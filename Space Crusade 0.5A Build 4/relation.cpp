#include "relation.h"

Relation::Relation()
{

}

Relation::Relation(string name, int affinity)
{
	rName = name;
	rAffinity = affinity;
}

void Relation::createRelation(string name, int affinity)
{
	rName = name;

	rAffinity = affinity;
}

void Relation::changeAffinity(int affinity, string operation)
{
	if (operation == "add")
	{
		if (rAffinity + affinity <= 100) //To make sure that rAffinity never goes above 100
		{
			rAffinity += affinity;
		}

		else
		{
			rAffinity = 100;
		}
	}

	else if (operation == "sub")
	{
		if (rAffinity - affinity >= -100) //To make sure that rAffinity never goes below -100
		{
			rAffinity -= affinity;
		}

		else
		{
			rAffinity = -100;
		}
	}

	else if (operation == "set")
	{
		rAffinity = affinity;
	}
}

int Relation::getAffinity()
{
	return rAffinity;
}

string Relation::getAffinityS()
{
	if (rAffinity > 77)
	{
		return "Allies";
	}

	else if ((rAffinity < 78) && (rAffinity > 51))
	{
		return "Friendly";
	}

	else if ((rAffinity < 52) && (rAffinity > 25))
	{
		return "Warm";
	}

	else if ((rAffinity < 26) && (rAffinity > 0))
	{
		return "Acquaintances";
	}

	else if (rAffinity == 0)
	{
		return "Ambivalent";
	}

	else if ((rAffinity < 0) && (rAffinity > -23))
	{
		return "Cool";
	}

	else if ((rAffinity < -22) && (rAffinity > -49))
	{
		return "Suspicious";
	}

	else if ((rAffinity < -48) && (rAffinity > -75))
	{
		return "Paranoid";
	}

	else if (rAffinity < -76)
	{
		return "Enemies";
	}
}

string Relation::getRName()
{
	return rName;
}

void Relation::setRName(string name)
{
	rName = name;
}

void Relation::setRAffinity(int affinity)
{
	rAffinity = affinity;
}