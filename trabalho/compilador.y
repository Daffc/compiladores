
// [FAZER] Receber entrada de dados (read -> LEIT). 
// [FAZER] Imprimir dados em saida (ESCR). 
// [ERRO] por algum motivo fluxo de 'chamada_procedimento' implica que, em 'atribui', ao verificar o tipo de 'variavel' utiliza-se o token de 'ATRIBUICAO'.  


%error-verbose          //Expressando melhor os Sytatic Errors.

%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"


int nivel_lexico = 0,   /*Armazena o nível  nível léxico*/
    num_vars = 0,           /* Armazena a quandtidade de variáveis para impressão de "AMEM num_vars */
    num_tipo_vars = 0;             /* Armazena a quantidade de variáveis a terem sei tipo identificado. */

char    entrada_rotulo[4],
        saida_rotulo[4];
/*  Armazena atributos de variável simples*/
Atributos_VS avs;

/*  Armazena atributos de parâmetro formal */
Atributos_PF apf;

/*  Armazena atributos de procedimento */
Atributos_PROC aproc;

/*  Auxilia na recuperação de Atributos */
void   *atributos;

/* Armazena o tipo de entrada para repasse ao lista_var por diferentes fontes. */
CategoriaSimbolos categoria_entrada_TS;

/* Auxilia em operções com entrada da tablea de simbolos. */
EntradaTabelaSimbolos entrada_ts;

/* Auxilia no controle de passagem de parâmetros. */
TipoPassagemParametro tipo_passagem;

/* Auxilia no controle dos escopos. */
EntradaEscopo entrada_escopo;

%}

%union{
    Variavel_Simples v_sim;
    char    texto[128];
    EntradaTabelaSimbolos entrada_ts;
    int numero;
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

/* TOKEN WHILE*/
%token WHILE

/*!!!!!! NÃO UTILIZADOS !!!!!!!*/
%token LABEL TYPE ARRAY OF PROCEDURE FUNCTION GOTO IF THEN ELSE DO


/* DEFINIÇÃO PARA ESTADOS NÃO-TERMINAIS */
%type <v_sim> variavel
%type <texto> fator termo exp_simples expressao relacao atribui identificador_comando
%type <numero> parte_de_declaracao_de_subrotinas


/* Aplicando precedência para IF THEN ELSE */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

programa:
        { geraCodigo (NULL, "INPP"); } PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  {geraCodigo (NULL, "PARA"); }
;

bloco:  
            {
                entrada_escopo.quantidade_parametros = num_vars;    // Armazena a quantidade de parâmetros pré calculada (antes da chamada de 'bloco').
                entrada_escopo.nivel_lexico = nivel_lexico;         // Armazena o nível léxico do escopo atual. 
                entrada_escopo.quantidade_procs = 0;                // Define a quantidade de funções/procedimentos do escopo atual como 0;
            }
        parte_declara_vars 
            {
                entrada_escopo.quantidade_vars = num_vars;          // Armazena a quantidade de variáveis locais do escopo atual.
                empilhaControleEscopo(entrada_escopo);              // Empilha escopo atual.

                nivel_lexico ++;    // Incrementa nível léxico para procedimentos/funções aninhados.                                

            } 
        parte_de_declaracao_de_subrotinas 
            {
                if($4){                                 // Verifica se algum procedimento foi definido.
                    desempilhaRotulo(saida_rotulo);     // Desempilha rótulo para pular definição de procedimentos.
                    geraCodigo(saida_rotulo, "NADA");   // Imprime rótulo destino para pulo de procedimentos.
                }
                
                nivel_lexico --; // Volta a nível léxico de escopo atual.
            } 
        comando_composto
            {
                entrada_escopo = desempilhaControleEscopo();                    // Desempilha entrada de controle escopo.
                imprimeDesalocaMemoria(entrada_escopo.quantidade_vars);         // Imprime comando MEPA DMEM n
                retiraEntradasTabelaSimbolos(entrada_escopo.quantidade_vars);   // Removendo Variáveis locais de TS.                                    

                // Verifica se escopo atual tem nível léxico > 0 (se não é a "raiz" do programa).
                if(entrada_escopo.nivel_lexico > 0){
                    imprimeRetornaProcedimento(entrada_escopo.nivel_lexico, entrada_escopo.quantidade_parametros);  // Imprime comando MEPA  "RPTR k,n".
                }

                retiraEntradasTabelaSimbolos(entrada_escopo.quantidade_parametros);     // Remove da TS os parâmetros.
                retiraEntradasTabelaSimbolos(entrada_escopo.quantidade_procs);          // Remove da TS os procedimentos aninhados.
            }
;


/*
    ------------------------------------------
    |   INICIO --- DECLARAÇÃO DE VARIAVEIS    |
    ------------------------------------------
*/

parte_declara_vars: 
        {
            num_vars = 0;
            categoria_entrada_TS = VariavelSimples;
        } 
            var 
        { imprimeAMEM(&num_vars); }
    |   /* VAZIO */
;


var:   
        VAR declara_vars
;

declara_vars: 
        declara_vars declara_var 
    |   declara_var 
;

declara_var:   
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

                strcpy(entrada_ts.identificador, token);        /* Resgata nome de variável. */
                entrada_ts.categoria = categoria_entrada_TS;    /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;                /* Indica o nível lexico da VS atual */
                
                if(categoria_entrada_TS == VariavelSimples){
                    avs.tipo[1] = '\0';                             /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = num_vars;                    /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);
                }
                if(categoria_entrada_TS == ParametroFormal){
                    apf.tipo[1] = '\0';                             /* Define o tipo de PF como string vazia. */
                    apf.deslocamento = num_vars;                    /* Deslocamento do PF. */
                    apf.tipo_passagem = tipo_passagem;              /* Define qual foi o tipo de passagem do PF */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &apf);
                }

                num_vars ++;       /* Incrementa 'deslocamento' par aproxima variável.*/
                num_tipo_vars ++;  /* Acrecentando a contagem de variáeis a serem tipadas.*/

            } 
    |   IDENT 
            { 
                
                strcpy(entrada_ts.identificador, token);        /* Resgata nome de variável. */
                entrada_ts.categoria = categoria_entrada_TS;     /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;                /* Indica o nível lexico da VS atual */

                if(categoria_entrada_TS == VariavelSimples){
                    avs.tipo[1] = '\0';                             /* Define o tipo de variável como string vazia. */
                    avs.deslocamento = num_vars;                    /* Deslocamento da variável. */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);
                }
                if(categoria_entrada_TS == ParametroFormal){
                    apf.tipo[1] = '\0';                             /* Define o tipo de PF como string vazia. */
                    apf.deslocamento = num_vars;                    /* Deslocamento do PF. */
                    apf.tipo_passagem = tipo_passagem;              /* Define qual foi o tipo de passagem do PF */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &apf);
                }


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
            {
                empilhaRotulo(entrada_rotulo);          // Empilhando Rótulo para código (comando composto da função de nível léxico atual.)
                imprimeDesviaSempre(entrada_rotulo);    // Definindo Desvio para esta código da função atual (pulando procedimentos declarados).
            }
        declaracao_de_procedimento PONTO_E_VIRGULA
            {
                $$ = 1;     // Informando a  'parte_de_declaracao_de_subrotinas' que um procedimento foi definido.             

                entrada_escopo = desempilhaControleEscopo(); 
                entrada_escopo.quantidade_procs ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();
            }
        
    |   parte_de_declaracao_de_subrotinas declaracao_de_procedimento PONTO_E_VIRGULA
            {
                $$ = 1;     // Informando a  'parte_de_declaracao_de_subrotinas' que um procedimento foi definido.  

                entrada_escopo = desempilhaControleEscopo(); 
                entrada_escopo.quantidade_procs ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();

            }

//    |   declaração de funcao PONTO_E_VIRGULA
//    |   parte_de_declaracao_de_subrotinas PONTO_E_VIRGULA declaração de funcao PONTO_E_VIRGULA
    |   /* VAZIO */     
            { 
                $$ = 0;  // Informando a  'parte_de_declaracao_de_subrotinas' que nenhuma função/procedimento foi definido.
            }
;

// LINHA 12
declaracao_de_procedimento:
        PROCEDURE IDENT 
            { 
                categoria_entrada_TS = Procedimento;

                strcpy(entrada_ts.identificador, token);        /* Resgata nome de variável. */
                entrada_ts.categoria = categoria_entrada_TS;    /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;                /* Indica o nível lexico da VS atual */
                
                empilhaRotulo(aproc.rotulo);                    /* Definindo e empilhando rótulo para procedimento. */

                /* [MELHORAR] Desvincular geração de rótulo com empilhamento .*/
                desempilhaRotulo(aproc.rotulo);                    /* Uma vez que o rótulo esteja na TDS, não é mais necessário empilha-lo*/


                imprimeEntraProcedimento(aproc.rotulo, nivel_lexico);   /* Imprime instrução MEPA de entrada para procedimento, indicando o nível lexico. */

                /* Adicionando Novo Simbolo a Tabela de Simbolos */
                insereTabelaSimbolos(entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &aproc);
            }
        ABRE_PARENTESES 
            { 
                    categoria_entrada_TS = ParametroFormal; /* A partir deste momendo, serão declarados Parâmetros fomais.  */
                    num_vars = 0;                           // Zeranvo variável para início da contagem de parâmetros.        
            }
        parametros_formais 
            {
                deslocaParametrosFormais(num_vars); // Redefine valor de deslocamento para parâmetros para condizer com edereço de execussão.
                preencheAtributosProcedimento(num_vars);    // Preenchendo sessão de parâmetros em entrada de procedimento em TS.
            }
        FECHA_PARENTESES PONTO_E_VIRGULA bloco
;

// LINHA 14
parametros_formais:
        secao_parametros_formais
    |   parametros_formais PONTO_E_VIRGULA secao_parametros_formais 
    |   /* VAZIO */
;


// LINHA 15
secao_parametros_formais:
            {
                num_tipo_vars = 0;      //Zerando contador de parâmetros por tipo.
                tipo_passagem = valor;  //Definindo o tipo de passagem dos parâmetros.
            } 
        lista_id_var DOIS_PONTOS IDENT 
            {
                defineTipoParametroFormal(num_tipo_vars, token, tipo_passagem); // Definindo o tipo dos parâmetros de acordocom o IDENT.
            }
    |       
            {
                num_tipo_vars = 0;      //Zerando contador de parâmetros por tipo.
                tipo_passagem = referencia;  //Definindo o tipo de passagem dos parâmetros.
            } 
        VAR lista_id_var DOIS_PONTOS IDENT 
            {
                defineTipoParametroFormal(num_tipo_vars, token, tipo_passagem);  // Definindo o tipo dos parâmetros de acordocom o IDENT.
            }
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
        IDENT 
            {
                // Armazena token de entrada do simbolo 'token' em $1.
                $1 = * validaSimbolo(nl, token);

            } 
        identificador_comando
            {
                // Caso IDENT sejá uma 'VariavelSimples'
                if ($1.categoria == VariavelSimples)
                // Caso 'identificador_comando' retorne de uma atribuição
                if($3[0] != '\0'){

                    /* Armazena em 'avs' atributos de entrada de 'IDENT'*/
                    avs = *( (Atributos_VS *) $1.ponteiro_atributos);

                    /* Verificando se 'IDENT' e 'identificador_comando' $3 possuem o mesmo tipo */
                    validaTipos(nl, avs.tipo, $3);

                    /* Defindo instrução MEPA para armazenamento em 'variavel' */
                    armazenaVariavelSimplesMEPA($1.nivel, avs.deslocamento);
                }

            }
    |   comando_condicional
    |   comando_repetitivo      
    |   comando_composto              
; 

// Necessário Fatoração em comandos de atribuição e chamada de procedimento.
identificador_comando:
        atribui
            {
                /* Repassando tipo de 'atribui' ($1) para 'identificador_comando'($$) */
                strcpy($$, $1);
            }
    |   chamada_procedimento
            {
                /* Repassando tipo de 'atribui' ($1) para 'identificador_comando'($$) */
                $$[0] = '\0';
            }
    ;

// LINHA 19
atribui:   
        ATRIBUICAO expressao
            {
                /* Repassando tipo de 'expressao' ($2) para 'atribui'($$) */
                strcpy($$, $2);
            }
;

// LINHA 20
chamada_procedimento:
    |   ABRE_PARENTESES lista_de_espressoes FECHA_PARENTESES
;

// LINHA 22
comando_condicional: 
        if_then cond_else 
            {
                /* Desempilha Rótulo de saida de if OU if/else */
                desempilhaRotulo(saida_rotulo);

                /* Imprime rótulo de saida em MEPA */
                geraCodigo(saida_rotulo, "NADA");
            }
;
if_then     : 
        IF expressao 
            {
                /* Empilha Rótulo para onde deve-se dirigir quando condição IF for FALSA. */
                empilhaRotulo(saida_rotulo);
                
                /* Imprime comando para saida de if caso 'expressao' seja falso (DSVF).*/
                imprimeDesviaSeFalsoMEPA(saida_rotulo);
            }
        THEN comando_sem_rotulo
;

cond_else   : 
        ELSE 
            {
                /* Desemmpilha Rótulo para onde deve-se dirigir quando condição IF for FALSA. */
                desempilhaRotulo(entrada_rotulo);
                /* Empilha Rótulo para onde deve-se dirigir ao final de 'comando_sem_rótulo' com IF VERDADEIRO */
                empilhaRotulo(saida_rotulo);
                
                /* Imprime instrução MEPA de desvio incondicional (DSVS) ao final de 'comando_sem_rotulo' de IF*/
                imprimeDesviaSempre(saida_rotulo);

                /* Imprime rótulo para onde deve-se dirigir quando expressão de IF é FALSA (equivalente ao ELSE). */
                geraCodigo(entrada_rotulo, "NADA");
            }
        comando_sem_rotulo
    |   %prec LOWER_THAN_ELSE
;

// LINHA 23
comando_repetitivo  :   
        WHILE 
            {
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(entrada_rotulo);

                /* Imprimendo rótulo de entrada do while em arquivo MEPA */
                geraCodigo(entrada_rotulo, "NADA");
            } 
        expressao DO
            { 
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(saida_rotulo);

                /* Imprime comando para saida de loop caso 'expressao' seja falsa.*/
                imprimeDesviaSeFalsoMEPA(saida_rotulo);
            } 
        comando_sem_rotulo
            {
                
                desempilhaRotulo(saida_rotulo);
                desempilhaRotulo(entrada_rotulo);

                /* Imprime comando para retorno ao inícion do while */
                imprimeDesviaSempre(entrada_rotulo);
                
                /* Imprimendo rótulo de saida do while em arquivo MEPA */
                geraCodigo(saida_rotulo, "NADA");
            }
;

// LINHA 24
lista_de_espressoes:
        lista_de_espressoes VIRGULA expressao
    |   expressao
    |   // VAZIO
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
exp_simples:   
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

                carregaVariavelSimplesMEPA(nivel_lexico, $1.deslocamento);
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
                avs = *( (Atributos_VS *) validaSimbolo(nl, token)->ponteiro_atributos);

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
    iniciaPilhaControleEscopo();

    yyin=fp;
    yyparse();
    
    liberaTabelaSimbolos();

    return 0;
}