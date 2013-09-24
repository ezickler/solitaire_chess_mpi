/**
 * Diese Datei stellt Funktionen bereit, um zu entscheiden, ob eine 
 * bestimmte Figur an einer bestimmten Stelle auf einem gegebenen Feld
 * irgendeine andere Figur schlagen kann. Ist eine Zug möglich, so wird 
 * dies zurück gegeben, ohne weitere Möglichkeiten zu berechnen.
 * 
 */ 

#ifndef SPIELFIGUREN_H_
#define SPIELFIGUREN_H_

#include <stdint.h>
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


/*
 * Typ für die oktal darstellung der Spielbretter
 */
typedef uint64_t sp_okt_t;


/*
 * Struct um die Signaturen der Figuren übersichlich zu halten. 
 */ 
typedef struct figuren_param{
	char **spielbrett_array; 
	sp_okt_t* spielbrett; 
	int anzahlFiguren;
	GHashTable* spielbretterHashtables[11]; 
	
}figuren_param_t;

/**
 * Prüft, ob ein Zug mit diesem Bauer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
 
int berechneBauer(figuren_param_t *param, int x, int y);
/**
 * Prüft, ob ein Zug mit diesem Turm an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
int berechneTurm(figuren_param_t *param, int x, int y);

/**
 * Prüft, ob ein Zug mit diesem Läufer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
int berechneLaeufer(figuren_param_t *param, int x, int y);

/**
 * Prüft, ob ein Zug mit diesem Springer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
int berechneSpringer(figuren_param_t *param, int x, int y);

/**
 * Prüft, ob ein Zug mit diesem König an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
int berechneKoenig(figuren_param_t *param, int x, int y);

/**
 * Prüft, ob ein Zug mit dieser Dame an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 * 
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */ 
int berechneDame(figuren_param_t *param, int x, int y);



#endif
