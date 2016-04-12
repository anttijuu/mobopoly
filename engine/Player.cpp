/*Copyright   Jan 27, 2006 Antti Juustila ----------------------

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

// Player.cpp
//
// $Id: Player.cpp,v 1.10 2006/02/15 13:25:36 Antti Exp $

#ifdef _DEBUG
#include <e32svr.h>
#endif 

#include "Player.h"
#include "FreeParking.h"
#include "GoSquare.h"
#include "BuildableProperty.h"
#include "MobopolyObserver.h"
#include "Turn.h"

namespace mobopoly 
{


/**
 Default constructor, calls CBase constructor.
*/
CPlayer::CPlayer() : CBase()
	{
	}

/**
 Destructor, basically does nothing.
*/
CPlayer::~CPlayer()
	{
	}

/**
 Parses the member data values from the descriptor parameter.
 See documentation for the structure of the data.
 Uses TLex for parsing.
 @param aData The player data values in a string.
*/
void CPlayer::ParseL(const TDesC & aData)
	{
	TLex lexer(aData);
	
	TChar chr;
	lexer.SkipSpaceAndMark(); // Skip any whitespace at the beginning
	while (!lexer.Eos())
		{
		chr = lexer.Get();
		if (chr == ',') // items separated by commas
			{
			lexer.UnGet(); // Unget the comma
			TPtrC nextToken = lexer.MarkedToken(); // Get the string
			SetName(nextToken);
			
			lexer.SkipAndMark(1); // Skip over the comma
			TPtrC data = lexer.Remainder();
			TLex numLexer(data);
			TInt tmp;
			if (numLexer.Val(tmp) == KErrNone)
				{
				iMoney = tmp;
				break;
				}
			}
		}	
	if (iName.Length() == 0 || iMoney== 0)
		{
		User::Leave(KErrCorrupt);
		}
	}

/**
 Tells the name of the player.
 @returns Name of the player.
*/
const TDesC & CPlayer::Name() const
	{
	return iName;
	}

/**
 Sets the name of the player.
 @param aName New name for the player.
*/
void CPlayer::SetName(const TDesC & aName)
	{
	iName = aName;
	}

// Money management

/**
 Tells the amount of money the player has.
 @returns Money
*/
TInt CPlayer::Money() const
	{
	return iMoney;
	}

/**
 Deposits a certain amount of money to the player.
 @param aAmount The sum to deposit.
*/	
void CPlayer::Deposit(TInt aAmount)
	{
	iMoney += aAmount;
	}

/**
 Withdraws a certain amount of money from the player.
 @param aAmount The sum to withdraw.
*/	
TInt CPlayer::Withdraw(TInt aAmount)
	{
	iMoney -= aAmount;
	if (iMoney < 0)
		{
		TInt couldWithdraw = aAmount + iMoney;
		return couldWithdraw;
		}
	return aAmount;
	}

// Property management

/**
 Tells the location of the player, const version.
 @returns Property where the player is located now.
*/
const CProperty & CPlayer::MyLocation() const
	{
	return *iMyLocation;
	}

/**
 Tells the location of the player, non const version.
 @returns Property where the player is located now.
*/
CProperty & CPlayer::MyLocation()
	{
	return *iMyLocation;
	}

/**
 Sets the location of the player.
 @param aProperty The property where the will be located.
*/
void CPlayer::SetLocation(CProperty & aProperty)
	{
	iMyLocation = &aProperty;
	}

// Turn management

/**
 Tells if the player has the turn now.
 @returns ETrue if the player has the turn.
*/
TBool CPlayer::IsMyTurn() const
	{
	return (iTurn != 0);
	}

/**
 Gives the turn to the player. Player throws the dices,
 moves and pass the turn to the next player.
 @param aTurn The turn object to take.
*/
void CPlayer::TakeTurnL(CTurn & aTurn)
	{
	iTurn = &aTurn;
	ThrowDicesAndMoveL();
	PassTurnToNextL();
	}

/**
 Player throws the dices and moves. Notifies
 the observer of the number of dices thrown.
 Advances the number of properties dices showed.
*/
void CPlayer::ThrowDicesAndMoveL()
	{
	if (IsMyTurn())
		{
#ifdef _DEBUG
	_LIT(KPlayerData, " Turn to: %S\n");
	_LIT(KPlace, "CPlayer::ThrowDicesAndMoveL\n");
	RDebug::Print(KPlace);
	RDebug::Print(KPlayerData, &iName);
#endif			
		TInt firstDice;
		TInt secondDice;
		iTurn->ThrowDices(firstDice, secondDice);
		iDiceCount = firstDice + secondDice;
		iStepsTaken = 0;
		if (iObserver)
			{
			iObserver->HandleGameEventL(MMobopolyObserver::EDicesThrown, iDiceCount);
			}

		iMyLocation->AcceptL(*this);
		}
	}

/**
 Tells the next player in the circular linked list.
 @returns The next player pointer.
*/
CPlayer * CPlayer::Next()
	{
	return iNextPlayer;
	}

/** 
 Sets the next player
 @param aNext The next player.
*/
void CPlayer::SetNext(CPlayer & aNext)
	{
	iNextPlayer = &aNext;
	}

/**
 Passes the turn to the next player.
 First checks if the player has any money. If yes,
 and the player has the turn, then gives the turn to the
 next player. If the player didn't have the turn, it asks
 the next player to give the turn to the following player.
*/
void CPlayer::PassTurnToNextL()
	{
	if (iMoney >= 0) // continue game only if Player has money
		{
		if (iNextPlayer)
			{
			if (iTurn)
				{
				// Have to save the turn to temp and then null own
				// and pass the temp to the other player.
				// Otherwise both this player and the other has the
				// turn object at the same time.
				CTurn * tmp = iTurn;
				iTurn = 0;
				iNextPlayer->TakeTurnL(*tmp);
				}
			else
				{
				iNextPlayer->PassTurnToNextL();
				}
			}
		}
	else
		{
		if (iObserver)
			{
			iObserver->HandleGameEventL(MMobopolyObserver::EPlayerOutOfMoney);
			}
		
		}
	}

/**
 Sets the observer who observers game events.
 @param aObserver The observer.
*/
void CPlayer::SetObserver(MMobopolyObserver * aObserver)
	{
	iObserver = aObserver;
	}

// From MPropertyVisitor

/**
 Implements the Visitor design pattern.
 Implements visiting for the free parking objects.
 Adds the number of steps taken. If there are still 
 steps to take, goes to the next property by calling
 AcceptL. Otherwise, sets the player's location to be
 the current property.
 @param aObject Free parking object to visit.
*/
void CPlayer::VisitL(CFreeParking & aObject)
	{
	// Do nothing, go forward if necessary
	iStepsTaken++;
	if (iStepsTaken < iDiceCount)
		{
		aObject.Next()->AcceptL(*this);
		}
	else
		{
		iMyLocation = &aObject;
		}
	}

/**
 Implements the Visitor design pattern.
 Implements visiting for the buildable property objects.
 Adds the number of steps taken. If there are still 
 steps to take, goes to the next property by calling
 AcceptL. Otherwise, sets the player's location to be
 the current property. Also, checks the owner. If the owner
 is somebody other, pays rent to this other player.
 If there is no owner, tries to buy the property.
 Notifies the observer of these events.
 @param aObject Buildable property object to visit.
*/
void CPlayer::VisitL(CBuildableProperty & aObject)
	{
	// Do nothing, go forward if necessary
	iStepsTaken++;
	if (iStepsTaken < iDiceCount)
		{
		aObject.Next()->AcceptL(*this);
		}
	else
		{
		iMyLocation = &aObject;
		CPlayer * currentOwner = aObject.Owner();
		if (currentOwner && currentOwner != this)
			{
			// Somebody else owns the lot!!
			TInt rent = aObject.Rent();
			Withdraw(rent);
			currentOwner->Deposit(rent);
			NotifyRentPaidL(rent); // Template method step 1
			if (Money() < 0)
				{
				// Bankrupt!!
				if (iObserver)
					{
					iObserver->HandleGameEventL(MMobopolyObserver::EPlayerOutOfMoney);
					}
				}			
			}
		else 
			{
			if (!currentOwner) // Nobody owns this, so I can buy
				{
				DoBuyPropertyL(aObject); // Template method step 2
				}
			}
		}
	}

/**
 Implements the Visitor design pattern.
 Implements visiting for the Go square objects.
 Adds the number of steps taken. If there are still 
 steps to take, goes to the next property by calling
 AcceptL. Also, deposits a sum determined by the Go square
 to the "account" of the player.
 @param aObject Go square object to visit.
*/
void CPlayer::VisitL(CGoSquare & aObject)
	{
	// Do nothing, go forward if necessary
	if (iStepsTaken > 0) // Not starting from GoSquare
		{
		Deposit(aObject.SumToPlayer());
		if (iObserver)
			{
			iObserver->HandleGameEventL(MMobopolyObserver::EPlayerCollectedGoMoney, aObject.SumToPlayer());
			}
		}
	if (++iStepsTaken < iDiceCount)
		{
		aObject.Next()->AcceptL(*this);
		}
	else
		{
		iMyLocation = &aObject;
		}
	}


/**
 Template method step implementation for software player to notify of paid rent.
 Notifies the user that the software player paid rent.
 @param aPrice How much rent was paid.
*/
void CPlayer::NotifyRentPaidL(TInt aPrice)
	{
	if (iObserver)
		{
		iObserver->HandleGameEventL(MMobopolyObserver::ESWPlayerPaidRent, aPrice);
		}
	}

/**
 Template method step implementation for software player to notify of property bought.
 Notifies the user that the software bought a property.
 @param aPrice How much was paid for the property.
*/
void CPlayer::NotifyPropertyBoughtL(TInt aPrice)
	{
	if (iObserver)
		{
		iObserver->HandleGameEventL(MMobopolyObserver::ESWPlayerBought, aPrice);
		}
	}
	
/**
 Template method implementation for software player to buy a property.
 Calls the BuyPropertyL.
 @param aObject The property to buy.
*/
void CPlayer::DoBuyPropertyL(CBuildableProperty & aObject)
	{
	BuyPropertyL(aObject);
	}

/**
 Implementation for software player to buy a property.
 Checks that there is enough money to buy the property,
 buys it and notifies the user of the transaction.
 @param aObject The property to buy.
*/
void CPlayer::BuyPropertyL(CBuildableProperty & aObject)
	{
	if (IsMyTurn() && !(aObject.Owner()))
		{
		TInt price = aObject.Price();
		if (price <= Money()) // Can buy
			{
			Withdraw(price);
			aObject.SetOwner(*this);
			NotifyPropertyBoughtL(price);
#ifdef _DEBUG
	_LIT(KPlayerData, " Player: %S BUYS Loc: %S\n");
	_LIT(KPlace, "CPlayer::BuyPropertyL\n");
	RDebug::Print(KPlace);
	RDebug::Print(KPlayerData, &iName, &aObject.Name());
#endif			
			}
		}
	}
	
	
	
} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Player.cpp,v $
* Revision 1.10  2006/02/15 13:25:36  Antti
* Fixed doxygen comments.
*
* Revision 1.9  2006/02/15 12:38:11  Antti
* Committing first public version of the example solution
*
*
*/