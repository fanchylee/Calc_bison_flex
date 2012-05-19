#ifndef __IRTREESTRUCT_H__
#define __IRTREESTRUCT_H__

typedef const char* Temp_label;
typedef const char* Temp_temp ;
typedef const char* Temp_fun ;

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
	enum {T_SEQ, T_LABEL, T_JUMP, T_CJUMP, T_MOVE, T_EXP} kind;
	union {
		struct {T_stm left, right;} SEQ;
		struct {Temp_label label;} LABEL;
		struct {T_exp exp; Temp_labelList labels;} JUMP;
		struct {T_relOp op; T_exp left, right; Temp_label tlabel, flabel;} CJUMP;
		struct {T_exp destination, source;} MOVE;
		struct {T_exp exp;} EXP;
	} u;
};
struct T_exp_ {
	enum {T_BIN0P, T_MEM, T_TEMP, T_ESEQ, T_NAME, T_CONST, T_CALL} kind;
	union {
		struct {T_binOp op; T_exp left, right;} BINOP;
		struct {T_exp exp;} T_MEM ;
		struct {Temp_temp temp;} T_TEMP ;
		struct {T_stm stm; T_exp exp;} T_ESEQ ;
		struct {Temp_label label;} T_NAME ;
		struct {int cnt;} T_CONST ;
		struct {T_exp exp; T_expList args;} T_CALL ;
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

T_stm T_Fun(Temp_fun) ;
T_stm T_Seq(T_stm left, T_stm right);
T_stm T_Label (Temp_label) ;
T_stm T_Jump(T_exp exp, Temp_labelList labels);
T_stm T_Cjump(T_relOp op, T_exp left, T_exp right, Temp_label tlable, Temp_label flable);
T_stm T_Move(T_exp, T_exp);
T_stm T_Exp(T_exp) ;

T_exp T_Binop (T_binOp, T_exp, T_exp) ;
T_exp T_Mem(T_exp);
T_exp T_Temp(Temp_temp);
T_exp T_Eseq(T_stm, T_exp);
T_exp T_Name (Temp_label) ;
T_exp T_Const(int);
T_exp T_Call(T_exp, T_expList) ;


T_expList T_ExpList(T_exp head, T_expList tail);

T_stmList T_StmList(T_stm head, T_stmList tail);

T_stm create_stm() ;
Temp_label create_label()
Temp_labelList create_labels();
#endif
