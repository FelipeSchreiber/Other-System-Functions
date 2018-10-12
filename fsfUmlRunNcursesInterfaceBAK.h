/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2016/2
Prof. Marcelo Luiz Drumond Lanza
Autor: Felipe Claudio da Silva Santos

$Author$
$Date$
$Log$
*/ 
#ifndef FSF_UML_RUN_NCURSES_INTERFACE_H
#define FSF_UML_RUN_NCURSES_INTERFACE_H "@(#)fsfRunNcursesInterface.h $Revisions$"
#include "fsfUmlErrors.h"
#include "fsfUmlConfig.h"
#include "fsfUmlTypes.h"
#define _XOPEN_SOURCE_EXTENDED = 1
#define _XOPEN_CURSES
#include <ncurses.h>
#include <string.h>
#include "fsfUmlTypes.h"
#include "fsfUmlUserInterface.h"
#include "fsfUmlErrors.h"
#include "fsfUmlConfig.h"
#include "fsfUmlConst.h"
#include "fsfUmlFunctions.h"

/*
fsfUmlErrorType
FsfUmlRunNcursesInterface(fsfUmlConfigurationOptionsType *fsfUmlConfigurations, char *fsfUmlNickname,fsfUmlLanguageType fsfUmlLanguage);


Arguments:

fsfUmlConfigurations - This struct contains the filenames that will be used at the current program

fsfUmlNickname - This is the user's nickname

fsfUmlLanguage - The language in which the messages will be shown at screen


Returned code:

fsfUmlNullConfigurationData - Case the pointer to struct fsfUmlConfigurations is NULL

fsfUmlKeypadUnabled - Case de keypad() function returned an error

fsfUmlErrNo - This equals to the returned value by the following functions: FsfUmlNcursesLogin,FsfUmlPrintWindow or FsfUmlPrintWindowMoveCursor

fsfUmlErrorClosingWindow - Case an problem occured while closing a window


Description:

This function runs the ncurses interface.Only login and password are required for a while.A menu is shown to the user, althought it's missing 
the primary functions and forms for each option available.
*/

fsfUmlErrorType
FsfUmlRunNcursesInterface(fsfUmlConfigurationOptionsType *fsfUmlConfigurationOptions,char *fsfUmlNickname,fsfUmlLanguageType fsfUmlLanguage); 

#endif

/* $RCSfile$ */

