
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
    num_vars = 0,       /* Armazena a quandtidade de variáveis para impressão de "AMEM num_vars */
    num_tipo_vars = 0,  /* Armazena a quantidade de variáveis a terem sei tipo identificado. */
    num_parametros = 0, // Armazena a quantidade de parâmetro recebidos por uma chamada de função.
    flag_PF_ref = 0;    // Informa se encontra-se em análise de passagem de parâmetro por referância.

char    entrada_rotulo[4],
        saida_rotulo[4];
/*  Armazena atributos de variável simples*/
Atributos_VS avs;

/*  Armazena atributos de parâmetro formal */
Atributos_PF apf;

/*  Armazena atributos de procedimento */
Atributos_SUBR aproc;

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
    char    texto[128];
    EntradaTabelaSimbolos entrada_ts;
    int numero;
    EntradaParametros   vetor_parametros[20];
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
%type <texto> fator termo exp_simples expressao relacao atribui define_terminal
%type <numero> parte_de_declaracao_de_subrotinas
%type <vetor_parametros> lista_de_espressoes
%type <entrada_ts> identificador_comando
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
                entrada_escopo.quantidade_subr = 0;                // Define a quantidade de funções/procedimentos do escopo atual como 0;
                num_vars = 0;                                       // Zerando a quantidade de variáveis ates de entrar em 'parte_declara_vars'
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
                retiraEntradasTabelaSimbolos(entrada_escopo.quantidade_subr);          // Remove da TS os procedimentos aninhados.
            }
;


/*
    ------------------------------------------
    |   INICIO --- DECLARAÇÃO DE VARIAVEIS    |
    ------------------------------------------
*/

parte_declara_vars: 
        {
            categoria_entrada_TS = VariavelSimples;
        } 
            var 
        { imprimeAMEM(num_vars); }
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
                    insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);
                }
                if(categoria_entrada_TS == ParametroFormal){
                    apf.tipo[1] = '\0';                             /* Define o tipo de PF como string vazia. */
                    apf.deslocamento = num_vars;                    /* Deslocamento do PF. */
                    apf.tipo_passagem = tipo_passagem;              /* Define qual foi o tipo de passagem do PF */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &apf);
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
                    insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &avs);
                }
                if(categoria_entrada_TS == ParametroFormal){
                    apf.tipo[1] = '\0';                             /* Define o tipo de PF como string vazia. */
                    apf.deslocamento = num_vars;                    /* Deslocamento do PF. */
                    apf.tipo_passagem = tipo_passagem;              /* Define qual foi o tipo de passagem do PF */

                    /* Adicionando Novo Simbolo a Tabela de Simbolos */
                    insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &apf);
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
                entrada_escopo.quantidade_subr ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();
            }
        
    |   parte_de_declaracao_de_subrotinas declaracao_de_procedimento PONTO_E_VIRGULA
            {
                $$ = 1;     // Informando a  'parte_de_declaracao_de_subrotinas' que um procedimento foi definido.  

                entrada_escopo = desempilhaControleEscopo(); 
                entrada_escopo.quantidade_subr ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();

            }

    |   
            {
                empilhaRotulo(entrada_rotulo);          // Empilhando Rótulo para código (comando composto da função de nível léxico atual.)
                imprimeDesviaSempre(entrada_rotulo);    // Definindo Desvio para esta código da função atual (pulando procedimentos declarados).
            }
        declaracao_de_funcao PONTO_E_VIRGULA
            {
                $$ = 1;     // Informando a  'parte_de_declaracao_de_subrotinas' que um procedimento foi definido.             

                entrada_escopo = desempilhaControleEscopo(); 
                entrada_escopo.quantidade_subr ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();
            }
    |   parte_de_declaracao_de_subrotinas declaracao_de_funcao PONTO_E_VIRGULA
            {
                $$ = 1;     // Informando a  'parte_de_declaracao_de_subrotinas' que um procedimento foi definido.  

                entrada_escopo = desempilhaControleEscopo(); 
                entrada_escopo.quantidade_subr ++;
                empilhaControleEscopo(entrada_escopo);
                // mostraPilhaControleEscopo();

            }
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
                insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &aproc);
                
                // Armazena em variavel de entrada de escopo o identificador do procedimento.
                strcpy(entrada_escopo.identificador, token);
            }
        ABRE_PARENTESES 
            { 
                    categoria_entrada_TS = ParametroFormal; /* A partir deste momendo, serão declarados Parâmetros fomais.  */
                    num_vars = 0;                           // Zeranvo variável para início da contagem de parâmetros.        
            }
        parametros_formais 
            {
                deslocaParametrosFormais(num_vars, Procedimento); // Redefine valor de deslocamento para parâmetros para condizer com edereço de execussão.
                preencheAtributosSubrotina(num_vars, NULL);    // Preenchendo sessão de parâmetros em entrada de procedimento em TS.
            }
        FECHA_PARENTESES PONTO_E_VIRGULA bloco
;

// LINHA 13
declaracao_de_funcao:
        FUNCTION IDENT 
            { 
                categoria_entrada_TS = Funcao;

                strcpy(entrada_ts.identificador, token);        /* Resgata nome de variável. */
                entrada_ts.categoria = categoria_entrada_TS;    /* Definindo Categoria de entrada. */
                entrada_ts.nivel = nivel_lexico;                /* Indica o nível lexico da VS atual */

                
                empilhaRotulo(aproc.rotulo);                    /* Definindo e empilhando rótulo para procedimento. */

                /* [MELHORAR] Desvincular geração de rótulo com empilhamento .*/
                desempilhaRotulo(aproc.rotulo);                 /* Uma vez que o rótulo esteja na TDS, não é mais necessário empilha-lo*/

                /* Adicionando Novo Simbolo a Tabela de Simbolos */
                insereTabelaSimbolos(nl, entrada_ts.identificador, entrada_ts.categoria, entrada_ts.nivel, &aproc);

                //Imprime instrução MEPA de entrada para procedimento, indicando o nível lexico.
                imprimeEntraProcedimento(aproc.rotulo, nivel_lexico);   

                // Armazena em variavel de entrada de escopo o identificador do procedimento.
                strcpy(entrada_escopo.identificador, token);
            }
        ABRE_PARENTESES 
            { 
                    categoria_entrada_TS = ParametroFormal; /* A partir deste momendo, serão declarados Parâmetros fomais.  */
                    num_vars = 0;                           // Zeranvo variável para início da contagem de parâmetros.        
            }
        parametros_formais 
            {
                deslocaParametrosFormais(num_vars, Funcao);         // Redefine valor de deslocamento para parâmetros para condizer com edereço de execussão.
            }
        FECHA_PARENTESES DOIS_PONTOS IDENT 
            {
                // Preenchendo sessão de parâmetros em entrada de procedimento e armazenando tipo de retorno da função.
                preencheAtributosSubrotina(num_vars, token); 
            }
        PONTO_E_VIRGULA bloco
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
                $1 = *validaSimbolo(nl, token);
            } 
        identificador_comando
    |   comando_condicional
    |   comando_repetitivo      
    |   comando_composto              
; 

// Necessário Fatoração em comandos de atribuição e chamada de procedimento.
identificador_comando:
        atribui
            {
                // Resgatando entrada de Tabela de Simbolos de IDENT em comando_sem_rotulo.
                $$ = $<entrada_ts>-1;
                
                switch($$.categoria){
                    // Caso IDENT sejá uma 'VariavelSimples'
                    case VariavelSimples:
                        /* Armazena em 'avs' atributos de entrada de 'IDENT'*/
                        avs = *( (Atributos_VS *) $$.ponteiro_atributos);

                        /* Verificando se 'IDENT' e 'atribui' $1 possuem o mesmo tipo */
                        validaTipos(nl, avs.tipo, $1);

                        /* Defindo instrução MEPA para armazenamento em 'variavel' */
                        armazenaVariavelSimplesMEPA($$.nivel, avs.deslocamento);
                    break;

                    // Caso IDENT sejá uma 'ParametroFormal'
                    case ParametroFormal:
                        /* Armazena em 'avs' atributos de entrada de 'IDENT'*/
                        apf = *( (Atributos_PF *) $$.ponteiro_atributos);

                        /* Verificando se 'IDENT' e 'atribui' $1 possuem o mesmo tipo */
                        validaTipos(nl, apf.tipo, $1);


                        if(apf.tipo_passagem == valor){
                            /* Defindo instrução MEPA para armazenamento em 'variavel' */
                            armazenaVariavelSimplesMEPA($$.nivel, apf.deslocamento);
                        }
                        else{
                            // Retorna Código MEPA de carregamento da variável.
                            armazenaVariavelIndiretaMEPA(nivel_lexico, apf.deslocamento);
                        }
                    break;

                    // Caso IDENT sejá uma 'Funcao', definir o retorno.
                    case Funcao:
                        // Verifica valor esta sendo atribuido enquanto dentro de função (ou seja, nivel léxico de função == nivel léxico atual).
                        validaNivelLexico(nl, $$.nivel, nivel_lexico);

                        /* Armazena em 'avs' atributos de entrada de 'IDENT'*/
                        aproc = *( (Atributos_SUBR *) $$.ponteiro_atributos);

                        /* Verificando se 'IDENT' e 'atribui' $1 possuem o mesmo tipo */
                        validaTipos(nl, aproc.tipo_retorno, $1);

                        /* Defindo instrução MEPA para armazenamento em retorno de funcao. */
                        armazenaVariavelSimplesMEPA($$.nivel, aproc.deslocamento);

                    break;

                    default:
                        erroAtribuiSimbolo(nl, $$.identificador);
                }
            }
    |   chamada_subrotina
            {
                // Resgatando entrada de Tabela de Simbolos de IDENT em comando_sem_rotulo.
                $$ = $<entrada_ts>-1;

                /* Armazena em 'aproc' atributos de entrada de 'IDENT'*/
                aproc = *( (Atributos_SUBR *) $$.ponteiro_atributos);

                // Verifica se quantidade de parâmetros da chamada é compatível com cabeçalho.
                validaNumParametros(nl, num_parametros, aproc.quantidade_parametros);

                // Imprime instrução MEPA de achamada de procedimento.
                imprimeChamaProcedimento(aproc.rotulo, nivel_lexico);
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
chamada_subrotina:
    ABRE_PARENTESES 
        {
            // Zera contador de parâmetros.
            num_parametros = 0;
        }
    lista_de_espressoes FECHA_PARENTESES
        {
            // Indica que não precisa se preocupar com referências
            // [FAZER] Efetuar o mesmo processo para funções !!!.
            flag_PF_ref = 0;
        }
    // | // VAZIO -> entra em conflito com definição de variavel. como concertar????
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
        lista_de_espressoes VIRGULA
            {
                // Recupeando tipo de passagem de parametro atual de'lista_de_expressoes'
                flag_PF_ref = $1[num_parametros].tipo_passagem;
            }
        expressao
            {               
                // Verifica se os tipos dos parâmetros são compatíveis com os do cabeçalho.
                validaParametro(nl, $$[num_parametros].tipo, $4, num_parametros);
                
                // Adiciona novo parâmetro a contador de parâmetros.
                num_parametros ++; 
            }
    |   
            {
                // Atributos de entrada de procedimento em Tabela de Simbolos.
                memcpy(&$<vetor_parametros>$, ((Atributos_SUBR *)($<entrada_ts>-3.ponteiro_atributos))->entradas_parametros, 20 * sizeof(EntradaParametros));
                // Caso armazena tipo de passagem de parâmetro atual.
                flag_PF_ref = $<vetor_parametros>$[num_parametros].tipo_passagem;
            }
        expressao
            {
                // Adiciona novo parâmetro a contador de parâmetros.
                
                // Verifica se os tipos dos parâmetros são compatíveis com os do cabeçalho.
                validaParametro(nl, $$[num_parametros].tipo, $2, num_parametros);
                
                // Adiciona novo parâmetro a contador de parâmetros.
                num_parametros ++; 
            }
    |   // VAZIO
            {
                // Evitar warnings (retorno dummy).
                $<vetor_parametros>$[num_parametros].tipo[0] = '\0';   
            }
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
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);
                
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
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
                strcpy($$, $2);
            }
    |   SUBTRACAO termo
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Imprime comando MEPA de INVERSÃO DE SINAL. */
                geraCodigo(NULL, "INVR");
                
                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
                strcpy($$, $2);
            }
    |   exp_simples SOMA termo
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                strcpy($$, validaTipos(nl,$1, $3));

                /* Imprime comando MEPA de SOMA. */
                geraCodigo(NULL, "SOMA");
            }
    |   exp_simples SUBTRACAO termo
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                strcpy($$, validaTipos(nl,$1, $3));

                /* Imprime comando MEPA de SUBTRAÇÃO. */
                geraCodigo(NULL, "SUBT");
            }
    |   exp_simples OR termo
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

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
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy($$, validaTipos(nl,$1, $3));

                /* Imprime comando MEPA de MULTIPLICAÇÃO. */
                geraCodigo(NULL, "MULT");

            }
    |   termo DIVISAO fator
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy($$, validaTipos(nl,$1, $3));
                
                /* Imprime comando MEPA de DIVISÃO. */
                geraCodigo(NULL, "DIVI");
            }
    |   termo AND fator
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy($$, validaTipos(nl,$1, $3));

                /* Imprime comando MEPA de CONJUNÇÃO. */
                geraCodigo(NULL, "CONJ");
            }
; 
              
// LINHA 29
fator:   
        //  [FAZER] fatorar variavel para receber function (mesma maneira que em atribui).
        IDENT 
            {
                // Armazena token de entrada do simbolo 'token' em $1.
                $1 = *validaSimbolo(nl, token);

                // Verifica se tipo de identificar é de função.
                if($1.categoria == Funcao){
                    // Reserva espaço para retorno de função em tempo de execussao.
                    imprimeAMEM(1);
                }
            }
        define_terminal
            {
                /* Repassando tipo de 'define_terminal' ($3) para 'fator'($$) */
                strcpy($$, $3);
            }
    |   NUMERO
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Definindo tipo de 'fator' para 'integer'. */
                strcpy($$, "integer");

                /* Imprime comando MEPA de definição de constante. */
                carregaConstanteMEPA(token);
            }
    |   ABRE_PARENTESES expressao FECHA_PARENTESES
            {
                /* Repassando tipo de 'expressao' ($2) para 'fator'($$) */
                strcpy($$, $2);
            }
    |   NOT fator
            {
                /* Verificando se análise chamada de função com passagem por referência.*/
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Repassando tipo de  $2 para $$ */
                strcpy($$, $2);

                /* Imprime comando MEPA de negação. */
                geraCodigo(NULL, "NEGA");
            }
;

// LINHAS 30 e 31
define_terminal:  
        chamada_subrotina
            {
                // Resgatando entrada de Tabela de Simbolos de IDENT em comando_sem_rotulo.
                entrada_ts = $<entrada_ts>-1;

                //[FAZER] Verificar se 'entrada_ts' é do tipo Funcao, caso contrário retornar erro.
                
                verificaProcedenciaReferencia(nl, flag_PF_ref);

                /* Armazena em 'aproc' atributos de entrada de 'IDENT'*/
                aproc = *( (Atributos_SUBR *) entrada_ts.ponteiro_atributos);

                // Verifica se quantidade de parâmetros da chamada é compatível com cabeçalho.
                validaNumParametros(nl, num_parametros, aproc.quantidade_parametros);

                // Imprime instrução MEPA de achamada de procedimento.
                imprimeChamaProcedimento(aproc.rotulo, nivel_lexico);

                // Retornando em 'define_terminal' o tipo de retorno da funçao identificad variável de 'IDENT' ($<entrada_ts>-1).
                strcpy($$, avs.tipo);
            }
    |    // VAZIO -> Caso termo em quetão se refira a uma variavel em uma expressão.
            {     
                /* Armazena em 'avs' atributos de 'IDENT'; */
                avs = *( (Atributos_VS *) $<entrada_ts>-1.ponteiro_atributos);

                // Caso IDENT sejá uma 'VariavelSimples'
                if ($<entrada_ts>-1.categoria == VariavelSimples)
                {
                    // Verifica se encontra-se em avaliação de parâmetro por referência.
                    if(flag_PF_ref){
                        // Retorna Código MEPA de carregamento da variável.
                        carregaReferenciaVariavelMEPA(nivel_lexico, avs.deslocamento);
                    }
                    else{                        
                        // Retorna Código MEPA de carregamento da variável.
                        carregaValorMEPA(nivel_lexico, avs.deslocamento);
                    }
                    
                    // Retornando em 'variavel' o tipo de variável de 'token'.
                    strcpy($$, avs.tipo);
                }

                // Caso IDENT sejá uma 'ParametroFormal'
                if ($<entrada_ts>-1.categoria == ParametroFormal)
                {

                    /* Armazena em 'avs' atributos de entrada de 'IDENT'*/
                    apf = *( (Atributos_PF *) $<entrada_ts>-1.ponteiro_atributos); 

                    // Verifica se encontra-se em avaliação de parâmetro por referência.
                    if(flag_PF_ref){

                        if(apf.tipo_passagem == valor){
                            // Retorna Código MEPA de carregamento da variável.
                            carregaReferenciaVariavelMEPA(nivel_lexico, avs.deslocamento);
                        }
                        else{
                            // Retorna Código MEPA de carregamento da variável.
                            carregaValorMEPA(nivel_lexico, apf.deslocamento);
                        }
                    }
                    else{                        
                        if(apf.tipo_passagem == valor){
                            // Retorna Código MEPA de carregamento da variável.
                            carregaValorMEPA(nivel_lexico, apf.deslocamento);
                        }
                        else{
                            // Retorna Código MEPA de carregamento da variável.
                            carregaVariavelIndiretoMEPA(nivel_lexico, apf.deslocamento);
                        }
                    }                   

                    // Retornando em 'define_terminal' o tipo de variável de 'token'.
                    strcpy($$, apf.tipo);
                }
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