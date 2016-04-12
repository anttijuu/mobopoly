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

#include "MobopolyApplication.h"

/**
* Entry point function for a Symbian DLL.
*/
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
    {
    return KErrNone;
    }

/**
* Function called by application framework when
* the application dll is loaded. This begins
* the app startup process.
*/
EXPORT_C CApaApplication* NewApplication()
    {
    using namespace mobopoly;
    return new CMobopolyApplication;
    }


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyAppDll.cpp,v $
* Revision 1.1  2006/02/15 12:38:12  Antti
* Committing first public version of the example solution
*
*
*
*/