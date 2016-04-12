/*Copyright   Jan 30, 2006 Antti Juustila ----------------------

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

// MobopolyObserver.h
//
// $Id: MobopolyObserver.h,v 1.1 2006/02/15 12:38:17 Antti Exp $
// @author Antti Juustila
// @version $Revision: 1.1 $

#ifndef __MOBOPOLYOBSERVER_H
#define __MOBOPOLYOBSERVER_H

#include <e32std.h>

namespace mobopoly
{
	
/** 
 This interface is used to notify an observer of the CBank and other
 classes implementing this interface about the game events.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class MMobopolyObserver
	{
public:

	/** The different game events observers react to. */
	enum TGameEvents 
		{
		ETurnToHumanPlayer,	/**< Turn was switched to human player. */
		ETurnToSWPlayer,		/**< Turn was switched to software player. */
		EPlayerCanBuy,			/**< The human player can buy this property. */
		ESWPlayerBought,		/**< The software player bought the property. */
		EHumanPlayerBought,	/**< The human player bought the property. */
		ESWPlayerDidNotBuy,	/**< The software player did not buy the property. */
		EPlayerOutOfMoney,	/**< Some player ran out of money. */
		ESWPlayerPaidRent,	/**< Software player paid rent. */
		EHumanPlayerPaidRent,/**< Human player paid rent. */
		EPlayerCollectedGoMoney, /**< Player passed or stayed at the Go square and got some money. */
		EBuyTimerFired,		/**< The timer fired at one sec interval, show time left to buy the property. */
		EDicesThrown			/**< Player threw the dices. */
		};
		
	/**
	 Called by the subjects of the observers to notify the observer of
	 the game events. The event specific parameter aParam is relevant
	 for the following events (see the implementation of CMobopolyGameInfo):
	 <ul>
	 <li>ESWPlayerPaidRent -- parameter tells how much rent was paid by the software player.</li>
	 <li>EHumanPlayerPaidRent -- parameter tells how much human player paid rent.</li>
	 <li>EPlayerCollectedGoMoney -- parameter tells how much money player got from Go square.</li>
	 <li>EBuyTimerFired -- parameter tells how many seconds there are left for the human player to buy the property.</li>
	 <li>EDicesThrown -- parameter tells the number the player threw with dices.</li>
	 </ul>
	 @param aEvent Specified the event that happened.
	 @param aParam Event specific parameter.
	*/
	virtual void HandleGameEventL(TGameEvents aEvent, TInt aParam = -1) = 0;
	
	virtual ~MMobopolyObserver() { /* Empty */};
	};

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyObserver.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/