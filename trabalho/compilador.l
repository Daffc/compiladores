%{


#include<stdio.h>
#include<string.h>

#include "compilador.h"
#include "compilador.tab.h"

//#define IMPRIME(STR) {};
#define IMPRIME(STR) printf("%s    # %s \n", STR, token);

int nl = 1;  

%}

pulo_linha [\n]

descarte [\t ]+

ident [a-zA-Z_][a-zA-Z0-9_]*

numero [0-9]+

comentario "(*".*"*)"

%%

{pulo_linha} {nl++;} 

{descarte}

{comentario}

program { simbolo  = simb_program;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("program ");
          return PROGRAM;
 }

var      { simbolo = simb_var;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("var  ");
          return VAR;
 }

begin { simbolo = simb_begin;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("begin ");
          return T_BEGIN;
 }

end { simbolo = simb_end;
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME("end  ");
          return T_END;
 }

:= { simbolo = simb_atribuicao;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" atribuicao  ");
          return ATRIBUICAO;  
 }

\; { simbolo = simb_ponto_e_virgula;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" pt_virgula  ");
          return PONTO_E_VIRGULA;
 }

\: { simbolo = simb_dois_pontos;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" dois pontos ");
          return DOIS_PONTOS;
 }

\, { simbolo = simb_virgula;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" virgula  ");
          return VIRGULA;
 }


\. { simbolo = simb_ponto;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" ponto  ");
          return PONTO; 
    }

\(  { simbolo = simb_abre_parenteses;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" abre_parenteses  ");
          return ABRE_PARENTESES;
    }

\)  { simbolo = simb_fecha_parenteses;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" fecha_parenteses ");
          return FECHA_PARENTESES;
 }

 /*====================== Minhas Modificações ======================*/
    /* PALAVRAS RESERVADAS */
label { simbolo  = simb_label;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" label ");
        return LABEL;
    }

type { simbolo  = simb_type;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" type ");
        return TYPE;
    }

array { simbolo  = simb_array;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" array ");
        return ARRAY;
    }

of { simbolo  = simb_of;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" of ");
        return OF;
    }

procedure { simbolo  = simb_procedure;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" procedure ");
        return PROCEDURE;
    }

function { simbolo  = simb_function;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" function ");
        return FUNCTION;
    }

goto { simbolo  = simb_goto;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" goto ");
        return GOTO;
    }

if { simbolo  = simb_if;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" if ");
        return IF;
    }

then { simbolo  = simb_then;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" then ");
        return THEN;
    }

else { simbolo  = simb_else;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" else ");
        return ELSE;
    }

while { simbolo  = simb_while;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" while ");
        return WHILE;
    }

do { simbolo  = simb_do;  
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" do ");
        return DO;
    }

read { simbolo = simb_read;
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" read ");
        return READ;
    }

write { simbolo = simb_write;
        strncpy (token, yytext, TAM_TOKEN);
        IMPRIME(" write ");
        return WRITE;
    }

    /* OPERADORES DE EXPRESSÕES */
\=  { simbolo = simb_igual;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" igual ");
          return IGUAL;
    }
\<>  { simbolo = simb_diferente;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" diferente ");
          return DIFERENTE;
    }

\<  { simbolo = simb_menor_que;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" menor_que ");
          return MENOR_QUE;
    }

\>  { simbolo = simb_maior_que;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" maior_que ");
          return MAIOR_QUE;
    }

\<=  { simbolo = simb_menor_ou_igual;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" menor_ou_igual ");
          return MENOR_OU_IGUAL;
    }

>=  { simbolo = simb_maior_ou_igual;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" maior_ou_igual ");
          return MAIOR_OU_IGUAL;
    }

\-  { simbolo = simb_subtracao;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" subtracao ");
          return SUBTRACAO;
    }

\+  { simbolo = simb_soma;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" soma ");
          return SOMA;
    }

or  { simbolo = simb_or;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" or ");
          return OR;
    }

\*  { simbolo = simb_produto;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" produto ");
          return PRODUTO;
    }

div  { simbolo = simb_divisao;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" divisao ");
          return DIVISAO;
    }

and  { simbolo = simb_and;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" and ");
          return AND;
    }

not  { simbolo = simb_not;  
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" not ");
          return NOT;
    }

 /*====================== Fim das minhas modificações ======================*/

{numero} { simbolo = simb_numero; 
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" numero  ");
          return NUMERO;
        }

{ident} { simbolo = simb_identificador; 
          strncpy (token, yytext, TAM_TOKEN);
          IMPRIME(" ident  ");
          return IDENT;
        }


%%

