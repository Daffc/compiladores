
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

/* Armazena a quandtidade de variáveis para impressão de "AMEM num_vars */
int num_vars;

/* Armazena a quantidade de variáveis a terem sei tipo identificado. */
int desloc;

/*  Armazena atributos de variável simples*/
Atributos_VS avs;

/*  Armazena atributos de parâmetro formal */
Atributos_PF apf;

/*  Armazena atributos de procedimento */
Atributos_PROC aproc;

%}

%union{
    EntradaTabelaSimbolos entrada_ts;
}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR  ATRIBUICAO

/* TOKENS RELAÇÃO */
%token IGUAL DIFERENTE MENOR_QUE MAIOR_QUE MENOR_OU_IGUAL MAIOR_OU_IGUAL

/* TOKENS OPERAÇÕES */
%token SOMA SUBTRACAO PRODUTO DIVISAO OR AND NOT

/*  TOKEN NUMEROS */
%token NUMERO
/* TOKEN IDENTIFICADOR */
%token <entrada_ts> IDENT

%%

programa    :{ geraCodigo (NULL, "INPP"); } PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  {geraCodigo (NULL, "PARA"); }
;

bloco       : parte_declara_vars comando_composto 
;




parte_declara_vars: {num_vars = 0;} var { imprimeAMEM(&num_vars); }
;


var         :  {desloc = 0;} VAR declara_vars
            | /* VAZIO */
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { } lista_id_var DOIS_PONTOS tipo PONTO_E_VIRGULA
;

tipo        : IDENT
                {
                    defineTipoVariavel(num_vars, token);    /* Definindo o tipo das "num-vars" variáveis para "token" */
                    mostraTabelaSimbolos();
                }

;

lista_id_var: lista_id_var VIRGULA IDENT    
                { 
                    num_vars ++;

                    strcpy($3.identificador, token);         /* Resgata nome de variável. */
                    $3.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    $3.nivel = nl;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos($3.identificador, $3.categoria, $3.nivel, &avs);
                    mostraTabelaSimbolos();

                    desloc ++;  /* Incrementa deslocamento par aproxima variável.*/
                } 
            | IDENT 
                { 
                    num_vars ++;
                    strcpy($1.identificador, token);         /* Resgata nome de variável. */
                    $1.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    $1.nivel = nl;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos($1.identificador, $1.categoria, $1.nivel, &avs);
                    mostraTabelaSimbolos();

                    desloc ++;  /* Incrementa deslocamento par aproxima variável.*/

                }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT 
;


comando_composto: T_BEGIN comandos T_END 

comandos:   comando_sem_rotulo
        |   NUMERO comando_sem_rotulo
;

comando_sem_rotulo  :   atribui
; 

// LINHA 19
atribui :   variavel ATRIBUICAO exp
;


// LINHA 25
exp     :   exp_simples
        |   relacao exp_simples
;

//LINHA 26
relacao :   IGUAL
        |   DIFERENTE
        |   MENOR_QUE
        |   MAIOR_QUE
        |   MENOR_OU_IGUAL
        |   MAIOR_OU_IGUAL
;

//LINHA 27
exp_simples :   sinal termo
            |   sinal termo SOMA termo
            |   sinal termo SUBTRACAO termo
            |   sinal termo OR termo

sinal   :   /*VAZIO*/
        |   SOMA    
        |   SUBTRACAO

// LINHA 28
termo   :   fator 
        |   fator PRODUTO
        |   fator DIVISAO
        |   fator AND
                  
// LINHA 29
fator   :   variavel
        |   NUMERO
        /* ADCIONAR ASSIM QUE FUNÇÕES FOREM APRESENTADAS.*/
        // |   chamada_funcao  
        |   NOT fator
;

// LINHA 30
variavel:   IDENT
;


%%

int main (int argc, char** argv) {
    FILE* fp;
    extern FILE* yyin;

    if (argc<2 || argc>2) {
            printf("usage compilador <arq>a %d\n", argc);
            return(-1);
        }

    fp=fopen (argv[1], "r");
    if (fp == NULL) {
        printf("usage compilador <arq>b\n");
        return(-1);
    }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
    Tabela_Simbolos ts;
    yyin=fp;
    yyparse();

    return 0;
}

