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

#ifndef __MOBOPOLY_VIEW1_H__
#define __MOBOPOLY_VIEW1_H__


#include <aknview.h>

namespace mobopoly 
{

class CMobopolyGameContainer;

/**
* This class defines the game view. Game view contains controls
* that show and enable the users to manipulate the game state.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyGameView : public CAknView
	{
public:

	static CMobopolyGameView* NewL();
	static CMobopolyGameView* NewLC();

	~CMobopolyGameView();

	TUid Id() const;

	void HandleCommandL(TInt aCommand);

	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();

	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

private:

	CMobopolyGameView();

	void ConstructL();

private:

	/** 
	* The container control, containing the subcontrols of the view.
	*/
	CMobopolyGameContainer* iContainer;
	};

} // namespace

#endif // __MOBOPOLY_VIEW1_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameView.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/