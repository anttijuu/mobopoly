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

#ifndef __MOBOPOLYMAININFO_H
#define __MOBOPOLYMAININFO_H

#include <coecntrl.h>

#include "MobopolyObserver.h"
#include "MobopolyDefines.h"

namespace mobopoly 
{

class CBank;
class CGameStateData;

/** This is an information control that shows information about
* the game state.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyGameInfo : public CCoeControl, public MMobopolyObserver
	{
public: 
	static CMobopolyGameInfo * NewL(const TRect& aRect, CBank * aBank);

	~CMobopolyGameInfo();

	// From MMobopolyObserver
	virtual void HandleGameEventL(TGameEvents aEvent, TInt aParam);

private:
	CMobopolyGameInfo(CBank * aMobopoly);
	void ConstructL(const TRect& aRect);
	
	// From CCoeControl
	void Draw(const TRect & aRect) const;
	
	void AddNotificationMsg(TInt aMsgResourceID, TInt aParam);
	void AddMsg(const TDesC & aMsg, TBool aMoveOthersDown = ETrue);
	
private:
	/** 
	 The game engine object needed in showing information about the state of the game.
	*/
	CBank * iBank; // Does not own
	/**
	 The game state object that is given to the engine when we want it
	 to fill the object with game state data.
	*/
	CGameStateData * iGameState;
	/**
	 The buffer for notification messages. New messages are inserted at the beginning,
	 old messages transferred down and last message erased.
	 */
	TBuf<KMaxUINotificationMsgLen> iMsgBuf[KUINotificationMsgBufSize];
	};

} // namespace

#endif // __MOBOPOLYMAININFO_H

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameInfo.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/