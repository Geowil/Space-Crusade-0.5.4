#include <vector>
#include "battleproc.h"
#include "random.h"
#include "datasystem.h"
#include "damage.h"
#include "msgproc.h"
#include "map.h"

/*  NOTES

Damage Type and Disabling system:

Stealth also applies to planetary defenses, will need to create a function to check if the weapon is detected or not.  If it is it can be shot down in another function call,
if not detected then it does extra damage.
*/

using namespace std;

//Class references
dataSystem ds;
Damage d;
msgProc mp;
Map m;

//Variable Init
battleProc::battleProc()
{
		sCode = 0; //Ship item code
		rCode = 0; //Race code
		wCode = 0; //Weapon item code
		i = 0; //For for loops
		i2 = 0; //Same as above
		banks = 0; //Total number of laser banks
		iBanks = 0; //number of installed lasers
		turrets = 0; //Total number of missile turrets
		iTurrets = 0; //Number of installed launchers
		bombs = 0; //Total number of bomb holds
		iBombs = 0; //Number of uses holds

		//Reward Variables
		rX = 0; //Xarn
		rR = 0; //Rubies
		rDi = 0; //Diamonds
		rD = 0; //Draconic
		rL = 0; //Lithium
		rPl = 0; //Platinum
		rU  = 0; //Uranium
		rP = 0; //Plutonium
		rNW = 0; //Nuclear Waste
		rCXP = 0; //CEXP
}

string battleProc::sBLoop(Player& mPlayer, Planet* gPlanet, bool defenders, Game& mGame, NPC& mNPC)
{
	bPBattle = false;
	
	//initialize hostile team
	bTSetup(mPlayer, false, gPlanet); //get number of hostile ships
	bInit(mPlayer, mNPC); //initialize ships into array w/ default values
	bAParticipants(mPlayer, mNPC); //Determine attack order

	m.setPOS(mPlayer, mNPC);

	//Setup default player/hostile target
	pTarget = 0;
	hTarget = 0;
	
	//Get player to pick a target
	getPTarget(mNPC);
	//bIsCTHostile = true;

/*	//Pre-battle menu loop
	while (!bBStarted)
	{
		//Continue with battle loop processing for player
		pChoice = mp.bMenu1();

		switch(pChoice)
		{
		case 1:
			
			if (pTarget == 0)
			{
				bPHail(mNPC.getRace(),mNPC.getAffil(), mPlayer);
			}

			else
			{
				bPHail(mNPC.eWingmen.at(pTarget-1).getRace(),mNPC.eWingmen.at(pTarget-1).getAffil(), mPlayer);
			}			
				
			break;

		case 2:
			bBStarted = true;
			break;

		case 3:

			if(pTarget == 0)
			{
				mp.hBStatus(mNPC);				
			}
			
			else
			{
				mp.hBStatus(mNPC.eWingmen.at(pTarget-1));
			}
			
			break;

		case 4:
			bEnd = bRetreat();
			break;
		}

		if (bDTSurrender) //If enemy surrenders end the battle and break the while loop
		{
			bEnd = true;
			bpResult = "No Battle";
			break;
		}

		else if (bDTTrade) //If the ship engaged in trade end the battle and break the loop
		{
			bEnd = true;
			bpResult = "No Battle";
			break;
		}

		else if (bITNHostile) //If the ship did not take a hostile act end the battle and break the loop
		{
			bEnd = true;
			bpResult = "No Battle";
			break;
		}

		else if (bEnd) //If player escaped end the battle and break the loop
		{
			bDPEscape = true;
			bpResult = "Escaped";
			break;
		}
	}*/

//	if (bBStarted)
//	{
	while (!bEnd)
	{
		bEMenu = false;

		//execute attack order
		for (i = 0; i < battleParticipants.size(); i++)
		{
			fCAttacker = battleParticipants.at(i).getName(); //Get name of attacking entity for this turn

			if ((mPlayer.getName() == fCAttacker) && (!mPlayer.Ship.isDisabled())) //If current attacker is the player and ship is not disabled
			{
				if (pTarget == 0)
				{
					if (mNPC.Ship.getSHull() <= 0) //Make player pick a new target if current one is destroyed
					{
						getPTarget(mNPC);
					}
				}

				else
				{
					if (mNPC.eWingmen.at(pTarget-1).Ship.getSHull() <= 0) //Make player pick a new target if current one is destroyed
					{
						getPTarget(mNPC);
					}
				}

				while (!bEMenu)
				{
					//Continue with battle loop processing for player
					pChoice = mp.bMenu1B(hostiles);

					switch(pChoice)
					{
					case 1:
						pChoice = mp.bMenu2();
						bPFSolutions(pChoice, mPlayer, mNPC);
						bIsPTFighting = true;
						bEMenu = true;
						break;

					case 2:
						getPTarget(mNPC);
						break;

					case 3:
						mp.pBStatus(mPlayer);
						break;

					case 4:

						if (pTarget == 0)
						{
							mp.hBStatus(mNPC);
						}

						else
						{
							mp.hBStatus(mNPC.eWingmen.at(pTarget-1));
						}

						break;

					case 5:

						if (pTarget == 0)
						{
							mPlayer.Ship.sPMove(mPlayer, mNPC);
						}

						else
						{
							mPlayer.Ship.sPMove(mPlayer,mNPC.eWingmen.at(pTarget-1));
						}

						bEMenu = true;
						break;

					case 6:
						bEnd = bRetreat();

						if (bEnd)
						{
							bDPEscape = true;
						}

						bEMenu = true;
						break;

					default:
						bEnd = bRetreat();

						if (bEnd)
						{
							bDPEscape = true;
						}

						bEMenu = true;
						break;
					}				
				}
			}

			else if ((mPlayer.getName() == fCAttacker) && (mPlayer.Ship.isDisabled())) //If player ship is disabled
			{
				mPlayer.Ship.dTDecrement(); //Call disable timer decrement
			}

			else if ((mNPC.getName() == fCAttacker) && (!mNPC.Ship.isDestroyed()) && (!mNPC.Ship.isDisabled()) && (mNPC.getStatus() == "In Battle")) //If the current attacker is main hostile and is not destroyed or disabled
			{
				aiHTasks(mNPC, mPlayer);
			}

			else if ((mNPC.getName() == fCAttacker) && (!mNPC.Ship.isDestroyed()) && (mNPC.Ship.isDisabled()) && (mNPC.getStatus() == "In Battle")) //If current attacker is main hostile ship is not destroyed but is disabled
			{
				mNPC.Ship.dTDecrement(); //Call disable timer decrement
			}


			if (allies > 0) //Continue if player has allies
			{
				for (i2 = 0; i2 < allies; i2++)
				{
					if (mPlayer.eWingmen.at(i2).getName() == fCAttacker) //If this turn entity is this wingman continue
					{
						if ((!mPlayer.eWingmen.at(i2).Ship.isDestroyed()) && (!mPlayer.eWingmen.at(i2).Ship.isDisabled()) && (mPlayer.eWingmen.at(i2).getStatus() == "In Battle")) //If this wingman is not destroyed and is not disabled
						{
							if (bIsPTFighting) //If player team is engaded in battle continue
							{
								aiATasks(mPlayer.eWingmen.at(i2), mNPC);
							}
						}

						else if ((!mPlayer.eWingmen.at(i2).Ship.isDestroyed()) && (mPlayer.eWingmen.at(i2).Ship.isDisabled()) && (mPlayer.eWingmen.at(i2).getStatus() == "In Battle")) //If current player wingman ship disabled and is not destoyed but is disabled
						{
							mPlayer.eWingmen.at(i2).Ship.dTDecrement(); //Call disable timer decrement
						}
					}
				}
			}

			if (hostiles > 0) //If main hostile has allies
			{
				for (i2 = 0; i2 < hostiles; i2++)
				{
					if (mNPC.eWingmen.at(i2).getName() == fCAttacker) //If current wingman is attacker continue
					{
						if ((!mNPC.eWingmen.at(i2).Ship.isDestroyed()) && (!mNPC.eWingmen.at(i2).Ship.isDisabled()) && (mNPC.eWingmen.at(i2).getStatus() == "In Battle")) //If the current wingman is not destroyed and is not disabled
						{
							if (bIsHTFighting) //If player team is engaded in battle continue
							{
								aiHTasks(mNPC.eWingmen.at(i2), mPlayer);
							}
						}

						else if ((!mNPC.eWingmen.at(i2).Ship.isDestroyed()) && (mNPC.eWingmen.at(i2).Ship.isDisabled()) && (mNPC.eWingmen.at(i2).getStatus() == "In Battle")) //If current wingman ship disabled but is not destoyed
						{
							mNPC.eWingmen.at(i2).Ship.dTDecrement(); //Call disable timer decrement
						}
					}
				}
			}

			//Check to see if all ships on enemy team are destroyed after all turns are done
			if (i == battleParticipants.size()-1)
			{
				for (i2 = 0; i2 <= hostiles+1; i2++)
				{
					if ((i2 == hostiles + 1) && (hNIBattle == hostiles) && (hostiles != 0)) //This goes first so that eWingmen does not go out of bounds
					{
						bEnd = true;
						break; //So we do not hit any of the other conditional statements here; if i2 is 0 and hostiles is 0, without this we could hit the next else if and potentially error
					}

					else if (i2 == 0)
					{
						if (mNPC.Ship.isDestroyed() || mNPC.getStatus() == "Retreated" || mNPC.getStatus() == "Surrendered")
						{
							if (hostiles == 0)
							{
								bEnd = true;
							}

							else if ((mNPC.Ship.isDestroyed()) && (mNPC.getStatus() != "Destroyed"))
							{
								mNPC.setStatus("Destroyed");

							}

							//hNIBattle += 1;
						}
					}

					else if ((mNPC.getNOWingmen() > 0) && ((i2 > 0) && (i2 < hostiles+1)))
					{
						if (mNPC.eWingmen.at(i2-1).Ship.isDestroyed() || mNPC.eWingmen.at(i2-1).getStatus() == "Retreated" || mNPC.eWingmen.at(i2-1).getStatus() == "Surrendered")
						{
							hNIBattle += 1;

							if (mNPC.eWingmen.at(i2-1).Ship.isDestroyed())
							{
								mNPC.eWingmen.at(i2-1).setStatus("Destroyed");
							}
						}
					}					
				}
			}

			if (mPlayer.Ship.isDestroyed() || mPlayer.getStatus() == "Surrendered" || mPlayer.getStatus() == "Captured")
			{
				bEnd = true;
			}

			if (bEnd)
			{
				break; //If battle is over break from this for loop and allow the while loop to continue
			}
		}
	}
	
	if (mPlayer.Ship.isDestroyed()) //Make sure battle not ended from player death
	{
		if(!mPlayer.gOver(mGame, mPlayer))
		{
			bpResult = "Used Clone";
		}

		else
		{
			bpResult = "Destroyed";
		}
	}

	else if (bEnd) //If player not destroyed load end battle
	{
		endBattle(mPlayer, mNPC);

		//Reset bools
		bDPEscape = false;
		bBStarted = false;
		bDTSurrender =  false;
		bDTTrade =  false;
		bITNHostile = false;
		bEnd = false;
		pGOver = false;
		pWin = false;
		bIsPTFighting = false;
		bIsHTFighting = false;
		hNIBattle = 0;
		hostiles = 0;
		
		battleParticipants.clear(); //Clear the vector before using it

		bpResult = "Won";
	}

	return bpResult;
}

string battleProc::pBLoop(Player& mPlayer, Planet* gPlanet, Game& mGame)
{
	bTSetup(mPlayer, true, gPlanet); //get number of hostile ships

	//Determine attack order
	bAParticipants_PB(mPlayer, gPlanet);

	pBPSTarget = -1;
	pBPDTarget = -1;
	aBPSTarget = -1;
	aBPDTarget = -1;

	if (allies > 0)
	{
		//Show player team status
		mp.pBAStatus(mPlayer, allies);
	}
	
	else
	{
		mp.pBStatus(mPlayer);
	}		

	while (!bEnd)
	{		
		//execute attack order
		for (i = 0; i < battleParticipants.size(); i++)
		{
			fCAttacker = battleParticipants.at(i).getName(); //Get name of attacking entity for this turn

			if ((mPlayer.getName() == fCAttacker) && (!mPlayer.Ship.isDisabled())) //If current attacker is the player and ship is not disabled
			{
				bEMenu = false;
				//Gets messy here.  We need to differentiate between shield, defense, and planet targets.  Each needs their own specific functions so either multiple switches

				if (gPlanet->pShd.size() > 0)
				{
					pBAShields = 0; //Reset this value each turn so that we get an updated value

					//If the planet has shields, player is forced to target the first most sheild in the vector that has SP (SP regenerates so we need to check this each time through if the conditions above are met
					for (i2 = 0; i2 < gPlanet->pShd.size(); i2++)
					{
						if (pBPSTarget == -1)
						{
							if (!gPlanet->pShd.at(i2).isDisabled())
							{
								pBPSTarget = i2;
							}
						}

						else if (pBPSTarget != -1)
						{
							if (gPlanet->pShd.at(pBPSTarget).isDisabled())
							{
								if ((!gPlanet->pShd.at(i2).isDisabled()) && (i2 != pBPSTarget)) //Find first enabled shield and make sure that we have not already targeted it
								{
									pBPSTarget = i2; //Set the player's target
									//pBAShields += 1; //Notify the game that a shield is active							
								}
							}
						}

						if (!gPlanet->pShd.at(i2).isDisabled())
						{
							pBAShields += 1;
								
						}
						
						else if (pBAShields > 1) //Make sure we never go below zero; if first shield is down then this does to -1 on the update.  Make sure that we never take off a value unless we are higher than 1; if we do then we allow player to attack planet even if it has an active shield
						{
							pBAShields -= 1;
						}
					}
				}

				else
				{
					pBAShields = 0; //Set to 0 as no shields are present
				}

				if (pBAShields > 0) //If planet has active shields then force player to attack the target set above
				{
					while (!bEMenu)
					{
						//Continue with battle loop processing for player
						pChoice = mp.bMenu1B_PB1();

						switch(pChoice)
						{
						case 1:
							pChoice = mp.bMenu2();
							bPFSolutions_PB(pChoice, mPlayer, gPlanet, true, false, false);
							bIsPTFighting = true;
							bEMenu = true;
							break;

						case 2:
							mp.pBStatus(mPlayer);
							break;

						case 3:
							mp.hBSStatus_PB(gPlanet, true, pBPSTarget, false, 0, false);
							break;

						default:
							bEnd = bRetreat();
							bEMenu = true;
							break;
						}
					}
				}

				else if ((pBAShields <= 0) && (hostiles > 0)) //If planet has no shields or no active shields and has defensive structures continue
				{
					//Get player to pick a target
					
					if (pBPDTarget == -1 || gPlanet->pDef.at(pBPDTarget).getState() == "Destroyed")
					{
						getPTarget_PB(gPlanet);
						bIsCTHostile = true;
					}

					while (!bEMenu)
					{
						//Continue with battle loop processing for player
						pChoice = mp.bMenu1B_PB3(hostiles);

						switch(pChoice)
						{
						case 1:
							pChoice = mp.bMenu2();
							bPFSolutions_PB(pChoice, mPlayer, gPlanet, false, true, false);
							bIsPTFighting = true;
							bEMenu = true;
							break;

						case 2:
							getPTarget_PB(gPlanet);
							break;

						case 3:
							mp.pBStatus(mPlayer);
							break;

						case 4:
							mp.hBSStatus_PB(gPlanet, false, 0, true, pBPDTarget, false);
							break;

						case 5:
							bEnd = bRetreat();
							bEMenu = true;
							break;

						default:
							bEnd = bRetreat();
							bEMenu = true;
							break;
						}
					}
				}

				else if ((hostiles < 1) && (pBAShields == 0)) //If planet has no shields or no active shields and no defensive structures then start planet bombardment phase
				{					
					bIsCTHostile = true;

					while (!bEMenu)
					{
						//Continue with battle loop processing for player
						pChoice = mp.bPBMenu();

						switch(pChoice)
						{
						case 1:
							mp.hBSStatus_PB(gPlanet, false, 0, false, 0, true);
							break;

						case 2:
							pChoice = mp.bMenu2_PB();
							bPFSolutions_PB(pChoice, mPlayer, gPlanet, false, false, true);
							bIsPTFighting = true;
							bEMenu = true;
							break;

						case 3:
							bEnd = bRetreat();
							bEMenu = true;
							break;

						default:
							bEnd = bRetreat();
							bEMenu = true;
							break;
						}
					}
				}
			}

			else if ((mPlayer.getName() == fCAttacker) && (mPlayer.Ship.isDisabled())) //If player ship is disabled
			{
				mPlayer.Ship.dTDecrement(); //Call disable timer decrement
			}

			if (allies > 0) //Continue if player has allies
			{
				for (i2 = 0; i2 < allies; i2++)
				{
					if (mPlayer.eWingmen.at(i2).getName() == fCAttacker) //If this turn entity is this wingman continue
					{
						if ((!mPlayer.eWingmen.at(i2).Ship.isDestroyed()) && (!mPlayer.eWingmen.at(i2).Ship.isDisabled()) && (mPlayer.eWingmen.at(i2).getStatus() == "In Battle")) //If this wingman is not destroyed and is not disabled
						{
							if (gPlanet->pShd.size() > 0)
							{
								pBAShields = 0; //Reset this value each turn so that we get an updated value

								//If the planet has shields, player is forced to target the first most sheild in the vector that has SP (SP regenerates so we need to check this each time through if the conditions above are met
								for (i3 = 0; i3 < gPlanet->pShd.size(); i3++)
								{
									if (pBPSTarget == -1)
									{
										if (!gPlanet->pShd.at(i3).isDisabled())
										{
											pBPSTarget = i3;
											aBPSTarget = i3;
										}
									}

									else if (pBPSTarget != -1)
									{
										if (gPlanet->pShd.at(pBPSTarget).isDisabled())
										{
											if ((!gPlanet->pShd.at(i3).isDisabled()) && (i3 != pBPSTarget)) //Find first enabled shield and make sure that we have not already targeted it
											{
												pBPSTarget = i3; //Set the player's target
												aBPSTarget = i3;
												//pBAShields += 1; //Notify the game that a shield is active							
											}
										}
									}

									if (!gPlanet->pShd.at(i3).isDisabled())
									{
										pBAShields += 1;

									}

									else if (pBAShields > 1) //Make sure we never go below zero; if first shield is down then this does to -1 on the update.  Make sure that we never take off a value unless we are higher than 1; if we do then we allow player to attack planet even if it has an active shield
									{
										pBAShields -= 1;
									}
								}
							}

							else
							{
								pBAShields = 0; //Set to 0 as no shields are present
							}

							if (pBAShields > 0)
							{
								aiATasks_PB(mPlayer.eWingmen.at(i2), gPlanet, true, false, false);
							}

							else if ((pBAShields <= 0) && (hostiles > 0))
							{
								if (aBPDTarget == -1)
								{
									while(aBPDTarget == -1)
									{
										i3 = Random(0,gPlanet->pDef.size()-1);

										for (i4 = 0; i4 <= gPlanet->pDef.size(); i4++)
										{
											if (i4 == gPlanet->pDef.size())
											{
												i4 = -1; //In case something goes wrong with the random above
											}

											else if (i4 == i3)
											{
												if (gPlanet->pDef.at(i4).getSPoints() > 0.0f)
												{														
													aBPDTarget = i4;
												}
											}
										}

										if (i4 == -1)
										{
											break; //Break becasue the planet has no defenses; Not really needed but put here in case something goes wrong, adds a layer of crash prevention.
										}
									}
								}

								else if (gPlanet->pDef.at(aBPDTarget).getSPoints() > 0.0f || hostiles != 0)
								{
									aiATasks_PB(mPlayer.eWingmen.at(i2), gPlanet, false, true, false);
								}									
							}							

							else
							{
								if (gPlanet->getPop() > 0) //Check so we do not atttack a planet with no population
								{
									aiATasks_PB(mPlayer.eWingmen.at(i2), gPlanet, false, false, true);
								}
							}
						}
					}

					else if ((!mPlayer.eWingmen.at(i2).Ship.isDestroyed()) && (mPlayer.eWingmen.at(i2).Ship.isDisabled()) && (mPlayer.eWingmen.at(i2).getStatus() == "In Battle")) //If current player wingman ship disabled and is not destoyed but is disabled
					{
						mPlayer.eWingmen.at(i2).Ship.dTDecrement(); //Call disable timer decrement
					}
				}
			}

			if (hostiles > 0) //If planet has non-destroyed defenses
			{
				for (i2 = 0; i2 < gPlanet->pDef.size(); i2++)
				{
					if ((gPlanet->pDef.at(i2).getDName() == fCAttacker) && (gPlanet->pDef.at(i2).getSPoints() > 0.0f))
					{	
						aiHTasks_PB(gPlanet->pDef.at(i2), mPlayer);
						break;
					}

					else if ((i2 == pBPDTarget) && (gPlanet->pDef.at(i2).getSPoints() <= 0.0f) && (gPlanet->pDef.at(i2).getState() != "Destroyed"))
					{
						hostiles -= 1; //If a defense is destroyed remove one from the hostiles counter
						gPlanet->pDef.at(i2).setState("Destroyed");
						break;
					}
				}
			}

			if ((gPlanet->pShd.size() > 0) && (fCAttacker == mPlayer.getName())) //If there are active shields
			{
				for (i2 = 0; i2 < gPlanet->pShd.size(); i2++)
				{
					if (!gPlanet->pShd.at(i2).isDisabled())
					{
						if (gPlanet->pShd.at(i2).getSP() < gPlanet->pShd.at(i2).getMSP()) //Check to make sure shields are not disabled and are depeleted
						{
							gPlanet->pShd.at(i2).psRegen(); //Run regen function to regenerate shielding for this shield
						}
					}

					else
					{
						if (!gPlanet->pShd.at(i2).getDTGState())
						{
							gPlanet->pShd.at(i2).dTTDown(gPlanet);
						}

						else
						{
							gPlanet->pShd.at(i2).updateDTGrace(false); //After one turn, set this to false so ticking can happen
						}
					}
				}
			}

			if (gPlanet->getPop() == 0 || gPlanet->getStatus() == "Surrendered")
			{
				bEnd = true;
			}

			if (mPlayer.Ship.isDestroyed() || mPlayer.getStatus() == "Surrendered" || mPlayer.getStatus() == "Captured")
			{
				bEnd = true;
			}

			if (bEnd)
			{				
				bpResult = "Battle Over";
				break; //If battle is over break from this for loop and allow the while loop to continue
			}

			bEMenu = false;
		}
	}

	if (mPlayer.Ship.isDestroyed()) //Make sure battle not ended from player death
	{		
		if(!mPlayer.gOver(mGame, mPlayer))
		{
			bpResult = "Used Clone";
		}

		else
		{
			bpResult = "Destroyed";
		}
	}

	else if (bEnd) //If player not destroyed load end battle
	{
		endBattle_PB(mPlayer, gPlanet);
	}

	//Reset bools
	bEnd = false;
	pGOver = false;
	pWin = false;
	bIsPTFighting = false;
	bIsHTFighting = false;

	battleParticipants.clear(); //Clear the vector before using it
	
	if ((bpResult != "Destroyed") && (mPlayer.getStatus() != "Captured") && (mPlayer.getStatus() != "Retreated") && (bpResult != "Used Clone"))
	{
		bpResult = "Won";
	}

	return bpResult;
}

void battleProc::bTSetup(Player& mPlayer, bool planet, Planet* gPlanet)
{
	if (!planet)
	{
		if (mPlayer.getCELvl() <= 30)
		{
			battleSize = Random(1, 1000);

			//60% chance of 0 hostile battle
			if ((battleSize >= 1) && (battleSize <= 600))
			{
				hostiles = 0;	
			}

			//30% chance of 2 hostile battle
			else if ((battleSize >= 601) && (battleSize <= 900))
			{
				hostiles = 1;
			}

			//10% chance of 3 hostile battle
			else if ((battleSize >= 901) && (battleSize <= 1000))
			{
				hostiles = 2;
			}
		}

		else if ((mPlayer.getCELvl() >= 31) && (mPlayer.getCELvl() <= 60))
		{
			battleSize = Random(1, 1000);

			//30% chance of 1 hostile battle
			if ((battleSize >= 1) && (battleSize <= 300))
			{
				hostiles = 1;	
			}

			//45% chance of 2 hostile battle
			else if ((battleSize >= 301) && (battleSize <= 745))
			{
				hostiles = 2;
			}

			//25% chance of 3 hostile battle
			else if ((battleSize >= 745) && (battleSize <= 1000))
			{
				hostiles = 3;
			}
		}

		else if (mPlayer.getCELvl() < 60)
		{
			battleSize = Random(1, 1000);

			//15% chance of 1 hostile battle
			if ((battleSize >= 1) && (battleSize <= 150))
			{
				hostiles = 1;	
			}

			//55% chance of 2 hostile battle
			else if ((battleSize >= 151) && (battleSize <= 600))
			{
				hostiles = 2;
			}

			//30% chance of 3 hostile battle
			else if ((battleSize >= 601) && (battleSize <= 1000))
			{
				hostiles = 3;
			}
		}
	}

	else if (planet)
	{
		for (i = 0; i < gPlanet->pDef.size(); i++)
		{ 
			if (gPlanet->pDef.at(i).getSPoints() > 0)
			{
				hostiles += 1;
			}
		}
	}

	allies = mPlayer.getNOWingmen();
}

void battleProc::endBattle(Player& mPlayer, NPC& mNPC)
{
	if ((!bDPEscape) && (mPlayer.getStatus() != "Surrendered") && (mPlayer.getStatus() != "Captured")) //Only if player did not escape or was not captured
	{		
		//Get player rewards
		if (mNPC.Ship.isDestroyed())
		{
			//Set Rewards
			mNPC.initRewards();

			rX += mNPC.getXarn();
			rR += mNPC.getRubies();
			rDi += mNPC.getDia();
			rD += mNPC.getDrac();
			rL += mNPC.getLith();
			rPl += mNPC.getPlat();
			rU += mNPC.getUra();
			rP += mNPC.getPlut();
			rNW += mNPC.getNWaste();
			rCXP += mNPC.getCXPReward();

			if (mNPC.Ship.getSClass() == "Frigate")
			{
				fK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Destroyer")
			{
				dK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Cruiser")
			{
				cK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Battle Cruiser")
			{
				bcK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Battleship")
			{
				bK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Mothership")
			{
				mK += 1;
			}

			else if (mNPC.Ship.getSClass() == "Titan")
			{
				tK += 1;
			}
		}

		else if (mNPC.getStatus() == "Surrendered")
		{
			//Set Rewards
			mNPC.initRewards();

			//TODO: Figure out how to differentiate from a captured ship and a captured but sold ship
			rX += (mNPC.getXarn()) * 2;
			rR += (mNPC.getRubies()) * 2;
			rDi += (mNPC.getDia()) * 2;
			rD += (mNPC.getDrac()) * 2;
			rL += (mNPC.getLith()) * 2;
			rPl += (mNPC.getPlat()) * 2;
			rU += (mNPC.getUra()) * 2;
			rP += (mNPC.getPlut()) * 2;
			rNW += (mNPC.getNWaste()) * 2;
			rCXP += mNPC.getCXPReward();
		}
		
		for (i = 0; i < hostiles; i++)
		{			
			if (mNPC.eWingmen.at(i).Ship.isDestroyed())
			{
				//Set Rewards
				mNPC.eWingmen.at(i).initRewards();

				rX += mNPC.eWingmen.at(i).getXarn();
				rR += mNPC.eWingmen.at(i).getRubies();
				rDi += mNPC.eWingmen.at(i).getDia();
				rD += mNPC.eWingmen.at(i).getDrac();
				rL += mNPC.eWingmen.at(i).getLith();
				rPl += mNPC.eWingmen.at(i).getPlat();
				rU += mNPC.eWingmen.at(i).getUra();
				rP += mNPC.eWingmen.at(i).getPlut();
				rNW += mNPC.eWingmen.at(i).getNWaste();
				rCXP += mNPC.eWingmen.at(i).getCXPReward();

				if (mNPC.eWingmen.at(i).Ship.getSClass() == "Frigate")
				{
					fK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Destroyer")
				{
					dK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Cruiser")
				{
					cK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Battle Cruiser")
				{
					bcK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Battleship")
				{
					bK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Mothership")
				{
					mK += 1;
				}

				else if (mNPC.eWingmen.at(i).Ship.getSClass() == "Titan")
				{
					tK += 1;
				}
			}

			else if (mNPC.eWingmen.at(i).getStatus() == "Surrendered")
			{
				//Set Rewards
				mNPC.eWingmen.at(i).initRewards();

				rX += (mNPC.eWingmen.at(i).getXarn()) * 2;
				rR += (mNPC.eWingmen.at(i).getRubies()) * 2;
				rDi += (mNPC.eWingmen.at(i).getDia()) * 2;
				rD += (mNPC.eWingmen.at(i).getDrac()) * 2;
				rL += (mNPC.eWingmen.at(i).getLith()) * 2;
				rPl += (mNPC.eWingmen.at(i).getPlat()) * 2;
				rU += (mNPC.eWingmen.at(i).getUra()) * 2;
				rP += (mNPC.eWingmen.at(i).getPlut()) * 2;
				rNW += (mNPC.eWingmen.at(i).getNWaste()) * 2;
				rCXP += mNPC.eWingmen.at(i).getCXPReward();
			}
		}


		mp.bRewards(mPlayer, rX, rR, rDi, rD, rL, rPl, rU, rP, rNW, rCXP, fK, dK, cK, bcK, bK, mK, tK, false);

		//Add rewards to player
		mPlayer.updateXarn(rX, "add");
		mPlayer.updateRubies(rR, "add");
		mPlayer.updateDia(rDi, "add");
		mPlayer.updateDrac(rD, "add");
		mPlayer.updateLith(rL, "add");
		mPlayer.updatePlat(rPl, "add");
		mPlayer.updateUra(rU, "add");
		mPlayer.updatePlut(rP, "add");
		mPlayer.updateNWaste(rNW, "add");
		mPlayer.updateFKills(fK, "add");
		mPlayer.updateDKills(dK, "add");
		mPlayer.updateCKills(cK, "add");
		mPlayer.updateBCKills(bcK, "add");
		mPlayer.updateBKills(bK, "add");
		mPlayer.updateMKills(mK, "add");
		mPlayer.updateTKills(tK, "add");

		//TODO: cut exp by number of ally ships remaining
		mPlayer.updateCEXP(rCXP, "add");

		resetRewards();
	}

	else
	{
		cout << "No rewards" << endl;
		mp.mCScreen(true);
	}
}

void battleProc::endBattle_PB(Player& mPlayer, Planet* gPlanet)
{
	if ((!bDPEscape) && (mPlayer.getStatus() != "Surrendered" || mPlayer.getStatus() != "Captured"))
	{		
		if (gPlanet->pDef.size() > 0)
		{
			for (i = 0; i < gPlanet->pDef.size(); i++)
			{	
				if (gPlanet->pDef.at(i).getSPoints() <= 0.0f) //Only process rewards for defenses that were destroyed; to handle planets surrendering before battle is actually done
				{
					rCXP += gPlanet->pDef.at(i).getDCXP();
				}
			}
		}

		gPlanet->pillagePlanet(&rX, &rR, &rDi, &rD, &rL, &rPl, &rU, &rP, &rNW); //Get resource rewards from planet; will always be pillaged in 0.5A, in 6A will implement the player planet owning system and more options will be added here
	}

	mp.bRewards(mPlayer, rX, rR, rDi, rD, rL, rPl, rU, rP, rNW, rCXP, fK, dK, cK, bcK, bK, mK, tK, true);

	//Add rewards to player
	mPlayer.updateXarn(rX, "add");
	mPlayer.updateRubies(rR, "add");
	mPlayer.updateDia(rDi, "add");
	mPlayer.updateDrac(rD, "add");
	mPlayer.updateLith(rL, "add");
	mPlayer.updatePlat(rPl, "add");
	mPlayer.updateUra(rU, "add");
	mPlayer.updatePlut(rP, "add");
	mPlayer.updateNWaste(rNW, "add");

	//TODO: cut exp by number of ally ships remaining
	mPlayer.updateCEXP(rCXP, "add");

	resetRewards();
}

void battleProc::resetRewards()
{
	rX = 0; //Xarn
	rR = 0; //Rubies
	rDi = 0; //Diamonds
	rD = 0; //Draconic
	rL = 0; //Lithium
	rPl = 0; //Platinum
	rU  = 0; //Uranium
	rP = 0; //Plutonium
	rNW = 0; //Nuclear Waste
	rCXP = 0; //CEXP

	fK = 0;
	dK = 0;
	cK = 0;
	bcK = 0;
	bK = 0;
	mK = 0;
	tK = 0;
}

void battleProc::bInit(Player& mPlayer, NPC& mNPC)
{
	//NPC Initialization
	if (mPlayer.getRank() == "Private")
	{
		initHR1(mNPC); //initialize hostile as rank 1 hostile (frigate)
	}

	else if (mPlayer.getRank() == "Private First Class")
	{
		initHR2(mNPC); //initialize hostile as rank 2 hostile (frigate-destroyer)
	}

	else if (mPlayer.getRank() == "Sub-Lieutenant")
	{
		initHR3(mNPC); //initialize hostile as rank 3 hostile (frigate-destroyer w/ stronger weapons)
	}

	else if (mPlayer.getRank() == "Lieutenant")
	{
		initHR4(mNPC); //initialize hostile as rank 4 hostile (frigate-crusier)
	}

	else if (mPlayer.getRank() == "Lieutenant-Commander")
	{
		initHR5(mNPC);
	}

	else if (mPlayer.getRank() == "Commander")
	{
		initHR6(mNPC);
	}

	else if (mPlayer.getRank() == "Captain")
	{
		initHR7(mNPC);
	}

	else if (mPlayer.getRank() == "Commodore")
	{
		initHR8(mNPC);
	}

	else if (mPlayer.getRank() == "Admiral")
	{
		initHR9(mPlayer, mNPC);
	}
}


/*

NPC initilization:

Initilization will be based on player rank.  Player's of a certain rank will
only make certain ships available to the enemy.  Example:

Player Rank is Private, hostile ships will not exceed frigate nor weapons ranging from id's 0 to 6.

This is to promote a more balanced game based on player progression, similarly to how RPG's ease you into tougher areas.

Difficulty Progressions:

Rank 1:
Frigates only, weapon's 1-5 unlocked.


Rank 2:
Frigats to destroyers, weapons 1-10 unlocked.


Rank 3:
Frigats to destroyers, weapons 1-15 unlocked.


Rank 4:
Frigates to destroyers, weapons 1-28 unlocked.


Rank 5:
Frigates to cruisers, weapons 1-28 unlocked.


Rank 6:
Frigats to battlecruisers, weapons 1-38 unlocked.


Rank 7:
Frigates to battleships, weapons 1-50 unlocked.


Rank 8:
Frigates to motShips, weapons 1-55 unlocked.


Rank 9:
All ships, all weapons unlocked.


More variation may be forthcoming with more ranks, ships, and weaponry and are subject to change.
*/


//TODO: Add bool checks to iWeapon in initHR's to check to make sure the weapon was actually installed.

void battleProc::initHR1(NPC& mNPC)
{
	for (i = 0; i <= hostiles; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,5); //Ship
		rkCode = 1; //Rank	
		
		if (i == 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon Initialization

			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,5);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,36);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.push_back(NPC()); //Create an element for each hostile entity over 0 in the for loop
			mNPC.eWingmen.at(i-1).hSetup(rkCode, rCode, sCode); //Set up this hostile entity
			
			//Weapon Initialization
			
			//Lasers
			banks = mNPC.eWingmen.at(i-1).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,5);
					mNPC.eWingmen.at(i-1).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i-1).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,36);
					mNPC.eWingmen.at(i-1).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i-1).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.eWingmen.at(i-1).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR2(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,10); //Ship
		rkCode = Random(1,2); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,10);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,38);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,10);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,38);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR3(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,10); //Ship
		rkCode = Random(1,3); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,13);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,42);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,10);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,42);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,107);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR4(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,10); //Ship
		rkCode = Random(1,4); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,13);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,44);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,110);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,13);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,44);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,110);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR5(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,16); //Ship
		rkCode = Random(1,5); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,18);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,50);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,113);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,18);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,50);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,113);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR6(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,21); //Ship
		rkCode = Random(1,6); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,21);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,55);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,117);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,21);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,55);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,117);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR7(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,26); //Ship
		rkCode = Random(1, 7); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,25);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,65);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,121);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,25);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,65);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,121);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR8(NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race
		sCode = Random(1,35); //Ship
		rkCode = Random(1,8); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,27);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,87);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,113);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,27);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,87);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,113);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::initHR9(Player& mPlayer, NPC& mNPC)
{
	for (i = 0; i <= hostiles - 1; i++)
	{
		//NPC init
		rCode = Random(1,7); //Race

		if (mPlayer.Ship.getSClass() == "Titan")
		{
			sCode = Random(1,43); //Ship	
		}

		else
		{
			sCode = Random(1,35);
		}

			rkCode = Random(1,9); //Rank	
		
		if (i = 0)
		{
			mNPC.hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,18);
					mNPC.Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,101);
					mNPC.Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,125);

					mNPC.Ship.iWeapon("bomb", wCode);
				}
			}
		}

		else
		{
			mNPC.eWingmen.at(i).hSetup(rkCode, rCode, sCode);		
			
			//Weapon init


			//Lasers
			banks = mNPC.eWingmen.at(i).Ship.getLHP(); //get number of possible laser banks

			if (banks != 0)
			{
				iBanks = Random(1,banks); //set a random number between 1 and max number of l. banks for use

				for (i2 = 0; i2 <= iBanks - 1; i2++)
				{
					wCode = Random(1,30);
					mNPC.eWingmen.at(i).Ship.iWeapon("laser", wCode);
				}
			}

			//Missiles
			turrets = mNPC.eWingmen.at(i).Ship.getMTP();

			if (turrets != 0)
			{
				iTurrets = Random(1,turrets); //set a random number between 1 and max number of m. turrets for use

				for (i2 = 0; i2 <= iTurrets - 1; i2++)
				{
					wCode = Random(32,101);
					mNPC.eWingmen.at(i).Ship.iWeapon("missile", wCode);
				}
			}

			//Bombs
			bombs = mNPC.eWingmen.at(i).Ship.getBH();

			if (bombs != 0)
			{
				iBombs = Random(1,bombs); //set a random number between 1 and max number of b. holds for use

				for (i2 = 0; i2<= iBombs - 1; i2++)
				{

					wCode = Random(103,125);

					mNPC.eWingmen.at(i).Ship.iWeapon("bomb", wCode);
				}
			}
		}
	}
}

void battleProc::bAParticipants(Player& mPlayer, NPC& mNPC)
{
	bPParticipants = allies;
	bHParticipants = hostiles;

	//Add player/hostile entities to vector
	for (i2 = -1; i2 < bPParticipants; i2++)
	{
		if (i2 == -1) //If i is 0 add the main player to the vector
		{
			battleParticipants.push_back(bParticipants(mPlayer.getName(),mPlayer.Ship.getMInit()));
		}

		else if (mPlayer.getNOWingmen() > 0) //Do the same as above only for non-player entities on the player's side
		{
			battleParticipants.push_back(bParticipants(mPlayer.eWingmen.at(i2).getName(),mPlayer.eWingmen.at(i2).Ship.getMInit()));
		}
	}
		
	//Add hostiles to vector
	for (i2 = -1; i2 < bHParticipants; i2++)
	{
		if (i2 == -1) //If i is 0 add the main hostile to the vector
		{				
			battleParticipants.push_back(bParticipants(mNPC.getName(),mNPC.Ship.getMInit()));
			mNPC.setStatus("In Battle");
		}
		
		else if (mNPC.getNOWingmen() > 0) //Do the same as above only for non-leader entities on the enemy's side
		{
			battleParticipants.push_back(bParticipants(mNPC.eWingmen.at(i2).getName(),mNPC.eWingmen.at(i2).Ship.getMInit()));
			mNPC.eWingmen.at(i2).setStatus("In Battle");
		}
	}

	//Bubble sort to arrange entities in order of highest movement initiative
	for (i2 = 0; i2 < battleParticipants.size(); i2++)
	{
		for ( i3 = 0; i3 < battleParticipants.size()-1; i3++)
			{
				if (battleParticipants.at(i3).getInit() < battleParticipants.at(i3+1).getInit())
				{
					//store elements
					storage1 = battleParticipants.at(i3);
					storage2 = battleParticipants.at(i3+1);

					//swap elements
					battleParticipants.at(i3) = storage2;
					battleParticipants.at(i3+1) = storage1;
				}
			}
		}
	}

void battleProc::bAParticipants_PB(Player& mPlayer, Planet* gPlanet)
{	
	bPParticipants = allies;
	bHParticipants = hostiles;

	//Add player/hostile entities to vector
	for (i2 = -1; i2 < bPParticipants; i2++)
	{
		if (i2 == -1) //If i is 0 add the main player to the vector
		{
			battleParticipants.push_back(bParticipants(mPlayer.getName(),mPlayer.Ship.getMInit()));
		}
		
		else if (mPlayer.getNOWingmen() > 0) //So long as there are player entities continue
		{
			//Do the same as above only for non-player entities on the player's side
			battleParticipants.push_back(bParticipants(mPlayer.eWingmen.at(i2).getName(),mPlayer.eWingmen.at(i2).Ship.getMInit()));			
		}
	}

	if (bHParticipants > 0)//So long as there are hostile entities continue
	{	
		for (i2 = 0; i2 < bHParticipants; i2++)
		{
			/*if (i == 0) //If i is 0 add the main hostile to the vector
			{				
				battleParticipants.push_back(bParticipants(mNPC.getName(),mNPC.Ship.getMInit()));
				bHParticipants -= 1; //Remove a counter from this variable to signify that a hostile entity has been added to the pool		
			}

			else //Do the same as above only for non-leader entities on the enemy's side
			{
				battleParticipants.push_back(bParticipants(mNPC.eWingmen.at(i).getName(),mNPC.eWingmen.at(i).Ship.getMInit()));
				bHParticipants -= 1;
			}*/
			
			//For now, until something can be added to make the above code work, planetary defenses will always attack last

			battleParticipants.push_back(bParticipants(gPlanet->pDef.at(i2).getDName(), 0));
			
			if (gPlanet->pDef.at(i2).getSPoints() > 0)
			{
				gPlanet->pDef.at(i2).setState("In Battle");
			}
		}
	}

	//Bubble sort to arrange entities in order of highest movement initiative
	if (battleParticipants.size() > 1) //Make sure that there ae more participants than just the player else the sort crashes from out of bounds
	{
		for (i = 0; i < battleParticipants.size(); i++)
		{
			for ( i2 = 0; i2 < battleParticipants.size()-1; i2++)
			{

				if (battleParticipants.at(i2).getInit() < battleParticipants.at(i2+1).getInit())
				{
					//store elements
					storage1 = battleParticipants.at(i2);
					storage2 = battleParticipants.at(i2+1);

					//swap elements
					battleParticipants.at(i2) = storage2;
					battleParticipants.at(i2+1) = storage1;
				}
			}
		}
	}
}

//hostile + player attack functions
//make sure to include someway to track who is being attacked for later use

void battleProc::getPTarget(NPC& mNPC)
{
	cout << mp.mRMessage(26) << endl;
	
	//Show hostile team status
	pTarget = mp.hBStatus(mNPC, hostiles);
}

void battleProc::getPTarget_PB(Planet* gPlanet)
{
	cout << mp.mRMessage(26) << endl;
	
	//Show hostile team status
	pBPDTarget = mp.hBStatus_PB(gPlanet);
}

void battleProc::bPFSolutions(int bPChoice, Player& mPlayer, NPC& mNPC)
{
	switch(bPChoice)
	{
	case 1:
		allout = true;
		spread = false;
		wsystem = false;
		single = false;

		if (mPlayer.Ship.bAWInstalled())
		{
			d.setupAType(allout, spread, wsystem, single); //Always call this function first

			mPlayer.Ship.sSAVector(false);
			
			if (pTarget == 0) //If player target is the leader on the hostile side go directly from mNPC
			{
				d.setupBAT(mPlayer.rEntity(),mNPC.rEntity());
				break;
			}

			else //Else if the player target is one of the enemy wingmen, grab the data from the respective winman in the eWingmen vector
			{
				d.setupBAT(mPlayer.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity()); //This function starts the damage processing
				break;
			}
		}

		else
		{
			cout << "Cannot attack..." << endl;
			break;
		}

	case 2:

		allout = false;
		spread = true;
		wsystem = false;
		single = false;

		d.setupAType(allout, spread, wsystem, single); //Always call this function first

		pChoice = mp.bCSpread(mPlayer.Ship.getSWSpreads(), mPlayer);

		if (pChoice >= 0)
		{
			if (pChoice == 0)
			{
				mPlayer.Ship.cRSpread();
			}

			else 
			{
				mPlayer.Ship.setCWSpread(pChoice);
			}
		
			
			if (pTarget == 0) //If player target is the leader on the hostile side go directly from mNPC
			{
				d.setupBAT(mPlayer.rEntity(),mNPC.rEntity());
				break;
			}

			else //Else if the player target is one of the enemy wingmen, grab the data from the respective winman in the eWingmen vector
			{
				d.setupBAT(mPlayer.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity()); //This function starts the damage processing
				break;
			}
		}

		else if (pChoice == -1)
		{
			cout << "Cannot attack..." << endl;
			break;
		}

	case 3:
		pChoice = mp.bCWSystem(mPlayer);

		if (pChoice == -1)
		{
			cout << "Cannot attack..." << endl;
			break;
		}

		else
		{
			mPlayer.Ship.setCWSystem(pChoice);

			allout = false;
			spread = false;
			wsystem = true;
			single = false;

			d.setupAType(allout, spread, wsystem, single); //Always call this function first

			if (pTarget == 0) //If player target is the leader on the hostile side go directly from mNPC
			{
				d.setupBAT(mPlayer.rEntity(),mNPC.rEntity());
				break;
			}

			else //Else if the player target is one of the enemy wingmen, grab the data from the respective winman in the eWingmen vector
			{
				d.setupBAT(mPlayer.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity()); //This function starts the damage processing
				break;
			}
		}

	case 4:
		

		allout = false;
		spread = false;
		wsystem = false;
		single = true;

		d.setupAType(allout, spread, wsystem, single); //Always call this function first
		
		pChoice = mp.bCWeapon(mPlayer, &wtype);

		if (pChoice == -1)
		{
			cout << "Cannot attack..." << endl;
			break;
		}

		else
		{
			mPlayer.Ship.cSWArray(pChoice, wtype);
			
			if (pTarget == 0) //If player target is the leader on the hostile side go directly from mNPC
			{
				d.setupBAT(mPlayer.rEntity(),mNPC.rEntity());
				break;
			}

			else //Else if the player target is one of the enemy wingmen, grab the data from the respective winman in the eWingmen vector
			{
				d.setupBAT(mPlayer.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity()); //This function starts the damage processing
				break;
			}
		}
	}
}

void battleProc::bPFSolutions_PB(int bPChoice, Player& mPlayer, Planet* gPlanet, bool shield, bool defense, bool planet)
{
	switch(bPChoice)
	{
	case 1:
		allout = true;
		spread = false;
		wsystem = false;
		single = false;

		if (mPlayer.Ship.bAWInstalled())
		{
			d.setupAType(allout, spread, wsystem, single); //Always call this function first

			if (shield)
			{			
				mPlayer.Ship.sSAVector(false);
				d.setupBAT_PS(mPlayer.rEntity(),gPlanet->pShd.at(pBPSTarget).rShield(), gPlanet);
				break;
			}

			else if (defense)
			{
				mPlayer.Ship.sSAVector(false);
				d.setupBAT_PDPA(mPlayer.rEntity(), gPlanet->pDef.at(pBPDTarget).rDefense(), gPlanet); //This function starts the damage processing
				break;
			}

			else if (planet)
			{
				mPlayer.Ship.sSAVector(true);
				d.setupBAT_PB(mPlayer.rEntity(), gPlanet); //This function starts the damage processing
				break;			
			}
		}

		else
		{
			cout << "Cannot attack..." << endl;
			break;
		}

	case 2:
		
		allout = false;
		spread = true;
		wsystem = false;
		single = false;		

		d.setupAType(allout, spread, wsystem, single); //Always call this function first
		
		if (shield)
		{			
			pChoice = mp.bCSpread(mPlayer.Ship.getSWSpreads(), mPlayer);

			if (pChoice >= 0)
			{
				if (pChoice == 0)
				{
					mPlayer.Ship.cRSpread();
				}

				else 
				{
					mPlayer.Ship.setCWSpread(pChoice);
				}

				d.setupBAT_PS(mPlayer.rEntity(),gPlanet->pShd.at(pBPSTarget).rShield(), gPlanet);
				break;
			}

			else if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
				break;
			}
		}

		else if (defense)
		{
			pChoice = mp.bCSpread(mPlayer.Ship.getSWSpreads(), mPlayer);
			
			if (pChoice >= 0)
			{
				if (pChoice == 0)
				{
					mPlayer.Ship.cRSpread();
				}

				else 
				{
					mPlayer.Ship.setCWSpread(pChoice);
				}

				d.setupBAT_PDPA(mPlayer.rEntity(), gPlanet->pDef.at(pBPDTarget).rDefense(), gPlanet); //This function starts the damage processing
				break;
			}

			else if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
				break;
			}
		}

		else if (planet)
		{
			pChoice = mp.bCSpread(mPlayer.Ship.getSWSpreads(), mPlayer);
			
			if (pChoice >= 0)
			{
				if (pChoice == 0)
				{
					mPlayer.Ship.cRSpread_B();
				}

				else 
				{
					mPlayer.Ship.setCWSpread(pChoice);
				}
				
				d.setupBAT_PB(mPlayer.rEntity(), gPlanet); //This function starts the damage processing
				break;
			}

			else if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
				break;		
			}
		}

	case 3:
		
		allout = false;
		spread = false;
		wsystem = true;
		single = false;
		d.setupAType(allout, spread, wsystem, single); //Always call this function first
		
		if (shield)
		{			
			pChoice = mp.bCWSystem(mPlayer);
			
			if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
			}

			else
			{
				mPlayer.Ship.setCWSystem(pChoice);

				d.setupBAT_PS(mPlayer.rEntity(),gPlanet->pShd.at(pBPSTarget).rShield(), gPlanet);
			}
			
			break;
		}

		else if (defense)
		{
			pChoice = mp.bCWSystem(mPlayer);
			
			if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
			}

			else
			{
				mPlayer.Ship.setCWSystem(pChoice);

				d.setupBAT_PDPA(mPlayer.rEntity(), gPlanet->pDef.at(pBPDTarget).rDefense(), gPlanet); //This function starts the damage processing
			}
			
			break;
		}

		else if (planet)
		{
			if (mPlayer.Ship.bABInstalled())
			{
				pChoice = 3;
				mPlayer.Ship.setCWSystem(pChoice);

				d.setupBAT_PB(mPlayer.rEntity(), gPlanet); //This function starts the damage processing
			}

			else
			{
				cout << "Cannot attack..." << endl;
			}

			break;			
		}

	case 4:
		
		allout = false;
		spread = false;
		wsystem = false;
		single = true;

		d.setupAType(allout, spread, wsystem, single); //Always call this function first
		
		if (shield)
		{			
			pChoice = mp.bCWeapon(mPlayer, &wtype);

			if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
			}

			else
			{
				mPlayer.Ship.cSWArray(pChoice, wtype);
				d.setupBAT_PS(mPlayer.rEntity(),gPlanet->pShd.at(pBPSTarget).rShield(), gPlanet);
			}

			break;
		}

		else if (defense)
		{
			pChoice = mp.bCWeapon(mPlayer, &wtype);
			
			if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
			}

			else
			{
				mPlayer.Ship.cSWArray(pChoice, wtype);
				d.setupBAT_PDPA(mPlayer.rEntity(), gPlanet->pDef.at(pBPDTarget).rDefense(), gPlanet); //This function starts the damage processing
			}
			break;
		}

		else if (planet)
		{
			pChoice = mp.bCBomb(mPlayer, &wtype);

			if (pChoice == -1)
			{
				cout << "Cannot attack..." << endl;
			}

			else
			{
				mPlayer.Ship.cSWArray(pChoice, wtype);
				d.setupBAT_PB(mPlayer.rEntity(), gPlanet); //This function starts the damage processing
			}

			break;			
		}
	}
}

//Comment out for now, not used anymore but might need in future

/*void battleProc::bAIFSolutions(NPC& tNPC, Player& tPlayer)
{
	d.setupAType(allout, spread, wsystem, single); //Always call this function first

	d.setupBAT(tPlayer.rEntity(), tNPC.rEntity()); //This function starts the damage processing
}*/

void battleProc::bPHail(string race, string affiliation, Player& mPlayer)
{
	//Check to see if this target's affiliation has made contact with player before
	tAffinity = mPlayer.getRStatus(affiliation);
	
	//get hail response from message proc
	mp.bHail1(affiliation, race, tAffinity);

	if (bTResponded)
	{
		pChoice = mp.bHail2(tAffinity);

		switch (pChoice)
		{
		case 1:
			mp.bHInfo(tAffinity,race);
			bITNHostile = true;
			break;

		case 2:
			mp.bHEnemies(race);
			bITNHostile = true;
			break;

		case 3:
			mp.bHSurrender(tAffinity,race);
			bDTSurrender = false;
			break;

		case 4:
			//pChoice2 = mp.bHTrade();
			//Start trade dialog; created class, start from there after stations re-added
			cout << mp.mRMessage(2001) << endl; //Temp until 0.6A
			break;

		case 5:
			mp.bHNothing();
			bITNHostile = true;
			break;

		default:
			mp.bHInfo(tAffinity,race);
			bITNHostile = true;
			break;
		}
	}
	
	else
	{
		cout << mp.mRMessage(2000) << endl;
		bITNHostile = true;
	}
	
	//response = hResponse
}

bool battleProc::bRetreat()
{
	bRChance = Random(1,100);

	//TODO: When modules are added figure out a way to incorporate ECM and warp blockers in determination for escape

	if ((bRChance >= 1) && (bRChance <= 15)) //Retreat Fails
	{
		return false;
	}

	else if ((bRChance >= 16) && (bRChance <= 36)) //Retreat Succeeds
	{
		bDPEscape = true;
		return true;
	}

	else if ((bRChance >= 37) && (bRChance <= 75)) //Retreat Fails
	{
		return false;
	}

	else if (bRChance >= 76) //Retreat Succeeds
	{
		bDPEscape = true;
		return true;
	}
}

void battleProc::aiHTasks(NPC& cNAttacker, Player& mPlayer)
{	
	bAITask1 = Random(1,40);

	//TODO: Currently everything is 25% chance of occuring, later on in 0.6 or 0.7 differentiate these based on difficulty

	if ((bAITask1 >= 1) && (bAITask1 <= 10)) //Attack
	{
		bAITask2 = Random(1,100);

		//45% Chance for single weapon
		if ((bAITask2 >= 1) && (bAITask2 <= 45))
		{
			cNAttacker.Ship.cWVector_AI();

			d.setupAType(false, false, false, true);

			if (hTarget == 0)
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.rEntity());
			}
			
			else
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.eWingmen.at(hTarget-1).rEntity());
			}
		}

		//25% Chance for single weapon system
		else if ((bAITask2 >= 46) && (bAITask2 <=70))
		{
			cNAttacker.Ship.cWSVector_AI();
			
			d.setupAType(false, false, true, false);
			
			if (hTarget == 0)
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.rEntity());
			}
			
			else
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.eWingmen.at(hTarget-1).rEntity());
			}
		}

		//17% Chance for weapon spread
		else if ((bAITask2 >= 71) && (bAITask2 <= 88))
		{
			cNAttacker.Ship.cRSpread();

			d.setupAType(false, true, false, false);
			
			if (hTarget == 0)
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.rEntity());
			}
			
			else
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.eWingmen.at(hTarget-1).rEntity());
			}
		}

		//12% Chance for all weapons
		else if ((bAITask2 >= 89) && (bAITask2 <= 100))
		{
			cNAttacker.Ship.sSAVector(false);

			d.setupAType(true, false, false, false);
			
			if (hTarget == 0)
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.rEntity());
			}
			
			else
			{
				d.setupBAT(cNAttacker.rEntity(), mPlayer.eWingmen.at(hTarget-1).rEntity());
			}
		}
	}

	else if ((bAITask1 >= 11) && (bAITask1 <=20)) //Hail
	{
		if (hTarget == 0)
		{
			bHPPerc1 = (cNAttacker.Ship.getSHull() / cNAttacker.Ship.getSMHull()) * 100;
			bHPPerc2 = (mPlayer.Ship.getSHull() / mPlayer.Ship.getSMHull()) * 100;

			if ((bHPPerc1 > 75.00) && ((bHPPerc2 <= 35.00) && (bHPPerc2 > 0.00))) //Demand surrender if conditions are met
			{
				cout << mp.mRMessage(2002) << endl;

				if (mp.bNHail1())
				{
					if (mp.bNHDemand())
					{
						bAITask2 = Random(1,90);

						if ((bAITask2 >= 1) && (bAITask2 <= 45)) //45% chance; ship is looted, use escape shuttle/pods and arrive at a nearby station
						{
							//TODO: finish after adding stations back in
						}

						else if ((bAITask2 >= 46) && (bAITask2 <= 83)) //37% chance; get sold into slavery
						{
							//TODO: Figure out how to do this
							mPlayer.Ship.clearSData(); //Remove all ship data
							mPlayer.setStatus("Surrendered");

							bAITask3 = Random(1,25);

							if (((bAITask3 >= 2) && (bAITask3 <= 8)) || ((bAITask3 >= 19) && (bAITask3 <= 24)))
							{
								//TODO: Send to nearest station & give some resources
							}

							else
							{
								mPlayer.setStatus("Captured");
							}
						}

						else if ((bAITask2 >= 84) && (bAITask2 <= 100)) //16% chance; pay a ransom and be free to go
						{
							bAITask3 = Random (1,9);

							for (i2 = 0; i2 < bAITask3; i2++)
							{
								while (false)
								{									
									bAITask4 = Random(0,8);

									if (rArray[bAITask4] == 0)
									{
										rArray[bAITask4] = Random(100,10000);
										break;
									}
								}
							}

							pChoice = mp.bPSurrender(rArray);

							if (pChoice = 1)
							{
								for (i2 = 0; i2 < 9; i2++)
								{
									if (rArray[i2] != 0)
									{
										switch(i2)
										{
										case 0:
											mPlayer.updateXarn(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 1:
											mPlayer.updateRubies(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 2:
											mPlayer.updateDia(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 3:
											mPlayer.updateDrac(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 4:
											mPlayer.updateLith(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 5:
											mPlayer.updatePlat(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 6:
											mPlayer.updateUra(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 7:
											mPlayer.updatePlut(rArray[i2],"sub");
											rArray[i2] = 0;
											break;

										case 8:
											mPlayer.updateNWaste(rArray[i2],"sub");
											rArray[i2] = 0;
											break;
										}
									}
								}
							}

							else
							{
								mPlayer.setStatus("Captured");
							}
						}
					}
				}									
			}
			
			else if ((bHPPerc1 < 15.00) && (bHPPerc2 >= 30.00)) //Surrender to enemies if conditions and subconditions are met
			{
				bAITask3 = Random(1,10);
				bAITask4 = Random(1,10);
				bAITask5 = Random(1,10);

				if ((bAITask3 > 6) && (bAITask4 > 7) && (bAITask5 > 4)) //If values coincide to these conditions, surrender
				{
					cout << mp.mRMessage(2002) << endl;

					if (mp.bNHSurrender()) //If player answered hail and accepted
					{
						cNAttacker.setStatus("Surrendered");
						//TODO: Add code for player to decide what to do with surrendered ships; in rewards section
					}
				}
			}				
		}
	}

	else if ((bAITask1 >= 21) && (bAITask1 <= 30)) //Move
	{
		if (hTarget == 0)
		{
			cNAttacker.Ship.sAIMove(mPlayer, cNAttacker, false);
		}

		else
		{
			cNAttacker.Ship.sAIMove(mPlayer.eWingmen.at(hTarget-1), cNAttacker, false);
		}
	}

	else if ((bAITask1 >= 31) && (bAITask1 <= 40)) //Retreat
	{
		bHPPerc1 = (cNAttacker.Ship.getSHull() / cNAttacker.Ship.getSMHull()) * 100;

		if ((bHPPerc1 < 15.00) && (bHPPerc2 >= 30.00)) //Surrender to enemies if conditions and subconditions are met
		{
			bAITask3 = Random(1,30);
			bAITask4 = Random(1,25);
			bAITask5 = Random(1,40);

			if ((bAITask3 > 26) && (bAITask4 > 19) && (bAITask5 > 32)) //If values coincide to these conditions, attempt to retreat
			{
				if (bRetreat())
				{
					cNAttacker.setStatus("Retreated");
				}
			}
		}
	}
}

void battleProc::aiHTasks_PB(Defense& pDefense, Player& mPlayer)
{	
	bAITask1 = Random(1,20);

	//TODO: Currently everything is 25% chance of occuring, later on in 0.6 or 0.7 differentiate these based on difficulty

	if ((bAITask1 >= 1) && (bAITask1 <= 15)) //Attack
	{ 
		//Modified due to defense-only attacking; in 0.6A will switch back and use flags for determining between this and the defenders code
		bAITask2 = Random(1,80);

		//45% Chance for attack
		if ((bAITask2 >= 1) && (bAITask2 <= 45))
		{
			d.setupAType(false, false, false, true);
			d.setupBAT_PDDA(pDefense.rDefense(), mPlayer.rEntity());
		}

		//25% Chance for miss
		else if ((bAITask2 >= 46) && (bAITask2 <=70))
		{
			mp.bEMiss_PD(pDefense);
		}
	}
	
	else if ((bAITask1 >= 16) && (bAITask1 <=20)) //Hail
	{
		cout << "Debug: planet battle hail chosen by bAITask1" << endl;
		/*if (hTarget.getName() == mPlayer.getName())
		{
			bHPPerc1 = (pDefense.getSPoints() / pDefense.getMSPoints()) * 100;
			bHPPerc2 = (hTarget.Ship.getSHull() / hTarget.Ship.getSMHull()) * 100;

			if ((bHPPerc1 > 75.00) && ((bHPPerc2 <= 35.00) && (bHPPerc2 > 0.00))) //Demand surrender if conditions are met
			{
				cout << mp.mRMessage(2002) << endl;

				if (mp.bNHail1())
				{
					if (mp.bNHDemand())
					{
						bAITask2 = Random(1,90);

						if ((bAITask2 >= 1) && (bAITask2 <= 45)) //45% chance; ship is looted, use escape shuttle/pods and arrive at a nearby station
						{
							//TODO: finish after adding stations back in
						}

						else if ((bAITask2 >= 46) && (bAITask2 <= 83)) //37% chance; get sold into slavery
						{
							//TODO: Figure out how to do this
							mPlayer.Ship.clearSData(); //Remove all ship data
							mPlayer.setStatus("Surrendered");

							bAITask3 = Random(1,25);

							if (((bAITask3 >= 2) && (bAITask3 <= 8)) || ((bAITask3 >= 19) && (bAITask3 <= 24)))
							{
								//TODO: Send to nearest station & give some resources
							}

							else
							{
								mPlayer.setStatus("Captured");
							}
						}

						else if ((bAITask2 >= 84) && (bAITask2 <= 100)) //16% chance; pay a ransom and be free to go
						{
							bAITask3 = Random (1,9);

							for (i = 0; i < bAITask3; i++)
							{
								while (false)
								{									
									bAITask4 = Random(0,8);

									if (rArray[bAITask4] == 0)
									{
										rArray[bAITask4] = Random(100,10000);
										break;
									}
								}
							}

							pChoice = mp.bPSurrender(rArray);

							if (pChoice = 1)
							{
								for (i = 0; i < 9; i++)
								{
									if (rArray[i] != 0)
									{
										switch(i)
										{
										case 0:
											mPlayer.updateXarn(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 1:
											mPlayer.updateRubies(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 2:
											mPlayer.updateDia(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 3:
											mPlayer.updateDrac(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 4:
											mPlayer.updateLith(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 5:
											mPlayer.updatePlat(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 6:
											mPlayer.updateUra(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 7:
											mPlayer.updatePlut(rArray[i],"sub");
											rArray[i] = 0;
											break;

										case 8:
											mPlayer.updateNWaste(rArray[i],"sub");
											rArray[i] = 0;
											break;
										}
									}
								}
							}

							else
							{
								mPlayer.setStatus("Captured");
							}
						}
					}
				}									
			}*/
		//}
	}
}


void battleProc::aiATasks(Player& cAAttacker, NPC& mNPC)
{
	bAITask1 = Random(1,40);

	//TODO: Currently everything is 25% chance of occuring, later on in 0.6 or 0.7 differentiate these based on difficulty

	if ((bAITask1 >= 1) && (bAITask1 <= 10)) //Attack
	{
		bAITask2 = Random(1,100);

		//45% Chance for single weapon
		if ((bAITask2 >= 1) && (bAITask2 <= 45))
		{
			cAAttacker.Ship.cWVector_AI();

			d.setupAType(false, false, false, true);

			if (pTarget == 0)
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.rEntity());			
			}

			else
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity());
			}
		}

		//25% Chance for single weapon system
		else if ((bAITask2 >= 46) && (bAITask2 <=70))
		{
			cAAttacker.Ship.cWSVector_AI();

			d.setupAType(false, false, true, false);
			
			if (pTarget == 0)
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.rEntity());			
			}

			else
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity());
			}
		}

		//17% Chance for weapon spread
		else if ((bAITask2 >= 71) && (bAITask2 <= 88))
		{
			cAAttacker.Ship.cRSpread();

			d.setupAType(false, true, false, false);
			
			if (pTarget == 0)
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.rEntity());			
			}

			else
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity());
			}
		}

		//12% Chance for all weapons
		else if ((bAITask2 >= 89) && (bAITask2 <= 100))
		{
			cAAttacker.Ship.sSAVector(false);

			d.setupAType(true, false, false, false);
			
			if (pTarget == 0)
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.rEntity());			
			}

			else
			{
				d.setupBAT(cAAttacker.rEntity(), mNPC.eWingmen.at(pTarget-1).rEntity());
			}
		}
	}		

	else if ((bAITask1 >= 21) && (bAITask1 <= 30)) //Move
	{
		if (pTarget == 0)
		{
			cAAttacker.Ship.sAIMove(cAAttacker, mNPC, true);
		}

		else
		{
			cAAttacker.Ship.sAIMove(cAAttacker, mNPC.eWingmen.at(pTarget-1), true);
		}
	}

	else if ((bAITask1 >= 31) && (bAITask1 <= 40)) //Retreat
	{
		bHPPerc1 = (cAAttacker.Ship.getSHull() / cAAttacker.Ship.getSMHull()) * 100;

		if ((bHPPerc1 < 15.00) && (bHPPerc2 >= 30.00)) //Surrender to enemies if conditions and subconditions are met
		{
			bAITask3 = Random(1,30);
			bAITask4 = Random(1,25);
			bAITask5 = Random(1,40);

			if ((bAITask3 > 26) && (bAITask4 > 19) && (bAITask5 > 32)) //If values coincide to these conditions, attempt to retreat
			{
				if (bRetreat())
				{
					cAAttacker.setStatus("Retreated");
				}
			}
		}
	}
}

void battleProc::aiATasks_PB(Player& cAAttacker, Planet* gPlanet, bool shield, bool defense, bool planet)
{
	bAITask1 = Random(1,30);
		
	//TODO: Currently everything is 25% chance of occuring, later on in 0.6 or 0.7 differentiate these based on difficulty

	if ((bAITask1 >= 1) && (bAITask1 <= 10)) //Attack
	{
		bAITask2 = Random(1,100);

		if (shield)
		{
			//45% Chance for single weapon
			if ((bAITask2 >= 1) && (bAITask2 <= 45))
			{
				cAAttacker.Ship.cWVector_AI();

				d.setupAType(false, false, false, true);
				d.setupBAT_PS(cAAttacker.rEntity(), gPlanet->pShd.at(aBPSTarget).rShield(), gPlanet);
			}


			//25% Chance for single weapon system
			else if ((bAITask2 >= 46) && (bAITask2 <=70))
			{
				cAAttacker.Ship.cWSVector_AI();

				d.setupAType(false, false, true, false);
				d.setupBAT_PS(cAAttacker.rEntity(), gPlanet->pShd.at(aBPSTarget).rShield(), gPlanet);
			}

			//17% Chance for weapon spread
			else if ((bAITask2 >= 71) && (bAITask2 <= 88))
			{
				cAAttacker.Ship.cRSpread();

				d.setupAType(false, true, false, false);
				d.setupBAT_PS(cAAttacker.rEntity(), gPlanet->pShd.at(aBPSTarget).rShield(), gPlanet);
			}

			//12% Chance for all weapons
			else if ((bAITask2 >= 89) && (bAITask2 <= 100))
			{
				cAAttacker.Ship.sSAVector(false);

				d.setupAType(true, false, false, false);
				d.setupBAT_PS(cAAttacker.rEntity(), gPlanet->pShd.at(aBPSTarget).rShield(), gPlanet);
			}
		}

		else if (defense)
		{
			//45% Chance for single weapon
			if ((bAITask2 >= 1) && (bAITask2 <= 45))
			{
				cAAttacker.Ship.cWVector_AI();

				d.setupAType(false, false, false, true);
				d.setupBAT_PDPA(cAAttacker.rEntity(), gPlanet->pDef.at(aBPDTarget).rDefense(), gPlanet);
			}


			//25% Chance for single weapon system
			else if ((bAITask2 >= 46) && (bAITask2 <=70))
			{
				cAAttacker.Ship.cWSVector_AI();

				d.setupAType(false, false, true, false);
				d.setupBAT_PDPA(cAAttacker.rEntity(), gPlanet->pDef.at(aBPDTarget).rDefense(), gPlanet);
			}

			//17% Chance for weapon spread
			else if ((bAITask2 >= 71) && (bAITask2 <= 88))
			{
				cAAttacker.Ship.cRSpread();

				d.setupAType(false, true, false, false);
				d.setupBAT_PDPA(cAAttacker.rEntity(), gPlanet->pDef.at(aBPDTarget).rDefense(), gPlanet);
			}

			//12% Chance for all weapons
			else if ((bAITask2 >= 89) && (bAITask2 <= 100))
			{
				cAAttacker.Ship.sSAVector(false);

				d.setupAType(true, false, false, false);
				d.setupBAT_PDPA(cAAttacker.rEntity(), gPlanet->pDef.at(aBPDTarget).rDefense(), gPlanet);
			}

		}

		else if (planet)
		{
			//45% Chance for single weapon
			if ((bAITask2 >= 1) && (bAITask2 <= 45))
			{
				cAAttacker.Ship.cWVector_AI_PB();

				d.setupAType(false, false, false, true);
				d.setupBAT_PB(cAAttacker.rEntity(), gPlanet);
			}


			//25% Chance for single weapon system
			else if ((bAITask2 >= 46) && (bAITask2 <=70))
			{
				cAAttacker.Ship.cWSVector_AI_PB();

				d.setupAType(false, false, true, false);
				d.setupBAT_PB(cAAttacker.rEntity(), gPlanet);
			}

			//17% Chance for weapon spread
			else if ((bAITask2 >= 71) && (bAITask2 <= 88))
			{
				cAAttacker.Ship.cRSpread_B();

				d.setupAType(false, true, false, false);
				d.setupBAT_PB(cAAttacker.rEntity(), gPlanet);
			}

			else if (bAITask2 >= 89)
			{
				cAAttacker.Ship.sSAVector(true);

				d.setupAType(true, false, false, false);
				d.setupBAT_PB(cAAttacker.rEntity(), gPlanet);
			}
		}
	}		

	//Commented out for now until I figure out if this will be needed for planet battle stages besides defenders (which are not implemented yet anyway)

	/*
	else if ((bAITask1 >= 21) && (bAITask1 <= 30)) //Move
	{
	cAAttacker.Ship.sAIMove(cAAttacker, pTarget, true);
	}*/

	else if ((bAITask1 >= 21) && (bAITask1 <= 30)) //Retreat
	{
		bHPPerc1 = (cAAttacker.Ship.getSHull() / cAAttacker.Ship.getSMHull()) * 100;

		if ((bHPPerc1 < 15.00) && (bHPPerc2 >= 30.00)) //Surrender to enemies if conditions and subconditions are met
		{
			bAITask3 = Random(1,30);
			bAITask4 = Random(1,25);
			bAITask5 = Random(1,40);

			if ((bAITask3 > 26) && (bAITask4 > 19) && (bAITask5 > 32)) //If values coincide to these conditions, attempt to retreat
			{
				if (bRetreat())
				{
					cAAttacker.setStatus("Retreated");
				}
			}
		}
	}
}

void battleProc::createBInfo()
{
	file = __FILE__;
	bLocale = "File: " + file + "  Line: ";

	time = __TIME__;
	date = __DATE__;

	bTDate = date + "  " + time;
}