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

// Property.h
//
// $Id: Property.h,v 1.1 2006/02/15 12:38:20 Antti Exp $

#ifndef __PROPERTY_H
#define __PROPERTY_H

#include <e32std.h>
#include <e32base.h>


#include "MobopolyDefines.h"

namespace mobopoly 
{

class MPropertyVisitor;

/**
 CProperty class is an abstract base class for all the game squares
 in the Mobopoly game.

 Properties form a circular list. The player objects are then traversed
 via the list as the dices are thrown. Player visits each property
 according to the property's type implementing the Visitor design pattern.
 Since there are different subtypes of properties and also players, and the
 AcceptL/VisitL methods are virtual, visiting behaves differently (polymorphically)
 according to the subtype of the both visiting and visited object.
 
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CProperty : public CBase
	{
public:
	CProperty();
	virtual ~CProperty();

	virtual void ParseL(const TDesC & aData) = 0;
	
	const TDesC & Name() const;
	void SetName(const TDesC & aName);
	
	CProperty * Next();
	void SetNext(CProperty & aNext);
	
	virtual void AcceptL(MPropertyVisitor & aVisitor) = 0;
	
private:	
	/** The name of the property. */
	TBufC<KMaxPropertyNameLen> iName;
	
	/** Pointer to the next property. Properties form a circular list. */
	CProperty * iNext;
	}; // CProperty

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Property.h,v $
* Revision 1.1  2006/02/15 12:38:20  Antti
* Committing first public version of the example solution
*
*
*/