/*
  Universidade Federal do Rio de Janeiro
  Escola Politecnica
  Departamento de Eletronica e de Computacao
  Prof. Marcelo Luiz Drumond Lanza
  EEL 270 - Computacao II - Turma 2017/1
 
  $Author$
  $Date$
  $Log$  

*/

#ifndef FSF_UML_NCURSES_FUNCTIONS
#define FSF_UML_NCURSES_FUNCTIONS "@(#)fsfUmlNcursesFunctions.h $Revision$"

#include "fsfUmlUserInterface.h"
#include "fsfUmlTypes.h"
#include "fsfUmlErrors.h"
#include <ncurses.h>
#include <curses.h>

/*
 FsfUmlPrintWindowMoveCursor(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,fsfUmlUserInterfaceMessageNumberType fsfUmlMessage,WINDOW* fsfUmlWindow,char* fsfUmlString,int fsfUmlMaxRow)


Arguments:

fsfUmlLanguage - This is the specified language (I)

fsfUmlField - This is the field to be printed at the specified window, which corresponds to nickname or password (I)

fsfUmlMessage - This is the message to be printed at the specified window, which corresponds to some instructions (I)

fsfUmlWindow - This is the window where things will be printed (I)

fsfUmlString - This is the pointer where information digited by the user will be stored (O)

fsfUmlMaxRow - This is the maximum height of the window where things will be prinnted on (I)


Description:

This function just print two messages: one at the top of the window and another at the bottom


Returned Code:

fsfUmlErrorPrintingWindow - An error occured while writing at window

fsfUmlErrorReloadingWindow - An error occured while reloading a window

fsfUmlErrorMovingCursor - An error occured while moving the cursor

fsfUmlErrorGettingString - An error occured while the user was digiting

fsfUmlOk - No problems occured
*/

fsfUmlErrorType
FsfUmlPrintWindowMoveCursor(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,fsfUmlUserInterfaceMessageNumberType fsfUmlMessage,WINDOW* fsfUmlWindow,char* fsfUmlString,int fsfUmlMaxRow);

/*
 FsfUmlPrintWindow(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,WINDOW* fsfUmlWindow,char* fsfUmlString)


Arguments:

fsfUmlLanguage - This is the specified language (I)

fsfUmlField - This is the first message to be printed at the specified window, which corresponds to nickname or password (I)

fsfUmlWindow - This is the window where things will be printed (I)

fsfUmlString - This is the pointer to the information to be printed (I)


Description:

This function just print the field correspondig to the password or login and it's value


Returned Code:

fsfUmlErrorPrintingWindow - An error occured while writing at window

fsfUmlErrorReloadingWindow - An error occured while reloading a window

fsfUmlOk - No problems occured
*/

fsfUmlErrorType
FsfUmlPrintWindow(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,WINDOW* fsfUmlWindow,char* fsfUmlString);

/*
fsfUmlErrorType
FsfUmlNcursesLogin(fsfUmlLanguageType fsfUmlLanguage,WINDOW* fsfUmlWindow,WINDOW* fsfUmlBorder,char* fsfUmlGetNickname,char* fsfUmlPassword,boolean *fsfUmlExit)


Arguments:

fsfUmlLanguage - This is the selected language (I)

fsfUmlWindow - The the window where will shown the login formulary (I)

fsfUmlBorder - The border of the window where will be show the login formulary (I)

fsfUmlGetNickname - This is where the nickname will be saved (O)

fsfUmlPassword - This is where the password will be stored (O)

fsfUmlExit - This is a variable that indicates whether the user left the formulary window without filling the required filds, or don't (O)


Description:

This function opens a window with the formulary requering nickname and password from user


Returned Code:

fsfUmlNullWindow - The pointer to WINDOW type is NULL

fsfUmlNullBorder - The pointer to WINDOW(border) is NULL

fsfUmlNullExit - The pointer to boolean type(fsfUmlExit) is NULL

fsfUmlNullStringField - The pointer to password or nickname is NULL

fsfUmlErrNo - The error returned by FsfUmlPrintWindowMoveCursor or FsfUmlPrintWindow functions

fsfUmlErrorClosingWindow - An error occured while closing a window

*/
fsfUmlErrorType
FsfUmlNcursesLogin(fsfUmlLanguageType fsfUmlLanguage,WINDOW* fsfUmlWindow,WINDOW* fsfUmlBorder,char* fsfUmlGetNickname,char* fsfUmlPassword,boolean *fsfUmlExit);
#endif

/*RCSFile*/

