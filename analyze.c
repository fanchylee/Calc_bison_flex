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
static int analyze_varlist(NODE* head);
static int analyze_dec_extdeclist(NODE* head);
static int analyze_vardec(NODE* head);
static void analyze_basictype(NODE* );
static int analyze_opttag(NODE * opt_tag_tag,enum nonterminal_enum tp);
static int analyze_tag(NODE * tag,enum nonterminal_enum tp);
int error(const char * info , int type ,long int line) ;
static int addvar(int kind,NODE* idnode);
static int addfunc(NODE * fun);
static void allowoverlap(IDTEM * head);
static void disallowoverlap(IDTEM * head);
static void setcur(IDTEM * cur);
static int addstruct(NODE* idnode);
static int process_def(NODE * temp, enum nonterminal_enum tp );
static int pass_attr_null_opttag(NODE * opt, Type* type);
static int pass_attr_id_opttag(NODE * opt, Type* type);

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
	}else if(ctemp == terminal_name[LC - WHILE]){
		printf("%s (%ld)\n",head->name,head->line);
		if(head->parent->previous_sister != NULL){
		}else{
			allowoverlap(idtable_head);
		}
	}else if(ctemp == terminal_name[RC - WHILE]){
		printf("%s (%ld)\n",head->name,head->line);
		disallowoverlap(idtable_head);
	}else if(ctemp == nonterminal_name[ExtDef]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ExtDef);
	}else if(ctemp == nonterminal_name[Def]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,Def);
	}else if(ctemp == nonterminal_name[DecList] || ctemp == nonterminal_name[ExtDecList]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_dec_extdeclist(head);
	}else if(ctemp == terminal_name[LP - WHILE]){
		printf("%s (%ld)\n",head->name,head->line);
		if(head->parent->name == nonterminal_name[FunDec]){
			allowoverlap(idtable_head);
		}
	}else if(ctemp == nonterminal_name[VarDec]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_vardec(head);
	}else if(ctemp == nonterminal_name[ParamDec]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_def(head,ParamDec);
	}else if(ctemp == nonterminal_name[VarList]){
		printf("%s (%ld)\n",head->name,head->line);
		analyze_varlist(head);
	}else {
		printf("%s (%ld)\n",head->name,head->line);
	}
	return 0;
}
static int analyze_def(NODE* head, enum nonterminal_enum tp){
	const char * ctemp ;
	if((ctemp = head->child_head->child_head->name) == terminal_name[TYPE - WHILE] ){
		NODE* temp = head->child_head->child_head ;//TYPE node
		analyze_basictype(temp);
		temp = head->child_head->next_sister ;//SEMI or ExtDecList or FunDec or DecList or VarDec
		process_def(temp ,tp);
	}else if(ctemp == nonterminal_name[StructSpecifier]){
		const char * ctemp = head->child_head->child_head->child_head->next_sister->name;
		NODE* temp = head->child_head->child_head->child_head->next_sister ;//OptTag or tag
		if(ctemp == nonterminal_name[OptTag]){
			NODE* temp = head->child_head->child_head->child_head->next_sister;//OptTag
			analyze_opttag(temp,tp);
		}else if(ctemp == nonterminal_name[Tag]){
			NODE* temp = head->child_head->child_head->child_head->next_sister->child_head ;//ID
			analyze_tag(temp,tp);
		}else {
			perror("unknown error :2");
			exit(EXIT_FAILURE);
		}
		temp = head->child_head->next_sister ;//SEMI or ExtDecList or FunDec or DecList or VarDec
		process_def(temp,tp);
	}else {
		perror("unknown error :1");
		exit(EXIT_FAILURE);
	}
	return 0;
}

static int analyze_dec_extdeclist(NODE* head){
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
		while((temp=temp->parent)->name == nonterminal_name[DecList]){}
		temp = temp->parent ;//
		while((temp=temp->parent)->name == nonterminal_name[DefList]){}
		if(temp->name == nonterminal_name[StructSpecifier]){
			Type* structuretype ;
			kind = STRUCTUREFIELD_KIND;
			structuretype =  temp->attr ;//get structure type from StructSpecifier
			if(head->child_head->name == terminal_name[ID - WHILE]){
				NODE* temp = head->child_head;
				temp->attr = structuretype ;//ID attr get structure type from StructSpecifier
			}
		}else if(temp->name == nonterminal_name[CompSt]){
			kind = VARIABLE_KIND;
		}else {
			perror("unknown error :impossible in analyze_vardec");
			exit(EXIT_FAILURE);
		}
	}else if(temp->name == nonterminal_name[ExtDecList]){
		head->attr = head->parent->attr ;
		kind = VARIABLE_KIND ;
	}else if(temp->name == nonterminal_name[ParamDec]){
		IDTEM * funid = head->parent->parent->value.type_p;
		head->attr = head->parent->attr ;//
		kind = VARIABLE_KIND ;
		if(funid->kind == FUNCTION_KIND){//determine the varlist type
			if(funid->u.funtype.varhead == NULL){
				funid->u.funtype.varhead = malloc(sizeof(FieldList));
				memset(funid->u.funtype.varhead,0,sizeof(FieldList));
				funid->u.funtype.varhead->type = tid->u.structurefieldtype.t ;
				funid->u.funtype.varhead->name = malloc(strlen(funid->name)+1) ;
				strcpy(funid->u.funtype.varhead->name,tid->name);
			}else{
				FieldList* fieldlist = funid->u.funtype.varhead ;
				if(fieldlist->tail != NULL){
					fieldlist = fieldlist->tail ;
				}
				fieldlist->tail = malloc(sizeof(FieldList));
				memset(fieldlist->tail,0,sizeof(FieldList));
				fieldlist->tail->type = tid->u.structurefieldtype.t ;
				fieldlist->tail->name = malloc(strlen(tid->name)+1) ;
				strcpy(fieldlist->tail->name,tid->name);
			}
		}
	}
	if((temp = head->child_head)->name == terminal_name[ID - WHILE]){
		addvar(kind,temp);
	}
	return 0;
}
static void allowoverlap(IDTEM * head){
	if(head == NULL){return;}else{
		allowoverlap(head->next);
		allowoverlap(head->forward);
	}
	if(head->overlap != UNSPECIFIED){
		head->overlap += 1 ;
	}
}
static void disallowoverlap(IDTEM * head){
	if(head == NULL){return ;}else{
		disallowoverlap(head->next);
		disallowoverlap(head->forward);
	}
	if(head->overlap == DISALLOW){
		if(head->forward != NULL){
		}else{
			head->forward = malloc(sizeof(IDTEM));
			memset(head->forward,0,sizeof(IDTEM));
			head->forward->backward = head ;
			head->forward->name = malloc(strlen(head->name)+1);
			strcpy(head->forward->name ,head->name);
			head->forward->overlap = UNSPECIFIED ;
		}
		if(head->previous != NULL)
			head->previous->next = head->forward ;
		if(head->next != NULL)
			head->next->previous = head->forward ;
		head->forward->previous = head->previous ;
		head->forward->next = head->next ;

		head->previous = head->next = NULL ;
		setcur(head->forward);
	}
	if(head->overlap != UNSPECIFIED){
		head->overlap -= 1;
	}
}
static addvar(int kind,NODE* idnode){
	IDTEM* tid = ((IDTEM*)idnode->value.type_p)->cur ;
	NODE* head = idnode->parent ;
	switch(tid->overlap){
		IDTEM* newid ;
		case ALLOW:
		newid = malloc(sizeof(IDTEM));
		memcpy(newid,tid,sizeof(IDTEM));
		newid->cur = newid ;
		if(newid->next != NULL)
			newid->next->previous = newid ;
		if(newid->previous != NULL)
			newid->previous->next = newid ;
		tid->next = tid->previous = NULL;
		tid->backward = newid ;
		newid->forward = tid ;
		tid = newid ;
		setcur(newid);
		case UNSPECIFIED:
		tid->overlap = DISALLOW ;
		tid->kind = kind ;
		switch(kind){  
			case VARIABLE_KIND:
			tid->u.t = head->attr ;	
			break ;

			case STRUCTUREFIELD_KIND:
			if(head->next_sister == NULL){
			}else if(head->next_sister->name == terminal_name[ASSIGNOP - WHILE]){
				error("initialize a field of a struct",15,idnode->line);
				break ;
			}else{
				perror("unknown error: impossible nest_sister in addvar");
				exit(EXIT_FAILURE);
			}
			tid->u.structurefieldtype.structure = idnode->attr ;
			tid->u.structurefieldtype.t =  head->attr;
			{
				Type* structuretype = idnode->attr ;
				if(structuretype->u.structure == NULL){
					structuretype->u.structure = malloc(sizeof(FieldList));
					memset(structuretype->u.structure,0,sizeof(FieldList));
					structuretype->u.structure->type = tid->u.structurefieldtype.t ;
					structuretype->u.structure->name = malloc(strlen(tid->name)+1) ;
					strcpy(structuretype->u.structure->name,tid->name);
				}else{
					FieldList* fieldlist = structuretype->u.structure ;
					if(fieldlist->tail != NULL){
						fieldlist = fieldlist->tail ;
					}
					fieldlist->tail = malloc(sizeof(FieldList));
					memset(fieldlist->tail,0,sizeof(FieldList));
					fieldlist->tail->type = tid->u.structurefieldtype.t ;
					fieldlist->tail->name = malloc(strlen(tid->name)+1) ;
					strcpy(fieldlist->tail->name,tid->name);
				}
			}
			break ;

			default:
			perror("unknown error :unknown kind");
			exit(EXIT_FAILURE);
			break ;
		}
		break;
		
		
		case DISALLOW:
		if(kind == VARIABLE_KIND){
			error("Symbol redeclared as variable",3,head->child_head->line);
		}else if(kind == STRUCTUREFIELD_KIND){
			error("Symbol redeclared as variable in a struct defination",15,head->child_head->line);
		}
		break;
		
		default:
		perror("unknown error :unknown overlap state");
		exit(EXIT_FAILURE);
		break;
	}
}
static void setcur(IDTEM * cur){
	IDTEM * ttid = cur ;
	ttid->cur = cur ;
	while((ttid = ttid->forward) != NULL){
		ttid->cur = cur ;
	}
	ttid = cur ;
	while((ttid = ttid->backward) != NULL){
		ttid->cur = cur ;
	}
}

static void analyze_basictype(NODE * temp){
	if((temp->value).type_p == type_name[int_type]){
		temp->parent->parent->attr = //extdef or def
		temp->parent->attr = //specifier
		temp->attr = create_type_kind(BASIC_TYPE,int_type);
	}else if((temp->value).type_p == type_name[float_type]){
		temp->parent->parent->attr =
		temp->parent->attr = 
		temp->attr = create_type_kind(BASIC_TYPE,float_type);
	}else{
		perror("unknown error :4");
		exit(EXIT_FAILURE);
	}
}
static int addfunc(NODE * fun){//determine the return type,the varlist type determined in analyze_vardec
	IDTEM * tid = fun->value.type_p;//ID
	Type * stype = fun->attr;
	tid = tid->cur ;
	if(tid->overlap == DISALLOW ){
		error("Symbol redeclared as function",4,fun->line);
	}else if(tid->overlap == UNSPECIFIED){
		tid->kind = FUNCTION_KIND ;
		tid->u.funtype.ret = stype ;
		tid->overlap = DISALLOW ;
	}else{
		perror("unknown error :impossible overlap state in addfunc");
		exit(EXIT_FAILURE);
	}
	return 0;
}
static int addstruct(NODE* idnode){
	IDTEM * id = idnode->value.type_p ;
	Type * stype = idnode->attr;
	id = id->cur ;
	if(id->overlap == DISALLOW){
		error("redefined as structure",16,idnode->line);
	}else if(id->overlap == UNSPECIFIED){
		id->kind = STRUCTURE_KIND;
		id->u.structuretype.t = stype ;
		id->overlap = DISALLOW ;
	}else{
		perror("unknown error :impossible overlap state in addstruct");
		exit(EXIT_FAILURE);
	}
	return 0;
}
static int analyze_tag(NODE* IDnode,enum nonterminal_enum tp){
	IDTEM * tid = IDnode->value.type_p ;
	tid = tid->cur ;
	if(tid->kind != STRUCTURE_KIND){
		error("undefined struct",17,IDnode->line);
		return 1;
	}else{
		Type* structuretype = tid->u.structuretype.t ;
		pass_attr_id_opttag(IDnode->parent->parent->parent->next_sister,structuretype);
	}
	return 0;
}
static int analyze_opttag(NODE * opt_tag_tag, enum nonterminal_enum tp){
	if(opt_tag_tag->child_head  == NULL){//anonymous struct
		NODE* temp = opt_tag_tag->parent->parent->next_sister ;//head->child_head->next_sister;//
		const char * ctemp = temp->name ;
		if(tp == ExtDef && ctemp == terminal_name[SEMI-WHILE] ){
			warning("unnamed struct that defines no instances", temp->parent->line);
		}else if(tp == ExtDef && ctemp == nonterminal_name[ExtDecList] ){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
		}else if(tp == ExtDef && ctemp == nonterminal_name[FunDec]){
			NODE* ttemp = temp->parent->child_head->next_sister->child_head ;//fun id
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
		}else if(tp == Def && ctemp == nonterminal_name[DecList]){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
		}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
		}else{
			perror("unknown error : anonymous struct");
			exit(EXIT_FAILURE);
		}
	}else if(opt_tag_tag->child_head->name == terminal_name[ID-WHILE]){
		NODE* temp = opt_tag_tag->parent->parent->next_sister ;//head->child_head->next_sister;//
		const char * ctemp = temp->name ;
		if(tp == ExtDef && ctemp == terminal_name[SEMI-WHILE] ){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == ExtDef && ctemp == nonterminal_name[ExtDecList] ){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == ExtDef && ctemp == nonterminal_name[FunDec]){
			NODE* ttemp = temp->parent->child_head->next_sister->child_head ;//fun id
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == Def && ctemp == nonterminal_name[DecList]){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
			/*ignore ID*/
		}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL));
		}else{
			perror("unknown error : anonymous struct");
			exit(EXIT_FAILURE);
		}
	}else{
		perror("unknown error :3");
		exit(EXIT_FAILURE);
	}
	

	return 0;
}
static int analyze_varlist(NODE* head){
	NODE* temp = head->previous_sister->previous_sister ;
	if(temp->name == terminal_name[ID - WHILE]){
		head->value.type_p = temp->value.type_p ;//varlist get idtem from fun id
	}else if(temp->name == nonterminal_name[ParamDec]){
		head->value.type_p = head->parent->value.type_p ;//varlist get idtem from parent varlist
	}else{
		perror("unknown error :varlist process error");
		exit(EXIT_FAILURE);
	}
	return 0;
}

static int process_def(NODE * temp, enum nonterminal_enum tp ){
	if(tp == ExtDef && temp->name == terminal_name[SEMI - WHILE] ){
///		warning("useless type name in empty declaration", temp->parent->line);
	}else if(tp == ExtDef && temp->name == nonterminal_name[ExtDecList] ){
		temp->parent->attr = temp->attr = temp->previous_sister->attr ;//ExtDef and ExtDecList get attribution form specifier
	}else if(tp == ExtDef && temp->name == nonterminal_name[FunDec]){
		IDTEM* tid;
		temp->child_head->attr = temp->attr = temp->previous_sister->attr ; //FunDec and ID get attr from specifier
		addfunc(temp->child_head);//the function ID node
	}else if(tp == Def && temp->name == nonterminal_name[DecList]){
		temp->child_head->attr = temp->parent->attr = temp->attr = temp->previous_sister->attr ;//DecList and Def and Dec get attr from apecifier
	}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
		temp->parent->attr = temp->attr = temp->previous_sister->attr ;//ParamDec and VarDec get attr from Specifier
		temp->value.type_p = temp->parent->parent->value.type_p ;//VarDec get value from varlist 
	}else{
		perror("unknown error: analyze.c:74");
		exit(EXIT_FAILURE);
	}
}
static int pass_attr_null_opttag(NODE* temp,Type* type){
	temp->parent->child_head->child_head->child_head->attr = //struct
	temp->parent->child_head->child_head->attr = //StructSpecifier
	temp->parent->child_head->attr =//specifier
	temp->parent->attr = type;//ExtDef attrbution
	return 0;
}
static int pass_attr_id_opttag(NODE* temp,Type* type){
	temp->parent->child_head->child_head->child_head->next_sister->child_head->attr = //ID
	temp->parent->child_head->child_head->child_head->attr = //struct
	temp->parent->child_head->child_head->attr = //StructSpecifier
	temp->parent->child_head->attr =//specifier
	temp->parent->attr = type ;//Def attrbution
	return 0 ;
}
static int warning(const char * information , long int line){
	return fprintf(stderr, "warning at line %ld: %s\n",line , information);
}
int error(const char * info , int type ,long int line){
	return fprintf(stdout,"Error type %d at line %ld: %s\n",type,line,info);
}
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

