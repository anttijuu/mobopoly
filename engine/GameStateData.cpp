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

// GameStateData.cpp
//
// $Id: GameStateData.cpp,v 1.2 2006/02/15 13:22:17 Antti Exp $

#ifdef _DEBUG
#include <e32svr.h>
#endif

#include "Player.h"
#include "GameStateData.h"
#include "BuildableProperty.h"
#include "FreeParking.h"
#include "GoSquare.h"

#include "Mobopoly.pan"

namespace mobopoly 
{

/**
 Constructor, initalizes all member variables to a default value.
 There is no need to initialize descriptors, since they have
 default constructors that do this automagically.
*/
EXPORT_C TPlayerStateData::TPlayerStateData()
	{
	iPlayerMoney = 0;
	iPlayerPropertyCount = 0;
	iPlayerLocationPrice = 0;
	iPlayerHouseCount = 0;
	iPlayerPropertyValue = 0;
	iHasTurnNow = EFalse;
	}

/**
 Creates a new game state data object using two-phase-construction.
 May leave with system general error codes.
*/	
EXPORT_C CGameStateData * CGameStateData::NewL()
	{
	CGameStateData * self = new (ELeave) CGameStateData;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}
/**
 Default constructor, does only non-leaving stuff.
*/
CGameStateData::CGameStateData()
	{	
	}
	
/**
 2nd phase constructor, does all the leaving stuff.
*/
void CGameStateData::ConstructL()
	{
	iPlayerStates = new (ELeave) CArrayFixFlat<TPlayerStateData>(2);
	}

/**
 Deallocates all the allocated resouces.
*/	
EXPORT_C CGameStateData::~CGameStateData()
	{
	delete iPlayerStates;
	}

/**
 Resets all the collected data. Called by the UI
 before starting to collect new game state data from
 the engine side.
*/
EXPORT_C void CGameStateData::Reset()
	{
	iPlayerStates->Reset();
	iHousesWithBank = 0;
	iHotelsWithBank = 0;
	iGoSquareVisited = EFalse;
	}

/**
 Adds a new player state data to the container.
 @param aData New player data.
*/
void CGameStateData::AddPlayerStateDataL(const TPlayerStateData & aData)
	{
	iPlayerStates->AppendL(aData);
	}

/**
 Modifies an existing player data in the container. The key to search 
 for is the player's name.
 @param aData The modified player data.
*/
void CGameStateData::ModifyPlayerStateData(const TPlayerStateData & aData)
	{
	for (TInt i = 0; i < iPlayerStates->Count(); i++)
		{
		if (aData.iPlayerName == (*iPlayerStates)[i].iPlayerName)
			{
			(*iPlayerStates)[i] = aData;
			break;
			}
		}
	}

/**
 Called by the UI to get the player's name who has got
 the turn at the moment.
 @returns The name of the player.
*/	
EXPORT_C const TDesC & CGameStateData::WhosTurn() const
	{
	for (TInt i = 0; i < iPlayerStates->Count(); i++)
		{
		if ((*iPlayerStates)[i].iHasTurnNow)
			{
			return (*iPlayerStates)[i].iPlayerName;
			}
		}
	return KNullDesC;
	}

/**
 Changes the number of houses the bank has.
 @param aHouses Number of houses.
*/		
void CGameStateData::SetHousesWithBank(TInt aHouses)
	{
	iHousesWithBank = aHouses;
	}

/**
 Changes the number of hotels the bank has.
 @param aHotels Number of hotels.
*/			
void CGameStateData::SetHotelsWithBank(TInt aHotels)
	{
	iHotelsWithBank = aHotels;
	}

/**
 Called by the UI to get the first player's game state data.
 TPlayerStateData object is filled with the collected data from
 the engine and used by the UI to display the game state for
 that player.
 @see GetFirstPlayerState
 @param aData The player game state data
 @returns ETrue, if there was an object returned in the parameter, EFalse if not.
*/
EXPORT_C TBool CGameStateData::GetFirstPlayerState(TPlayerStateData & aData) const
	{
	iCurrentObject = 0;
	if (iPlayerStates->Count() > 0)
		{
		aData = (*iPlayerStates)[iCurrentObject];
		return ETrue;
		}
	return EFalse;
	}
	
/**
 Called by the UI to get the next player's game state data.
 TPlayerStateData object is filled with the collected data from
 the engine and used by the UI to display the game state for
 that player.
 @see GetFirstPlayerState
 @param aData The player game state data
 @returns ETrue, if there was an object returned in the parameter, EFalse if not.
*/
EXPORT_C TBool CGameStateData::GetNextPlayerState(TPlayerStateData & aData) const
	{
	if (++iCurrentObject < iPlayerStates->Count())
		{
		aData = (*iPlayerStates)[iCurrentObject];
		return ETrue;
		}
	return EFalse;
	}

/**
 Called by the UI to query how many houses the bank still has.
 @returns How many houses there are to buy.
*/	
EXPORT_C TInt  CGameStateData::HousesWithBank() const
	{
	return iHousesWithBank;
	}
	
/**
 Called by the UI to query how many hotels the bank still has.
 @returns How many hotels there are to buy.
*/	
EXPORT_C TInt  CGameStateData::HotelsWithBank() const
	{
	return iHotelsWithBank;
	}


/**
 Visits a free parking property to collect game data.
 Does basically nothing here, just goes to the next property.
 @param aObject The freeparking object.
*/
void CGameStateData::VisitL(CFreeParking & aObject)
	{
	// Do nothing.
	aObject.Next()->AcceptL(*this);
	}
	
/**
 Visits a buildable property to collect game data.
 Goes through all the players and for each player
 <ol>
 <li>Gets the player data</li>
 <li>If the player is at that location, get the price and
     owner of the location and put it in the player data.</li>
 <li>If the object is owned by the player, the player statistics is updated.</li>
 <li>The modified player data is saved in the container</li>
 </ol>
 Finally, the visitor is passed to the next property.
 @param aObject The buildable property object.
*/
void CGameStateData::VisitL(CBuildableProperty & aObject)
	{
#ifdef _DEBUG
	_LIT(KPlayerData, " Property: %S Owner: %S\n");
	TBuf<100> tmp;
	if (aObject.Owner())
		tmp = aObject.Owner()->Name();
	RDebug::Print(KPlayerData, &aObject.Name(), &tmp);
#endif			

	TPlayerStateData playerData;
	if (GetFirstPlayerState(playerData))
		{
		TBool changes = EFalse;
		do
			{
			if (playerData.iPlayerLocation == aObject.Name())
				{
				playerData.iPlayerLocationPrice = aObject.Price();
				changes = ETrue;
				if (aObject.Owner())
					{
					playerData.iLocationOwner = aObject.Owner()->Name();
					}
				}
			if (aObject.Owner())
				{
				if (aObject.Owner()->Name() == playerData.iPlayerName)
					{
					changes = ETrue;
					playerData.iPlayerPropertyCount++;
					playerData.iPlayerHouseCount = aObject.HouseCount();
					playerData.iPlayerPropertyValue += aObject.Price();
					}
				}
			if (changes)
				{
				ModifyPlayerStateData(playerData);
				}
			changes = EFalse;
			} while (GetNextPlayerState(playerData));
		}
		aObject.Next()->AcceptL(*this);
	}

/**
 Visits a Go square property to collect game data.
 Does basically nothing here, just checks that if the
 Go square has not been visited, goes on to the next property.
 Otherwise, all the properties have been visited (since the Go square
 is visited first) and this concludes the visiting.
 @param aObject The freeparking object.
*/
void CGameStateData::VisitL(CGoSquare & aObject)
	{
	// Do nothing.	
	if (!iGoSquareVisited)
		{
		iGoSquareVisited = ETrue;
		aObject.Next()->AcceptL(*this);
		}
	}

	
	
} // namespace


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: GameStateData.cpp,v $
* Revision 1.2  2006/02/15 13:22:17  Antti
* Fixed doxygen comments.
*
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/