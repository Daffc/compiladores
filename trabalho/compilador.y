
// [FAZER] Desalocar variáveis após o fim de procedimentos. 
// [FAZER] Receber entrada de dados (read -> LEIT). 
// [FAZER] Imprimir dados em saida (ESCR). 


%error-verbose          //Expressando melhor os Sytatic Errors.

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"


int nivel_lexico = 0,   /*Armazena o nível  nível léxico*/
    num_vars,           /* Armazena a quandtidade de variáveis para impressão de "AMEM num_vars */
    num_tipo_vars;             /* Armazena a quantidade de variáveis a terem sei tipo identificado. */

char    entrada_while[4],
        saida_while[4];
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

/* TOKEN WHILE*/
%token WHILE

/*!!!!!! NÃO UTILIZADOS !!!!!!!*/
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION GOTO IF THEN ELSE DO


/* DEFINIÇÃO PARA ESTADOS NÃO-TERMINAIS */
%type <v_sim> variavel
%type <texto> fator termo exp_simples expressao relacao

/* Aplicando precedência para IF THEN ELSE */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa:
        { geraCodigo (NULL, "INPP"); } PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  {geraCodigo (NULL, "PARA"); }
;

bloco: 
        parte_declara_vars parte_de_declaracao_de_subrotinas comando_composto
;


/*
    ------------------------------------------
    |   INICIO --- DECLARAÇÃO DE VARIAVEIS    |
    ------------------------------------------
*/

parte_declara_vars: 
        {num_vars = 0;} var { imprimeAMEM(&num_vars); }
    |   /* VAZIO */
;


var:   
        VAR declara_vars
;

declara_vars: 
        declara_vars declara_var 
    |   declara_var 
;

declara_var :   
        {num_tipo_vars = 0;} lista_id_var DOIS_PONTOS tipo  PONTO_E_VIRGULA
;

tipo: 
        IDENT
            {
                defineTipoVariavel(num_tipo_vars, token);    /* Definindo o tipo das "num_tipo_vars" variáveis para "token" */
            }

;

lista_id_var: 
        lista_id_var VIRGULA IDENT    
            { 

                strcpy(entrada_ts.identificador, token);    /* Resgata nome de variável. */
                entrada_ts.categoria = VariavelSimples;     /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;            /* Indica o nível lexico da VS atual */
                avs.tipo[1] = '\0';                         /* Define o tipo de variável como string vazia. */
                avs.deslocamento = num_vars;                /* Deslocamento da variável. */

                

                /* Adicionando Novo Simbolo a Tabela de Simbolos */
                insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);

                num_vars ++;       /* Incrementa 'deslocamento' par aproxima variável.*/
                num_tipo_vars ++;  /* Acrecentando a contagem de variáeis a serem tipadas.*/
            } 
    |   IDENT 
            { 
                
                strcpy(entrada_ts.identificador, token);    /* Resgata nome de variável. */
                entrada_ts.categoria = VariavelSimples;     /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;            /* Indica o nível lexico da VS atual */
                avs.tipo[1] = '\0';                         /* Define o tipo de variável como string vazia. */
                avs.deslocamento = num_vars;                /* Deslocamento da variável. */

                

                /* Adicionando Novo Simbolo a Tabela de Simbolos */
                insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);

                num_vars ++;       /* Incrementa 'deslocamento' par aproxima variável.*/
                num_tipo_vars ++;  /* Acrecentando a contagem de variáeis a serem tipadas.*/
            }
;

lista_idents: 
        lista_idents VIRGULA IDENT  
    |   IDENT 
;

/*
    ---------------------------------------
    |   FIM --- DECLARAÇÃO DE VARIAVEIS    |
    ---------------------------------------
*/

/*
    ------------------------------------------
    |   INICIO --- PROCEDIMENTOS/FUNÇÕES      |
    ------------------------------------------
*/


// LINHA 11
parte_de_declaracao_de_subrotinas:
        declaracao_de_procedimento PONTO_E_VIRGULA
    |   parte_de_declaracao_de_subrotinas declaracao_de_procedimento PONTO_E_VIRGULA
//    |   declaração de funcao PONTO_E_VIRGULA
//    |   parte_de_declaracao_de_subrotinas PONTO_E_VIRGULA declaração de funcao PONTO_E_VIRGULA
    |   /* VAZIO */
;

// LINHA 12
declaracao_de_procedimento:
        PROCEDURE IDENT ABRE_PARENTESES parametros_formais FECHA_PARENTESES PONTO_E_VIRGULA bloco
;

// LINHA 14
parametros_formais:
        secao_parametros_formais
    |   parametros_formais PONTO_E_VIRGULA secao_parametros_formais 
    |   /* VAZIO */
;


// LINHA 15
secao_parametros_formais:
        lista_idents DOIS_PONTOS IDENT
    |   VAR lista_idents DOIS_PONTOS IDENT
;

/*
    ------------------------------------------
    |   FIM --- PROCEDIMENTOS/FUNÇÕES         |
    ------------------------------------------
*/

comando_composto: 
        T_BEGIN comandos T_END 
;

comandos:   
        comando         
    |   comandos PONTO_E_VIRGULA comando
;

comando:
        comando_sem_rotulo 
    |   NUMERO DOIS_PONTOS comando_sem_rotulo
    |   /* VAZIO -> MAS PORQUE NÃO EXISTE EM DEFINIÇÃO? */
;


comando_sem_rotulo:   
        atribui
    |   chamada_procedimento
    |   comando_condicional
    |   comando_repetitivo      
    |   comando_composto              
; 

// LINHA 19
atribui :   
        variavel ATRIBUICAO expressao
            {
                /* Verificando se 'variavel' $1 e 'expressao' $3 possuem o mesmo tipo */
                validaTipos(nl, $1.tipo, $3);

                /* Defindo instrução MEPA para armazenamento em 'variavel' */
                armazenaVariavelSimplesMEPA($1.nivel, $1.deslocamento);
            }
;

// LINHA 20
chamada_procedimento:
        IDENT PONTO_E_VIRGULA
    |   IDENT ABRE_PARENTESES lista_de_espressoes FECHA_PARENTESES PONTO_E_VIRGULA;
;

// LINHA 22
comando_condicional: 
        if_then cond_else 
            {
                /* Desempilha Rótulo de saida de if OU if/else */
                desempilhaRotulo(saida_while);

                /* Imprime rótulo de saida em MEPA */
                geraCodigo(saida_while, "NADA");
            }
;
if_then     : 
        IF expressao 
            {
                /* Empilha Rótulo para onde deve-se dirigir quando condição IF for FALSA. */
                empilhaRotulo(saida_while);
                
                /* Imprime comando para saida de if caso 'expressao' seja falso (DSVF).*/
                imprimeDesviaSeFalsoMEPA(saida_while);
            }
        THEN comando_sem_rotulo
;

cond_else   : 
        ELSE 
            {
                /* Desemmpilha Rótulo para onde deve-se dirigir quando condição IF for FALSA. */
                desempilhaRotulo(entrada_while);
                /* Empilha Rótulo para onde deve-se dirigir ao final de 'comando_sem_rótulo' com IF VERDADEIRO */
                empilhaRotulo(saida_while);
                
                /* Imprime instrução MEPA de desvio incondicional (DSVS) ao final de 'comando_sem_rotulo' de IF*/
                imprimeDesviaSempre(saida_while);

                /* Imprime rótulo para onde deve-se dirigir quando expressão de IF é FALSA (equivalente ao ELSE). */
                geraCodigo(entrada_while, "NADA");
            }
        comando_sem_rotulo
    |   %prec LOWER_THAN_ELSE
;

// LINHA 23
comando_repetitivo  :   
        WHILE 
            {
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(entrada_while);

                /* Imprimendo rótulo de entrada do while em arquivo MEPA */
                geraCodigo(entrada_while, "NADA");
            } 
        expressao DO
            { 
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(saida_while);

                /* Imprime comando para saida de loop caso 'expressao' seja falsa.*/
                imprimeDesviaSeFalsoMEPA(saida_while);
            } 
        comando_sem_rotulo
            {
                
                desempilhaRotulo(saida_while);
                desempilhaRotulo(entrada_while);

                /* Imprime comando para retorno ao inícion do while */
                imprimeDesviaSempre(entrada_while);
                
                /* Imprimendo rótulo de saida do while em arquivo MEPA */
                geraCodigo(saida_while, "NADA");
            }
;

// LINHA 24
lista_de_espressoes:
        expressao
    |   lista_de_espressoes VIRGULA expressao
;

// LINHA 25
expressao:   
        exp_simples
            {
                /* Repassando tipo de 'exp_simples' ($1) para 'expressao'($$) */
                strcpy($$, $1);
            }

    |   exp_simples relacao exp_simples
            {
                /* Verificando tipos de $1 e $3 e repassando para 'expressao' */
                strcpy($$, validaTipos(nl,$1, $3));
                /* Imprime comando MEPA de relação  obtido por 'relacao' */
                geraCodigo(NULL, $2);
            }
;

//LINHA 26
relacao :   
        IGUAL
            {
                /* Imprime comando MEPA de '='. */
                strcpy($$, "CMIG");
            }
    |   DIFERENTE
            {
                /* Imprime comando MEPA de '<>'. */
                strcpy($$, "CMDG");
            }
    |   MENOR_QUE
            {
                /* Imprime comando MEPA de '<'. */
                strcpy($$, "CMME");
            }
    |   MAIOR_QUE
            {
                /* Imprime comando MEPA de '>'. */
                strcpy($$, "CMMA");
            }
    |   MENOR_OU_IGUAL
            {
                /* Imprime comando MEPA de '<='. */
                strcpy($$, "CMEG");
            }
    |   MAIOR_OU_IGUAL
            {
                /* Imprime comando MEPA de '>='. */
                strcpy($$, "CMAG");
            }
;

//LINHA 27
exp_simples :   
        termo
            {
                /* Repassando tipo de 'termo' ($1) para 'exp_simples'($$) */
                strcpy($$, $1);
            }
    |   SOMA  termo
            {
                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
                strcpy($$, $2);
            }
    |   SUBTRACAO termo
            {
                /* Imprime comando MEPA de INVERSÃO DE SINAL. */
                geraCodigo(NULL, "INVR");
                
                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
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

// LINHA 28
termo   :   
        fator 
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
fator   :   
        variavel
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
variavel:   
        IDENT
            {              
                /* Armazena em 'avs' atributos de 'token' após verificação por validaSimbolo(); */
                avs = *( (Atributos_VS *) validaSimbolo(nl, token));

                /* Populando 'variavel' com atributos recebidos de Tabela de Simbolos. */
                strcpy($$.token, token);
                strcpy($$.tipo, avs.tipo);
                $$.nivel = nivel_lexico;
                $$.deslocamento = avs.deslocamento;
            }
;


%%

int main (int argc, char** argv) {

    #ifdef YYDEBUG
        yydebug = 1;
    #endif

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
    iniciaTabelaSimbolos();
    iniciaPilhaRotulos();

    yyin=fp;
    yyparse();
    
    liberaTabelaSimbolos();

    return 0;
}