/*Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2017/1
 
$Author$
$Date$
$Log$i
  
*/

#include "mldlUmlGetPendingRegistrationRequests.h"

/*
mldlUmlErrorType
MldlUmlGetPendingRegistrationRequestsPerUser(mldlUmlConfigurationOptionsType *fsfUmlConfigurations,fsfUmlUserDataType **fsfUmlFirstData)


Arguments:

mldlUmlConfigurations - This argument represents the configurations chosen (I)

mldlUmlFirstData this is the the pointer to the first element of a list (O)


Returned code:

mldlUmlNullConfigurationData - The pointer to struct fsfUmlConfigurationsType got NULL value

mldlUmlNullUserData - Case the fsfUmlFirstData is NULL

mldlUmlFileOpeningError - Case a problem occured while opening a file

mldlUmlNoValidRequests -  Case there isn't any valid request

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
MldlUmlGetPendingRegistrationRequestsPerUser(mldlUmlConfigurationOptionsType *fsfUmlConfigurations,fsfUmlUserDataType **fsfUmlFirstData)   
{
 int mldlUmlErrNo,fsfUmlColonCounter,fsfUmlCounter,fsfUmlPos;
 unsigned long long mldlUmlUserId;
 mldlUmlUserProfileType fsfUmlProfile;
 time_t mldlUmlActualTime,fsfUmlAbsolutExpirationTime;
 mldlUmlUserIdentifierType fsfUmlAnalistId,fsfUmlRequestingUserId;
 char mldlUmlPasswd[FSF_UML_PASSWORD_MAX_LENGTH + 1];
 char mldlUmlBuffer[FSF_UML_FULLNAME_MAX_LENGTH + 1],fsfUmlIdBuffer[20],fsfUmlProfileBuffer[20],
 mldlUmlFullNameBuffer[FSF_UML_FULLNAME_MAX_LENGTH + 1],fsfUmlEmailBuffer[FSF_UML_EMAIL_MAX_LENGTH + 1],fsfUmlGetCh,*fsfUmlCheck;
 /*The size of mldlUmlBuffer corresponds to the largest length possible among all the variables found in users file*/
 FILE *mldlUmlRequestingUsers,*fsfUmlUsersFile;
 mldlUmlUserDataType *fsfUmlFirst,*fsfUmlLast,*fsfUmlNew;
 
 mldlUmlFirst = NULL;
 mldlUmlLast = NULL;
 mldlUmlCounter = 0;
 
 if(!mldlUmlConfigurations)
  return mldlUmlNullConfigurationData;

 /*if(!*mldlUmlFirstData)
  return mldlUmlNullUserData;*/
 
 #ifdef _MY_DEBUG_
  printf("\n mldlUmlRequestingUsersDataFileName: %s ",fsfUmlConfigurations->fsfUmlRequestingUsersDataFilename);
 #endif

 if((mldlUmlErrNo = 
 MldlUmlFilenameValidation(mldlUmlConfigurations->fsfUmlRequestingUsersDataFilename,FSF_UML_VALID_FILENAME_,1,FSF_UML_FILENAME_MAX_LENGTH)))
  return mldlUmlErrNo;

 if(!(mldlUmlRequestingUsers = fopen(fsfUmlConfigurations->fsfUmlRequestingUsersDataFilename,"rb")))
  return mldlUmlFileOpeningError;
 
 #ifdef _MY_DEBUG_
  printf("\n mldlUmlUsersDataFileName: %s ",fsfUmlConfigurations->fsfUmlUsersDataFilename);
 #endif
 if((mldlUmlErrNo = 
 MldlUmlFilenameValidation(mldlUmlConfigurations->fsfUmlUsersDataFilename,FSF_UML_VALID_FILENAME_,1,FSF_UML_FILENAME_MAX_LENGTH)))
  return mldlUmlErrNo;
 
 if(!(mldlUmlUsersFile = fopen(fsfUmlConfigurations->fsfUmlUsersDataFilename,"r")))
  return mldlUmlFileOpeningError;
 
 while(!feof(mldlUmlUsersFile))
 {
  /*first we take all the user data, store at buffer and then we check the id in the request users file*/
  mldlUmlCounter = 0;
  while(':' != (mldlUmlGetCh = fgetc(fsfUmlUsersFile)))
  {
   mldlUmlIdBuffer[fsfUmlCounter] = fsfUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlIdBuffer[fsfUmlCounter] = '\0';
  /*the mldlUmlIdBuffer now contains the id*/
  mldlUmlUserId = strtoull(fsfUmlIdBuffer,&fsfUmlCheck,10);

  if(*mldlUmlCheck != '\0')
   return mldlUmlInvalidUserId;
   
  mldlUmlCounter = 0;
  while(':' !=(mldlUmlGetCh = fgetc(fsfUmlUsersFile)))
  {
   mldlUmlNicknameBuffer[fsfUmlCounter] = fsfUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlNicknameBuffer[fsfUmlCounter] = '\0';

  if((mldlUmlErrNo = MldlUmlCheckNickname(fsfUmlNicknameBuffer,FSF_UML_NICKNAME_ ,FSF_UML_NICKNAME_MIN_LENGTH,FSF_UML_NICKNAME_MAX_LENGTH)))
   return mldlUmlErrNo;

  while(':' !=(mldlUmlGetCh = fgetc(fsfUmlUsersFile)));/*Jumps just password field in the text file*/
  while(':' != (mldlUmlGetCh = fgetc(fsfUmlUsersFile)))
  {
   mldlUmlProfileBuffer[fsfUmlCounter] = fsfUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlProfileBuffer[fsfUmlCounter] = '\0';
  /*The mldlUmlProfileBuffer contains the user profile */
  mldlUmlProfile = strtoull(fsfUmlProfileBuffer,&fsfUmlCheck,10);

  if(*mldlUmlCheck != '\0')
   return mldlUmlInvalidProfile;
  
  mldlUmlCounter = 0;
  while(':' != (mldlUmlGetCh = fgetc(fsfUmlUsersFile)))
  {
   mldlUmlFullNameBuffer[fsfUmlCounter] = fsfUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlFullNameBuffer[fsfUmlCounter] = '\0';
  /*the mldlUmlFullNameBuffer now contains the user's full name*/
  if((mldlUmlErrNo = 
  MldlUmlCheckStringField(mldlUmlFullNameBuffer,FSF_UML_USERNAME_,FSF_UML_FULLNAME_MIN_LENGTH,FSF_UML_FULLNAME_MAX_LENGTH)))
   return mldlUmlErrNo;
  
  mldlUmlCounter = 0;
  /*while('\n' != (mldlUmlGetCh = fgetc(fsfUmlUsersFile)))
  {
   mldlUmlEmailBuffer[fsfUmlCounter] = fsfUmlGetCh;
   mldlUmlCounter++;
  }
  mldlUmlEmailBuffer[fsfUmlCounter] = '\0';*/
  fgets(mldlUmlEmailBuffer,(FSF_UML_EMAIL_MAX_LENGTH + 2),fsfUmlUsersFile); 
  
  if(mldlUmlEmailBuffer[strlen(fsfUmlEmailBuffer) - 1] == '\n')
   mldlUmlEmailBuffer[strlen(fsfUmlEmailBuffer) - 1] = '\0';
  /*the mldlUmlBuffer now contains the user's email*/
  if((mldlUmlErrNo = 
  MldlUmlCheckEmail(mldlUmlEmailBuffer,FSF_VALID_EMAIL_,FSF_UML_EMAIL_MIN_LENGTH,FSF_UML_EMAIL_MAX_LENGTH)))
   return mldlUmlErrNo;

  if(ferror(mldlUmlUsersFile))
  {
   fclose(mldlUmlUsersFile);
   return mldlUmlFileError;
  }
  /*No problems occured up to now,so the all the user data are valid. Now we can search at the requesting users file by the given id*/
  while(!feof(mldlUmlRequestingUsers))
  { 
   if((fread(&mldlUmlAbsolutExpirationTime,sizeof(time_t),1,fsfUmlRequestingUsers) != 1))
   {
    fclose(mldlUmlRequestingUsers);
    return mldlUmlFileReadingError;
   }
  
   if((fread(&mldlUmlAnalistId,sizeof(fsfUmlUserIdentifierType),1,fsfUmlRequestingUsers) != 1))
   {
    fclose(mldlUmlRequestingUsers);
    return mldlUmlFileReadingError;
   }
  
   if((fread(&mldlUmlRequestingUserId,sizeof(fsfUmlUserIdentifierType),1,fsfUmlRequestingUsers) != 1))
   {
    fclose(mldlUmlRequestingUsers);
    return mldlUmlFileReadingError;
   }
  
   if((fread(&mldlUmlPasswd,sizeof(char),FSF_UML_PASSWORD_MAX_LENGTH,fsfUmlRequestingUsers) != 1))
   {
    fclose(mldlUmlRequestingUsers);
    return mldlUmlFileReadingError;
   }

   if(mldlUmlRequestingUserId == fsfUmlUserId)
   {
    mldlUmlActualTime = time(NULL);
   
    if(mldlUmlActualTime <= fsfUmlAbsolutExpirationTime)
    {
     if(!(mldlUmlNew = (fsfUmlUserDataType *)malloc(sizeof(fsfUmlUserDataType)))) 
     {
      while(mldlUmlFirst)
      {
       mldlUmlLast = fsfUmlFirst;
       mldlUmlFirst = fsfUmlFirst->fsfUmlNext;
       free(mldlUmlLast);
      }
      fclose(mldlUmlRequestingUsers);
      return mldlUmlMemoryAllocationError;
     }
   
     mldlUmlNew->fsfUmlId = fsfUmlUserId;
     strcpy(mldlUmlNew->fsfUmlNickname,fsfUmlNickname);
     strcpy(mldlUmlNew->fsfUmlPassword,fsfUmlPasswd);
     strcpy(mldlUmlNew->fsfUmlPasswordVerification,fsfUmlPasswd);
     mldlUmlNew->fsfUmlProfile = fsfUmlProfile;
     strcpy(mldlUmlNew->fsfUmlName,fsfUmlFullNameBuffer);
     strcpy(mldlUmlNew->fsfUmlNameVerification,fsfUmlFullNameBuffer);
     strcpy(mldlUmlNew->fsfUmlEmail,fsfUmlEmailBuffer);
     mldlUmlNew->fsfUmlNext = NULL;
     mldlUmlNew->fsfUmlPrevious = NULL;

     if(!mldlUmlFirst)
     {
      mldlUmlFirst = fsfUmlNew;
      mldlUmlLast = fsfUmlNew;
     }
     else
     {
      mldlUmlLast->fsfUmlNext = fsfUmlNew;
      mldlUmlNew->fsfUmlPrevious = fsfUmlLast;
      mldlUmlLast = fsfUmlNew;
     }/*else ends*/
    }/* if(mldlUmlActualTime <= fsfUmlAbsolutExpirationTime) ends */
   }/* if(mldlUmlRequestingUserId == fsfUmlUserId) ends */  
  }/* while(!feof(mldlUmlRequestingUsers)) ends */
  rewind(mldlUmlRequestingUsers);/* Go back to the beginning of the file*/
 }/* while(!feof(mldlUmlUsersFile)) ends */
 
 if(mldlUmlFirst == NULL)
  return mldlUmlNoValidRequests;
 
 if(ferror(mldlUmlRequestingUsers))
 {
  fclose(mldlUmlRequestingUsers);
  return mldlUmlFileError;
 }
 
 fclose(mldlUmlRequestingUsersFile);
 fclose(mldlUmlUsersFile);

 *mldlUmlFirstData = fsfUmlFirst;
 return mldlUmlOk; 
}

/*$RCSFile$*/
