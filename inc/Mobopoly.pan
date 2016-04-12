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

#ifndef __MOBOPOLY_PAN_
#define __MOBOPOLY_PAN_

/** Mobopoly application panic codes */
enum TMobopolyPanics 
	{
	EMobopolyNoCommandHandler = 1,
	EMobopolyInvalidArrayIndex,
	EMobopolyInvalidSwitchCaseValue
	};

/**
 The panic utility function that is called by the app when a 
 panic is needed.
 @param aReason The reason code for the panic.
*/

inline void Panic(TMobopolyPanics aReason)
	{
	_LIT(KApplicationName,"Mobopoly");
	User::Panic(KApplicationName, aReason);
	}

#endif 

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: Mobopoly.pan,v $
* Revision 1.1  2006/02/15 12:38:16  Antti
* Committing first public version of the example solution
*
*
*/