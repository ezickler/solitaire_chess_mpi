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
	
}spielbretter_t;


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne(spielbretter_t *bretter);


/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 */
spielbretter_t* spielbretter_create();


/**
 * Löscht alle übergebenen Spielbretter.
 */ 
void spielbretter_destruct(spielbretter_t* bretter);

#endif
