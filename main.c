#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include "mpi.h"

#include "main.h"
#include "askparam.h"




int main(int argc, char * argv[]){
	
	struct options options;
	
	AskParam(&options, argc, argv);
	
	return EXIT_SUCCESS;
	
}