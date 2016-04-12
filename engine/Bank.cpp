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

// BANK.cpp
//
// $Id: Bank.cpp,v 1.2 2006/02/15 12:57:32 Antti Exp $

#include <e32svr.h>
#include <f32file.h>
#include <bautils.h>

#include "Bank.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GoSquare.h"
#include "BuildableProperty.h"
#include "FreeParking.h"
#include "Turn.h"
#include "GameStateData.h"
#include "MobopolyObserver.h"


namespace mobopoly 
{

/**
 The factory method for creating the bank object safely.
 Leaves if the object cannot be created with a system leave code.
 @returns The bank object.
*/
EXPORT_C CBank * CBank::NewL()
	{
	CBank * self = new (ELeave) CBank;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

/**
 Second phase constructor, does all the leaving stuff.
 <ol>
 <li>Creates the dynamic containers for the players and properties</li>
 <li>Creates the turn object</li>
 <li>Creates the timer active object.</li>
 </ol>
*/
void CBank::ConstructL()
	{
	// Create containers
	iPlayers = new (ELeave) CArrayPtrFlat<CPlayer>(2);
	iProperties = new (ELeave) CArrayPtrFlat<CProperty>(8);
		
	// Create the turn
	iTurn = new (ELeave) CTurn;
	
	iBuyTimer = CBuyTimer::NewL(this, 10);
	}

/** 
 Constructor, does all non leaving stuff.
*/
CBank::CBank() : iWhoseTurn(ENobody), iHumanCanBuy(EFalse)
	{
#ifdef _DEBUG
	RDebug::Open();
#endif	
	}
	
/** In the destructor of the bank object, release any
 resources allocated by the object. Remember that C++
 destructors must not cause exceptions (Symbian leaves).
 Do not assume full construction, since ConstructL may
 have leave'd.
*/

EXPORT_C CBank::~CBank()
	{
#ifdef _DEBUG
	RDebug::Close();
#endif	
	if (iPlayers)
		iPlayers->ResetAndDestroy();
	delete iPlayers;
	if (iProperties)
		iProperties->ResetAndDestroy();
	delete iProperties;
	delete iTurn;
	delete iBuyTimer;
	}
	
/**
 Initializes the game by
 <ol>
 <li>Clearing the dynamic containers</li>
 <li>Checking that the configuration file exists, and opening it.</li>
 <li>Reading the file line by line using TFileText and RFile.</li>
 <li>Parsing the lne and creating the correct objects based on the file content.</li>
 <li>Cleaning up</li>
 </ol>
*/
void CBank::InitializeGameL()
	{
	iPlayers->ResetAndDestroy();
	iProperties->ResetAndDestroy();

	_LIT(KMoboFile, "C:\\Documents\\Mobopoly\\Mobopoly.txt");

	RFs fsSession;
	RFile msgFile;
	TFileText txtFile;
	TInt result;
	
	User::LeaveIfError(fsSession.Connect());
	CleanupClosePushL(fsSession);
	if (BaflUtils::FileExists(fsSession, KMoboFile))
		{
		TBuf<256> msg;
		User::LeaveIfError(msgFile.Open(fsSession, KMoboFile, EFileRead));
		CleanupClosePushL(msgFile);
		txtFile.Set(msgFile);
		txtFile.Seek(ESeekStart);
		do 
			{
			result = txtFile.Read(msg);
			if (msg.Length() && (result == KErrNone || result == KErrTooBig))
				{
				ParseLineL(msg);
				}
			else
				{
				 if (result != KErrEof && result != KErrNone)
				 	{
					User::Leave(result);
				 	}
				}
			} while (result != KErrEof);
		CleanupStack::PopAndDestroy(); // msgFile
		}
	CleanupStack::PopAndDestroy(); // fsSession
	LinkAndPlaceObjects();
	}

/**
 Parses a single line of confituration file text, creating correct objects 
 for the game. Uses TLex for parsing. See documentation on details of the
 file structure.
 @see TLex
 @param aLine Text line to parse.
*/
void CBank::ParseLineL(const TDesC & aLine)
	{
	_LIT(KGoSquare, "GO");
	_LIT(KPlayer,"PLAYER");
	_LIT(KSWPlayer, "SWPLAYER");
	_LIT(KBuildings, "BUILDINGS");
	_LIT(KBuildableProperty, "PROPERTY");
	_LIT(KFreeParking, "FREEPARKING");
	
	TLex lexer(aLine);
	TChar chr;
	lexer.SkipSpaceAndMark(); // Skip any whitespace at the beginning
	while (!lexer.Eos())
		{
		chr = lexer.Get();
		if (chr == ',') // items separated by commas
			{
			lexer.UnGet(); // Unget the comma
			TPtrC nextToken = lexer.MarkedToken(); // Get the string
			if (nextToken == KGoSquare)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				CProperty * prop = new (ELeave) CGoSquare;
				CleanupStack::PushL(prop);
				prop->ParseL(data);
				iProperties->AppendL(prop);
				CleanupStack::Pop();
				break;
				}
			else if (nextToken == KPlayer)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				CPlayer * player = new (ELeave) CHumanPlayer;
				CleanupStack::PushL(player);
				player->ParseL(data);
				iPlayers->AppendL(player);
				CleanupStack::Pop();
				break;
				}
			else if (nextToken == KSWPlayer)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				CPlayer * player = new (ELeave) CPlayer;
				CleanupStack::PushL(player);
				player->ParseL(data);
				iPlayers->AppendL(player);
				CleanupStack::Pop();
				break;				
				}
			else if (nextToken == KBuildings)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				ParseBuildingsL(data);
				break;
				}
			else if (nextToken == KBuildableProperty)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				CProperty * prop = new (ELeave) CBuildableProperty;
				CleanupStack::PushL(prop);
				prop->ParseL(data);
				iProperties->AppendL(prop);
				CleanupStack::Pop();
				break;
				}
			else if (nextToken == KFreeParking)
				{
				lexer.SkipAndMark(1); // Skip over the comma
				TPtrC data = lexer.Remainder();
				CProperty * prop = new (ELeave) CFreeParking;
				CleanupStack::PushL(prop);
				prop->ParseL(data);
				iProperties->AppendL(prop);
				CleanupStack::Pop();
				break;
				}
			else
				{
				break;
				}
			lexer.SkipSpaceAndMark(); // Skip over any whitespace and mark.
			}
		}
	}

/**
 Called after the objects have been created from the file.
 Since players and properties form a linked list, these links are
 now set up. Also observer relationships are set up, and the locations
 of the players.
*/	
void CBank::LinkAndPlaceObjects()
	{
	TInt i;
	for (i = 1; i < iPlayers->Count(); i++)	
		{
		(*iPlayers)[i-1]->SetNext(*(*iPlayers)[i]);
		(*iPlayers)[i-1]->SetLocation(*(*iProperties)[0]);
		}
	(*iPlayers)[iPlayers->Count()-1]->SetNext(*(*iPlayers)[0]);
	(*iPlayers)[iPlayers->Count()-1]->SetLocation(*(*iProperties)[0]);

	if (iObserver)	
		{
		for (i = 0; i < iPlayers->Count(); i++)
			{
			(*iPlayers)[i]->SetObserver(this);
			}
		}
	
	for (i = 1; i < iProperties->Count(); i++)	
		{
		(*iProperties)[i-1]->SetNext(*(*iProperties)[i]);
		}
	(*iProperties)[iProperties->Count()-1]->SetNext(*(*iProperties)[0]);
	}

/**
 Parses the building data from the configuration file.
 Extracts the number of houses and hotels the bank has in the game.
 @param aData The string to parse.
*/
void CBank::ParseBuildingsL(const TDesC & aData)
	{
	TLex lexer(aData);
	
	TChar chr;

	iNumberOfHouses = 0;
	iNumberOfHotels = 0;

	lexer.SkipSpaceAndMark(); // Skip any whitespace at the beginning
	while (!lexer.Eos())
		{
		chr = lexer.Get();
		if (chr == ',') // items separated by commas
			{
			lexer.UnGet(); // comma
			TPtrC data = lexer.MarkedToken();
			TLex numLexer(data);
			TInt tmp;
			if (numLexer.Val(tmp) == KErrNone)
				{
				if (iNumberOfHouses == 0)
					{
					iNumberOfHouses = tmp;

					lexer.SkipAndMark(1); // Skip over the comma
					TPtrC data = lexer.Remainder();
					TLex numLexer(data);
					TInt tmp;
					if (numLexer.Val(tmp) == KErrNone)
						{
						iNumberOfHotels = tmp;
						break;
						}
					}
				}
			lexer.SkipAndMark(1); // Skip over the comma
			}
		}
	if (iNumberOfHotels == 0 || iNumberOfHotels == 0)
		{
		User::Leave(KErrCorrupt);
		}
	}

/**
 Called by the UI, when user selects the start game
 menu. May leave with general system leave codes.
 In here, the bank object
 <ol>
 <li>Opens and reads game data from the game initialization file</li>
 <li>Creates the game objects based on the file contents</li>
 <li>Sets up other necessary objects needed in the game</li>
 <li>Starts the game by giving the turn to the human player (first player)</li>
 </ol>
*/

EXPORT_C void CBank::StartGameL()
	{
#ifdef _DEBUG
	_LIT(KPlace, "CBank::StartGameL\n");
	RDebug::Print(KPlace);
#endif			

	TRAPD(err, InitializeGameL());
	if (err != KErrNone)
		{
		iPlayers->ResetAndDestroy();
		iProperties->ResetAndDestroy();
		iNumberOfHotels = 0;
		iNumberOfHouses = 0;
		User::Leave(err);
		}

	if (iPlayers->Count() > 1)
		{
		iWhoseTurn = EHuman;
		(*iPlayers)[0]->TakeTurnL(*iTurn);
		}
	}

/**
 Indicates if the human player may throw the dices.
 Used by the UI to enable or disable the throw dices menu item.
 @returns ETrue, if human player can trow.
*/
EXPORT_C TBool CBank::HumanPlayerCanThrow() const
	{
	return (iWhoseTurn == EHuman);
	}
	
/**
 Indicates if the human player can buy the selected property.
 Used by the UI to enable or disable the buy menu item.
 @returns ETrue, if human player can buy.
*/
EXPORT_C TBool CBank::HumanPlayerCanBuy() const
	{
	return iHumanCanBuy;	
	}

/**
 Indicates if the game has been started and not ended.
 Used by the UI to enable or disable the start game menu item.
 @returns ETrue, if the game is active.
*/
EXPORT_C TBool CBank::GameIsActive() const
	{
	return (iWhoseTurn != ENobody);
	}

/**
 Called by the UI when the human player selects the
 throw dices menu item. May leave with any of the system
 leave codes. The dices are thrown, and the human player
 is moved ahead according to the game rules. If the human
 stops at a property that can be bought, the user is notified
 of this and the timer that controls the timeout for buying is
 started. If the user stops at a property owned by another
 player, the player pays the correct rent. If the player
 passes by or stops at the Go square, the specified amount of
 money is given to the player.
 @returns ETrue, if the player throwed the dices.
*/
EXPORT_C TBool CBank::HumanPlayerThrowsL()
	{
	if (HumanPlayerCanThrow())
		{
		for (TInt i = 0; i < iPlayers->Count(); i++)
			{
			CPlayer * player = (*iPlayers)[i];
			if (player->IsMyTurn())
				{
				player->ThrowDicesAndMoveL();
				if (!HumanPlayerCanBuy())
					{
					player->PassTurnToNextL();
					}
				return ETrue;
				}
			}
		}
		return EFalse;
	}

/**
 Called by the UI when the human player decides to buy the
 property the player is at. It should not be possible to 
 call this method
 <ul>
 <li>if it is not the user's turn</li>
 <li>the property is not buyable</li>
 <li>the player has not got enough money or</li>
 <li>if the buy timer has already fired.</li>
 </ul>
 The property is given to the player, the correct amount
 of money is taken away from the user, and the buy timer
 is cancelled. Finally, if the game can still continue
 (the player didn't run out of money) the turn is given
 to the next player.
*/
EXPORT_C void CBank::HumanPlayerBuysPropertyL()
	{
	if (HumanPlayerCanBuy())
		{
		iBuyTimer->Cancel();
		for (TInt i = 0; i < iPlayers->Count(); i++)
			{
			CPlayer * player = (*iPlayers)[i];
			if (player->IsMyTurn())
				{
				player->MyLocation().AcceptL(*player);
				player->PassTurnToNextL();
				break;
				}
			}
		}
	}

/**
 Tells how many houses the bank has.
 @returns The number of houses
*/
TInt CBank::HousesAvailable() const
	{
	return iNumberOfHouses;
	}
	
/**
 Tells how many hotels the bank has.
 @returns The number of hotels
*/
TInt CBank::HotelsAvailable() const
	{
	return iNumberOfHotels;
	}

/**
 Buys a specified number of houses from the bank.
 @param aHowMany How many houses to buy.
 @returns How many houses could be bought.
*/
TInt CBank::BuyHouses(TInt aHowMany)
	{
	iNumberOfHouses -= aHowMany;
	if (iNumberOfHouses < 0)
		{
		TInt couldBuy = aHowMany + iNumberOfHouses;
		iNumberOfHouses = 0;
		return couldBuy;
		}
	return aHowMany;
	}

/**
 Buys a specified number of hotels from the bank.
 @param aHowMany How many hotels to buy.
 @returns How many hotels could be bought.
*/
TInt CBank::BuyHotels(TInt aHowMany)
	{
	iNumberOfHotels -= aHowMany;
	if (iNumberOfHotels < 0)
		{
		TInt couldBuy = aHowMany + iNumberOfHotels;
		iNumberOfHotels = 0;
		return couldBuy;
		}
	return aHowMany;
	}


/**
 Sets the observer to the game engine (the bank). The observer
 is notified of the game events using the MMobopolyObserver
 interface. Called by the UI.
 @see MMobopolyObserver
 @param aObserver The observer to notify of the game events
*/
EXPORT_C void CBank::SetObserver(MMobopolyObserver * aObserver)
	{
	iObserver = aObserver;
	for (TInt i = 0; i < iPlayers->Count(); i++)
		{
		(*iPlayers)[i]->SetObserver(this);
		}
	}

/**
 Called by the UI to get the current game state data. This data
 is used by the UI to draw game status to the UI view(s). May
 leave with any of the general system leave codes.
 @see CGameStateData
 @see TPlayerStateData
 @param aState The game state object that is filled with
 the game state data.
*/
EXPORT_C void CBank::GetGameStateDataL(CGameStateData & aState)
	{
	TInt i;

	aState.Reset();
	
/*
#ifdef _DEBUG
	_LIT(KPlace, "---- CBank::GetGameStateDataL:\n");
	RDebug::Print(KPlace);
#endif			
*/

	aState.SetHousesWithBank(iNumberOfHouses);
	aState.SetHotelsWithBank(iNumberOfHotels);
	for (i = 0; i < iPlayers->Count(); i++)
		{
		CPlayer * player = (*iPlayers)[i];
		TPlayerStateData playerData;
		playerData.iPlayerName = player->Name();
		playerData.iPlayerLocation = player->MyLocation().Name();
		playerData.iPlayerMoney = player->Money();
		playerData.iHasTurnNow = player->IsMyTurn();
		aState.AddPlayerStateDataL(playerData);
/*
#ifdef _DEBUG
	_LIT(KPlayerData, " Player: %S Loc: %S\n");
	RDebug::Print(KPlayerData, &playerData.iPlayerName, &playerData.iPlayerLocation);
#endif			
*/
		}

/*
#ifdef _DEBUG
	_LIT(KStartVisit, "--CGameStateData::VisitL\n");
	RDebug::Print(KStartVisit);
#endif			
*/
	(*iProperties)[0]->AcceptL(aState);
	
	}


/**
 The bank is an observer to the actual event generating objects, the game players.
 The bank handles the events, updates it's state that is again used by the UI to
 determine, for example, what is possible for the user to do and what is not.
 @see MMobopolyObserver
 @param aEvent The event that happened.
 @param aParam The event specific param. See MMobopolyObserver for more details.
*/
void CBank::HandleGameEventL(TGameEvents aEvent, TInt aParam)
	{
	iHumanCanBuy = EFalse;
	switch (aEvent) 
		{
		case EPlayerCanBuy:
			{
			iHumanCanBuy = ETrue;
			iBuyTimer->Start();
			iObserver->HandleGameEventL(aEvent, aParam);
			break;
			}

		case ETurnToHumanPlayer:
			{
			iWhoseTurn = EHuman;
			iObserver->HandleGameEventL(aEvent, aParam);
			break;
			}
			
		case ETurnToSWPlayer:
			{
			iWhoseTurn = EMobopoly;
			iObserver->HandleGameEventL(aEvent, aParam);
			break;
			}

		case EPlayerOutOfMoney:
			{
			iWhoseTurn = ENobody;
			iObserver->HandleGameEventL(aEvent, aParam);
			break;
			}

		default:
			{
			iObserver->HandleGameEventL(aEvent, aParam);
			break;
			}
		}
	}


/**
 Called by the CBuyTimer as the timer fires, once a second.
 If the time runs out for the user to buy the property, the turn
 is given to the next player.
 @param aHowManySecondsLeft How many secs the user has time to consider bying.
*/
void CBank::TimerFiredL(TInt aHowManySecondsLeft)
	{
	iObserver->HandleGameEventL(EBuyTimerFired, aHowManySecondsLeft);
	if (aHowManySecondsLeft == 0)
		{
		(*iPlayers)[0]->PassTurnToNextL();
		}
	}

} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Bank.cpp,v $
* Revision 1.2  2006/02/15 12:57:32  Antti
* Changed the way local variables were defined in loops for compiler and tool compatibility.
*
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/