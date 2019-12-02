#ifndef operacoes_h
#define operacoes_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "codigo_erros.h"
//#include "mensagens.h"


//Operações com as agendas

void inicializarAgenda(TAgenda *agenda)
{
	agenda->ultPos = -1;
}

boolean cheiaAgenda(TAgenda *agenda)
{
	return (agenda->ultPos == TAM-1);
}

boolean vaziaAgenda(TAgenda *agenda)
{
	return (agenda->ultPos == -1);
}

void inicializarCompromisso(TAgenda *agenda, int idP)
{
	agenda->item[idP].compromisso.ultPos = -1;
}
boolean eAdiavel(TAgenda *agenda, int idP, int idComp)
{
	return (agenda->item[idP].compromisso.item[idComp].eAd == true);
}

void resolveConflito(TAgenda *agenda, int idP)
{
	

}
int criarAgenda(TAgenda *agenda, int idP, char nome[TAM], int ano)
{
	if(cheiaAgenda(agenda)) return AGENDA_FULL;
	agenda->ultPos++; agenda->item[agenda->ultPos].idProf = idP;
	agenda->item[agenda->ultPos].ano = ano;
	strcpy(agenda->item[agenda->ultPos].nomeProf, nome);
	inicializarCompromisso(agenda, agenda->ultPos);

	return OK;
}

int removerAgenda(TAgenda *agenda, TAgendaItem *agend, int *id)
{
	if(vaziaAgenda(agenda)) return AGENDA_EMPTY;
	int idP;
	telaCmpId(&agenda, &idP);
	*id  = idP;
	*agend = agenda->item[idP];
	int i;
	for ( i = idP; i < agenda->ultPos; i++) agenda->item[i] = agenda->item[i+1];
	agenda->ultPos--;
	return OK;
}


//Operações com o compromisso



boolean cheioCompromisso(TAgenda *agenda, int idP)
{
	return (agenda->item[idP].compromisso.ultPos == TAM-1);
}

boolean vazioCompromisso(TAgenda *agenda, int idP)
{
	return (agenda->item[idP].compromisso.ultPos == -1);
}

void trocaCompTipo(TAgenda *agenda, int idP, int i, int j)
{
	TCompItem auxComp;
	if(agenda->item[idP].compromisso.item[i].tipo != agenda->item[idP].compromisso.item[j].tipo)
	{
		auxComp = agenda->item[idP].compromisso.item[i]; agenda->item[idP].compromisso.item[i] = agenda->item[idP].compromisso.item[j];
		agenda->item[idP].compromisso.item[j] = auxComp;
	}
	else
	{
		if(agenda->item[idP].compromisso.item[i].tempo.data.ano > agenda->item[idP].compromisso.item[j].tempo.data.ano)
		{
			auxComp = agenda->item[idP].compromisso.item[i]; agenda->item[idP].compromisso.item[i] = agenda->item[idP].compromisso.item[j];
			agenda->item[idP].compromisso.item[j] = auxComp;
		}
		else if(agenda->item[idP].compromisso.item[i].tempo.data.ano == agenda->item[idP].compromisso.item[j].tempo.data.ano)
		{
			if(agenda->item[idP].compromisso.item[i].tempo.data.mes > agenda->item[idP].compromisso.item[j].tempo.data.mes)
			{
				auxComp = agenda->item[idP].compromisso.item[i]; agenda->item[idP].compromisso.item[i] = agenda->item[idP].compromisso.item[j];
				agenda->item[idP].compromisso.item[j] = auxComp;
			}
			else if(agenda->item[idP].compromisso.item[i].tempo.data.mes == agenda->item[idP].compromisso.item[j].tempo.data.mes)
			{
				if(agenda->item[idP].compromisso.item[i].tempo.data.dia > agenda->item[idP].compromisso.item[j].tempo.data.dia)
				{
					auxComp = agenda->item[idP].compromisso.item[i]; agenda->item[idP].compromisso.item[i] = agenda->item[idP].compromisso.item[j];
					agenda->item[idP].compromisso.item[j] = auxComp;
				}
				else if((agenda->item[idP].compromisso.item[i].tempo.data.dia == agenda->item[idP].compromisso.item[j].tempo.data.dia) && (agenda->item[idP].compromisso.item[i].tempo.hora > agenda->item[idP].compromisso.item[j].tempo.hora ))
				{
					auxComp = agenda->item[idP].compromisso.item[i]; agenda->item[idP].compromisso.item[i] = agenda->item[idP].compromisso.item[j];
					agenda->item[idP].compromisso.item[j] = auxComp;
				}

			}
		}

		
	}

}
void ordemPrioridade(TAgenda *agenda, int idP)
{
	int i, j;
	for(i = 0; i < agenda->item[idP].compromisso.ultPos; i++ )
		for(j = i+1; j <= agenda->item[idP].compromisso.ultPos; j++)
			if(agenda->item[idP].compromisso.item[i].tipo >= agenda->item[idP].compromisso.item[j].tipo ) trocaCompTipo(agenda, idP, i, j);

}
int inserirCompromisso(TAgenda *agenda, int idProf, int tipo, TData data, int hora, int duracao, char nome[TAM])
{
	if(cheioCompromisso(agenda, idProf) ) return COMPROMISSO_FULL;
	TCompItem compromisso;
	compromisso.tipo = tipo; compromisso.tempo.hora = hora;
	compromisso.tempo.duracao = duracao;
	compromisso.tempo.data = data;
	compromisso.estado = 1;
	strcpy(compromisso.descricao, nome);
	if(tipo == 2 || tipo == 3) compromisso.eAd = false;
	else
		compromisso.eAd = true;	
	agenda->item[idProf].compromisso.ultPos++; agenda->item[idProf].compromisso.item[agenda->item[idProf].compromisso.ultPos] = compromisso;
	return OK;
}



void remTempo(int *ano, int *mes, int *dia)
{
	int an, d, m; //d = dia, m = mês, an= ano, hr = hora, dr = duração
	boolean flag = true;
	
	printf("O\nO \t\t\t>> Ano:");
	while(flag)
	{
		scanf("%d", &an);
		if(an >= 2017 && an <=2021) flag = false;
		else
			printf("\nO \tAno válido apenas de 2017 à 2021. Insira o ano novamente: "); 
	}
	printf("O\nO \t\t\t>> Mês:"); flag = true;
	while(flag)
	{
		scanf("%d", &m);
		if(m >= 1 && m <=12) flag = false;
		else
			printf("\nO \tMês inválido. No planeta terra existem apenas 12 meses [1-12]. Insira novamente: "); 
	}
	printf("O\nO \t\t\t>> Dia:"); flag = true;
	while(flag)
	{
		scanf("%d", &d);
		if(((an%4 != 0) && (m==2)) && d > 28) printf("\nO \tDia inválido para o mês de fevereiro. Insira novamente: "); 
		else if(((an%4 == 0) && (m==2)) && d > 29) printf("\nO \tDia inválido para o mês de fevereiro. Insira novamente: ");
		else if(d >= 1 && d <=31) flag = false;
		else
			printf("\nO \tDia inválido. [1-31]. Insira novamente: "); 
	}

	*ano = an; *mes = m;
	*dia = d; 
}

int buscaIdComp(TAgenda *agenda, int idP)
{
	int tipo, an, m, d, j, o = imprimirAgendaProf(agenda, idP);
	TData data;
	boolean flag = true;
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Agenda -> Professor: %s                                        -O-O\n", agenda->item[idP].nomeProf);
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("\nO \t\t\tTipo do compromisso:");
	while(flag)
	{
		scanf("%d", &tipo);
		if(tipo >= 1 && tipo <=5) flag = false;
		else
			printf("\nO \t Tipo de compromisso inválido. Insira novamente: "); 
	}
	remTempo(&an, &m, &d);
	for(j = 0; j < agenda->item[idP].compromisso.ultPos; j++)
		if( agenda->item[idP].compromisso.item[j].tipo == tipo)
			if(agenda->item[idP].compromisso.item[j].tempo.data.ano == an)
				if(agenda->item[idP].compromisso.item[j].tempo.data.mes == m)
					if(agenda->item[idP].compromisso.item[j].tempo.data.dia == d) return j;
	
	return COMPROMISSO_NOT_FOUND;
}
int removerCompromisso(TAgenda *agenda, TCompItem *compromisso, int idProf)
{
	if(vazioCompromisso(agenda,idProf)) return COMPROMISSO_EMPTY;
	int j, idCompromisso = buscaIdComp(agenda, idProf);
	if(idCompromisso == COMPROMISSO_EMPTY) return COMPROMISSO_NOT_FOUND;
	*compromisso = agenda->item[idProf].compromisso.item[idCompromisso];

	for ( j = idCompromisso; j < agenda->item[idProf].compromisso.ultPos; j++) 
		agenda->item[idProf].compromisso.item[j] = agenda->item[idProf].compromisso.item[j+1];
	agenda->item[idProf].compromisso.ultPos--; 
	return OK;
}

int buscaIdProf(TAgenda *agenda, int idP)
{
	if(vaziaAgenda(agenda)) return NOT_FOUND;
	int i;
	for ( i = 0; i <= agenda->ultPos; i++) 
		if(agenda->item[i].idProf == idP) return i;
	return -1;
}

int novaAgenda(TAgenda *agenda)
{
	char nome[TAM];
	int ano, id;
	boolean flag = true;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Nova Agenda                                                         -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O\nO \t\t\tNome do professor: "); scanf("%s", nome);
	printf("O\nO \t\t\tId do professor: "); 
	while(flag)
	{
		scanf("%d", &id);
		if(buscaIdProf(agenda, id)==NOT_FOUND) flag = false;
		else
			printf("\nO \t\t\tId de professor já existente. Insira outro id: "); 
	}
	printf("\nO \t\t\tAno da agenda: "); flag = true;
	while(flag)
	{
		scanf("%d", &ano);
		if(ano >= 2017 && ano <=2021) flag = false;
		else
			printf("\nO \t\t\tAno válido apenas de 2017 à 2021. Insira outro ano: "); 
	}
	return criarAgenda(agenda, id, nome, ano);

}
int tipoComp()
{
	int op;
	boolean flag = true;
	printf("O\nO \t\t\tO Tipo 1 Orientação        O");
	printf("\nO \t\t\tO Tipo 2 Aulas              O");
	printf("\nO \t\t\tO Tipo 3 Eventos            O");
	printf("\nO \t\t\tO Tipo 4 Reuniões           O");
	printf("\nO \t\t\tO Tipo 5 Compro. Particular O\nO \t Tipo:");
	while(flag)
	{
		scanf("%d", &op);
		if(op >= 1 && op <=5) return op;
		else
			printf("\nO \t Tipo de compromisso inválido. Insira novamente: "); 
	}

}
void insereTempo(TData *data, int *hora, int *duracao, int tipo)
{
	int d, m, an, hr, dr; //d = dia, m = mês, an= ano, hr = hora, dr = duração
	boolean flag = true;
	printf("O\nO \t\t\t>> Data e Tempo <<");
	
	printf("O\nO \t\t\t>> Ano:");
	while(flag)
	{
		scanf("%d", &an);
		if(an >= 2017 && an <=2021) flag = false;
		else
			printf("\nO \tAno válido apenas de 2017 à 2021. Insira o ano novamente: "); 
	}

	printf("O\nO \t\t\t>> Mês:"); flag = true;
	while(flag)
	{
		scanf("%d", &m);
		if(m >= 1 && m <=12) flag = false;
		else
			printf("\nO \tMês inválido. No planeta terra existem apenas 12 meses [1-12]. Insira novamente: "); 
	}

	printf("O\nO \t\t\t>> Dia:"); flag = true;
	while(flag)
	{
		scanf("%d", &d);
		if(((an%4 != 0) && (m==2)) && d > 28) printf("\nO \tDia inválido para o mês de fevereiro. Insira novamente: "); 
		else if(((an%4 == 0) && (m==2)) && d > 29) printf("\nO \tDia inválido para o mês de fevereiro. Insira novamente: ");
		else if(d >= 1 && d <=31) flag = false;
		else
			printf("\nO \tDia inválido. [1-31]. Insira novamente: "); 
	}

	printf("O\nO \t\t\t>> Hora:"); flag = true;
	while(flag)
	{
		scanf("%d", &hr);
		if(hr >= 0 && hr <=23) flag = false;
		else
			printf("\nO \tHora inválida. [0-23h]. Insira novamente: "); 
	}
	if(tipo == 3)
	{
		printf("O\nO \t\t\t>> Duração(dias):");
		flag = true;
		while(flag)
		{
			scanf("%d", &dr);
			if(dr >= 1 && dr <= 15) flag = false;
			else
				printf("\nO \tDias inválidos para um evento sério. [1-15 dias]. Insira novamente: "); 
		}
	}
	else
	{
		printf("O\nO \t\t\t>> Duração(min):");
		flag = true;
		while(flag)
		{
			scanf("%d", &dr);
			if(dr >= 10 && dr <= 1440) flag = false;
			else
				printf("\nO \tMinutos inválidos para um compromisso sério. [10-1440min]. Insira novamente: "); 
		}
	}
	data->ano = an; data->mes = m;
	data->dia = d; *hora = hr;
	*duracao = dr; 

}
int novCompromisso(TAgenda *agenda, int idP)
{
	int idProf = idP, tipo, hora, duracao;
	char nome[TAM];
	TData data;
	boolean flag = true;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Agenda -> Professor: %s                                        -O-O\n", agenda->item[idProf].nomeProf);
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	tipo=tipoComp();
	if(tipo == 1)
	{
		printf("O\nO \t\t\tNome do Aluno:  "); scanf("%s", nome);
		insereTempo(&data, &hora, &duracao, tipo);
	}
	else if(tipo == 2)
	{
		printf("O\nO \t\t\tNome da Disciplina:  "); scanf("%s", nome);
		insereTempo(&data, &hora, &duracao, tipo);
	}
	else if(tipo == 3)
	{
		printf("O\nO \t\t\tNome do Evento:  "); scanf("%s", nome);
		insereTempo(&data, &hora, &duracao, tipo);
	}
	else if(tipo == 4)
	{
		printf("O\nO \t\t\tAssunto da reunião:  "); scanf("%s", nome);
		insereTempo(&data, &hora, &duracao, tipo);
	}
	else if(tipo == 5)
	{
		printf("O\nO \t\t\tRazão do compromisso:  "); scanf("%s", nome);
		insereTempo(&data, &hora, &duracao, tipo);
	}
	
	return inserirCompromisso(agenda, idProf, tipo, data, hora, duracao,  nome);
}

void telaCmpId(TAgenda *agenda, int *idP)
{
	int id;
	boolean flag = true;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Alterar Agenda                                                      -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O\nO \t\t\tId do professor: "); 
	while(flag)
	{
		scanf("%d", &id); 
		id = buscaIdProf(agenda, id); 
		if(id!=NOT_FOUND) flag = false;
		else
			printf("\nO \t\t\tId de professor  ivalido. Insira outro id: "); 
	}
	*idP = id; 

}
int telaCmp(TAgenda *agenda, int id)
{
	int op;
	boolean flag = true;	
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Alterar Agenda                                                      -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O\nO \t\t\tNome do professor: %s\n", agenda->item[id].nomeProf);
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O                                                                                               O\n");
	printf("O                                                                                               O\n");
	printf("O                                  1 - CRIAR NOVO COMPROMISSO                                   O\n");
	printf("O                                                                                               O\n");
	printf("O                                  2 - REMOVER COMPROMISSO                                      O\n");
	printf("O                                                                                               O\n");
	printf("O                                  3 - ALTERAR UM COMPROMISSO                                   O\n");
	printf("O                                                                                               O\n");
	printf("O                                  4 - CONSULTAR COMPROMISSOS                                   O\n");
	printf("O                                                                                               O\n");
	printf("O                                  5 - VER COMPROMISSOS                                         O\n");
	printf("O                                                                                               O\n");
	printf("O                                  6 - Alterar Prioridade                                       O\n");
	printf("O                                                                                               O\n");
	printf("O                                  7 - Resolver Conflitos                                       O\n");
	printf("O                                                                                               O\n");
	printf("O                                  8 - VOLTAR                                                   O\n");
	printf("O                                                                                               O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("\nOpção:");
	while(flag)
	{
		scanf("%d", &op);
		if(op >= 1 && op <= 8) return op;
		printf("O\nO Opção inválida: ");
	}
}
void tipoCompromisso(int tipo, char nome[TAM])
{
	if(tipo ==1) printf("O\nO\t\t\tTipo: Orientação\nO\t\t\tNome do aluno: %s", nome);
	else if(tipo ==2) printf("O\nO\t\t\tTipo: Aulas\nO\t\t\tNome da Disciplina: %s", nome);
	else if(tipo ==3)printf("O\nO\t\t\tTipo: Eventos\nO\t\t\tNome do evento: %s", nome);
	else if(tipo ==4)printf("O\nO\t\t\tTipo: Reunião\nO\t\t\tAssunto: %s", nome);
	else if(tipo ==5)printf("O\nO\t\t\tTipo: Compromisso Paricular\nO\t\t\tRazão: %s", nome);
	
}
int imprimirAgendaProf(TAgenda *agenda, int i)
{
	if(vaziaAgenda(agenda)) return AGENDA_EMPTY;
	boolean flag = true;
	int j, op;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Imprimir Compromissos                                               -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O                                                                                               O"); 
	printf("\nO \nO\t\t\tNome do professor: %s\nO\t\t\tId: %d\nO\t\t\tAno: %d\nO\n", agenda->item[i].nomeProf,agenda->item[i].idProf,agenda->item[i].ano); 
	if(vazioCompromisso(agenda,i)) printf("O\nO\t\t\tSem Compromissos\n");
	else
		for ( j = 0; j <= agenda->item[i].compromisso.ultPos; j++)
		{
			printf("\nO\nO\t\t\t\t Compromisso [%d]\n\n", j+1);
			tipoCompromisso(agenda->item[i].compromisso.item[j].tipo, agenda->item[i].compromisso.item[j].descricao);			
			printf("\nO\t\t\tData: %d/%d/%d",agenda->item[i].compromisso.item[j].tempo.data.dia,agenda->item[i].compromisso.item[j].tempo.data.mes,agenda->item[i].compromisso.item[j].tempo.data.ano);
			printf("\nO\t\t\tHora: %dh",agenda->item[i].compromisso.item[j].tempo.hora);
			if(agenda->item[i].compromisso.item[j].tipo==3)printf("\nO\t\t\Duração (dias): %d",agenda->item[i].compromisso.item[j].tempo.duracao);
			else
				printf("\nO\t\t\Duração (min): %d",agenda->item[i].compromisso.item[j].tempo.duracao);
			if(agenda->item[i].compromisso.item[j].estado == 1) printf("\nO\t\tEstado: A Cumprir");
			else if(agenda->item[i].compromisso.item[j].estado == 2) printf("\nO\t\tEstado: Adiado");
			else if(agenda->item[i].compromisso.item[j].estado == 3) printf("\nO\t\tEstado: Cancelado");
		}
	printf("\nO-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n\n\n");
	//system("sleep 10"); 
	printf("\n\nVoltar (qualquer número)\n\n\n"); scanf("%d", &op);
	return OK;

}

int imprimirAgenda(TAgenda *agenda)
{
	if(vaziaAgenda(agenda)) return AGENDA_EMPTY;
	boolean flag = true;
	int i, j, op;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda -> Imprimir Agendas                                                    -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O                                                                                               O"); 
	for ( i = 0; i <= agenda->ultPos; i++)
	{
		printf("\nO | Nº: %d | \nO\t\t\tNome do professor: %s\nO\t\t\tId: %d\nO\t\t\tAno: %d\nO\n", i+1,agenda->item[i].nomeProf,agenda->item[i].idProf,agenda->item[i].ano); 
		if(vazioCompromisso(agenda,i)) printf("O\nO\t\t\tSem Compromissos\n");
		else
			for ( j = 0; j <= agenda->item[i].compromisso.ultPos; j++)
			{
				printf("O\nO\t\t\t\t Compromisso [%d]\n\n", j+1);
				tipoCompromisso(agenda->item[i].compromisso.item[j].tipo, agenda->item[i].compromisso.item[j].descricao);			
				printf("\nO\t\t\tData: %d/%d/%d",agenda->item[i].compromisso.item[j].tempo.data.dia,agenda->item[i].compromisso.item[j].tempo.data.mes,agenda->item[i].compromisso.item[j].tempo.data.ano);
				printf("\nO\t\t\tHora: %dh",agenda->item[i].compromisso.item[j].tempo.hora);
				if(agenda->item[i].compromisso.item[j].tipo==3)printf("\nO\t\t\Duração (dias): %d",agenda->item[i].compromisso.item[j].tempo.duracao);
				else
					printf("\nO\t\t\Duração (min): %d",agenda->item[i].compromisso.item[j].tempo.duracao);
				if(agenda->item[i].compromisso.item[j].estado == 1) printf("\nO\t\tEstado: A Cumprir");
				else if(agenda->item[i].compromisso.item[j].estado == 2) printf("\nO\t\tEstado: Adiado");
				else if(agenda->item[i].compromisso.item[j].estado == 3) printf("\nO\t\tEstado: Cancelado");
			}
		printf("\nO-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n\n\n");

	}
	printf("\n\nO Fim da lista."); 
	//system("sleep 10"); 
	printf("\n\nVoltar (qualquer número)\n\n\n"); scanf("%d", &op);
	return OK;

}
int recuperaAgenda(TAgenda *agenda)
{
	if(vaziaAgenda(agenda)) return AGENDA_EMPTY;
	boolean flag = true;
	int i, j, ano, mes, dia;
	remTempo(&ano, &mes, &dia);
	for ( i = 0; i <= agenda->ultPos; i++)
	{
		if(agenda->item[i].ano == ano)
		{
			printf("\nO | Nº: %d | \nO\t\t\tNome do professor: %s\nO\t\t\tId: %d\nO\t\t\tAno: %d\nO\n", i+1,agenda->item[i].nomeProf,agenda->item[i].idProf,agenda->item[i].ano); 
			if(!(vazioCompromisso(agenda,i)))
				for ( j = 0; j <= agenda->item[i].compromisso.ultPos; j++)
					if(agenda->item[i].compromisso.item[j].tempo.data.ano == ano)
					{
						printf("O\nO\t\t\t\t Compromisso [%d]\n\n", j+1);
						tipoCompromisso(agenda->item[i].compromisso.item[j].tipo, agenda->item[i].compromisso.item[j].descricao);	
						printf("\nO\t\t\tData: %d/%d/%d",agenda->item[i].compromisso.item[j].tempo.data.dia,agenda->item[i].compromisso.item[j].tempo.data.mes,agenda->item[i].compromisso.item[j].tempo.data.ano);
						if(agenda->item[i].compromisso.item[j].estado == 1) printf("\nO\t\tEstado: A Cumprir");
						else if(agenda->item[i].compromisso.item[j].estado == 2) printf("\nO\t\tEstado: Adiado");
						else if(agenda->item[i].compromisso.item[j].estado == 3) printf("\nO\t\tEstado: Cancelado");
					}
		}			
		printf("\nO-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n\n\n");

	}
	sleep("5");
	return OK;
}
int telaInicio()
{
	system("clear");
	int op;
	boolean flag=true;
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio                                                                                  -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O                                                                                               O\n");
	printf("O                                  1 - AGENDAS                                                  O\n");
	printf("O                                                                                               O\n");
	printf("O                                  2 - Sair                                                     O\n");
	printf("O                                                                                               O\n");
	printf("O                                                                                               O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
        printf("O\nO Opção: ");
	while(flag)
	{
		scanf("%d", &op);
		if(op == 1 || op == 2)return op;
		printf("O\nO Opção inválida: ");
	}
}


int telaAg()
{
	int op;
	boolean flag=true;
	system("clear");
	printf("O-O- Desenvolvedor: Edy Vemba \n"); 
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSOS PARA PROFESSORES\t\t        O\n");
	printf("O-O-\t\t\t\t\t\t\t\t\t\t\t     -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O-O- Inicio -> Agenda                                                                        -O-O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("O                                                                                               O\n");
	printf("O                                  1 - CRIAR NOVA AGENDA PARA UM PROFESSOR                      O\n");
	printf("O                                                                                               O\n");
	printf("O                                  2 - REMOVER AGENDA DE UM PROFESSOR                           O\n");
	printf("O                                                                                               O\n");
	printf("O                                  3 - ALTERAR AGENDA  DE UM PROFESSOR                          O\n");
	printf("O                                                                                               O\n");
	printf("O                                  4 - CONSULTAR AGENDA DE UM PROFESSOR                         O\n");
	printf("O                                                                                               O\n");
	printf("O                                  5 - VER AGENDAS                                              O\n");
	printf("O                                                                                               O\n");
	printf("O                                  6 - RECUPERAR AGENDA                                         O\n");
	printf("O                                                                                               O\n");
	printf("O                                  7 - VOLTAR                                                   O\n");
	printf("O                                                                                               O\n");
	printf("O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O-O\n");
	printf("\nOpção:");
	while(flag)
	{
		scanf("%d", &op);
		if(op >= 1 && op <= 7) return op;
		printf("O\nO Opção inválida: ");
	}
}
void telaAgenda(TAgenda *agenda)
{

}
void telaCompromisso()
{
	system("clear");
	printf("o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\n");
	printf("o-o-\t\t\t\t\t\t\t\t\t\t\t     -o-o\n");
	printf("o\t\t\t AGENDA UNIVERSITÁRIA DE COMPROMISSoS PARA PROFESSoRES\t\t        o\n");
	printf("o-o-\t\t\t\t\t\t\t\t\t\t\t     -o-o\n");
	printf("o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\n");
	printf("o-o- Inicio -> Agenda -> Compromissos                                                        -o-o\n");
	printf("o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\n");
	printf("o                                                                                               o\n");
	printf("o                                o 1 - CRIAR NOVO COMPROMISSO                                   o\n");
	printf("o                                                                                               o\n");
	printf("o                                o 2 - REMOVER UM COMPROMISSO                                   o\n");
	printf("o                                                                                               o\n");
	printf("o                                o 3 - CONSULTAR UM COMPROMISSO                                 o\n");
	printf("o                                                                                               o\n");
	printf("o                                o 4 - VER COMPROMISSOS                                         o\n");
	printf("o                                                                                               o\n");
	printf("o                                o 5 - VOLTAR                                                   o\n");
	printf("o                                                                                               o\n");
	printf("o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o\n");
	printf("o-o- Desenvolvedor: Edy Vemba ");                                                  
	printf("\nopção:");
}
#endif
