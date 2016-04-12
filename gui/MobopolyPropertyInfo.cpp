/*Copyright   Jan 31, 2006 Antti Juustila ----------------------

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

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>

#include <Mobopoly.rsg>

#include "MobopolyPropertyInfo.h"
#include "Bank.h"
#include "MobopolyDefines.h"

namespace mobopoly
{
	
/** 
* Factory method for creating the info control.
* @param aRect The area the control occupies.
* @param aBank The object for getting game state information
* @returns The property info control.
*/
CMobopolyPropertyInfo* CMobopolyPropertyInfo::NewL(const TRect& aRect, CBank * aBank)
	{
	CMobopolyPropertyInfo* self = new (ELeave) CMobopolyPropertyInfo(aBank);
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop(self);
	return self;
	}

/** 
* 2nd phase constructor for creating the info control.
* @param aRect The area the control occupies.
*/
void CMobopolyPropertyInfo::ConstructL(const TRect& aRect)
	{
	SetRect(aRect);
	}

/** 
* Constructor for initializing non-leaving items.
* @param aBank The Mobopoly used for showing the information.
*/
CMobopolyPropertyInfo::CMobopolyPropertyInfo(CBank * aBank) : iBank(aBank)
	{
	// Empty
	}
	
/** 
* Destructor for the info control.
* Stop the animator, if it has been created, and delete it.
*/
CMobopolyPropertyInfo::~CMobopolyPropertyInfo()
	{
	}
	
/** 
* Draws the control to the screen.
* @param aRect The area that needs to be drawn.
*/
void CMobopolyPropertyInfo::Draw(const TRect & aRect) const
	{
	CWindowGc & gc = SystemGc();
	gc.SetClippingRect(aRect);
	const CFont * font = CEikonEnv::Static()->DenseFont();
	gc.UseFont(font);
	TRect rect(Rect());
	rect.Shrink(2,2);
	gc.DrawLine(rect.iTl, TPoint(rect.iBr.iX, rect.iTl.iY));
	gc.CancelClippingRect();
	}


} // namespace

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyPropertyInfo.cpp,v $
* Revision 1.2  2006/02/15 13:23:23  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
*
*/