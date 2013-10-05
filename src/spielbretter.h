#ifndef SPIELBRETTER_H_
#define SPIELBRETTER_H_
#include <glib-2.0/glib.h>

typedef struct spielbretter
{
	/* Array für die Pointer auf die Hashtabellen für 2-10 Figuren.
	 * Die Felder 0 und 1 werden nicht benutzt.
	 */  
	GHashTable* spielbretterHashtables[11]; 
    
    /* variablen in den gespeichert ist in welcher Hashtabelle welche Bretter sind*/
    int aktuelleSpielbretter;
    int vorgaengerSpielbretter;
    
    /* MPI Prozessanzahl und Przessnummer */
    int prozessNummer;
    int anzahlProzesse;
	
    /* Anzahl der Bretter */
    long anzahlBretter[11];
    long anzahlBretterGesamt;
    
    /* Anzahl loesbarer Bretter insgesammt */
    long loesbareBretter[11];
    long loesbareBretterGesamt;
    
    /* Zeiten zum lösen der Spielbretter */
    double berechnungsZeit[11];
    double berechnungsZeitMin[11];
    double berechnungsZeitMax[11];
    double berechnungsZeitAvg[11];
    double berechnungsZeitGesamt;
	
}spielbretter_t;



/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * für eine variable Spielbrettgröße.
 * Hierbei wird figurenweise vorgegangen. Die Figuren werden auf die 
 * Felder gesetzt. Dabei kommt es zur Mehrfacherzeugung von gleichen
 * Brettern, wenn es mehr als 10 Felder auf dem Spielbrett gibt. 
 */
void spielbretter_berechne(spielbretter_t *bretter);


/**
 * Löscht alle übergebenen Spielbretter.
 */ 
void spielbretter_destruct(spielbretter_t* bretter);

#endif
