#ifndef __TYPE_H__
#define __TYPE_H__

#define YYSTYPE NODE*
#include "const.h"
#define BASIC_TYPE 1
#define ARRAY_TYPE 2
#define STRUCTURE_TYPE 3


typedef struct Type_ Type;
typedef struct FieldList_ FieldList;

struct Type_
{
	enum { basic=1, array, structure } kind;
	union{enum {type_INT,type_FLOAT} basic;struct { Type* elem; int size; }array;FieldList* structure;} u;
};
struct FieldList_
{
    char* name;           // field name
    Type* type;            // field type 
    FieldList* tail;       // next field
};

extern Type* create_type();
extern Type* basic_create_type(enum type_enum t);
extern Type* create_type_kind(int type_kind,...);
#endif
