/* Universidade Federal do Rio de Janeiro
*  Escola Politecnica
*  Departamento de Eletronica e de Computacao
*  Prof. Marcelo Luiz Drumond Lanza
*  EEL 270 - Computacao II - Turma 2017/1
* 
*  $Author: $
*  $Date: $
*  $Log: $
*
*/
#ifndef _MLDL_UML_ADD_USER_H_                                          
#define _MLDL_UML_ADD_USER_H_ "@(#) $Revision: $"   

#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"
/*
 * mldlUmlErrorType
 * MldlUmlAddUser (mldlUmlConfigurationOptionsType *, mldlUmlUserDataType *)
 * Arguments:
 * mldlUmlConfigurationOptionsType * - Configuration
 * mldlUmlUserDataType * - user's information
 *
 * Returned code:
 * mldlUmlErrorType - Validation
  . . .
 * Description:
 * Adds a user to the database
 */
mldlUmlErrorType
MldlUmlAddUser (mldlUmlConfigurationOptionsType *mldlUmlConfiguration, mldlUmlUserDataType *mldlUmlUserData);

#endif

/* $RCSfile:$ */