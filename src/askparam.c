#include "askparam.h" 


void AskParams(options_t* option, int argc, char** argv )
{
	
	if (argc != 5 ||
		strcmp("help",(char *)argv[1])==0 || strcmp("-h",(char *)argv[1])==0 ||
		strcmp("-?",  (char *)argv[1])==0 || strcmp("?", (char *)argv[1])==0 
		)
	{
		printf("\nUsage:\n");
		printf("%s [num][method] [spielbrettBreite] [spielbrettHoehe] \n", argv[0]);
		printf("  - num:    number of threads to use\n");
		printf("  - method: \n");
		printf("  - spielbrettBreite: Breite des Spielbrettes \n");
		printf("  - spielbrettHoehe: Hoehe des Spielbrettes \n");
		printf("\n");
		printf("Example: %s 12 0 4 4 \n", argv[0]);
		exit(0);
	}
		
	if(argc == 5)
	{
		sscanf( argv[1],"%d", &(option->num ));
		sscanf( argv[2],"%d", &(option->method));
		sscanf( argv[3],"%d", &(option->spielbrettBreite));
		sscanf( argv[4],"%d", &(option->spielbrettHoehe));
	}
}
