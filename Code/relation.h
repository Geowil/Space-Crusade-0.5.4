#ifndef RELATIONS_H
#define RELATIONS_H

#include <string>

using std::string;

class Relation
{
public:

	Relation();
	Relation(string name, int affinity);

	void createRelation(string name, int affinity); //Create a new relationship

	void changeAffinity(int affinity, string operation); //Update relationship

	int getAffinity(); //Get status of relationship
	string getAffinityS(); //Get status of relationship in string form
	string getRName(); //Get entity name

	void setRName(string name);
	void setRAffinity(int affinity);

private:

	string	rName; //Name of entity the relationship is relevent to (IE: Earth Alliance)
	int		rAffinity; //Value of the relationship; negative numbers indicate a negative relationship.  See scale below.
};
#endif

/*
Relationship Scale:

-100 to -75: Enemies; pilots belonging to an entity of this relationship will attack you on sight and are not likely to respond to hails.  Stations may deny you access but will charge you up to 400% more.  Negative actions have a much larger effect until -100.  Under -100 affinity positive actions are half as effective.  At -100, positive actions are very ineffective.

-74 to -49: Paranoid; pilots belonging to an entity with this relationship will be very suspicious but will not attack you on sight.  May be agressive during hails and will be easily provoked.  Stations may deny you access but will charge you up to 250% more.  Negative actions have a much larger impact than positive ones and positive actions have a smaller impact.

-48 to -23: Suspicious; pilots belonging to an entity with this relationship will be suspicious but will not attack you on sight.  May be aggressive during hails and may be provoked.  Stations may deny you access but will charge you up to 150% more. Negative actions have a greater impact that positive ones.

-22 to -1: Cool; pilots belonging to an entity with this relationship will be wary but will not attack you on sight.  Small chance of being aggressive during hails and of being provoked into attacking.  Stations have a small chance of denying you acccess and will charge you up to 125% more.  Negative actions have a slightly higher impact than positive ones.

0: Ambivalent; the default relationship state.  No bonuses, positive or negative.

1 to 25: Acquaintances; pilots belonging to an entity with this relationship will be warm but may attack you if you threaten them.  May be slightly more likely to engage in trade.  Stations will charge you up to 10% less.  Negative actions will have a slightly lower impact than positive ones.

26 to 51: Warm; pilots belonging to an entity with this relationship will be warm and have a higher chance of not attacking you if you threaten them.  May be more likely to engage in trade.  Stations will charge you up to 20% less.  Negative actions will have a lower impact than positive ones.

52-77: Friendly; pilots belonging to an entity with this relationship will be helpful and a high chance of not attacking you if you threaten them.  Will be more likely to engage in trade.  Stations will charge you up to 25% less.  Negative actions will have much less of an impact than positive ones.

78 to 100: Allied; pilots belonging to an entity with this relationship will likely aid you if under attack and will not likely attack you if you threaten them.  Will be very likely to engage in trade.  Stations will charge you up to 35% less.  Negative actions will be half as costly untin 100 affinity.  Positive actions will have a much greater effect until 100 affinity.  At 100, negative actions are not very costly.
*/
