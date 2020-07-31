
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

// int imprimeErro ( char* erro ) {
// 	fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
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


void mostraTabelaSimbolos(){

	printf("------------------------------\n");
	printf("TOPO: %d\tTAMANHO: %d\n", ts.topo, ts.tamanho);
	printf("------------------------------\n");
	for (int i = 0; i <= ts.topo; i++)
		printf("%s\t%d\t%d\t%p\n", ts.entrada[i].identificador, ts.entrada[i].categoria, ts.entrada[i].nivel, ts.entrada[i].ponteiro_atributos);
	printf("------------------------------\n\n");
}
void InsereTabelaSimbolos(char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos){

	if (ts.tamanho == 0){
		ts.tamanho = 1;
		ts.topo = -1;
		ts.entrada = malloc(sizeof(ts.entrada));
	}
	if (ts.tamanho <= (ts.topo + 1)){
		ts.tamanho  = ts.tamanho * 2;
		ts.entrada = realloc(ts.entrada, ts.tamanho * sizeof(EntradaTabelaSimbolos));
	}
	
	ts.topo ++;
	strcpy(ts.entrada[ts.topo].identificador, identificador);
	ts.entrada[ts.topo].categoria = categoria;
	ts.entrada[ts.topo].nivel = nivel;

	mostraTabelaSimbolos();
}

int main (){
	InsereTabelaSimbolos("a", VariavelSimples, 0, NULL);
	InsereTabelaSimbolos("x", VariavelSimples, 1, NULL);
	InsereTabelaSimbolos("c", VariavelSimples, 2, NULL);
	InsereTabelaSimbolos("d", VariavelSimples, 3, NULL);
}