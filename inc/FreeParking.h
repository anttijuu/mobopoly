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

// FreeParking.h
//
// $Id: FreeParking.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __FREEPARKING_H
#define __FREEPARKING_H

#include <e32std.h>
#include <e32base.h>

#include "Property.h"

namespace mobopoly 
{

/**
 Freeparking property is a property that cannot be bought
 nor build on. Nothing happens when the player visits this property.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CFreeParking : public CProperty
	{
public:
		
	CFreeParking();
	virtual ~CFreeParking();
	
	virtual void ParseL(const TDesC & aData);

	virtual void AcceptL(MPropertyVisitor & aVisitor);
	
private:
	}; // CProperty

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: FreeParking.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/