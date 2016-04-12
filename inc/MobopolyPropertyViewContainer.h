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

#ifndef __MOBOPOLY_CONTAINER2_H__
#define __MOBOPOLY_CONTAINER2_H__

#include <aknview.h>
#include <eiklbo.h>
#include <coecobs.h>


namespace mobopoly
{

class CBank;
class CMobopolyPropertyInfo;

/**
 This class is NOT USED in the implementation given to the students.
 The class and contained controls can be used to implement optional
 features to the Mobopoly game.
 
 This is a container control that contains the property info control
 for showing recording information. Also contains the CBank object.
 This container is contained within the CMobopolyPropertyView.
 
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CMobopolyPropertyContainer : 	public CCoeControl
	{
public: 

	static CMobopolyPropertyContainer* NewL(const TRect& aRect);
	static CMobopolyPropertyContainer* NewLC(const TRect& aRect);
	
	~CMobopolyPropertyContainer();
	// From MCoeControl
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	// from CoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;

private:
	void ConstructL(const TRect& aRect);

private:
	/** 
	* The infocontrol in this control, shows the recording info and playing status.
	* Is deleted by the container control when it is deleted.
	*/
	CMobopolyPropertyInfo		* iInfoControl; // Owns
	
	/** 
	 The Bank, can be used to extract data to the view and invoke
	 functionality.
	 Is not deleted by the container control when it is deleted!
	*/
	CBank								* iBank;	// Does not own
	};

} // namespace

#endif // __MOBOPOLY_CONTAINER2_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyPropertyViewContainer.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/