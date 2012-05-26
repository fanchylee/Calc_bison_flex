#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stddef.h>
#include "type.h"
#include "struct.h"
//#define SUBMIT

extern IDTEM* idtable_head   ;
extern  NODE* node_head ;
extern FILE *fpdebug ;
extern FILE *nul ;
extern FILE *irout ;
extern char *tab ;
extern char noerror  ;
extern void reset_tab();
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})

#endif
