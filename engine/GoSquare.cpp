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

// GoSquare.cpp
//
// $Id: GoSquare.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include "GoSquare.h"
#include "PropertyVisitor.h"

namespace mobopoly 
{

/**
 Default constructor, calls CProperty default constructor.
*/
CGoSquare::CGoSquare() : CProperty()
	{
	}

/**
 Default desstructor, does nothing.
*/
CGoSquare::~CGoSquare()
	{
	}

/**
 Parses Go square's data from the parameter text string.
 See documentation on the structure of the data.
 @param aData The member data for the Go square.
*/
void CGoSquare::ParseL(const TDesC & aData)
	{
	TLex lexer(aData);
	
	TChar chr;
	lexer.SkipSpaceAndMark(); // Skip any whitespace at the beginning
	while (!lexer.Eos())
		{
		chr = lexer.Get();
		if (chr == ',') // items separated by commas
			{
			lexer.UnGet(); // Unget the comma
			TPtrC nextToken = lexer.MarkedToken(); // Get the string
			SetName(nextToken);
			
			lexer.SkipAndMark(1); // Skip over the comma
			TPtrC data = lexer.Remainder();
			TLex numLexer(data);
			TInt tmp;
			if (numLexer.Val(tmp) == KErrNone)
				{
				iGiveAwaySum = tmp;
				break;
				}
			}
		}
	if (Name().Length() == 0 || iGiveAwaySum == 0)
		{
		User::Leave(KErrCorrupt);
		}
	}

/**
 Implements the Visitor patter by accepting a property visitor
 to visit into a Go square.
 Calls visitor's VisitL with *this.
 @param aVisitor The visitor that is visiting the Go square.
*/
void CGoSquare::AcceptL(MPropertyVisitor & aVisitor)
	{
	aVisitor.VisitL(*this);
	}

/**
 Tells the sum that must be given to a player as she
 visits the Go square (either by staying or by passing by).
 @returns The sum to give to the player.
*/
TInt CGoSquare::SumToPlayer() const
	{
	return iGiveAwaySum;
	}

} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: GoSquare.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/