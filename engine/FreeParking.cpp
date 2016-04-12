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

// FreeParking.cpp
//
// $Id: FreeParking.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include <e32std.h>
#include <e32base.h>

#include "FreeParking.h"
#include "PropertyVisitor.h"

namespace mobopoly 
{

/**
 Default constructor, calls property's default c'tor.
*/
CFreeParking::CFreeParking() : CProperty()
	{
	
	}

/**
 Destructor, does basically nothing.
*/

CFreeParking::~CFreeParking()
	{
	
	}

/**
 Parses data from the string to get freeparking square properties.
 See documentation on details on the string structure.
 @param aData Member data for the freeparking square.
*/
void CFreeParking::ParseL(const TDesC & aData)
	{
	SetName(aData);
	if (Name().Length() == 0)
		{
		User::Leave(KErrCorrupt);
		}
	}

/**
 Implements the visitor pattern, accepts the visitor by
 calling VisitL.
 @param aVisitor The visitor.
*/
void CFreeParking::AcceptL(MPropertyVisitor & aVisitor)
	{
	aVisitor.VisitL(*this);
	}
	

} // namespace

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: FreeParking.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/