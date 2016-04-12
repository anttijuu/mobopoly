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

#ifndef __MOBOPOLY_CONTAINER1_H__
#define __MOBOPOLY_CONTAINER1_H__

#include <aknview.h>

namespace mobopoly 
{

class CBank;
class CMobopolyGameInfo;

/**
* Container control that contains the control for showing game state
* information.
* This container is contained within the CMobopolyGameView.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyGameContainer : public CCoeControl
	{
public: 

	// From CCoeControl
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	static CMobopolyGameContainer* NewL(const TRect& aRect);
	static CMobopolyGameContainer* NewLC(const TRect& aRect);
	/** Destructs the container and child controls with it. */
	~CMobopolyGameContainer();

	// from CoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;

private:
	void ConstructL(const TRect& aRect);

private:
	/** 
	* The infocontrol in this control, shows the game state data.
	* Is deleted by the container control when it is deleted.
	*/
	CMobopolyGameInfo	* iInfoControl;
	
	/** 
	 The game engine used to get information about the game state
	 and invoke functionality in the engine.
	 Is not deleted by the container control when it is deleted!
	*/
	CBank	* iBank;
	};

} // namespace

#endif // __MOBOPOLY_CONTAINER1_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyGameViewContainer.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/