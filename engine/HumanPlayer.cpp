/*Copyright   Feb 1, 2006 Antti Juustila ----------------------

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
http://www.gnu.org/copyleft/gpl.html
---------------------------------------------------------------*/

// HumanPlayer.cpp
//
// $Id: HumanPlayer.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include "HumanPlayer.h"
#include "MobopolyObserver.h"
#include "BuildableProperty.h"

namespace mobopoly 
{

/**
 Default constructor, calls CPlayer constructor.
*/
CHumanPlayer::CHumanPlayer() : CPlayer()
	{	
	}
	
/**
 Destructor, does nothing.
*/
CHumanPlayer::~CHumanPlayer()
	{
	}

/**
 Implementation of the human player's style of taking the turn.
 Resets the flag that user is asked about buying a property, used later.
 Takes the turn object and notifies the user that it's her turn to 
 throw the dices.
 @param aTurn The turn object to take.
*/
void CHumanPlayer::TakeTurnL(CTurn & aTurn)
	{
	iInterestToBuyAsked = EFalse;
	iTurn = &aTurn;
	if (iObserver)
		{
		iObserver->HandleGameEventL(MMobopolyObserver::ETurnToHumanPlayer);
		}
	}

/**
 Human player's implementation of how payment of rent is notified.
 @param aPrice How much was paid.
*/
void CHumanPlayer::NotifyRentPaidL(TInt aPrice)
	{
	if (iObserver)
		{
		iObserver->HandleGameEventL(MMobopolyObserver::EHumanPlayerPaidRent, aPrice);
		}
	}

/**
 Human player's implementation of how property was bought.
 @param aPrice How much was paid.
*/
void CHumanPlayer::NotifyPropertyBoughtL(TInt aPrice)
	{
	if (iObserver)
		{
		iObserver->HandleGameEventL(MMobopolyObserver::EHumanPlayerBought, aPrice);
		}
	}
	
/**
 Template method implementation for human player to buy a property.
 Checks if the user has been notified that the property could be bought.
 If yes, the assumption is that the property is now really bought and
 calls BuyPropertyL and resets the flag about thue user query. Otherwise,
 check if there is enough money to buy the property, then notify the user
 that it's possible to buy. Calls the BuyPropertyL.
 @param aObject The property to buy.
*/
void CHumanPlayer::DoBuyPropertyL(CBuildableProperty & aObject)
	{
	if (!iInterestToBuyAsked)
		{
		if (aObject.Price() <= Money())
			{
			iInterestToBuyAsked = ETrue;
			if (iObserver)
				{
				iObserver->HandleGameEventL(MMobopolyObserver::EPlayerCanBuy);
				}
			}
		}
	else
		{
		iInterestToBuyAsked = EFalse;
		BuyPropertyL(aObject);
		}
	}

} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HumanPlayer.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/