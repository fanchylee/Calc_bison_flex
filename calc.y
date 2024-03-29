%{
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
#include "translate.h"


extern int num_lines;
extern int yylineno;
extern int yylex(void);

void yyerror (char  *);
int relop_switch(int arg1,int arg2,int arg3);
NODE *  cp_node(const char * ,NODE *  );
NODE * cp_link(const char * ,NODE *) ;
NODE * csp_node(const char * ,NODE * head , ...) ;
NODE * empty_node() ;
static int opt_tag_id(NODE* node);
static int tag_id(NODE* node);
//static int var_id(NODE* node);
static int fun_var_id(NODE* node,int kind);
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
ExtDefList:	  /*empty*/ 			{$$=empty_node(nonterminal_name[ExtDefList]) ;				}
		| ExtDef ExtDefList		{$$=csp_node(nonterminal_name[ExtDefList],$1,$2,NULL);			}
;                                                                                                
ExtDef:		  Specifier ExtDecList SEMI	{$$=csp_node(nonterminal_name[ExtDef],$1,$2,$3,NULL);			}
		| Specifier SEMI		{$$=csp_node(nonterminal_name[ExtDef],$1,$2,NULL);			}	
		| Specifier FunDec CompSt	{$$=csp_node(nonterminal_name[ExtDef],$1,$2,$3,NULL);			}
		| Specifier error		{yyerror(": Expected \";\"\n");yyerrok;					}
		| error SEMI			{yyerror(": error in Specifier\n");yyerrok;				}
		| Specifier ExtDecList error	{yyerror(": Expected \";\"\n");yyerrok;					}
;                                                                                                
ExtDecList:	  VarDec			{$$=csp_node(nonterminal_name[ExtDecList],$1,NULL);			}
		| VarDec COMMA ExtDecList 	{$$=csp_node(nonterminal_name[ExtDecList],$1,$2,$3,NULL);		}
;                                                                                                
Specifier:	  TYPE				{$$=csp_node(nonterminal_name[Specifier],$1,NULL);			}	
		| StructSpecifier		{$$=csp_node(nonterminal_name[Specifier],$1,NULL);			}
;                                                                                                
StructSpecifier:  STRUCT OptTag LC DefList RC	{$$=csp_node(nonterminal_name[StructSpecifier],$1,$2,$3,$4,$5,NULL);	}
		| STRUCT Tag			{$$=csp_node(nonterminal_name[StructSpecifier],$1,$2,NULL);		}
		| STRUCT error			{yyerror(": error in struct specifier\n");yyerrok;			}
		| STRUCT OptTag LC DefList error{yyerror(": Expected \"}\"\n");yyerrok;					}	
		
;                                                                                                
OptTag:	  /*empty*/                             {$$=empty_node(nonterminal_name[OptTag]) ;			}
		| ID				{/*opt_tag_id($1);*/$$=csp_node(nonterminal_name[OptTag],$1,NULL);	}
;
Tag:	  	  ID				{/*tag_id($1);*/$$=csp_node(nonterminal_name[Tag],$1,NULL);	}
;
 
VarDec:		  ID				{/*fun_var_id($1,VARIABLE_KIND);*/$$=csp_node(nonterminal_name[VarDec],$1,NULL);	}
		| VarDec LB INT RB		{$$=csp_node(nonterminal_name[VarDec],$1,$2,$3,$4,NULL);	}
		| VarDec LB INT error		{yyerror(": Expected \"]\"\n");yyerrok;				}
;
FunDec:		  ID LP VarList RP		{/*fun_var_id($1,FUNCTION_KIND);*/$$=csp_node(nonterminal_name[FunDec],$1,$2,$3,$4,NULL);	}
		| ID LP RP			{/*fun_var_id($1,FUNCTION_KIND);*/$$=csp_node(nonterminal_name[FunDec],$1,$2,$3,NULL);		}
		| ID LP VarList error		{yyerror(": Expected \")\" \n");yyerrok;			}
		| ID LP error			{yyerror(": Expected \")\" \n");yyerrok;			}
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
		| Specifier DecList error	{yyerror(": Expected \"; 1\"\n");yyerrok;			}
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
	| error RP		{yyerror("\n");yyerrok;						}
	| error RB		{
				yyerror(": unknown stuff before \"]\"\n");
				yyerrok;
				} 
;                                                                         
Args:	  Exp COMMA Args	{$$=csp_node(nonterminal_name[Args],$1,$2,$3,NULL);		}
	| Exp			{$$=csp_node(nonterminal_name[Args],$1,NULL);			}	
;                                
%%



int main (int ac,char *av[]){
	NODE * head;
	nul=fopen("/dev/null","w");
	if(irout = fopen(av[2],"w")){
	}else {
		perror("input file error");
		exit(EXIT_FAILURE);
	}
	if(stdin=fopen(av[1],"r")){
	}else{
		perror("input file error");
		exit(EXIT_FAILURE);
	}
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
	reset_tab();
	T_stm irtreehead ;
	if(noerror ){
		traverse_node_tree((NODE*)head,analyze);
		irtreehead = translate((NODE*)head);
#ifndef SUBMIT
		traverse_item_list(idtable_head);
#endif
		traverse_irtree_stm(irtreehead);
	}

	//free_list(idtable_head) ;
	//free_tree(head);
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
NODE * csp_node(const char * name ,NODE * ch , ...){
	NODE * p ;
	va_list ap ;
	NODE* temp ;
	p = cp_link(name,ch) ;
	va_start(ap , ch) ;
	temp=(NODE*)ch ;
	while((temp->next_sister = (NODE*)va_arg(ap , NODE *))!= NULL){
		temp->next_sister->previous_sister = temp ;
		temp = temp->next_sister ;
		temp->parent = p ;

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
static int fun_var_id(NODE* node , int kind){
	IDTEM* tid = node->value.type_p ;
	switch(tid->kind){ 
		IDTEM* newid ;
		case UNSPECIFIED:
		tid->kind = kind; 
		break;

		case STRUCTURE_KIND:
		if((newid = malloc(sizeof(IDTEM))) != NULL){
			memcpy(newid,tid,sizeof(IDTEM));
			newid->name = malloc(strlen(tid->name)+1);
			strcpy(newid->name , tid->name );
			newid->cur = newid ;
			newid->kind = kind ;
			newid->next = ((IDTEM*)(node->value.type_p))->next;
			if(newid->next != NULL){
				newid->next->previous = newid ;
			}
			newid->previous = node->value.type_p ;
			((IDTEM*)(node->value.type_p))->next = newid ;
			node->value.type_p = newid ;
		}else{
			perror("null pointer");
			exit(EXIT_FAILURE);
		}
		break ;

		default:
		break;
	}
	return 0;
}

static int tag_id(NODE* node){
	IDTEM* tid = node->value.type_p ;
	if(tid->kind == STRUCTURE_KIND){
	}else if(tid->next != NULL && tid->next->kind == STRUCTURE_KIND){
		node->value.type_p = tid->next ;
	}else{
		error("undefined structure",17,node->line);
	}
	
	return 0;
}
static int opt_tag_id(NODE* node){
	IDTEM* tid = node->value.type_p ;
	switch(tid->kind){ 
		IDTEM* newid ;
		case UNSPECIFIED:
		break;
	
		case STRUCTURE_KIND:
		error("structure redefined",16,node->line);
		break;
		
		default:
//		error("symbol redefined as a structure",16,node->line);
		if((newid = malloc(sizeof(IDTEM))) != NULL){
			memcpy(newid,tid,sizeof(IDTEM));
			newid->cur = newid ;
			newid->kind = STRUCTURE_KIND ;
			newid->next = ((IDTEM*)(node->value.type_p))->next;
			if(newid->next != NULL){
				newid->next->previous = newid ;
			}
			newid->previous = node->value.type_p ;
			((IDTEM*)(node->value.type_p))->next = newid ;
			node->value.type_p = newid ;
		}else{
			perror("null pointer");
			exit(EXIT_FAILURE);
		}
		break ;
	}
	return 0;
}
int traverse_node_tree(NODE* head ,int (*action)(NODE*)){
	char * temp;
	if(head->line==0)goto recursive;
#ifndef SUBMIT
	fputs(tab,stdout);
#endif
	(*action)(head);
recursive:
	if(head->child_head != NULL){
		tab = realloc(tab,strlen(tab)+3);
		strcat(tab,"  ");
		traverse_node_tree(head->child_head,action);//here to recurse
		temp = tab ;
		tab=(char *)malloc(strlen(tab));
		strcpy(tab,temp+2);
		free(temp);
	}
	if(head->next_sister != NULL){
		traverse_node_tree(head->next_sister,action);//here to recurse
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
