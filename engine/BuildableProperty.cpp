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

// BuildableProperty.cpp
//
// $Id: BuildableProperty.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include "BuildableProperty.h"
#include "PropertyVisitor.h"

namespace mobopoly 
{


/** 
 Default constructor, calls property's default one.
*/
CBuildableProperty::CBuildableProperty() : CProperty()
	{
	iHouseCount = KNoHouses;
	}

/**
 Destructor, does nothing.
*/	
CBuildableProperty::~CBuildableProperty()
	{
	}

/**
 Parses the buildable propertie's member data values from the
 string. See the documentation for the description of the data structure.
 @see TLex
 @param aData The property's data in a string.
*/
void CBuildableProperty::ParseL(const TDesC & aData)
	{
	TLex lexer(aData);
	
	TChar chr;
	TInt commaCount = 0;
	lexer.SkipSpaceAndMark(); // Skip any whitespace at the beginning
	while (!lexer.Eos())
		{
		chr = lexer.Get();
		if (chr == ',' || chr == 0) // items separated by commas
			{
			commaCount++;
			switch (commaCount)
				{
				case 1: // Name
					{
					lexer.UnGet(); // Unget the comma
					TPtrC nextToken = lexer.MarkedToken(); // Get the string
					SetName(nextToken);
					lexer.SkipAndMark(1); // Skip over the comma
					break;
					}

				case 2: // Price
					{
					lexer.UnGet(); // Unget the comma
					TPtrC data = lexer.MarkedToken();
					TLex numLexer(data);
					TInt tmp;
					if (numLexer.Val(tmp) == KErrNone)
						{
						iPrice = tmp;
						}
					lexer.SkipAndMark(1); // Skip over the comma
					break;
					}

				case 3: // Rent
					{
					lexer.UnGet(); // Unget the comma
					TPtrC data = lexer.MarkedToken();
					TLex numLexer(data);
					TInt tmp;
					if (numLexer.Val(tmp) == KErrNone)
						{
						iRents[KPlainRentIndex] = tmp;
						}
					lexer.SkipAndMark(1); // Skip over the comma
					break;
					}
				
				case 4: // Houseprice
					{
					lexer.UnGet(); // Unget the comma
					TPtrC data = lexer.MarkedToken();
					TLex numLexer(data);
					TInt tmp;
					if (numLexer.Val(tmp) == KErrNone)
						{
						iHousePrice = tmp;
						}
					lexer.SkipAndMark(1); // Skip over the comma

					// Get the last bit, rent with house
					numLexer.Assign(lexer.Remainder());
					if (numLexer.Val(tmp) == KErrNone)
						{
						iRents[KHouseRentIndex] = tmp;
						break;
						}
					break;
					}
				}
			}
		}
	if (Name().Length() == 0 || iPrice == 0 || iHousePrice == 0 ||
		 iRents[KPlainRentIndex] == 0 || iRents[KHouseRentIndex] == 0)
		{
		User::Leave(KErrCorrupt);
		}
	}

/**
 Implements the Visitor pattern by accepting the visitors.
 @param aVisitor The visitor.
*/
void CBuildableProperty::AcceptL(MPropertyVisitor & aVisitor)
	{
	aVisitor.VisitL(*this);
	}

/**
 Tells the price of the property.
 @returns The property's price.
*/	
TInt CBuildableProperty::Price() const
	{
	return iPrice;
	}

/**
 Tells the rent of the house, depending on the amount of houses
 or hotel build on the property.
 @returns The rent.
*/	
TInt CBuildableProperty::Rent() const
	{
	if (iHouseCount == KNoHouses)
		return iRents[KPlainRentIndex];
	else
		return iRents[KHouseRentIndex] * iHouseCount;
	}
/**
 Tells the house's price for the property.
 @returns The price of the house.
*/
TInt CBuildableProperty::HousePrice() const
	{
	return iHousePrice;
	}

/**
 Tells if the specified amount of houses could be build on the property.
 @param aNumberOfHousesToBuild The number of houses to build.
 @returns Can those houses be build (ETrue) or not.
*/
TBool CBuildableProperty::CanBuild(TInt aNumberOfHousesToBuild) const
	{
	if (iHouseCount < KHotel)
		{
		if (aNumberOfHousesToBuild == KHotel)
			{
			if (iHouseCount != KFourHouses)
				{
				return EFalse;
				}
			else
				{
				return ETrue;
				}
			}
		else
			{
			if ((aNumberOfHousesToBuild + iHouseCount) < KFourHouses)
				{
				return ETrue;
				}
			}
		}
	return EFalse;
	}

/**
 Builds a specified number of houses on the property.
 @param aNumberOfHousesToBuild Number of houses to build.
 @returns Were the houses build (ETrue) or not.
*/
TBool CBuildableProperty::Build(TInt aNumberOfHousesToBuild)
	{
	if (CanBuild(aNumberOfHousesToBuild))
		{
		iHouseCount += aNumberOfHousesToBuild;
		return ETrue;
		}
	return EFalse;
	}

/**
 Tells the count of houses on the property.
 @returns The number of build houses.
*/
TInt CBuildableProperty::HouseCount() const
	{
	return iHouseCount;
	}

/**
 Sets the owner for the property.
 @param aPlayer The player who owns the property now.
*/
void CBuildableProperty::SetOwner(CPlayer & aPlayer)
	{
	iOwner = &aPlayer;
	}
	
/**
 Returns the owner of the property, const version.
 @returns The player who owns the property.
*/
const CPlayer * CBuildableProperty::Owner() const
	{
	return iOwner;
	}

/**
 Returns the owner of the property, non const version.
 @returns The player who owns the property.
*/
CPlayer * CBuildableProperty::Owner()
	{
	return iOwner;
	}
	
} // namespace

	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: BuildableProperty.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/