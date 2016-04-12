/*Copyright   Jan 26, 2006 Antti Juustila ----------------------

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

// Turn.h
//
// $Id: Turn.h,v 1.1 2006/02/15 12:38:21 Antti Exp $

#ifndef __MOBOPOLYTURN_H
#define __MOBOPOLYTURN_H

#include <e32std.h>
#include <e32base.h>


/**
* The namespace <b>Mobopoly</b> contains all the classes that form the 
* exercise work of the Mobile Systems Programming course for the Spring 2006.<p>
* Some of the classes are given already implemented to the students. Some of
* the classes are only given partially: students will get header files with class definitions.
* The class definitions contain only the public interface of the classes.<p>
* Students are required to implement the public interface and add protected and private
* properties (both methods and data) to the classes so that the functionality of the
* application fulfills the requirements for the exercise work.<p>
* Some of the features are optional. See the more detailed description from
* http://www.tol.oulu.fi/kurssit/mobo/
*/

namespace mobopoly 
{


/**
 The turn class is responsible for providing services related to switching turns.
 The turn object is passed from one Mobopoly to another as the turn switches. The Mobopoly
 uses the turn object to throw dices and see, how many steps the player can move ahead.
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CTurn : public CBase 
	{
public:
   CTurn();
   
	virtual ~CTurn();

	void ThrowDices(TInt & aFirst, TInt & aSecond);
	
private:

	/**
	 The value of the first dice thrown. Could do with one member variable,
	 but this is "more realistic". */
	TInt iFirstDiceValue;
	/**
	 The value of the second dice thrown. Could do with one member variable,
	 but this is "more realistic". */
	TInt iSecondDiceValue;
	
	/** The seed number for the random number generator, taken from time. */
	TInt64 iSeed;
	}; // CTurn

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Turn.h,v $
* Revision 1.1  2006/02/15 12:38:21  Antti
* Committing first public version of the example solution
*
*
*
*/