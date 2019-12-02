#ifndef operacoes_h
#define operacoes_h

#include "estruturas.h"

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda
Objectivo: Inicializar a agenda
Devolve : agenda inicializada
---------------------------------------------------------------------------------------------------*/
void inicializarAgenda(TAgenda *agenda);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda
Objectivo: Verificar se a agenda está cheia
Devolve : Verdadeiro ou falso
---------------------------------------------------------------------------------------------------*/
boolean cheiaAgenda(TAgenda agenda);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda
Objectivo: Verificar se a agenda está vazia
Devolve : Verdadeiro ou falso
---------------------------------------------------------------------------------------------------*/
boolean vaziaAgenda(TAgenda agenda);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, id do professor, o nome e o ano
Objectivo: Criar uma agenda para um professor
Devolve : Agenda criada
---------------------------------------------------------------------------------------------------*/
int criarAgenda(TAgenda agenda, int idP, char nome[TAM], int ano);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, campo do tipo agenda para armazenar, id do professor
Objectivo: Remove agenda de um professor
Devolve : Agenda removida
---------------------------------------------------------------------------------------------------*/
int removerAgenda(TAgenda *agenda, TAgendaItem *agend, int *id);








/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, id do professor
Objectivo: Inicializar campo de compromissos da agenda de um professor
Devolve : campo de compromisso inicializdo
---------------------------------------------------------------------------------------------------*/
void inicializarCompromisso(TAgenda *agenda, int idP);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, id do professor
Objectivo: Verificar se o campo de compromisso da agenda de um professor está cheio
Devolve : Verdadeiro ou falso
---------------------------------------------------------------------------------------------------*/
boolean cheioCompromisso(TAgenda agenda, int idP);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, id do professor
Objectivo: Verificar se o campo de compromisso da agenda de um professor está vazio
Devolve : Verdadeiro ou falso
---------------------------------------------------------------------------------------------------*/
boolean vazioCompromisso(TAgenda agenda, int idP);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, id do professor, o tipo, a data, a hora, duração e descrição
Objectivo: Inserir novo compromisso no campo de compromisso da agenda de um professor
Devolve : Compromisso inserido na agenda
---------------------------------------------------------------------------------------------------*/
int inserirCompromisso(TAgenda *agenda, int idProf, int tipo, TData data, int hora, int duracao, char nome[TAM]);

/*---------------------------------------------------------------------------------------------------
Recebe: Estrutura da agenda, um campo de compromisso para armazenar, id do professor e id do compromisso
Objectivo: Remover um compromisso no campo de compromisso da agenda de um professor
Devolve : Compromisso removido na agenda
---------------------------------------------------------------------------------------------------*/
int removerCompromisso(TAgenda *agenda, TCompItem *compromisso, int idProf);


int telaInicio();

int buscaIdProf(TAgenda *agenda);
boolean eAdiavel(TAgenda agenda, int idP, int idComp);
int novaAgenda(TAgenda *agenda);
int novCompromisso(TAgenda *agenda, int idP);
int telaCmp(TAgenda *agenda, int *idP);
int imprimirAgenda(TAgenda *agenda);
int buscaIdComp(TAgenda *agenda, int idP);
int imprimirAgendaProf(TAgenda *agenda, int i);

void telaAgenda(TAgenda *agenda);
void resolveConflito(TAgenda *agenda, int idP);
int telaAg();
int recuperaAgenda(TAgenda *agenda);
void tipoCompromisso(int tipo);
int tipoComp();
void telaCmpId();
void insereTempo(TData *data, int *hora, int *duracao, int tipo);
void telaCompromisso();

void ordemPrioridade(TAgenda *agenda, int idP);
void trocaCompTipo(TAgenda *agenda, int idP, int i, int j);




#endif

