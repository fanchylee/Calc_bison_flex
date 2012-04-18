main()
{
	FILE * nul=NULL;
	FILE * fpdebug=NULL;
	nul=fopen("/dev/null","w");
	fpdebug = stdout; 
	if(nul != NULL){
//		fpdebug=nul ;
	}
	yylex();
//	printf( "# of lines = %d, # of chars = %d\n",num_lines, num_chars );
}
