/* Universidade Federal do Rio de Janeiro
*  Escola Politecnica
*  Departamento de Eletronica e de Computacao
*  Prof. Marcelo Luiz Drumond Lanza
*  EEL 270 - Computacao II - Turma 2017/1
* 
*  $Author:$
*  $Date:$
*  $Log:$
*/

#ifndef _MLDL_UML_LOCK_USER_ACCOUNT_H
#define _MLDL_UML_LOCK_USER_ACCOUNT_H "@(#)mldlUmlLockUserAccount.h $Revision:$"

#include "mldlUmlTypes.h"

/*

	mldlUmlErrorType
	MldlUmlLockedUserAccount(mldlUmlConfigurationOptionsType *, char *, char *);

	Arguments:

	mldlUmlConfigurationOptionsType * - determines which process is meant to be executed (I)

	char * - determines the nickname of the user executing the command (I)

	char * - determines the nickname of the user being unlocked (I)

	Description
	If the user is an administrator, this function removes a certain user from the "locked.users" file, and changes its password in the "users" file accordingly.
	If not, a request is set in the "unlocking.requests" file, requesting that the current user's account is unlocked.

*/


mldlUmlErrorType 
MldlUmlLockUserAccount(mldlUmlConfigurationOptionsType *mldlUmlConfigurationOption, char *mldlUmlAdminNickname, char *mldlUmlLockedNickname)


#endif

/* $RCSfile:$ */