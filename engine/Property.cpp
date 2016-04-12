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

// Property.cpp
//
// $Id: Property.cpp,v 1.1 2006/02/15 12:38:11 Antti Exp $

#include "Property.h"

namespace mobopoly 
{

/**
 Constructor, does basically nothing more than calls CBase
 constructor (which is very important).
*/
CProperty::CProperty() : CBase()
	{
	
	}

/**
 Destructor, does basically nothing.
*/	
CProperty::~CProperty()
	{
	}

/**
 Gets the name of the property.
 @returns Name of the property.
*/
const TDesC & CProperty::Name() const
	{
	return iName;
	}

/**
 Sets the name of the property.
 @param aName New name for the property.
*/
void CProperty::SetName(const TDesC & aName)
	{
	iName = aName;
	}

/**
 Properties are linked in a circular linked list. This enables
 the player objects to move in the gameboard formed by properties
 in a circular list easily.
 @returns Returns the pointer to the next property.
*/
CProperty * CProperty::Next()
	{
	return iNext;
	}

/** 
 Sets the next property for this property object.
 @param aNext The next property in the list.
*/
void CProperty::SetNext(CProperty & aNext)
	{
	iNext = &aNext;
	}


} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Property.cpp,v $
* Revision 1.1  2006/02/15 12:38:11  Antti
* Committing first public version of the example solution
*
*
*/