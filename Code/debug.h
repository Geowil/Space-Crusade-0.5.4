#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <vector>

using std::string;

class Debug
{
public:
	Debug();

	void createBReport(string bname, string bdesc, string bclass, string btstamp, string PATH); //create bug report
	
	string getBName();
	string getBDesc();
	string getBLocale();
	string getBTStamp();

	void printToFile(string PATH);

	bool fileExists(const char *filename);

private:
	string		bName;
	string		bDesc;
	string		bLocale;
	string		bTStamp;
	string		fData; //file data storage
};
#endif