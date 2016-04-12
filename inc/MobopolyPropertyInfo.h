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

#ifndef __MOBOPOLYPROPERTYINFO_H
#define __MOBOPOLYPROPERTYINFO_H

#include <coecntrl.h>

namespace mobopoly 
{

class CBank;


/**
 This class is NOT USED in the implementation given to the students.
 The class and contained controls can be used to implement optional
 features to the Mobopoly game.

 You could display here e.g. information about a selected property
 or the game board graphically, or whatever.
  
 @author Antti Juustila
 @version $Revision: 1.1 $
*/

class CMobopolyPropertyInfo : public CCoeControl
	{
public: 
	static CMobopolyPropertyInfo* NewL(const TRect& aRect, CBank * aBank);

	~CMobopolyPropertyInfo();

private:
	CMobopolyPropertyInfo(CBank * aBank);
	void ConstructL(const TRect& aRect);
	
	// From CCoeControl
	void Draw(const TRect & aRect) const;
	
private:
	/** 
	* The bank object needed in showing information about the state of the app.
	*/
	CBank				* iBank; // Does not own
	};

} //namespace 

#endif // __MOBOPOLYPROPERTYINFO_H

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyPropertyInfo.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/