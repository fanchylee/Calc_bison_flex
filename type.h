#ifndef __TYPE_H__
#define __TYPE_H__

#define YYSTYPE NODE*
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

extern Type* create_type();
extern Type* basic_create_type(enum type_enum t);
#endif
