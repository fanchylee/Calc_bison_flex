#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "global.h"

#define BASIC_TYPE 1 
#define ARRAY_TYPE 2 
#define STRUCTURE_TYPE 3 

#ifndef __TYPE_H__

typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
struct Type_{
	enum { basic=1, array=2, structure=3 } kind;
	union{enum {type_INT,type_FLOAT} basic;struct { Type* elem; int size; }array;struct {FieldList* field;char * name;}structure;} u;
};
struct FieldList_
{
    const char* name;           // field name
    Type* type;            // field type 
    FieldList* tail;       // next field
};
#endif

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
#ifndef SUBMIT
		printf("size:%d\n",tp->u.array.size );
#endif
		break;

		case STRUCTURE_TYPE:
		tp->u.structure.field = va_arg(ap,FieldList*);
		tp->u.structure.name = va_arg(ap,char *);
		break ;

		default:
		break;
	}
	va_end(ap);
	return tp ;
}
