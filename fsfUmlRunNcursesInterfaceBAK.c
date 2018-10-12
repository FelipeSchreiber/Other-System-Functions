/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
EEL270 - Computacao II - Turma 2016/2
Prof. Marcelo Luiz Drumond Lanza

$Author$
$Date$
$Log$
*/ 

#include "fsfUmlRunNcursesInterface.h"
#include "fsfUmlNcursesFunctions.h"
#include "fsfUmlShowConfigurationValues.h"

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
FsfUmlRunNcursesInterface(fsfUmlConfigurationOptionsType *fsfUmlConfigurations, char *fsfUmlNickname,fsfUmlLanguageType fsfUmlLanguage)
{
 WINDOW *fsfUmlWindow;
 fsfUmlWindow = initscr();
 raw();
 noecho();
 
 if(!fsfUmlConfigurations)
  return fsfUmlNullConfigurationData;

 if((keypad(fsfUmlWindow,TRUE) != OK))
  return(fsfUmlKeypadUnabled);
 
 int fsfUmlCounter,fsfUmlUserInput,fsfUmlUnderline,fsfUmlMaxRow,fsfUmlMaxColumn,fsfUmlCounterMinValue,fsfUmlCounterMaxValue,fsfUmlErrNo;
 char fsfUmlPassword[FSF_UML_PASSWORD_MAX_LENGTH + 1];
 char fsfUmlGetNickname[FSF_UML_NICKNAME_MAX_LENGTH + 1];
 /*fsfUmlLanguageType fsfUmlLanguage;*/
 boolean fsfUmlExit;
 WINDOW *fsfUmlSecondaryWindow,*fsfUmlBorder;

 fsfUmlUnderline = 0;
 fsfUmlCounter = 0;
 wrefresh(fsfUmlWindow);
 fsfUmlExit = fsfUmlFalse;
 getmaxyx(fsfUmlSecondaryWindow,fsfUmlMaxRow,fsfUmlMaxColumn);

 /*fsfUmlLanguage = FsfUmlGetLanguageIndex (fsfUmlLanguages);*/
 if(FsfUmlCheckNickname(fsfUmlNickname,FSF_UML_NICKNAME_,FSF_UML_NICKNAME_MIN_LENGTH,FSF_UML_NICKNAME_MAX_LENGTH))/*The nickname was invalid*/
 {
  fsfUmlGetNickname[0] = '\0';
  fsfUmlPassword[0] ='\0';

  wprintw(fsfUmlWindow,"%s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlHelp,fsfUmlLanguage));
  wrefresh(fsfUmlWindow);
  fsfUmlBorder = newwin(16,FSF_UML_NICKNAME_MAX_LENGTH + 4,4,4);
  wborder(fsfUmlBorder,'|','|','=','=','*','*','*','*');
  wrefresh(fsfUmlBorder);
  
  fsfUmlSecondaryWindow = newwin(14,FSF_UML_NICKNAME_MAX_LENGTH + 2,5,5);
  echo();
 
  if((fsfUmlErrNo = FsfUmlNcursesLogin(fsfUmlLanguage,fsfUmlSecondaryWindow,fsfUmlBorder,fsfUmlGetNickname,fsfUmlPassword,&fsfUmlExit)))
   return fsfUmlErrNo;
 
  if(fsfUmlExit == fsfUmlFalse)
  {    
   wclear(fsfUmlSecondaryWindow);
   if((fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlSecondaryWindow,fsfUmlGetNickname)))
    return fsfUmlErrNo;

   if((fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertPassword,fsfUmlSecondaryWindow,fsfUmlPassword)))
    return fsfUmlErrNo;
   
   mvwprintw(fsfUmlSecondaryWindow,fsfUmlMaxRow,fsfUmlMaxColumn - 7,"%s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlEnter,fsfUmlLanguage));
   wattroff(fsfUmlSecondaryWindow,A_BOLD|A_UNDERLINE);
   getch();
  }/*the other else ends*/
  wclear(fsfUmlWindow);
  wrefresh(fsfUmlWindow);/*Clear the help message from the main window*/
 }/*if ends*/  
 else/*The user has a valid nickname before calling this function*/ 
 {
  fsfUmlBorder = newwin(16,FSF_UML_NICKNAME_MAX_LENGTH + 4,4,4);
  wborder(fsfUmlBorder,'|','|','=','=','*','*','*','*');
  wrefresh(fsfUmlBorder);
  fsfUmlSecondaryWindow = newwin(14,FSF_UML_NICKNAME_MAX_LENGTH + 2,5,5);
  echo();
   
  wclear(fsfUmlSecondaryWindow);
  if((fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlSecondaryWindow,fsfUmlGetNickname)))
   return fsfUmlErrNo;
  
  while(((fsfUmlUserInput) != 27) && (FsfUmlCheckStringField(fsfUmlPassword,FSF_UML_PASSWORD_,
          FSF_UML_PASSWORD_MIN_LENGTH,FSF_UML_PASSWORD_MAX_LENGTH)))
  {
   wclear(fsfUmlSecondaryWindow);
   
   if((fsfUmlErrNo = FsfUmlPrintWindowMoveCursor(fsfUmlLanguage,fsfUmlInsertPassword,fsfUmlPasswordWarning,fsfUmlSecondaryWindow,
      fsfUmlPassword,fsfUmlMaxRow)))
    return fsfUmlErrNo;
 
   noecho();
   fsfUmlUserInput = wgetch(fsfUmlSecondaryWindow);
   wrefresh(fsfUmlSecondaryWindow);
   echo();
  }
 
  if(fsfUmlUserInput == 27)
  {
   #ifdef _MY_DEBUG_
   wprintw(fsfUmlSecondaryWindow,"\nfsfUmlExit reconhecido\n");
   wrefresh(fsfUmlSecondaryWindow);
   #endif
    
   fsfUmlPassword[0] ='\0';

   wclear(fsfUmlSecondaryWindow);
   wclear(fsfUmlBorder);
   wrefresh(fsfUmlSecondaryWindow);
   wrefresh(fsfUmlBorder);
   
   if(delwin(fsfUmlSecondaryWindow) != OK)
    return(fsfUmlErrorClosingWindow);
   if(delwin(fsfUmlBorder) != OK)
    return(fsfUmlErrorClosingWindow);
 
   fsfUmlExit = fsfUmlTrue;
  
   #ifdef _MY_DEBUG_
   wprintw(fsfUmlWindow,"\nSeg. Fault?");
   wrefresh(fsfUmlWindow);
   delay_output(3000);  
   wprintw(fsfUmlWindow,"\nfsfUmlExit :%i\n",fsfUmlExit);
   wrefresh(fsfUmlWindow);
   delay_output(3000);  
   #endif
  }/*The user decided to quit from this page*/
  else
  {
   wclear(fsfUmlSecondaryWindow);
   if((fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertNickname,fsfUmlSecondaryWindow,fsfUmlGetNickname)))
    return fsfUmlErrNo;
   
   if((fsfUmlErrNo = FsfUmlPrintWindow(fsfUmlLanguage,fsfUmlInsertPassword,fsfUmlSecondaryWindow,fsfUmlPassword)))
    return fsfUmlErrNo;
   
   mvwprintw(fsfUmlSecondaryWindow,fsfUmlMaxRow -2,fsfUmlMaxColumn -10,"%s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlEnter,fsfUmlLanguage));
   wrefresh(fsfUmlSecondaryWindow);
   wattroff(fsfUmlSecondaryWindow,A_BOLD|A_UNDERLINE);
   getch();
  /*The user has a valid nickname and password and decided to continue*/
  }
  
  if(fsfUmlExit == fsfUmlFalse)
  {
   wclear(fsfUmlSecondaryWindow);
   wclear(fsfUmlBorder);
   wrefresh(fsfUmlSecondaryWindow);
   wrefresh(fsfUmlBorder);
   
   if(delwin(fsfUmlSecondaryWindow) != OK)
    return(fsfUmlErrorClosingWindow);
   if(delwin(fsfUmlBorder) != OK)
    return(fsfUmlErrorClosingWindow);
  }/*Close the secondary window in order to show up the menu from the main window*/
 } 
   
 while(fsfUmlUnderline != fsfUmlLeave)/*This creates a loop condition: the programm will only close when the user decides to leave*/
 {

 if(fsfUmlExit)
 {
  wclear(fsfUmlWindow);
  
  #ifdef _MY_DEBUG_
  wprintw(fsfUmlWindow,"\nfsfUmlExit --> setting values");
  wrefresh(fsfUmlWindow);
  delay_output(3000);
  #endif 
  
  fsfUmlCounterMaxValue = fsfUmlLeave;/*The menu ends with the Exit option*/
  fsfUmlCounterMinValue = fsfUmlEnter;/*The menu begins with the Enter option*/
  fsfUmlUnderline = fsfUmlEnter;/*The underline shows up the selected option.It begins with the first option from menu*/
 }/*It means that the user has not entered with nickname and password, so all other options must be disabled*/
 else
 {
  fsfUmlCounterMaxValue = fsfUmlSearchUsers ;/*The menu ends with the Search Users option*/
  fsfUmlCounterMinValue = fsfUmlHelp;/*The menu begins with the Help option*/
  fsfUmlUnderline = fsfUmlHelp;/*The underline shows up the selected option.It begins with the first option from menu*/
 }/*The user has already entered with nickname and password, so all the options will be available, except the login one*/
 
  do
  {
   wprintw(fsfUmlWindow,"%s\n",FsfUmlGetNcursesUserInterfaceMessage(0,fsfUmlLanguage));
   fsfUmlCounter = fsfUmlCounterMinValue;

   while(fsfUmlCounter < (fsfUmlCounterMaxValue + 1))
   {
    if(fsfUmlCounter == fsfUmlUnderline)
    {
     wattron(fsfUmlWindow,A_UNDERLINE);
     wprintw(fsfUmlWindow, "\n %s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlCounter,fsfUmlLanguage));
     attroff(A_UNDERLINE);
    }
    else
     wprintw(fsfUmlWindow, "\n %s",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlCounter,fsfUmlLanguage));
    fsfUmlCounter++;
   }
  
   wrefresh(fsfUmlWindow);
   
   fsfUmlUserInput = wgetch(fsfUmlWindow);
   
   switch(fsfUmlUserInput)
   {
    case(KEY_UP):
    {
     if(fsfUmlUnderline == fsfUmlCounterMinValue)
      fsfUmlUnderline = fsfUmlCounterMaxValue;
     else
      fsfUmlUnderline--;
    }
    break;
   
    case(KEY_DOWN):
    {
     if(fsfUmlUnderline == fsfUmlCounterMaxValue)
      fsfUmlUnderline = fsfUmlCounterMinValue;
     else
      fsfUmlUnderline++;
    }
    break;
 
    default:
    /*mvwprintw(fsfUmlWindow,,"Unrecognized key.Only KEY_UP,KEY_DOWN and ENTER are allowed");*/
    break;
   }
  wclear(fsfUmlWindow);
 }while(fsfUmlUserInput != 10);/*This is the code associated with KEY_ENTER*/

 wclear(fsfUmlWindow); 
 wprintw(fsfUmlWindow,"\n%s < %s > ...",FsfUmlGetNcursesUserInterfaceMessage(fsfUmlSelectedOption,fsfUmlLanguage),
         FsfUmlGetNcursesUserInterfaceMessage(fsfUmlUnderline,fsfUmlLanguage));
 wrefresh(fsfUmlWindow);
 delay_output(3000);
 wclear(fsfUmlWindow);
 wrefresh(fsfUmlWindow);
 
 fsfUmlBorder = newwin(16,FSF_UML_NICKNAME_MAX_LENGTH + 4,4,4);
 wborder(fsfUmlBorder,'|','|','=','=','*','*','*','*');
 wrefresh(fsfUmlBorder);
 fsfUmlSecondaryWindow = newwin(14,FSF_UML_NICKNAME_MAX_LENGTH + 2,5,5);
 wrefresh(fsfUmlSecondaryWindow);
 wrefresh(fsfUmlBorder);
 echo();
 
 switch(fsfUmlUnderline)
 {
  case(fsfUmlEnter):
  {
   if((fsfUmlErrNo = FsfUmlNcursesLogin(fsfUmlLanguage,fsfUmlSecondaryWindow,fsfUmlBorder,fsfUmlGetNickname,fsfUmlPassword,&fsfUmlExit)))
    return fsfUmlErrNo;
  
   #ifdef _MY_DEBUG_
   wprintw(fsfUmlWindow,"\nfsfUmlExit :%i\n",fsfUmlExit);
   wrefresh(fsfUmlWindow);
   delay_output(3000);
   #endif
  }
  break;
  
  case(fsfUmlHelp):
   break;
  
  case(fsfUmlLeave):
   break;
  
  case(fsfUmlShowConfigurationValues):
  {
   /*fsfUmlBorder = newwin(16,FSF_UML_NICKNAME_MAX_LENGTH + 4,4,4);
   wborder(fsfUmlBorder,'|','|','=','=','*','*','*','*');
   wrefresh(fsfUmlBorder);
   fsfUmlSecondaryWindow = newwin(14,FSF_UML_NICKNAME_MAX_LENGTH + 2,5,5);
   wrefresh(fsfUmlSecondaryWindow);
   wrefresh(fsfUmlBorder);
   
   wprintw(fsfUmlSecondaryWindow,"\nComeca\n");
   wrefresh(fsfUmlSecondaryWindow);
   delay_output(3000);
   wclear(fsfUmlSecondaryWindow);
   wclear(fsfUmlBorder);
   wrefresh(fsfUmlSecondaryWindow);
   wrefresh(fsfUmlBorder);
   
   if(delwin(fsfUmlSecondaryWindow) != OK)
    return(fsfUmlErrorClosingWindow);
   if(delwin(fsfUmlBorder) != OK)
    return(fsfUmlErrorClosingWindow);
  
   wgetch(fsfUmlWindow); 
     
   if(fsfUmlErrNo = FsfUmlShowConfigurationValues(fsfUmlConfigurations,fsfUmlLanguage))
   {
    wprintw(fsfUmlWindow,"\nfsfUmlShowErr :%i\n",fsfUmlErrNo);
    wrefresh(fsfUmlWindow);
    delay_output(3000);
    return fsfUmlErrNo;
   }
   wprintw(fsfUmlWindow,"\nTermina\n");
   wrefresh(fsfUmlWindow);
   delay_output(3000);*/
  } 
  break;
 
  case(fsfUmlRequireRegistration):
   break;

  case(fsfUmlAcceptInvitation):
  {
   
  } 
  break;
 
  case(fsfUmlRejectInvitation):
   break;

  case(fsfUmlAddUser):
   break;
 
  case(fsfUmlGetPendingRegistrationRequestsPerUser):
   break;
  
  case(fsfUmlGetPendingRegistrationRequests):
   break;
 
  case(fsfUmlApproveRegistrationRequest):
   break;
  
  case(fsfUmlDisapproveRegistrationRequest):
   break;
  
  case(fsfUmlGetUnlockingRequests):
   break;
  
  case(fsfUmlLockUserAccount):
   break;
  
  case(fsfUmlUnlockUserAccount):
   break;
  
  case(fsfUmlChangeUserPassword):
   break;
  
  case(fsfUmlResetUserPassword):
   break;
  
  case(fsfUmlChangeUserName):
   break;
  
  case(fsfUmlChangeUserEmail):
   break;
  
  case(fsfUmlConfirmEmailChange):
   break;
  
  case(fsfUmlChangeUserProfile):
   break;

  case(fsfUmlGetUsers):
   break;
  
  case(fsfUmlSearchUsers):
   break;
  
  default:
   break;
 }
}
 endwin();
 return 0;
}  


/* $RCSfile$ */
