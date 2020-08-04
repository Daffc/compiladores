
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

/* Auxilia em operções com entrada da tablea de simbolos. */
EntradaTabelaSimbolos entrada_ts;
%}

%union{
    Variavel_Simples v_sim;
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
%token IDENT


/*!!!!!! NÃO UTILIZADOS !!!!!!!*/
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION GOTO IF THEN ELSE WHILE DO


/* DEFINIÇÃO PARA ESTADOS NÃO-TERMINAIS */
%type <v_sim> variavel
%type <texto> fator termo exp_simples expressao

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

                    strcpy(entrada_ts.identificador, token);         /* Resgata nome de variável. */
                    entrada_ts.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    entrada_ts.nivel = nivel_lexico;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);

                    desloc ++;  /* Incrementa deslocamento par aproxima variável.*/
                } 
            | IDENT 
                { 
                    num_vars ++;
                    strcpy(entrada_ts.identificador, token);         /* Resgata nome de variável. */
                    entrada_ts.categoria = VariavelSimples;          /* Definindo Categoria de entrada. */
                    entrada_ts.nivel = nivel_lexico;                           /* Indica o nível lexico da VS atual */
                    avs.tipo[1] = '\0';      /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = desloc; /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);

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
                    validaTipos(nl, $1.tipo, $3);

                    /* Defindo instrução MEPA para armazenamento em 'variavel' */
                    armazenaVariavelSimplesMEPA($1.nivel, $1.deslocamento);
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

                        /* Imprime comando MEPA de SOMA. */
                        geraCodigo(NULL, "SOMA");
                    }
            |   exp_simples SUBTRACAO termo
                    {
                        /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                        strcpy($$, validaTipos(nl,$1, $3));

                        /* Imprime comando MEPA de SUBTRAÇÃO. */
                        geraCodigo(NULL, "SUBT");
                    }
            |   exp_simples OR termo
                    {
                        /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                        strcpy($$, validaTipos(nl,$1, $3));

                        /* Imprime comando MEPA de DISJUNÇÃO. */
                        geraCodigo(NULL, "DISJ");
                    }
;

sinal   :   /*VAZIO*/
        |   SOMA    
        |   SUBTRACAO
                {
                    /* Imprime comando MEPA de INVERSÃO DE SINAL. */
                    geraCodigo(NULL, "INVER");
                }
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

                    /* Imprime comando MEPA de MULTIPLICAÇÃO. */
                    geraCodigo(NULL, "MULT");
 
                }
        |   termo DIVISAO fator
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                    strcpy($$, validaTipos(nl,$1, $3));
                    
                    /* Imprime comando MEPA de DIVISÃO. */
                    geraCodigo(NULL, "DIVI");
                }
        |   termo AND fator
                {
                    /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                    strcpy($$, validaTipos(nl,$1, $3));

                    /* Imprime comando MEPA de CONJUNÇÃO. */
                    geraCodigo(NULL, "CONJ");
                }
; 
              
// LINHA 29
fator   :   variavel
                {
                    /* Repassando tipo de 'variavel' ($2) para 'fator'($$) */
                    strcpy($$, $1.tipo);

                    carregaVariavelSimplesMEPA( nivel_lexico, $1.deslocamento);
                }
        |   NUMERO
                {
                    /* Definindo tipo de 'fator' para 'integer'. */
                    strcpy($$, "integer");

                    /* Imprime comando MEPA de definição de constante. */
                    carregaConstanteMEPA(token);
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

                    /* Imprime comando MEPA de negação. */
                    geraCodigo(NULL, "NEGA");
                }
;

// LINHA 30
variavel:   IDENT
                {              
                    /* Armazena em 'avs' atributos de 'token' após verificação por validaSimbolo(); */
                    avs = *( (Atributos_VS *) validaSimbolo(token));

                    /* Populando 'variavel' com atributos recebidos de Tabela de Simbolos. */
                    strcpy($$.token, token);
                    strcpy($$.tipo, avs.tipo);
                    $$.nivel = nivel_lexico;
                    $$.deslocamento = avs.deslocamento;
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

