#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <direct.h>
#include "debug.h"

using namespace std;

Debug::Debug()
{

}

void Debug::createBReport(string bname, string bdesc, string blocale, string btstamp, string PATH)
{
	bName = bname;
	bDesc = bdesc;
	bLocale = blocale;
	bTStamp = btstamp;

	printToFile(PATH.c_str());
}

string Debug::getBName()
{
	return bName;
}

string Debug::getBDesc()
{
	return bDesc;
}

string Debug::getBLocale()
{
	return bLocale;
}

string Debug::getBTStamp()
{
	return bTStamp;
}

void Debug::printToFile(string PATH)
{
	cout << fileExists(PATH.c_str()) << endl;
	
	if (!fileExists(PATH.c_str()))
	{		
		ofstream oF(PATH.c_str());
		
		if (oF)
		{
			oF << "Bug Name: " << getBName() << endl;
			oF << endl;
			oF << "Bug Description: " << getBDesc() << endl;
			oF << endl;
			oF << "Where Bug Occurred: " << getBLocale() << endl;
			oF << endl;
			oF << "Timestamp: " << getBTStamp() << endl;
			oF << endl;
		}

		oF.close();
	}

	else
	{
		ofstream oF;

		oF.open(PATH.c_str(), ios::app);

		if (oF)
		{
			oF << "/" << endl;
			oF << "/" << endl;
			oF << endl;
			oF << "Bug Name: " << getBName() << endl;
			oF << endl;
			oF << "Bug Description: " << getBDesc() << endl;
			oF << endl;
			oF << "Where Bug Occurred: " << getBLocale() << endl;
			oF << endl;
			oF << "Timestamp: " << getBTStamp() << endl;
			oF << endl;
			oF << "Please report this bug at: http://bugs.lmpgames.com/tbg/index.php!" << endl;
			oF << endl;
		}

		oF.close();
	}
}

bool Debug::fileExists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}