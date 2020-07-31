
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Fun��es auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"


/* -------------------------------------------------------------------
*  vari�veis globais
* ------------------------------------------------------------------- */
Tabela_Simbolos ts;

FILE* fp=NULL;
void geraCodigo (char* rot, char* comando) {

	if (fp == NULL) {
    	fp = fopen ("MEPA", "w");
  	}

	if ( rot == NULL ) {
		fprintf(fp, "     %s\n", comando); fflush(fp);
	} else {
		fprintf(fp, "%s: %s \n", rot, comando); fflush(fp);
	}
}

/*
	DESCOMENTAR POSTERIORMENTE !!!!
*/

// int imprimeErro ( char* erro ) {
// 	fprintf (stderr, "Erro na linha %d - %s\n", 1, erro);
// 	exit(-1);
// }

/* 
	-----------------------------
	|	MINHAS ALTERAÇÔES		|
	-----------------------------	
*/
void imprimeAMEM (int *num_variaveis){

	char str[12];

	sprintf(str, "AMEM %d", *num_variaveis);
	geraCodigo(NULL, str);
}


/* 
	-----------------------------
	|			DEBUG			|
	-----------------------------	
*/

void mostra_att_VS(Atributos_VS *ponteiro){
	printf("\t%s\t%d\n", ponteiro->tipo, ponteiro->deslocamento);
}

void mostra_att_PF(Atributos_PF *ponteiro){
	/*	Preencher Posteriormente */
}

void mostra_att_PROC(Atributos_PROC *ponteiro){
	/*	Preencher Posteriormente */
}


void mostraTabelaSimbolos(){

	printf("------------------------------\n");
	printf("TOPO: %d\tTAMANHO: %d\n", ts.topo, ts.tamanho);
	printf("------------------------------\n");
	for (int i = 0; i <= ts.topo; i++){
		/*	Imprime elemento da tabela de simbolos	*/
		printf("%s\t%d\t%d\t%p", ts.entrada[i].identificador, ts.entrada[i].categoria, ts.entrada[i].nivel, ts.entrada[i].ponteiro_atributos);

		/*	imprime atributos do elemento de acordo com a categoria	*/
		switch(ts.entrada[i].categoria){
			case VariavelSimples:
				mostra_att_VS(ts.entrada[i].ponteiro_atributos);
				break;
			case ParametroFormal:
				break;
			case Procedimento:
				break;
		}
		printf("\n");
	}
	printf("------------------------------\n\n");
}


/* 
	-----------------------------
	|		  FIM DEBUG			|
	-----------------------------	
*/

void InsereTabelaSimbolos(char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos){
	/*	Inicializando tabela de simbolos */
	if (ts.tamanho == 0){
		ts.tamanho = 1;
		ts.topo = -1;
		ts.entrada = malloc(sizeof(EntradaTabelaSimbolos));
	}

	/*	Caso não tenha espaço para novo simbolo, duplicar tamanho de tabela.	*/
	if (ts.tamanho <= (ts.topo + 1)){
		ts.tamanho  = ts.tamanho * 2;
		ts.entrada = realloc(ts.entrada, ts.tamanho * sizeof(EntradaTabelaSimbolos));
	}
	
	/*	Subindo topo da pilha e armazenando informações.	*/
	ts.topo ++;
	strcpy(ts.entrada[ts.topo].identificador, identificador);
	ts.entrada[ts.topo].categoria = categoria;
	ts.entrada[ts.topo].nivel = nivel;

	/*	Armazenando atributos de acordo com a categoria do simbolo	*/
	switch(categoria){
		case VariavelSimples:
			ts.entrada[ts.topo].ponteiro_atributos = malloc(sizeof(Atributos_VS));
			memcpy(ts.entrada[ts.topo].ponteiro_atributos, atributos, sizeof(Atributos_VS));
			break;
		case ParametroFormal:
			ts.entrada[ts.topo].ponteiro_atributos = malloc(sizeof(Atributos_PF));
			memcpy(ts.entrada[ts.topo].ponteiro_atributos, atributos, sizeof(Atributos_PF));
			break;
		case Procedimento:
			ts.entrada[ts.topo].ponteiro_atributos = malloc(sizeof(Atributos_PROC));
			memcpy(ts.entrada[ts.topo].ponteiro_atributos, atributos, sizeof(Atributos_PROC));
	}

	

	mostraTabelaSimbolos();
}

int main (){

	Atributos_VS dummy_AVS;

	strcpy(dummy_AVS.tipo, "Inteiro");
	dummy_AVS.deslocamento = 1;

	InsereTabelaSimbolos("a", VariavelSimples, 0, &dummy_AVS);
	InsereTabelaSimbolos("x", VariavelSimples, 1, &dummy_AVS);
	InsereTabelaSimbolos("c", VariavelSimples, 2, &dummy_AVS);
	InsereTabelaSimbolos("d", VariavelSimples, 3, &dummy_AVS);
}