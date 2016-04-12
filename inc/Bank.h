/*Copyright   Jan 31, 2006 Antti Juustila ----------------------

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

// BANK.h
//
// $Id: Bank.h,v 1.1 2006/02/15 12:38:15 Antti Exp $

#ifndef __BANK_H
#define __BANK_H

#include <e32std.h>
#include <e32base.h>

#include "MobopolyObserver.h"
#include "BuyTimer.h"

namespace mobopoly 
{

class CProperty;
class CPlayer;
class CTurn;
class CGameStateData;
class CFreeParking;
class CBuildableProperty;
class CGoSquare;
class MMobopolyObserver;

/**
 Class CBank is the engine object of the Mobopoly game. It provides
 an interface to the UI side to invoke functionality and provide
 data to the UI side. See documentation of the methods for details
 on how to use this class from the UI side. The task of the students
 is to implement the exported methods in the class. This also
 requires additional other classes as well as adding member variables
 and non-exported public and/or private and/or protected methods to
 this and the other new classes. The design of the solution is up to
 the students. Remember good OO design practices as well as Symbian OS
 C++ programming principles and idioms.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CBank : public CBase, public MMobopolyObserver, public MBuyTimerObserver
	{
public:
	IMPORT_C static CBank * NewL();
	IMPORT_C virtual ~CBank();

	IMPORT_C void StartGameL();

	IMPORT_C TBool HumanPlayerCanThrow() const;
	IMPORT_C TBool HumanPlayerCanBuy() const;
	IMPORT_C TBool GameIsActive() const;
	
	IMPORT_C TBool HumanPlayerThrowsL();
	IMPORT_C void HumanPlayerBuysPropertyL();
		
	TInt HousesAvailable() const;
	TInt HotelsAvailable() const;

	IMPORT_C void GetGameStateDataL(CGameStateData & aState);
	
	TInt BuyHouses(TInt aNumber);
	TInt BuyHotels(TInt aNumber);

	IMPORT_C void SetObserver(MMobopolyObserver * aObserver);
	
	// From MMobopolyObserver
	virtual void HandleGameEventL(TGameEvents aEvent, TInt aParam);

	// From MBuyTimerObserver
	virtual void TimerFiredL(TInt aHowManySecondsLeft);

private:
	CBank();
	void ConstructL();

	void InitializeGameL();
	void ParseLineL(const TDesC & aLine);
	void ParseBuildingsL(const TDesC & aData);
	void LinkAndPlaceObjects();

private:

	/** This enumeration specifies who has the turn at the game. */
	enum TWhoseTurn 
		{
		ENobody, 		/**< Nobody has the turn, game has not started/has ended. */
		EMobopoly,		/**< Mobopoly (software player) has the turn. */
		EHuman			/**< Human player has the turn. */
		};
		
	/** Who has the turn right now. */
	TWhoseTurn 						iWhoseTurn;
	/** If ETrue, human player could by the place she is on now. */
	TBool								iHumanCanBuy;
	/** The number of houses available to be bought. */
	TInt 								iNumberOfHouses;
	/** The number of hotels available to be bought. */
	TInt 								iNumberOfHotels;
	
	/** All the properties of the game. Used only for deleting them, since
	    it is a bit difficult to delete objects correctly from a circular list. */
	CArrayPtrFlat<CProperty>	* iProperties;
	/** All the players of the game. Used only for deleting them, since
	    it is a bit difficult to delete objects correctly from a circular list. */
	CArrayPtrFlat<CPlayer>		* iPlayers;
	/** The turn object. Given to the player who has the turn. */
	CTurn								* iTurn;

	/** The active object timer that manages the timeout for buying properties. */
	CBuyTimer						* iBuyTimer;
	
	/** The observer observing the game state. */
	MMobopolyObserver 			* iObserver;
	}; // CBank

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Bank.h,v $
* Revision 1.1  2006/02/15 12:38:15  Antti
* Committing first public version of the example solution
*
*
*/