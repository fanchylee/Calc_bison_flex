#include <stdio.h>
#include "struct.h"
#include "type.h"
#include "irtreestruct.h"
#define TEMPSIZE 12


static T_exp tr_exp(NODE* exp) ;
static T_stm tr_stmt(NODE* stmt) ;
static T_stm tr_stmtlist(NODE* stmtlist);
static T_stm tr_compst(NODE* compst);
static T_stm tr_cond(NODE* condexp);
static T_relOp tr_relop(NODE* relop);
static Temp_temp tr_id(NODE* id);
static T_exp tr_condexp(NODE* exp);
static T_stm tr_fundec(NODE* head);
static T_stm tr_deflist(NODE* deflist);
static T_exp tr_struct(NODE* structexp, NODE* fieldid) {


int translate(NODE* head){
	const char * ctemp ;
	if((ctemp = head->name) == nonterminal_name[StmtList]){
	}else if(ctemp == nonterminal_name[FunDec]){
		tr_fundec(head);
	}
}
static T_stm tr_fundec(NODE* head){
	NODE* temp = head->child_head ;
	NODE* temp_compst = head->next_sister/*CompSt*///->child_head->next_sister->next_sister ;
	return T_Seq(T_Fun(((IDTEM*)temp->value.type_p)->name), tr_compst(temp_compst));
}
static T_stm tr_stmt(NODE* stmt){
	if(stmt != NULL) {
		return NULL ;
	}else if(stmt->name == nonterminal_name[Stmt]){
		temp = stmt->child_head ;
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
				T_stm turelabel = T_Label(t) ;
				T_stm truestm = tr_stm(stmt);
				T_stm falselabel = T_Label(f) ;
				return T_Seq(condstm, T_Seq(truelabel, T_Seq(truestm, falselabel)));
			}else if(el->name == terminal_name[ELSE - WHILE]){
				NODE* elsestmt = el->next_sister;
				Temp_label t = create_label();
				Temp_label f = create_label();
				Temp_label next = create_label();
				T_stm condstm = tr_cond(exp, t, f);
				T_stm turelabel = T_Label(t);
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
			T_stm turestm = tr_stmt(stmt) ;
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
	return tr_stmtlist(stmtlist);
}
static T_stm tr_stmtlist(NODE* stmtlist){
	T_stm right ;
	if(stmtlist->child_head == NULL){
		right = NULL ;
	}else{
		right = tr_stmtlist(stmtlist->child_head->next_sister);
	} 
	return T_Seq(tr_stmt(stmtlist->child_head), right);
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
			if(third->name == nonterminal_name[Args]){
				/*TODO*/
				return T_Call(T_funName(((IDTEM*)child_head->value.type_p)->name), tr_args(third));
			}else if(third->name == terminal_name[RP - WHILE]){
				/*TODO*/
				return T_Call(T_funName(((IDTEM*)child_head->value.type_p)->name), NULL) ;
			}
		}
	}else if(child_head->name == terminal_name[INT - WHILE]){
		return T_Const(child_head->value.type_int) ;
	}else if(child_head->name == terminal_name[LP - WHILE]){
		return Tr_exp(second) ;
	}else if(child_head->name == terminal_name[NOT - WHILE]){
		return tr_condexp(exp) ;
	}else if(child_head->name == terminal_name[MINUS - WHILE]){
		T_exp T_expexp = tr_exp(exp);
		T_exp bopminus = T_Binop(T_minus, T_Const(0), T_expexp);
		return bopminus ;
	}else if(child_head->name == nonterminal_name[Exp]){
		if(second != NULL){
			
		third = second->next_sister ;
		if(second->name == terminal_name[ASSIGNOP - WHILE]){
			T_exp exp2 = tr_exp(third) ;
			return T_Eseq(T_Move(tr_exp(child_head), exp2), exp2) ;
		}else if(second->name == terminal_name[PLUS - WHILE]||
			second->name == terminal_name[MINUS - WHILE]||
			second->name == terminal_name[STAR - WHILE]||
			second->name == terminal_name[DIV - WHILE]){
			return T_Binop((T_binOp)second->value.type_int, tr_exp(child_head), tr_exp(third));
		}else if(second->name == terminal_name[RELOP - WHILE]||
			second->name == terminal_name[AND - WHILE]||
			second->name == terminal_name[OR - WHILE]||){
			return tr_condexp(exp) ;
		}else if(second->name == terminal_name[LB - WHILE]){
			return T_Mem(tr_arrayexp(child_head));
		}else if(second->name == terminal_name[DOT - WHILE]){
			return T_Mem(tr_struct(child_head, third)) ;
		}
		
		
		}
	}
	
	}
}
static T_exp tr_array(NODE* exp){
	Type* arraytype = ((IDTEM*)exp->parent->attr)->u.t ;
	if(exp->name == nonterminal_name[Exp]){
		NODE* third_next = exp->next_sister->next_sister ;//exp
		T_exp plused = T_Binop(T_star, tr_exp(third_next), size_array(arraytype)) ;
		if(exp->next_sister == terminal_name[LB - WHILE]){
			return T_Binop(T_plus, tr_arrayexp(exp->child_head), plused);
		}else if(exp->next_sister == terminal_name[DOT - WHILE]){
			return tr_struct(child_head, third_next) ;
		}
	}else if(exp->name == terminal_name[ID - WHILE]){
		IDTEM* arrayidtem = exp->value.type_p ;
		Type* arraytype = arrayidtem->u.t  ;
		Temp_temp arraytemp = tr_id(exp);
		T_exp arraytempexp = T_Tem(arraytemp) ;
		return T_Eseq(T_Dec(arraytempexp, T_Const(size_array(arraytype))),T_Addr(arraytempexp)) ;
	}
}
static T_exp tr_struct(NODE* structexp, NODE* fieldid) {
	Type* structtype = ((IDTEM*)structexp->attr)->u.t ;
	int offset = field_offset(structtype->u.structure.field, fieldid) ;
	int width = field_offset(structtype->u.structure.field, NULL) ;
	T_exp structtempexp = tr_exp(structexp) ;
	return T_Eseq(T_Dec(structtempexp, T_Const(width)), T_Binop(T_plus, T_Addr(structtempexp), offset)) ;
}
static int field_offset(FieldList* field, NODE* fieldid){
	if(fieldid == NULL ){
		if(field == NULL) {
			return 0;
		}else {
			return size_field(field->type) + field_offset(field->tail, fieldid);
		}
	}else {
		if( strcmp(field->name, ((IDTEM*)fieldid->value.type_p)->name)){
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
	}
}
static int size_array(Type* arraytype){
	Type* childtype = arraytype->u.array.elem ;
	if(arraytype->kind == ARRAY_TYPE){
		return arraytype->u.array.size * size_array(childtype);
	}else if(arraytype->kind == BASIC_TYPE){
		return 4 ;
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
					T_exp exp = tr_exp(exp) ;
					return T_Cjump(T_ne, exp, T_Const(0), t, f);
				}
			}
		}else {
			T_exp exp = tr_exp(exp) ;
			return T_Cjump(T_ne, exp, T_Const(0), t, f);
		}
	}
}
static T_relOp tr_relop(NODE* relop){
	return (T_relOp)relop->value.type_int ;
}
static Temp_temp tr_id(NODE* id){
	Temp_temp tempid = malloc(TEMPSIZE);
	sprintf(tempid, "t%x\0", (int)id->value.type_p);
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
static T_exp tr_condexp(NODE* exp){
	Temp_label t = create_label();
	Temp_label f = create_label();
	Temp_temp tem = create_temp();
	return T_Eseq(T_Move(T_Temp(tem),T_Const(0)),
		T_Eseq(tr_cond(exp),
		T_Eseq(T_Label(t),
		T_Eseq(T_Move(T_Temp(tem),T_Const(1)),
		T_Eseq(T_Label(f),T_Temp(tem)))))) ;
}
