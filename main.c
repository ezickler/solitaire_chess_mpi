#include "main.h"

int berechneDame(int x, int y);

int berechneKoenig(int x, int y);
int berechneSpringer(int x, int y);
int berechneLaeufer(int x, int y);
int berechneTurm(int x, int y);
int berechneBauer(int x, int y);


#define SpielbrettBreite	options.spielbrettBreite
#define SpielbrettHoehe		options.spielbrettHoehe
#define SpielfelderAnzahl  16 //TODO in define rechnung aus anderen defines moeglich SpielbrettBreite*SpielbrettHoehe




// Array fuer die Pointer auf die Hashtabelen fuer 2-10 Figuren.
// Die Felder 0 und 1 werden nicht benutzt.
GHashTable* _spielbretterHashtables[11]; 


// Array fuer das gerade zuberechnende Spielfeld
char _spielbrett[4][4];

/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
void erzeugeHashtables(){
	int figurenAnzahl;
	for(figurenAnzahl=2; figurenAnzahl<=10; figurenAnzahl++){
		_spielbretterHashtables[figurenAnzahl] = g_hash_table_new ( g_direct_hash, g_direct_equal);
	}
}




/**
 * Berechnet ein einzelnes Spielbrett.
 * Funktioniert nur, wenn die Spielbretter mit weniger Figuren bereits berechnet 
 * sind!
 * Signatur nach GHRFunc() aus der gnome library 
 * 
 * @param spielbrett gpointer (eigentlich long long *)
 * @param loesbar gpointer (eigentlich int*)
 * @param notUsed gpointer ( fuer GHFunktion vorgeschrieben hier aber nicht benutzt) 
 * 
 */
void berechneSpielbrett(gpointer spielbrett, gpointer loesbar, gpointer notUsed){
  
     int x, y;
     // UMSTELLUNG AUF ARRAY (noch in arbeit)
     for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            _spielbrett[x][y] = ((*((long long*) spielbrett) >> (x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }

     int geloest= 0; // wird gesezt, wenn ein Nachfolger gefunden ist     
     for(x=0; x<4 && geloest == 0; x++){
		for(y=0; y<4 && geloest == 0; y++){
			switch(_spielbrett[x][y]){
				case DarstellungBauer:
					geloest = berechneBauer(x, y);
					break;
				case DarstellungTurm:
					geloest = berechneTurm(x, y);
					break;
				case DarstellungLaeufer:
					geloest = berechneLaeufer(x, y);
					break;
				case DarstellungSpringer:
					geloest = berechneSpringer(x, y);
					break;
				case DarstellungKoenig:
					geloest = berechneKoenig(x, y);
					break;
				case DarstellungDame:
					geloest = berechneDame(x, y);
					break;
				default:
					//TODO müssen irgendwelche Dinge für jeden Fall gemacht werden?
					break;
			}
		}
	}
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen
 *
 */
void berechneSpielbretter(){
    int anzahlFiguren;
    // Reihenfolge der zu berechnenden Spielbretter nach Anzahl der Figuren (aufsteigend)
    for(anzahlFiguren = 2; anzahlFiguren <= 10; anzahlFiguren++){
        //TODO  erweiterte for-Schleife ueber die Hashtabelle _hashtable[figurenAnzahl]
        
        g_hash_table_foreach(_spielbretterHashtables[anzahlFiguren], berechneSpielbrett, 0);
    }
}


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char ** argv){
	
	//struct options options;
	
	AskParams(&options, argc, argv);
	
	erzeugeHashtables();
	erzeugeSpielbretter();
	
	// berechneSpielbretter();
	
	return EXIT_SUCCESS;	
}
