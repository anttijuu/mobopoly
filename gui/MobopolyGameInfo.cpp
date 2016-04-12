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

#include <eikenv.h>

#include <Mobopoly.rsg>

#include "MobopolyGameInfo.h"
#include "GameStateData.h"

#include "Bank.h"

namespace mobopoly 
{
	
/** 
* Factory method for creating the info control.
* @param aRect The area the control occupies.
* @param aBank The engine object for getting game state information
* and showing game status.
* @returns The new info control.
*/
CMobopolyGameInfo * CMobopolyGameInfo::NewL(const TRect& aRect, CBank * aBank)
	{
	CMobopolyGameInfo* self = new (ELeave) CMobopolyGameInfo(aBank);
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop(self);
	return self;
	}

/**
* 2nd phase constructor for creating the info control.
* @param aRect The area the control occupies.
*/
void CMobopolyGameInfo::ConstructL(const TRect& aRect)
	{
	SetRect(aRect);
	iGameState = CGameStateData::NewL();
	iBank->SetObserver(this);
	}

/** 
* Constructor for initializing non-leaving items.
* @param aBank The Mobopoly engine object used for showing the information.
*/
CMobopolyGameInfo::CMobopolyGameInfo(CBank * aBank) : iBank(aBank)
	{
	// Empty
	}
	
/**
* Destructor for the info control.
*/
CMobopolyGameInfo::~CMobopolyGameInfo()
	{
	delete iGameState;
	}
	
/**
 Draws the control to the screen. Draws information about the game state.
  @param aRect The area that needs to be drawn.
*/
void CMobopolyGameInfo::Draw(const TRect & aRect) const
	{
	CWindowGc & gc = SystemGc();
	gc.SetClippingRect(aRect);

	gc.Clear(aRect);
	
	const CFont * font = iEikonEnv->DenseFont();
	gc.UseFont(font);
	TRect rect(Rect());
	rect.Shrink(2,2);

	TInt baseline = font->AscentInPixels() + 4; 
	TInt lineHeight = font->HeightInPixels() + 4;

	_LIT(KAt, " at ");
	_LIT(KAnd, " and ");
	_LIT(KCurrency, " $:");
	_LIT(KProperties, " properties");
	_LIT(KOwner, "Owned by: %S");
	_LIT(KParenthesisOpen, " ($");
	_LIT(KParenthesisClose, ")");
	
	rect.SetHeight(lineHeight);
	TBuf<150> textLine;
	TPlayerStateData playerData;
	if (iGameState->GetFirstPlayerState(playerData))
		{
		do
			{
			if (playerData.iHasTurnNow)
				{
				gc.SetUnderlineStyle(EUnderlineOn);
				}
			else 
				{
				gc.SetUnderlineStyle(EUnderlineOff);
				}
			// First Line, player and location
			textLine = playerData.iPlayerName;
			textLine += KAt;
			textLine += playerData.iPlayerLocation;
			textLine += KParenthesisOpen;
			textLine.AppendNum(playerData.iPlayerLocationPrice);
			textLine += KParenthesisClose;
			gc.DrawText(textLine, rect, baseline);
			gc.SetUnderlineStyle(EUnderlineOff);
			// Second line, location owner
			rect.Move(0, lineHeight);
			textLine.Format(KOwner, &playerData.iLocationOwner);
			gc.DrawText(textLine, rect, baseline);
			// Third line, money and property info			
			rect.Move(0, lineHeight);
			textLine = KCurrency;
			textLine.AppendNum(playerData.iPlayerMoney);
			textLine += KAnd;
			textLine.AppendNum(playerData.iPlayerPropertyCount);
			textLine += KProperties;
			gc.DrawText(textLine, rect, baseline);
			gc.SetPenColor(KRgbBlue);
			gc.DrawLine(TPoint(rect.iTl.iX, rect.iBr.iY+1), TPoint(rect.iBr.iX, rect.iBr.iY+1));
			gc.SetPenColor(KRgbBlack);
			rect.Move(0, lineHeight);
			} while (iGameState->GetNextPlayerState(playerData));
		}
	rect = Rect();
	rect.iTl.iX += 2;
	rect.iTl.iY = rect.iBr.iY;
	rect.iTl.iY -= KUINotificationMsgBufSize * lineHeight;

	for (TInt index = 0; index < KUINotificationMsgBufSize; index++)
		{
		if (index > 0)
			{
			gc.SetPenColor(KRgbDarkGray);
			}
		gc.DrawText(iMsgBuf[index], rect, baseline);
		rect.Move(0, lineHeight);
		}
	gc.SetPenColor(KRgbBlack);

	gc.CancelClippingRect();
	}

/**
 Handles the events from the game engine.
 @see MMobopolyObserver
 @param aEvent The event that happened.
 @param aParam The event related data.
*/
void CMobopolyGameInfo::HandleGameEventL(TGameEvents aEvent, TInt aParam)
	{
	switch (aEvent) 
		{
		case ETurnToHumanPlayer:
			{
			iBank->GetGameStateDataL(*iGameState);
			break;
			}
			
		case ETurnToSWPlayer:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_TURN_TO_SWPLAYER, aParam);
			break;
			}

		case EPlayerCanBuy:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_BUY_IF_YOU_WISH, aParam);
			break;
			}

		case ESWPlayerBought:
		case EHumanPlayerBought:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_PLAYER_BOUGHT_PROPERTY, aParam);
			break;
			}

		case ESWPlayerDidNotBuy:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_SWPLAYER_DID_NOT_BUY, aParam);
			break;
			}

		case EPlayerOutOfMoney:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_OUT_OF_MONEY, aParam);
			AddNotificationMsg(R_MOBOPOLY_GAME_OVER, aParam);
			break;
			}

		case ESWPlayerPaidRent:
		case EHumanPlayerPaidRent:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_PLAYER_PAID_RENT, aParam);
			break;
			}

		case EPlayerCollectedGoMoney:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_PLAYER_COLLECTED_MONEY, aParam);
			break;
			}
		
		case EBuyTimerFired:
			{
			AddNotificationMsg(R_MOBOPOLY_SECONDS_TO_BUY, aParam);
			break;
			}
	
		case EDicesThrown:
			{
			iBank->GetGameStateDataL(*iGameState);
			AddNotificationMsg(R_MOBOPOLY_PLAYER_THREW, aParam);
			break;
			}

		default:
			break;
		}
		DrawNow();
	}

/**
 Adds a notification message by a resource identification, adds also 
 integer data in the message.
 @param aMsgResourceID The text resoure to load.
 @param aParam The integer data from engine, related to the notification message.
*/
void CMobopolyGameInfo::AddNotificationMsg(TInt aMsgResourceID, TInt aParam)
	{
	TBuf<KMaxUINotificationMsgLen> rawmsg;
	TBuf<KMaxUINotificationMsgLen> msg;
	
	// Change 1st param to (TDes16&)rawmsg if ccc tool complains about this.
	iEikonEnv->ReadResourceAsDes16(rawmsg, aMsgResourceID);
	if (aParam >= 0)
		{
		switch (aMsgResourceID)
			{
			case R_MOBOPOLY_TURN_TO_SWPLAYER:
			case R_MOBOPOLY_PLAYER_THREW:
			case R_MOBOPOLY_PLAYER_COLLECTED_MONEY:
			case R_MOBOPOLY_PLAYER_BOUGHT_PROPERTY:
			case R_MOBOPOLY_SWPLAYER_DID_NOT_BUY:
			case R_MOBOPOLY_PLAYER_PAID_RENT:
				{
				msg.Format(rawmsg, &iGameState->WhosTurn(), aParam);
				break;
				}
				
			default:
				{
				msg.Format(rawmsg, aParam);
				break;
				}
			}
		}
	else
		{
		msg = rawmsg;
		}
	AddMsg(msg, aMsgResourceID != R_MOBOPOLY_SECONDS_TO_BUY);
	}

/**
 Adds a single message to the message buffer.
 @param aMsg The message to add.
 @param aMoveOthersDown If ETrue, move other messages down, otherwise, replace
 the top one with the new one.
*/
void CMobopolyGameInfo::AddMsg(const TDesC & aMsg, TBool aMoveOthersDown)
	{
	if (aMoveOthersDown)
		{
		for (TInt index = KUINotificationMsgBufSize-1; index > 0 ; index--)
			{
			iMsgBuf[index] = iMsgBuf[index-1];
			}
		}
	iMsgBuf[0] = aMsg;
	}


} // namespace
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameInfo.cpp,v $
* Revision 1.3  2006/02/15 13:23:24  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.2  2006/02/15 13:04:37  Antti
* Added a hint to fix ccc error msg on a correct piece of code.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
*
*/