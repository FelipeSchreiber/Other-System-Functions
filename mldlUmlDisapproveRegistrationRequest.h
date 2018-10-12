/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Eletronica e de Computacao
	EEL270 - Computacao II - Turma 2017/1
	Prof. Marcelo Luiz Drumond Lanza
	Autor: Mateus da Silva Gilbert

	$Author$
	$Date$
	$Log$

*/

#ifndef MLDL_UML_DISAPPROVE_REGISTRATION_REQUEST_H
#define MLDL_UML_DISAPPROVE_REGISTRATION_REQUEST_H "@(#)mldlUmlDisapproveRegistrationRequest.h $Revision$"

#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"

/*
	mldlUmlErrorType
	MldlUmlDisapproveRegistrationRequest(mldlUmlConfigurationsType *, char *, mldlUmlDataType *)

	Arguments:
	mldlUmlConfigurationOptionsType * - pointer for structure that contains the names for
	the files used by the UML system (I)
	char * - analyser username (I)
	char * - username of the person that wants to join the system (I)

	Returned code:
	mldlUmlOk - returned if the user's registered password is successfully inserted in users file
	and his invite is deleted from invite users file
	mldlUmlNoConfigurationOptions - is returned when the configuration options files pointer is empty
	mldlUmlEmptyUsername - returned if there is no analyser username 
	mldlUmlEmptyRequesterUsername - returned if there is no requester username
	mldlUmlNoUserData - returned if the function doesn't receive the user's data, required for validation
	and register operations
	mldlUmlUserNotFound - returned if the username of the analyser wasn't found
	mldlUmlUnableToOpenFile - returned if the function failes to open any file required for its operations
	mldlUmlInvalidId - returned if no matching id was found
	mldlUmlExpiredRequest - returned if the request expiration associated with the id expired
	mldlUmlCorruptedFile - returned if the read file is corrupted
	mldlUmlUnableToObtainFileDescriptor - returned if the function fails to obtain a valid fail descriptor for
	opening the temporary file
	mldlUmlUnableToOpenTemporaryFile - returned if the funtion is unable to open the temporary file from the given	
	file descriptor
	mldlUmlErrorDuringFileCopy - returned if any error occurs during file copying
	mldlUmlErrorRenamingFile - returned if the function fails the renaming of the backup and temporary files 
	mldlUmlPermissionDenied - returned if the user isn't qualified to do approve the request
	mldlUmlRequestingUserNotFound - returned if the requester username wasn't found
	
	Description:
	This function allows a qualified user of the system to disapprove the entrace of an user who requested entry to
	the system.
*/

mldlUmlErrorType
MldlUmlDisapproveRegistrationRequest(mldlUmlConfigurationOptionsType *, char *, char *);

#endif

/*	$RCSfile$ */
