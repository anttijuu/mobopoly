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

// PropertyVisitor.h
//
// $Id: PropertyVisitor.h,v 1.1 2006/02/15 12:38:20 Antti Exp $

#ifndef __PROPERTYVISITOR_H
#define __PROPERTYVISITOR_H

#include <e32std.h>


namespace mobopoly 
{

class CFreeParking;
class CBuildableProperty;
class CGoSquare;

/**
 This interface defines the Visitor pattern's interface for objects
 that can visit other objects.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class MPropertyVisitor
	{
public:
	MPropertyVisitor();
	virtual ~MPropertyVisitor();

	/** Visit CFreeParking objects. */
	virtual void VisitL(CFreeParking & aObject)	= 0;
	/** Visit CBuildableProperty objects. */
	virtual void VisitL(CBuildableProperty & aObject)	= 0;
	/** Visit CGoSquare objects. */
	virtual void VisitL(CGoSquare & aObject)	= 0;

	
	}; // MPropertyVisitor

} // namespace

#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: PropertyVisitor.h,v $
* Revision 1.1  2006/02/15 12:38:20  Antti
* Committing first public version of the example solution
*
*
*/