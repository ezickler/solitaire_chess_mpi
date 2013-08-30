#include "main.h"




/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
void erzeugeHashtables(){
	int figurenAnzahl;
	for(figurenAnzahl=2; figurenAnzahl<=10; figurenAnzahl++){
		_spielbretterHashtables[figurenAnzahl] = g_hash_table_new ( g_direct_hash, g_direct_equal);
	}
}

char** init_spielbrett_array(int hoehe, int breite)
{
	int n;
	char** tmp_array;
	tmp_array = calloc(hoehe, sizeof(char*));
	for(n = 0; n < hoehe; n++)
	{
		tmp_array[n] = calloc(breite, sizeof(char));
	}
	return tmp_array;
}

void destruct_spielbrett_array(char** array, int hoehe)
{	//TODO: valgrind Speicherleck durch free? (eigtl nicht)s
	int n;
	for(n = 0 ;n < hoehe;n ++)
	{
	 free(array[n]);
	}
	free(array);
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
void berechneSpielbrett(gpointer spielbrett, gpointer loesbar, gpointer anzahlFiguren ){
	
	// TODO: auf struct umstellen!
	
	int *geloest = (int*) loesbar;
    int x, y;
    for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            _spielbrett_array[x][y] = ((*((long long*) spielbrett) >> (x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }
      

     for(x=0; x<4 && *geloest == 0; x++){
		for(y=0; y<4 && *geloest == 0; y++){
			switch(_spielbrett_array[x][y]){
				case DarstellungBauer:
				//TODO: Parameterübergabe überprüfen! 
					*geloest= berechneBauer(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
				case DarstellungTurm:
					*geloest = berechneTurm(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
				case DarstellungLaeufer:
					*geloest = berechneLaeufer(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
				case DarstellungSpringer:
					*geloest = berechneSpringer(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
				case DarstellungKoenig:
					*geloest = berechneKoenig(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
				case DarstellungDame:
					*geloest = berechneDame(_spielbrett_array, spielbrett, x, y, anzahlFiguren);
					break;
			}
		}
	}
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen
 *
 */
void berechneSpielbretter(GHashTable spielbretter){
	//TODO: WO soll die eigentlich mal hin? Datei?
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
	_spielbrett_array = init_spielbrett_array(SpielbrettHoehe, SpielbrettBreite);
	
	berechneSpielbretter(_spielbretterHashtables);
	destruct_spielbrett_array(_spielbrett_array, SpielbrettHoehe);
	return EXIT_SUCCESS;	
}
