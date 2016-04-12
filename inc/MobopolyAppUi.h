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

#ifndef __MOBOPOLY_APPUI_H__
#define __MOBOPOLY_APPUI_H__

#include <aknViewAppUi.h>

#include "Bank.h"

namespace mobopoly 
{

class CMobopolyGameView;
class CMobopolyPropertyView;

/** 
* The application ui class constructs the application views and
* handles any commands that the views do not handle.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyAppUi : public CAknViewAppUi
	{
public:

	void ConstructL();
	void HandleCommandL(TInt aCommand);

private:

	/** 
	 The game view, the default view for the application
	 showing the game state.
	*/
	CMobopolyGameView* iAppView1;
	
	/**
	 The propety view, that is NOT implemented, does nothing
	 and cannot be switched to currently. You can use this to
	 implement your own optional functionality.
	*/
	CMobopolyPropertyView* iAppView2;

	/** 
	* The engine of the application; Mobopoly game bank.
	*/
	CBank * iBank;
	};

} // namespace

#endif // __MOBOPOLY_APPUI_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyAppUi.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*
*/