%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <signal.h>

#include "struct.h"
#include "relop.h"
#include "global.h"
#include "const.h"
#include "type.h"

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

%}

/* declared types */
%token			WHILE IF RETURN STRUCT TYPE COMMA SEMI LC RC 
%nonassoc		LOWER_THAN_ELSE
%nonassoc		ELSE
%token 			INT
%token 			FLOAT
%token 			ID
%right			ASSIGNOP
%left			OR
%left			AND 
%left 			RELOP
%left			PLUS MINUS
%left			STAR DIV
%right			NEG NOT 
%left			LP RP LB RB  DOT

%%

Program:	ExtDefList			{
							$$=csp_node(nonterminal_name[Program],$1 , NULL) ;	
							node_head = $$ ;
							YYACCEPT;
						}
;                                                                                                
ExtDefList:	  /*empty*/ 			{$$=empty_node(nonterminal_name[ExtDefList]) ;			}
		| ExtDef ExtDefList		{$$=csp_node(nonterminal_name[ExtDefList],$1,$2,NULL);		}
;                                                                                                
ExtDef:		  Specifier ExtDecList SEMI	{$$=csp_node(nonterminal_name[ExtDef],$1,$2,$3,NULL);		}
		| Specifier SEMI		{$$=csp_node(nonterminal_name[ExtDef],$1,$2,NULL);		}	
		| Specifier FunDec CompSt	{$$=csp_node(nonterminal_name[ExtDef],$1,$2,$3,NULL);		}
		| Specifier error		{yyerror(": Expected \";\"\n");yyerrok;		}
		| error SEMI			{yyerror(": error in Specifier\n");yyerrok;	}
		| Specifier ExtDecList error	{yyerror(": Expected \";\"\n");yyerrok;		}
;                                                                                                
ExtDecList:	  VarDec			{$$=csp_node(nonterminal_name[ExtDecList],$1,NULL);		}
		| VarDec COMMA ExtDecList 	{$$=csp_node(nonterminal_name[ExtDecList],$1,$2,$3,NULL);	}
;                                                                                                
                                                                                                 
Specifier:	  TYPE				{$$=csp_node(nonterminal_name[Specifier],$1,NULL);			}	
		| StructSpecifier		{$$=csp_node(nonterminal_name[Specifier],$1,NULL);			}
;                                                                                                
StructSpecifier:  STRUCT OptTag LC DefList RC	{$$=csp_node(nonterminal_name[StructSpecifier],$1,$2,$3,$4,$5,NULL);	}
		| STRUCT Tag			{$$=csp_node(nonterminal_name[StructSpecifier],$1,$2,NULL);		}
		| STRUCT error			{yyerror(": error in struct specifier\n");yyerrok;	}
		| STRUCT OptTag LC DefList error{yyerror(": Expected \"}\"\n");yyerrok;		}	
		
;                                                                                                
OptTag:	  /*empty*/                             {$$=empty_node(nonterminal_name[OptTag]) ;			}                                                
		| ID				{$$=csp_node(nonterminal_name[OptTag],$1,NULL);			}
;
Tag:	  	  ID				{$$=csp_node(nonterminal_name[Tag],$1,NULL);			}
;
 
VarDec:		  ID				{$$=csp_node(nonterminal_name[VarDec],$1,NULL);			}
		| VarDec LB INT RB		{$$=csp_node(nonterminal_name[VarDec],$1,$2,$3,$4,NULL);	}
		| VarDec LB INT error		{yyerror(": Expected \"]\"\n");yyerrok;		}
;
FunDec:		  ID LP VarList RP		{$$=csp_node(nonterminal_name[FunDec],$1,$2,$3,$4,NULL);	}	
		| ID LP RP			{$$=csp_node(nonterminal_name[FunDec],$1,$2,$3,NULL);		}
		| ID LP VarList error		{yyerror(": Expected \")\" \n");yyerrok;	}
		| ID LP error			{yyerror(": Expected \")\" \n");yyerrok;	}
;
VarList:	  ParamDec COMMA VarList	{$$=csp_node(nonterminal_name[VarList],$1,$2,$3,NULL);		}
		| ParamDec			{$$=csp_node(nonterminal_name[VarList],$1,NULL);		}
;                                                                                                
ParamDec:	  Specifier VarDec		{$$=csp_node(nonterminal_name[ParamDec],$1,$2,NULL);		}
;                                                                                                
                                                                                                 
CompSt:		  LC DefList StmtList RC	{$$=csp_node(nonterminal_name[CompSt],$1,$2,$3,$4,NULL);	}
		| error DefList StmtList RC	{yyerror(": Expected \"{\"\n");yyerrok;		}
;                                                                                          
StmtList: /*empty */				{$$=empty_node(nonterminal_name[StmtList]) ;			}                                                
		| Stmt StmtList			{$$=csp_node(nonterminal_name[StmtList],$1,$2,NULL);		}
;                                                                                                
Stmt:		  Exp SEMI			{$$=csp_node(nonterminal_name[Stmt],$1,$2,NULL);		}
		| CompSt			{$$=csp_node(nonterminal_name[Stmt],$1,NULL);			}
		| RETURN Exp SEMI		{$$=csp_node(nonterminal_name[Stmt],$1,$2,$3,NULL);		}
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE	{$$=csp_node(nonterminal_name[Stmt],$1,$2,$3,$4,$5,NULL);	}
		| IF LP Exp RP Stmt ELSE Stmt	{$$=csp_node(nonterminal_name[Stmt],$1,$2,$3,$4,$5,$6,$7,NULL);	}
		| WHILE LP Exp RP Stmt		{$$=csp_node(nonterminal_name[Stmt],$1,$2,$3,$4,$5,NULL);	}
		| error SEMI			{	
						yyerror(": unknown statement before \";\"\n");
						yyerrok;
						}
		| IF LP Exp error Stmt ELSE Stmt{yyerror(": Expected \")\" \n");yyerrok;	}
		| IF error Exp RP Stmt ELSE Stmt{yyerror(": Expected \"(\" \n");yyerrok;	}
		| Exp error			{yyerror(": Expected \";\"\n");yyerrok;		}
		| RETURN Exp error		{yyerror(": Expected \";\" \n");yyerrok;	}
;                                                                                                
DefList:  /* empty*/				{$$=empty_node(nonterminal_name[DefList]) ;			}
		| Def DefList			{$$=csp_node(nonterminal_name[DefList],$1,$2,NULL);		}
;
Def:		  Specifier DecList SEMI	{$$=csp_node(nonterminal_name[Def],$1,$2,$3,NULL);		}
		| Specifier DecList error	{yyerror(": Expected \"; 1\"\n");yyerrok;	}
;                                                                                                
DecList:	  Dec				{$$=csp_node(nonterminal_name[DecList],$1,NULL);		}
		| Dec COMMA DecList		{$$=csp_node(nonterminal_name[DecList],$1,$2,$3,NULL);		}
;                                                                                                
Dec:		  VarDec			{$$=csp_node(nonterminal_name[Dec],$1,NULL);			}
		| VarDec ASSIGNOP Exp		{$$=csp_node(nonterminal_name[Dec],$1,$2,$3,NULL);		}
;

Exp:	  ID			{$$=cp_node(nonterminal_name[Exp],$1) ;				}
	| INT			{$$=cp_node(nonterminal_name[Exp],$1);				}
	| FLOAT			{$$=cp_node(nonterminal_name[Exp],$1);				}
	| Exp AND Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp OR Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp PLUS Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp MINUS Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp STAR Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp DIV Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| MINUS Exp  %prec NEG	{$$=csp_node(nonterminal_name[Exp],$1,$2,NULL);			}
	| LP Exp RP		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp RELOP Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| NOT Exp		{$$=csp_node(nonterminal_name[Exp],$1,$2,NULL);			}
	| Exp LB Exp RB		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,$4,NULL);		}
	| Exp ASSIGNOP Exp	{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| ID LP RP		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| Exp DOT ID		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,NULL);		}
	| ID LP Args RP		{$$=csp_node(nonterminal_name[Exp],$1,$2,$3,$4,NULL);		}
	| error RP		{yyerror("\n");yyerrok;				}
	| error RB		{
				yyerror(": unknown stuff before \"]\"\n");
				yyerrok;
				} 
;                                                                         
Args:	  Exp COMMA Args	{$$=csp_node(nonterminal_name[Args],$1,$2,$3,NULL);		}
	| Exp			{$$=csp_node(nonterminal_name[Args],$1,NULL);			}	
;                                
%%


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
	printf(tab);
	if(head->name == terminal_name[ID-WHILE]){
		printf("%s:%s\n",head->name , ((IDTEM*)(head->value).type_p)->name);
		if(head->parent->name == nonterminal_name[FunDec]){
			
		}else if(head->parent->name == nonterminal_name[VarDec]){
		}else if(head->parent->name == nonterminal_name[Tag]){
		}else if(head->parent->name == nonterminal_name[OptTag]){
		}else{
		}
	}else if(head->name == terminal_name[TYPE-WHILE]){
		printf("%s: %s\n",head->name,(char *)(head->value).type_p) ;
		if(strcmp((char*)(head->value).type_p,"int")){
			((head->parent->next_sister->child_head)->value).type_p = basic_create_type(int_type);
		}else if(strcmp((char*)(head->value).type_p,"float")){
			(head->value).type_p = basic_create_type(float_type);
		}else{
			perror("calc.y:249,error");
			exit(EXIT_FAILURE);
		}
	}else if(head->name == terminal_name[FLOAT-WHILE]){
		printf("%s: %f\n",head->name,(head->value).type_float) ;
	}else if(head->name == terminal_name[INT-WHILE]){
		printf("%s: %d\n",head->name,(head->value).type_int);
	}else{
		printf("%s (%d)\n",head->name,head->line);
	}
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
		fprintf(stderr,msg);
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
