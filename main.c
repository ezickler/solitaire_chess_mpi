#include "main.h"
#include <glib.h>
#include <stdbool.h>

#define SpielbrettBreite	options.spielbrettBreite
#define SpielbrettHoehe		options.spielbrettHoehe
#define SpielfelderAnzahl  16 //TODO in define rechnung aus anderen defines moeglich SpielbrettBreite*SpielbrettHoehe

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


// Array fuer das gerade zuberechnende Spielfeld
char _spielfeld[4][4];

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
 * Berechnet alle Spielbretter aus den Hashtabellen
 *
 */
void brechneSpielbretter(){
    int anzahlFiguren;
    // Reihenfolge der zu berchnenden Speilbrette nach Anzahl der Figuren (aufsteigend)
    for(anzhalfiguren = 2; anzahlFiguren <= 10; anzhalFiguren++){
        //TODO  erweiterte for-Schleife ueber die Hashtabelle _hashtable[figurenAnzahl]
        {
            berechneSpielbrett(spielbrett);
        }
    }
}


/**
 * Berechnet ein einzelnes Spielbrett.
 * Funktioniert nur, wenn die Spielbretter mit weniger Figuren bereits berechnet 
 * sind!
 */
void brerchneSpielbrett(long long spielbrett){
     int pos; // Position auf dem Spielbrett die gerade betrachtet wird
     int x, y;
     // UMSTELLUNG AUF ARRAY (noch in abriet)
     for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            _spielbrett[x][y] = ((spielbrett >> ((x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }
     int figur; // Darstellung der Feldbelegung an der jeweiligen Position
     int loesbar = 0; // wird gesezt wenn ein Nachfolger gefunden ist
     for(pos = 0; pos < SpielfelderAnzahl && loesbar == 0; pos++){
        figur = (pos >> (spielfeld * 3)) % 8;
        switch(figur){
            case DarstellungBauer:
                loesbar = berechneBauer(pos);
                break;
            case DarstellungTurm:
                loesbar = berechneTurm(pos);
                break;
            case DarstellungLaeufer:
                loesbar = berechneLaeufer(pos);
                break;
            case DarstellungSpringer:
                loesbar = berechneSpringer(pos);
                break;
            case DarstellungKoenig:
                loesbar = berechneKoenig(pos);
                break;
            case DarstellungDame:
                loesbar = berechneDame(pos);
                break;
            default:
                //TODO müssen irgendwelche Dinge für jeden Fall gemacht werden?
                break;
        }
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
	
	// berechneSpielbretter();
	
	return EXIT_SUCCESS;
	
}
