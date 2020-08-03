/* -------------------------------------------------------------------
 *            Arquivo: compilaodr.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, prot�tipos e vai�veis globais do compilador
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 16

typedef enum simbolos { 
  simb_program, simb_var, simb_begin, simb_end, 
  simb_identificador, simb_numero,
  simb_ponto, simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
  simb_atribuicao, simb_abre_parenteses, simb_fecha_parenteses,
  simb_label, simb_type, simb_array, simb_of, simb_procedure, 
  simb_function, simb_goto, simb_if, simb_then, simb_else, 
  simb_while, simb_do, simb_igual, simb_diferente, simb_menor_que, 
  simb_maior_que, simb_menor_ou_igual, simb_maior_ou_igual, 
  simb_subtracao, simb_soma, simb_or, simb_produto, simb_divisao, simb_and, simb_not
} simbolos;


/*	
	--------------------------------------
	| 	INICIO --- TABELA DE SIMBOLOS    |
	--------------------------------------
*/

/*
	Definindo categoria de simbolos.
*/
typedef enum categoria_simbolos_t{
	VariavelSimples,
	ParametroFormal,
	Procedimento
} CategoriaSimbolos;

/*
	Definindo entrada para atributos de cada categoria.
*/

typedef struct atributos_vs_t{
	char tipo[20];
	unsigned char deslocamento;
}Atributos_VS;

typedef struct atributos_pf_t{
	/*Completar posteriormente*/
}Atributos_PF;

typedef struct atributos_proc_t{
	/*Completar Posteriormente*/
}Atributos_PROC;


/* Definindo entrada de tabela de simbolos*/
typedef struct entrada_tabela_simbolos_t{
	char 				identificador[128];
	CategoriaSimbolos 	categoria;
	unsigned char 		nivel;
	void				*ponteiro_atributos;	
} EntradaTabelaSimbolos;


/*	Definindo estrutura para Tabela de simbolos.*/
typedef struct tabela_simbolos_t{
	int 					topo;
	int 					tamanho;
	EntradaTabelaSimbolos 	*entrada; 
} Tabela_Simbolos;

/*
	Declarando API de tabela de Simbolos.
*/

/* Empilha novo elemento na tabela de simbolos. */
void insereTabelaSimbolos(char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos);
/* Busca elemento na tabela de simbolos de acordo com o identificador informado.*/
void * buscaTabelaSimbolos(char* identificador);
/* Desempilha "quantidade" entradas da tabela de Simbolos. */
void retiraEntradasTabelaSimbolos(unsigned char quantidade);
/* Define para "quantidade" variáveis o tipo "tipo".*/
void defineTipoVariavel(unsigned char quantidade, char* tipo);

/*	Debug */
void mostraTabelaSimbolos();
void mostra_att_VS(Atributos_VS *ponteiro);
void mostra_att_PF(Atributos_PF *ponteiro);
void mostra_att_PROC(Atributos_PROC *ponteiro);

/*
    -----------------------------------
    |   FIM --- TABELA DE SIMBOLOS    |
    -----------------------------------
*/

/* -------------------------------------------------------------------
 * vari�veis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;


simbolos simbolo, relacao;
char token[TAM_TOKEN];

void geraCodigo (char* rot, char* comando);

/*
    -----------------------------------
    |   INICIO --- NOVAS FUNÇÕES      |
    -----------------------------------
*/

/*Recebe o número de variáveis em num_variaveis e imprime "AMEM num_variaveis" em MEPA*/
void imprimeAMEM (int *num_variaveis);

/*
	Verifica se "primeiro" e "segundo" São do mesmo tipo, retornando "primeiro" caso verdadeiro 
	e imprime mensagem de error e para execussão (exit(-1)) caso seja falso.
*/
char * validaTipos(int nivel, char *primeiro, char *segundo);

/*
	Verifica se "primeiro" e "segundo" São do mesmo tipo, retornando "primeiro" caso verdadeiro 
	e imprime mensagem de error e para execussão (exit(-1)) caso seja falso.
*/
void * validaSimbolo(char *simbolo);

