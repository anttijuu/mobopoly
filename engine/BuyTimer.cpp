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

// BuyTimer.cpp
//
// $Id: BuyTimer.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include "BuyTimer.h"


namespace mobopoly 
{


/**
 The factory method for creating new buy timers.
 @param aObserver The observer that is notified of timer events.
 @param aSecondsToAlarm How many seconds user can consider bying.
 @returns The new buy timer object.
*/
CBuyTimer * CBuyTimer::NewL(MBuyTimerObserver * aObserver, TInt aSecondsToAlarm)
	{
	CBuyTimer * self = new (ELeave) CBuyTimer(aObserver, aSecondsToAlarm);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

/**
 Destructor, must remember to Cancel the timer as well as release the RTimer object.
*/
CBuyTimer::~CBuyTimer()
	{
	Cancel();
	iTimer.Close();
	}


/**
 Constructor, does non-leaving initialization. Also calls CActive's constructor
 to set the priority of the active object.
 @param aObserver The observer that is notified of timer events.
 @param aSecondsToAlarm How many seconds user can consider bying.
*/
CBuyTimer::CBuyTimer(MBuyTimerObserver * aObserver, TInt aSecondsToAlarm)
		: CActive(CActive::EPriorityStandard), iObserver(aObserver), iSecondsToAlarm(aSecondsToAlarm)
	{
	}

/**
 Second constructor, does leaving stuff.
 Creates the timer object, adds the active object into the active scheduler.
*/
void CBuyTimer::ConstructL()
	{
	User::LeaveIfError(iTimer.CreateLocal());
	CActiveScheduler::Add(this);
	}

/**
 Starts the timer.
 Remember to check if the timer is already on and handle that. Here 
 we just cancel and restart the timer.
 Remember also to set the active object active.
*/	
void CBuyTimer::Start()
	{
	if (IsActive())
		{
		Cancel();
		}
	iTicksLeft = iSecondsToAlarm;
	iTimer.After(iStatus, 1000000); // Fire after one second
	SetActive();
	}

/**
 Cancel protocol for the timer. Never call this directly,
 call CActive::Cancel. Cancels the timer and resets data.
*/	
void CBuyTimer::DoCancel()
	{
	iTimer.Cancel();
	iTicksLeft = iSecondsToAlarm;
	}

/**
 Always when RunL could leave, you should think of
 handling the leave in RunError. Active sheduler calls this
 if RunL leaves. Default implementation in CActive just returns
 the error code to the scheduler. Default implementation panics
 the application. So you should handle the leave gracefully here
 if you can. Here just return the error, the method was shown only
 to remind of this functionality.
 @param aError Error code for the leave happened in RunL.
*/
TInt CBuyTimer::RunError(TInt aError)
	{
	return aError;	
	}

/**
 Asynchronous event handler. Called when the timer fires.
 Update state and if necessary, ask another timer event.
 Call observers method to notify of the timer event.
*/
void CBuyTimer::RunL()
	{
	iTicksLeft--;
	if (iTicksLeft > 0)
		{
		iTimer.After(iStatus, 1000000); // Fire after one second
		SetActive();
		}
	iObserver->TimerFiredL(iTicksLeft);
	}


} // namespace

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: BuyTimer.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/