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
#ifndef _MLDL_UML_ADD_USER_H
#define _MLDL_UML_ADD_USER_H "@(#)mldlUmlAddUser.h $Revision:$"

#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"
#include "mldlUmlFunctions.h"
#include "mldlUmlConst.h"

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
MldlUmlAddUser (mldlUmlConfigurationOptionsType *mldlUmlConfiguration, mldlUmlUserDataType *mldlUmlUserData)
{
 size_t mldlUmlIndexPoint = 0, mldlUmlLength;
 FILE *mldlUmlUserFile, *mldlUmlAbeyances;
 unsigned mldlUmlTest;
 char mldlUmlBuffer[2], mldlUmlPassword[17];
 boolean mldlUmlFound = false;
 mldlUmlUserDataType *mldlUmlFirst, *mldlUmlPrevious, *mldlUmlNew, *mldlUmlHelper;

 if(!mldlUmlUserData)
  return 1 \*error*\;

 if(!mldlUmlConfiguration)
 {	
  mldlUmlTest = MldlUmlGetConfigurationOptionsValues (DEFAULT_CFG, mldlUmlConfiguration);
  if (mldlUmlTest)
  return 1 \*error*\;
 }
 
 if((mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "r")))
 {
  fclose(mldlUmlUserFile);
  if(mldlUmlUserData->profile == 0)
  return 1 \*error*\;
 }
	
 if(!(mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "a")))
  return 1 \*error*\;

 fclose(mldlUmlUserFile);

 if(!(mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "r")))
		return 1 \*error*\;


	mldlUmlFirst = NULL;
	if (!(mldlUmlFirst = (mldlUmlUserDataType *) malloc (sizeof (mldlUmlUserDataType))))
    {
		fclose (mldlUmlUserFile);
		return 1 \*error*\;			  
	}

	memset (mldlUmlFirst, 0x00, sizeof (mldlUmlUserDataType));

	mldlUmlFirst->next = NULL;
	mldlUmlFirst->previous = NULL;

	mldlUmlNew  = mldlUmlFirst;

	mldlUmlUserData->id = 0;

	mldlUmlPrevious = NULL;
	printf("\n\nBuffer: ");
	while ((fgets (mldlUmlBuffer, 2, mldlUmlUserFile)) != NULL) 
	{
		printf("%s", mldlUmlBuffer);
		if(mldlUmlBuffer[0] == ':')
		{	
			mldlUmlIndexPoint++;
		}
		else
		{
			switch (mldlUmlIndexPoint)
			{
				case 0:
					mldlUmlNew->id = (mldlUmlNew -> id * 10) + (mldlUmlBuffer[0] - '0');
				break;

				case 1:
					mldlUmlLength = strlen(mldlUmlNew->nickname);
					mldlUmlNew->nickname[mldlUmlLength] = mldlUmlBuffer[0];
					mldlUmlNew->nickname[mldlUmlLength + 1] = '\0';
				break;
					
				case 2:
					mldlUmlLength = strlen(mldlUmlNew->password);
					mldlUmlNew->password[mldlUmlLength] = mldlUmlBuffer[0];
					mldlUmlNew->password[mldlUmlLength + 1] = '\0';
				break;
					
				case 3:
					mldlUmlNew->profile = (mldlUmlNew -> profile * 10) + (mldlUmlBuffer[0] - '0');
				break;
					
				case 4:
					mldlUmlLength = strlen(mldlUmlNew->name);
					mldlUmlNew->name[mldlUmlLength] = mldlUmlBuffer[0];
					mldlUmlNew->name[mldlUmlLength + 1] = '\0';
				break;

				case 5:
					mldlUmlLength = strlen(mldlUmlNew->email);
					mldlUmlNew->email[mldlUmlLength] = mldlUmlBuffer[0];
					mldlUmlNew->email[mldlUmlLength + 1] = '\0';
				break;			
			}
		}

		if(mldlUmlBuffer[0] == '\n')
		{
			mldlUmlNew->email[strlen(mldlUmlNew->email) - 1] = '\0';

			#ifdef DEBUGGING
			printf("New->id: %Lu\n", mldlUmlNew->id);
			printf("New->nickname: %s\n", mldlUmlNew->nickname);
			#endif

			mldlUmlIndexPoint = 0;

			if(mldlUmlPrevious)
			{	
				mldlUmlNew->previous = mldlUmlPrevious;
				mldlUmlPrevious->next = mldlUmlNew;
				mldlUmlNew->next = NULL;
			}

			mldlUmlPrevious = mldlUmlNew;
			if (!(mldlUmlNew = (mldlUmlUserDataType *) malloc (sizeof (mldlUmlUserDataType))))
		    {
				while (mldlUmlFirst)
				{
					mldlUmlHelper = mldlUmlFirst;
					mldlUmlFirst = mldlUmlFirst->next;
					free (mldlUmlHelper);
				}
				fclose (mldlUmlUserFile);
				return 1 \*error*\;			  
			}
			memset (mldlUmlNew, 0x00, sizeof (mldlUmlUserDataType));

			if(mldlUmlPrevious->previous)
			{	
				mldlUmlHelper = mldlUmlPrevious->previous;
				if((mldlUmlPrevious->id - mldlUmlHelper->id) >=2 && !mldlUmlFound)
				{	
					mldlUmlFound = true;			
					mldlUmlUserData->id = mldlUmlHelper->id + 1;
					mldlUmlUserData->previous = mldlUmlHelper;
					mldlUmlUserData->next = mldlUmlPrevious;
					mldlUmlHelper->next = mldlUmlUserData;
					mldlUmlPrevious->previous = mldlUmlUserData;
					mldlUmlPrevious = mldlUmlUserData;
				}
			}		
		}
	}
	if(mldlUmlNew)	
		free(mldlUmlNew);

	if(mldlUmlPrevious)
	{	
		if(!mldlUmlFound)
		{

			mldlUmlUserData->id = mldlUmlPrevious->id + 1;
			mldlUmlUserData->previous = mldlUmlPrevious;
			mldlUmlUserData->next = NULL;
			mldlUmlPrevious->next = mldlUmlUserData;
		}
	}
	else
	{
		mldlUmlFirst = mldlUmlUserData;
		mldlUmlUserData->previous = NULL;
		mldlUmlUserData->next = NULL;
	}		

	fclose(mldlUmlUserFile);

	if(!strlen(mldlUmlUserData->password))
	{	
		MldlUmlCreateRandomString (RANDOM_PASSWORD_VALID_CHARS, 16, mldlUmlPassword);
		
		if(!(mldlUmlAbeyances = fopen(mldlUmlConfiguration->mldlUmlInvitedUsersDataFilename, "a")))
			return 1 \*error*\;
		
		fprintf(mldlUmlAbeyances, "%Lu:", mldlUmlUserData->id);
		fprintf(mldlUmlAbeyances, "%s:", mldlUmlPassword);
		fprintf(mldlUmlAbeyances, "%s\n", "time + 72hrs");
		fclose(mldlUmlAbeyances);

	}

	/*rewrite the file*/	
	
	if (!(mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "w"))) 
	{
		return 1 \*error*\;
	}

	#ifdef DEBUGGING
	printf("First->id: %Lu\n", mldlUmlFirst->id);
	printf("First->nickname: %s\n", mldlUmlFirst->nickname);
	printf("Previous->id: %Lu\n", mldlUmlPrevious->id);
	printf("Previous->nickname: %s\n", mldlUmlPrevious->nickname);
	printf("Previous->next->id: %Lu\n", mldlUmlPrevious->next->id);
	printf("Previous->next->nickname: %s\n", mldlUmlPrevious->next->nickname);
	#endif

	while (mldlUmlFirst)
	{
		fprintf(mldlUmlUserFile, "%Lu:", mldlUmlFirst->id);
		fprintf(mldlUmlUserFile, "%s:", mldlUmlFirst->nickname);
		fprintf(mldlUmlUserFile, "%s:", mldlUmlFirst->password);
		fprintf(mldlUmlUserFile, "%Lu:", mldlUmlFirst->profile);
		fprintf(mldlUmlUserFile, "%s:", mldlUmlFirst->name);
		fprintf(mldlUmlUserFile, "%s\n", mldlUmlFirst->email);

		mldlUmlHelper = mldlUmlFirst;
		mldlUmlFirst = mldlUmlFirst->next;
		if(mldlUmlHelper != mldlUmlUserData)
			free (mldlUmlHelper);
	}	

	fclose(mldlUmlUserFile);	

	return mldlUmlOk;

}
#endif	

/* $RCSfile:$ */
