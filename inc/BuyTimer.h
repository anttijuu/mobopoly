/*Copyright   Feb 03, 2006 Antti Juustila ----------------------

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

// BuyTimer.h
//
// $Id: BuyTimer.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __BUYTIMER_H
#define __BUYTIMER_H

#include <e32std.h>
#include <e32base.h>


namespace mobopoly 
{


/**
 The interface class the CBuyTimer uses to notify an observer
 that a timer with a period of one second is fired.
*/

class MBuyTimerObserver 
	{
public:
	/**
	 Called as the timer fires.
	 @param aHowManySecondsLeft How many seconds left until buying is too late. */
	virtual void TimerFiredL(TInt aHowManySecondsLeft) = 0;
	};
	
/**
 The timer active object used to give a timeout to the user
 for buying a property.
 
 The MBuyTimerObserver is notified every time a second passes by.
 The notification message includes the number of seconds the user
 has left to decide whether to buy the property or not.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/
	
class CBuyTimer : public CActive
	{
public:
	static CBuyTimer * NewL(MBuyTimerObserver * aObserver, TInt aSecondsToAlarm);	
	virtual ~CBuyTimer();

	void Start();

protected:
	// From CActive
	virtual void DoCancel();
	virtual void RunL();
	TInt RunError(TInt aError);
	
private:

	CBuyTimer(MBuyTimerObserver * aObserver, TInt aSecondsToAlarm);
	void ConstructL();
	
private:
	/** The timer object used for timing events. */
	RTimer 					iTimer;
	/** The observer to notify of seconds passing by. */
	MBuyTimerObserver 	* iObserver;
	/** The number of seconds the user has time to consider buying. */
	const TInt 				iSecondsToAlarm;
	/** How many seconds there is left to consider buying. */
	TInt						iTicksLeft;
	}; // CBuyTimer

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: BuyTimer.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/