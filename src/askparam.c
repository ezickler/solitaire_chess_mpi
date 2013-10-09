#include "askparam.h" 


void AskParams(options_t* option, int argc, char** argv )
{
	
	if (argc != 4 ||
		strcmp("help",(char *)argv[1])==0 || strcmp("-h",(char *)argv[1])==0 ||
		strcmp("-?",  (char *)argv[1])==0 || strcmp("?", (char *)argv[1])==0 
		)
	{
		printf("\nUsage:\n");
		printf("%s [num][method] [spielbrettBreite] [spielbrettHoehe] \n", argv[0]);
		printf("  - num:    Anzahl der threads. 0 Automatisch, ab 4 nurnoch vielfach von 4 eingeben \n");
		printf("  - spielbrettBreite: Breite des Spielbrettes \n");
		printf("  - spielbrettHoehe: Hoehe des Spielbrettes \n");
		printf("\n");
		printf("Example: %s 12 4 4 \n", argv[0]);
		exit(0);
	}
		
	if(argc == 4)
	{
		sscanf( argv[1],"%d", &(option->numThreads ));
		sscanf( argv[2],"%d", &(option->spielbrettBreite));
		sscanf( argv[3],"%d", &(option->spielbrettHoehe));
	}
}
