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
