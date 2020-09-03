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
#define MAX_ROTULOS 20
#define MAX_PARAMETROS 20
#define MAX_ESCOPO 20

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


typedef enum tipo_passagem_parametro_t{
	valor,
	referencia
} TipoPassagemParametro;


typedef struct entrada_parametros{
	char tipo[20];
	TipoPassagemParametro tipo_passagem;
}EntradaParametros;

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
	Procedimento,
	Funcao
} CategoriaSimbolos;

/*
	Definindo entrada para atributos de cada categoria.
*/

typedef struct atributos_vs_t{
	char tipo[20];
	unsigned char deslocamento;
}Atributos_VS;

typedef struct atributos_pf_t{
	char tipo[20];
	char deslocamento;
	TipoPassagemParametro tipo_passagem;
}Atributos_PF;

typedef struct atributos_subr_t{
	char rotulo[4];
	int quantidade_parametros;
	char tipo_retorno[20];
	int deslocamento;
	EntradaParametros entradas_parametros[MAX_PARAMETROS];		// [FAZER] tornar dinâmico caso haja tempo.
}Atributos_SUBR;


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

/* Define valores para Tabela de Simbolos vazia. */
void iniciaTabelaSimbolos();
/* Empilha novo elemento na tabela de simbolos. */
void insereTabelaSimbolos(int linha, char* identificador, CategoriaSimbolos categoria, unsigned char nivel, void *atributos);
/* Busca elemento na tabela de simbolos de acordo com o identificador informado.*/
EntradaTabelaSimbolos* buscaTabelaSimbolos(char* identificador);
/* Desempilha "quantidade" entradas da tabela de Simbolos. */
void retiraEntradasTabelaSimbolos(unsigned char quantidade);
/* Define para "quantidade" variáveis o tipo "tipo".*/
void defineTipoVariavel(unsigned char quantidade, char* tipo);

/*	Definindo o "tipo" para todas as "quantidade" variáveis a partir do topo	*/
void defineTipoParametroFormal(unsigned char quantidade, char* tipo, TipoPassagemParametro tipo_passagem);

/* Define deslocamento de 'quantidade' parâmetros formais. */
void deslocaParametrosFormais(unsigned char quantidade, CategoriaSimbolos tipo_chamada);

/* Preenche parte de parâmetros em entrada de Procedimento em TS. */
void preencheAtributosSubrotina(int quantidade, char * tipo_retorno);

/* Libera Memória Alocada por Tablea de Simbolos*/
void liberaTabelaSimbolos();

/*	Debug */
void mostraTabelaSimbolos();
void mostra_att_VS(Atributos_VS *ponteiro);
void mostra_att_PF(Atributos_PF *ponteiro);
void mostra_att_PROC(Atributos_SUBR *ponteiro);
void mostraPilhaControleEscopo();

/*
    -----------------------------------
    |   FIM --- TABELA DE SIMBOLOS    |
    -----------------------------------
*/

/*	
	--------------------------------------------
	| 	INICIO --- PILHA DE CONTROLE ESCOPO    |
	--------------------------------------------
*/

// Estrutura para controle de entadas e aplicação de DMEM em table de simbolos.
typedef struct entrada_escopo_t{
	int 	nivel_lexico;
	int 	quantidade_vars;		// Armazena quantidae de variáveis por escopo.
	int 	quantidade_subr;		// Armazena quantidade de procedimentos por escopo.
	int		quantidade_parametros;	// Armazena quantidade de parâmetros por escopo.
	char 	identificador[128];		// Armazena o identificador do escopo (mesmo da tabela de simbolos no caso de subrotinas.)
}EntradaEscopo;


// Estrutura para controle de entadas e aplicação de DMEM em table de simbolos.
typedef struct controle_escopo_t{
	int topo;
	EntradaEscopo entradas_escopo[MAX_ESCOPO];	// Armazena quantidae de variáveis por escopo.
}ControleEscopo;


/* Inicia  a pilha de controle de escopos.  */
void iniciaPilhaControleEscopo();

/* Empilha 'entrada' de escopo. */
EntradaEscopo empilhaControleEscopo( EntradaEscopo entrada);

/* Desempilha 'entrada' de escopo. */
EntradaEscopo desempilhaControleEscopo();
/*
    -----------------------------------------
    |   FIM --- PILHA DE CONTROLE ESCOPO    |
    -----------------------------------------
*/


/*	
	------------------------------------
	| 	INICIO --- PILHA DE ROTULOS    |
	------------------------------------
*/

/*	Definindo estrutura para Pilha de Rotulos.*/
typedef struct pilha_rotulos_t{
	int 					topo;					/* armazena o topo da pilha de rótulos	*/
	unsigned int			contador;				/* Incrementado sempre que um rótulo é solicitado. */
	int 					rotulos[MAX_ROTULOS]; 	/* Quantidade máxima de Rótulos "abertos" por vez. */
} Pilha_Rotulos;

/* Define valores Iniciais para Pilha de Rotulos vazia. */
void iniciaPilhaRotulos();

/* Empilha novo elemento na Pilha de Rotulos e retorna seu rótulo em 'rotulo'. */
void empilhaRotulo(char *rotulo);

/* Retorna rotulo no topo da pilha de rotulos em 'rotulo'.*/
void desempilhaRotulo(char *rotulo);

/*
    ---------------------------------
    |   FIM --- PILHA DE ROTULOS    |
    ---------------------------------
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

/* 
		-------------------------
		|		VALIDAÇÃO		|
		-------------------------	
*/

/*
	Verifica se "primeiro" e "segundo" São do mesmo tipo, retornando "primeiro" caso verdadeiro 
	e imprime mensagem de error e para execussão (exit(-1)) caso seja falso.
*/
char * validaTipos(int nivel, char *primeiro, char *segundo);

/*
	Verifica se "primeiro" e "segundo" São do mesmo tipo, retornando "primeiro" caso verdadeiro 
	e imprime mensagem de error e para execussão (exit(-1)) caso seja falso.
*/
EntradaTabelaSimbolos * validaSimbolo(int linha, char *simbolo);

/*
	Verifica se "primeiro" e "segundo" São do mesmo tipo, retornando "primeiro" caso verdadeiro 
	e imprime mensagem de error indicando parâmetro e para execussão (exit(-1)) caso seja falso.
*/
char * validaParametro(int linha, char *primeiro, char *segundo, int ordem);

// Verifica se quantidade de parâmetros é igual, caso contrário retorna erro.
void validaNumParametros(int linha, int parametros_encontraros, int parametros_necesarios);

// Verifica se o simbolo 'identificador' pode ser inserido em Tabela de Simbolos, caso contrário retorna erro.
void validaInsercaoSimbolo(int linha, char *identificador, int nivel, CategoriaSimbolos categoria);

// Verifica se flag indicativa que expressão se trata do passamento de variavel por referência ('flag_PF_ref'), caso verdadeiro retornar erro.
void verificaProcedenciaReferencia(int linha, int flag_PF_ref);

// Compara valores de 'primeiro_nivel' e 'segundo_nivel', caso diferentes, retorna erro indicando linha 'linha'.
void validaNivelLexico(int linha, int primeiro_nivel, int segundo_nivel);
/* 
		-----------------------------
		|		FIM VALIDAÇÃO		|
		-----------------------------	
*/

/* 
		-----------------------------
		|		DEFINIÇÕES MEPA		|
		-----------------------------	
*/
/*Recebe o número de variáveis em num_variaveis e imprime "AMEM num_variaveis" em MEPA*/
void imprimeAMEM (int num_variaveis);

/* Recebe texto com valor de constante e imprime em arquivo MEPA */
void carregaConstanteMEPA(char *constante);

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de recuperação de variável em arquivo MEPA.*/
void carregaValorMEPA(int nivel_lexico, int deslocamento);

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de recuperação de variável em arquivo MEPA.*/
void carregaVariavelIndiretoMEPA(int nivel_lexico, int deslocamento);

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de passagem de variável por referência em arquivo MEPA. */
void carregaReferenciaVariavelMEPA(int nivel_lexico,int deslocamento);

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de armazenamento de valore em variavel MEPA.*/
void armazenaVariavelSimplesMEPA(int nivel_lexico, int deslocamento);

/* Recebe valores de 'nível_lexico' e 'deslocamento' e imprime comando MEPA de armazenamento de valor indiretamente em variavel MEPA.*/
void armazenaVariavelIndiretaMEPA(int nivel_lexico, int deslocamento);

/* Recebe 'rotulo' imprime comando MEPA de desvio condicional em arquivo MEPA.*/
void imprimeDesviaSeFalsoMEPA(char* rotulo);

/* Recebe 'rotulo' imprime comando MEPA de desvio incondicional em arquivo MEPA. */
void imprimeDesviaSempre(char* rotulo);

/* Recebe 'rotulo' e 'nivelL léxico' imprime comando MEPA de entrada de subrotina em arquivo MEPA.*/
void imprimeEntraProcedimento(char *rotulo, int nivel_lexico);

/* Recebe a quantidade de variáveis a serem desalocadas em 'quantidade' e imprime 'DMEM quantidade' */
void imprimeDesalocaMemoria(int quantidade);

/* Recebe o nível léxico e a quantidade de parâmetros da função a ser retornada e imprime 'RPTR nivel_lexico,quantidade_parametros' */
void imprimeRetornaProcedimento(int nivel_lexico, int quantidade_parametros);

/* Recebe o rótulo e o nível léxico de retorno da função a ser chamada e imprime 'CHPR rotulo,nivel_lexico' */
void imprimeChamaProcedimento(char *rotulo,int nivel_lexico);
/* 
		---------------------------------
		|		FIM DEFINIÇÕES MEPA		|
		---------------------------------	
*/

