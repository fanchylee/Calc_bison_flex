#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>


#ifndef __IRTREESTRUCT_H__
#define __IRTREESTRUCT_H__
#define LABELSIZE 7
typedef  char* Temp_label;
typedef char* Temp_temp ;
typedef char* Temp_fun ;

typedef struct T_labelList_ *T_labelList ;
struct T_labelList_{
	Temp_label head ;
	T_labelList tail ;
};
typedef T_labelList Temp_labelList ;
typedef enum {
	T_plus, T_minus, T_mul, T_div, T_and, T_or
} T_binOp ;
typedef enum {
	T_eq, T_ne, T_lt, T_gt, T_le, T_ge,
	T_ult, T_ule, T_ugt, T_uge
} T_relOp;
typedef struct T_stm_ *T_stm;
typedef struct T_exp_ *T_exp;
typedef struct T_stmList_ *T_stmList;
typedef struct T_expList_ *T_expList;
struct T_stm_ {
	enum {T_FUN=100, T_SEQ, T_LABEL, T_JUMP, T_CJUMP, T_MOVE, T_EXP, T_RET, T_DEC, T_READ, T_WRITE} kind;
	union {
		struct {Temp_fun fun; T_expList args;} FUN;
		struct {T_stm left, right;} SEQ;
		struct {Temp_label label;} LABEL;
		struct {T_exp exp; Temp_labelList labels;} JUMP;
		struct {T_relOp op; T_exp left, right; Temp_label tlabel, flabel;} CJUMP;
		struct {T_exp destination, source;} MOVE;
		struct {T_exp exp;} EXP;
		struct {T_exp retexp;} RET;
		struct {T_exp name, width;} DEC;
		struct {T_exp readto;} READ ;
		struct {T_exp writefrom;} WRITE ;
	} u;
};
struct T_exp_ {
	enum {T_BINOP=200, T_MEM, T_TEMP, T_ESEQ, T_NAME, T_FUNNAME, T_CONST, T_CALL, T_ADDR} kind;
	union {
		struct {T_binOp op; T_exp left, right;} BINOP;
		struct {T_exp memexp;} MEM ;
		struct {Temp_temp temp;} TEMP ;
		struct {T_stm eseqstm; T_exp eseqexp;} ESEQ ;
		struct {Temp_label label;} NAME ;
		struct {Temp_fun fun; } FUNNAME ;
		struct {int cnt;} CONST ;
		struct {T_exp callexp; T_expList args;} CALL ;
		struct {T_exp nameexp;} ADDR ;
	} u;
};
struct T_stmList_ {
	T_stm head;
	T_stmList tail;
};
struct T_expList_ {
	T_exp head;
	T_expList tail;
};

T_stm T_Fun(Temp_fun, T_expList ) ;
T_stm T_Seq(T_stm left, T_stm right);
T_stm T_Label (Temp_label) ;
T_stm T_Jump(T_exp exp, Temp_labelList labels);
T_stm T_Cjump(T_relOp op, T_exp left, T_exp right, Temp_label tlable, Temp_label flable);
T_stm T_Move(T_exp, T_exp);
T_stm T_Exp(T_exp) ;
T_stm T_Ret(T_exp);
T_stm T_Dec(T_exp, T_exp) ;
T_stm T_Read(T_exp);
T_stm T_Write(T_exp);

T_exp T_Binop (T_binOp, T_exp, T_exp) ;
T_exp T_Mem(T_exp);
T_exp T_Temp(Temp_temp);
T_exp T_Eseq(T_stm, T_exp);
T_exp T_Name (Temp_label) ;
T_exp T_FunName(Temp_fun) ;
T_exp T_Const(int);
T_exp T_Call(T_exp, T_expList) ;
T_exp T_Addr(T_exp);


T_expList T_ExpList(T_exp head, T_expList tail);

T_stm create_stm();
T_exp create_exp();
T_expList create_explist();
Temp_label create_label();
Temp_temp create_temp();
Temp_labelList create_labels(Temp_label first, ...);

//T_stmList T_StmList(T_stm head, T_stmList tail);


#endif
T_stm create_stm(){
	T_stm stm ;
	stm = malloc(sizeof(struct T_stm_));
	memset(stm, 0, sizeof(struct T_stm_));
	return stm ;
}
T_exp create_exp(){
	T_exp exp ;
	exp = malloc(sizeof(struct T_exp_));
	memset(exp, 0, sizeof(struct T_exp_));
	return exp ;
}
T_expList create_explist(){
	T_expList explist ;
	explist = malloc(sizeof(struct T_expList_));
	memset(explist, 0, sizeof(struct T_expList_));
	return explist ;
}


Temp_label create_label(){
	static int id = 0;
	char * label = malloc(LABELSIZE);
	sprintf(label, "l%d\0", id++);
	return label ;
}
Temp_temp create_temp(){
	static int id = 0 ;
	char * temp = malloc(LABELSIZE);
	sprintf(temp, "t%d\0", id++) ;
	return temp;
}
Temp_labelList create_labels(Temp_label first, ...){
	Temp_labelList ret ;	
	Temp_labelList temp ;	
	Temp_label next ;
	va_list ap ;
	ret = malloc(sizeof(struct T_labelList_)) ;
	ret->head = first ;
	temp = ret ;
	va_start(ap, first) ;
	while((next = va_arg(ap, Temp_label))!=NULL) {
		temp->tail = malloc(sizeof(struct T_labelList_)) ;
		temp->tail->head = next ;
		temp = temp->tail ;
	}
	va_end(ap);
	temp->tail = NULL ;
	return ret ;
}

T_stm T_Fun(Temp_fun fun, T_expList args){
	T_stm stm = create_stm() ;
	stm->kind = T_FUN ;
	stm->u.FUN.fun = fun ;
	stm->u.FUN.args = args ;
	return stm ;
}
T_stm T_Seq(T_stm left, T_stm right){
	T_stm stm = create_stm() ;
	stm->kind = T_SEQ ;
	stm->u.SEQ.left = left ;
	stm->u.SEQ.right = right ;
	return stm ;
}
T_stm T_Label(Temp_label label){
	T_stm stm = create_stm() ;
	stm->kind = T_LABEL ;
	stm->u.LABEL.label = label ;
	return stm ;
}
T_stm T_Jump(T_exp exp, Temp_labelList labels){
	T_stm stm = create_stm() ;
	stm->kind = T_JUMP ;
	stm->u.JUMP.exp = exp ;
	stm->u.JUMP.labels = labels ;
	return stm ;
}
T_stm T_Cjump(T_relOp op, T_exp left, T_exp right, Temp_label tlabel,Temp_label flabel){
	T_stm stm = create_stm() ;
	stm->kind = T_CJUMP ;
	stm->u.CJUMP.op = op ;
	stm->u.CJUMP.left = left ;
	stm->u.CJUMP.right = right ;
	stm->u.CJUMP.tlabel = tlabel ;
	stm->u.CJUMP.flabel = flabel ;
	return stm ;
}
T_stm T_Move(T_exp destination,T_exp source){
	T_stm stm = create_stm() ;
	stm->kind = T_MOVE ;
	stm->u.MOVE.destination = destination ;
	stm->u.MOVE.source = source ;
	return stm ;
}
T_stm T_Exp(T_exp exp){
	T_stm stm = create_stm() ;
	stm->kind = T_EXP ;
	stm->u.EXP.exp = exp ;
	return stm ;
}
T_stm T_Ret(T_exp retexp){
	T_stm stm = create_stm() ;
	stm->kind = T_RET ;
	stm->u.RET.retexp = retexp ;
	return stm ;
}
T_stm T_Dec(T_exp name,T_exp width){
	T_stm stm = create_stm() ;
	stm->kind = T_DEC ;
	stm->u.DEC.name = name ;
	stm->u.DEC.width = width ;
	return stm ;
}
T_stm T_Read(T_exp exp){
	T_stm stm = create_stm() ;
	stm->kind = T_READ ;
	stm->u.READ.readto = exp ;
	return stm ;
}
T_stm T_Write(T_exp exp){
	T_stm stm = create_stm() ;
	stm->kind = T_WRITE ;
	stm->u.WRITE.writefrom = exp ;
	return stm ;
}


T_exp T_Binop (T_binOp op , T_exp left, T_exp right) {
	T_exp exp = create_exp();
	exp->kind = T_BINOP ;
	exp->u.BINOP.op = op ;
	exp->u.BINOP.left = left ;
	exp->u.BINOP.right = right ;
	return exp ;
}
T_exp T_Mem(T_exp memexp){
	T_exp exp = create_exp();
	exp->kind = T_MEM ;
	exp->u.MEM.memexp = memexp ;
	return exp ;
}
T_exp T_Temp(Temp_temp temp){
	T_exp exp = create_exp();
	exp->kind = T_TEMP ;
	exp->u.TEMP.temp = temp ;
	return exp ;
}
T_exp T_Eseq(T_stm eseqstm, T_exp eseqexp){
	T_exp exp = create_exp();
	exp->kind = T_ESEQ ;
	exp->u.ESEQ.eseqstm = eseqstm ;
	exp->u.ESEQ.eseqexp = eseqexp ;
	return exp ;
}
T_exp T_Name (Temp_label label) {
	T_exp exp = create_exp();
	exp->kind = T_NAME ;
	exp->u.NAME.label = label ;
	return exp ;
}
T_exp T_FunName(Temp_fun fun) {
	T_exp exp = create_exp();
	exp->kind = T_FUNNAME ;
	exp->u.FUNNAME.fun = fun ;
	return exp ;
}
T_exp T_Const(int cnt){
	T_exp exp = create_exp();
	exp->kind = T_CONST ;
	exp->u.CONST.cnt = cnt ;
	return exp ;
}
T_exp T_Call(T_exp callexp, T_expList args) {
	T_exp exp = create_exp();
	exp->kind = T_CALL;
	exp->u.CALL.callexp = callexp ;
	exp->u.CALL.args = args ;
	return exp ;
}
T_exp T_Addr(T_exp nameexp){
	T_exp exp = create_exp();
	exp->kind = T_ADDR ;
	exp->u.ADDR.nameexp = nameexp ;
	return exp ;
}

T_expList T_ExpList(T_exp exp, T_expList explist){
	T_expList retexplist = create_explist();
	retexplist->head = exp;
	retexplist->tail = explist ;
	return retexplist ;
}
