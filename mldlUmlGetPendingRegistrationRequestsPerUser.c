/*Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2017/1
 
$Author$
$Date$
$Log$i
  
*/

#include "mldlUmlGetPendingRegistrationRequestsPerUser.h"
#include <errno.h>

/*
mldlUmlErrorType
MldlUmlGetPendingRegistrationRequestsPerUser(mldlUmlConfigurationOptionsType *mldlUmlConfigurations, char *mldlUmlNickname,mldlUmlUserDataType **mldlUmlFirstData)


Arguments:

mldlUmlConfigurations - This argument represents the configurations chosen (I)

mldlUmlNickname - This is the target user (I)

mldlUmlFirstData this is the the pointer to the first element of a list (O)


Returned code:

mldlUmlNullConfigurationData - The pointer to struct mldlUmlConfigurationsType got NULL value

mldlUmlNullUserData - Case the mldlUmlFirstData is NULL

mldlUmlFileOpeningError - Case a problem occured while opening a file

mldlUmlNicknameNotFound - Case the nickname desired wasn't found at the users file

mldlUmlInvalidUserId - Case the user's id found at users file contains more than just numbers

mldlUmlInvalidProfile - Case the user's profile found at users file contains more than just numbers

mldlUmlFileError - Case the error pointer is set at users or requesting users file

mldlUmlFileReadingError - Case a problem occured while reading the file's data

mldlUmlMemoryAllocationError - Case a problem occured while allocating memory

mldlUmlErrNo - This equals to the returned value by the following functions: MldlUmlCheckNickname,FsfUmlFilenameValidation or
MldlUmlCheckStringField


Description:

This function search for the user's nickname in users file, takes the id, email address,full name and his profile.Then serach at 
requesting users file for his id.Once the id is found and the absolut time expiration is valid, a structure is put in the list, containing all
his information.   

*/

mldlUmlErrorType
MldlUmlGetPendingRegistrationRequestsPerUser(mldlUmlConfigurationOptionsType *mldlUmlConfigurations, char *mldlUmlNickname,mldlUmlUserDataType **mldlUmlFirstData)   
{
 #ifdef _MY_DEBUG_
  printf("\nDebug is set in mldlUmlGetPendingRegistrationRequestPerUser\n");
 #endif
   
 int mldlUmlErrNo,mldlUmlColonCounter,mldlUmlCounter,mldlUmlPos,mldlUmlRead;
 unsigned long long mldlUmlUserId;
 mldlUmlUserProfileType mldlUmlProfile;
 time_t mldlUmlActualTime,mldlUmlAbsolutExpirationTime;
 mldlUmlUserIdentifierType mldlUmlAnalistId,mldlUmlRequestingUserId;
 char mldlUmlPasswd[FSF_UML_PASSWORD_MAX_LENGTH];
 /*mldlUmlPendingRequestType mldlUmlPendingRegistration;*/
 char mldlUmlBuffer[FSF_UML_FULLNAME_MAX_LENGTH + 1],mldlUmlIdBuffer[20],mldlUmlProfileBuffer[20],
 mldlUmlFullNameBuffer[FSF_UML_FULLNAME_MAX_LENGTH + 1],mldlUmlEmailBuffer[FSF_UML_EMAIL_MAX_LENGTH + 1],mldlUmlGetCh,*mldlUmlCheck;
 /*The size of mldlUmlBuffer corresponds to the largest length possible among all the variables found in users file*/
 FILE *mldlUmlRequestingUsers,*mldlUmlUsersFile;
 boolean mldlUmlFound = mldlUmlFalse;
 mldlUmlUserDataType *mldlUmlFirst,*mldlUmlLast,*mldlUmlNew;
 
 mldlUmlFirst = NULL;
 mldlUmlLast = NULL;
 mldlUmlPos = mldlUmlColonCounter = mldlUmlCounter = 0;
 
 if(!mldlUmlConfigurations)
  return mldlUmlNullConfigurationData;

 if((mldlUmlErrNo = MldlUmlCheckNickname(mldlUmlNickname,FSF_UML_NICKNAME_ ,FSF_UML_NICKNAME_MIN_LENGTH,FSF_UML_NICKNAME_MAX_LENGTH)))
 {
  #ifdef _MY_DEBUG_
   printf("\nmldlUmlNickname: %s \n",mldlUmlNickname);
  #endif
  #ifdef _MY_DEBUG_
   printf("\nErrNo:#%i ",mldlUmlErrNo);
  #endif
  return mldlUmlErrNo;
 } 
 /*#ifdef _MY_DEBUG_
 printf("\nUp to now is ok\n");
 if(!fSchreibersfUmlFirstData)
  printf("\FelipenmldlUmlFirstData is NULL\n");
 #endif
 if(!*mldlUmlFirstData)
  return mldlUmlNullUserData;
 */

 if((mldlUmlErrNo = 
 MldlUmlFilenameValidation(mldlUmlConfigurations->mldlUmlRequestingUsersDataFilename,FSF_UML_VALID_FILENAME_,
                          FSF_UML_FILENAME_MIN_LENGTH,FSF_UML_FILENAME_MAX_LENGTH)))
 {
  #ifdef _MY_DEBUG_
   printf("\nmldlUmlRequestingUsersDataFileName: %s\n\n ",mldlUmlConfigurations->mldlUmlRequestingUsersDataFilename);
   printf("\nmldlUmlRequestingUsersDataFileName LENGTH: %i\n\n ",(int)strlen(mldlUmlConfigurations->mldlUmlRequestingUsersDataFilename));
  #endif
  return mldlUmlErrNo;
 }
 if(!(mldlUmlRequestingUsers = fopen(mldlUmlConfigurations->mldlUmlRequestingUsersDataFilename,"rb")))
 {
  #ifdef _MY_DEBUG_
   printf("\nREQUESTING USERS FILE OPENING ERROR\n\n");
  #endif
  return mldlUmlFileOpeningError;
 }
 
 if((mldlUmlErrNo = 
 MldlUmlFilenameValidation(mldlUmlConfigurations->mldlUmlUsersDataFilename,FSF_UML_VALID_FILENAME_,
                          FSF_UML_FILENAME_MIN_LENGTH,FSF_UML_FILENAME_MAX_LENGTH)))
 {
  #ifdef _MY_DEBUG_
   printf("\nmldlUmlUsersDataFileName: %s\n\n ",mldlUmlConfigurations->mldlUmlUsersDataFilename);
   printf("\nmldlUmlUsersDataFileName LENGTH: %i\n\n ",(int)strlen(mldlUmlConfigurations->mldlUmlUsersDataFilename));
  #endif
  return mldlUmlErrNo;
 }
 
 if(!(mldlUmlUsersFile = fopen(mldlUmlConfigurations->mldlUmlUsersDataFilename,"r")))
 {
  #ifdef _MY_DEBUG_
   printf("\nFILE OPENING ERROR\n\n ");
  #endif
  return mldlUmlFileOpeningError;
 }
 
 while((!mldlUmlFound) && (!feof(mldlUmlUsersFile)))
 {
  #ifdef _MY_DEBUG_
   printf("\nSeg. Fault???\n");
  #endif
  mldlUmlCounter = 0;
  mldlUmlGetCh = '1';
  while((':' != mldlUmlGetCh) && ('\n' != mldlUmlGetCh))
  {
   mldlUmlGetCh = fgetc(mldlUmlUsersFile);
   mldlUmlBuffer[mldlUmlCounter] = mldlUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlBuffer[mldlUmlCounter] = '\0';
  
  if((mldlUmlBuffer[(mldlUmlCounter - 1)] == ':') || (mldlUmlBuffer[(mldlUmlCounter - 1)] == '\n'))
   mldlUmlBuffer[(mldlUmlCounter - 1)] = '\0';
  #ifdef _MY_DEBUG_
   printf("\n BUFFER CONTENT : %s\n",mldlUmlBuffer);
   printf("\n NICKNAME TARGET: %s\n",mldlUmlNickname);
  #endif

  if(!strcmp(mldlUmlBuffer,mldlUmlNickname))
   mldlUmlFound = mldlUmlTrue;
  else
   mldlUmlPos++;
 }/*The mldlUmlPos stores where the nickname was found, so the previus argument is the id of the target user*/

 #ifdef _MY_DEBUG_
  printf("\nSeg. Fault 2???\n");
 #endif

 if(feof(mldlUmlUsersFile) && !mldlUmlFound)
  return mldlUmlNicknameNotFound;

 rewind(mldlUmlUsersFile);
  #ifdef _MY_DEBUG_
   printf("\nSeg. Fault 1 ???\n");
  #endif
 while(mldlUmlColonCounter != (mldlUmlPos - 1)) 
 {
  mldlUmlGetCh = fgetc(mldlUmlUsersFile);
  if((mldlUmlGetCh == ':') || (mldlUmlGetCh == '\n'))  
   mldlUmlColonCounter++;
 }

 mldlUmlCounter = 0;
 while(':' != (mldlUmlGetCh = fgetc(mldlUmlUsersFile)))
 {
  mldlUmlIdBuffer[mldlUmlCounter] = mldlUmlGetCh;
  mldlUmlCounter++;
 }
 mldlUmlIdBuffer[mldlUmlCounter] = '\0';
 /*the mldlUmlIdBuffer now contains the id*/
 mldlUmlUserId = strtoull(mldlUmlIdBuffer,&mldlUmlCheck,10);

 if(*mldlUmlCheck != '\0')
 {
  #ifdef _MY_DEBUG_
   printf("\nINVALID USER ID:\nbuffer:%s\ninvalid char: %c\n\n ",mldlUmlIdBuffer,*mldlUmlCheck);
  #endif
  return mldlUmlInvalidUserId;
 }  
 mldlUmlCounter = 0;
 while(':' !=(mldlUmlGetCh = fgetc(mldlUmlUsersFile)));
 while(':' !=(mldlUmlGetCh = fgetc(mldlUmlUsersFile)));/*Jumps both nickname and crypted password fields in the text file*/
 while(':' != (mldlUmlGetCh = fgetc(mldlUmlUsersFile)))
 {
  mldlUmlProfileBuffer[mldlUmlCounter] = mldlUmlGetCh;
  mldlUmlCounter++;
 }
 mldlUmlProfileBuffer[mldlUmlCounter] = '\0';
 /*The mldlUmlProfileBuffer contains the user profile */
 mldlUmlProfile = strtoull(mldlUmlProfileBuffer,&mldlUmlCheck,10);
 
 if(*mldlUmlCheck != '\0')
 {
  #ifdef _MY_DEBUG_
   printf("\nINVALID USER PROFILE\n PROFILE: %s\n invalid char:%c\n\n ",mldlUmlProfileBuffer,*mldlUmlCheck);
  #endif
  return mldlUmlInvalidProfile;
 }
  
 mldlUmlCounter = 0;
 while(':' != (mldlUmlGetCh = fgetc(mldlUmlUsersFile)))
 {
  mldlUmlFullNameBuffer[mldlUmlCounter] = mldlUmlGetCh;
  mldlUmlCounter++;
 }
 mldlUmlFullNameBuffer[mldlUmlCounter] = '\0';

 /*the mldlUmlFullNameBuffer now contains the user's full name*/
 if((mldlUmlErrNo = 
 MldlUmlCheckStringField(mldlUmlFullNameBuffer,FSF_UML_USERNAME_,FSF_UML_FULLNAME_MIN_LENGTH,FSF_UML_FULLNAME_MAX_LENGTH)))
 {
  #ifdef _MY_DEBUG_
   printf("FULL NAME: %s\n\n ",mldlUmlFullNameBuffer);
   printf("\nLENGTH: %i\n\n ",(int)strlen(mldlUmlFullNameBuffer));
  #endif
  return mldlUmlErrNo;
 }
 /*mldlUmlCounter = 0;*/
 fgets(mldlUmlEmailBuffer,(FSF_UML_EMAIL_MAX_LENGTH + 2),mldlUmlUsersFile);
 /*while()
 {
  mldlUmlEmailBuffer[mldlUmlCounter] = mldlUmlGetCh;
  mldlUmlCounter++;
 }*/
 if(mldlUmlEmailBuffer[strlen(mldlUmlEmailBuffer) - 1] == '\n')
  mldlUmlEmailBuffer[strlen(mldlUmlEmailBuffer) - 1] = '\0';
 /*the mldlUmlFullNameBuffer now contains the user's full name*/
 if((mldlUmlErrNo = 
 MldlUmlCheckEmail(mldlUmlEmailBuffer,FSF_VALID_EMAIL_,FSF_UML_EMAIL_MIN_LENGTH,FSF_UML_EMAIL_MAX_LENGTH)))
 {
  #ifdef _MY_DEBUG_
   printf("\nUSER EMAIL: %s\n\n ",mldlUmlEmailBuffer);
   printf("\nUSER EMAIL LENGTH: %i\n\n ",(int)strlen(mldlUmlEmailBuffer));
  #endif
  return mldlUmlErrNo;
 }

 if(ferror(mldlUmlUsersFile))
 {
  #ifdef _MY_DEBUG_
   printf("\nFILE ERROR NO: %i\n\n ",errno);
   printf("\nFILE ERROR CAUSE: %s\n\n ",strerror(errno));
  #endif
  fclose(mldlUmlUsersFile);
  return mldlUmlFileError;
 }
 
 /*No problems occured up to now, so the id,profile,name and email are valid. Now we can search at the requesting users file by the given id*/
 mldlUmlCounter = 0;
 #ifdef _MY_DEBUG_
  /*SHOW ALL DATA STORED AT REQUESTING.USERS*/
  while(fread(&mldlUmlAbsolutExpirationTime,sizeof(time_t),1,mldlUmlRequestingUsers))
  {
   printf("\n\n-----------------------------------------------------------\n\n");
   printf("\nHorario: %i",(int) /*difftime(timeTest,localTime)*/mldlUmlAbsolutExpirationTime);
   fread(&mldlUmlAnalistId,sizeof(unsigned long long),1,mldlUmlRequestingUsers);
   printf("\nAnalyst: %llu",mldlUmlAnalistId);
   fread(&mldlUmlRequestingUserId,sizeof(unsigned long long),1,mldlUmlRequestingUsers);
   printf("\nUser: %llu",mldlUmlRequestingUserId);
   fread(mldlUmlPasswd,sizeof(char),128,mldlUmlRequestingUsers);
   mldlUmlPasswd[strlen(mldlUmlPasswd)] = '\0';
   printf("\nPass: %s",mldlUmlPasswd);
   printf("\n\n-----------------------------------------------------------\n\n");
  }
  rewind(mldlUmlRequestingUsers);
 #endif
 
 while(!feof(mldlUmlRequestingUsers))
 { 
  #ifdef _MY_DEBUG_
   printf("\nLoop No: %i\n",mldlUmlCounter);
  #endif
  if((fread(&mldlUmlAbsolutExpirationTime,sizeof(time_t),1,mldlUmlRequestingUsers) != 1))
  {
   fclose(mldlUmlRequestingUsers);
   return mldlUmlFileReadingError;
  }
  
  if((mldlUmlRead = fread(&mldlUmlAnalistId,sizeof(mldlUmlUserIdentifierType),1,mldlUmlRequestingUsers)) != 1)
  {
   #ifdef _MY_DEBUG_
    printf("\nExpiration time: %i",(int)mldlUmlAbsolutExpirationTime);   
    printf("\nAnalist Id: %i\n",(int)mldlUmlAnalistId);
    printf("\nTotal read: %i\n",(int)mldlUmlRead);
    printf("\nERROR READING REQUESTING USERS FILE 1\n");
   #endif
   fclose(mldlUmlRequestingUsers);
   return mldlUmlFileReadingError;
  }
  
  if((fread(&mldlUmlRequestingUserId,sizeof(mldlUmlUserIdentifierType),1,mldlUmlRequestingUsers) != 1))
  {
   #ifdef _MY_DEBUG_
    printf("\nERROR READING REQUESTING USERS FILE 2\n");
   #endif
   fclose(mldlUmlRequestingUsers);
   return mldlUmlFileReadingError;
  }
  
  /*if(((mldlUmlRead = fread(mldlUmlPasswd,sizeof(char),(FSF_UML_PASSWORD_MAX_LENGTH),mldlUmlRequestingUsers)) == 0 ))
  {
   #ifdef _MY_DEBUG_
    printf("\nERROR READING REQUESTING USERS FILE 3\n");
    printf("\nTotal Read: %i\n",mldlUmlRead);
    printf("\nNmemb requested: %i\n",FSF_UML_PASSWORD_MAX_LENGTH);
   #endif
   fclose(mldlUmlRequestingUsers);
   return mldlUmlFileReadingError;
  }*/
  fread(mldlUmlPasswd,sizeof(char),(FSF_UML_PASSWORD_MAX_LENGTH),mldlUmlRequestingUsers);
  mldlUmlPasswd[strlen(mldlUmlPasswd)] = '\0';

  #ifdef _MY_DEBUG_
   printf("\n----------------------------------------------------------------\n");
   printf("\nExpiration time: %i",(int)mldlUmlAbsolutExpirationTime);   
   printf("\nAnalist Id: %i\n",(int)mldlUmlAnalistId);
   printf("\nUser Id: %i\n",(int)mldlUmlUserId);
   printf("\nPassword: %s\n",mldlUmlPasswd);
   printf("\n----------------------------------------------------------------\n");
  #endif 
   
  if(mldlUmlRequestingUserId == mldlUmlUserId)
  {
   mldlUmlActualTime = time(NULL);
   #ifdef _MY_DEBUG_
    printf("\nCurrent time: %i\nExpiration: %i",(int)mldlUmlActualTime,(int)mldlUmlAbsolutExpirationTime);   
   #endif
 
   if(mldlUmlActualTime <= mldlUmlAbsolutExpirationTime)
   {
    if(!(mldlUmlNew = (mldlUmlUserDataType *)malloc(sizeof(mldlUmlUserDataType)))) 
    {
     while(mldlUmlFirst)
     {
      mldlUmlLast = mldlUmlFirst;
      mldlUmlFirst = mldlUmlFirst->mldlUmlNext;
      free(mldlUmlLast);
     }
     fclose(mldlUmlRequestingUsers);
     return mldlUmlMemoryAllocationError;
    }
   
    mldlUmlNew->mldlUmlId = mldlUmlUserId;
    strcpy(mldlUmlNew->mldlUmlNickname,mldlUmlNickname);
    strcpy(mldlUmlNew->mldlUmlPassword,mldlUmlPasswd);
    strcpy(mldlUmlNew->mldlUmlPasswordVerification,mldlUmlPasswd);
    mldlUmlNew->mldlUmlProfile = mldlUmlProfile;
    strcpy(mldlUmlNew->mldlUmlName,mldlUmlFullNameBuffer);
    strcpy(mldlUmlNew->mldlUmlNameVerification,mldlUmlFullNameBuffer);
    strcpy(mldlUmlNew->mldlUmlEmail,mldlUmlEmailBuffer);
    mldlUmlNew->mldlUmlNext = NULL;
    mldlUmlNew->mldlUmlPrevious = NULL;
    
    #ifdef _MY_DEBUG_
     printf("\nFirst element got all parameters\n");
    #endif

    if(!mldlUmlFirst)
    {
     mldlUmlFirst = mldlUmlNew;
     mldlUmlLast = mldlUmlNew;
     #ifdef _MY_DEBUG_
      printf("\nFirst element allocated succesfully\n");
     #endif
    }
    else
    {
     #ifdef _MY_DEBUG_
      printf("\n Another element added to list\n");
     #endif
     mldlUmlLast->mldlUmlNext = mldlUmlNew;
     mldlUmlNew->mldlUmlPrevious = mldlUmlLast;
     mldlUmlLast = mldlUmlNew;
    }
   }/* if(mldlUmlActualTime <= mldlUmlAbsolutExpirationTime) ends */
  }/* if(mldlUmlRequestingUserId == mldlUmlUserId) ends */  
  #ifdef _MY_DEBUG_
   if(feof(mldlUmlRequestingUsers))
    printf("\nmldlUmlRequestingUser reached EOF\n");
  #endif
  mldlUmlCounter++;
 }/* while(!feof(mldlUmlRequestingUsers)) ends */
 
 if(mldlUmlFirst == NULL)
  return mldlUmlIdNotFoundInRequestFile;
 
 if(ferror(mldlUmlRequestingUsers))
 {
  fclose(mldlUmlRequestingUsers);
  return mldlUmlFileError;
 }
 
 fclose(mldlUmlRequestingUsers);
 fclose(mldlUmlUsersFile);

 *mldlUmlFirstData = mldlUmlFirst;
 return mldlUmlOk; 
}

/*$RCSFile$*/
