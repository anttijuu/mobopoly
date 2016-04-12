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

// GoSquare.h
//
// $Id: GoSquare.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __GOSQUARE_H
#define __GOSQUARE_H

#include <e32std.h>
#include <e32base.h>

#include "Property.h"

namespace mobopoly 
{

/**
 The Go square property class.
 This property cannot be bought, you cannot build on it.
 As the player visits the property, she will get a certain
 sum of money even she is not stopping on the property.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CGoSquare : public CProperty
	{
public:
	CGoSquare();
	virtual ~CGoSquare();
	
	virtual void ParseL(const TDesC & aData);
	
	virtual void AcceptL(MPropertyVisitor & aVisitor);
	
	TInt SumToPlayer() const;

private:
	/** The sum to give away to the player.  */
	TInt iGiveAwaySum;
	}; // CGoSquare

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: GoSquare.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/