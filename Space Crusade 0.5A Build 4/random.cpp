#include "random.h"
#include <cstdlib>


int Random(Range r)
{
	return r.mLow + rand() % ((r.mHigh + 1) - r.mLow);
}

int Random(int low, int high)
{
	return low + rand() % ((high + 1) - low);
}

float fRandom(float low, float high)
{
	return low + (float)rand()/((float)RAND_MAX/(high-low));
}