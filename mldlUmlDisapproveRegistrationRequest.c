/*
	Universidade Federal do Rio de Janeiro
	Escola Politecnica
	Departamento de Eletronica e de Computacao
	EEL270 - Computacao II - Turma 2017/1
	Prof. Marcelo Luiz Drumond Lanza
	Autor: Mateus da Silva Gilbert

	$Author$
	$Date$
	$Log$

*/

#define _XOPEN_SOURCE 		500

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "mldlUmlDisapproveRegistrationRequest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mldlUmlTypes.h"
#include "mldlUmlConst.h"
#include "mldlUmlFunctions.h"

mldlUmlErrorType
MldlUmlDisapproveRegistrationRequest (mldlUmlConfigurationOptionsType *mldlUmlConfigurationOptions, char *mldlUmlUsername, 
											char *mldlUmlRequesterUsername)
{
	mldlUmlErrorType mldlUmlError;
	FILE *mldlUmlRead, *mldlUmlWrite;
	char mldlUmlBuffer[MLDL_UML_BUFFER_SIZE], *mldlUmlDoubleDotPosition, *mldlUmlNextDoubleDot, *mldlUmlValidation;
	char mldlUmlStringCompare[MLDL_UML_STRING_MAXIMUM_SIZE], *mldlUmlWritingAuxiliary, *mldlUmlSecondWritingAuxiliary;
	char mldlUmlBackupName[MLDL_UML_FILE_NAME_MAXIMUM_SIZE + 5];
	char mldlUmlTemporaryFilename[MLDL_UML_FILE_NAME_MAXIMUM_SIZE] = "tempXXXXXX";
	char mldlUmlUserIdForm[MLDL_UML_ID_MAXIMUM_SIZE], mldlUmlRequesterIdForm[MLDL_UML_ID_MAXIMUM_SIZE];
	unsigned long long mldlUmlUserId, mldlUmlRequesterId;
	unsigned mldlUmlIndex;
	mldlUmlBoolean mldlUmlFound = mldlUmlFalse;
	mldlUmlRequest mldlUmlReadingAuxiliary;
	int mldlUmlFileDescriptor;

	if (!(mldlUmlConfigurationOptions))
		return mldlUmlNoConfigurationOptions;

	if (!(mldlUmlUsername))
		return mldlUmlEmptyUsername;

	if (!(mldlUmlRequesterUsername))
		return mldlUmlEmptyRequesterUsername;

	if (!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "r"))))
		return mldlUmlUnableToOpenFile;

	while (!(mldlUmlFound) && fgets(mldlUmlBuffer, sizeof(mldlUmlBuffer), mldlUmlRead))
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

		if (!(strcmp(mldlUmlStringCompare, mldlUmlUsername)))
			mldlUmlFound = mldlUmlTrue;
	}

	if (!(mldlUmlFound))
	{
		fclose(mldlUmlRead);	
		return mldlUmlUserNotFound;
	}

	for (mldlUmlIndex = 0; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex++)
		mldlUmlUserIdForm[mldlUmlIndex] = mldlUmlBuffer[mldlUmlIndex];

	mldlUmlUserIdForm[mldlUmlIndex] = EOS;

	mldlUmlUserId = (unsigned long long) strtoll(mldlUmlUserIdForm, &mldlUmlValidation, 10);

	if (*mldlUmlValidation != EOS)
	{
		fclose(mldlUmlRead);
		return mldlUmlCorruptedFile;
	}

	mldlUmlFound = mldlUmlFalse;

	while (!(mldlUmlFound) && fgets(mldlUmlBuffer, sizeof(mldlUmlBuffer), mldlUmlRead))
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

		if (!(strcmp(mldlUmlStringCompare, mldlUmlRequesterUsername)))
			mldlUmlFound = mldlUmlTrue;
	}

	fclose(mldlUmlRead);	

	if (!(mldlUmlFound))
		return mldlUmlRequestingUserNotFound;

	for (mldlUmlIndex = 0; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex++)
		mldlUmlRequesterIdForm[mldlUmlIndex] = mldlUmlBuffer[mldlUmlIndex];

	mldlUmlRequesterIdForm[mldlUmlIndex] = EOS;

	mldlUmlRequesterId = (unsigned long long) strtoll(mldlUmlRequesterIdForm, &mldlUmlValidation, 10);

	if (*mldlUmlValidation != EOS)
		return mldlUmlCorruptedFile;

	if(!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename, "rb"))))
		return mldlUmlUnableToOpenFile;

	mldlUmlFound = mldlUmlFalse;

	while (!(mldlUmlFound) && fread(&mldlUmlReadingAuxiliary, sizeof(mldlUmlRequest), 1, mldlUmlRead))
		if ( mldlUmlReadingAuxiliary.mldlUmlRequestingUserId == mldlUmlRequesterId)
			mldlUmlFound = mldlUmlTrue;

	fclose(mldlUmlRead);

	if (!(mldlUmlFound))
		return mldlUmlInvalidId;

	if (mldlUmlReadingAuxiliary.mldlUmlExpirationDate < time(NULL))
		return mldlUmlExpiredRequest;

	if (mldlUmlReadingAuxiliary.mldlUmlAnalyserId != mldlUmlUserId)
		return mldlUmlPermissionDenied;

	if (!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "r"))))
		return mldlUmlUnableToOpenFile;

	if ((mldlUmlFileDescriptor = mkstemp(mldlUmlTemporaryFilename)) == -1)
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToObtainFileDescriptor;
	}

	if (!(mldlUmlWrite = fdopen(mldlUmlFileDescriptor, "w")))
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToOpenTemporaryFile;
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
			remove(mldlUmlTemporaryFilename);
			return mldlUmlCorruptedFile;
		}

		mldlUmlNextDoubleDot = (mldlUmlDoubleDotPosition + 1);

		while ((*mldlUmlNextDoubleDot != ':') && (*mldlUmlNextDoubleDot != EOS))
			mldlUmlNextDoubleDot++;

		if (mldlUmlNextDoubleDot == EOS)
		{
			fclose(mldlUmlRead);
			fclose(mldlUmlWrite);
			remove(mldlUmlTemporaryFilename);
			return mldlUmlCorruptedFile;
		}

		for((mldlUmlIndex = 0, ++mldlUmlDoubleDotPosition); mldlUmlDoubleDotPosition != mldlUmlNextDoubleDot;
			(mldlUmlIndex++, mldlUmlDoubleDotPosition++))
			mldlUmlStringCompare[mldlUmlIndex] = *mldlUmlDoubleDotPosition;

		mldlUmlStringCompare[mldlUmlIndex] = EOS;

		if (strcmp(mldlUmlStringCompare, mldlUmlRequesterUsername))
			fprintf(mldlUmlWrite, "%s", mldlUmlBuffer);
	}

	if (ferror(mldlUmlRead))
	{
		fclose(mldlUmlRead);
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFilename);
		return mldlUmlErrorDuringFileCopy;
	}

	fclose(mldlUmlRead);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFilename);
		return mldlUmlErrorDuringFileCopy;
	}

	fclose(mldlUmlWrite);

	mldlUmlWritingAuxiliary = (char *) malloc((strlen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename) + 1));
	strcpy(mldlUmlWritingAuxiliary, (*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename);

	snprintf(mldlUmlBackupName, (strlen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename) + strlen(".bak") + 1), "%s%s",
	         (*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, ".bak");

	if (rename((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, mldlUmlBackupName))
	{
		remove(mldlUmlTemporaryFilename);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}

	if (rename(mldlUmlTemporaryFilename, mldlUmlWritingAuxiliary))
	{
		remove(mldlUmlTemporaryFilename);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}

	free(mldlUmlWritingAuxiliary);

	if (!(mldlUmlRead = (fopen((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename, "rb"))))
		return mldlUmlUnableToOpenFile;

	strcpy(mldlUmlTemporaryFilename, "tempXXXXXX");

	if ((mldlUmlFileDescriptor = mkstemp(mldlUmlTemporaryFilename)) == -1)
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToObtainFileDescriptor;
	}

	if (!(mldlUmlWrite = fdopen(mldlUmlFileDescriptor, "wb")))
	{
		fclose(mldlUmlRead);
		return mldlUmlUnableToOpenTemporaryFile;
	}

	while (fread(&mldlUmlReadingAuxiliary, sizeof(mldlUmlRequest), 1, mldlUmlRead))
		if (mldlUmlReadingAuxiliary.mldlUmlRequestingUserId != mldlUmlRequesterId)
			fwrite(&mldlUmlReadingAuxiliary, sizeof(mldlUmlRequest), 1, mldlUmlWrite);

	if (ferror(mldlUmlRead))
	{
		fclose(mldlUmlRead);
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFilename);
		return mldlUmlErrorDuringFileCopy;
	}
	
	fclose(mldlUmlRead);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		remove(mldlUmlTemporaryFilename);
		return mldlUmlErrorDuringFileCopy;
	}
	
	fclose(mldlUmlWrite);

	mldlUmlWritingAuxiliary = (char *) malloc((strlen((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename) + 1));
	strcpy(mldlUmlWritingAuxiliary, (*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename);

	snprintf(mldlUmlBackupName, (strlen((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename) + strlen(".bak") + 1), "%s%s",
				(*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename, ".bak");

	if (rename((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename, mldlUmlBackupName))
	{
		remove(mldlUmlTemporaryFilename);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}

	if (rename(mldlUmlTemporaryFilename, mldlUmlWritingAuxiliary))
	{
		remove(mldlUmlTemporaryFilename);
		free(mldlUmlWritingAuxiliary);
		return mldlUmlErrorRenamingFile;
	}

	free(mldlUmlWritingAuxiliary);

	printf("End\n");
	/* send e-mail */

	return mldlUmlOk;
}

/*	$RCSfile$ */
