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
	variavel_simples,
	parametro_formal,
	procedimento
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

