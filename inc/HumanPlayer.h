/*Copyright   Feb 1, 2006 Antti Juustila ----------------------

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

// HumanPlayer.h
//
// $Id: HumanPlayer.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __MOBOPOLYHUMANPLAYER_H
#define __MOBOPOLYHUMANPLAYER_H

#include "Player.h"

namespace mobopoly 
{

/**
 The HumanPlayer class represents the human player in the game.
 Human player is a subclass of CPlayer. CPlayer is the software player
 that plays automagically (throws dices, buys properties, etc.).
 
 Human player asks the user to throw dices and whether to buy a
 property or not.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CHumanPlayer : public CPlayer
	{
public:
	CHumanPlayer();
	virtual ~CHumanPlayer();

	virtual void TakeTurnL(CTurn & aTurn);
	
protected:
	// See docs in CPlayer header for these methods.
	virtual void NotifyRentPaidL(TInt aPrice);
	virtual void NotifyPropertyBoughtL(TInt aPrice);
	virtual void DoBuyPropertyL(CBuildableProperty & aObject);
	
private:
	/**
	 Has the user already been asked if she wants to buy the property.
	 See implementation of DoBuyPropertyL. */
	TBool iInterestToBuyAsked;
	}; // CHumanPlayer

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: HumanPlayer.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/