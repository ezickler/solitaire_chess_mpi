#ifndef SPIELBRETTER_H_
#define SPIELBRETTER_H_
#include <glib-2.0/glib.h>

typedef struct spielbretter
{
	/* Array für die Pointer auf die Hashtabellen für 2-10 Figuren.
	 * Die Felder 0 und 1 werden nicht benutzt.
	 */  
	GHashTable* spielbretterHashtables[11]; 
	
	/* Anzahl der Figuren auf dem Spielbrett*/
	int anzahlFiguren;
    
    /* Anzahl der Bretter */
    long anzahlBretterGesamt;
    
    /* Anzahl loesbarer Bretter insgesammt */
    long loesbareBretterGesamt;
	
}spielbretter_t;


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne(spielbretter_t *bretter);


/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * Ist noch in Arbeit.
 * Versuch die Spielbrett felderweise zu erzeugen, 
 * um Mehrfacherzeugung zu vermeiden.
 * 
 */
spielbretter_t* spielbretter_create_felderweise();

/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * für eine variable Spielbrettgröße.
 * Hierbei wird figurenweise vorgegangen. Die Figuren werden auf die 
 * Felder gesetzt. Dabei kommt es zur Mehrfacherzeugung von gleichen
 * Brettern, wenn es mehr als 10 Felder auf dem Spielbrett gibt. 
 */
spielbretter_t* spielbretter_create_figurenweise();


/**
 * Löscht alle übergebenen Spielbretter.
 */ 
void spielbretter_destruct(spielbretter_t* bretter);

#endif
