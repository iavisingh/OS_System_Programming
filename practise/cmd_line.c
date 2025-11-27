#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) 
{
	printf("\ncommand line args==>>\n");

	for(int i = 0; i < argc; i++) {
		printf("%s\t",argv[i]);
	}

	printf("\ncommand line args==>> end\n");
}
