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
#include <eikmenup.h>

#include <Mobopoly.rsg>

#include "Bank.h"

#include "MobopolyDocument.h"
#include "MobopolyGameView.h"
#include "MobopolyGameViewContainer.h"

#include "Mobopoly.hrh"

namespace mobopoly 
{
	
/** 
* The factory method for creating new game view.
* @returns The new game view object.
*/
CMobopolyGameView * CMobopolyGameView::NewL()
    {
    CMobopolyGameView * self = CMobopolyGameView::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

/** 
* The factory method for creating new vame view.
* Places the view to the cleanup stack and returns.
* @returns The new view object.
*/
CMobopolyGameView * CMobopolyGameView::NewLC()
    {
    CMobopolyGameView * self = new (ELeave) CMobopolyGameView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

/** 
* Default constructor for initializing non-leaving items.
*/
CMobopolyGameView::CMobopolyGameView()
    {
    // no implementation required
    }

/** 
* Destroys the view.
*/
CMobopolyGameView::~CMobopolyGameView()
    {
    //  DoDeactivate is called by the base class destructor
    }

/** 
* The 2nd phase constructor for initializing leaving items.
*/
void CMobopolyGameView::ConstructL()
    {
    BaseConstructL(R_MOBOPOLY_VIEW_GAMEVIEW);
    }


/**
* Returns the view id used in view switching.
*/
TUid CMobopolyGameView::Id() const
    {
    return TUid::Uid(EGameViewId);
    }

/** 
* Called when the view is activated. Initialize the view contents here.
* @param aPrevViewId The id of the view that was active before this view.
* @param aCustomMessageId Not used here.
* @param aCustomMessage Not used here.
*/
void CMobopolyGameView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    ASSERT(iContainer == NULL);
    // Create the container when the view is activated.
    iContainer = CMobopolyGameContainer::NewL(ClientRect());
    // Let the control handle keyboard events.
    AppUi()->AddToStackL(iContainer);
    }

	/** Called by the GUI framework when the view is deactivated. Release resources here. */
void CMobopolyGameView::DoDeactivate()
    {
    if (iContainer)
        {
        // No keyboard events to this control anymore.
        AppUi()->RemoveFromStack(iContainer);
        delete iContainer;
        iContainer = 0;
        }
    }

/** 
* Handles the menu commands specific to this view.
* @param aCommand The command id.
*/
void CMobopolyGameView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		default:
			{
			AppUi()->HandleCommandL(aCommand);
			}    
		}
	}


void CMobopolyGameView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	if (aResourceId == R_MOBOPOLY_MENU_GAMEVIEW)
		{
		// Get a pointer to the model (engine; the Mobopoly).
		CMobopolyDocument * doc = static_cast<CMobopolyDocument*>(CEikonEnv::Static()->EikAppUi()->Document());
		CBank * bank = doc->Bank();
		if (!bank->HumanPlayerCanThrow() || bank->HumanPlayerCanBuy())
			{
			aMenuPane->SetItemDimmed(EThrowDices, ETrue);
			}
		if (!bank->HumanPlayerCanBuy())
			{
			aMenuPane->SetItemDimmed(EBuyProperty, ETrue);
			}
		if (bank->GameIsActive())
			{
			aMenuPane->SetItemDimmed(EStartGame, ETrue);
			}
		}
	}


} // namespace

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameView.cpp,v $
* Revision 1.2  2006/02/15 13:23:24  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
*
*/