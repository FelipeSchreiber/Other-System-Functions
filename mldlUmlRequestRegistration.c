#define _XOPEN_SOURCE 		500

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "mldlUmlRequestRegistration.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mldlUmlTypes.h"
#include "mldlUmlConst.h"
#include "mldlUmlFunctions.h"

mldlUmlErrorType
MldlUmlRequestRegistration (mldlUmlConfigurationOptionsType *mldlUmlConfigurationOptions, char *mldlUmlResponsibleUserEmail, 
									mldlUmlUserDataType *mldlUmlUserData)
{
	mldlUmlErrorType mldlUmlError;
	mldlUmlRequest *mldlUmlRequestingForm;
	FILE *mldlUmlRead, *mldlUmlWrite;
	char mldlUmlBuffer[MLDL_UML_BUFFER_SIZE], mldlUmlStringCompare[MLDL_UML_STRING_MAXIMUM_SIZE];
	char *mldlUmlCompareEmail, *mldlUmlIdForm, *mldlUmlProfileForm, *mldlUmlValidation;
	unsigned mldlUmlIndex, mldlUmlBufferSize;
	int mldlUmlFileDescriptor;
	mldlUmlBoolean mldlUmlFound = mldlUmlFalse;

	if (!(mldlUmlConfigurationOptions))
		return mldlUmlNoConfigurationOptions;

	if (!(mldlUmlResponsibleUserEmail))
		return mldlUmlEmptyResponsibleUserEmail;

	if (!(mldlUmlUserData))
		return mldlUmlNoUserData;

	if (!(mldlUmlRead = fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "r")))
		return mldlUmlUnableToOpenFile;

	while (fgets(mldlUmlBuffer, sizeof(mldlUmlBuffer), mldlUmlRead) && (!(mldlUmlFound)))
	{
		if ((mldlUmlBufferSize = strlen(mldlUmlBuffer)) > MLDL_UML_STRING_MAXIMUM_SIZE)
		{
			fclose(mldlUmlRead);
			return mldlUmlCorruptedFile;
		}

		for (mldlUmlIndex = mldlUmlBufferSize; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex--);
		mldlUmlCompareEmail = &mldlUmlBuffer[mldlUmlIndex+1]; 

		if (strcmp(mldlUmlCompareEmail, mldlUmlResponsibleUserEmail))
			mldlUmlFound = mldlUmlTrue;
	}

	fclose(mldlUmlRead);

	if (mldlUmlFound == mldlUmlFalse)
		return mldlUmlNoMatchingEmail;
	
	if (!(mldlUmlRequestingForm = (mldlUmlRequest *) malloc(sizeof(mldlUmlRequest))))
		return mldlUmlMemoryAllocationError;

	mldlUmlIdForm = (char *) malloc(MLDL_UML_ID_MAXIMUM_SIZE);

	for (mldlUmlIndex = 0; mldlUmlBuffer[mldlUmlIndex] != ':'; mldlUmlIndex++)
		mldlUmlIdForm[mldlUmlIndex] = mldlUmlBuffer[mldlUmlIndex];

	mldlUmlIdForm[mldlUmlIndex] = EOS;

	(*mldlUmlRequestingForm).mldlUmlAnalyzerId = strtoll(mldlUmlIdForm, &mldlUmlValidation, 10);

	if (*mldlUmlValidation != EOS)
	{
		free(mldlUmlRequestingForm);
		free(mldlUmlIdForm);
		return mldlUmlCorruptedFile;
	}

	free(mldlUmlIdForm);

	if (MldlUmlGetUserId(mldlUmlConfigurationOptions, &(*mldlUmlRequestingForm).mldlUmlRequestingUserId))
		return mldlUmlUnableToGetValidId;

	(*mldlUmlUserData).mldlUmlUserId = (*mldlUmlRequestingForm).mldlUmlRequestingUserId;

	strcpy((*mldlUmlRequestingForm).mldlUmlRequestingUserPassword, (*mldlUmlUserData).mldlUmlPassword);

	(*mldlUmlRequestingForm).mldlUmlExpirationDate = (time(NULL) + (7*24*3600));

	if (!(mldlUmlWrite = fopen((*mldlUmlConfigurationOptions).mldlUmlRequestingUsersDataFilename, "ab")))
		return mldlUmlUnableToOpenFile;

	fwrite(mldlUmlRequestingForm, sizeof(*mldlUmlRequestingForm), 1, mldlUmlWrite);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		free(mldlUmlRequestingForm);
		return mldlUmlErrorWritingFile;
	}

	free(mldlUmlRequestingForm);
	fclose(mldlUmlWrite);

	mldlUmlIdForm = (char *) malloc(MLDL_UML_ID_MAXIMUM_SIZE + 1);

	if (MldlUmlUnsignedLongLongToString((unsigned long long) (*mldlUmlUserData).mldlUmlUserId, MLDL_UML_ID_MAXIMUM_SIZE, mldlUmlIdForm))
	{
		free(mldlUmlIdForm);
		return mldlUmlErrorConvertingNumberToString;
	}

	mldlUmlProfileForm = (char *) malloc(MLDL_UML_PROFILE_MAXIMUM_SIZE + 1);

	if (MldlUmlUnsignedLongLongToString((unsigned long long) (*mldlUmlUserData).mldlUmlUserProfile, MLDL_UML_PROFILE_MAXIMUM_SIZE, 
													mldlUmlProfileForm))
	{
		free(mldlUmlIdForm);
		free(mldlUmlProfileForm);
		return mldlUmlErrorConvertingNumberToString;
	}

	snprintf(mldlUmlBuffer, ((5*sizeof(':')) + strlen((*mldlUmlUserData).mldlUmlUserNickname) +
									strlen((*mldlUmlUserData).mldlUmlEmail) + strlen((*mldlUmlUserData).mldlUmlUsername) + strlen(mldlUmlIdForm) +
									strlen(mldlUmlProfileForm) + 1), "%s:%s::%s:%s:%s", mldlUmlIdForm, (*mldlUmlUserData).mldlUmlUserNickname, 
									mldlUmlProfileForm, (*mldlUmlUserData).mldlUmlUsername, (*mldlUmlUserData).mldlUmlEmail);

	free(mldlUmlIdForm);
	free(mldlUmlProfileForm);

	if (!(mldlUmlWrite = fopen((*mldlUmlConfigurationOptions).mldlUmlUsersDataFilename, "a")))
		return mldlUmlUnableToOpenFile;

	fprintf(mldlUmlWrite, "%s\n", mldlUmlBuffer);

	if (ferror(mldlUmlWrite))
	{
		fclose(mldlUmlWrite);
		return mldlUmlErrorWritingFile;
	}

	fclose(mldlUmlWrite);

	printf("End\n");
	/* send e-mail */

	return mldlUmlOk;
}
