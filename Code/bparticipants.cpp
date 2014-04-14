#include "bparticipants.h"

bParticipants::bParticipants()
{

}

bParticipants::bParticipants(string name, int init)
{
	bPName = name;
	bPInit = init;
}

string bParticipants::getName()
{
	return bPName;
}

int bParticipants::getInit()
{
	return bPInit;
}