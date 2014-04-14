#include <string>
#include "mission.h"
#include "datasystem.h"
#include "msgproc.h"

using namespace std;

dataSystem ds_msn;
msgProc mp_msn;

Mission::Mission()
{

}

void Mission::createMission(int mCode)
{
	ds_msn.rData("Mission_Data","select from",mCode);

	mID			=	 mCode;
	mName		=	 ds_msn.getMName();
	mDesc		=	 ds_msn.getMDesc();
	mType		=	 ds_msn.getMType();
	mCBEReq		=	 ds_msn.getMCBEReq();
	mSCReq		=	 ds_msn.getMSCReq();
	mMWReq		=	 ds_msn.getMMWReq();
	mDur		=	 ds_msn.getMTLimit();
	mDifficulty =	 ds_msn.getMDiff();
	mLSector	=	 ds_msn.getMSector();
	mLSystem	=	 ds_msn.getMSystem();
	mTName		=	 ds_msn.getMTName();
	mTSClass	=	 ds_msn.getMTSClass();
	mBounty		=	 ds_msn.getMBounty();
	mXR			=	 ds_msn.getMXR(); 
	mRR			=	 ds_msn.getMRR(); 
	mDiR		=	 ds_msn.getMDiR();
	mDR			=	 ds_msn.getMDR(); 
	mLR			=	 ds_msn.getMLR(); 
	mPlR		=	 ds_msn.getMPlR(); 
	mUR			=	 ds_msn.getMUR(); 
	mPR			=	 ds_msn.getMPR(); 
	mNWR		=	 ds_msn.getMNWR();
	mEXPR		=	 ds_msn.getMEXPR();
	mIR			=	 ds_msn.getMIR();
	mState		=	 0;
}

void Mission::getRewards(Player& mPlayer)
{
	if (mBounty != 0)
	{
		mPlayer.updateXarn(mBounty, "add");
	}
	
	else if (mXR != 0)
	{
		mPlayer.updateXarn(mXR, "add");
	}

	if (mRR != 0)
	{
		mPlayer.updateRubies(mRR,"add");
	}
	
	if (mDiR != 0)
	{
		mPlayer.updateDia(mDiR,"add");
	} 
	
	if (mDR != 0)
	{
		mPlayer.updateDrac(mDR,"add");
	}
	
	if (mLR != 0)
	{
		mPlayer.updateLith(mLR,"add");
	}
	
	if (mPlR != 0)
	{
		mPlayer.updatePlat(mPlR,"add");
	}

	if (mUR != 0)
	{
		mPlayer.updateUra(mUR,"add");
	}

	if (mPR != 0)
	{
		mPlayer.updatePlut(mPR,"add");
	}

	if (mNWR != 0)
	{
		mPlayer.updateNWaste(mNWR,"add");
	}

	if (mEXPR != 0)
	{
		mPlayer.updateCEXP(mEXPR,"add");
	}

	/*if (mIR != 0)
	{
		mPlayer.addICode(mIR);
	}*/
}

void Mission::getBMInfo()
{
	mp_msn.mInfo(this,false);
}

void Mission::getCMInfo()
{
	mp_msn.mInfo(this,true);
}

string Mission::getMName()
{
	return mName;
}

string Mission::getMDesc()
{
	return mDesc;
}

string Mission::getMType()
{
	return mType;
}

int Mission::getMDur()
{
	return mDur;
}

string Mission::getMDiff()
{
	return mDifficulty;
}

string Mission::getMSector()
{
	return mLSector;
}

string Mission::getMSystem()
{
	return mLSystem;
}

	//Comprehensive Info
int Mission::getMCBEReq()
{
	return mCBEReq;
}

string Mission::getMSCReq()
{
	return mSCReq;
}

string Mission::getMMWReq()
{
	return mMWReq;
}

string Mission::getMTName()
{
	return mTName;
}

string Mission::getMTSClass()
{
	return mTSClass;
}

int	Mission::getMBounty()
{
	return mBounty;
}

int Mission::getMXR()
{
	return mXR;
}

int Mission::getMRR()
{
	return mRR;
}

int Mission::getMDiR()
{
	return mDiR;
}

int Mission::getMDR()
{
	return mDR;
}

int Mission::getMLR()
{
	return mLR;
}

int Mission::getMPlR()
{
	return mPlR;
}

int Mission::getMUR()
{
	return mUR;
}

int Mission::getMPR()
{
	return mPR;
}

int Mission::getMNWR()
{
	return mNWR;
}

int Mission::getMEXPR()
{
	return mEXPR;
}

string Mission::getMIR()
{
	return mIR;
}

void Mission::updateMission(bool bChangeTName, string tname, bool bChangeMLSector, string mlsector, bool bChangeMLSystem, string mlsystem, bool bChangeDur, int duration)
{
	if (bChangeTName)
	{
		mTName = tname;
	}

	if (bChangeMLSector)
	{
		mLSector = mlsector;
	}

	if (bChangeMLSystem)
	{
		mLSystem = mlsystem;
	}

	if (bChangeDur)
	{
		mDur = duration;
	}
}

string Mission::getMState()
{
	if (mState == 0)
	{
		return "In Progress";
	}

	else if (mState == 1)
	{
		return "Partially Completed";
	}

	else if (mState == 2)
	{
		return "Completed";
	}

	else if (mState == 3)
	{
		return "Closed";
	}

	else if (mState == 4)
	{
		return "Failed";
	}
}

void Mission::updateMState(int state)
{
	mState = state;
}

int Mission::getMID()
{
	return mID;
}

int Mission::getMStateID()
{
	return mState;
}

void Mission::setMName(string name)
{
	mName = name;
}

void Mission::setMDesc(string desc)
{
	mDesc = desc;
}

void Mission::setMType(string type)
{
	mType = type;
}

void Mission::setMDur(int dur)
{
	mDur = dur;
}

void Mission::setMDiff(string difficulty)
{
	mDifficulty = difficulty;
}

void Mission::setMSector(string sector)
{
	mLSector = sector;
}

void Mission::setMSystem(string system)
{
	mLSystem = system;
}

void Mission::setMID(int id)
{
	mID = id;
}

void Mission::setMCBEReq(int lvl)
{
	mCBEReq = lvl;
}

void Mission::setMSCReq(string sclass)
{
	mSCReq = sclass;
}

void Mission::setMMWReq(string req)
{
	mMWReq = req;
}

void Mission::setMTName(string name)
{
	mTName = name;
}

void Mission::setMTSClass(string sclass)
{
	mTSClass = sclass;
}

void Mission::setMBounty(int i)
{
	mBounty = i;
}

void Mission::setMXR(int i)
{
	mXR = i;
}

void Mission::setMRR(int i)
{
	mRR = i;
}

void Mission::setMDiR(int i)
{
	mDiR = i;
}

void Mission::setMDR(int i)
{
	mDR = i;
}

void Mission::setMLR(int i)
{
	mLR = i;
}

void Mission::setMPlR(int i)
{
	mPlR = i;
}

void Mission::setMUR(int i)
{
	mUR = i;
}

void Mission::setMPR(int i)
{
	mPR = i;
}

void Mission::setMNWR(int i)
{
	mNWR = i;
}

void Mission::setMEXPR(int i)
{
	mEXPR = i;
}

void Mission::setMIR(string s)
{
	mIR = s;
}

void Mission::setMState(int i)
{
	mState = i;
}