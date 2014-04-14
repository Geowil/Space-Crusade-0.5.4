#ifndef MISSION_H
#define MISSION_H

#include <string>

using std::string;

class Player;

class Mission
{
public:
	Mission();

	void createMission(int mCode);

	void getRewards(Player& mPlayer);

	void getBMInfo();
	void getCMInfo();
	

	string getMState();
	int getMStateID();
	void updateMState(int state);

	void updateMission(bool bChangeTName, string tname, bool bChangeMLSector, string mlsector, bool bChangeMLSystem, string mlsystem, bool bChangeDur, int duration); //Update a mission
	
	//Get Info

	//Basic Info
	string getMName();
	string getMDesc();
	string getMType();
	int getMDur();
	string getMDiff();
	string getMSector();
	string getMSystem();
	int getMID();
	
	//Comprehensive Info
	int getMCBEReq();
	string getMSCReq();
	string getMMWReq();
	string getMTName();
	string getMTSClass();
	int	getMBounty();
	int getMXR();
	int getMRR();
	int getMDiR();
	int getMDR();
	int getMLR();
	int getMPlR();
	int getMUR();
	int getMPR();
	int getMNWR();
	int getMEXPR();
	string getMIR();
	

	//Set Info
	
	void setMName(string name);
	void setMDesc(string desc);
	void setMType(string type);
	void setMDur(int dur);
	void setMDiff(string difficulty);
	void setMSector(string sector);
	void setMSystem(string system);
	void setMID(int id);
	void setMCBEReq(int lvl);
	void setMSCReq(string sclass);
	void setMMWReq(string req);
	void setMTName(string name);
	void setMTSClass(string sclass);
	void setMBounty(int i);
	void setMXR(int i);
	void setMRR(int i);
	void setMDiR(int i);
	void setMDR(int i);
	void setMLR(int i);
	void setMPlR(int i);
	void setMUR(int i);
	void setMPR(int i);
	void setMNWR(int i);
	void setMEXPR(int i);
	void setMIR(string s);
	void setMState(int i);


private:
	int mID; //Mission ID
	string mName;
	string mDesc;
	string mType;
	int mCBEReq; //combat experience requirement
	string mSCReq; //ship requirement
	string mMWReq; //module/weapon requirement
	int mDur; //duration in days
	//int mTAccepted; //When the mission was accepted
	//int mTPassed; //How much time has passed since the mission was undertaken
	string mDifficulty;
	string mLSector; //location; sector
	string mLSystem; //location; system
	string mTName; //target name
	string mTSClass; //target ship class
	int mBounty;
	int mXR; //xarn reward
	int mRR; //ruby reward
	int mDiR; //diamond reward
	int mDR; //draconic reward
	int mLR; //lithium reward
	int mPlR; //platinum reward
	int mUR; //uranium reward
	int mPR; //plutonium reward
	int mNWR; //nuclear waste reward
	int mEXPR; //exp reward
	string mIR; //item reward;

	int mState; //Mission state

	/*
	Mission States:

	0 = In Progress
	1 = Partially Completed (for multi-stage quests)
	2 = Completed
	3 = Closed (ran out of time to complete)
	4 = Failed
	5 = Repeatable
	
	*/
};
#endif