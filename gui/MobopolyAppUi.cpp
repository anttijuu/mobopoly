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

#include <e32std.h>
#include <eikdialg.h>
#include <avkon.hrh>
#include <akndialog.h>

#include <Mobopoly.rsg>

#include "Mobopoly.pan"
#include "MobopolyAppUi.h"
#include "MobopolyDocument.h"
#include "MobopolyGameView.h"
#include "MobopolyPropertyView.h"
#include "Mobopoly.hrh"

#include "Bank.h"

namespace mobopoly 
{


/**
* Second phase constructor function. Called by the application
* framework when the application is initialized.
*/
void CMobopolyAppUi::ConstructL()
	{
	BaseConstructL(); // Must call before doing anything else

	// Get a pointer to the model.
	CMobopolyDocument * doc = static_cast<CMobopolyDocument*>(Document());
	iBank = doc->Bank();
	
	// Create the game view.
	CMobopolyGameView * view1 = CMobopolyGameView::NewLC();
	AddViewL(view1); // transfer ownership to base class 
	CleanupStack::Pop(); // view1
	iAppView1 = view1;
	
	// Create the property view.
	CMobopolyPropertyView * view2 = CMobopolyPropertyView::NewLC();
	AddViewL(view2); // transfer ownership to base class 
	CleanupStack::Pop(); // view2
	iAppView2 = view2;

	// Playlist view is the default view.
	SetDefaultViewL(*iAppView1);
	}

/**
* Handles the commands user has selected. The command is first
* offered to the active view, and if it is not handling it, the
* view can then offer the command to the ui object.
* @param aCommand The command to handle.
*/
void CMobopolyAppUi::HandleCommandL(TInt aCommand)
	{
	switch(aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit: 
			{
			Exit();
			break;
			}

		case EStartGame:
			{
			iBank->StartGameL();
			break;
			}

		case EThrowDices:
			{
			iBank->HumanPlayerThrowsL();
			break;
			}
			
		case EBuyProperty:
			{
			iBank->HumanPlayerBuysPropertyL();
			break;
			}
			
		case EBuildHouse:
			{
			// TODO
			break;
			}
		case ESwitchToPropertyView:
			{
			ActivateLocalViewL(TUid::Uid(EPropertyViewId));
			break;
			}

		default:
			{
			Panic(EMobopolyNoCommandHandler);
			break;
			}
		}
	}

} // namespace

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyAppUi.cpp,v $
* Revision 1.1  2006/02/15 12:38:12  Antti
* Committing first public version of the example solution
*
*
*/