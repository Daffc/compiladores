
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
Pilha_Rotulos pr;
ControleEscopo ce;


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

int imprimeErro ( char* erro ) {
	fprintf (stderr, "Erro na linha %d - %s\n", 1, erro);
	exit(-1);
}

/* 
	-----------------------------
	|	MINHAS ALTERAÇÔES		|
	-----------------------------	
*/
/* 
	-----------------------------
	|			DEBUG			|
	-----------------------------	
*/

void mostra_att_VS(Atributos_VS *ponteiro){
	printf("\t%s\t%d\n", ponteiro->tipo, ponteiro->deslocamento);
}

void mostra_att_PF(Atributos_PF *ponteiro){
	printf("\t%s\t%d\t%d\n", ponteiro->tipo, ponteiro->deslocamento, ponteiro->tipo_passagem);
}

void mostra_att_PROC(Atributos_PROC *ponteiro){
	printf("\n");
	printf("\t%s\t%d\n", ponteiro->rotulo, ponteiro->quantidade_parametros);
	for (int i = 0; i < ponteiro->quantidade_parametros; i++)
		printf("\t\t%s\t%d\n", ponteiro->entradas_parametros[i].tipo, ponteiro->entradas_parametros[i].tipo_passagem);
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
				mostra_att_PF(ts.entrada[i].ponteiro_atributos);
				break;
			case Procedimento:
				mostra_att_PROC(ts.entrada[i].ponteiro_atributos);
				break;
		}
		printf("\n");
	}
	printf("------------------------------\n\n");
}

void mostraPilhaRotulos(){

	printf("------------------------------\n");
	printf("TOPO: %d\tCONTADOR: %d\n", pr.topo, pr.contador);
	printf("------------------------------\n");
	for (int i = pr.topo; i >= 0; i--){
		/*	Imprime elemento da tabela de simbolos	*/
		printf("%d\t%d", i, pr.rotulos[i]);
		printf("\n");
	}
	printf("------------------------------\n\n");
}

void mostraPilhaControleEscopo(){

	printf("------------------------------\n");
	printf("TOPO: %d\n", ce.topo);
	printf("------------------------------\n");
	for (int i = ce.topo; i >= 0; i--){
		/*	Imprime elemento da tabela de simbolos	*/
		printf("%d\t%d\t%d\t%d", i, ce.entradas_escopo[i]. quantidade_vars, ce.entradas_escopo[i].quantidade_procs, ce.entradas_escopo[i].quantidade_parametros );
		printf("\n");
	}
	printf("------------------------------\n\n");
}


/* 
	-----------------------------
	|		  FIM DEBUG			|
	-----------------------------	
*/
/*	
	--------------------------------------
	| 	INICIO --- TABELA DE SIMBOLOS    |
	--------------------------------------
*/

/*	Inicializando Tabela de Simbolos*/
void iniciaTabelaSimbolos(){

	/*	Inicializando tabela de simbolos com uma entrada. */
	ts.tamanho = 1;
	ts.topo = -1;
	ts.entrada = malloc(sizeof(EntradaTabelaSimbolos));
}

/*	Insere novo simbolo em tabela de simbolos de acordo com sua categoria.	*/
void insereTabelaSimbolos(int linha, char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos){

	// Cerifica se novo simbolo 'identificador' pode ser inserido em Tabela de Simbolos.
	validaInsercaoSimbolo(linha, identificador, nivel, categoria);

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

/*	Busca simbolo em tabela de simbolos de acordo com o identificador, retornando ponteiro para entrada de identificador caso encontrado e NULL caso contrário.	*/
EntradaTabelaSimbolos * buscaTabelaSimbolos(char* identificador){
	/* Busca em todos os simbolos validos, do topo a base.*/
	for (int i = ts.topo; i >= 0; i--){
		/* Compara se entrada corresponde a nível informado e depois compara identificadores */
		if ( strcmp(ts.entrada[i].identificador, identificador) == 0 )
			return &(ts.entrada[i]);
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
		/*	Definindo o tipo da variavel */
		strcpy(((Atributos_VS *)ts.entrada[i].ponteiro_atributos)->tipo, tipo);
	}
}

/*	Definindo o "tipo" para todas as "quantidade" variáveis a partir do topo	*/
void defineTipoParametroFormal(unsigned char quantidade, char* tipo, TipoPassagemParametro tipo_passagem){
	for (int i = ts.topo; i > (ts.topo - quantidade); i--){
		
		/*	Definindo o tipo do parâmetro formal */
		strcpy(((Atributos_PF *)ts.entrada[i].ponteiro_atributos)->tipo, tipo);
		/*	Definindo o tipo de passagem do parâmetro formal */
		((Atributos_PF *)ts.entrada[i].ponteiro_atributos)->tipo_passagem = tipo_passagem;
	}
}

/* Define deslocamento de 'quantidade' parâmetros formais. */
void deslocaParametrosFormais(unsigned char quantidade){
	
	int contador = 0;
	for (int i = ts.topo; i > (ts.topo - quantidade); i--){
		
		((Atributos_PF *)ts.entrada[i].ponteiro_atributos)->deslocamento = - (4 + contador);
		contador ++;
	}
}

/* Preenche parte de parâmetros em entrada de Procedimento em TS. */
void preencheAtributosProcedimento(int quantidade){

	int contador = quantidade - 1;
	Atributos_PROC *entrada_proc;

	entrada_proc = ((Atributos_PROC *) ts.entrada[ts.topo - quantidade].ponteiro_atributos);

	// Define a quantidade de parâmetros recebidos por procedimento.
	entrada_proc->quantidade_parametros = quantidade;

	for (int i = ts.topo; i > (ts.topo - quantidade); i--){
		
		// Copiando tipo do parãmetro.
		strcpy(entrada_proc->entradas_parametros[contador].tipo, ((Atributos_PF *)ts.entrada[i].ponteiro_atributos)->tipo); 
		// Copiando tipo de passagem to parâmetro (valor/referência).
		entrada_proc->entradas_parametros[contador].tipo_passagem = ((Atributos_PF *)ts.entrada[i].ponteiro_atributos)->tipo_passagem; 
		
		contador --;
	}
}

/* Libera Memória Alocada por Tablea de Simbolos*/
void liberaTabelaSimbolos(){
	free(ts.entrada);
}

/* 
	-----------------------------------
	|	FIM --- TABELA DE SIMBOLOS     |
	-----------------------------------	
*/

/* 
	-------------------------
	|		VALIDAÇÃO		|
	-------------------------	
*/

char * validaTipos(int linha, char *primeiro, char *segundo){

	// Verifica se "primeiro" e "segundo" NÃO são do mesmo tipo, informando erro caso verdadeiro.
	if(strcmp(primeiro, segundo)){
		/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
		fprintf (stderr,"ERRO LINHA %d: Operação entre '%s' e '%s' inválida.\n", linha, primeiro, segundo);
		exit(-1);
	}

	/* Retorna ponteiro para string 'primeiro' */
	return primeiro;
}


char * validaParametro(int linha, char *primeiro, char *segundo){

	// Verifica se "primeiro" e "segundo" NÃO são do mesmo tipo, informando erro caso verdadeiro.
	if(strcmp(primeiro, segundo)){
		/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
		fprintf (stderr,"ERRO LINHA %d: Tipo de parâmetro '%s' incompatível ( esperado: '%s' ).\n", linha, primeiro, segundo);
		exit(-1);
	}

	/* Retorna ponteiro para string 'primeiro' */
	return primeiro;
}


EntradaTabelaSimbolos * validaSimbolo(int linha, char *simbolo){
	
	/* Recupera atributos da variável */
	EntradaTabelaSimbolos *ponteiro = buscaTabelaSimbolos(simbolo);

	/* Verifica se 'simbolo' NÃO consta em Tabela de Sombolos, retirnando mensagem. */
	if (!ponteiro){
		/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
		fprintf (stderr,"ERRO LINHA %d: Simbolo '%s' não definido.\n", linha, simbolo);
		exit(-1);
	}
	
	/* Retorna ponteiro para entrada de 'simbolo' caso ele seja encontrado */
	return ponteiro;
}

// Verifica se quantidade de parâmetros é igual, caso contrário retorna erro.
void validaNumParametros(int linha, int parametros_encontraros, int parametros_necesarios){

	if(parametros_encontraros != parametros_necesarios){
		/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
		fprintf (stderr,"ERRO LINHA %d: Quantidade de parâmetros incompatível ( esperado %d, recebido %d ).\n", linha, parametros_necesarios, parametros_encontraros);
		exit(-1);
	}
}

// Verifica se o simbolo 'identificador' pode ser inserido em Tabela de Simbolos, caso contrário retorna erro.
void validaInsercaoSimbolo(int linha, char *identificador, int nivel, CategoriaSimbolos categoria){

	// Busca por simbolo em Tabela de Simbolos.
	EntradaTabelaSimbolos *entrada = buscaTabelaSimbolos(identificador);

	// Caso simbolo conste em Tabela de Simbolos.
	if (entrada){

		// Caso Categoria do Simbolo encontrado seja VariavelSimples.
		if (categoria == VariavelSimples){
			if(entrada->nivel == nivel){
				/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
				fprintf (stderr,"ERRO LINHA %d: Simbolo entre '%s' já foi declarado neste escopo.\n", linha, identificador);
				exit(-1);
			}
		}
		// Caso Categoria do Simbolo encontrado seja Procedimento.
		if (categoria == Procedimento){
			if(entrada->nivel == (nivel) || entrada->nivel == (nivel - 1) ){
				/* [MELHORAR] Descobrir melhor maneira de mostar erros e para execussão.*/
				fprintf (stderr,"ERRO LINHA %d: Simbolo entre '%s' já foi declarado neste escopo.\n", linha, identificador);
				exit(-1);
			}
		}
	}

}

/* 
	-----------------------------
	|		FIM VALIDAÇÃO		|
	-----------------------------	
*/
/*	
	--------------------------------------------
	| 	INICIO --- PILHA DE CONTROLE ESCOPO    |
	--------------------------------------------
*/

/* Inicia  a pilha de controle de escopos.  */
void iniciaPilhaControleEscopo(){
	ce.topo = -1;
}

/* Empilha 'entrada' de escopo. */
EntradaEscopo empilhaControleEscopo( EntradaEscopo entrada){
	
	/* Ajustando topo */
	ce.topo++;

	/* Verifica se é possível armazenar novo escopo */
	if(pr.topo >= MAX_ESCOPO){
		fprintf (stderr,"ERRO: Quantidade máxima de Escopos ativos (%d) excedida.\n", MAX_ESCOPO);
		exit(-1);
	}

	ce.entradas_escopo[ce.topo] = entrada;

	return  ce.entradas_escopo[ce.topo];
}

/* Desempilha 'entrada' de escopo. */
EntradaEscopo desempilhaControleEscopo(){
	
	EntradaEscopo entrada;
	
	/* Verifica se existe escopo a ser desempilhado. */
	if(ce.topo < 0){
		fprintf (stderr,"ERRO: Não existe escopo a ser desempilhado.\n");
		exit(-1);
	}

	entrada = ce.entradas_escopo[ce.topo];

	/* Ajustando contadores */
	ce.topo --;	

	return  entrada;
}
/*
    -----------------------------------------
    |   FIM --- PILHA DE CONTROLE ESCOPO    |
    -----------------------------------------
*/

/*	
	------------------------------------
	| 	INICIO --- PILHA DE ROTULOS    |
	------------------------------------
*/

/* Define valores Iniciais para Pilha de Rotulos vazia. */
void iniciaPilhaRotulos(){
	pr.topo = -1;
	pr.contador = -1;
}

/* Empilha novo elemento na Pilha de Rotulos e retorna seu rótulo. */
void empilhaRotulo( char *rotulo){
	
	/* Ajustando contadores */
	pr.contador ++;
	pr.topo++;

	/* Verifica se é possível armazenar novo rótulo */
	if(pr.topo >= MAX_ROTULOS){
		fprintf (stderr,"ERRO: Quantidade máxima de Rotulos ativos (%d) excedida.\n", MAX_ROTULOS);
		exit(-1);
	}

	/* Armazena contador de rótulo */
	pr.rotulos[pr.topo] = pr.contador;
	
	/*Retorna retorna rótulo em ponteiro 'rotulo'*/
	sprintf(rotulo, "R%02d", pr.contador);

}
/* Busca elemento na tabela de simbolos de acordo com o identificador informado.*/
void desempilhaRotulo(char *rotulo){

	/* Verifica se existe rótulo a ser desempilhado. */
	if(pr.topo < 0){
		fprintf (stderr,"ERRO: Não existe rótulo a ser desempilhado.\n");
		exit(-1);
	}

	/*Retorna retorna rótulo em ponteiro 'rotulo'*/
	sprintf(rotulo, "R%02d", pr.rotulos[pr.topo]);

	/* Ajustando contadores */
	pr.topo --;	
}

/*
    ---------------------------------
    |   FIM --- PILHA DE ROTULOS    |
    ---------------------------------
*/


/* 
	-----------------------------
	|		DEFINIÇÕES MEPA		|
	-----------------------------	
*/


/*Recebe o número de variáveis em num_variaveis e imprime "AMEM num_variaveis" em MEPA*/
void imprimeAMEM (int *num_variaveis){

	char str[12];

	sprintf(str, "AMEM %d", *num_variaveis);
	geraCodigo(NULL, str);
}


/* Recebe texto com valor de constante e imprime em arquivo MEPA */
void carregaConstanteMEPA(char *constante){

	char resultado[20];

	/* Armazenando comando 'CRCT constante' em buffer resltado */	
	sprintf(resultado, "CRCT %s", constante);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
}

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de recuperação de variável em arquivo MEPA.*/
void carregaVariavelSimplesMEPA(int nivel_lexico, int deslocamento){

	char 	resultado[20];

	/* Armazenando comando 'CRCT nivel_lexico,deslocamento' em buffer resltado */
	sprintf(resultado, "CRVL %d,%d", nivel_lexico, deslocamento);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
}

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de armazenamento de valore em variavel MEPA.*/
void armazenaVariavelSimplesMEPA(int nivel_lexico, int deslocamento){

	char 	resultado[20];

	/* Armazenando comando 'ARMZ nivel_lexico,deslocamento' em buffer resltado */
	sprintf(resultado, "ARMZ %d,%d", nivel_lexico, deslocamento);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
}

/* Recebe 'rotulo' imprime comando MEPA de desvio condicional em arquivo MEPA.*/
void imprimeDesviaSeFalsoMEPA(char* rotulo){
	
	char resultado[20];

	/* Imnprimeindo comando 'DSVF rotulo' em buffer resltado */
	sprintf(resultado, "DSVF %s", rotulo);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
}

/* Recebe 'rotulo' imprime comando MEPA de desvio incondicional em arquivo MEPA.*/
void imprimeDesviaSempre(char* rotulo){
	
	char resultado[20];

	/* Imnprimeindo comando 'DSVS rotulo' em buffer resltado */
	sprintf(resultado, "DSVS %s", rotulo);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
}

/* Recebe 'rotulo' e 'nivelL léxico' imprime comando MEPA de entrada de procedimento em arquivo MEPA.*/
void imprimeEntraProcedimento(char *rotulo, int nivel_lexico){
	
	char resultado[20];

	/* Imnprimeindo comando 'ENPR nivel_lexico' em buffer resltado */
	sprintf(resultado, "ENPR %d", nivel_lexico);

	/* Imprimindo resultado em MEPA */
	geraCodigo(rotulo,resultado);
}

/* Recebe a quantidade de variáveis a serem desalocadas em 'quantidade' e imprime 'DMEM quantidade' */
void imprimeDesalocaMemoria(int quantidade){

	char resultado[20];

	/* Imnprimeindo comando 'ENPR nivel_lexico' em buffer resltado */
	sprintf(resultado, "DMEM %d", quantidade);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
};

/* Recebe a o nível léxico e a quantidade de parâmetros da função a ser retornada e imprime 'RPTR nivel_lexico,quantidade_parametros' */
void imprimeRetornaProcedimento(int nivel_lexico, int quantidade_parametros){

	char resultado[20];

	/* Imnprimeindo comando 'RPTR nivel_lexico,quantidade_parametros' em buffer resltado */
	sprintf(resultado, "RPTR %d,%d", nivel_lexico, quantidade_parametros);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
};

/* Recebe o rótulo e o nível léxico de retorno da função a ser chamada e imprime 'CHPR rotulo,nivel_lexico' */
void imprimeChamaProcedimento(char *rotulo,int nivel_lexico){
	
	char resultado[20];

	/* Imnprimeindo comando 'CHPR rotulo,nivel_lexico' em buffer resltado */
	sprintf(resultado, "CHPR %s,%d", rotulo, nivel_lexico);

	/* Imprimindo resultado em MEPA */
	geraCodigo(NULL,resultado);
};



/* 
	---------------------------------
	|		FIM DEFINIÇÕES MEPA		|
	---------------------------------	
*/


/* 
	-----------------------------
	|			DEBUG			|
	-----------------------------	
*/

// int main (){
// 	EntradaEscopo entrada;

// 	iniciaPilhaControleEscopo();

// 	entrada.quantidade_simbolos = 0;
// 	entrada.quantidade_vars = 0;
// 	entrada.quantidade_procs = 0;
// 	empilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// 		entrada.quantidade_simbolos = 1;
// 		entrada.quantidade_vars = 0;
// 	entrada.quantidade_procs = 0;
// 	empilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// 	entrada = desempilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// 		entrada.quantidade_simbolos = 2;
// 		entrada.quantidade_vars = 0;
// 	entrada.quantidade_procs = 0;
// 	empilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// 		entrada.quantidade_simbolos = 3;
// 		entrada.quantidade_vars = 0;
// 	entrada.quantidade_procs = 0;
// 	empilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// 		entrada.quantidade_simbolos = 4;
// 		entrada.quantidade_vars = 0;
// 	entrada.quantidade_procs = 0;
// 	empilhaControleEscopo(entrada);
// 	mostraPilhaControleEscopo();

// }

/* 
	-----------------------------
	|		  FIM DEBUG			|
	-----------------------------	
*/
