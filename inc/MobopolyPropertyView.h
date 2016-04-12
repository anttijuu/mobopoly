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

#ifndef __MOBOPOLY_VIEW2_H__
#define __MOBOPOLY_VIEW2_H__


#include <aknview.h>

namespace mobopoly 
{

class CMobopolyPropertyContainer;

/**
 This class is NOT USED in the implementation given to the students.
 The class and contained controls can be used to implement optional
 features to the Mobopoly game.
 
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyPropertyView : public CAknView
	{
public:

	static CMobopolyPropertyView* NewL();
	static CMobopolyPropertyView* NewLC();

	~CMobopolyPropertyView();

	TUid Id() const;

	void HandleCommandL(TInt aCommand);

	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();

private:

	CMobopolyPropertyView();
	void ConstructL();

private:

	/** 
	* The container control, containing the subcontrols of the view.
	*/
	CMobopolyPropertyContainer* iContainer;
	};

} // namespace 

#endif

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyPropertyView.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/