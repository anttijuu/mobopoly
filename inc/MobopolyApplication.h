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

#ifndef __MOBOPOLY_APPLICATION_H__
#define __MOBOPOLY_APPLICATION_H__

#include <aknapp.h>

namespace mobopoly 
{

/**
* The application class for the Mobopoly game.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/


class CMobopolyApplication : public CAknApplication
	{
public:

	// from CAknApplication
	TUid AppDllUid() const;

protected:
	// from CAknApplication
	CApaDocument* CreateDocumentL();
	};

} // namespace
#endif // __MOBOPOLY_APPLICATION_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyApplication.h,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/