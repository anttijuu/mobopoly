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

#ifndef __MOBOPOLY_DOCUMENT_H__
#define __MOBOPOLY_DOCUMENT_H__

#include <akndoc.h>

// Forward declaration
class CEikApplication;

namespace mobopoly 
{

class CMobopolyAppUi;
class CBank;

/**
* The document class for the Mobopoly game.
* Document creates the model (the CBank),
* and also creates the application's UI object when the application
* is launched.
* @author Antti Juustila
* @version $Revision: 1.1 $
*/

class CMobopolyDocument : public CAknDocument
	{
public:

	static CMobopolyDocument* NewL(CEikApplication& aApp);
	static CMobopolyDocument* NewLC(CEikApplication& aApp);

	~CMobopolyDocument();

	void NewDocumentL();

	CBank * Bank();

public:
	// from CAknDocument
	CEikAppUi* CreateAppUiL();

private:
	void ConstructL();
	CMobopolyDocument(CEikApplication& aApp);
	void ResetModelL();

private:
	/**
	* The application model, alias engine; the Mobopoly game engine.
	* This must be allocated and destroyed by the document.
	*/
	CBank * iBank;
	};

} // namespace 

#endif // __MOBOPOLY_DOCUMENT_H__

/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyDocument.h,v $
* Revision 1.1  2006/02/15 12:38:17  Antti
* Committing first public version of the example solution
*
*
*/