#ifndef mensagens_h
#define mensagens_h

#include "codigo_erros.h"
#include <stdio.h>
#include <stdlib.h>
void ImprimirErro(int codErro)
{
	system("sleep 4");
	system("clear");

	switch ( codErro )
	{	
		case OK : printf("\n Operação Realizada Com Sucesso\n ");
		break;
		
		case AGENDA_FULL : printf("\n Erro : Agenda Cheia\n ");
		break;
		
		case AGENDA_EMPTY : printf("\n Erro : Agenda Vazia \n");
		break;
		
		case COMPROMISSO_FULL  : printf("\n Erro : Lista de compromisso cheia \n");
		break;

		case COMPROMISSO_EMPTY   : printf("\n Erro : Lista de compromisso vazia \n");
		break;

		case NOT_FOUND   : printf("\n Erro : Elemento não encontrado \n");
		break;

	}
	system("sleep 2");
}

#endif
