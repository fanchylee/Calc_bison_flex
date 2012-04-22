#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "const.h"
#include "calc.yy.h"
#include "global.h"

static int analyze_def(NODE* head, enum nonterminal_enum tp);
static int warning(const char * information, long int line ) ;
static int analyze_funvar(NODE* head);
static int analyze_extdeclist(NODE* head);
static int analyze_vardec(NODE* head);
int error(const char * info , int type ,long int line) ;
static int addvar(int kind,IDTEM* tid,NODE* head);
static void allowoverlap(IDTEM * head);

int analyze(NODE* head){
	const char * ctemp ;
	int depth ;
	if((ctemp = head->name) == terminal_name[ID-WHILE]){
		printf("%s: %s\n",head->name , ((IDTEM*)(head->value).type_p)->name);
	}else if(ctemp == terminal_name[TYPE-WHILE]){
		printf("%s: %s\n",head->name,(char *)(head->value).type_p) ;
	}else if(ctemp == terminal_name[FLOAT-WHILE]){
		printf("%s: %f\n",head->name,(head->value).type_float) ;
	}else if(ctemp == terminal_name[INT-WHILE]){
		printf("%s: %d\n",head->name,(head->value).type_int);
	}else if(ctemp == nonterminal_name[ExtDef]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ExtDef);
	}else if(ctemp == nonterminal_name[Def]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,Def);
	}else if(ctemp == nonterminal_name[ExtDecList]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_extdeclist(head);
	}else if(ctemp == nonterminal_name[VarList]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_funvar(head);
	}else if(ctemp == nonterminal_name[VarDec]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_vardec(head);
	}else if(ctemp == nonterminal_name[ParamDec]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ParamDec);
	}else{
		printf("%s (%ld)\n",head->name,head->line);
	}
	return 0;
}
static int analyze_def(NODE* head, enum nonterminal_enum tp){
	const char * ctemp ;
	if((ctemp = head->child_head->child_head->name) == terminal_name[TYPE - WHILE] ){
		NODE* temp = head->child_head->child_head ;
		if((temp->value).type_p == type_name[int_type]){
			temp->parent->parent->attr =
			temp->parent->attr = 
			temp->attr = create_type_kind(BASIC_TYPE,int_type);
		}else if((temp->value).type_p == type_name[float_type]){
			temp->parent->parent->attr =
			temp->parent->attr = 
			temp->attr = create_type_kind(BASIC_TYPE,float_type);
		}else{
			perror("unknown error :4");
			exit(EXIT_FAILURE);
		}
		temp = head->child_head->next_sister ;
		if(tp == ExtDef && temp->name == terminal_name[SEMI - WHILE] ){
			warning("useless type name in empty declaration", temp->parent->line);
		}else if(tp == ExtDef && temp->name == nonterminal_name[ExtDecList] ){
			temp->attr = temp->previous_sister->attr ;
		}else if(tp == ExtDef && temp->name == nonterminal_name[FunDec]){
			IDTEM* tid;
			temp->attr = temp->previous_sister->attr ;
			tid = temp->child_head->value.type_p;
			if(tid->overlap == DISALLOW &&
			tid->kind != STRUCTURE_KIND){
				error("Symbol redeclared as function",4,temp->line);
			}else{
				tid->kind = FUNCTION_KIND ;
				tid->u.funtype.ret = temp->attr ;
				tid->overlap = DISALLOW ;
			}
		}else if(tp == Def && temp->name == nonterminal_name[DecList]){
			temp->attr = temp->previous_sister->attr ;
		}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
			temp->attr = temp->previous_sister->attr ;
		}else{
			perror("unknown error: analyze.c:74");
			exit(EXIT_FAILURE);
		}
	}else if(ctemp == nonterminal_name[StructSpecifier]){
		const char * ctemp ;
		if((ctemp = head->child_head->child_head->child_head->next_sister->name) == nonterminal_name[OptTag]){
			NODE* temp ;
			if((temp = head->child_head->child_head->child_head->next_sister)->child_head  == NULL){//anonymous struct
				const char * ctemp = head->child_head->next_sister->name;
				if(tp == ExtDef && ctemp == terminal_name[SEMI-WHILE] ){
					warning("unnamed struct that defines no instances", temp->parent->line);
				}else if(tp == ExtDef && ctemp == nonterminal_name[ExtDecList] ){
				}else if(tp == ExtDef && ctemp == nonterminal_name[FunDec]){
					NODE* temp = head->child_head->next_sister->child_head ;//fun id
					
				}else if(tp == Def && ctemp == nonterminal_name[DecList]){
				}else{
					perror("unknown error : anonymous struct");
					exit(EXIT_FAILURE);
				}
			}else if(temp->child_head->name == terminal_name[ID-WHILE]){
			}else{
				perror("unknown error :3");
				exit(EXIT_FAILURE);
			}
		}else if(ctemp == nonterminal_name[Tag]){
			NODE* temp = head->child_head->child_head->child_head->next_sister->child_head ;//ID
			
		}else {
			perror("unknown error :2");
			exit(EXIT_FAILURE);
		}
	}else {
		perror("unknown error :1");
		exit(EXIT_FAILURE);
	}
	return 0;
}
static int analyze_funvar(NODE* head){
	allowoverlap(idtable_head);
	return 0;
}
static int analyze_extdeclist(NODE* head){
	head->attr = head->parent->attr ;
	return 0 ;
}
static int analyze_vardec(NODE* head){
	NODE* temp;
	IDTEM* tid ;
	int kind ;
	if((temp = head->parent)->name == nonterminal_name[VarDec]){
		int size ;
		size = head->next_sister->next_sister->value.type_int ;
		head->attr = create_type_kind(ARRAY_TYPE,head->parent->attr,size);
		kind = VARIABLE_KIND;
	}else if(temp->name == nonterminal_name[Dec]){
		head->attr = head->parent->attr ;
		temp = temp->parent->parent->parent ;
		while((temp=temp->parent)->name == nonterminal_name[DefList]){}
		if(temp->name == nonterminal_name[StructSpecifier]){
			kind = STRUCTUREFIELD_KIND;
		}else{
			kind = VARIABLE_KIND;
		}
	}else {
		head->attr = head->parent->attr ;
		kind = VARIABLE_KIND ;
	}
	if((temp = head->child_head)->name == terminal_name[ID - WHILE]){
		tid = temp->value.type_p;
		addvar(kind,tid,head);
/*
		switch(tid->kind){
			case STRUCTURE_KIND:
			addvar(kind,tid,head);
			break ;
			
			case VARIABLE_KIND:
			case STRUCTUREFIELD_KIND:
			case FUNCTION_KIND:
				switch(tid->overlap){
			 	case DISALLOW :
				error("Symbol redeclared as variable",3,temp->line);
				break;

				case UNSPECIFIED:
				case ALLOW:
				addvar(kind,tid,head);
				break;
				
				default:
				perror("unknown error :unknown id kind");
				exit(EXIT_FAILURE);
				break;
			}
		}
*/
	}
	return 0;
}
static void allowoverlap(IDTEM * head){
	if(head == NULL){return;}else{
		allowoverlap(head->next);
	}
	if(head->overlap == DISALLOW){
		head->overlap = ALLOW ;
	}
}
static addvar(int kind,IDTEM* tid,NODE* head){
	if(tid->kind == STRUCTURE_KIND){
		perror("unknown error :here cannot be structure");
		exit(EXIT_FAILURE);
	}
	switch(tid->overlap){
		IDTEM* newid ;
		case ALLOW:
		newid = malloc(sizeof(IDTEM));
		tid->overlap = DISALLOW;
		memcpy(newid,tid,sizeof(IDTEM));
		tid->next = tid->previous = NULL;
		tid = newid ;
		case UNSPECIFIED:
		tid->overlap = DISALLOW ;
		tid->kind = kind ;
		switch(kind){  
			case VARIABLE_KIND:
			tid->u.t = head->attr ;
			break ;

			case STRUCTUREFIELD_KIND:
			tid->u.structurefieldtype.t = head->attr ;
			//TODO  structurefieldtype.structure 
			break ;

			default:
			perror("unknown error :unknown kind");
			exit(EXIT_FAILURE);
			break ;
		}
		break;
		
		
		case DISALLOW:
		error("Symbol redeclared as variable",3,head->child_head->line);
		break;
		
		default:
		perror("unknown error :unknown overlap state");
		exit(EXIT_FAILURE);
		break;
	}
}
static int warning(const char * information , long int line){
	return fprintf(stderr, "warning at line %ld: %s\n",line , information);
}
int error(const char * info , int type ,long int line){
	return fprintf(stdout,"Error type %d at line %ld: %s\n",type,line,info);
}
