/* Universidade Federal do Rio de Janeiro
*  Escola Politecnica
*  Departamento de Eletronica e de Computacao
*  Prof. Marcelo Luiz Drumond Lanza
*  EEL 270 - Computacao II - Turma 2017/1
* 
*  $Author:$
*  $Date:$
*  $Log:$
*/

#include "mldlUmlTypes.h"

/*
 * void
 * MldlUmlShowCliHelp (mldlUmlConfigurationOptionsType *, mldlUmlLanguageType);
 * Arguments:
 * mldlUmlConfigurationOptionsType * - configuration file
 * mldlUmlLanguageType - language
  . . .
 * Description:
 * Shows the cli help message
 */
void
MldlUmlShowCliHelp (mldlUmlConfigurationOptionsType *mldlUmlConfiguration, mldlUmlLanguageType mldlUmlLanguage)
{

	if (!mldlUmlLanguage)
		mldlUmlLanguage = mldlUmlEnglish;

	switch (mldlUmlLanguage)
	{
		case mldlUmlEnglish:
		default:
			printf("\nHelp Message:\n\n\tUsage:\n\n\t$UML [-OPTION/--LONG_OPTION] [SUBOPTIONS=VALUE]\n\tOptions:\n\t-h --help 	Shows this message\n",);
		break;

		case mldlUmlPortuguese:
			printf("\nMensagem de ajuda:\n\n\tUso:\n\n\t$UML [-OPCAO/--OPCAO_LONGA] [SUBOPCAO=VALOR]\n\tOpcoes:\n\t-h --help 	Mostra esta mensagem\n",);
		break;	
	}

}

/* $RCSfile:$ */
