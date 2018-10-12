#ifndef MLDL_UML_REQUEST_REGISTRATION_H
#define MLDL_UML_REQUEST_REGISTRATION_H "@(#)mldlUmlRequestRegistration.h $Revision$"

#include "mldlUmlErrors.h"
#include "mldlUmlTypes.h"

/*
	mldlUmlErrorType
	MldlUmlAcceptInvite(mldlUmlConfigurationsType *, char *, mldlUmlDataType *)

	Arguments:
	mldlUmlConfigurationOptionsType * - pointer for structure that contains the names for
	the files used by the UML system (I)
	char * - string containing the email of the user that will analyse the request (I)
	mldlUmlUserDataType * - memory address for the struture holding user's info for validation
	and register (I)

	Returned code:
	mldlUmlOk - returned if the user's registered password is successfully inserted in users file
	and his invite is deleted from invite users file
	mldlUmlNoConfigurationOptions - is returned when the configuration options files pointer is empty
	mldlUmlEmptyResponsibleUserEmail - returned if the a user email isn't inserted for request validation
	mldlUmlNoUserData - returned if the function doesn't receive the user's data, required for validation
	and register operations
	mldlUmlUnableToOpenFile - returned if the function failes to open any file required for its operations
	mldlUmlInvalidId - returned if no matching id was found
	mldlUmlCorruptedFile - returned if the read file is corrupted
	mldlUmlErrorWritingFile - returned if any error occurs during file writing
	mldlUmlNoMatchingEmail - returned if the inserted analyser email wasn't found
	mldlUmlMemoryAllocationError - returned if the functin is unable to gain memory space to run a required action
	mldlUmlUnableToGetValidId - returned if the function is unable to receive a valid user id to ralate to the requesting
	user 
	mldlUmlErrorConvertingNumberToString - returned if the function required to convert any number (id, profile...) to the
	string form, so the function is able to write the values in an text file
	
	Description:
	This function adds the requesting user informations into the requesting users and users files if the inserted values 
	meets the registration requirements.
*/

mldlUmlErrorType
MldlUmlRequestRegistration (mldlUmlConfigurationOptionsType *, char *, mldlUmlUserDataType *);

#endif
