#include "main.h"


#define SpielbrettBreite	options.spielbrettBreite
#define SpielbrettHoehe		options.spielbrettHoehe
#define SpielfelderAnzahl  16 //TODO in define rechnung aus anderen defines moeglich SpielbrettBreite*SpielbrettHoehe




// Array fuer die Pointer auf die Hashtabelen fuer 2-10 Figuren.
// Die Felder 0 und 1 werden nicht benutzt.
GHashTable* _spielbretterHashtables[11]; 


// Array fuer das gerade zuberechnende Spielfeld
char _spielbrett_array[4][4];

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
 * @param anzahlSpielfiguren gpointer (eigentlich *int) 
 * 
 */
void berechneSpielbrett(gpointer spielbrett, gpointer loesbar, gpointer anzahlFiguren){
  
     int x, y;
     for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            _spielbrett_array[x][y] = ((*((long long*) spielbrett) >> (x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }

          
     for(x=0; x<4 && *loesbar == 0; x++){
		for(y=0; y<4 && *loesbar == 0; y++){
			/*
			switch(_spielbrett_array[x][y]){
				case DarstellungBauer:
					*loesbar = berechneBauer(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
				case DarstellungTurm:
					*loesbar = berechneTurm(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
				case DarstellungLaeufer:
					*loesbar = berechneLaeufer(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
				case DarstellungSpringer:
					*loesbar = berechneSpringer(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
				case DarstellungKoenig:
					*loesbar = berechneKoenig(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
				case DarstellungDame:
					*loesbar = berechneDame(&_spielbrett_array, spielbrett, x, y, &anzahlFiguren);
					break;
			}*/
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
        g_hash_table_foreach(_spielbretterHashtables[anzahlFiguren], berechneSpielbrett, &anzahlFiguren);
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
	
	berechneSpielbretter();
	
	return EXIT_SUCCESS;	
}
