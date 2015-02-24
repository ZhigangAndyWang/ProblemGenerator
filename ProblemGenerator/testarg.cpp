#include <stdio.h>
 // main program
 int main(int argc,char *argv[]) {
	int i=0;
	// decode arguments
	if(argc < 2) {
	     printf("You must provide at least one argument\n");
	     return 1;
	     }
	// report settings
        for (;i<argc;i++) printf("Argument %d:%s\n",i,argv[i]);
	return(0);
 }

