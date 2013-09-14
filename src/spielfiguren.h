#ifndef SPIELFIGUREN_H_
#define SPIELFIGUREN_H_

#include <glib-2.0/glib.h>
#include "askparam.h"
#define DarstellungLeer	    0x0LL
#define DarstellungBauer    0x1LL
#define	DarstellungTurm	    0x2LL
#define DarstellungLaeufer  0x3LL
#define DarstellungSpringer 0x4LL
#define DarstellungKoenig   0x5LL
#define DarstellungDame     0x6LL

#define SpielbrettBreite	option.spielbrettBreite
#define SpielbrettHoehe		option.spielbrettHoehe
#define SpielfelderAnzahl   option.spielbrettBreite * option.spielbrettHoehe

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
