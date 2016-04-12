/*Copyright   Jan 30, 2006 Antti Juustila ----------------------

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

// MobopolyDefines.h
//
// $Id: MobopolyDefines.h,v 1.1 2006/02/15 12:38:17 Antti Exp $
//
// @author Antti Juustila
// @version $Revision: 1.1 $

#ifndef __MOBOPOLYDEFINES_H
#define __MOBOPOLYDEFINES_H

/**
 The Unique Application Identifier.
 Must match the UID in the MMP file as well as the
 aif resource file (rss) and installation package file (pkg).
*/
#define KMobopolyAppUID 0x017ac299

// You can use these constant values when defining
// descriptors for holding text data. For example,
// a buffer descriptor for Mobopoly's name (30 chars) would 
// look like this: TBuf<KMaxMobopolyNameLen> nameBuf.

/** Max length for the name of the player. */
#define KMaxPlayerNameLen 20
/** Max length for the name of the property. */
#define KMaxPropertyNameLen 20
/** Max length for the notification message in the UI. */
#define KMaxUINotificationMsgLen 30
/** Max messages to store in the message buffer. */
#define KUINotificationMsgBufSize 3

#endif

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyDefines.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*
*/