#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "const.h"
#include "calc.yy.h"

static int analyze_def(NODE* head, enum nonterminal_enum tp);
static int warning(const char * information, long int line ) ;
static int analyze_funvar(NODE* head);

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
	}else if(ctemp == nonterminal_name[VarList]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_funvar(head);
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
			temp->parent->attr = 
			temp->attr = create_type_kind(BASIC_TYPE,int_type);
		}else if((temp->value).type_p == type_name[float_type]){
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
			(tid = temp->child_head->value.type_p)->kind = FUNCTION_KIND ;
			tid->u.funtype.ret = temp->attr ;
		}else if(tp == Def && temp->name == nonterminal_name[DecList]){
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
static int warning(const char * information , long int line){
	return fprintf(stderr, "warning at line %ld: %s\n",line , information);
}
static int analyze_funvar(NODE* head){
	
	return 0;
}
