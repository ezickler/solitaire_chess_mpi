#include "main.h"
#include <glib.h>
#include <stdbool.h>

#define SpielbrettBreite	4
#define SpielbrettHoehe		4
#define DarstellungLeer	    0
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6



// Array fuer die Pointer auf die Hashtabelen fuer 2-10 Figuren.
// Die Felder 0 und 1 werden nicht benutzt.
GHashTable* _hashtable[11]; 


/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
void erzeugeHashtables(){
	int figurenAnzahl;
	for(figurenAnzahl=2; figurenAnzahl<=10; figurenAnzahl++){
		_hashtable[figurenAnzahl] = g_hash_table_new ( g_direct_hash(), g_direct_equal());
	}
}




/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, char ** argv){
	
	struct options options;
	
	AskParams(&options, argc, argv);
	
	erzeugeHashtables();
	erzeugeSpielbretter();
	
	return EXIT_SUCCESS;
	
}





