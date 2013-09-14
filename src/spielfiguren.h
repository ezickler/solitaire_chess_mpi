#ifndef SPIELFIGUREN_H_
#define SPIELFIGUREN_H_

#include <glib-2.0/glib.h>
#include "askparam.h"
#define DarstellungLeer	    0 //TODO: spielfiguren_Leer ?
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6

#define SpielbrettBreite	option.spielbrettBreite //TODO: evtl streichen und für lesbarkeit options.b im code verwenden
#define SpielbrettHoehe		option.spielbrettHoehe
#define SpielfelderAnzahl  16 //TODO in define, rechnung aus anderen defines möglich, SpielbrettBreite*SpielbrettHoehe

typedef struct figuren_param{
	char **spielbrett_array; 
	long long* spielbrett; 
	int anzahlFiguren;
	GHashTable* spielbretterHashtables[11]; 
	
}figuren_param_t;

/**
 * Prüft, ob ein Zug mit diesem Bauer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneBauer(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit diesem Turm an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneTurm(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit diesem Läufer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneLaeufer(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit diesem Springer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneSpringer(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit diesem König an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneKoenig(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit dieser Dame an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 */ 
int berechneDame(figuren_param_t *param, int x, int y);




#endif
