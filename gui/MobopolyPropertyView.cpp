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

#include <aknviewappui.h>
#include <avkon.hrh>
#include <aknconsts.h>
#include <aknnotewrappers.h>
#include <eikmenup.h>

#include <Mobopoly.rsg>

#include "MobopolyDocument.h"
#include "MobopolyPropertyView.h"
#include "MobopolyPropertyViewContainer.h"

#include "Bank.h"

#include "Mobopoly.hrh"

namespace mobopoly 
{
	
/** 
* The factory method for creating new property views.
* @returns The new recording view object.
*/
CMobopolyPropertyView* CMobopolyPropertyView::NewL()
	{
	CMobopolyPropertyView* self = CMobopolyPropertyView::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

/** 
* The factory method for creating new property views.
* Places the view to the cleanup stack and returns.
* @returns The new property view object.
*/
CMobopolyPropertyView* CMobopolyPropertyView::NewLC()
	{
	CMobopolyPropertyView* self = new (ELeave) CMobopolyPropertyView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/** 
* Default constructor for initializing non-leaving items. 
*/
CMobopolyPropertyView::CMobopolyPropertyView()
	{
	// no implementation required
	}

/** 
* Destroys the view and objects within.
*/
CMobopolyPropertyView::~CMobopolyPropertyView()
	{
	//  DoDeactivate is called by the base class destructor
	}

/** 
* The 2nd phase constructor for initializing leaving items.
*/
void CMobopolyPropertyView::ConstructL()
	{
	BaseConstructL(R_MOBOPOLY_VIEW_PROPERTYVIEW);
	}


/** 
* Returns the view id used in view switching.
* @returns The view id.
*/
TUid CMobopolyPropertyView::Id() const
	{
	return TUid::Uid(EPropertyViewId);
	}

/** 
* Called when the view is activated. Initialize the view contents here.
* @param aPrevViewId The id of the view that was active before this view.
* @param aCustomMessageId Not used here.
* @param aCustomMessage Not used here. */
void CMobopolyPropertyView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
											TUid /*aCustomMessageId*/,
											const TDesC8& /*aCustomMessage*/)
	{
	ASSERT(iContainer == NULL);
	iContainer = CMobopolyPropertyContainer::NewL(ClientRect());
	AppUi()->AddToStackL(iContainer);
	}

/** 
* Called by the GUI framework when the view is deactivated. Release resources here.
*/
void CMobopolyPropertyView::DoDeactivate()
	{
	if (iContainer)
		{
		AppUi()->RemoveFromStack(iContainer);
		delete iContainer;
		iContainer = 0;
		}
	}

/** 
* Handles the menu commands specific to this view.
* @param aCommand The command id.
*/
void CMobopolyPropertyView::HandleCommandL(TInt aCommand)
	{   
	if (aCommand == EAknSoftkeyBack)
		{
		AppUi()->ActivateLocalViewL(TUid::Uid(EGameViewId));
		return;
		}

	switch (aCommand)
		{
			
		default:
			{
			AppUi()->HandleCommandL(aCommand);
			}
		}
	}

}

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyPropertyView.cpp,v $
* Revision 1.2  2006/02/15 13:23:23  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
*
*/