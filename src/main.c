#include "askparam.h"
#include "spielbretter.h"
#include "spielfiguren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <glib-2.0/glib.h>
#include <stdint.h>
#include <math.h>

//#include <mpi.h>



/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char ** argv){
	
	//struct options options;
	
	AskParams(&options, argc, argv);
	
	
	spielbretter_t *bretter = spielbretter_create_figurenweise();
	spielbretter_berechne(bretter);
	spielbretter_destruct(bretter);
	return EXIT_SUCCESS;	
}
