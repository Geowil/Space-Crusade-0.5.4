#ifndef BENTITY_H
#define BENTITY_H

#include "entity.h"
#include "planet.h"


class bEntity
{
public:

	//Consturctor for normal ship-to-ship battle
	bEntity(Entity* entity1);

	//Constructor for planet: ship-to-shield battle
	bEntity(Shield* shield);

	bEntity(Defense* defense);

	bEntity(Planet* planet);

	void clearE();
	void clearD();
	void clearS();
	void clearP();

	Entity* entity; //store accessed entity as pointer so we can access it from the class as needed
	
	Shield* pShield; //Store shield object
	
	Defense* pDefense; //Store defense object

	Planet* bPlanet; //Store planet pointer
};
#endif