#include "entity.h"
#include "bentity.h"

bEntity::bEntity(Entity* entity1)
{
	entity = entity1; //Load current instance of entity into entity1
}

bEntity::bEntity(Shield* shield)
{
	pShield = shield;
}

bEntity::bEntity(Defense* defense)
{
	pDefense = defense;
}

bEntity::bEntity(Planet* planet)
{
	bPlanet = planet;
}

void bEntity::clearE()
{
	entity = 0; //Unload pointer when done using it
}

void bEntity::clearD()
{
	pDefense = 0;
}

void bEntity::clearS()
{
	pShield = 0;
}

void bEntity::clearP()
{
	bPlanet = 0;
}