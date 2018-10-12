#ifdef __FreeBSD__
#define _WITH_DPRINTF_
#endif
#include <stdio.h>
#define _XOPEN_SOURCE 		500
#include <unistd.h>
#include <sys/types.h>
#include "mldlUmlAcceptInvite.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mldlUmlTypes.h"
#include "mldlUmlConst.h"
#include "mldlUmlFunctions.h"

mldlUmlErrorType
MldlUmlAcceptInvite (mldlUmlConfigurationOptionsType *mldlUmlConfigurationOptions, char *mldlUmlTemporaryPassword, mldlUmlUserDataType *mldlUmlUserData)
{
	mldlUmlErrorType mldlUmlError;
	FILE *mldlUmlRead, *mldlUmlWrite;
	char mldlUmlBuffer[MLDL_UML_BUFFER_SIZE], *mldlUmlDoubleDotPosition, *mldlUmlNextDoubleDot;
	char mldlUmlStringCompare[MLDL_UML_STRING_MAXIMUM_SIZE], *mldlUmlWritingAuxiliary, *mldlUmlSecondWritingAuxiliary;
	char mldlUmlBackupName[MLDL_UML_FILE_NAME_MAXIMUM_SIZE + 5];
	char mldlUmlTemporaryFileName[MLDL_UML_FILE_NAME_MAXIMUM_SIZE] = "tempXXXXXX";
	unsigned mldlUmlIndex;
	mldlUmlBoolean mldlUmlFound = mldlUmlFalse;
	mldlUmlInvite mldlUmlReadingAuxiliary;
	int mldlUmlFileDescriptor;

	if (!(mldlUmlConfigurationOptions))
		return mldlUmlNoConfigurationOptions;		/*include*/

	if (!(mldlUmlTemporaryPassword))
		return mldlUmlEmptyPassword;			/*include*/

	if (!(mldlUmlUserData))
		return mldlUmlNoUserData;			/*include*/

	if (!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename, "rb"))))
		return mldlUmlUnableToOpenFile;		/*include*/

	while ((fread(&mldlUmlReadingAuxiliary, sizeof(mldlUmlInvite), 1, mldlUmlRead)) && !(mldlUmlFound))
		if (mldlUmlReadingAuxiliary.mldlUmlUserId == (*mldlUmlUserData).mldlUmlUserId)
			mldlUmlFound = mldlUmlTrue;

	if (!(mldlUmlFound))
	{
		fclose(mldlUmlRead);
		return mldlUmlInvalidId;					/*include*/
	}

	if (mldlUmlReadingAuxiliary.mldlUmlExpirationDate > time(NULL))
	{
		fclose(mldlUmlRead);
		return mldlUmlExpiredInvite;			/*include*/
	}

	mldlUmlError = MldlUmlCheckPassword(mldlUmlTemporaryPassword, mldlUmlReadingAuxiliary.mldlUmlTemporaryPassword);	

	if (mldlUmlError)
	{
		fclose(mldlUmlRead);
		return mldlUmlIncorectPassword;		/*include*/
	}

	fclose(mldlUmlRead);

	if (!(mldlUmlRead = fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "r")))
		return mldlUmlUnableToOpenFile;			/*include*/

	mldlUmlFound = mldlUmlFalse;

	while (fgets(mldlUmlBuffer, sizeof(mldlUmlBuffer), mldlUmlRead) && !(mldlUmlFound))
	{
		mldlUmlDoubleDotPosition = mldlUmlBuffer;
		
		while((*mldlUmlDoubleDotPosition != ':') && (*mldlUmlDoubleDotPosition != EOS))
			mldlUmlDoubleDotPosition++;

		if (mldlUmlDoubleDotPosition == EOS)
		{
			fclose(mldlUmlRead);
			return mldlUmlCorruptedFile;
		}		

		mldlUmlNextDoubleDot = (mldlUmlDoubleDotPosition + 1);

		while((*mldlUmlNextDoubleDot != ':') && (*mldlUmlNextDoubleDot != EOS))
			mldlUmlNextDoubleDot++;

		if (mldlUmlNextDoubleDot == EOS)
		{
			fclose(mldlUmlRead);
			return mldlUmlCorruptedFile;
		}		

		for ((mldlUmlIndex = 0, ++mldlUmlDoubleDotPosition); mldlUmlDoubleDotPosition != mldlUmlNextDoubleDot;
			 (mldlUmlIndex++, mldlUmlDoubleDotPosition++))
			mldlUmlStringCompare[mldlUmlIndex] = *mldlUmlDoubleDotPosition;

		mldlUmlStringCompare[mldlUmlIndex] = EOS;

		if (!(strcmp(mldlUmlStringCompare, (*mldlUmlUserData).mldlUmlUserNickname)))
			mldlUmlFound = mldlUmlTrue;
	}

	fclose(mldlUmlRead);

	if (!(mldlUmlFound))
		return mldlUmlUserNotFound;				/*include*/

	if (!(mldlUmlRead = fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "r")))
		return mldlUmlUnableToOpenFile;			/*include*/

	if ((mldlUmlFileDescriptor = mkstemp(mldlUmlTemporaryFileName)) == -1)
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToObtainFileDescriptor; /*include*/
	}

	if(!(mldlUmlWrite = fdopen(mldlUmlFileDescriptor, "w")))
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToOpenTemporaryFile;   /*include*/
	}

	while (fgets(mldlUmlBuffer, sizeof(mldlUmlBuffer), mldlUmlRead))
	{
		mldlUmlDoubleDotPosition = mldlUmlBuffer;
		
		while((*mldlUmlDoubleDotPosition != ':') && (*mldlUmlDoubleDotPosition != EOS))
			mldlUmlDoubleDotPosition++;

		if (mldlUmlDoubleDotPosition == EOS)
		{
			fclose(mldlUmlRead);
			fclose(mldlUmlWrite);
			remove(mldlUmlTemporaryFileName);
			return mldlUmlCorruptedFile;
		}		

		mldlUmlNextDoubleDot = (mldlUmlDoubleDotPosition + 1);

		while((*mldlUmlNextDoubleDot != ':') && (*mldlUmlNextDoubleDot != EOS))
			mldlUmlNextDoubleDot++;

		if (mldlUmlNextDoubleDot == EOS)
		{
			fclose(mldlUmlRead);
			fclose(mldlUmlWrite);
			remove(mldlUmlTemporaryFileName);
			return mldlUmlCorruptedFile;    /*include*/
		}		

		for ((mldlUmlIndex = 0, ++mldlUmlDoubleDotPosition); mldlUmlDoubleDotPosition != mldlUmlNextDoubleDot;
			 (mldlUmlIndex++, mldlUmlDoubleDotPosition++))
			mldlUmlStringCompare[mldlUmlIndex] = *mldlUmlDoubleDotPosition;

		mldlUmlStringCompare[mldlUmlIndex] = EOS;

		if (!(strcmp(mldlUmlStringCompare, (*mldlUmlUserData).mldlUmlUserNickname)))
		{
			mldlUmlWritingAuxiliary = (char *) malloc(strlen(mldlUmlBuffer));

			snprintf(mldlUmlWritingAuxiliary, (mldlUmlDoubleDotPosition - mldlUmlBuffer) + 2, "%s", mldlUmlBuffer);

			mldlUmlSecondWritingAuxiliary = (char *) malloc(strlen(mldlUmlWritingAuxiliary) + strlen((*mldlUmlUserData).mldlUmlPassword) +
																			strlen(mldlUmlDoubleDotPosition) + 2);

			snprintf(mldlUmlSecondWritingAuxiliary, (strlen(mldlUmlWritingAuxiliary) + strlen((*mldlUmlUserData).mldlUmlPassword) + 
				strlen(mldlUmlDoubleDotPosition) + 2),	"%s%s%s", mldlUmlWritingAuxiliary, ((*mldlUmlUserData).mldlUmlPassword), 
				(mldlUmlDoubleDotPosition + 1));

			fprintf(mldlUmlWrite, "%s", mldlUmlSecondWritingAuxiliary);	

			free(mldlUmlWritingAuxiliary);
			free(mldlUmlSecondWritingAuxiliary);
		}
		else
			fprintf(mldlUmlWrite, "%s", mldlUmlBuffer);	
	}

	if (ferror(mldlUmlRead))
	{
		fclose(mldlUmlRead);
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFileName);
		return mldlUmlErrorDuringFileCopy; /*include*/
	}	
	
	fclose(mldlUmlRead);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFileName);
		return mldlUmlErrorDuringFileCopy; /*include*/
	}	

	fclose(mldlUmlWrite);

	mldlUmlWritingAuxiliary = (char *) malloc((strlen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename) + 1));
	strcpy(mldlUmlWritingAuxiliary, (*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename);

	snprintf(mldlUmlBackupName, (strlen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename) + strlen(".bak") + 1), "%s%s",
				(*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, ".bak");

	if (rename((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, mldlUmlBackupName))
	{
		remove(mldlUmlTemporaryFileName);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;	/*include*/
	}

	if (rename(mldlUmlTemporaryFileName, mldlUmlWritingAuxiliary))
	{
		remove(mldlUmlTemporaryFileName);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}
	
	free(mldlUmlWritingAuxiliary);

	if (!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename, "rb"))))
		return mldlUmlUnableToOpenFile;		/*include*/

	strcpy(mldlUmlTemporaryFileName, "tempXXXXXX");
	
	if ((mldlUmlFileDescriptor = mkstemp(mldlUmlTemporaryFileName)) == -1)
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToObtainFileDescriptor; /*include*/
	}

	if(!(mldlUmlWrite = fdopen(mldlUmlFileDescriptor, "wb")))
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToOpenTemporaryFile;   /*include*/
	}

	while (fread(&mldlUmlReadingAuxiliary, sizeof(mldlUmlInvite), 1, mldlUmlRead))
		if (mldlUmlReadingAuxiliary.mldlUmlUserId != (*mldlUmlUserData).mldlUmlUserId)
			fwrite(&mldlUmlReadingAuxiliary, sizeof(mldlUmlInvite), 1, mldlUmlWrite);

	if (ferror(mldlUmlRead))
	{
		fclose(mldlUmlRead);
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFileName);
		return mldlUmlErrorDuringFileCopy; /*include*/
	}	
	
	fclose(mldlUmlRead);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFileName);
		return mldlUmlErrorDuringFileCopy; /*include*/
	}	

	fclose(mldlUmlWrite);

	mldlUmlWritingAuxiliary = (char *) malloc((strlen((*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename) + 1));
	strcpy(mldlUmlWritingAuxiliary, (*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename);
	
	snprintf(mldlUmlBackupName, (strlen((*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename) + strlen(".bak") + 1), "%s%s",
				(*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename, ".bak");

	if (rename((*mldlUmlConfigurationOptions).mldlUmlInvitedUsersDataFilename, mldlUmlBackupName))
	{
		remove(mldlUmlTemporaryFileName);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}

	if (rename(mldlUmlTemporaryFileName, mldlUmlWritingAuxiliary))
	{
		remove(mldlUmlTemporaryFileName);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}
	
	free(mldlUmlWritingAuxiliary);
	
	printf("End\n");
	/* send e-mail */

	return mldlUmlOk;
}
