/*Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2017/1
 
$Author$
$Date$
$Log$
 
*/

#include "fsfUmlErrors.h"
#include "fsfUmlConfig.h"
#include "fsfUmlTypes.h"
#include "fsfUmlFunctions.h"
#include "fsfUmlConst.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef _FSF_UML_GET_PENDING_REGISTRATION_REQUESTS_H_
#define _FSF_UML_GET_PENDING_REGISTRATION_REQUESTS_H_ "@(#)fsfUmlGetPendingRegistrationRequests.h $Revision$" 
/*
fsfUmlErrorType
FsfUmlGetPendingRegistrationRequestsPerUser(fsfUmlConfigurationOptionsType *fsfUmlConfigurations,fsfUmlUserDataType **fsfUmlFirstData)


Arguments:

fsfUmlConfigurations - This argument represents the configurations chosen (I)

fsfUmlFirstData this is the the pointer to the first element of a list (O)


Returned code:

fsfUmlNullConfigurationData - The pointer to struct fsfUmlConfigurationsType got NULL value

fsfUmlNullUserData - Case the fsfUmlFirstData is NULL

fsfUmlFileOpeningError - Case a problem occured while opening a file

fsfUmlNoValidRequests -  Case there isn't any valid request

fsfUmlInvalidUserId - Case the user's id found at users file contains more than just numbers

fsfUmlInvalidProfile - Case the user's profile found at users file contains more than just numbers

fsfUmlFileError - Case the error pointer is set at users or requesting users file

fsfUmlFileReadingError - Case a problem occured while reading the file's data

fsfUmlMemoryAllocationError - Case a problem occured while allocating memory

fsfUmlErrNo - This equals to the returned value by the following functions: FsfUmlCheckNickname,FsfUmlFilenameValidation or
FsfUmlCheckStringField


Description:

This function search for the user's nickname in users file, takes the id, email address,full name and his profile.Then serach at 
requesting users file for his id.Once the id is found and the absolut time expiration is valid, a structure is put in the list, containing all
his information.   

*/

fsfUmlErrorType
FsfUmlGetPendingRegistrationRequestsPerUser(fsfUmlConfigurationOptionsType *fsfUmlConfigurations,fsfUmlUserDataType **fsfUmlFirstData);

#endif
/*$RCSFile$*/

