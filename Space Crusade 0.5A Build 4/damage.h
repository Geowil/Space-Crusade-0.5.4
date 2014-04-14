/*FILE HEADER

File Name:

damage.h

File Description:

This class handles all damage processing for battle.

How it Works:

Attacker and target entities are identified and sent through the damage loop.  Attacker's attack is processed and damage is applied to the target.  If there are any
special damage bonuses to be applied they also happen during this stage.

Created On:

Monday, February 11, 2013

Version:

1.0 - 02/01/2013
1.1 - 02/08/2013
1.2 - 02/16/2013
1.3 - 02/27/2013
1.4 - 02/28/2013
1.5 - 4/10/2013
1.6 - 4/30/2013
1.7 - 6/4/2013
1.8 - 6/18/2013
1.9 - 10/10/2013
1.10 - 10/11/2013

Changes:

1.0:
-Created the class

1.1:
-Renamed to Damage

1.2:
-Added bPAttack and bHAttack functions

1.3:
-Added setupWQueue and cleanWQueue to deal with maintenance on the weapon queue vector

1.4:
-Added new member variables vDamage, mDamage, fDamage, tSDamage, and sDamage
-Added dLow and dHigh variables to store damage ranges
-Added nSDamage, nADamage, and nHDamage for nanite damage claculation
-Added several new functions: processWQueue, processSDamage, processSecDamage, getSDNTurns,
and getSDNANTurns.
-Started coding bPAttack and added code for all of the functions listed above

1.5:
-Added two new classes to store player and hostile ship objects
-Changed how the class executes.  Starts from dmgProcessing after initializing bAttacker and bTarget
-Started recoding to take those changes into account
-Added other weapon types to weapon queue processing code

1.6:
-Moved bAttacker and bTarget out of this class into a seperate one and did the required
code changes to compensate
-Removed stand alone EMP damage functions and merged then streamlined them in processSDamage
-Added the rest of the damage bonus and turn defines

1.7:
-Started recoding processSDamage to add priecing damage types and so that I could move it in
the new direction I am taking the class
-Removed much of the code from processSDamage relating to turn-based damage to take into account
recent changes
-Added new function called processDamage that takes the place of takeDamage in entity
-Removed any references to sDamage and mDamage as they are no longer needed
-Changed how damage is set up in processWQueue so that it is added directly to
vDamage and then removed the sDamage pass to processSDamage as it was not required

1.8:
-Added two new functions called getTDamage and processTDamage to handle turn-based damage
-Removed napalm and nanite code from processSDamage and replaced with code that sets up the
vector elements in cDamage in Ship

1.9:

-Added mDistance to store distances between the attacker and target for range related processing

1.10:

-Added dBCollateral to store extra damage done by bomb weapons weight

*/

#ifndef DAMAGE_H
#define DAMAGE_H

#include <string>
#include "entity.h"
#include "bentity.h"
#include "hardPoint.h"
#include "tDamage.h"
#include <vector>

using std::string;
using std::vector;

class Damage
{
public:

	Damage();

	void dmgProcessing(bEntity& bAttacker, bEntity& bTarget); //Ship-to-Ship
	void dmgProcessing_PS(bEntity& bAttacker, bEntity& bTarget); //Planet: Shield
	void dmgProcessing_PDP(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Player Attacker
	void dmgProcessing_PDD(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Defense Attacker
	void dmgProcessing_PB(bEntity& bAttacker, bEntity& bTarget); //Planet: Bombing

	//Generate damage
	void bAttack(bEntity& bAttacker, bEntity& bTarget); //Ship-to-Ship
	void bAttack_PS(bEntity& bAttacker, bEntity& bTarget); //Planet: Shield
	void bAttack_PDP(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Player Attacker
	void bAttack_PDD(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Defense Attacker
	void bAttack_PB(bEntity& bAttacker, bEntity& bTarget); //Planet: Bombing

	//Set final damage
	void bDamage(bEntity& bAttacker, bEntity& bTarget); //Ship-to-Ship
	void bDamage_PS(bEntity& bAttacker, bEntity& bTarget); //Planet: Shield
	void bDamage_PDP(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Player Attacker
	void bDamage_PDD(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Defense Attacker
	void bDamage_PB(bEntity& bAttacker, bEntity& bTarget); //Planet: Bombing

	void setupWQueue(bEntity& bAttacker);
	void setupWQueue_PD(bEntity& bAttacker);
	void setupWQueue_PB(bEntity& bAttacker);

	void cleanWQueue();

	void processWQueue(bEntity& bAttacker, bEntity& bTarget);
	void processWQueue_PB(bEntity& bAttacker, bEntity& bTarget, bool pAPDef, bool pAPShd, bool pADef);

	void processSDamage(bEntity& bAttacker, bEntity& bTarget);
	void processSDamage_PS(bEntity& bAttacker, bEntity& bTarget);
	void processSDamage_PD(bEntity& bAttacker, bEntity& bTarget);

	//Apply Damage
	void processDamage(bEntity& bAttacker, bEntity& bTarget, bool defense); //Ship-to-Ship & Planet: Defense, Defense Attacker
	void processDamage_PS(bEntity& bAttacker, bEntity& bTarget); //Planet: Shield
	void processDamage_PDP(bEntity& bAttacker, bEntity& bTarget); //Planet: Defense, Player Attacker
	void processDamage_PB(bEntity& bAttacker, bEntity& bTarget); //Planet: Bombing

	//BAT Functions for ship-to-ship battle
	void setupBAT(Entity* entity1, Entity* entity2);
	void clearBAT(bEntity& bAttacker, bEntity& bTarget);

	//BAT Functions for Planet Battle

	//Planet Battle: Shield
	void setupBAT_PS(Entity* entity1, Shield* pShield, Planet* bPlanet);
	void clearBAT_PS(bEntity& bAttacker, bEntity& bTarget);

	//Planet Battle: Defense; Player Attacking
	void setupBAT_PDPA(Entity* entity1, Defense* pDefense, Planet* bPlanet);
	void clearBAT_PDPA(bEntity& bAttacker, bEntity& bTarget);

	//Planet Battle: Defense: Player Targeted
	void setupBAT_PDDA(Defense* pDefense, Entity* entity1);
	void clearBAT_PDDA(bEntity& bAttacker, bEntity& bTarget);

	//Planet Battle: Planet
	void setupBAT_PB(Entity* entity1, Planet* bPlanet);
	void clearBAT_PB(bEntity& bAttacker, bEntity& bTarget);

	void setupAType(bool allout, bool spread, bool wsystem, bool single); 

	void getTDamage(bEntity& bTarget); //Get each turn based damage
	void getTDamage_PDP(bEntity& bTarget);

	void processTDamage(bEntity& bTarget, int elm); //Apply that damage and decrement the turns left by one
	void processTDamage_PDP(bEntity& bTarget, int elm);

private:

	vector<hardPoint> weaponQueue;

	float vDamage; //Vanilla Damage
	float mDamage; //Modified Damage
	float fDamage; //Final Damage
	float sDamage; //Secondary Damage
	float tDamage; //Storage for turn based damage

	int i;

	int sDNTurns, sDNANTurns; //Number of turns to apply secondary damage for (N = Napalm, NAN = Nanite)
	

	int dLow, dHigh;

	int weapons;
	int bCSpread;

	string wDType, tDType; //store weapon and turn based damage types
	string aType; //attack type

	bool bIsDestroyed; //Bool for checking if a target has been destroyed, to short circuit for loop processing if there is no target

	float nSDamage, nADamage, nHDamage; //Health interface variables for nanite secondary damage
	float npDamage; //To store extra napalm damage

	float mDistance;
	float dBCollateral;

	Planet* tempPlanet;

};
#endif


/*Damage Types:

piercing1: Armor Piercing, does not affect hull
piercing2: Hull Piercing, does not affect armor
piercing3: Armor and Hull piercing
napalm1: low level napalm damage, lasts two turns
napalm2: medium level napalm damage, lasts four turns
napalm3: high level napalm damage, lasts six turns
destructor: higher damage to defenses
nanite1: low level nanite damage, does 5% of HP damage for two turns
nanite2: medium level nanite damage, does 8% of HP damage for four turns
nanite3: high level nanite damage, does 15% of HP damage for eight turns
doomsday1: large scale damage, kills off 25% of population instantly along with 15% of all infrastructure and 10% of biomass
doomsday2: larger scale damage, kills off 40% of population instantly along with 25% of all infrastructure and 18% of biomass
stealth: invisible to point defenses, point defenses will still have a 2% chance to destroy a missile volley per point defense up to 10%.
frigonly: only damages frigate class ships, no damage to higher classes
null: no special damage
emp1: low level shield damage, if shields down will cripple non-emp protected target for one turn
emp2: medium level shield damage, if shields down will cripple non-emp protected target for three turns
emp3: high level shield damage, if shields down will cripple non-emp protected target for seven turns
virus1: scrambles targeting systems of enemy ship, target will not attack for two turns and loses shields
virus2: scrambles targeting systems and crashes computer, target will not attack for five turns and loses shields
virus3: scrambles targeting systems, crashes computer, and disables life support and loses shields (RTS/RPG).  Crews of ships lower then crusier class can be killed in two turns and ship can be salvaged whole (twice the resources; RTS only)
virus4: crashes all systems and injects core breach code into engines and loses shields.  35% chance that the ship will self destruct over 4 turns, after which systems reboot and core breach stopped.  10% chance per 20 tech crewmen or 5 tech module on board to avert code breach. (RTS only)
massaccel: Mass Accelerator damage bypasses shield and armor and deals direct hull damage.

*/