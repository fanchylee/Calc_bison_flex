
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#define BASIC_TYPE 0
#define ARRAY_TYPE 1
#define STRUCTURE_TYPE 2
typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
struct Type_{
	enum { basic=0, array=1, structure=2 } kind;
	union{int basic;struct { Type* elem; int size; }array;FieldList* structure;} u;
};
struct FieldList_
{
    char* name;           // field name
    Type type;            // field type 
    FieldList* tail;       // next field
};



Type* create_type(){
	Type* tp = NULL;
	tp = malloc(sizeof(Type));
	memset(tp,0,sizeof(Type));
	return tp ;
}
Type* create_type_kind(int type_kind,...){
	va_list ap ;
	Type* tp ;
	tp = create_type();
	tp->kind = type_kind ;

	va_start(ap,type_kind);
	switch(type_kind){
		case BASIC_TYPE:
		tp->u.basic = va_arg(ap,enum type_enum);
		break;

		case ARRAY_TYPE:
		tp->u.array.elem = va_arg(ap,Type* );
		tp->u.array.size = va_arg(ap,int);
		printf("size:%d\n",tp->u.array.size );
		break;

		case STRUCTURE_TYPE:
		tp->u.structure = va_arg(ap,FieldList*);
		break ;

		default:
		break;
	}
	va_end(ap);
	return tp ;
}
