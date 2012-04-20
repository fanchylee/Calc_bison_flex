#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
struct Type_
{
    enum { basic, array, structure } kind;
    union
    {
         //basic type
         int basic;
         // array type:information including element type and array size
         struct { Type* elem; int size; } array;
         // struct type : information is a linked list
         FieldList* structure;
    } u;
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
Type* basic_create_type(enum type_enum t){
	Type* tp ;
	tp = create_type();
	tp->kind = basic ;
	(tp->u).basic = t ;
	return tp ;
}
