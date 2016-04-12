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

// AppEngDll.cpp
// (c) Antti Juustila, 2006
//
// $Id: AppEngDll.cpp,v 1.1 2006/02/15 12:38:10 Antti Exp $

#include <e32std.h>

// requirement for E32 DLLs
EXPORT_C TInt E32Dll(TDllReason)
	{
	return 0;
	}


/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: AppEngDll.cpp,v $
* Revision 1.1  2006/02/15 12:38:10  Antti
* Committing first public version of the example solution
*
*
*/