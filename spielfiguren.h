#ifndef SPIELFIGUREN_H_
#define SPIELFIGUREN_H_

#include <glib-2.0/glib.h>
#include "askparam.h"
#define DarstellungLeer	    0
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6

#define SpielbrettBreite	options.spielbrettBreite
#define SpielbrettHoehe		options.spielbrettHoehe
#define SpielfelderAnzahl  16 //TODO in define, rechnung aus anderen defines möglich, SpielbrettBreite*SpielbrettHoehe


typedef struct spielparameter 
{
	
	// Array für die Pointer auf die Hashtabellen für 2-10 Figuren.
	// Die Felder 0 und 1 werden nicht benutzt.
	GHashTable* spielbretterHashtables[11]; 
	// Array für das gerade zuberechnende Spielbrett
	char **_spielbrett_array;


}




int berechneBauer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneTurm(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneLaeufer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneSpringer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneKoenig(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneDame(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);




#endif
