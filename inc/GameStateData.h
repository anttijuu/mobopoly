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

// GameStateData.h
//
// $Id: GameStateData.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __GAMESTATEDATA_H
#define __GAMESTATEDATA_H

#include <e32std.h>
#include <e32base.h>

#include "MobopolyDefines.h"
#include "PropertyVisitor.h"

namespace mobopoly 
{

/**
 This structure defines the data elements collected from the game engine
 when the UI fetches the game state from the engine using
 CBank::GetGameStateDataL(CGameStateData & aState). The CGameStateData object
 is filled with TPlayerStateData objects, one for each player.
 The current UI implementation given as is, does not use all of these
 data elements. For implementing optional features, you may change this
 structure.
 @see CGameStateData
 @see CBank
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class TPlayerStateData
	{
public:
	/** Initializes default values for member data. */
	IMPORT_C TPlayerStateData();
	
	/** The name of the player. */
	TBufC<KMaxPlayerNameLen> 	iPlayerName;
	/** The current location (name of the property) where the player is at. */
	TBufC<KMaxPropertyNameLen>	iPlayerLocation;
	/** The current location's owner name, where the player is at. */
	TBufC<KMaxPlayerNameLen> 	iLocationOwner;
	/** The price to pay for buying the property where the player is currently at. */
	TInt								iPlayerLocationPrice;
	/** The current amount of money the player has. */
	TInt								iPlayerMoney;
	/** The count of properties the player currently has. */
	TInt								iPlayerPropertyCount;
	/** The number of houses the player has built. */
	TInt								iPlayerHouseCount;
	/** The total sum of properties values the player owns. */
	TInt								iPlayerPropertyValue;
	/** Does the player currently has the turn (ETrue) or not (EFalse). */
	TBool								iHasTurnNow;
	}; // TGameStateData

/**
 This class is a container that contains all the game state data. UI uses
 this object to gather data from the game engine. This data stored into
 TPlayerStateData objects, contained in this class, one for each palyer.
 This data is then displayed in the UI to the user. The game state data
 is fetched from the engine always when the game state changes so
 that fresh data is needed. The number of houses and hotels the bank
 currently has is also stored in this class.

 @see TPlayerStateData
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CGameStateData : public CBase, public MPropertyVisitor
	{
public:
	IMPORT_C static CGameStateData * NewL();
	IMPORT_C virtual ~CGameStateData();
	
	IMPORT_C void Reset();
	
	void AddPlayerStateDataL(const TPlayerStateData & aData);
	void ModifyPlayerStateData(const TPlayerStateData & aData);
	void SetHousesWithBank(TInt aHouses);
	void SetHotelsWithBank(TInt aHotels);
	
	IMPORT_C TBool GetFirstPlayerState(TPlayerStateData & aData) const;
	IMPORT_C TBool GetNextPlayerState(TPlayerStateData & aData) const;
	IMPORT_C TInt  HousesWithBank() const;
	IMPORT_C TInt  HotelsWithBank() const;

	IMPORT_C const TDesC & WhosTurn() const;
	
	// From MPropertyVisitor
	void VisitL(CFreeParking & aObject);
	void VisitL(CBuildableProperty & aObject);
	void VisitL(CGoSquare & aObject);

private:
	CGameStateData();
	void ConstructL();
	
private:
	/** The container for player state data. */
	CArrayFixFlat<TPlayerStateData>	* iPlayerStates;
	/** The number of houses the bank has. */
	TInt iHousesWithBank;
	/** The number of hotels the bank has. */
	TInt iHotelsWithBank;
	/**
	 Internal counter used by GetFirstPlayerState and 
	 GetNextPlayerState. Mutable, since these are both const methods. */
	mutable TInt iCurrentObject;
	/**
	 Used to keep track of has the object already been in the Go square.
	 Going through the properties starts from the Go square, and as it 
	 is reentered, all properties have been handled for a player. */
	TBool iGoSquareVisited;
	};
	
} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: GameStateData.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/