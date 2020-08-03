
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

/*Armazena o nível  nível léxico*/
int nivel_lexico = 0;

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

/*  Auxilia na recuperação de Atributos */
void   *atributos;

%}

%union{
    EntradaTabelaSimbolos entrada_ts;
    char    texto[128];
}

/* DEFINIÇÃO PARA ESTADOS TERMINAIS */

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


/*!!!!!! NÃO UTILIZADOS !!!!!!!*/
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION GOTO IF THEN ELSE WHILE DO


/* DEFINIÇÃO PARA ESTADOS NÃO-TERMINAIS */

%type <texto> variavel fator termo exp_simples expressao

%%

programa    :{ geraCodigo (NULL, "INPP"); } PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  {geraCodigo (NULL, "PARA"); }
;

bloco       : parte_declara_vars comando_composto 
;


/*
    ------------------------------------------
    |   INICIO --- DECLARAÇÃO DE VARIAVEIS    |
    ------------------------------------------
*/

parte_declara_vars: {num_vars = 0;} var { imprimeAMEM(&num_vars); }
;


var         :   VAR declara_vars
            |   /* VAZIO */
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var :   {desloc = 0;} lista_id_var DOIS_PONTOS tipo  PONTO_E_VIRGULA
;

tipo        : IDENT
                {
                    defineTipoVariavel(desloc, token);    /* Definindo o tipo das "desloc" variáveis para "token" */
                }

;

lista_id_var: lista_id_var VIRGULA IDENT    
                { 
                    num_vars ++;

                    strcpy($3.identificador, token);         /* Resgata nome de variável. */
                    $3.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    $3.nivel = nivel_lexico;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos($3.identificador, $3.categoria, $3.nivel, &avs);

                    desloc ++;  /* Incrementa deslocamento par aproxima variável.*/
                } 
            | IDENT 
                { 
                    num_vars ++;
                    strcpy($1.identificador, token);         /* Resgata nome de variável. */
                    $1.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    $1.nivel = nivel_lexico;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos($1.identificador, $1.categoria, $1.nivel, &avs);

                    desloc ++;  /* Incrementa deslocamento par aproxima variável.*/

                }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT 
;

/*
    ---------------------------------------
    |   FIM --- DECLARAÇÃO DE VARIAVEIS    |
    ---------------------------------------
*/

comando_composto: T_BEGIN comandos T_END 

comandos:   comando_sem_rotulo 
        |   NUMERO DOIS_PONTOS comando_sem_rotulo
        |   comandos PONTO_E_VIRGULA comandos
        |   /* VAZIO -> MARS PORQUE NÃO EXISTE EM DEFINIÇÃO? */
;

comando_sem_rotulo  :   atribui
; 

// LINHA 19
atribui :   variavel ATRIBUICAO expressao
                {
                    /* Verificando se 'variavel' $1 e 'expressao' $3 possuem o mesmo tipo */
                    validaTipos(nl,$1, $3);
                }
;

// LINHA 25
expressao:   exp_simples
                {
                    /* Repassando tipo de 'exp_simples' ($1) para 'expressao'($$) */
                    strcpy($$, $1);
                }

        |   exp_simples relacao exp_simples
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'expressao' */
                    strcpy($$, validaTipos(nl,$1, $3));
                }
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
                    {
                        /* Repassando tipo de 'fator' ($2) para 'termo'($$) */
                        strcpy($$, $2);
                    }

            |   exp_simples SOMA termo
                    {
                        /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                        strcpy($$, validaTipos(nl,$1, $3));
                    }
            |   exp_simples SUBTRACAO termo
                    {
                        /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                        strcpy($$, validaTipos(nl,$1, $3));
                    }
            |   exp_simples OR termo
                    {
                        /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                        strcpy($$, validaTipos(nl,$1, $3));
                    }
;

sinal   :   /*VAZIO*/
        |   SOMA    
        |   SUBTRACAO
;

// LINHA 28
termo   :   fator 
                {
                    /* Repassando tipo de 'fator' ($1) para 'termo'($$) */
                    strcpy($$, $1);
                }

        |   termo PRODUTO fator                 
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                    strcpy($$, validaTipos(nl,$1, $3));
 
                }
        |   termo DIVISAO fator
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                    strcpy($$, validaTipos(nl,$1, $3));
                }
        |   termo AND fator
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                    strcpy($$, validaTipos(nl,$1, $3));
                }
; 
              
// LINHA 29
fator   :   variavel
                {
                    /* Repassando tipo de 'variavel' ($2) para 'fator'($$) */
                    strcpy($$, $1);
                }
        |   NUMERO
                {
                    /* Definindo tipo de 'fator' para 'integer'. */
                    strcpy($$, "integer");
                }
        /* ADCIONAR ASSIM QUE FUNÇÕES FOREM APRESENTADAS.*/
//      |   chamada_funcao  
        |   ABRE_PARENTESES expressao FECHA_PARENTESES
                {
                    /* Repassando tipo de 'expressao' ($2) para 'fator'($$) */
                    strcpy($$, $2);
                }
        |   NOT fator
                {
                    /* Repassando tipo de  $2 para $$ */
                    strcpy($$, $2);
                }
;

// LINHA 30
variavel:   IDENT
                {
                    // [FAZER] Buscar atributo de variáveis e repassar pra "variavel"
                    // [FAZER] Verificar existência de IDENT (retorno de buscaTabelaSimbolos).
                                            
                    /* Armazena em 'avs' atributos de 'token' após verificação por validaSimbolo(); */
                    avs = *( (Atributos_VS *) validaSimbolo(token));

                    /* repassa tipo de IDENT para 'variavel' .*/
                    strcpy($$,  avs.tipo);
                }
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

