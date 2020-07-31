
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

/*	Insere novo simbolo em tabela de simbolos de acordo com sua categoria.	*/
void insereTabelaSimbolos(char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos){
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
}

/*	Busca simbolo em tabela de simbolos de acordo com o identificador, retornando ponteiro para atributos caso encontrado e NULL caso contrário.	*/
void * buscaTabelaSimbolos(unsigned char nivel, char* identificador){
	/* Busca em todos os simbolos validos, do topo a base.*/
	for (int i = ts.topo; i >= 0; i--){
		/* Compara se entrada corresponde a nível informado e depois compara identificadores */
		if ((ts.entrada[i].nivel == nivel) && (strcmp(ts.entrada[i].identificador, identificador) == 0 ))
			return ts.entrada[i].ponteiro_atributos;
	}
	return NULL;
}

/*	Removendo "quantidade" elementos da Tabela de simbolos. */
void retiraEntradasTabelaSimbolos(unsigned char quantidade){
	for (int i = ts.topo; i > (ts.topo - quantidade); i--){
		/*	liberando memória de atributos dos elementos	*/
		free(ts.entrada[i].ponteiro_atributos);
	}

	/*	Diminuindo pilha	*/
	ts.topo -= quantidade;
}

/*	Definindo o "tipo" para todas as "quantidade" variáveis a partir do topo	*/
void defineTipoVariavel(unsigned char quantidade, char* tipo){
	for (int i = ts.topo; i > (ts.topo - quantidade); i--){
		/*	liberando memória de atributos dos elementos	*/
		strcpy(((Atributos_VS *)ts.entrada[i].ponteiro_atributos)->tipo, tipo);
	}
}

int main (){

	Atributos_VS dummy_AVS;

	strcpy(dummy_AVS.tipo, "");
	dummy_AVS.deslocamento = 1;
	insereTabelaSimbolos("a", VariavelSimples, 0, &dummy_AVS);
	mostraTabelaSimbolos();

	strcpy(dummy_AVS.tipo, "");
	dummy_AVS.deslocamento ++;
	insereTabelaSimbolos("b", VariavelSimples, 0, &dummy_AVS);
	mostraTabelaSimbolos();

	defineTipoVariavel(2, "Inteiro");
	mostraTabelaSimbolos();

	retiraEntradasTabelaSimbolos(2);

	strcpy(dummy_AVS.tipo, "");
	dummy_AVS.deslocamento ++;
	insereTabelaSimbolos("c", VariavelSimples, 1, &dummy_AVS);
	mostraTabelaSimbolos();

	strcpy(dummy_AVS.tipo, "");
	dummy_AVS.deslocamento ++;
	insereTabelaSimbolos("d", VariavelSimples, 2, &dummy_AVS);
	mostraTabelaSimbolos();
	
	defineTipoVariavel(2, "Boolean");
	mostraTabelaSimbolos();

	strcpy(dummy_AVS.tipo, "");
	dummy_AVS.deslocamento ++;
	insereTabelaSimbolos("e", VariavelSimples, 2, &dummy_AVS);
	mostraTabelaSimbolos();	
	
	defineTipoVariavel(1, "Float");
	mostraTabelaSimbolos();

}