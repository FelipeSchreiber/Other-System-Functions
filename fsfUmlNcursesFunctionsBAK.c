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
#include "fsfUmlErrors.h"
#include "fsfUmlFunctions.h"
#include "fsfUmlUserInterface.h"
#include "fsfUmlTypes.h"
#include <ncurses.h>
#include <curses.h>
#include <string.h>
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
FsfUmlPrintWindowMoveCursor(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,fsfUmlUserInterfaceMessageNumberType fsfUmlMessage,WINDOW* fsfUmlWindow,char* fsfUmlString,int fsfUmlMaxRow)
{
 int fsfUmlCursorY,fsfUmlCursorX;
 
 if((wprintw(fsfUmlWindow,"\n%s\n", FsfUmlGetNcursesUserInterfaceMessage(fsfUmlField,fsfUmlLanguage))) != OK)
  return fsfUmlErrorPrintingWindow;

 if((wrefresh(fsfUmlWindow)) != OK)
  return fsfUmlErrorReloadingWindow;
 
 getyx(fsfUmlWindow,fsfUmlCursorY,fsfUmlCursorX);
 wattron(fsfUmlWindow,A_BOLD|A_UNDERLINE);

 if((mvwprintw(fsfUmlWindow,fsfUmlMaxRow - 5,1,"%s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlMessage,fsfUmlLanguage))) != OK)
  return fsfUmlErrorPrintingWindow;
    
 if((wmove(fsfUmlWindow,fsfUmlCursorY,fsfUmlCursorX)) != OK)
  return fsfUmlErrorMovingCursor;

 if((wgetstr(fsfUmlWindow,fsfUmlString)) != OK)
  return fsfUmlErrorGettingString;
 
 wattroff(fsfUmlWindow,A_BOLD|A_UNDERLINE);

 if((wrefresh(fsfUmlWindow)) != OK)
  return fsfUmlErrorReloadingWindow;

 return fsfUmlOk;
}

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
FsfUmlPrintWindow(fsfUmlLanguageType fsfUmlLanguage,fsfUmlUserInterfaceMessageNumberType fsfUmlField,WINDOW* fsfUmlWindow,char* fsfUmlString)
{
 if((wprintw(fsfUmlWindow,"%s\n", FsfUmlGetNcursesUserInterfaceMessage(fsfUmlField,fsfUmlLanguage))) != OK)
  return fsfUmlErrorPrintingWindow;
 
 if((wrefresh(fsfUmlWindow)) != OK)
  return fsfUmlErrorReloadingWindow; 
 
 wattron(fsfUmlWindow,A_BOLD|A_UNDERLINE);

 if((wprintw(fsfUmlWindow,"%s\n",fsfUmlString)) != OK)
  return fsfUmlErrorPrintingWindow;

 wattroff(fsfUmlWindow,A_BOLD|A_UNDERLINE);
 
 if((wrefresh(fsfUmlWindow)) != OK)
  return fsfUmlErrorReloadingWindow;
 
 return fsfUmlOk;
}

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
FsfUmlNcursesLogin(fsfUmlLanguageType fsfUmlLanguage,WINDOW* fsfUmlWindow,WINDOW* fsfUmlBorder,char* fsfUmlGetNickname,char* fsfUmlPassword,boolean *fsfUmlExit)
{
 int fsfUmlUserInput,fsfUmlMaxRow,fsfUmlMaxColumn;
 int fsfUmlErrNo;
 
 if(!fsfUmlWindow)
  return fsfUmlNullWindow;

 if(!fsfUmlBorder)
  return fsfUmlNullBorder;
 
 if(FsfUmlCheckStringField(fsfUmlPassword,FSF_UML_PASSWORD_,FSF_UML_PASSWORD_MIN_LENGTH,FSF_UML_PASSWORD_MAX_LENGTH) ==
    fsfUmlNullStringField)
  return fsfUmlNullStringField;

 if(FsfUmlCheckNickname(fsfUmlGetNickname,FSF_UML_NICKNAME_,FSF_UML_NICKNAME_MIN_LENGTH,FSF_UML_NICKNAME_MAX_LENGTH) ==
    fsfUmlNullStringField)
  return fsfUmlNullStringField; 

 if(!fsfUmlExit)
  return fsfUmlNullExit;

 getmaxyx(fsfUmlWindow,fsfUmlMaxRow,fsfUmlMaxColumn); 

 fsfUmlGetNickname[0] = '\0';
 fsfUmlPassword[0] ='\0';   

 while((FsfUmlCheckNickname(fsfUmlGetNickname,FSF_UML_NICKNAME_,FSF_UML_NICKNAME_MIN_LENGTH,FSF_UML_NICKNAME_MAX_LENGTH)) && ((fsfUmlUserInput) != 27))
 {
  wclear(fsfUmlWindow);
  if(fsfUmlErrNo = FsfUmlPrintWindowMoveCursor(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlNicknameWarning,fsfUmlWindow,fsfUmlGetNickname,fsfUmlMaxRow))
   return fsfUmlErrNo;

  noecho();
  fsfUmlUserInput = wgetch(fsfUmlWindow);
  wrefresh(fsfUmlWindow);
  echo();
 }
 fsfUmlGetNickname[strlen(fsfUmlGetNickname)] = '\0';

 if(fsfUmlUserInput == 27)
 {
  fsfUmlGetNickname[0] = '\0';

  wclear(fsfUmlWindow);
  wclear(fsfUmlBorder);
  wrefresh(fsfUmlWindow);
  wrefresh(fsfUmlBorder);    
  
  if(delwin(fsfUmlWindow) != OK)
   return(fsfUmlErrorClosingWindow);
  if(delwin(fsfUmlBorder) != OK)
   return(fsfUmlErrorClosingWindow);
  
  *fsfUmlExit = fsfUmlTrue;
 }/*The nickname was invalid and the user decided to quit*/
 else
 {
  while((FsfUmlCheckStringField(fsfUmlPassword,FSF_UML_PASSWORD_,FSF_UML_PASSWORD_MIN_LENGTH,FSF_UML_PASSWORD_MAX_LENGTH)) && ((fsfUmlUserInput) != 27))
  {
   wclear(fsfUmlWindow);
   
   if(fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlWindow,fsfUmlGetNickname))
    return fsfUmlErrNo;
  
   if(fsfUmlErrNo = FsfUmlPrintWindowMoveCursor(fsfUmlLanguage,fsfUmlInsertPassword,fsfUmlPasswordWarning,fsfUmlWindow,fsfUmlPassword,fsfUmlMaxRow))
   {
    #ifdef _MY_DEBUG_
    mvwprintw(fsfUmlWindow,0,0,"\nVai sair da funcao.Erro: %i",fsfUmlErrNo);
    wrefresh(fsfUmlWindow);   
    delay_output(10000);
    #endif
    return fsfUmlErrNo;
   }
  
   noecho();
   fsfUmlUserInput = wgetch(fsfUmlWindow);
   wrefresh(fsfUmlWindow);
   echo();
  }/*The nickname was incorrect, and the user decided to keep the login process*/
  
  #ifdef _MY_DEBUG_
  wprintw(fsfUmlWindow,"\nSeg. Fault2?");
  wrefresh(fsfUmlWindow);
  delay_output(3000);  
  #endif

  wclear(fsfUmlWindow);
  if(fsfUmlUserInput == 27)
  {
   fsfUmlGetNickname[0] = '\0';
   fsfUmlPassword[0] ='\0';
 
   wclear(fsfUmlWindow);
   wclear(fsfUmlBorder);
   wrefresh(fsfUmlWindow);
   wrefresh(fsfUmlBorder);

   if(delwin(fsfUmlWindow) != OK)
    return(fsfUmlErrorClosingWindow);
   if(delwin(fsfUmlBorder) != OK)
    return(fsfUmlErrorClosingWindow);
 
   *fsfUmlExit = fsfUmlTrue;
  }
  else
  { 
   if(fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlWindow,fsfUmlGetNickname))
    return fsfUmlErrNo;
  
   wprintw(fsfUmlWindow,"\n%s\n",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlInsertPassword,fsfUmlLanguage));
   wattron(fsfUmlWindow,A_BOLD|A_UNDERLINE);
   wprintw(fsfUmlWindow,"%s",fsfUmlPassword);  
   wrefresh(fsfUmlWindow);

   getmaxyx(fsfUmlWindow,fsfUmlMaxRow,fsfUmlMaxColumn);
   mvwprintw(fsfUmlWindow,fsfUmlMaxRow - 2,fsfUmlMaxColumn - 10,"%s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlEnter,fsfUmlLanguage));
   wattroff(fsfUmlWindow,A_BOLD|A_UNDERLINE);
   wrefresh(fsfUmlWindow);
   wgetch(fsfUmlWindow);
   
   *fsfUmlExit = fsfUmlFalse;
  
   #ifdef _MY_DEBUG_
   wprintw(fsfUmlWindow,"\nSeg. Fault3?");
   wrefresh(fsfUmlWindow);
   delay_output(3000);  
   #endif
  } /*else ends*/
 } 
 return fsfUmlOk;
}

/*RCSFile*/

