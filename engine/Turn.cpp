/*Copyright   Jan 27, 2006 Antti Juustila ----------------------

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

// Turn.cpp
//
// $Id: Turn.cpp,v 1.2 2006/02/15 13:25:36 Antti Exp $

#include <e32math.h>

#include "Turn.h"


namespace mobopoly 
{


/** 
 In constructor, take the seed number for the random number generator.
*/
CTurn::CTurn() : CBase()
	{
	TTime now;
	now.HomeTime();
	iSeed = now.Int64();
	}
   
CTurn::~CTurn()
	{
	}

/**
 Get two random numbers (the two dices). Could have been implemented simply
 just to return one integer, but this way it really "looks like" in the code
 that you have two dices ;-)
 @param aFirst Number of the first dice.
 @param aSecond Number of the second dice.
*/
void CTurn::ThrowDices(TInt & aFirst, TInt & aSecond)
	{
	aFirst = 1 + (Math::Rand(iSeed) % 5);
	aSecond = 1 + (Math::Rand(iSeed) % 5);
	}
	

} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Turn.cpp,v $
* Revision 1.2  2006/02/15 13:25:36  Antti
* Fixed doxygen comments.
*
* Revision 1.1  2006/02/15 12:38:12  Antti
* Committing first public version of the example solution
*
*
*
*/