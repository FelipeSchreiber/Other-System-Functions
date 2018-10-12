/*

	mldlUmlErrorType
	MldlUmlUnlockUserAccount(mldlUmlConfigurationOptionsType *, char *, char *);

	Arguments:

	mldlUmlConfigurationOptionsType * - determines which process is meant to be executed (I)

	char * - determines the nickname of the user executing the command (I)

	char * - determines the nickname of the user being unlocked (I)

	Description
	If the user is an administrator, this function removes a certain user from the "locked.users" file, and changes its password in the "users" file accordingly.
	If not, a request is set in the "unlocking.requests" file, requesting that the current user's account is unlocked.

*/
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include 'MldlUmlUnlockUserAccount.h'

mldlUmlErrorType
mldlUmlUnlockUserAmount(mldlUmlConfigurationOptionsType * mldlUmlOptionType, char *mldlUmlUserNickname, char *mldlUmlUnlockedUserNickname)

{
  	time_t mldlUmlCurrentTime = time(NULL);

  	FILE *mldlUmlUsersFile;
  	FILE *mldlUmlLockedUsersFile;
  	FILE *mldlUmlUnlockingRequestsFile;

  	char mldlUmlBuffer[sizeof (mldlUmlUserDataType)];
  	char *mldlUmlBinaryBuffer;
  	char *mldlUmlAuxilaryIdentifierNumber;
  	char *mldlUmlAuxilaryNickname;
  	char *mldlUmlAuxilaryUserType;
  	char *mldlUmlAuxilaryPassword;
  	char *mldlUmlAuxilaryUserName;
  	char *mldlUmlAuxilaryEmail;
  	char *mldlUmlAuxilaryEmailConfirmation;
  	char *mldlUmlValidation;
  	char *mldlUmlUnlockedUserIdentifier;
  	char *mldlUmlUnlockedUserPassword;
  	char *mldlUmlLockedUsersListOrganiser;
  	char *mldlUmlUnlockingUsersListBuffer;

  	char *mldlUmlLockedUsersList[sizeof(mldlUmlUserDataType)];
  	char *mldlUmlUnlockingUsersList[sizeof(mldlUmlUserDataType)];

  	char *mldlUmlAuxilaryUnlockedIdentifierNumber;
  	char *mldlUmlAuxilaryUnlockedPassword;
  	time_t mldlUmlLockingTime;

  	unsigned mldlUmlAuxilaryCounter = 0;
  	unsigned mldlUmlAuxilaryCounter2;
  	unsigned mldlUmlAuxilaryOrganiser = 0;
  	unsigned mldlUmlAuxilaryError = 1;
  	unsigned mldlUmlAuxilaryUserIdentifier;
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

 		mldlUmlAuxilaryUserIdentifier = strtoull (mldlUmlAuxilaryUserType, &mldlUmlValidation, 10);

 		if(mldlUmlAuxilaryNickname = mldlUmlUserNickname)
 			mldlUmlAuxilaryError = 0;

 		
 	}

 	if (!(mldlUmlAuxilaryError))
 		return mldlUmlInvalidNickname;

 	if ((mldlUmlAuxilaryUserNumber % 2) != 1)
 		return mldlUmlInvalidUserNickname;

 	mldlUmlAuxilaryCounter = 0;

	fclose(mldlUmlUsersFile);

	mldlUmlUsersFile = fopen (users, 'r');


	mldlUmlListFirst = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryList = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryListPrevious = malloc(sizeof(mldlUmlUserDataType));

	mldlUmlAuxilaryListPrevious = NULL;

	mldlUmlAuxilaryCounter = 0;

	if ((mldlUmlAuxilaryUserType % 2) = 1)
	{

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

			mldlUmlLockedUsersFile = fopen(locked.users, 'r');
	 		
	 		while (fgets(mldlUmlBuffer, sizeof(mldlUmlUserDataType), mldlUmlLockedUsersFile) != EOF)
	 		{
	 			for (mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryOrganiser < 2; mldlUmlAuxilaryCounter2++ && mldlUmlAuxilaryCounter++)
	 			{
	 				if (mldlUmlBuffer[mldlUmlAuxilaryCounter2] = ':')
		 			{
						mldlUmlAuxilaryOrganiser++;
		 				mldlUmlAuxilaryCounter2 = 0;
		 				mldlUmlAuxilaryCounter++;
		 			}
		 	
		 			if (mldlUmlAuxilaryOrganiser == 0)
		 			{
		 				mldlUmlAuxilaryUnlockedIdentifierNumber[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
		 			}
		 	
		 			else
		 			{
		 				mldlUmlAuxilaryUnlockedPassword[mldlUmlAuxilaryCounter2] = mldlUmlBuffer[mldlUmlAuxilaryCounter];
		 			}
				
	 			}


		 							 					
	 			if (strcmp(mldlUmlAuxilaryUnlockedUserIdentifier[mldlUmlAuxilaryCounter2], mldlUmlAuxilaryIdentifierNumber) != 0)
	 			{
	 				mldlUmlLockedUsersList[mldlUmlAuxilaryCounter] = mldlUmlBuffer;
	 				mldlUmlAuxilaryCounter++;
	 			}	

	 			else
	 			{
	 				mldlUmlUnlockedUserIdentifier = mldlUmlAuxilaryIdentifierNumber;
	 				mldlUmlUnlockedUserPassword = mldlUmlAuxilaryUnlockedPassword;
	 			}
	 		}


		 	if (mldlUmlAuxilaryList->nickname == mldlUmlLockedNickname)
		 	{
		 		mldlUmlAuxilaryList->password == mldlUmlAuxilaryUnlockedPassword;
		 	}

		}

		fclose(mldlUmlLockedUsersFile);

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

	}

	else if (mldlUmlAuxilaryUserType % 2 == 0)
	{
		mldlUmlUsersFile = fopen(users, 'r');
		while (mldlUmlAuxilaryNickname != mldlUmlUnlockedUserNickname)
		{
			fgets(mldlUmlBuffer, sizeof(mldlUmlUserDataType), mldlUmlUsersFile);

			for(mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryOrganiser < 2; mldlUmlAuxilaryCounter++ && mldlUmlAuxilaryCounter2++)
		 	{

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

			}

			mldlUmlAuxilaryIdentifierNumber[strlen(mldlUmlAuxilaryIdentifierNumber)] = EOS;

	 		mldlUmlAuxilaryNickname[strlen (mldlUmlAuxilaryNickname)] = EOS;

		
		}

		fclose (mldlUmlUsersFile)

		mldlUmlUnlockingRequestsFile = fopen(unlocking.users,'r');

		for (mldlUmlAuxilaryCounter = 0; fread ((char *)*mldlUmlUnlockingUsersListBuffer, 1, sizeof (mldlUmlUserDataType), mldlUmlUnlockingRequestsFile) != EOF; mldlUmlAuxilaryCounter++)
			mldlUmlUnlockingUsersList[mldlUmlAuxilaryCounter] = mldlUmlUnlockingUsersListBuffer;

		sprintf (mldlUmlUnlockingUsersList[mldlUmlAuxilaryCounter + 1], "%llu:%s", (mldlUmlCurrentTime + 86400), mldlUmlUnlockedUserIdentifier);

		fclose(mldlUmlUnlockingRequestsFile);

		mldlUmlUnlockingRequestsFile = fopen(unlocking.users, 'w');

		for (mldlUmlAuxilaryCounter2 = 0; mldlUmlAuxilaryCounter2 <= (mldlUmlAuxilaryCounter + 1); mldlUmlAuxilaryCounter2++)
			fwrite (mldlUmlUnlockingUsersList[mldlUmlAuxilaryCounter2], 1, sizeof(mldlUmlUnlockingUsersList[mldlUmlAuxilaryCounter2], mldlUmlUnlockingRequestsFile));

		fclose(mldlUmlUnlockingRequestsFile);

	}


	return mldlUmlOk;
}