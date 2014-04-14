#ifndef BPARTICIPANTS_H
#define BPARTICIPANTS_H

#include <string>

using std::string;

class bParticipants
{
public:
	bParticipants();
	bParticipants(string name, int init);

	string getName();
	int getInit();

private:
	string bPName;
	int bPInit;
};
#endif