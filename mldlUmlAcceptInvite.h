#ifndef MLDL_UML_ACCEPT_INVITE_H
#define MLDL_UML_ACCEPT_INVITE_H "@(#)mldlUmlAcceptInvite.h $Revision$"

#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"

/*
	mldlUmlErrorType
	MldlUmlAcceptInvite(char *)

	Arguments:
	mldlUmlConfigurationOptionsType * - pointer for structure that contains the names for
	the files used by the UML system (I)
	char * - temporary password inserted by the user willing to join the system
	for validation (I)
	mldlUmlUserDataType * - memory address for the struture holding user's info for validation
	and register (I)

	Returned code:
	mldlUmlOk - returned if the user's registered password is successfully inserted in users file
	and his invite is deleted from invite users file
	mldlUmlNoConfigurationOptions - is returned when the configuration options files pointer is empty
	mldlUmlEmpty - returned if the temporary password isn't inserted
	mldlUmlNoUserData - returned if the function doesn't receive the user's data, required for validation
	and register operations
	mldlUmlUnableToOpenFile - returned if the function failes to open any file required for its operations
	mldlUmlInvalidId - returned if no matching id was found
	mldlUmlExpiredInvite - returned if the invitation expiration associated with the id expired
	mldlUmlIncorectPassword - returned if the inserted temporary password is incorrect
	mldlUmlCorruptedFile - returned if the read file is corrupted
	mldlUmlUnableToObtainFileDescriptor - returned if the function fails to obtain a valid fail descriptor for
	opening the temporary file
	mldlUmlUnableToOpenTemporaryFile - returned if the funtion is unable to open the temporary file from the given	
	file descriptor
	mldlUmlErrorDuringFileCopy - returned if any error occurs during file copying
	mldlUmlErrorRenamingFile - returned if the function fails the renaming of the backup and temporary files 
	
	Description:
	This function validates the potential user's invite acceptance, checking if the invite is valid and, if it is,
	adds the registered password to the users related file. It also removes the accepted invite from the file related
	to potential user invitations.
*/

mldlUmlErrorType
MldlUmlAcceptInvite(mldlUmlConfigurationOptionsType *, char *, mldlUmlUserDataType *);

#endif

