#ifndef __CONST_H__
#define __CONST_H__

extern const char * terminal_name[];

extern const char * type_name[];
enum type_enum{
int_type=0,
float_type} ;

extern const char * nonterminal_name[] ;
enum nonterminal_name_enum{
Program = 0,
ExtDefList,
ExtDef,
ExtDecList,
Specifier,
StructSpecifier,
OptTag,
Tag,
VarDec,
FunDec,
VarList,
ParamDec,
CompSt,
StmtList,
Stmt,
DefList,
Def,
DecList,
Dec,
Exp,
Args};

#endif
