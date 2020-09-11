/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "compilador.y" /* yacc.c:339  */

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
Atributos_SUBR aproc;

/*  Auxilia na recuperação de Atributos */
void   *atributos;

/* Auxilia em operções com entrada da tablea de simbolos. */
EntradaTabelaSimbolos entrada_ts;

#line 96 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    ABRE_PARENTESES = 259,
    FECHA_PARENTESES = 260,
    VIRGULA = 261,
    PONTO_E_VIRGULA = 262,
    DOIS_PONTOS = 263,
    PONTO = 264,
    T_BEGIN = 265,
    T_END = 266,
    VAR = 267,
    ATRIBUICAO = 268,
    IGUAL = 269,
    DIFERENTE = 270,
    MENOR_QUE = 271,
    MAIOR_QUE = 272,
    MENOR_OU_IGUAL = 273,
    MAIOR_OU_IGUAL = 274,
    SOMA = 275,
    SUBTRACAO = 276,
    PRODUTO = 277,
    DIVISAO = 278,
    OR = 279,
    AND = 280,
    NOT = 281,
    NUMERO = 282,
    IDENT = 283,
    WHILE = 284,
    LABEL = 285,
    TYPE = 286,
    ARRAY = 287,
    OF = 288,
    PROCEDURE = 289,
    FUNCTION = 290,
    GOTO = 291,
    IF = 292,
    THEN = 293,
    ELSE = 294,
    DO = 295,
    LOWER_THAN_ELSE = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 36 "compilador.y" /* yacc.c:355  */

    Variavel_Simples v_sim;
    char    texto[128];

#line 180 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 197 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    77,    81,    82,    93,    93,    98,    99,
     103,   104,   108,   108,   112,   120,   137,   157,   158,   176,
     182,   187,   188,   194,   195,   205,   209,   210,   211,   212,
     217,   218,   219,   225,   238,   249,   248,   261,   260,   274,
     280,   288,   279,   311,   317,   328,   333,   338,   343,   348,
     353,   362,   367,   372,   380,   388,   396,   408,   414,   423,
     431,   443,   450,   460,   465,   477
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "ABRE_PARENTESES",
  "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO",
  "T_BEGIN", "T_END", "VAR", "ATRIBUICAO", "IGUAL", "DIFERENTE",
  "MENOR_QUE", "MAIOR_QUE", "MENOR_OU_IGUAL", "MAIOR_OU_IGUAL", "SOMA",
  "SUBTRACAO", "PRODUTO", "DIVISAO", "OR", "AND", "NOT", "NUMERO", "IDENT",
  "WHILE", "LABEL", "TYPE", "ARRAY", "OF", "PROCEDURE", "FUNCTION", "GOTO",
  "IF", "THEN", "ELSE", "DO", "LOWER_THAN_ELSE", "$accept", "programa",
  "$@1", "bloco", "parte_declara_vars", "$@2", "var", "declara_vars",
  "declara_var", "$@3", "tipo", "lista_id_var", "lista_idents",
  "parte_de_declaracao_de_subrotinas", "declaracao_de_procedimento",
  "parametros_formais", "secao_parametros_formais", "comando_composto",
  "comandos", "comando_sem_rotulo", "atribui", "comando_condicional",
  "if_then", "$@4", "cond_else", "$@5", "comando_repetitivo", "$@6", "$@7",
  "expressao", "relacao", "exp_simples", "termo", "fator", "variavel", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -56,     7,     3,   -56,   -15,    14,    -9,   -56,    74,    24,
      18,    22,   -56,    49,    72,    73,    70,   -56,   -56,    80,
     -56,   -12,   -56,   -56,   -56,     2,    77,   -56,   -56,     1,
      13,   -56,   -56,   -56,    47,   -56,    75,    59,   -56,    61,
      -9,    63,    65,   -56,     8,     1,     1,     6,     6,     6,
     -56,   -56,    34,    42,   -56,   -56,   -12,   -56,   -56,   -56,
       1,   -56,   -56,    67,    68,    62,    84,     2,   -56,    52,
      88,    42,    42,   -56,    56,   -56,   -56,   -56,   -56,   -56,
     -56,     6,     6,     6,     1,     6,     6,     6,    89,     8,
     -56,    69,    71,    76,   -56,    22,   -56,   -56,   -56,     8,
      42,    42,    42,    39,   -56,   -56,   -56,   -56,   -56,   -56,
      91,   -56,   -56,    90,   -56,   -56,   -12,    55,    94,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    18,     0,     0,
       0,     6,    17,     0,     0,     0,     9,     5,    19,     0,
       3,    29,     4,    12,     7,     0,     0,    65,    40,     0,
       0,    26,    30,    31,    39,    32,     0,     8,    11,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
      62,    35,    43,    51,    57,    61,    29,    25,    37,    34,
       0,    10,    16,     0,     0,     0,     0,     0,    27,     0,
       0,    52,    53,    64,     0,    45,    46,    47,    48,    49,
      50,     0,     0,     0,     0,     0,     0,     0,    28,     0,
      33,     0,     0,     0,    23,     6,    22,    41,    63,     0,
      54,    55,    56,    44,    58,    59,    60,    38,    15,    14,
       0,    24,    20,     0,    36,    13,    29,     0,     0,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,    10,   -56,   -56,   -56,   -56,    66,   -56,
     -56,   -56,    -2,   -56,   -56,   -56,    35,   -56,   -55,   -42,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -34,
     -56,    23,   -39,   -46,   -21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    14,    15,    16,    24,    37,    38,    39,
     110,    63,    41,    17,    18,    42,    43,    22,    30,    31,
      32,    33,    34,    74,    59,    89,    35,    45,   113,    51,
      84,    52,    53,    54,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    88,    68,    73,     8,    46,     4,     3,    71,    72,
      46,    69,    70,     5,    40,    26,    27,    28,     6,     7,
      56,    47,    48,    36,    57,    29,    90,    49,    50,    27,
       7,    11,    49,    50,    27,    36,    27,    28,    64,   104,
     105,   106,   100,   101,   102,    29,    12,   107,    75,    76,
      77,    78,    79,    80,    81,    82,    13,   114,    83,    81,
      82,   117,    56,    83,    85,    86,   118,    87,    36,    10,
      66,    65,    67,    91,    10,    92,    93,    19,    36,     9,
      10,    20,    23,    21,    25,    44,    58,   -12,    60,    62,
      94,    95,    97,    98,    99,    36,    56,   108,   115,   109,
     116,   119,    96,    61,   111,   112,     0,   103
};

static const yytype_int8 yycheck[] =
{
      21,    56,    44,    49,     6,     4,     3,     0,    47,    48,
       4,    45,    46,    28,    12,    27,    28,    29,     4,    28,
       7,    20,    21,    44,    11,    37,    60,    26,    27,    28,
      28,     7,    26,    27,    28,    56,    28,    29,    40,    85,
      86,    87,    81,    82,    83,    37,    28,    89,    14,    15,
      16,    17,    18,    19,    20,    21,    34,    99,    24,    20,
      21,   116,     7,    24,    22,    23,    11,    25,    89,     6,
       5,     8,     7,     6,     6,     8,     8,    28,    99,     5,
       6,     9,    12,    10,     4,     8,    39,    28,    13,    28,
      28,     7,    40,     5,    38,   116,     7,    28,     7,    28,
      10,     7,    67,    37,    28,    95,    -1,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     3,    28,     4,    28,    54,     5,
       6,     7,    28,    34,    45,    46,    47,    55,    56,    28,
       9,    10,    59,    12,    48,     4,    27,    28,    29,    37,
      60,    61,    62,    63,    64,    68,    76,    49,    50,    51,
      12,    54,    57,    58,     8,    69,     4,    20,    21,    26,
      27,    71,    73,    74,    75,    76,     7,    11,    39,    66,
      13,    50,    28,    53,    54,     8,     5,     7,    61,    71,
      71,    74,    74,    75,    65,    14,    15,    16,    17,    18,
      19,    20,    21,    24,    72,    22,    23,    25,    60,    67,
      71,     6,     8,     8,    28,     7,    58,    40,     5,    38,
      74,    74,    74,    73,    75,    75,    75,    61,    28,    28,
      52,    28,    45,    70,    61,     7,    10,    60,    11,     7
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    44,    43,    45,    45,    47,    46,    48,    48,
      49,    49,    51,    50,    52,    53,    53,    54,    54,    55,
      56,    57,    57,    58,    58,    59,    60,    60,    60,    60,
      61,    61,    61,    62,    63,    65,    64,    67,    66,    66,
      69,    70,    68,    71,    71,    72,    72,    72,    72,    72,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      74,    75,    75,    75,    75,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     9,     2,     1,     0,     2,     2,     0,
       2,     1,     0,     5,     1,     3,     1,     3,     1,     1,
       7,     1,     3,     3,     4,     3,     1,     3,     3,     0,
       1,     1,     1,     3,     2,     0,     5,     0,     3,     0,
       0,     0,     9,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     3,     1,     3,     3,
       3,     1,     1,     3,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 77 "compilador.y" /* yacc.c:1646  */
    { geraCodigo (NULL, "INPP"); }
#line 1359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 77 "compilador.y" /* yacc.c:1646  */
    {geraCodigo (NULL, "PARA"); }
#line 1365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "compilador.y" /* yacc.c:1646  */
    {num_vars = 0;}
#line 1371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "compilador.y" /* yacc.c:1646  */
    { imprimeAMEM(&num_vars); }
#line 1377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 108 "compilador.y" /* yacc.c:1646  */
    {num_tipo_vars = 0;}
#line 1383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 113 "compilador.y" /* yacc.c:1646  */
    {
                defineTipoVariavel(num_tipo_vars, token);    /* Definindo o tipo das "num_tipo_vars" variáveis para "token" */
            }
#line 1391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 121 "compilador.y" /* yacc.c:1646  */
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
#line 1412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 138 "compilador.y" /* yacc.c:1646  */
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
#line 1433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 226 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando se 'variavel' $1 e 'expressao' $3 possuem o mesmo tipo */
                validaTipos(nl, (yyvsp[-2].v_sim).tipo, (yyvsp[0].texto));

                /* Defindo instrução MEPA para armazenamento em 'variavel' */
                armazenaVariavelSimplesMEPA((yyvsp[-2].v_sim).nivel, (yyvsp[-2].v_sim).deslocamento);
            }
#line 1445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 239 "compilador.y" /* yacc.c:1646  */
    {
                /* Desempilha Rótulo de saida de if OU if/else */
                desempilhaRotulo(saida_while);

                /* Imprime rótulo de saida em MEPA */
                geraCodigo(saida_while, "NADA");
            }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 249 "compilador.y" /* yacc.c:1646  */
    {
                /* Empilha Rótulo para onde deve-se dirigir quando condição IF for FALSA. */
                empilhaRotulo(saida_while);
                
                /* Imprime comando para saida de if caso 'expressao' seja falso (DSVF).*/
                imprimeDesviaSeFalsoMEPA(saida_while);
            }
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 261 "compilador.y" /* yacc.c:1646  */
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
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 280 "compilador.y" /* yacc.c:1646  */
    {
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(entrada_while);

                /* Imprimendo rótulo de entrada do while em arquivo MEPA */
                geraCodigo(entrada_while, "NADA");
            }
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 288 "compilador.y" /* yacc.c:1646  */
    { 
                /* Gerando os Rótulos de entrada e saida do WHILE*/
                empilhaRotulo(saida_while);

                /* Imprime comando para saida de loop caso 'expressao' seja falsa.*/
                imprimeDesviaSeFalsoMEPA(saida_while);
            }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 296 "compilador.y" /* yacc.c:1646  */
    {
                
                desempilhaRotulo(saida_while);
                desempilhaRotulo(entrada_while);

                /* Imprime comando para retorno ao inícion do while */
                imprimeDesviaSempre(entrada_while);
                
                /* Imprimendo rótulo de saida do while em arquivo MEPA */
                geraCodigo(saida_while, "NADA");
            }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 312 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'exp_simples' ($1) para 'expressao'($$) */
                strcpy((yyval.texto), (yyvsp[0].texto));
            }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 318 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'expressao' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));
                /* Imprime comando MEPA de relação  obtido por 'relacao' */
                geraCodigo(NULL, (yyvsp[-1].texto));
            }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 329 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '='. */
                strcpy((yyval.texto), "CMIG");
            }
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 334 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '<>'. */
                strcpy((yyval.texto), "CMDG");
            }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 339 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '<'. */
                strcpy((yyval.texto), "CMME");
            }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 344 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '>'. */
                strcpy((yyval.texto), "CMMA");
            }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 349 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '<='. */
                strcpy((yyval.texto), "CMEG");
            }
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 354 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de '>='. */
                strcpy((yyval.texto), "CMAG");
            }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 363 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'termo' ($1) para 'exp_simples'($$) */
                strcpy((yyval.texto), (yyvsp[0].texto));
            }
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 368 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
                strcpy((yyval.texto), (yyvsp[0].texto));
            }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 373 "compilador.y" /* yacc.c:1646  */
    {
                /* Imprime comando MEPA de INVERSÃO DE SINAL. */
                geraCodigo(NULL, "INVR");
                
                /* Repassando tipo de 'termo' ($2) para 'exp_simples'($$) */
                strcpy((yyval.texto), (yyvsp[0].texto));
            }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 381 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));

                /* Imprime comando MEPA de SOMA. */
                geraCodigo(NULL, "SOMA");
            }
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 389 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));

                /* Imprime comando MEPA de SUBTRAÇÃO. */
                geraCodigo(NULL, "SUBT");
            }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 397 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'exp_simples' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));

                /* Imprime comando MEPA de DISJUNÇÃO. */
                geraCodigo(NULL, "DISJ");
            }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 409 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'fator' ($1) para 'termo'($$) */
                strcpy((yyval.texto), (yyvsp[0].texto));
            }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 415 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));

                /* Imprime comando MEPA de MULTIPLICAÇÃO. */
                geraCodigo(NULL, "MULT");

            }
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 424 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));
                
                /* Imprime comando MEPA de DIVISÃO. */
                geraCodigo(NULL, "DIVI");
            }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 432 "compilador.y" /* yacc.c:1646  */
    {
                /* Verificando tipos de $1 e $3 e repassando para 'termo' */
                strcpy((yyval.texto), validaTipos(nl,(yyvsp[-2].texto), (yyvsp[0].texto)));

                /* Imprime comando MEPA de CONJUNÇÃO. */
                geraCodigo(NULL, "CONJ");
            }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 444 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'variavel' ($2) para 'fator'($$) */
                strcpy((yyval.texto), (yyvsp[0].v_sim).tipo);

                carregaValorMEPA( nivel_lexico, (yyvsp[0].v_sim).deslocamento);
            }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 451 "compilador.y" /* yacc.c:1646  */
    {
                /* Definindo tipo de 'fator' para 'integer'. */
                strcpy((yyval.texto), "integer");

                /* Imprime comando MEPA de definição de constante. */
                carregaConstanteMEPA(token);
            }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 461 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de 'expressao' ($2) para 'fator'($$) */
                strcpy((yyval.texto), (yyvsp[-1].texto));
            }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 466 "compilador.y" /* yacc.c:1646  */
    {
                /* Repassando tipo de  $2 para $$ */
                strcpy((yyval.texto), (yyvsp[0].texto));

                /* Imprime comando MEPA de negação. */
                geraCodigo(NULL, "NEGA");
            }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 478 "compilador.y" /* yacc.c:1646  */
    {              
                /* Armazena em 'avs' atributos de 'token' após verificação por validaSimbolo(); */
                avs = *( (Atributos_VS *) validaSimbolo(nl, token));

                /* Populando 'variavel' com atributos recebidos de Tabela de Simbolos. */
                strcpy((yyval.v_sim).token, token);
                strcpy((yyval.v_sim).tipo, avs.tipo);
                (yyval.v_sim).nivel = nivel_lexico;
                (yyval.v_sim).deslocamento = avs.deslocamento;
            }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1775 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 491 "compilador.y" /* yacc.c:1906  */


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
