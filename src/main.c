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
#include <mpi.h>

static void gibStatisticAus(spielbretter_t *bretter)
{
    printf("Berechnungszeit:    %f s \n", bretter->berechnungsZeitGesamt);
    printf("Bretter / Sekunde: %f \n", (bretter->anzahlBretterGesamt / bretter->berechnungsZeitGesamt) );
    
    printf("\nFiguren: \t Loesbare: \t Gesamt: \t Lösbar in %%: \t Zeit:\n");
    printf("==========================================================================\n");
	for(int tala=0; tala <= 10; tala++)
	{
        printf(" %2d \t \t %10d \t %10ld \t %10.3f \t %8.3f \n",tala, bretter->loesbareBretter[tala], bretter->anzahlBretter[tala],bretter->loesbareBretter[tala]*100.0/bretter->anzahlBretter[tala] , bretter->berechnungsZeit[tala]);
	}
    printf("==========================================================================\n");
    printf("Summe: \t\t %10ld \t %10ld \t %10.3f \t %8.3f \n\n",bretter->loesbareBretterGesamt,bretter->anzahlBretterGesamt,bretter->loesbareBretterGesamt*100.0/bretter->anzahlBretterGesamt, bretter->berechnungsZeitGesamt );

    
    printf("Anteil der loesbaren Bretter in Prozent: %f\n", (((bretter->anzahlBretterGesamt - bretter->loesbareBretterGesamt)*100.0)/bretter->anzahlBretterGesamt));
}




/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char ** argv)
{
    int rc;
    spielbretter_t bretter;
    
    /* initialisiere Bretter */
    bretter.anzahlBretterGesamt=0;
    bretter.loesbareBretterGesamt=0;
    for(int x =0; x <11; x++)
    {
        bretter.anzahlBretter[x]=0;
        bretter.loesbareBretter[x]=0;
    }

    
    //TODO MPI init
    rc = MPI_Init(&argc,&argv);
   	if (rc != MPI_SUCCESS) {
     	printf ("Error starting MPI program. Terminating.\n");
    	MPI_Abort(MPI_COMM_WORLD, rc);
	}
    MPI_Comm_size(MPI_COMM_WORLD, &(bretter.anzahlProzesse));
	MPI_Comm_rank(MPI_COMM_WORLD, &(bretter.prozessNummer));
    AskParams(&option, argc, argv);
	
    if(bretter.prozessNummer == 0)
    {
        printf ( "\n");
        printf ( "===============================================================\n" );
        printf ( "Programm zur Berechnung aller lösbaren Spielbretter \n" );
        printf ( "===============================================================\n" );
        printf ( "    Kira Duwe\n");
        printf ( "    Enno Zickler\n");
        printf ( "===============================================================\n"  );
        printf ( "Starte Berechnung für %d x %d Spielbretter. \n", option.spielbrettBreite, option.spielbrettHoehe);
    }

        
    spielbretter_berechne(&bretter);
    
    
    
    if(bretter.prozessNummer == 0)
    {
        gibStatisticAus(&bretter);
    }

    MPI_Finalize();
	return EXIT_SUCCESS;	
}
