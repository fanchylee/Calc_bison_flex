#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "const.h"
#include "calc.yy.h"

static int analyze_def(NODE* head, enum nonterminal_enum tp);

int analyze(NODE* head){
	const char * ctemp ;
	if((ctemp = head->name) == terminal_name[ID-WHILE]){
		printf("%s: %s\n",head->name , ((IDTEM*)(head->value).type_p)->name);
/*
		if(head->parent->name == nonterminal_name[FunDec]){
			
		}else if(head->parent->name == nonterminal_name[VarDec]){
		}else if(head->parent->name == nonterminal_name[Tag]){
		}else if(head->parent->name == nonterminal_name[OptTag]){
		}else{
		}
*/
	}else if(ctemp == terminal_name[TYPE-WHILE]){
		printf("%s: %s\n",head->name,(char *)(head->value).type_p) ;
/*
		if(strcmp((char*)(head->value).type_p,"int")){
			((IDTEM*)(((head->parent->next_sister->child_head)->value)
			.type_p))->type = basic_create_type(int_type);
		}else if(strcmp((char*)(head->value).type_p,"float")){
			(head->value).type_p = basic_create_type(float_type);
		}else{
			perror("calc.y:249,error");
			exit(EXIT_FAILURE);
		}
*/
	}else if(ctemp == terminal_name[FLOAT-WHILE]){
		printf("%s: %f\n",head->name,(head->value).type_float) ;
	}else if(ctemp == terminal_name[INT-WHILE]){
		printf("%s: %d\n",head->name,(head->value).type_int);
	}else if(ctemp == nonterminal_name[ExtDef]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ExtDef);
	}else if(ctemp == nonterminal_name[Def]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ExtDef);
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
		}else if((temp->value).type_p == type_name[float_type]){
		}else{
			perror("unknown error :4");
			exit(EXIT_FAILURE);
		}
	}else if(ctemp == nonterminal_name[StructSpecifier]){
		const char * ctemp ;
		if((ctemp = head->child_head->child_head->child_head->next_sister->name) == nonterminal_name[OptTag]){
			const char * ctemp ;
			if((ctemp = head->child_head->child_head->child_head->next_sister->child_head->name ) == NULL){
			}else if(ctemp == terminal_name[ID]){
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
