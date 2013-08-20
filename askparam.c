#include "askparam.h" 


void AskParams( struct options* options, int argc, char** argv )
{
	printf ( "\n");
	printf ( "===============================================================\n" );
	printf ( "Programm zur Berechnung aller lösbaren Spielbretter \n" );
	printf ( "===============================================================\n" );
	printf ( "    Kira Duwe\n");
	printf ( "    Enno Zickler\n");
	printf ( "===============================================================\n"  );
	
	
	
	if (argc != 3 ||
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
		
	if(argc == 3)
	{
		sscanf( argv[1],"%d", &(options->num ));
		sscanf( argv[2],"%d", &(options->method));
		sscanf( argv[3],"%d", &(options->spielbrettBreite));
		sscanf( argv[4],"%d", &(options->spielbrettHoehe));
	}
}
