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

#include "MobopolyDocument.h"
#include "MobopolyApplication.h"
#include "MobopolyDefines.h"

namespace mobopoly 
{
	
/** 
* Creates the document object and returns it to
* the application framework.
*/
CApaDocument* CMobopolyApplication::CreateDocumentL()
    {  
    // Create an MultiViews document, and return a pointer to it
    CApaDocument* document = CMobopolyDocument::NewL(*this);
    return document;
    }
    
/**
* Provides the application UID to the system.
* @returns The UID of the application.
*/
TUid CMobopolyApplication::AppDllUid() const
    {
    // Return the UID for the MultiViews application
    return TUid::Uid(KMobopolyAppUID);
    }

}

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyApplication.cpp,v $
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
* Revision 1.1.1.1  2005/03/01 18:27:34  Antti
* Importing first public release.
*
*
*/