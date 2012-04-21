
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "calc.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#include "struct.h"
#include "relop.h"
#include "global.h"
#include "const.h"
#include "type.h"
#include "analyze.h"

extern int num_lines;
extern int yylineno;
extern int yylex(void);

void yyerror (char  *);
int relop_switch(int arg1,int arg2,int arg3);
NODE *  cp_node(const char * ,NODE *  );
NODE * cp_link(const char * ,NODE *) ;
NODE * csp_node(const char * ,NODE * head , ...) ;
NODE * empty_node() ;
static void free_list(void* head);
static void free_tree(void* root);



/* Line 189 of yacc.c  */
#line 103 "calc.yy.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHILE = 258,
     IF = 259,
     RETURN = 260,
     STRUCT = 261,
     TYPE = 262,
     COMMA = 263,
     SEMI = 264,
     LC = 265,
     RC = 266,
     LOWER_THAN_ELSE = 267,
     ELSE = 268,
     INT = 269,
     FLOAT = 270,
     ID = 271,
     ASSIGNOP = 272,
     OR = 273,
     AND = 274,
     RELOP = 275,
     MINUS = 276,
     PLUS = 277,
     DIV = 278,
     STAR = 279,
     NOT = 280,
     NEG = 281,
     DOT = 282,
     RB = 283,
     LB = 284,
     RP = 285,
     LP = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 176 "calc.yy.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    16,    20,    23,
      26,    30,    32,    36,    38,    40,    46,    49,    52,    58,
      59,    61,    63,    65,    70,    75,    80,    84,    89,    93,
      97,    99,   102,   107,   112,   113,   116,   119,   121,   125,
     131,   139,   145,   148,   156,   164,   167,   171,   172,   175,
     179,   183,   185,   189,   191,   195,   197,   199,   201,   205,
     209,   213,   217,   221,   225,   228,   232,   236,   239,   244,
     248,   252,   256,   261,   264,   267,   271
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    -1,    35,    34,    -1,    37,
      36,     9,    -1,    37,     9,    -1,    37,    42,    45,    -1,
      37,     1,    -1,     1,     9,    -1,    37,    36,     1,    -1,
      41,    -1,    41,     8,    36,    -1,     7,    -1,    38,    -1,
       6,    39,    10,    48,    11,    -1,     6,    40,    -1,     6,
       1,    -1,     6,    39,    10,    48,     1,    -1,    -1,    16,
      -1,    16,    -1,    16,    -1,    41,    29,    14,    28,    -1,
      41,    29,    14,     1,    -1,    16,    31,    43,    30,    -1,
      16,    31,    30,    -1,    16,    31,    43,     1,    -1,    16,
      31,     1,    -1,    44,     8,    43,    -1,    44,    -1,    37,
      41,    -1,    10,    48,    46,    11,    -1,     1,    48,    46,
      11,    -1,    -1,    47,    46,    -1,    52,     9,    -1,    45,
      -1,     5,    52,     9,    -1,     4,    31,    52,    30,    47,
      -1,     4,    31,    52,    30,    47,    13,    47,    -1,     3,
      31,    52,    30,    47,    -1,     1,     9,    -1,     4,    31,
      52,     1,    47,    13,    47,    -1,     4,     1,    52,    30,
      47,    13,    47,    -1,    52,     1,    -1,     5,    52,     1,
      -1,    -1,    49,    48,    -1,    37,    50,     9,    -1,    37,
      50,     1,    -1,    51,    -1,    51,     8,    50,    -1,    41,
      -1,    41,    17,    52,    -1,    16,    -1,    14,    -1,    15,
      -1,    52,    19,    52,    -1,    52,    18,    52,    -1,    52,
      22,    52,    -1,    52,    21,    52,    -1,    52,    24,    52,
      -1,    52,    23,    52,    -1,    21,    52,    -1,    31,    52,
      30,    -1,    52,    20,    52,    -1,    25,    52,    -1,    52,
      29,    52,    28,    -1,    52,    17,    52,    -1,    16,    31,
      30,    -1,    52,    27,    16,    -1,    16,    31,    53,    30,
      -1,     1,    30,    -1,     1,    28,    -1,    52,     8,    53,
      -1,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    48,    48,    54,    55,    57,    58,    59,    60,    61,
      62,    64,    65,    67,    68,    70,    71,    72,    73,    76,
      77,    79,    82,    83,    84,    86,    87,    88,    89,    91,
      92,    94,    97,    98,   100,   101,   103,   104,   105,   106,
     107,   108,   109,   113,   114,   115,   116,   118,   119,   121,
     122,   124,   125,   127,   128,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   155,   156
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "IF", "RETURN", "STRUCT",
  "TYPE", "COMMA", "SEMI", "LC", "RC", "LOWER_THAN_ELSE", "ELSE", "INT",
  "FLOAT", "ID", "ASSIGNOP", "OR", "AND", "RELOP", "MINUS", "PLUS", "DIV",
  "STAR", "NOT", "NEG", "DOT", "RB", "LB", "RP", "LP", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    36,    36,    37,    37,    38,    38,    38,    38,    39,
      39,    40,    41,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    45,    45,    46,    46,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     2,
       3,     1,     3,     1,     1,     5,     2,     2,     5,     0,
       1,     1,     1,     4,     4,     4,     3,     4,     3,     3,
       1,     2,     4,     4,     0,     2,     2,     1,     3,     5,
       7,     5,     2,     7,     7,     2,     3,     0,     2,     3,
       3,     1,     3,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     2,     4,     3,
       3,     3,     4,     2,     2,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    13,     0,     2,     0,     0,    14,     9,
      17,    21,     0,    16,     1,     4,     8,     6,    22,     0,
      11,     0,    47,     0,    10,     5,     0,     0,    47,    47,
       7,     0,     0,    47,    28,    26,     0,     0,    30,    22,
      12,     0,     0,     0,    53,     0,    51,    18,    15,    48,
      31,    27,    25,     0,    24,    23,    47,     0,     0,     0,
      56,    57,    55,     0,     0,     0,    37,     0,     0,     0,
       0,     0,    50,    49,     0,    29,    42,    74,    73,     0,
       0,     0,     0,     0,     0,    64,    67,     0,    33,    35,
      45,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    54,    52,     0,     0,     0,    46,    38,
      70,    76,     0,    65,    69,    59,    58,    66,    61,    60,
      63,    62,    71,     0,     0,     0,     0,     0,     0,    72,
      68,    41,     0,     0,    39,    75,     0,     0,     0,    44,
      43,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    19,    31,     8,    12,    13,    20,
      21,    37,    38,    66,    67,    68,    42,    33,    45,    46,
      69,   112
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int16 yypact[] =
{
     117,     7,    85,   -60,    32,   -60,   117,   105,   -60,   -60,
     -60,    38,    43,   -60,   -60,   -60,   -60,   -60,    50,    79,
       2,     8,    52,    22,   -60,   -60,    66,    49,    52,    52,
     -60,    66,    44,    52,   -60,   -60,    66,    13,    67,   -60,
     -60,    16,    46,    46,    47,    96,    91,   -60,   -60,   -60,
      74,   -60,   -60,    52,   -60,   -60,    59,    73,    10,    95,
     -60,   -60,    88,    95,    95,    95,   -60,   114,    46,   135,
     116,    95,   -60,   -60,    66,   -60,   -60,   -60,   -60,    95,
      95,    95,   -15,   159,    77,    86,    86,   204,   -60,   -60,
     -60,   -60,    95,    95,    95,    95,    95,    95,    95,    95,
     106,    95,   -60,   259,   -60,   218,   232,   111,   -60,   -60,
     -60,   176,   107,   -60,   259,   270,   280,   289,   119,   119,
      86,    86,   -60,   246,    69,    69,    69,    69,    95,   -60,
     -60,   -60,   126,   132,   134,   -60,    69,    69,    69,   -60,
     -60,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   143,   -60,   124,     1,   -60,   -60,   -60,   -28,
     -60,    98,   -60,   140,   -41,    82,    -3,   -60,    89,   -60,
     -59,    37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -35
static const yytype_int16 yytable[] =
{
      83,     7,    70,    44,    85,    86,    87,     7,    50,    28,
      26,    80,   103,    77,    51,    78,     9,    54,    29,    32,
     105,   106,   107,    34,    36,   111,    43,    89,     2,     3,
      49,    27,    14,   114,   115,   116,   117,   118,   119,   120,
     121,    81,   123,    52,    55,    47,    44,    56,   -20,    57,
      58,    59,    35,    22,    36,    48,    29,   -34,     2,     3,
      60,    61,    62,    41,    71,     2,     3,    63,    76,   111,
      56,    64,    57,    58,    59,    53,    27,    65,    82,    29,
      24,    23,    39,    60,    61,    62,    10,    77,    25,    78,
      63,    60,    61,    62,    64,   -19,    82,    72,    63,    74,
      65,    11,    64,    27,    79,    73,    16,   110,    65,    60,
      61,    62,   126,   100,    17,   101,    63,    -3,     1,    84,
      64,    18,   122,     2,     3,    88,    65,   102,    92,    93,
      94,    95,    96,    97,    98,    99,    90,   129,   100,   136,
     101,   127,    98,    99,    91,   137,   100,   138,   101,    15,
      40,    75,    92,    93,    94,    95,    96,    97,    98,    99,
     108,    30,   100,   104,   101,   135,     0,     0,   109,     0,
       0,     0,     0,     0,     0,     0,    92,    93,    94,    95,
      96,    97,    98,    99,   128,     0,   100,     0,   101,     0,
       0,     0,     0,    92,    93,    94,    95,    96,    97,    98,
      99,     0,     0,   100,     0,   101,   131,   132,   133,   134,
       0,     0,     0,     0,     0,     0,     0,     0,   139,   140,
     141,    92,    93,    94,    95,    96,    97,    98,    99,     0,
       0,   100,     0,   101,   113,    92,    93,    94,    95,    96,
      97,    98,    99,     0,     0,   100,     0,   101,   124,    92,
      93,    94,    95,    96,    97,    98,    99,     0,     0,   100,
       0,   101,   125,    92,    93,    94,    95,    96,    97,    98,
      99,     0,     0,   100,   130,   101,    92,    93,    94,    95,
      96,    97,    98,    99,     0,     0,   100,     0,   101,    94,
      95,    96,    97,    98,    99,     0,     0,   100,     0,   101,
      95,    96,    97,    98,    99,     0,     0,   100,     0,   101,
      96,    97,    98,    99,     0,     0,   100,     0,   101
};

static const yytype_int16 yycheck[] =
{
      59,     0,    43,    31,    63,    64,    65,     6,    36,     1,
       8,     1,    71,    28,     1,    30,     9,     1,    10,    22,
      79,    80,    81,     1,    23,    84,    29,    68,     6,     7,
      33,    29,     0,    92,    93,    94,    95,    96,    97,    98,
      99,    31,   101,    30,    28,     1,    74,     1,    10,     3,
       4,     5,    30,    10,    53,    11,    10,    11,     6,     7,
      14,    15,    16,    14,    17,     6,     7,    21,     9,   128,
       1,    25,     3,     4,     5,     8,    29,    31,     1,    10,
       1,    31,    16,    14,    15,    16,     1,    28,     9,    30,
      21,    14,    15,    16,    25,    10,     1,     1,    21,     8,
      31,    16,    25,    29,    31,     9,     1,    30,    31,    14,
      15,    16,     1,    27,     9,    29,    21,     0,     1,    31,
      25,    16,    16,     6,     7,    11,    31,    11,    17,    18,
      19,    20,    21,    22,    23,    24,     1,    30,    27,    13,
      29,    30,    23,    24,     9,    13,    27,    13,    29,     6,
      26,    53,    17,    18,    19,    20,    21,    22,    23,    24,
       1,    21,    27,    74,    29,   128,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,     8,    -1,    27,    -1,    29,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    -1,    29,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   136,   137,
     138,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    27,    -1,    29,    30,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    -1,    29,    30,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    29,    30,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    29,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    27,    -1,    29,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    -1,    29,
      20,    21,    22,    23,    24,    -1,    -1,    27,    -1,    29,
      21,    22,    23,    24,    -1,    -1,    27,    -1,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,    33,    34,    35,    37,    38,     9,
       1,    16,    39,    40,     0,    34,     1,     9,    16,    36,
      41,    42,    10,    31,     1,     9,     8,    29,     1,    10,
      45,    37,    48,    49,     1,    30,    37,    43,    44,    16,
      36,    14,    48,    48,    41,    50,    51,     1,    11,    48,
      41,     1,    30,     8,     1,    28,     1,     3,     4,     5,
      14,    15,    16,    21,    25,    31,    45,    46,    47,    52,
      46,    17,     1,     9,     8,    43,     9,    28,    30,    31,
       1,    31,     1,    52,    31,    52,    52,    52,    11,    46,
       1,     9,    17,    18,    19,    20,    21,    22,    23,    24,
      27,    29,    11,    52,    50,    52,    52,    52,     1,     9,
      30,    52,    53,    30,    52,    52,    52,    52,    52,    52,
      52,    52,    16,    52,    30,    30,     1,    30,     8,    30,
      28,    47,    47,    47,    47,    53,    13,    13,    13,    47,
      47,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 48 "calc.y"
    {
							(yyval)=csp_node(nonterminal_name[Program],(yyvsp[(1) - (1)]) , NULL) ;	
							node_head = (yyval) ;
							YYACCEPT;
						;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 54 "calc.y"
    {(yyval)=empty_node(nonterminal_name[ExtDefList]) ;				;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 55 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDefList],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);			;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 57 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDef],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);			;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 58 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDef],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);			;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 59 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDef],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);			;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 60 "calc.y"
    {yyerror(": Expected \";\"\n");yyerrok;					;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 61 "calc.y"
    {yyerror(": error in Specifier\n");yyerrok;				;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 62 "calc.y"
    {yyerror(": Expected \";\"\n");yyerrok;					;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 64 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDecList],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 65 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ExtDecList],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 67 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Specifier],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 68 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Specifier],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 70 "calc.y"
    {(yyval)=csp_node(nonterminal_name[StructSpecifier],(yyvsp[(1) - (5)]),(yyvsp[(2) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(4) - (5)]),(yyvsp[(5) - (5)]),NULL);	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 71 "calc.y"
    {(yyval)=csp_node(nonterminal_name[StructSpecifier],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 72 "calc.y"
    {yyerror(": error in struct specifier\n");yyerrok;			;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 73 "calc.y"
    {yyerror(": Expected \"}\"\n");yyerrok;					;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 76 "calc.y"
    {(yyval)=empty_node(nonterminal_name[OptTag]) ;			;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 77 "calc.y"
    {(yyval)=csp_node(nonterminal_name[OptTag],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 79 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Tag],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 82 "calc.y"
    {(yyval)=csp_node(nonterminal_name[VarDec],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 83 "calc.y"
    {(yyval)=csp_node(nonterminal_name[VarDec],(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),NULL);	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 84 "calc.y"
    {yyerror(": Expected \"]\"\n");yyerrok;				;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 86 "calc.y"
    {(yyval)=csp_node(nonterminal_name[FunDec],(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),NULL);	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 87 "calc.y"
    {(yyval)=csp_node(nonterminal_name[FunDec],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 88 "calc.y"
    {yyerror(": Expected \")\" \n");yyerrok;			;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 89 "calc.y"
    {yyerror(": Expected \")\" \n");yyerrok;			;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 91 "calc.y"
    {(yyval)=csp_node(nonterminal_name[VarList],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 92 "calc.y"
    {(yyval)=csp_node(nonterminal_name[VarList],(yyvsp[(1) - (1)]),NULL);		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 94 "calc.y"
    {(yyval)=csp_node(nonterminal_name[ParamDec],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 97 "calc.y"
    {(yyval)=csp_node(nonterminal_name[CompSt],(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),NULL);	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 98 "calc.y"
    {yyerror(": Expected \"{\"\n");yyerrok;		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 100 "calc.y"
    {(yyval)=empty_node(nonterminal_name[StmtList]) ;			;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 101 "calc.y"
    {(yyval)=csp_node(nonterminal_name[StmtList],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 103 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 104 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 105 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 106 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (5)]),(yyvsp[(2) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(4) - (5)]),(yyvsp[(5) - (5)]),NULL);	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 107 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (7)]),(yyvsp[(2) - (7)]),(yyvsp[(3) - (7)]),(yyvsp[(4) - (7)]),(yyvsp[(5) - (7)]),(yyvsp[(6) - (7)]),(yyvsp[(7) - (7)]),NULL);	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 108 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Stmt],(yyvsp[(1) - (5)]),(yyvsp[(2) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(4) - (5)]),(yyvsp[(5) - (5)]),NULL);	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 109 "calc.y"
    {	
						yyerror(": unknown statement before \";\"\n");
						yyerrok;
						;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 113 "calc.y"
    {yyerror(": Expected \")\" \n");yyerrok;	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 114 "calc.y"
    {yyerror(": Expected \"(\" \n");yyerrok;	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 115 "calc.y"
    {yyerror(": Expected \";\"\n");yyerrok;		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 116 "calc.y"
    {yyerror(": Expected \";\" \n");yyerrok;	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 118 "calc.y"
    {(yyval)=empty_node(nonterminal_name[DefList]) ;			;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 119 "calc.y"
    {(yyval)=csp_node(nonterminal_name[DefList],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 121 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Def],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 122 "calc.y"
    {yyerror(": Expected \"; 1\"\n");yyerrok;			;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 124 "calc.y"
    {(yyval)=csp_node(nonterminal_name[DecList],(yyvsp[(1) - (1)]),NULL);		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 125 "calc.y"
    {(yyval)=csp_node(nonterminal_name[DecList],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 127 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Dec],(yyvsp[(1) - (1)]),NULL);			;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 128 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Dec],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 131 "calc.y"
    {(yyval)=cp_node(nonterminal_name[Exp],(yyvsp[(1) - (1)])) ;				;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 132 "calc.y"
    {(yyval)=cp_node(nonterminal_name[Exp],(yyvsp[(1) - (1)]));				;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 133 "calc.y"
    {(yyval)=cp_node(nonterminal_name[Exp],(yyvsp[(1) - (1)]));				;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 134 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 135 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 136 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 137 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 138 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 139 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 140 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);			;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 141 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 142 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 143 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),NULL);			;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 144 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),NULL);		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 145 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 146 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 147 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 148 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Exp],(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]),NULL);		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 149 "calc.y"
    {yyerror("\n");yyerrok;				;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 150 "calc.y"
    {
				yyerror(": unknown stuff before \"]\"\n");
				yyerrok;
				;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 155 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Args],(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]),NULL);		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 156 "calc.y"
    {(yyval)=csp_node(nonterminal_name[Args],(yyvsp[(1) - (1)]),NULL);			;}
    break;



/* Line 1455 of yacc.c  */
#line 2063 "calc.yy.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 158 "calc.y"



int main (void){
	NODE * head;
	nul=fopen("/dev/null","w");
	fpdebug = stdout; 
//	signal(SIGSEGV, &dump);
	idtable_head = create_idtem() ;
	if(nul != NULL){
//		fpdebug=nul ;
	}
	yydebug = 0; 
	
	if(yyparse () == 0)
		head = node_head;
	else{
		putc('\n',stderr);
		return -1;
	}
	traverse_item_list(idtable_head);
	tab = (char *)malloc(1);
	tab[0]='\0';
	if(noerror )traverse_node_tree((NODE*)head);

	free_list(idtable_head) ;
	free_tree(head);
	free(tab) ;
	return 0 ;
}
NODE * cp_node(const char * name ,NODE * c) {
	NODE* p_node = NULL;
	NODE* c_node= (NODE* )c ;
	p_node = value_create_node(c_node->value , c_node->line,c_node->name); 
	p_node->child_head = c_node ;
	c_node->parent = p_node ;
	p_node->name = name ;
	return (NODE *)p_node ;
}
NODE * cp_link(const char * name ,NODE * c) {
	NODE* p_node = NULL;
	NODE* c_node= (NODE* )c ;
	p_node = create_node(); 
	p_node->child_head = c_node ;
	c_node->parent = p_node ;
	p_node->line=c_node->line ;
	p_node->name= name ;
	return (NODE *)p_node ;
}
NODE * csp_node(const char * name ,NODE * ch , ...) {
	NODE * p ;
	va_list ap ;
	NODE* temp ;
	p = cp_link(name,ch) ;
	va_start(ap , ch) ;
	temp=(NODE*)ch ;
	while((temp->next_sister = (NODE*)va_arg(ap , NODE *))!= NULL){
		temp->next_sister->previous_sister = temp ;
		temp = temp->next_sister ;
		cp_link(name,temp);
	}
	va_end(ap);
	return p ;
}
NODE * empty_node(const char * name ) {
	NODE* node ;
	node= create_node() ;
	node->name = name ;
	return (NODE *)node ;
}

int traverse_node_tree(NODE* head ){
	char * temp;
	if(head->line==0)goto recursive;
	fputs(tab,stdout);
	analyze(head);
recursive:
	if(head->child_head != NULL){
		tab = realloc(tab,strlen(tab)+3);
		strcat(tab,"  ");
		traverse_node_tree(head->child_head);//here to recurse
		temp = tab ;
		tab=(char *)malloc(strlen(tab));
		strcpy(tab,temp+2);
		free(temp);
	}
	if(head->next_sister != NULL){
		traverse_node_tree(head->next_sister);//here to recurse
	}
	return 0;
}
static void free_tree(void* root){
	NODE* head = root ;
	if(head->child_head != NULL){
		free_tree(head->child_head) ;
	}
	if(head->next_sister != NULL){
		free_tree(head->next_sister);
	}
	free(head);
}

static void free_list(void* head){
	IDTEM* item = (IDTEM*)head ;
	if(item == NULL){return;}else{
		free_list(item->next) ;
	}
	free(item->name) ;
	free(item);
}
void yyerror(char* msg)
{
	noerror=0;
	if(strcmp(msg,"syntax error") == 0)
		fprintf(stderr,"Error Type 2 at line: %d: %s",yylineno,msg);
	else 
		fputs(msg,stderr);
}
int relop_switch(arg1,arg2,arg3){
	switch(arg2)
	{
	case LT:
	return (arg1< arg3);
        case LE:
	return (arg1<=arg3);
        case NE:
	return (arg1!=arg3);
        case EQ:
	return (arg1==arg3);
        case GT:
	return (arg1> arg3);
        case GE:
	return (arg1>=arg3);
	default:
	yyerror("relop error");
	return -1;
	}	
}

