/*Copyright   Jan 26, 2006 Antti Juustila ----------------------

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

// Player.h
//
// $Id: Player.h,v 1.3 2006/02/15 12:38:18 Antti Exp $

#ifndef __MOBOPOLYPlayer_H
#define __MOBOPOLYPlayer_H

#include <e32std.h>
#include <e32base.h>

#include "PropertyVisitor.h"
#include "MobopolyDefines.h"

namespace mobopoly 
{

class CProperty;
class CFreeParking;
class CBuildableProperty;
class CGoSquare;
class CTurn;
class MMobopolyObserver;

/**
 The Player class represents the software Player in the game. It is
 also a base class for the human Player. Software Player automates
 the throwing of dices and moving along the properties in the game,
 as the human Player subclass overrides some of the functionality
 to ask the user to e.g. throw the dices.
 
 Player objects move along the property objects in a circular linked
 list, forming the game board. Player objects also form a circular
 list -- the turn object is passed along this chain from one player
 to the next and back to the first player.

 DoBuyPropertyL, NotifyRentPaidL and DoBuyPropertyL are template
 method steps called from VisitL(CBuildableProperty & aObject).
 CPlayer implements them so that it just notifies and buys the
 property. CHumanPlayer notifies the user (with a different msg)
 and then requests the user to buy. User buys from menu and calls
 CBank's method that lets the player with turn buy the current
 property.
 
 @author Antti Juustila
 @version $Revision: 1.3 $
*/

class CPlayer : public CBase, public MPropertyVisitor
	{
public:
	CPlayer();
	virtual ~CPlayer();

	const TDesC & Name() const;
	void SetName(const TDesC & aName);
	
	virtual void ParseL(const TDesC & aData);
	
	// Money management
	TInt Money() const;
	void Deposit(TInt aAmount);
	TInt Withdraw(TInt aAmount);
	
	// Property management
	const CProperty & MyLocation() const;
	CProperty & MyLocation();
	void SetLocation(CProperty & aProperty);
	
	// Turn management
	TBool IsMyTurn() const;
	virtual void TakeTurnL(CTurn & aTurn);
	void PassTurnToNextL();
	void ThrowDicesAndMoveL();
	
	// Next Player management
	CPlayer * Next();
	void SetNext(CPlayer & aNext);
	
	// From MPropertyVisitor
	void VisitL(CFreeParking & aObject);
	void VisitL(CBuildableProperty & aObject);
	void VisitL(CGoSquare & aObject);
	
	void SetObserver(MMobopolyObserver * aObserver);

	void BuyPropertyL(CBuildableProperty & aObject);
	
protected:
	/**
	*/
	virtual void NotifyRentPaidL(TInt aPrice);
	virtual void NotifyPropertyBoughtL(TInt aPrice);
	virtual void DoBuyPropertyL(CBuildableProperty & aObject);

protected:
	// Don't like protected data members but what the hell...
	/** The turn object. If not null, the player has the turn. */
	CTurn * iTurn;
	/** The observer that is notified of the events regarding this player. */
	MMobopolyObserver * iObserver;
	
private:
	/** The name of the player. */
	TBufC<KMaxPlayerNameLen> iName;
	
	/** The amount of money the player has. */
	TInt iMoney;
	/** The current location of this player. */
	CProperty * iMyLocation;
	/** The pointer to the next player, forms a circular list. */
	CPlayer * iNextPlayer;
	
	/** The number of the dices thrown. */
	TInt iDiceCount;
	/**
	 The number of steps taken since the dice was thrown.
	 When the steps reach zero, player stops advancing the
	 list of properties.
	*/
	TInt iStepsTaken;
	
	}; // CPlayer

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Player.h,v $
* Revision 1.3  2006/02/15 12:38:18  Antti
* Committing first public version of the example solution
*
*
*/