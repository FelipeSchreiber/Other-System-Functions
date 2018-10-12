/* Universidade Federal do Rio de Janeiro
*  Escola Politecnica
*  Departamento de Eletronica e de Computacao
*  Prof. Marcelo Luiz Drumond Lanza
*  EEL 270 - Computacao II - Turma 2017/1
* 
*  $Author: $
*  $Date: $
*  $Log: $
*/

#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"
#include "mldlUmlFunctions.h"
#include "mldlUmlConst.h"

/*
 * mldlUmlErrorType
 * MldlUmlGetUsers (mldlUmlConfigurationOptionsType *mldlUmlConfiguration, mldlUmlUserDataType **mldlUmlFirstRequest)
 * Arguments:
 * mldlUmlConfigurationOptionsType * - Configuration
 * mldlUmlUserDataType ** - user's information list
 *
 * Returned code:
 * mldlUmlErrorType - Validation
  . . .
 * Description:
 * Lists all users in the database
 */
mldlUmlErrorType
MldlUmlGetUsers (mldlUmlConfigurationOptionsType *mldlUmlConfiguration, mldlUmlUserDataType **mldlUmlFirst)
{
	size_t mldlUmlIndexPoint = 0, mldlUmlLength;
	FILE *mldlUmlUserFile, *mldlUmlAbeyances;
	unsigned mldlUmlTest;
	char mldlUmlBuffer[2], mldlUmlPassword[17];
	bool mldlUmlFound = false;
	mldlUmlUserDataType *mldlUmlPrevious, *mldlUmlNew, *mldlUmlHelper;

	if(!mldlUmlFirst)
		return mldlUmlNullUserData;

	if(!mldlUmlConfiguration)
	{	
		mldlUmlTest = MldlUmlGetConfigurationOptionsValues (DEFAULT_CFG, mldlUmlConfiguration);
		if (mldlUmlTest)
			return mldlUmlTest;
	}
	if((!mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "r")))
	{
		return mldlUmlErrorOpenningFile;
	}

	mldlUmlFirst = NULL;
	if (!(mldlUmlFirst = (mldlUmlUserDataType *) malloc (sizeof (mldlUmlUserDataType))))
    {
		fclose (mldlUmlUserFile);
		return mldlUmlErrorAllocatingMemory;			  
	}

	memset (mldlUmlFirst, 0x00, sizeof (mldlUmlUserDataType));

	mldlUmlFirst->next = NULL;
	mldlUmlFirst->previous = NULL;

	mldlUmlNew = mldlUmlFirst;

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
			strcpy(mldlUmlNew->emailConfirmation, mldlUmlNew->email);
			strcpy(mldlUmlNew->nameConfirmation, mldlUmlNew->name);

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
				return mldlUmlErrorAllocatingMemory;			  
			}
			memset (mldlUmlNew, 0x00, sizeof (mldlUmlUserDataType));		
		}
	}
	if(mldlUmlNew)	
		free(mldlUmlNew);

	#ifdef DEBUGGING
	printf("Chained list:\n\n");
	while(mldlUmlFirst)
	{
		mldlUmlHelper = mldlUmlFirst;
		printf("->id: %Lu\n", mldlUmlFirst->id);
		printf("->nickname: %s\n", mldlUmlFirst->nickname);
		mldlUmlFirst = mldlUmlFirst->next;
		free(mldlUmlHelper);
	}
	#endif			

	fclose(mldlUmlUserFile);
	
	*mldlUmlFirstRequest = mldlUmlFirst;

	return mldlUmlOk;

}
#endif	

/* $RCSfile:$ */
