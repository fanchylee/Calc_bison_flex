%{
#include <string.h>

#include "type.h"
#include "struct.h"
#include "relop.h"
#include "calc.yy.h"
#include "global.h"
#include "const.h"

int num_chars = 0;
extern FILE * fpdebug;
extern char  noerror ;
%}
%option noyywrap
%option yylineno

delim	[ \t\n]
ws	{delim}+
letter	[A-Za-z]
letter_	{letter}|_
digit	[0-9]
int	{digit}+
id	{letter_}({letter_}|{digit})*
float	{digit}*(\.{digit}+)
type	int|float
l_cmt_s	\/\/
l_cmt	{l_cmt_s}.*$
any	.|\n
ml	\/\*{any}*\*\/


%%
{ws}		{}
{l_cmt}		{}
{ml}		{}
if		{				
			yylval = value_create_node((MYVALUE)NULL,yylineno,terminal_name[IF          -WHILE]) ;
			return(IF          );
		}
struct		{	
			yylval = value_create_node((MYVALUE)NULL,yylineno,terminal_name[STRUCT      -WHILE]) ;
			return(STRUCT      );
		}
return		{
			yylval = value_create_node((MYVALUE)NULL,yylineno,terminal_name[RETURN      -WHILE]) ;
			return(RETURN      );
		}
while		{
			yylval = value_create_node((MYVALUE)NULL,yylineno,terminal_name[WHILE       -WHILE]) ;
			return(WHILE       );
		}
else		{	
			yylval = value_create_node((MYVALUE)NULL,yylineno,terminal_name[ELSE        -WHILE]) ;
			return(ELSE        );
		}
{type}		{
			if(strcmp(yytext,"int") == 0)
				yylval = value_create_node(ptou((void *)type_name[int_type]),yylineno,terminal_name[TYPE        -WHILE]) ;
			if(strcmp(yytext,"float") == 0)
				yylval = value_create_node(ptou((void *)type_name[float_type]),yylineno,terminal_name[TYPE        -WHILE]) ;
			return(TYPE        );
		}
{id}		{
			yylval = value_create_node(ptou(install_id(yytext)),yylineno,terminal_name[ID          -WHILE]) ;
			return(ID          );
		}
{int}		{
			yylval = value_create_node(itou(atoi(yytext)),yylineno,terminal_name[INT         -WHILE]);
			return(INT         );
		}
{float}		{
			yylval = value_create_node(ftou(atof(yytext)),yylineno,terminal_name[FLOAT       -WHILE]);
			return(FLOAT       );
		}
"&&"		{
			yylval = value_create_node(itou(AND),yylineno,terminal_name[AND         -WHILE]);
			return(AND         );
		}
"||"		{
			yylval = value_create_node(itou(OR),yylineno,terminal_name[OR          -WHILE]);
			return(OR          );
		}
"<"		{
			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);

			return(RELOP       );
		}
"<="		{

			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);
			return(RELOP       );
		}
"!="		{		

			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);
			return(RELOP       );
		}
"="		{
			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[ASSIGNOP    -WHILE]);
			return(ASSIGNOP    );
		}
"=="		{

			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);
			return(RELOP       );
		}
">"		{

			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);
			return(RELOP       );
		}
">="		{

			yylval = value_create_node(itou(RELOP),yylineno,terminal_name[RELOP       -WHILE]);
			return(RELOP       );
		}
";"		{
			yylval = value_create_node(itou(SEMI),yylineno,terminal_name[SEMI        -WHILE]);
			return(SEMI        );
		}
","		{
			yylval = value_create_node(itou(COMMA),yylineno,terminal_name[COMMA       -WHILE]);
			return(COMMA       );
		}
"("		{
			yylval = value_create_node(itou(LP),yylineno,terminal_name[LP          -WHILE]);
			return(LP          );
		}
")"		{
			yylval = value_create_node(itou(RP),yylineno,terminal_name[RP          -WHILE]);
			return(RP          );
		}
"["		{
			yylval = value_create_node(itou(LB),yylineno,terminal_name[LB          -WHILE]);
			return(LB          );
		}
"]"		{
			yylval = value_create_node(itou(RB),yylineno,terminal_name[RB          -WHILE]);
			return(RB          );
		}
"{"		{
			yylval = value_create_node(itou(LC),yylineno,terminal_name[LC          -WHILE]);
			return(LC          );
		}
"}"		{
			yylval = value_create_node(itou(RC),yylineno,terminal_name[RC          -WHILE]);
			return(RC          );
		}
"+"		{
			yylval = value_create_node(itou(PLUS),yylineno,terminal_name[PLUS        -WHILE]);
			return(PLUS        );
		}
"-"		{
			yylval = value_create_node(itou(MINUS),yylineno,terminal_name[MINUS       -WHILE]);
			return(MINUS       );
		}
"*"		{
			yylval = value_create_node(itou(STAR),yylineno,terminal_name[STAR        -WHILE]);
			return(STAR        );
		}
"/"		{
			yylval = value_create_node(itou(DIV),yylineno,terminal_name[DIV         -WHILE]);
			return(DIV         );
		}
"."		{
			yylval = value_create_node(itou(DOT),yylineno,terminal_name[DOT         -WHILE]);
			return(DOT         );
		}
"!"		{
			yylval = value_create_node(itou(NOT),yylineno,terminal_name[NOT         -WHILE]);
			return(NOT         );
		}
.		{
			noerror = 0 ;
			printf("Error type 1 at line %d: Mysterious character \'%s\'\n", yylineno, yytext);
		}

%%
NODE* create_node(){
	NODE* n ;
	n = (NODE*)calloc(1, sizeof(NODE)) ;
	memset(n,0,sizeof(NODE));
	return n ;
}
NODE* value_create_node(MYVALUE vl,int line,const char * name){
	NODE* temp_node;
	temp_node=create_node() ;
	temp_node->value = vl ;
	temp_node->line=line;
	temp_node->name=name ;
	return temp_node ;
}

IDTEM* create_idtem(){
	IDTEM* i ;
	i = (IDTEM*)calloc(1, sizeof(IDTEM) ) ;
	memset(i , 0 ,sizeof(IDTEM) ) ;
	return i ;
}
IDTEM* str_create_idtem(const char * str) {
	IDTEM* i ;
	char * n ;
	i = create_idtem() ;
	n = (char*)calloc(1, sizeof(strlen(str)));
	strcpy(n , str) ;
	i->name = n ;
	i->cur = i ;
	return i ;
}
IDTEM* install_id(const char * str) {
	IDTEM* item = NULL;
	if(item = cmp_item_list(idtable_head, str)){
		/*nothing*/
	}else{
		item = idtable_head ;
		while(item->next != NULL ) {
			item=item->next ;
		}
		item->next = str_create_idtem(str) ;
		item->next->previous = item ;
		item= item->next ;
	}
	return item ;
}

union myvalue itou(int y){ 
	union myvalue vl;
	vl.type_int = y ;
	return vl ;
}
union myvalue ftou(float y){
	union myvalue vl ;
	vl.type_float = y;
	return vl ;
}
union myvalue ptou(void * p){
	union myvalue vl ;
	vl.type_p = p ;
	return vl ;
}

int traverse_item_list( IDTEM*  head){
	IDTEM* item = NULL ;
	item = head->next  ;
	while(item != NULL){
		printf("name:%s,kind:%d",item->name, item->kind );
		fputc('\n',stdout);
		item= item->next ;
	}
	return  0 ;
}
IDTEM* cmp_item_list( IDTEM* head , const char * str ) { 
	IDTEM* item = NULL ;
	item = head-> next ;
	while(item != NULL){
		if(strcmp(str , item->name ) == 0 ) {
			break ;
		}
		item= item->next ;
	}
	return item ;
}
