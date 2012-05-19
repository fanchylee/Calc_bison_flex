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
static Type* analyze_exp(NODE * exp);
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
static int analyze_args_exp(NODE* exp , FieldList * arg);
static int cmp_array(Type * arr1 , Type * arr2);
static int cmp_structure_name(Type* stt1, Type* stt2);
static int error_argument_array_struct(int err,int line);
static int pass_attr_for_declist(NODE * declist);

int analyze(NODE* head){
	const char * ctemp ;
	if((ctemp = head->name) == terminal_name[ID-WHILE]){
#ifndef SUBMIT
		printf("%s: %s\n",head->name , ((IDTEM*)(head->value).type_p)->name);
#endif
	}else if(ctemp == terminal_name[TYPE-WHILE]){
#ifndef SUBMIT
		printf("%s: %s\n",head->name,(char *)(head->value).type_p) ;
#endif
	}else if(ctemp == terminal_name[FLOAT-WHILE]){
#ifndef SUBMIT
		printf("%s: %f\n",head->name,(head->value).type_float) ;
#endif
	}else if(ctemp == terminal_name[INT-WHILE]){
#ifndef SUBMIT
		printf("%s: %d\n",head->name,(head->value).type_int);
#endif
	}else if(ctemp == nonterminal_name[Exp]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_exp(head);
	}else if(ctemp == terminal_name[LC - WHILE]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		if(head->parent->previous_sister != NULL){
		}else{
			allowoverlap(idtable_head);
		}
	}else if(ctemp == terminal_name[RC - WHILE]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		disallowoverlap(idtable_head);
	}else if(ctemp == nonterminal_name[ExtDef]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_def(head,ExtDef);
	}else if(ctemp == nonterminal_name[Def]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_def(head,Def);
	}else if(ctemp == nonterminal_name[DecList] || ctemp == nonterminal_name[ExtDecList]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_dec_extdeclist(head);
	}else if(ctemp == terminal_name[LP - WHILE]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		if(head->parent->name == nonterminal_name[FunDec]){
			allowoverlap(idtable_head);
		}
	}else if(ctemp == nonterminal_name[VarDec]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_vardec(head);
	}else if(ctemp == nonterminal_name[ParamDec]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_def(head,ParamDec);
	}else if(ctemp == nonterminal_name[VarList]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
		analyze_varlist(head);
	}else if(ctemp == terminal_name[RETURN - WHILE]){
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
	}else{
#ifndef SUBMIT
		printf("%s (%ld)\n",head->name,head->line);
#endif
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
	NODE* temp = NULL;
	IDTEM* tid =NULL;
	int kind ;
	if((temp = head->parent)->name == nonterminal_name[VarDec]){
		int size ;
		size = head->next_sister->next_sister->value.type_int ;
		head->attr = create_type_kind(ARRAY_TYPE,head->parent->attr,size);
		kind = VARIABLE_KIND;
	}else if(temp->name == nonterminal_name[Dec]){
		NODE * tmp = temp;
		head->attr = head->parent->attr ;
		while((tmp=tmp->parent)->name == nonterminal_name[DecList]){}
		while((tmp=tmp->parent)->name == nonterminal_name[DefList]){}
		if(tmp->name == nonterminal_name[StructSpecifier]){
			Type* structuretype ;
			kind = STRUCTUREFIELD_KIND;
			structuretype =  tmp->attr ;//get structure type from StructSpecifier
			if(head->child_head->name == terminal_name[ID - WHILE]){
				NODE* tmp = head->child_head;
				tmp->attr = structuretype ;//ID attr get structure type from StructSpecifier
			}
		}else if(tmp->name == nonterminal_name[CompSt]){
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
			NODE * tmp = head ;//tmp is the fisrt vardec
			while(tmp->child_head->name == nonterminal_name[VarDec]){tmp=tmp->child_head;}//get the ID node
			if(funid->u.funtype.varhead == NULL){
				funid->u.funtype.varhead = malloc(sizeof(FieldList));
				memset(funid->u.funtype.varhead,0,sizeof(FieldList));
				funid->u.funtype.varhead->type = head->attr ;
				funid->u.funtype.varhead->name = tmp->name;
			}else{
				FieldList* fieldlist = funid->u.funtype.varhead ;
				if(fieldlist->tail != NULL){
					fieldlist = fieldlist->tail ;
				}
				fieldlist->tail = malloc(sizeof(FieldList));
				memset(fieldlist->tail,0,sizeof(FieldList));
				fieldlist->tail->type = head->attr ;
				fieldlist->tail->name = tmp->name ;
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
	NODE* head = idnode->parent ;//VarDec
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
				if(structuretype->u.structure.field == NULL){
					structuretype->u.structure.field = malloc(sizeof(FieldList));
					memset(structuretype->u.structure.field,0,sizeof(FieldList));
					structuretype->u.structure.field->type = tid->u.structurefieldtype.t ;
					structuretype->u.structure.field->name = tid->name ;
				}else{
					FieldList* fieldlist = structuretype->u.structure.field ;
					if(fieldlist->tail != NULL){
						fieldlist = fieldlist->tail ;
					}
					fieldlist->tail = malloc(sizeof(FieldList));
					memset(fieldlist->tail,0,sizeof(FieldList));
					fieldlist->tail->type = tid->u.structurefieldtype.t ;
					fieldlist->tail->name = tid->name ;
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
		error("undefined struct to define a variable",17,IDnode->line);
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
#ifndef SUBMIT
			warning("unnamed struct that defines no instances", temp->parent->line);
#endif
		}else if(tp == ExtDef && ctemp == nonterminal_name[ExtDecList] ){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,NULL));
		}else if(tp == ExtDef && ctemp == nonterminal_name[FunDec]){
			NODE* ttemp = temp->parent->child_head->next_sister->child_head ;//fun id
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,NULL));
		}else if(tp == Def && ctemp == nonterminal_name[DecList]){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,NULL));
		}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
			pass_attr_null_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,NULL));
		}else{
			perror("unknown error : anonymous struct");
			exit(EXIT_FAILURE);
		}
	}else if(opt_tag_tag->child_head->name == terminal_name[ID-WHILE]){
		NODE* temp = opt_tag_tag->parent->parent->next_sister ;//head->child_head->next_sister;//
		const char * ctemp = temp->name ;
		IDTEM * tid = opt_tag_tag->child_head->value.type_p ;
		tid = tid->cur ;
		if(tp == ExtDef && ctemp == terminal_name[SEMI-WHILE] ){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,tid->name));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == ExtDef && ctemp == nonterminal_name[ExtDecList] ){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,tid->name));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == ExtDef && ctemp == nonterminal_name[FunDec]){
			NODE* ttemp = temp->parent->child_head->next_sister->child_head ;//fun id
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,tid->name));
			addstruct(temp->parent->child_head->child_head->child_head->next_sister->child_head);
		}else if(tp == Def && ctemp == nonterminal_name[DecList]){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,tid->name));
			/*ignore ID*/
		}else if(tp == ParamDec && temp->name == nonterminal_name[VarDec]){
			pass_attr_id_opttag(temp,create_type_kind(STRUCTURE_TYPE,NULL,tid->name));
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
		pass_attr_for_declist(temp);
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

static Type* analyze_exp(NODE* exp){
/*child_head*/
	if(exp->attr == NULL){
		NODE * temp = exp->child_head ;
		if(temp->name == terminal_name[ID - WHILE]){
			NODE* ntemp = temp->next_sister ;
			IDTEM* tid = temp->value.type_p ;
			tid = tid->cur;
			temp->parent->attr = tid->u.t;//Exp get attr from ID
			temp->value.type_p = tid ;
			if(ntemp == NULL){
				if(tid->kind != VARIABLE_KIND){
					error("Undefined variable",1,temp->line);
					temp->parent->attr = create_type();
				}else{
					if(temp->parent->attr){}else{
						temp->parent->attr = create_type();
					}
				}
			}else if(ntemp->name == terminal_name[LP - WHILE]){
				if(tid->kind == UNSPECIFIED ){
					error("Undefined function",2,temp->line);
					temp->parent->attr = create_type();
				}else if(tid->kind == FUNCTION_KIND){
					FieldList * arg = tid->u.funtype.varhead ;
					NODE * tmp = temp->next_sister->next_sister ;
					analyze_args_exp(tmp , arg) ;
				}else if(tid->kind == STRUCTURE_KIND){
					error("not a function before \'(\':it\'s a struct name",11,ntemp->line);
					temp->parent->attr = create_type();
				}else{
					error("not a function before \'(\':it\'s a variable",11,ntemp->line);
					temp->parent->attr = create_type();
				}
			}
		}else if(temp->name == terminal_name[FLOAT - WHILE]){
			(temp->parent->attr = create_type_kind(BASIC_TYPE,float_type)) ;//Exp get attr from FLOAT 
		}else if(temp->name == terminal_name[INT - WHILE]){
			(temp->parent->attr = create_type_kind(BASIC_TYPE,int_type)) ;//Exp get attr from INT
		}else if(temp->name == terminal_name[MINUS - WHILE]){//int or float
			Type * ttype = temp->parent->attr = temp->next_sister->attr ;//Exp get attr from  Exp after MINUS
			if(ttype->kind == BASIC_TYPE){
			}else {
				error("illegal arithmetic operation",7,temp->line);
			}
			(temp->parent->attr = ttype) ;
		}else if(temp->name == terminal_name[LP - WHILE]){
			(temp->parent->attr = temp->next_sister->attr) ;//Exp get attr from Exp after LP
		}else if(temp->name == terminal_name[NOT - WHILE]){// only int 
			Type * ttype = temp->parent->attr = temp->next_sister->attr ;//Exp get attr from  Exp after MINUS
			if(ttype->kind == BASIC_TYPE && ttype->u.basic == int_type){
			}else {
				error("illegal NOT logic operation",7,temp->line);
			}
			(temp->parent->attr = ttype) ;
		}else if(temp->name == nonterminal_name[Exp]){
			NODE* ntemp = temp->next_sister; 
			if(ntemp->name == terminal_name[AND - WHILE] || ntemp->name == terminal_name[OR - WHILE]){//only int
				Type * ttype1 = analyze_exp(temp) ;
				Type * ttype2 = analyze_exp(ntemp->next_sister) ;
				if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic && ttype1->u.basic == int_type){
					(temp->parent->attr = ttype1) ;
				}else{
					error("illegal logic operation ",7,ntemp->line);
					(temp->parent->attr = create_type_kind(BASIC_TYPE,int_type));
				}
			}else if(ntemp->name == terminal_name[PLUS - WHILE]||
				ntemp->name == terminal_name[MINUS - WHILE]||
				ntemp->name == terminal_name[STAR - WHILE]||
				ntemp->name == terminal_name[DIV - WHILE]  ){//int or float
				Type * ttype1 = analyze_exp(temp) ;
				Type * ttype2 = analyze_exp(ntemp->next_sister) ;
				if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic){
				}else {
					error("illegal arithmetic operation" , 7 , ntemp->line);
				}
				(temp->parent->attr = ttype1) ;
			}else if(ntemp->name == terminal_name[RELOP - WHILE]){//int or float
				Type * ttype1 = analyze_exp(temp) ;
				Type * ttype2 = analyze_exp(ntemp->next_sister) ;
				if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic){
				}else {
					error("illegal relation operation",7,ntemp->line);
				}
				(temp->parent->attr = create_type_kind(BASIC_TYPE,int_type));
			}else if(ntemp->name == terminal_name[LB - WHILE]){
				Type * ttype1 = analyze_exp(temp) ;
				Type * ttype2 = analyze_exp(ntemp->next_sister) ;
				if(ttype2->kind == BASIC_TYPE && ttype2->u.basic == int_type){
				}else{
					error("noninteger in bracket",12,ntemp->next_sister->line);
				}
				if(ttype1->kind == ARRAY_TYPE){
					(temp->parent->attr = ttype1->u.array.elem );
				}else {
					error("not an array before \'[\'",10,ntemp->line);
					(temp->parent->attr = create_type());
				}
			}else if(ntemp->name == terminal_name[ASSIGNOP - WHILE]){
				Type * ttype1 = analyze_exp(temp) ;
				Type * ttype2 = analyze_exp(ntemp->next_sister) ;
				if((temp->child_head->name == terminal_name[ID - WHILE] && temp->child_head->next_sister == NULL)||
					(temp->child_head->name == nonterminal_name[Exp] && (
					temp->child_head->next_sister->name == terminal_name[LB - WHILE] || 
					temp->child_head->next_sister->name == terminal_name[DOT - WHILE] ))){// temp->child_head->next_sister may not be null pointer
					if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic){	
					}else if(ttype1->kind == ttype2->kind && ttype1->kind == STRUCTURE_TYPE && ttype1->u.structure.name == ttype2->u.structure.name){
					}else {
						if(ttype1->kind != UNSPECIFIED && ttype2->kind != UNSPECIFIED)
                                        		error("unmatched type",5,ntemp->line);
                                        }
					(temp->parent->attr = ttype1) ;
				}else{
					error("lvalue expression expected",6,ntemp->line);
					(temp->parent->attr = ttype2) ;
				}
			}else if(ntemp->name == terminal_name[DOT - WHILE]){
				Type * ttype1 = analyze_exp(temp) ;
				IDTEM * tid = ntemp->next_sister->value.type_p ;
				tid = tid->cur ;
				const char * ctemp = tid->name ;
				if(ttype1->kind == STRUCTURE_TYPE){
					FieldList * field = ttype1->u.structure.field;
					while(field){
						if(strcmp(field->name,ctemp) == 0){
							break;
						}
						field = field->tail ;
					}
					if(field == NULL){
						error("undefined field" , 14, ntemp->next_sister->line);
						(temp->parent->attr = create_type());
					}else{
						(temp->parent->attr = field->type);
					}
				}else{
					error("not a structure before \'.\'",13,ntemp->line);
					(temp->parent->attr = create_type());
				}
				
			}
		}
	}
	{
		NODE * temp = exp->previous_sister ;
		if(temp && temp->name == terminal_name[RETURN - WHILE]){
			NODE * tmp = temp;
			Type * ttype1 ;
			Type * ttype2 = exp->attr ;
			while((tmp = tmp->parent)->name != nonterminal_name[CompSt]) {}//tmp->name ==CompSt
			tmp = tmp->previous_sister ;//tmp->name == FunDec
			ttype1 = tmp->attr ;
			if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic){
			}else if(ttype1->kind == ttype2->kind && ttype1->kind == STRUCTURE_TYPE && cmp_structure_name(ttype1,ttype2)==0){
			}else {
				error("function return unmatched type",8,temp->line);
			}
		}else if(temp && temp->name == terminal_name[ASSIGNOP - WHILE] 
			&& temp->previous_sister && temp->previous_sister->name == nonterminal_name[VarDec]
			&& temp->next_sister && temp->next_sister->name == nonterminal_name[Exp]){
			NODE * tmp1 = temp->previous_sister ;
			NODE * tmp2 = temp->next_sister ;
			Type* ttype1 = tmp1->attr ;
			Type* ttype2 = tmp2->attr ;
			if(ttype1->kind == ttype2->kind && ttype1->kind == BASIC_TYPE && ttype1->u.basic == ttype2->u.basic){
			}else if(ttype1->kind == ttype2->kind && ttype1->kind == STRUCTURE_TYPE && cmp_structure_name(ttype1,ttype2)==0){
			}else {
				error("unmatched type before and after \'=\'",5,temp->line);
			}
			
		}
	}
	return exp->attr;
}

#define ARRAY_DIM_UNMATCH 1
#define BASIC_STRUCT_UNMATCH 2
#define INT_FLOAT_UNMATCH 3
#define STRUCT_NAME_UNMATCH 4

static int analyze_args_exp(NODE* expp , FieldList * arg){
	NODE* exp = expp->child_head;
	int errno = 0;
	while(arg != NULL){
		if(exp != NULL && exp->name == nonterminal_name[Exp]){
			Type* ttype ;
			ttype = analyze_exp(exp) ;
			if(ttype->kind != arg->type->kind){
				error("unmatched argument type",9,exp->line);
				errno = 1;
			}else{
				if(ttype->kind == BASIC_TYPE){
					if(ttype->u.basic != ttype->u.basic){
						error("unmatched argument type:one is INT the other is FLOAT",9,exp->line);
						errno = 1 ;
					}
				}else if(ttype->kind == ARRAY_TYPE){
					errno = error_argument_array_struct(cmp_array(arg->type,ttype),exp->line) ;
				}else if(ttype->kind == STRUCTURE_TYPE){
					errno = error_argument_array_struct(cmp_array(arg->type,ttype),exp->line) ;
				}
			}
		}else{
			error("too few arguments in \'(\' \')\'",9,expp->line);
			errno = 1;
			break ;
		}
		if(arg = arg->tail ) {
			if((exp = exp->next_sister) && (exp = exp->next_sister) && (exp = exp->child_head)){
				continue ;
			}
			exp = NULL ;
		}
	}
	if(exp && (exp = exp->next_sister)&&(exp = exp->next_sister)&&(exp = exp->child_head)){
		error("too many arguments",9,exp->line);
	}
	return errno ;
}
static int error_argument_array_struct(int err,int line){
	int errno ;
	switch(err){
		case ARRAY_DIM_UNMATCH:
		error("unmatched argument type:array dimension unmatched",9,line);
		errno = 1;
		break; 

		case BASIC_STRUCT_UNMATCH:
		error("unmatched argument type:basic array with struct array",9,line);
		errno = 1;
		break; 

		case INT_FLOAT_UNMATCH:
		error("unmatched argument type:int array with float array",9,line);
		errno = 1;
		break; 

		case STRUCT_NAME_UNMATCH:
		error("unmatched argument type:different struct",9,line);
		errno = 1;
		break; 
		
		default:
		errno = 0 ;
		break ;
	}
	return errno ;
}
static int cmp_array(Type * arr1 , Type * arr2){
	int dim1 = 0 ,dim2 = 0;
	while(arr1->kind == ARRAY_TYPE){
		dim1 ++ ;
		arr1 = arr1->u.array.elem ;
	}
	while(arr2->kind == ARRAY_TYPE){
		dim2 ++ ;
		arr2 = arr2->u.array.elem ;
	}
	if(dim1 != dim2){
		return ARRAY_DIM_UNMATCH;
	}
	if(arr1->kind == arr1->kind){
	switch(arr1->kind){
		case BASIC_TYPE:
		if(arr1->u.basic != arr2->u.basic){
			return INT_FLOAT_UNMATCH;
		}
		break ;

		case STRUCTURE_TYPE:
		return cmp_structure_name(arr1 , arr2);
		break ;

		default:
		break ;
	}
	}else{
		return BASIC_STRUCT_UNMATCH ;
	}
	return 0 ;
}
static int cmp_structure_name(Type* stt1, Type* stt2){
	if(strcmp(stt1->u.structure.name,stt2->u.structure.name) == 0){
	}else{
		return STRUCT_NAME_UNMATCH;
	}
	return 0;
}
static int cmp_structure(Type* stt1, Type* stt2){
	FieldList * stf1 = stt1->u.structure.field ;
	FieldList * stf2 = stt2->u.structure.field ;
	return 0;
}
static int pass_attr_for_declist(NODE * declist){
	NODE* temp = declist ;
	NODE* tmp = temp->child_head ;//Dec
	temp->child_head->attr = //Dec get attr from a pecifier
	temp->parent->attr =//Def get attr from a pecifier
	temp->attr = temp->previous_sister->attr ;//DecList  get attr from a pecifier
	while((tmp=tmp->next_sister) && (tmp = tmp->next_sister) &&(tmp->name == nonterminal_name[DecList])){
		tmp->child_head->attr = ////Dec get attr from DecList
		tmp->attr = temp->attr ;//DecList  get attr from last DecList
		tmp=tmp->child_head;
	}
	return 0;
}
/*
static int illope(Type* ttype){
	if(ttype->u.basic != error_type){
		error("illegal operation",7,temp->line);
		ttype->kind = BASIC_TYPE ;
		ttype->u.basic = error_type ;
		return 1 ;
	}
	return 0 ;
}
*/
