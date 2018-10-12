/*

	mldlUmlErrorType
	MldlUmlLockUserAccount(mldlUmlConfigurationOptionsType *, char *, char *);

	Arguments:

	mldlUmlConfigurationOptionsType * - determines which process is meant to be executed (I)

	char * - determines the nickname of the administrator executing the command (I)

	char * - determines the nickname of the user being locked (I)

	Description
	If the user is an administrator, this function puts certain user in the "locked.users" file, and changes its password in the "users" file to a string with lenght == 0.
*/


mldlUmlErrorType 
MldlUmlLockUserAccount(mldlUmlConfigurationOptionsType *mldlUmlConfigurationOption, char *mldlUmlAdminNickname, char *mldlUmlLockedNickname)
{


	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include 'MldlUmlLockUserAccount.h'

  	time_t mldlUmlCurrentTime = time(NULL);

  	FILE *mldlUmlUsersFile;
  	FILE *mldlUmlLockedUsersFile;

  	char mldlUmlBuffer[sizeof (mldlUmlUserDataType)];
  	char *mldlUmlAuxilaryIdentifierNumber;
  	char *mldlUmlAuxilaryNickname;
  	char *mldlUmlAuxilaryUserType;
  	char *mldlUmlAuxilaryPassword;
  	char *mldlUmlAuxilaryUserName;
  	char *mldlUmlAuxilaryEmail;
  	char *mldlUmlAuxilaryEmailConfirmation;
  	char *mldlUmlValidation;
  	char *mldlUmlLockedUserIdentifier;
  	char *mldlUmlLockedUsersListOrganiser;

  	char *mldlUmlLockedUsersList[sizeof(mldlUmlUserDataType)];

  	char *mldlUmlAuxilaryLockedIdentifierNumber;
  	char *mldlUmlAuxilaryLockedNickname;
  	time_t mldlUmlLockingTime;

  	unsigned mldlUmlAuxilaryCounter = 0;
  	unsigned mldlUmlAuxilaryCounter2;
  	unsigned mldlUmlAuxilaryOrganiser = 0;
  	unsigned mldlUmlAuxilaryError = 1;
  	unsigned mldlUmlAuxilaryAdminIdentifier;
  	unsigned mldlUmlLockedUserIdentifier;

  	mldlUmlUserIdentifierType mldlUmlUserType;

  	mldlUmlUserDataType *mldlUmlListFirst;
  	mldlUmlUserDataType *mldlUmlAuxilaryList;
  	mldlUmlUserDataType *mldlUmlAuxilaryListPrevious;
  	mldlUmlUserDataType *mldlUmlAuxilaryLockedList;
  	mldlUmlUserDataType *mldlUmlAuxilaryLockedListPrevious;


  	mldlUmlUsersFile = fopen(users, 'r');

  	while (mldlUmlAuxilaryError && mldlUmlBuffer != EOF)
  	{
 		fgets(mldlUmlBuffer, sizeof(mldlUmlUserDataType), mldlUmlUsersFile);


 		for(mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryNickname[mldlUmlAuxilaryCounter] != EOS; mldlUmlAuxilaryCounter++ && mldlUmlAuxilaryCounter2++)
 		{
 			if (mldlUmlBuffer[mldlUmlAuxilaryCounter] = ':')
 			{
 				mldlUmlAuxilaryOrganiser++;
 				mldlUmlAuxilaryCounter2 = 0;
 				mldlUmlAuxilaryCounter++;
 			}

 			if (mldlUmlAuxilaryOrganiser == 0)
 				mldlUmlAuxilaryIdentifierNumber[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];

 			if (mldlUmlAuxilaryOrganiser == 1)
 				mldlUmlAuxilaryNickname[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];

			if (mldlUmlAuxilaryOrganiser == 2)
				mldlUmlAuxilaryPassword[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];

			if (mldlUmlAuxilaryOrganiser == 3)
				mldlUmlAuxilaryUserType[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];

			if (mldlUmlAuxilaryOrganiser == 4)
				mldlUmlAuxilaryUserName[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];

			if (mldlUmlAuxilaryOrganiser == 5)
				mldlUmlAuxilaryEmail[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];


			}

		mldlUmlAuxilaryIdentifierNumber[strlen(mldlUmlAuxilaryIdentifierNumber)] = EOS;

 		mldlUmlAuxilaryNickname[strlen (mldlUmlAuxilaryNickname)] = EOS;

 		mldlUmlAuxilaryPassword[strlen (mldlUmlAuxilaryPassword)] = EOS;

 		mldlUmlAuxilaryUserType[strlen (mldlUmlAuxilaryUserType)] = EOS;

 		mldlUmlAuxilaryUserName[strlen (mldlUmlAuxilaryUserName)] = EOS;

 		mldlUmlAuxilaryEmail[strlen (mldlUmlAuxilaryEmail)]0 = EOS;

 		mldlUmlAuxilaryEmailConfirmation = mldlUmlAuxilaryEmail;

 		mldlUmlAuxilaryAdminIdentifier = strtoull (mldlUmlAuxilaryUserType, &mldlUmlValidation, 10);

 		if(mldlUmlAuxilaryNickname = mldlUmlAdminNickname)
 			mldlUmlAuxilaryError = 0;

 		
 	}

 	if (!(mldlUmlAuxilaryError))
 		return mldlUmlInvalidNickname;

 	if ((mldlUmlAuxilaryUserNumber % 2) != 1)
 		return mldlUmlInvalidAdminNickname;

 	mldlUmlAuxilaryCounter = 0;

	fclose(mldlUmlUsersFile);


	mldlUmlUsersFile = fopen (users, 'r');


	mldlUmlListFirst = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryList = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryListPrevious = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryListPrevious = NULL;

	while (mldlUmlBuffer != EOF && mldlUmlAuxilaryError)
	{
		for(mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryNickname[mldlUmlAuxilaryCounter] != EOS; mldlUmlAuxilaryCounter++ && mldlUmlAuxilaryCounter2++)
	 		{
	 			fgets(mldlUmlBuffer, sizeof(mldlUmlUserDataType), mldlUmlUsersFile);

	 			if (mldlUmlBuffer[mldlUmlAuxilaryCounter] = ':')
	 			{
	 				mldlUmlAuxilaryOrganiser++;
	 				mldlUmlAuxilaryCounter2 = 0;
	 				mldlUmlAuxilaryCounter++;
	 			}

	 			if (mldlUmlAuxilaryOrganiser == 0)
	 			{
	 				mldlUmlAuxilaryIdentifierNumber[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
	 			}

	 			else if (mldlUmlAuxilaryOrganiser == 1)
	 			{
	 				mldlUmlAuxilaryNickname[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
	 			}

				else if (mldlUmlAuxilaryOrganiser == 2)
				{
					mldlUmlAuxilaryPassword[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
				}

				else if (mldlUmlAuxilaryOrganiser == 3)
				{
					mldlUmlAuxilaryUserType[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
				}

				else if (mldlUmlAuxilaryOrganiser == 4)
				{
					mldlUmlAuxilaryUserName[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
				}

				else if (mldlUmlAuxilaryOrganiser == 5)
				{
					mldlUmlAuxilaryEmail[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
				}


			}

			mldlUmlAuxilaryIdentifierNumber[strlen(mldlUmlAuxilaryIdentifierNumber)] = EOS;

	 		mldlUmlAuxilaryNickname[strlen (mldlUmlAuxilaryNickname)] = EOS;

	 		mldlUmlAuxilaryPassword[strlen (mldlUmlAuxilaryPassword)] = EOS;

	 		mldlUmlAuxilaryUserType[strlen (mldlUmlAuxilaryUserType)] = EOS;

	 		mldlUmlAuxilaryUserName[strlen (mldlUmlAuxilaryUserName)] = EOS;

	 		mldlUmlAuxilaryEmail[strlen (mldlUmlAuxilaryEmail)] = EOS;

	 		mldlUmlAuxilaryEmailConfirmation = mldlUmlAuxilaryEmail;

	 		mldlUmlAuxilaryUserIdentifier = strtoull (mldlUmlAuxilaryIdentifierNumber, &mldlUmlValidation, 10);


	 		mldlUmlAuxilaryList->userIdentifier = mldlUmlAuxilaryUserIdentifier;

	 		mldlUmlAuxilaryList->nickname = mldlUmlAuxilaryNickname;

	 		mldlUmlAuxilaryList->password = mldlUmlAuxilaryPassword;

	 		mldlUmlAuxilaryList->profile = strtoull (mldlUmlAuxilaryUserType, &mldlUmlValidation, 10)

	 		mldlUmlAuxilaryList->userName = mldlUmlAuxilaryUserName;

	 		mldlUmlAuxilaryList->userNameConfirmation = mldlUmlAuxilaryUserName;

	 		mldlUmlAuxilaryList->email = mldlUmlAuxilaryEmail;

	 		mldlUmlAuxilaryList->emailConfirmation = mldlUmlAuxilaryEmailConfirmation;

	 		mldlUmlAuxilaryList->previous = mldlUmlAuxilaryListPrevious;


	 		if (mldlUmlAuxilaryList->previous == NULL)
	 			mldlUmlListFirst = mldlUmlAuxilaryList;

	 		mldlUmlAuxilaryListPrevious = mldlUmlAuxilaryList

	 		mldlUmlAuxilaryList = malloc (sizeof(mldlUmlUserDataType));

	 		mldlUmlAuxilaryListPrevious->next = mldlUmlAuxilaryList;

	 		if (mldlUmlAuxilaryList->nickname == mldlUmlLockedNickname)
	 		{
		 		if ((mldlUmlAuxilaryList->profile % 2) != 1)
		 			mldlUmlAuxilaryError = 0;

		 		else 
		 		{
		 			mldlUmlAuxilaryList->password[0] = EOS;

		 			mldlUmlLockedUserIdentifier = mldlUmlAuxilaryIdentifierNumber;

		 			mldlUmlLockedUserPassword = mldlUmlAuxilaryPassword;

		 			mldlUmlLockedUsersFile = fopen(locked.users, 'r');

		 			mldlUmlAuxilaryCounter = 0;

		 			mldlUmlLockedUsersFile = fopen(locked.users, 'r');
		 			while (fgets(mldlUmlBuffer, sizeof(mldlUmlUserDataType), mldlUmlLockedUsersFile) != EOF)
		 			{
		 				for (mldlUmlAuxilaryCounter2 = 0; mldlUmlBuffer[mldlUmlAuxilaryCounter2] != ':'; mldlUmlAuxilaryCounter2++)
		 					mldlUmlLockedUsersList[mldlUmlAuxilaryCounter][mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter2];
		 				
			 	 		if (strcmp(mldlUmlLockedUsersList[mldlUmlAxuilaryCounter][mldlUmlAuxilaryCounter2], mldlUmlLockedUserIdentifier) < 0)
			 				{
			 					sprintf (mldlUmlLockedUsersList[mldlUmlAuxilaryCounter][mldlUmlAuxilaryCounter2], "%s:%s:%u:%llu", mldlUmlLockedUserIdentifier, mldldUmlLockedPassword, mldlUmlCurrentTime, mldlUmlAdminIdentifier);
			 					mldlUmlAuxilaryCounter++;
			 				}

		 				mldlUmlLockedUsersList[mldlUmlAuxilaryCounter] = mldlUmlBuffer;
		 					
		 				mldlUmlAuxilaryCounter++;
		 			}
		 			fclose(mldlUmlLockedUsersFile);
		 			
	 			}
			}

			fclose(mldlUmlUsersFile);

			if (mldlUmlAuxilaryError == 0)
				return mldlUmlBlockingAdmin;


			mldlUmlUsersFile = fopen(users, 'w');

			while (mldlUmlListFirst)
			{
				fprintf (mldlUmlUsersFile, "%llu:%s:%s:%s:%llu:%s:%s:%s:%s", mldlUmlListFirst->userIdentifier
																			 mldlUmlListFirst->nickname
																			 mldlUmlListFirst->password
																			 mldlUmlListFirst->password
																			 mldlUmlListFirst->profile
																			 mldlUmlListFirst->userName
																			 mldlUmlListFirst->userNameConfirmation
																			 mldlUmlListFirst->email
																			 mldlUmlListFirst->emailConfirmation);

				if (mldlUmlFirst->next == NULL)
				{
					free(mldlUmlListFirst);
				}
				else
				{
					mldlUmlListFirst = mldlUmlListFirst->next;
					free(mldlUmlListFirst->previous);
				}
			}

			fclose(mldlUmlUsersFile);

			mldlUmlLockedUsersFile = fopen(locked.users,'w');

			for (mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryCounter2 >= mldlUmlAuxilaryCounter; mldlUmlAuxilaryCounter2++)
				frpintf (mldlUmlLockedUsersFile, "%s", mldlUmlLockedUsersList[mldlUmlAuxilaryCounter2]);
			
			mldlUmlLockedUsersList = NULL;

			fclose(mldlUmlLockedUsersFile);
			return OK;
}

/* $RCSfile:$ */
