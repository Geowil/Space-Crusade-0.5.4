/*FILE HEADER

File Name:

tDamage.h

File Description:

This class will be used as class objects for a vector in Ship that will store turn based damage.

How it Works:

Special, turn based damage is calculated in Damage and then some functions in Ship are accessed to create a new element in the vector.
Into this element, via the contrusctor here, will go the damage done per turn by the weapon and the number of turns it will be applied including the turn the weapon is fired on; all turn based
damage is applied after the current battle turn is done.

A function in Damage is called at the end of each battle turn to process this damage.  Once the damage has been processed for a turn, a value of 1 is removed from tTComplete (turns till complete).

Once an element reaches zero it is removed from the vector.  Damage stacks but multiple damage of the same type will be limited to 50% effectiveness; for more on that see Damage.

Created On:

Wednesday, June 5, 2013

Version:

1.0 - 06/05/2013

Changes:

1.0 - Created the class

*/

#ifndef TDAMAGE_H
#define TDAMAGE_H

#include <string>
using std::string;

class tDamage
{
public:

	tDamage(float damage, int turns, string type); //Constructor

	void subTurn();
	
	float	getDamage();
	int		getTurns();
	string	getType();
	string	getATo();

	void	setATo(string s);

private:
	
	float	tBDamage;
	int		tTComplete;
	string	dType;
	string	appliedTo;
};
#endif