#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

IDTEM * idtable_head ;
NODE * node_head ;
FILE * fpdebug ;
FILE * nul=NULL;
char * tab=NULL ;
char noerror = 1 ;

void reset_tab(){
	tab = (char *)malloc(1);
	tab[0]='\0';
}
