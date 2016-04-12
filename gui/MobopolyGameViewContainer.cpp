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

#include <eiktxlbx.h>
#include <eiktxlbm.h>
#include <eikenv.h>
#include <eikappui.h>

#include "MobopolyGameViewContainer.h"
#include "MobopolyGameInfo.h"
#include "MobopolyDocument.h"
#include "Bank.h"

#include "Mobopoly.hrh"

namespace mobopoly 
{
	
/** 
* Factory method for creating new game view containers.
* @param aRect The area on the screen the control occupies.
* @returns The new container control.
*/
CMobopolyGameContainer* CMobopolyGameContainer::NewL(const TRect& aRect)
	{
	CMobopolyGameContainer* self = CMobopolyGameContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

/**
* Factory method for creating new game view containers.
* Puts the control container to the cleanup stack and returns.
* @param aRect The area on the screen the control occupies..
* @returns The new container control.
*/
CMobopolyGameContainer* CMobopolyGameContainer::NewLC(const TRect& aRect)
	{
	CMobopolyGameContainer* self = new (ELeave) CMobopolyGameContainer;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self; 
	}

/** 
* The 2nd phase constructor, info control.
* @param aRect The area occupied by this control.
*/
void CMobopolyGameContainer::ConstructL(const TRect& aRect)
	{
	CreateWindowL();		// Create a window for the control
	SetRect(aRect);		// Set it's area
	SetBlank();				// This control need not draw
	
	// Get a pointer to the model (engine; the Mobopoly bank).
	CMobopolyDocument * doc = static_cast<CMobopolyDocument*>(CEikonEnv::Static()->EikAppUi()->Document());
	iBank = doc->Bank();
		
	// Create the info control.
	iInfoControl = CMobopolyGameInfo::NewL(Rect(), iBank);
	// Info control is a component control of this compound control too.
	iInfoControl->SetContainerWindowL(*this);
	
	// Make view and components invisible until ViewActivated has been called
	SetComponentsToInheritVisibility();
	MakeVisible(ETrue);
	
	// Activate the control and all composite controls too.
	ActivateL();
	}

CMobopolyGameContainer::~CMobopolyGameContainer()
	{
	delete iInfoControl;
	}

/**	
* Required for compound controls, that contain other controls.
* @returns The number of contained controls.
*/
TInt CMobopolyGameContainer::CountComponentControls() const
	{
	return 1;
	}

/**
* Required for compound controls, that contain other controls.
* @param aIndex The index of the contained control.
* @returns A pointer to the contained control.
*/
CCoeControl* CMobopolyGameContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
		case 0:
			{
			return iInfoControl;
			}
		default:
			{
			break;
			}
		}
	return 0;
	}


/** 
* Called by the framework when user presses keys on the phone. Control has to
* be on the control stack to get these key events.
* @param aKeyEvent Information about the key event.
* @param aType The type of the key event.
* @returns Was the key event handled or not.
* @see CCoeControl::OfferKeyEventL
*/
TKeyResponse CMobopolyGameContainer::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

}

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameViewContainer.cpp,v $
* Revision 1.3  2006/02/15 13:23:23  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.2  2006/02/15 12:50:46  Antti
* Commented out unused parameters.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
*
*/