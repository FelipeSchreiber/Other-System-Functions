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

#define  _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mldlUmlTypes.h"
#include "mldlUmlErrors.h"
#include "mldlUmlFunctions.h"
#include "mldlUmlConst.h"

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
MldlUmlRejectInvite(mldlUmlConfigurationOptionsType *mldlUmlConfiguration, char *mldlUmlLogin, char *mldlUmlPassword)
{
	unsigned mldlUmlTest, mldlUmlIndexPoint;
	size_t mldlUmlLines, mldlUmlLength, mldlUmlIndex, mldlUmlLine;

	char mldlUmlSearchLogin[66], mldlUmlSearchId[22], mldlUmlTempName[12] = "temp-XXXXXX", mldlUmlTempName2[12] = "temp-XXXXXX",
		mldlUmlBuffer[40], mldlUmlCharId[22], mldlUmlId[22], mldlUmlSearchPassword[17];

	FILE *mldlUmlOriginalFile, *mldlUmlNewFile, *mldlUmlUserFile;
	int mldlUmlNewFileId;

	bool mldlUmlFound = false;

	if(!mldlUmlLogin)
		return 1;/*error*/

	if(!mldlUmlPassword)
		return 1;/*error*/

	if(!mldlUmlConfiguration)
	{	
		mldlUmlTest = MldlUmlGetConfigurationOptionsValues (DEFAULT_CFG, mldlUmlConfiguration);
		if (mldlUmlTest)
			return 1;/*error*/
	}

	if(!(mldlUmlUserFile = fopen(mldlUmlConfiguration->mldlUmlUsersDataFilename, "r")))
		return 1;/*error*/

	mldlUmlSearchLogin[0] = '\0';
	
	/*Search id based on login*/
	#ifdef DEBUGGING 
	printf("\nSearch ID\n\n");
	#endif

	while ((fgets (mldlUmlBuffer, 2, mldlUmlUserFile)) != NULL) 
	{

		if(mldlUmlBuffer[0] == '\n')
		{	
			mldlUmlLines++;
			mldlUmlIndexPoint = 0;

			#ifdef DEBUGGING 
			printf("Login: %s\n", mldlUmlSearchLogin);
			#endif

			if(!strcmp(mldlUmlLogin, mldlUmlSearchLogin))
			{	
				strcpy(mldlUmlId, mldlUmlSearchId);
				#ifdef DEBUGGING 
				printf("Id: %s\n", mldlUmlId);
				#endif
			}	

			mldlUmlSearchLogin[0] = '\0';
			mldlUmlSearchId[0] = '\0';
		}

		if (mldlUmlIndexPoint == 0 && mldlUmlBuffer[0] != ':' && mldlUmlBuffer[0] != '\n')
		{ 
			mldlUmlLength = strlen(mldlUmlSearchId);
			mldlUmlSearchId[mldlUmlLength] = mldlUmlBuffer[0];
			mldlUmlSearchId[mldlUmlLength + 1] = '\0';
		} 	
		

		if (mldlUmlIndexPoint == 1 && mldlUmlBuffer[0] != ':' && mldlUmlBuffer[0] != '\n')
		{ 
			mldlUmlLength = strlen(mldlUmlSearchLogin);
			mldlUmlSearchLogin[mldlUmlLength] = mldlUmlBuffer[0];
			mldlUmlSearchLogin[mldlUmlLength + 1] = '\0';
		} 	

		if (mldlUmlBuffer[0] == ':')
			mldlUmlIndexPoint++;			  
	}
	fclose(mldlUmlUserFile);
	/*Remove from invited users file*/
	#ifdef DEBUGGING 
	printf("\nRemove from invited.users\n\n");
	#endif

	if (!(mldlUmlOriginalFile = fopen (mldlUmlConfiguration->mldlUmlInvitedUsersDataFilename, "r"))) 
		return 1;/*error*/
	
	if (!(mldlUmlNewFileId = mkstemp(mldlUmlTempName)))
		return 1;/*error*/
	

	if (!(mldlUmlNewFile = fdopen(mldlUmlNewFileId, "a"))) 
	{
		fclose(mldlUmlOriginalFile);
		return 1;/*error*/
	}

	while ((fgets (mldlUmlBuffer, 41, mldlUmlOriginalFile)) != NULL) 
	{
		mldlUmlCharId[0] = '\0';
		mldlUmlSearchPassword[0] = '\0';

		for (mldlUmlIndex = 0; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex++)
		{
			mldlUmlLength = strlen(mldlUmlCharId);
			mldlUmlCharId[mldlUmlLength] = mldlUmlBuffer[mldlUmlIndex];
			mldlUmlCharId[mldlUmlLength + 1] = '\0';
			if(mldlUmlBuffer[mldlUmlIndex] == '\n')
			{	
				fclose(mldlUmlOriginalFile);
				fclose(mldlUmlNewFile);
				remove(mldlUmlTempName);
				return 1;/*error*/
			}	
		}

		for (mldlUmlIndex++; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex++)
		{
			printf("%c", mldlUmlBuffer[mldlUmlIndex]);
			mldlUmlLength = strlen(mldlUmlSearchPassword);
			mldlUmlSearchPassword[mldlUmlLength] = mldlUmlBuffer[mldlUmlIndex];
			mldlUmlSearchPassword[mldlUmlLength + 1] = '\0';
			if(mldlUmlBuffer[mldlUmlIndex] == '\n')
			{	
				fclose(mldlUmlOriginalFile);
				fclose(mldlUmlNewFile);
				remove(mldlUmlTempName);
				return 1;/*error*/
			}	
		}
		
		#ifdef DEBUGGING
		printf("\n"); 
		printf("\nSearch Password: \"%s\"\n", mldlUmlSearchPassword);
		printf("Password: \"%s\"\n", mldlUmlPassword);
		printf("Id: %s\n", mldlUmlId);
		printf("Search Id: %s\n", mldlUmlCharId);
		#endif

		if(!strcmp(mldlUmlId, mldlUmlCharId))
		{	
			#ifdef DEBUGGING 
			strcpy(mldlUmlPassword, mldlUmlSearchPassword);
			#endif	
			if(strcmp(mldlUmlPassword, mldlUmlSearchPassword))
			{
				fclose(mldlUmlOriginalFile);
				fclose(mldlUmlNewFile);
				remove(mldlUmlTempName);
				return 1;/*error*/	
			}		
		}
		else
		{
			fprintf (mldlUmlNewFile, "%s", mldlUmlBuffer);
		}

	}

	fclose(mldlUmlOriginalFile);
	remove(mldlUmlConfiguration->mldlUmlInvitedUsersDataFilename);
	fclose(mldlUmlNewFile);
	rename(mldlUmlTempName, mldlUmlConfiguration->mldlUmlInvitedUsersDataFilename);

	/*remove from users file*/
	#ifdef DEBUGGING 
	printf("\nRemove from users\n\n");
	#endif

	if (!(mldlUmlOriginalFile = fopen (mldlUmlConfiguration->mldlUmlUsersDataFilename, "r"))) 
		return 1;/*error*/
	
	if (!(mldlUmlNewFileId = mkstemp(mldlUmlTempName2)))
		return 1;/*error*/
	

	if (!(mldlUmlNewFile = fdopen(mldlUmlNewFileId, "a"))) 
	{
		fclose(mldlUmlOriginalFile);
		return 1;/*error*/
	}

	mldlUmlCharId[0] = '\0';
	mldlUmlSearchPassword[0] = '\0';

	mldlUmlIndexPoint = 0;
	mldlUmlLines = 0;
	while ((fgets (mldlUmlBuffer, 2, mldlUmlOriginalFile)) != NULL && !mldlUmlFound) 
	{
		if(mldlUmlBuffer[0] == ':')
			mldlUmlIndexPoint++;

		if(!mldlUmlIndexPoint)
		{	
			mldlUmlLength = strlen(mldlUmlCharId);
			mldlUmlCharId[mldlUmlLength] = mldlUmlBuffer[0];
			mldlUmlCharId[mldlUmlLength + 1] = '\0';
		}

		if(mldlUmlBuffer[0] == '\n')
		{	
			mldlUmlIndexPoint = 0;

			if(!mldlUmlFound)
				mldlUmlLines++;

			#ifdef DEBUGGING
			printf("Id: %s\n", mldlUmlId);
			printf("Search Id: %s\n", mldlUmlCharId);
			printf("Lines: %lu\n", mldlUmlLines);
			#endif

			if(!strcmp(mldlUmlId, mldlUmlCharId))
				mldlUmlFound = true;

			mldlUmlCharId[0] = '\0';
			mldlUmlSearchPassword[0] = '\0';
		}
	}

	fclose(mldlUmlOriginalFile);
	system("lsof users");

	if (!(mldlUmlOriginalFile = fopen (mldlUmlConfiguration->mldlUmlUsersDataFilename, "r"))) 
		return 1;/*error*/

	#ifdef DEBUGGING 
	printf("Line to remove: %lu\n", mldlUmlLines);
	#endif

	mldlUmlLine = 1;
	while ((fgets (mldlUmlBuffer, 2, mldlUmlOriginalFile)) != NULL) 
	{
		if(mldlUmlLine != mldlUmlLines)
			fprintf (mldlUmlNewFile, "%c", mldlUmlBuffer[0]);

		if(mldlUmlBuffer[0] == '\n')
		{	
			mldlUmlLine++;
				
		}
	}

	fclose(mldlUmlOriginalFile);
	fclose(mldlUmlNewFile);
	remove(mldlUmlConfiguration->mldlUmlUsersDataFilename);
	rename(mldlUmlTempName2, mldlUmlConfiguration->mldlUmlUsersDataFilename);

	return 0;
}

/* $RCSfile:$ */