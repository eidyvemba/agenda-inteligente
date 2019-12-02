#ifndef estruturas_h
#define estruturas_h

#define D 15
#define TAM 100


typedef enum {false, true} boolean;

typedef struct
{
	int dia;
	int mes;
	int ano;

}TData;
typedef struct
{
	TData data;
	int hora;
	int duracao;

}TTempo;

typedef struct
{
	int tipo;
	char descricao[TAM];
	TTempo tempo;
	boolean eAd;
	int estado;
}TCompItem;

typedef struct 
{
	TCompItem item[TAM];
	int ultPos;
}TCompromisso;

typedef struct 
{
	int idProf;
	char nomeProf[TAM];
	int ano;
	TCompromisso compromisso;
}TAgendaItem;

typedef struct 
{
	TAgendaItem item[TAM];
	int ultPos;
}TAgenda;


#endif
