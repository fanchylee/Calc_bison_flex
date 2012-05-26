#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "calc.yy.h"
#include "struct.h"
#include "type.h"
#include "irtreestruct.h"
#include "global.h"
#define TEMPSIZE 15
#define BINOPSIZE 45
#define IROUT irout


static T_exp get_eseqexp(T_exp expeseq);
static T_exp tr_exp(NODE* exp) ;
static T_stm tr_stm(NODE* stmt) ;
static T_stm tr_stmtlist(NODE* stmtlist);
static T_stm tr_compst(NODE* compst);
static T_stm tr_cond(NODE* condexp, Temp_label t, Temp_label f);
static T_relOp tr_relop(NODE* relop);
static Temp_temp tr_id(NODE* id);
static T_exp tr_condexp(NODE* exp);
static T_stm tr_fundec(NODE* head);
static T_stm tr_deflist(NODE* deflist);
static T_exp tr_struct(NODE* structexp, NODE* fieldid) ;
static T_expList tr_args(NODE* args);
static T_exp tr_array(NODE* arrayexp);
static int field_offset(FieldList* field, NODE* fieldid);
static int size_field(Type* fieldtype);
static int size_array(Type* arraytype);
static T_stm tr_program(NODE* program);
static T_stm tr_extdeflist(NODE* extdeflist);
static T_stm tr_extdef(NODE* extdef);
static void traverse_explist(T_expList args);
static char* get_location(T_exp locationexp);
static void traverse_explist_f(T_expList args);
static char* get_relop(T_relOp op);
static char* get_binop(T_binOp op);
static T_expList tr_param(NODE* varlist);
static T_stm tr_deflist(NODE* deflist);
static T_stm tr_def(NODE* def);
static T_stm tr_dec(NODE* dec);
static T_stm tr_declist(NODE* declist);
static T_stm tr_arraydec(NODE* dec);
static T_stm tr_dec_struct(NODE* dec);
static T_stm tr_declist_struct(NODE* dec);

T_stm translate(NODE* head);
int traverse_irtree(T_stm node);
T_exp traverse_irtree_exp(T_exp node);

static char* get_relop(T_relOp op){
	char * opchar = malloc(3);
	switch(op){
	case T_eq:
	strcpy(opchar,"==\0");
	break;

	case T_ne:
	strcpy(opchar,"!=\0");
	break;

	case T_lt:
	strcpy(opchar,"<\0");
	break;

	case T_gt:
	strcpy(opchar,">\0");
	break;

	case T_le:
	strcpy(opchar, "<=\0");
	break;

	case T_ge:
	strcpy(opchar, ">=\0");
	break;
	}
	return opchar ;
}
static char* get_binop(T_binOp op){
	char * opchar = malloc(3);
	switch(op){
	case T_plus:
	strcpy(opchar,"+\0");
	break;

	case T_minus:
	strcpy(opchar,"-\0");
	break;

	case T_mul:
	strcpy(opchar,"*\0");
	break;

	case T_div:
	strcpy(opchar,"/\0");
	break;
	}
	return opchar;
}

int traverse_irtree_stm(T_stm node ){
	T_exp exp1, exp2;
	T_stm stm1, stm2;
	char *c1, *c2 ;
	if(node == NULL){
		return 0;
	}
	switch(node->kind){
	case T_FUN:
	fprintf(IROUT, "FUNCTION %s :\n", node->u.FUN.fun);
	traverse_explist_f(node->u.FUN.args);
	break ;

	case T_SEQ:
	traverse_irtree_stm(node->u.SEQ.left);
	traverse_irtree_stm(node->u.SEQ.right);
	break ;

	case T_LABEL:
	fprintf(IROUT, "LABEL %s :\n", node->u.LABEL.label);
	break ;

	case T_JUMP:
	fprintf(IROUT, "GOTO %s\n", get_location(traverse_irtree_exp(node->u.JUMP.exp))); 
	break ;

	case T_CJUMP:
	exp1 = traverse_irtree_exp(node->u.CJUMP.left);
	exp2 = traverse_irtree_exp(node->u.CJUMP.right);
	fprintf(IROUT, "IF %s %s %s GOTO %s\n", get_location(exp1), get_relop(node->u.CJUMP.op), get_location(exp2), node->u.CJUMP.tlabel);
	fprintf(IROUT, "GOTO %s\n", node->u.CJUMP.flabel);
	break ;

	case T_MOVE:
	exp1 =traverse_irtree_exp(node->u.MOVE.destination);
	exp2 =traverse_irtree_exp(node->u.MOVE.source );
	c1 = get_location(exp1) ;
	c2 = get_location(exp2) ;
	fprintf(IROUT, "%s := %s\n", c1, c2);
	break ;

	case T_EXP:
	traverse_irtree_exp(node->u.EXP.exp);
	break ;

	case T_RET:
	exp1 = traverse_irtree_exp(node->u.RET.retexp);
	if(exp1->kind == T_BINOP){
		Temp_temp t = create_temp();
		c1 = get_location(exp1);
		fprintf(IROUT, "%s := %s\n", t, c1);
		fprintf(IROUT, "RETURN %s\n", t);
	}else {
		c1 = get_location(exp1);
		fprintf(IROUT, "RETURN %s\n", c1);
	}
	break ;

	case T_DEC:
	exp1 = traverse_irtree_exp(node->u.DEC.name);
	exp2 = traverse_irtree_exp(node->u.DEC.width);
	fprintf(IROUT, "DEC %s %s\n", get_location(exp1), get_location(exp2) + 1);
	break ;

	case T_READ:
	exp1 = traverse_irtree_exp(node->u.READ.readto);
	fprintf(IROUT, "READ %s\n", get_location(exp1));
	break;
	
	case T_WRITE:
	exp1 = traverse_irtree_exp(node->u.WRITE.writefrom);
	fprintf(IROUT, "WRITE %s\n", get_location(exp1));
	break;
	}
	return 0 ;
}
static int operation(T_binOp op, int first, int second){
	switch(op){
	case T_plus:
	return first+second;
	break ;
	case T_minus:
	return first-second;
	break ;
	case T_mul:
	return first*second;
	break ;
	case T_div:
	return first/second;
	break ;
	}
}
T_exp traverse_irtree_exp(T_exp node){
	T_exp temexp1, temexp2, temexp3;
	switch(node->kind){
	case T_BINOP:
/*
	temexp1 = node->u.BINOP.left;
	temexp2 = node->u.BINOP.right;
	if(temexp1->kind == T_ESEQ){
		temexp1 = get_eseqexp(temexp1);
	}
	if(temexp2->kind == T_ESEQ){
		temexp2 = get_eseqexp(temexp2);
	}
	if(node->u.BINOP.left->kind == node->u.BINOP.right->kind && 
	node->u.BINOP.left->kind == T_CONST){
		node->u.BINOP.left = temexp1 ;	
		node->u.BINOP.right = temexp2 ;
		return T_Const(operation(node->u.BINOP.op, node->u.BINOP.left->u.CONST.cnt, node->u.BINOP.right->u.CONST.cnt)) ;
	}else {
		return  node;
	}
	break ;
*/

	case T_MEM:
	case T_TEMP:
	case T_NAME:
	case T_FUNNAME:
	case T_CONST:
	case T_CALL:
	case T_ADDR:	
	return node ;
	break ;

	case T_ESEQ:
	traverse_irtree_stm(node->u.ESEQ.eseqstm);
	return traverse_irtree_exp(node->u.ESEQ.eseqexp);
	break ;

	}
}
static void traverse_explist(T_expList args){
	T_exp head, exp1, exp2, exp3;
	if(args == NULL){
		return ;
	}
	traverse_explist(args->tail);
//	T_exp head = traverse_irtree_exp(args->head);
	head = args->head ;

	if((exp1 = head)->kind == T_ESEQ){
		exp1 = get_eseqexp(exp1);
	}

	switch(exp1->kind){
	Temp_temp t ;

	case T_BINOP:
	t = create_temp();
	fprintf(IROUT, "%s := %s\n", t, get_location(head));
	fprintf(IROUT, "ARG %s\n", t);
	break ;

	case T_ESEQ: 
	break;

	case T_CALL: case T_MEM: case T_ADDR: case T_NAME: case T_FUNNAME: case T_CONST: case T_TEMP:
	fprintf(IROUT, "ARG %s\n", get_location(head));
	break;

	default:
	break;
	}
}
static void traverse_explist_f(T_expList args){
	T_exp head, exp1  ;
	if(args == NULL){
		return ;
	}
//	T_exp head = traverse_irtree_exp(args->head);
	head = args->head ;
	if((exp1 = head)->kind == T_ESEQ){
		exp1 = get_eseqexp(exp1);
	}

	switch(head->kind){
	Temp_temp t ;

	case T_BINOP:
	t = create_temp();
	fprintf(IROUT, "%s := %s\n", t, get_location(head));
	fprintf(IROUT, "PARAM %s\n", t);
	break ;

	case T_ESEQ: 
	break;
	case T_CALL: case T_MEM: case T_ADDR: case T_NAME: case T_FUNNAME: case T_CONST: case T_TEMP:
	fprintf(IROUT, "PARAM %s\n", get_location(head));
	break;

	default:
	break;
	}
	traverse_explist(args->tail);
}
static char* get_location(T_exp locationexp){
	char* ret ;
	T_exp exp1, exp2, exp3 ;
	Temp_temp t1, t2 ;
	switch(locationexp->kind){
	case T_NAME:
	case T_FUNNAME:
	case T_TEMP:
	ret = locationexp->u.NAME.label ;
	break ;

	case T_CONST:
	ret = malloc(TEMPSIZE);
	sprintf(ret, "#%d", locationexp->u.CONST.cnt);
	break ;

	case T_MEM:
	//exp1 = traverse_irtree_exp(locationexp->u.MEM.memexp);
	exp1 = locationexp->u.MEM.memexp ;
	ret = malloc(TEMPSIZE);
	if(exp1->kind == T_BINOP){
		char *ct = get_location(exp1);
		Temp_temp t = create_temp();
		fprintf(IROUT, "%s := %s\n", t, ct);
		sprintf(ret, "*%s", t);
	}else {
		sprintf(ret, "*%s", get_location(exp1));
	}
	break ;

	case T_ADDR:
//	exp1 = traverse_irtree_exp(locationexp->u.ADDR.nameexp);
	exp1 = locationexp->u.ADDR.nameexp ;
	ret = malloc(TEMPSIZE);
	if(exp1->kind == T_BINOP){
		char *ct = get_location(exp1);
		Temp_temp t = create_temp();
		fprintf(IROUT, "%s := %s\n", t, ct);
		sprintf(ret, "&%s", t);
	}else{
		sprintf(ret, "&%s", get_location(exp1));
	}
	break ;
	
	case T_ESEQ:
//	exp1 = traverse_irtree_exp(locationexp->u.ESEQ.eseqexp);
	traverse_irtree_stm(locationexp->u.ESEQ.eseqstm);
	exp1 = locationexp->u.ESEQ.eseqexp ;
	ret = get_location(exp1);
	break ;
	
	case T_BINOP:
//	exp1 = traverse_irtree_exp(locationexp);
	exp1 = locationexp ;
	ret = malloc(BINOPSIZE);
	if(exp1->kind != T_BINOP){
		ret = get_location(exp1);
	}else{
		char * opc = get_binop(exp1->u.BINOP.op);
		char * leftc =  get_location(exp1->u.BINOP.left );
		char * rightc = get_location(exp1->u.BINOP.right);
		Temp_temp t1, t2 ;
/*
		if(exp1->u.BINOP.left->kind != T_BINOP && exp1->u.BINOP.right->kind != T_BINOP){
			sprintf(ret, "%s %s %s", leftc, opc, rightc);
		}else if(exp1->u.BINOP.left->kind == T_BINOP && exp1->u.BINOP.right->kind != T_BINOP){
			Temp_temp t = create_temp();
			fprintf(IROUT, "%s := %s\n", t, get_location(exp1->u.BINOP.left));
			sprintf(ret, "%s %s %s", t, opc,  get_location(exp1->u.BINOP.right));
		}else if(exp1->u.BINOP.left->kind != T_BINOP && exp1->u.BINOP.right->kind == T_BINOP){
			Temp_temp t = create_temp();
			fprintf(IROUT, "%s := %s\n", t, get_location(exp1->u.BINOP.right));
			sprintf(ret, "%s %s %s",  get_location(exp1->u.BINOP.left), opc, t);
		}else if(exp1->u.BINOP.left->kind == T_BINOP && exp1->u.BINOP.right->kind == T_BINOP){
	
*/		
		if((exp2 = exp1->u.BINOP.left)->kind == T_ESEQ){
			exp2 = get_eseqexp(exp2);
		}
		if((exp3 = exp1->u.BINOP.right)->kind == T_ESEQ){
			exp3 = get_eseqexp(exp3);
		}
		switch(exp2->kind){
			case T_BINOP:
			t1 = create_temp();
			fprintf(IROUT, "%s := %s\n", t1, leftc);
			break ;

			case T_ESEQ: 
			break;

			case T_CALL: case T_MEM: case T_ADDR: case T_NAME: case T_FUNNAME: case T_CONST: case T_TEMP:
			t1 = leftc;
			break;

			default:
			t1 = create_temp();
			fprintf(IROUT, "%s := %s\n", t1, leftc);
			break;
		}
		switch(exp3->kind){
			case T_BINOP:
			t2 = create_temp();
			fprintf(IROUT, "%s := %s\n", t2, rightc);
			break ;

			case T_ESEQ: 
			break;

			case T_CALL: case T_MEM: case T_ADDR: case T_NAME: case T_FUNNAME: case T_CONST: case T_TEMP:
			t2 = rightc;
			break;

			default:
			t2 = create_temp();
			fprintf(IROUT, "%s := %s\n", t2, rightc);
			break;
		}
		sprintf(ret, "%s %s %s",  t1, opc, t2);
	}
	break;
	
	case T_CALL:
	traverse_explist(locationexp->u.CALL.args);
	t1 = create_temp();
	fprintf(IROUT, "%s := CALL %s\n", t1, get_location(locationexp->u.CALL.callexp));
	ret = t1;
	break ;

	default:
	fprintf(stderr, "get location error\n");
	return NULL;
	break;
	}
	return ret ;
}
static T_exp get_eseqexp(T_exp expeseq){
	T_exp childexp = expeseq->u.ESEQ.eseqexp ;
	if(childexp->kind == T_ESEQ){
		return get_eseqexp(childexp);
	}else{
		return childexp ;
	}
}
///////////////////
T_stm translate(NODE* head){
	const char * ctemp ;
	if((ctemp = head->name) == nonterminal_name[Program]){
		return tr_program(head);
	}
}
static T_stm tr_program(NODE* program){
	NODE* child_head = program->child_head ;
	return tr_extdeflist(child_head);

}
static T_stm tr_extdeflist(NODE* extdeflist){
	NODE* child_head = extdeflist->child_head ;
	if(child_head == NULL){
		return NULL;
	}else if(child_head->name == nonterminal_name[ExtDef]){
		T_stm extdefstm = tr_extdef(child_head);
		if(extdefstm == NULL){
			return tr_extdeflist(child_head->next_sister) ;
		}else {
			return T_Seq(extdefstm, tr_extdeflist(child_head->next_sister)) ;
		}
	}
}
static T_stm tr_extdef(NODE* extdef){
	NODE* second_child = extdef->child_head->next_sister ;
	if(second_child->name == nonterminal_name[FunDec]){
		return tr_fundec(second_child);
	}else {
		return NULL;
	}
	
}
static T_stm tr_fundec(NODE* head){
	NODE* temp = head->child_head ;
	NODE* second = temp->next_sister ;
	NODE* third = second->next_sister ;
	NODE* temp_compst = head->next_sister ;/*CompSt*///->child_head->next_sister->next_sister ;
	if(third->name == nonterminal_name[VarList]){
		return T_Seq(T_Fun(((IDTEM*)temp->value.type_p)->name, tr_param(third)), tr_compst(temp_compst));
	}else {
		return T_Seq(T_Fun(((IDTEM*)temp->value.type_p)->name, NULL), tr_compst(temp_compst));
	}
}
static T_stm tr_stm(NODE* stmt){
	if(stmt == NULL) {
		return NULL ;
	}else if(stmt->name == nonterminal_name[Stmt]){
		NODE* temp = stmt->child_head ;
		if(temp->name == nonterminal_name[Exp]){
			return T_Exp(tr_exp(temp));
		}else if(temp->name == nonterminal_name[CompSt]){
			return tr_compst(temp);
		}else if(temp->name == terminal_name[RETURN - WHILE]){
			NODE* exp = temp->next_sister ;
			return T_Ret(tr_exp(exp));
		}else if(temp->name == terminal_name[IF - WHILE]){
			NODE* exp = temp->next_sister->next_sister ;
			NODE* stmt = exp->next_sister->next_sister ;
			NODE* el = stmt->next_sister ;
			if(el == NULL){
				Temp_label t = create_label() ;
				Temp_label f = create_label() ;
				T_stm condstm = tr_cond(exp, t, f);
				T_stm truelabel = T_Label(t) ;
				T_stm truestm = tr_stm(stmt);
				T_stm falselabel = T_Label(f) ;
				return T_Seq(condstm, T_Seq(truelabel, T_Seq(truestm, falselabel)));
			}else if(el->name == terminal_name[ELSE - WHILE]){
				NODE* elsestmt = el->next_sister;
				Temp_label t = create_label();
				Temp_label f = create_label();
				Temp_label next = create_label();
				T_stm condstm = tr_cond(exp, t, f);
				T_stm truelabel = T_Label(t);
				T_stm truestm = tr_stm(stmt);
				T_stm falselabel = T_Label(f);
				T_stm falsestm = tr_stm(elsestmt);
				T_stm nextlabel = T_Label(next);
				return T_Seq(condstm, 
					T_Seq(truelabel, 
					T_Seq(truestm, 
					T_Seq(T_Jump(T_Name(next),create_labels(next, NULL)), T_Seq(falselabel, T_Seq(falsestm, nextlabel))))));
			}
		}else if(temp->name == terminal_name[WHILE - WHILE]){
			NODE* exp = temp->next_sister->next_sister ;
			NODE* stmt = exp->next_sister->next_sister ;
			Temp_label start = create_label() ;
			Temp_label t = create_label();
			Temp_label f = create_label();
			T_stm startlabel = T_Label(start) ;
			T_stm condstm = tr_cond(exp, t, f) ;
			T_stm truelabel = T_Label(t) ;
			T_stm turestm = tr_stm(stmt) ;
			T_stm falselabel = T_Label(f) ;
			return T_Seq(startlabel, 
				T_Seq(condstm,
				T_Seq(truelabel, 
				T_Seq(turestm,
				T_Seq(T_Jump(T_Name(start), create_labels(start, NULL)), falselabel))))) ;
		}
	}
}
static T_stm tr_compst(NODE* compst){
	NODE* deflist = compst->child_head->next_sister ;
	NODE* stmtlist = deflist->next_sister ;//StmtList
	T_stm left = tr_deflist(deflist);
	T_stm right = tr_stmtlist(stmtlist);
	if(left != NULL && right == NULL){
        	return left ;
        }else if(left != NULL&& right != NULL){
        	return T_Seq(left, right);
        }else if(left == NULL && right != NULL){
        	return right ;
        }else if(left == NULL && right == NULL){
        	return NULL ;
        }
}
static T_stm tr_deflist(NODE* deflist){
	if(deflist->child_head == NULL){
		return NULL;
	}else{
		NODE* def = deflist->child_head ;
		NODE* deflistn = def->next_sister; 
		T_stm left = tr_def(def);
		T_stm right = tr_deflist(deflistn);
		if(left != NULL && right == NULL){
			return left ;
		}else if(left != NULL && right != NULL){
			return T_Seq(left, right);
		}else if(left == NULL && right != NULL){
			return right ;
		}else if(left == NULL && right == NULL){
			return NULL ;
		}
	}
}
static T_stm tr_def(NODE* def){
	NODE* specifier = def->child_head ;
	NODE* structspecifier = specifier->child_head ;
	if(structspecifier->name == nonterminal_name[StructSpecifier]){
		return tr_declist_struct(def->child_head->next_sister);
	}
	return tr_declist(def->child_head->next_sister);
}
static T_stm tr_declist_struct(NODE* declist){
	NODE* dec = declist->child_head ;
	NODE* comma = dec->next_sister;
	T_stm left = tr_dec_struct(dec);
	T_stm right ;
	if(comma == NULL){
		right = NULL ;
	}else {
		right = tr_declist_struct(comma->next_sister);
	}
	if(left != NULL && right == NULL){
		return left ;
	}else if(left != NULL&& right != NULL){
		return T_Seq(left, right);
	}else if(left == NULL && right != NULL){
		return right ;
	}else if(left == NULL && right == NULL){
		return NULL ;
	}
}
static T_stm tr_dec_struct(NODE* dec){
	NODE* vardec = dec->child_head;
	NODE* id;
	NODE* exp ;
	NODE* assignop;
	if(vardec->next_sister == NULL){
		id = vardec->child_head ;
		if(id->name != terminal_name[ID - WHILE]){
			return tr_arraydec(id) ;
		}else {
			Temp_temp t = tr_id(id) ;
			FieldList* fieldhead = ((IDTEM*)id->value.type_p)->u.structuretype.t->u.structure.field ;
			int width = field_offset(fieldhead, NULL);
			return T_Dec(T_Temp(t), T_Const(width)); 
		}
	}
}
static T_stm tr_declist(NODE* declist){
		NODE* dec = declist->child_head ;
		NODE* comma = dec->next_sister; 
		T_stm left = tr_dec(dec);
		T_stm right ;
		if(comma == NULL){
			right = NULL ;
		}else {
			right = tr_declist(comma->next_sister);
		}
		if(left != NULL && right == NULL){
			return left ;
		}else if(left != NULL&& right != NULL){
			return T_Seq(left, right);
		}else if(left == NULL && right != NULL){
			return right ;
		}else if(left == NULL && right == NULL){
			return NULL ;
		}
}
static T_stm tr_dec(NODE* dec){
	NODE* vardec = dec->child_head;
	NODE* id;
	NODE* exp ;
	NODE* assignop;
	if(vardec->next_sister == NULL){
		id = vardec->child_head ;
		if(id->name != terminal_name[ID - WHILE]){
			return tr_arraydec(id) ;
		}
		return NULL ;
	}
	assignop = vardec->next_sister ;
	if(assignop->name != terminal_name[ASSIGNOP - WHILE])return NULL;
	id = vardec->child_head ;
	exp = assignop->next_sister ;
	return T_Move(T_Temp(tr_id(id)), tr_exp(exp));
}
static T_stm tr_arraydec(NODE* dec){
	if(dec->name == terminal_name[ID - WHILE]){
		IDTEM* arrayidtem = dec->value.type_p ;
		Type* arraytype = arrayidtem->u.t  ;
		return T_Dec(T_Temp(tr_id(dec)), T_Const(size_array(arraytype))); 
	}else {
		return tr_arraydec(dec->child_head);
	}
}
static T_stm tr_stmtlist(NODE* stmtlist){
	if(stmtlist->child_head == NULL){
		return NULL;
	}else{
		NODE* stmt = stmtlist->child_head ;
		NODE* stmtlistn = stmt->next_sister; 
		T_stm left = tr_stm(stmt);
		T_stm right = tr_stmtlist(stmtlistn);
		if(left != NULL && right == NULL){
			return left ;
		}else if(left != NULL&& right != NULL){
			return T_Seq(left, right);
		}else if(left == NULL && right != NULL){
			return right ;
		}else if(left == NULL && right == NULL){
			return NULL ;
		}
	}
}
static T_exp tr_exp(NODE* exp){
	NODE* child_head = exp->child_head ;
	NODE* second ;
	NODE* third ;
	if(child_head != NULL){
	
	second = child_head->next_sister ;
	if(child_head->name == terminal_name[ID - WHILE]){
		if(second == NULL){
			return T_Temp(tr_id(child_head)) ;
		}else if(second->name == terminal_name[LP - WHILE]){
			third = second->next_sister ;
			char *fname = ((IDTEM*)child_head->value.type_p)->name ;
			if(strcmp(fname, "read") == 0 ){
				Temp_temp t = create_temp();
				return T_Eseq(T_Read(T_Temp(t)), T_Temp(t));
			}
			if( strcmp(fname, "write") == 0 ){
				return T_Eseq(T_Write(tr_exp(third->child_head)), T_Const(0)) ;
			}
			if(third->name == nonterminal_name[Args]){
				/*TODO*/
				
				return T_Call(T_FunName(fname), tr_args(third));
			}else if(third->name == terminal_name[RP - WHILE]){
				/*TODO*/
				return T_Call(T_FunName(fname), NULL) ;
			}
		}
	}else if(child_head->name == terminal_name[INT - WHILE]){
		return T_Const(child_head->value.type_int) ;
	}else if(child_head->name == terminal_name[LP - WHILE]){
		return tr_exp(second) ;
	}else if(child_head->name == terminal_name[NOT - WHILE]){
		return tr_condexp(exp) ;
	}else if(child_head->name == terminal_name[MINUS - WHILE]){
		T_exp T_expexp = tr_exp(exp->child_head->next_sister);
		T_exp bopminus = T_Binop(T_minus, T_Const(0), T_expexp);
		return bopminus ;
	}else if(child_head->name == nonterminal_name[Exp]){
		if(second != NULL){
			
		third = second->next_sister ;
		if(second->name == terminal_name[ASSIGNOP - WHILE]){
			T_exp exp2 = tr_exp(third) ;
			Temp_temp t = create_temp() ;
			T_exp te = T_Temp(t);
			return T_Eseq(T_Seq(T_Move(te, exp2), T_Move(tr_exp(child_head), te)), te) ;
		}else if(second->name == terminal_name[PLUS - WHILE]||
			second->name == terminal_name[MINUS - WHILE]||
			second->name == terminal_name[STAR - WHILE]||
			second->name == terminal_name[DIV - WHILE]){
			return T_Binop((T_binOp)second->value.type_int, tr_exp(child_head), tr_exp(third));
		}else if(second->name == terminal_name[RELOP - WHILE]||
			second->name == terminal_name[AND - WHILE]||
			second->name == terminal_name[OR - WHILE]){
			return tr_condexp(exp) ;
		}else if(second->name == terminal_name[LB - WHILE]){
			return T_Mem(tr_array(child_head));
		}else if(second->name == terminal_name[DOT - WHILE]){
			return T_Mem(tr_struct(child_head, third)) ;
		}
		
		
		}
	}
	
	}
}
static T_exp tr_array(NODE* exp){
	Type* arraytype = exp->parent->attr ;
	if(exp->name == nonterminal_name[Exp]){
		NODE* third_next = exp->next_sister->next_sister ;//exp
		T_exp plused = T_Binop(T_mul, tr_exp(third_next), T_Const(size_array(arraytype)));
		if(exp->next_sister->name == terminal_name[LB - WHILE]){
			return T_Binop(T_plus, tr_array(exp->child_head), plused);
		}else if(exp->next_sister->name == terminal_name[DOT - WHILE]){
			return tr_struct(exp, third_next) ;
		}
	}else if(exp->name == terminal_name[ID - WHILE]){
/*
		IDTEM* arrayidtem = exp->value.type_p ;
		Type* arraytype = arrayidtem->u.t  ;
		Temp_temp arraytemp = tr_id(exp);
		T_exp arraytempexp = T_Temp(arraytemp) ;
*/
		return T_Addr(T_Temp(tr_id(exp))) ;
	}
}
static T_exp tr_struct(NODE* structexp, NODE* fieldid) {
	Type* structtype = structexp->attr ;
	int offset = field_offset(structtype->u.structure.field, fieldid) ;
	int width = field_offset(structtype->u.structure.field, NULL) ;
	T_exp structtempexp = tr_exp(structexp) ;
//	return T_Eseq(T_Dec(structtempexp, T_Const(width)), T_Binop(T_plus, T_Addr(structtempexp), T_Const(offset))) ;
	return T_Binop(T_plus, T_Addr(structtempexp), T_Const(offset));
}
static int field_offset(FieldList* field, NODE* fieldid){
	if(fieldid == NULL ){
		if(field == NULL) {
			return 0;
		}else {
			return size_field(field->type) + field_offset(field->tail, fieldid);
		}
	}else {
		if( strcmp(field->name, ((IDTEM*)fieldid->value.type_p)->name) == 0){
			return 0 ;
		}else {
			return size_field(field->type) + field_offset(field->tail, fieldid);
		}
	}	
}
static int size_field(Type* fieldtype){
	if(fieldtype->kind == BASIC_TYPE){
		return 4 ;
	}else if(fieldtype->kind == ARRAY_TYPE){
		return size_array(fieldtype) ;
	}else if(fieldtype->kind == STRUCTURE_TYPE){
		return field_offset(fieldtype->u.structure.field, NULL) ;
	}
}
static int size_array(Type* arraytype){
	Type* childtype = arraytype->u.array.elem ;
	if(arraytype->kind == ARRAY_TYPE){
		return arraytype->u.array.size * size_array(childtype);
	}else if(arraytype->kind == BASIC_TYPE){
		return 4 ;
	}else if(arraytype->kind == STRUCTURE_TYPE){
		return field_offset(arraytype->u.structure.field, NULL) ;
	}
}
static T_stm tr_cond(NODE* cond, Temp_label t, Temp_label f){
	NODE* child_head = cond->child_head ;
	NODE* second ;
	NODE* third ;
	if(child_head != NULL ){
		second = child_head->next_sister  ;
		if(child_head->name == terminal_name[NOT - WHILE]){
			return tr_cond(second, f, t) ;
		}else if(child_head->name == nonterminal_name[Exp]){
			if(second != NULL){
				third = second->next_sister ;
				if(second->name == terminal_name[AND - WHILE]){
					Temp_label label1 = create_label();
					T_stm stmt1 = tr_cond(child_head, label1, f);
					T_stm labelstmt = T_Label(label1) ;
					T_stm stmt2 = tr_cond(third, t, f);
					return T_Seq(stmt1, T_Seq(labelstmt, stmt2));
				}else if(second->name == terminal_name[OR - WHILE]){
					Temp_label label1 = create_label();
					T_stm stmt1 = tr_cond(child_head, t, label1);
					T_stm labelstmt = T_Label(label1) ;
					T_stm stmt2 = tr_cond(third, t, f);
					return T_Seq(stmt1, T_Seq(labelstmt, stmt2));
				}else if(second->name == terminal_name[RELOP - WHILE]){
					T_exp exp1 = tr_exp(child_head);
					T_exp exp2 = tr_exp(third);
					T_relOp op = tr_relop(second) ;
					return  T_Cjump(op, exp1, exp2, t, f) ;
				}else {
					T_exp exp = tr_exp(cond) ;
					return T_Cjump(T_ne, exp, T_Const(0), t, f);
				}
			}
		}else {
			T_exp exp = tr_exp(cond) ;
			return T_Cjump(T_ne, exp, T_Const(0), t, f);
		}
	}
}
static T_relOp tr_relop(NODE* relop){
	return (T_relOp)relop->value.type_int ;
}
static Temp_temp tr_id(NODE* id){
	Temp_temp tempid = malloc(TEMPSIZE);
	sprintf(tempid, "t%x\0", (long int)((IDTEM*)id->value.type_p));
	return tempid ;
}
static T_expList tr_args(NODE* args){
	T_expList ret ;
	NODE* child_head = args->child_head ;
	if(child_head->next_sister != NULL){
		NODE* third = child_head->next_sister->next_sister ;
		ret = T_ExpList(tr_exp(child_head), tr_args(third));
	}else {
		ret = T_ExpList(tr_exp(child_head), NULL) ;
	}
	return ret ;
}
static T_expList tr_param(NODE* varlist){
	NODE* paramdec = varlist->child_head ;
	NODE* vardec = paramdec->child_head->next_sister ;
	NODE* nvarlist ;
	NODE* tmp = vardec ;
	T_expList ret ;
	while(tmp->name == nonterminal_name[VarDec]){tmp=tmp->child_head;}
	if(paramdec->next_sister == NULL){
		ret = T_ExpList(T_Temp(tr_id(tmp)), NULL);
	}else {
		nvarlist = paramdec->next_sister->next_sister ;
		ret = T_ExpList(T_Temp(tr_id(tmp)), tr_param(nvarlist));
	}
	return ret ;
}
static T_exp tr_condexp(NODE* exp){
	Temp_label t = create_label();
	Temp_label f = create_label();
	Temp_temp tem = create_temp();
	return T_Eseq(T_Move(T_Temp(tem),T_Const(0)),
		T_Eseq(tr_cond(exp, t, f),
		T_Eseq(T_Label(t),
		T_Eseq(T_Move(T_Temp(tem),T_Const(1)),
		T_Eseq(T_Label(f),T_Temp(tem)))))) ;
}

