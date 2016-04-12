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

#include "MobopolyAppUi.h"
#include "MobopolyDocument.h"

#include "MobopolyDefines.h"

#include "Bank.h"

namespace mobopoly 
{


/** 
* Factory method for creating the document object.
* @param aApp The application object, passed to the CEikDocument.
* @returns The document object.
*/
CMobopolyDocument* CMobopolyDocument::NewL(CEikApplication& aApp)
	{
	CMobopolyDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

/** 
* Factory method for creating the document object.
* Puts the doc object to the cleanup stack and returns it.
* @param aApp The application object, passed to the CEikDocument.
* @returns The document object.
*/
CMobopolyDocument* CMobopolyDocument::NewLC(CEikApplication& aApp)
	{
	CMobopolyDocument* self = new (ELeave) CMobopolyDocument(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/** 
* 2nd phase constructor for the document.
* The application model (the engine) is created here.
*/
void CMobopolyDocument::ConstructL()
	{
	iBank = CBank::NewL();
	}    

/** 
* C++ constructor.
* @param aApp The application object, passed to CEikDocument constructor.
*/
CMobopolyDocument::CMobopolyDocument(CEikApplication& aApp)
		 : CAknDocument(aApp) 
	{
	// no implementation required
	}   

/** 
* Destructor frees the resources allocated. Especially document
* is responsible for destroying the model (the Mobopoly).
*/
CMobopolyDocument::~CMobopolyDocument()
	{
	delete iBank;
	}

/** 
* Creates the application's UI object. Called by the framework.
* @returns The application UI object.
*/
CEikAppUi* CMobopolyDocument::CreateAppUiL()
	{
	return new (ELeave) CMobopolyAppUi;
	}

/** 
* Used by the framework classes to get access to the app's model (the Mobopoly).
*/
CBank * CMobopolyDocument::Bank()
	{
	return iBank;
	}
	
/** 
* Resets the model (the Mobopoly).
*/
void CMobopolyDocument::ResetModelL()
	{
	// Nothing to see here. Go away.
	}

/**
* Resets the application model.
*/
void CMobopolyDocument::NewDocumentL()
	{
	ResetModelL();
	}


} // namespace
/**
* Do not edit text here. These comments are maintained by CVS!
*
* $Log: MobopolyDocument.cpp,v $
* Revision 1.2  2006/02/15 13:23:24  Antti
* Added and modified doxygen comments, removed commented out code.
*
* Revision 1.1  2006/02/15 12:38:13  Antti
* Committing first public version of the example solution
*
* Revision 1.1.1.1  2005/03/01 18:27:34  Antti
* Importing first public release.
*
*
*/