#ifndef NAMEGEN_H
#define NAMEGEN_H

#include <string>
#include "random.h"
#include "datasystem.h"

using std::string;

class nameGen
{
public:
	nameGen();

	string genName(string race); //Start the name generation process; pass the race of the entity so that we can create race-accurate sounding names
	
private:
	//In private because nothing outside of this class interacts with them
	void getPrefix();
	void getStem();
	void getSuffix();

	string nPrefix; //Store prefix
	string nStem; //Store stem
	string nSuffix; //Store suffix
	string eRace; //Store entity race

	string gFName; //Store generated first name
	string gLName; //Store generated last name
	string gCName; //Store generated complete name

	int prefRand; //Store the id of the prefix to be used
	int stemRand; //Store the id of the stem to be used
	int suffRand; //Store the id of the suffix to be used

	int cNRand; //Use to determine if a first and last name is to be generated
};
#endif
