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
// $Id: BuildableProperty.h,v 1.1 2006/02/15 12:38:16 Antti Exp $

#ifndef __BUILDABLEPROPERTY_H
#define __BUILDABLEPROPERTY_H

#include <e32std.h>
#include <e32base.h>

#include "Property.h"

namespace mobopoly 
{

class CPlayer;

const TInt KNoHouses = 0;
const TInt KOneHouse = 1;
const TInt KTwoHouses = 2;
const TInt KThreeHouses = 3;
const TInt KFourHouses = 4;
const TInt KHotel = 5;

const TInt KPlainRentIndex = 0;
const TInt KHouseRentIndex = 1;

/**
 Buildable property is the most complex propety in the game.
 They can be bought, rent can be taken from players visiting them,
 and houses and hotels can be built on them.

 @author Antti Juustila
 @version $Revision: 1.1 $
*/


class CBuildableProperty : public CProperty
	{
public:

	CBuildableProperty();
	virtual ~CBuildableProperty();
	
	virtual void ParseL(const TDesC & aData);
	
	virtual void AcceptL(MPropertyVisitor & aVisitor);

	TInt Price() const;
	TInt Rent() const;
	TBool CanBuild(TInt aNumberOfHousesToBuild) const;
	TBool Build(TInt aNumberOfHousesToBuild);

	TInt HousePrice() const;	

	TInt HouseCount() const;
		
	const CPlayer * Owner() const;
	CPlayer * Owner();
	void SetOwner(CPlayer & aPlayer);
	
private:
	/** The price of the property.*/
	TInt iPrice;
	/** The price of a house or hotel for the property.*/
	TInt iHousePrice;
	/** The count of houses built on the property. */
	TInt iHouseCount;
	
	/**
	 The rents taken from visitors. First rent is the rent
	 without houses, the second one is the rent taken if one house
	 is built on the property. If there are e.g. three houses, this
	 sum is multiplied by three. When a hotel is build, the sum is
	 multiplied by five.
	 */
	TInt iRents[2];
	
	/** The owner of the property, null if no owner. */
	CPlayer * iOwner;
	
	}; // CBuildableProperty

} // namespace


#endif
	
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: BuildableProperty.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/