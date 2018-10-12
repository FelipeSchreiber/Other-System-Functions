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

#ifndef _MLDL_UML_REJECT_INVITE_H_                                          
#define _MLDL_UML_REJECT_INVITE_H_ "@(#) $Revision: $"
#include "mldlUmlConfig.h"  

/*
 * mldlUmlErrorType
 * MldlUmlRejectInvite(mldlUmlConfigurationOptionsType *mldlUmlConfiguration, char *mldlUmlLogin, char *mldlUmlPassword)
 * 
 * Arguments
 * mldlUmlConfigurationOptionsType * - confirguration
 * char * - user
 * char * - password
 *
 * Returned code:
 * mldlUmlErrorType - Validation
  . . .
 * Description:
 * Gets and compares the passwords entered
 */
mldlUmlErrorType
MldlUmlRejectInvite(mldlUmlConfigurationOptionsType *mldlUmlConfiguration, char *mldlUmlLogin, char *mldlUmlPassword);

#endif

/* $RCSfile:$ */