#include "spielbretter.h"
#include "spielfiguren.h"
#include <stdbool.h>


/**

Spielbrett:

Links-Oben 0:0 nach x:y

  0, 1, 2, 3
  4, 5, 6, 7
  8, 9,10,11
 12,13,14,15


Repräsentation des Spielbrettbelegung in einem long long (64bit-integer)
Pro Figur werden drei Bit benötigt.
Beginnend mit dem Spielfeld "15" werden die Belegungen der einzelnen Felder von vorn nach hinten im 
long long codiert. 
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
Die Dreierbitblöcke werden von links nach rechts ausgewertet.
z.B.: 000....000010 bedeutet ein Turm auf Feld 0 (also links oben).


Repräsentation der Spielfiguren auf dem Brett:
	Dez			Code	
	0 Frei		000
	1 Bauer		001
	2 Turm		010
	3 Läufer	011
	4 Springer	100
	5 König		101
	6 Dame		110
*/



/**
 * Hilfsfunktion die bestimmt ob auf auf einem uebergebenen Brett an einer uebergeben Posistion eine Figur steht.
 *
 * @param position *int 
 * @param spielbrett *long long
 * @return bool
 */
bool feldBelegt(int* position, long long* spielbrett)
{
	return (*spielbrett >> (*position * 3)) % 8 == DarstellungLeer;
}

/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
 void erzeugeHashtables(spielbretter_t *bretter){
	int figurenAnzahl;
	for(figurenAnzahl=2; figurenAnzahl<=10; figurenAnzahl++){
		bretter->spielbretterHashtables[figurenAnzahl] = g_hash_table_new ( g_direct_hash, g_direct_equal);
	}
}

void spielbretter_destruct(spielbretter_t* bretter)
{
	free(bretter);
}

/**
 * Alloziert das Array zum Zwischenspeichern des Brettes.
 */
char** spielbretterArrayCreate(int hoehe, int breite)
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

/**
 * Gibt den Speicher des zweidimensionalen Arrays frei.
 */
void spielbretterArrayDestruct(char** array, int hoehe)
{
	int n;
	for(n = 0 ;n < hoehe;n ++)
	{
	 free(array[n]);
	}
	free(array);
}

/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 *
 */
spielbretter_t* spielbretter_create(){
	long long spielbrett;
	int anzFiguren;
	int posDame, 
		posKoenig, 
		posSpringer1, posSpringer2, 
		posLaeufer1, posLaeufer2,
		posTurm1, posTurm2,
		posBauer1, posBauer2;
	spielbretter_t *bretter;



	/** Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;
	
	bretter = malloc(sizeof(spielbretter_t));
	
	erzeugeHashtables(bretter);
	

	/* Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
	 * für alle anderen Figuren analog!*/
	for(posDame=0; posDame<=anzFelder; posDame++){
		anzFiguren=10;
		/* posDame * 3, da die Figurenrepräsentation Oktal erfolgt und 3 Binärstellen eine Oktalstelle sind*/
		if(posDame<anzFelder && feldBelegt(&posDame, &spielbrett)){
			spielbrett += posDame *8* DarstellungDame; 
		}
		/* Keine Dame gesetzt worden*/
		else{
			anzFiguren--;
		}

		/* Iteration für den König */
		for(posKoenig=0; posKoenig<=anzFelder; posKoenig++){
			if(posKoenig<anzFelder && feldBelegt(&posKoenig, &spielbrett)){
				spielbrett += posKoenig *8* DarstellungKoenig; 
			}
			else{
				anzFiguren--;
			}
			
			/* Iteration für den Springer */
			for(posSpringer1=0; posSpringer1<=anzFelder; posSpringer1++){
				if(posSpringer1<anzFelder && feldBelegt(&posSpringer1, &spielbrett)){
					spielbrett += posSpringer1 *8* DarstellungSpringer; 
				}
				else{
					anzFiguren--;
				}
				
				/* Iteration für den Springer2 
				 * geänderte Startposition, um Duplikate zu vermeiden
				 * analog für andere doppelte Figuren */
				for(posSpringer2=posSpringer1+1; posSpringer2<=anzFelder; posSpringer2++){
					if(posSpringer2<anzFelder && feldBelegt(&posSpringer2, &spielbrett)){
						spielbrett += posSpringer2 *8* DarstellungSpringer; 
					}
					else{
						anzFiguren--;
					}
					
					/* Iteration für den Laeufer1 */
					for(posLaeufer1=0; posLaeufer1<=anzFelder; posLaeufer1++){
						if(posLaeufer1<anzFelder && feldBelegt(&posLaeufer1, &spielbrett)){
							spielbrett += posLaeufer1 *8* DarstellungLaeufer;
						}
						else{
							anzFiguren--;
						}

						/* Iteration für den Laeufer2 */
						for(posLaeufer2=posLaeufer1+1; posLaeufer2<=anzFelder; posLaeufer2++){
							if(posLaeufer2<anzFelder && feldBelegt(&posLaeufer2, &spielbrett)){
								spielbrett += posLaeufer2 *8* DarstellungLaeufer;
							}
							else{
								anzFiguren--;
							}

							/* Iteration für den Turm1 */
							for(posTurm1=0; posTurm1<=anzFelder; posTurm1++){
								if(posTurm1<anzFelder && feldBelegt(&posTurm1, &spielbrett)){
									spielbrett += posTurm1 *8* DarstellungTurm;
								}
								else{
									anzFiguren--;
								}
								
								/* Iteration für den Turm2 */
								for(posTurm2=posTurm1+1; posTurm2<=anzFelder; posTurm1++){
									if(posTurm2<anzFelder && feldBelegt(&posTurm2, &spielbrett)){
										spielbrett += posTurm2 *8* DarstellungTurm;
									}
									else{
										anzFiguren--;
									}
									
									/* Iteration für den Bauer1 */
									for(posBauer1=0; posBauer1<=anzFelder; posBauer1++){
										if(posBauer1<anzFelder && feldBelegt(&posBauer1, &spielbrett)){
											spielbrett += posBauer1 *8* DarstellungBauer;
										}
										else{
											anzFiguren--;
										}
                                        // Spart die innere Schleife bei zu wenigen Figuren, 
                                        // es koennen aber trotzdem Bretter mit einer Figur erstellt
                                        if(anzFiguren > 0){

										    /* Iteration für den Bauer2 */
										    for(posBauer2=posBauer1+1; posBauer2<=anzFelder; posBauer2++){
											    if(posBauer2<anzFelder  && feldBelegt(&posBauer2, &spielbrett)){
												    spielbrett += posBauer2 *8* DarstellungBauer;
											    }
											    else{
												    anzFiguren--;
											    }

											    // Bretter mit einer Figur in Hashtable speichern und nachher löschen besser als if-Abfrage?
											    // Mischung, die if Abfrage kommt frueher und spart Schleifen durchgaenge, es enstehen
											    // aber trotzdem Bretter mit nur einer Figur.
											    // TODO: gpointer übergeben??
											    g_hash_table_insert(bretter->spielbretterHashtables[anzFiguren], &spielbrett, 0 ); 
											    //TODO:  spielbrett = 0; setzen NOTWENDIG?
											    }
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return bretter;
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
void spielbrettBerechne(gpointer spielbrett, gpointer loesbar, gpointer bretter_ptr ){
	
	int *geloest = (int*) loesbar;
	spielbretter_t *bretter = (spielbretter_t*) bretter_ptr;
    int x, y;
    figuren_param_t param;
    
    memcpy(param.spielbretterHashtables, bretter->spielbretterHashtables, sizeof(GHashTable*)*11);
    param.spielbrett_array = spielbretterArrayCreate(SpielbrettHoehe, SpielbrettBreite);
  
    for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            param.spielbrett_array[x][y] = ((*((long long*) spielbrett) >> (x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }
      

     for(x=0; x<4 && *geloest == 0; x++){
		for(y=0; y<4 && *geloest == 0; y++){
			switch(param.spielbrett_array[x][y]){
				case DarstellungBauer:
					*geloest= berechneBauer(&param, x, y);
					break;
				case DarstellungTurm:
					*geloest = berechneTurm(&param, x, y);
					break;
				case DarstellungLaeufer:
					*geloest = berechneLaeufer(&param, x, y);
					break;
				case DarstellungSpringer:
					*geloest = berechneSpringer(&param, x, y);
					break;
				case DarstellungKoenig:
					*geloest = berechneKoenig(&param, x, y);
					break;
				case DarstellungDame:
					*geloest = berechneDame(&param, x, y);
					break;
			}
		}
	}
	spielbretterArrayDestruct(param.spielbrett_array, SpielbrettHoehe);
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne(spielbretter_t *bretter){
	
    int anzahlFiguren;
    /* Reihenfolge der zu berechnenden Spielbretter nach Anzahl der Figuren (aufsteigend)*/
    for(anzahlFiguren = 2; anzahlFiguren <= 10; anzahlFiguren++){
		bretter->anzahlFiguren = anzahlFiguren;
        g_hash_table_foreach(bretter->spielbretterHashtables[anzahlFiguren], spielbrettBerechne, bretter);
    }
}
