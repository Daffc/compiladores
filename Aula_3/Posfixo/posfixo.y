
%{
#include <stdio.h>
%}

%token IDENT_A MAIS MENOS ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES IDENT_B OR AND

%%
// ESTÁGIO INICIAL QUE DECIDIRA SE EXPRESSÃO SE REFERE A INTEIROS (expr_a) OU A BOOLEANOS (expr_b).

start		 : expr_a|
			 expr_b

// RAMO GRAMATICAL PARA INTEIROS.

expr_a       : expr_a MAIS termo_a {printf ("+"); } |
             expr_a MENOS termo_a {printf ("-"); } | 
             termo_a
;

termo_a      : termo_a ASTERISCO fator_a  {printf ("*"); }| 
             termo_a DIV fator_a  {printf ("/"); }|
             fator_a
;

fator_a      : IDENT_A {printf ("A"); }
;

// RAMO GRAMATICAL PARA BOOLEANOS.

expr_b		: expr_b OR termo_b {printf ("∪");} |
			termo_b
;
termo_b		: termo_b AND fator_b {printf("∩");}|
			fator_b
;
fator_b		: IDENT_B {printf("B");}
;
%%

main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

