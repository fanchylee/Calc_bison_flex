#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "const.h"
#include "type.h"
#define VARIABLE_KIND 0
#define STRUCTURE_KIND 1
#define FUNCTION_KIND 2
#define STRUCTUREFIELD_KIND 3

union myvalue{
	int type_int;
	float type_float;
	double type_double;
	void * type_p ;
};
typedef union myvalue MYVALUE ;

struct node{
	struct node * parent ;
	struct node * child_head  ;
	struct node * next_sister ;
	struct node * previous_sister ;
	MYVALUE value ;
	const char * name ;
	void * attr ;
	long int line ;
};
typedef struct node NODE ;

struct id_item{
	enum kind_ {Variable=0 , Structure, Function, StructionField } kind ;
	union {
		Type* t; //for variables
		struct {Type* ret;struct id_item * varhead;} funtype;
		struct {Type* t;} structruetype ;
		struct {Type* t;Type* structure;} structurefieldtype ;
	}u;
	char* name ;
	unsigned char overlapable ;
	struct id_item * back ;
	struct id_item * forward ;
	struct id_item * next ;
	struct id_item * previous ;
};
typedef struct id_item IDTEM ;

extern NODE* create_node() ;
extern NODE* value_create_node(MYVALUE value,int line,const  char * name);


extern IDTEM* create_idtem() ;
extern IDTEM* str_create_idtem(const char * str) ;

extern MYVALUE itou(int);
extern MYVALUE ftou(float);
extern MYVALUE ptou(void * ) ;

extern IDTEM* install_id(const char * );


extern int run_item_list(IDTEM *  ) ;
extern IDTEM* cmp_item_list( IDTEM* head , const char * str ) ;

#endif
