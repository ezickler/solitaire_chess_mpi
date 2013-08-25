#ifndef SPIELBRETTER_H_
#define SPIELBRETTER_H_

#include <stdbool.h>


#define DarstellungLeer	    0
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6


/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 *
 */
void erzeugeSpielbretter();

#endif
