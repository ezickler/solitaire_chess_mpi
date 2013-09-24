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


#include <omp.h>
//#include <mpi.h>


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char ** argv)
{
    
    //TODO MPI init
	
	AskParams(&option, argc, argv);
	
    
	spielbretter_t *bretter = spielbretter_berechne();
    
	//spielbretter_berechne_alt(bretter);
  
    printf("Es es sind %ld von %ld Spielbretter lösbar. \n", bretter->loesbareBretterGesamt, bretter->anzahlBretterGesamt);
    
	spielbretter_destruct(bretter);
    
    
	return EXIT_SUCCESS;	
}
