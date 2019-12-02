#include <stdio.h>
#include <stdlib.h>

#include "bibliotecas/codigo_erros.h"
#include "bibliotecas/estruturas.h"
#include "bibliotecas/mensagens.h"
#include "bibliotecas/operacoes.h"
#include "bibliotecas/telas.h"


int main()
{
	TAgenda agenda;
	inicializarAgenda(&agenda);
	int opc;
	boolean rodar = true;
	char c;
	while(rodar)
	{
		if(telaInicio()==2) rodar=false;
		/*{
			printf("O\nO\nO Todos os dados da agenda serão perdidos. Deseja realmente sair?  [s/n]: "); 
			scanf("%c", &c);
			if(c == 's') rodar=false;
		}   */
		else
		{
			boolean rodar2=true;
			while(rodar2)
			{
				opc=telaAg();
				if(opc == 1)ImprimirErro(novaAgenda(&agenda));
				else if(opc == 2)
				{
					int id, codErro;
					TAgendaItem agendaItem;
					codErro = removerAgenda(&agenda, &agendaItem, &id); ImprimirErro(codErro);
					if(codErro == OK) ordemPrioridade(&agenda, id);
				}
				else if(opc == 3)
				{
					if(agenda.ultPos != -1)
					{
						int id, op, codErro;
						boolean rodar3=true;
					
						while(rodar3)
						{
							telaCmpId(&agenda, &id);
							op=telaCmp(&agenda, id); //tem problemas aqui para resolver
							TCompItem *compromisso;
							if(op==1)
							{
								codErro = novCompromisso(&agenda, id); ImprimirErro(codErro);
								if(codErro == OK) ordemPrioridade(&agenda, id);
							}
							else if(op==2)
							{
								codErro = removerCompromisso(&agenda, &compromisso, id); ImprimirErro(codErro);
								//if(codErro == OK) ordemPrioridade(&agenda, id);
							}
							else if (op == 5)ImprimirErro(imprimirAgendaProf(&agenda, id));
							else if(op==8) rodar3 = false;
						
						}
					}
				}
				else if(opc == 4)
				{
					if(agenda.ultPos != -1)
					{
						int id, op, codErro;
						boolean rodar3=true;
						telaCmpId(&agenda, &id);
						ImprimirErro(imprimirAgendaProf(&agenda, id));
					}
				}
				else if(opc == 5)ImprimirErro(imprimirAgenda(&agenda));
				else if(opc == 6)ImprimirErro(recuperaAgenda(&agenda));
				else if(opc == 7)rodar2 = false;

			}
		}
	}
	printf("\n\n\nFim da execução.\n\n");
	return 0;
}



