#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "main.h"
#include "askparam.h" 


void AskParams( struct options* options, int argc, char** argv )
{
	printf ( "\n");
	printf ( "===============================================================\n" );
	printf ( "Program for calculate all Posible Solutions of Solitaire Chess \n" );
	printf ( "===============================================================\n" );
	printf ( "    Kira Duwe\n");
	printf ( "    Enno Zickler\n");
	printf ( "===============================================================\n"  );
	
	
	
	if (strcmp("help",(char *)argv[1])==0 || strcmp("-h",(char *)argv[1])==0 ||
		strcmp("-?",  (char *)argv[1])==0 || strcmp("?", (char *)argv[1])==0 ||
		argc < 2)
	{
		printf("\nUsage:\n");
		printf("%s [num][method] \n", argv[0]);
		printf("  - num:    number of threads to use\n");
		printf("  - method: \n");
		printf("\n");
		printf("Example: %s 12 0 \n", argv[0]);
		exit(0);
	}
		
	if(argc == 2)
	{
		sscanf( argv[1],"%d", &(options->num));
		sscanf( argv[2],"%d", &(options->method));
	}
}
