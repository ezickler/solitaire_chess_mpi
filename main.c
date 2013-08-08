#include "main.h"
#include <glib.h>
#include <stdbool.h>

#define SpielbrettBreite	4
#define SpielbrettHoehe		4
#define DarstellungLeer	    0
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6

GHashTable* _hashtable[11]; 

/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
void erzeugeHashtables(){
	int figurenAnzahl;
	for(figurenAnzahl=2; figurenAnzahl<=10; figurenAnzahl++){
		_hashtable[figurenAnzahl] = g_hash_table_new ( g_direct_hash(), g_direct_equal());
	}
}

bool feldBelegt(int* position, long long* spielbrett)
{
	return (*spielbrett >> (*position * 3)) % 8 == DarstellungLeer;
}



/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 *
 */
void erzeugeSpielbretter(){
	long long spielbrett;
	int anzFiguren;
	int posDame, 
		posKoenig, 
		posSpringer1, posSpringer2, 
		posLaeufer1, posLaeufer2,
		posTurm1, posTurm2,
		posBauer1, posBauer2;


	/** Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;

	/*Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
	/* für alle anderen Figuren analog!*/
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
				/* geänderte Startposition, um Duplikate zu vermeiden
				/* analog für andere doppelte Figuren */
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

										/* Iteration für den Bauer2 */
										for(posBauer2=posBauer1+1; posBauer2<=anzFelder; posBauer2++){
											if(posBauer2<anzFelder  && feldBelegt(&posBauer2, &spielbrett)){
												spielbrett += posBauer2 *8* DarstellungBauer;
											}
											else{
												anzFiguren--;
											}

											if (anzFiguren > 1){
											//Bretter mit einer Figur in Hashtable speichern und nachher löschen besser als if-Abfrage?
											// TODO: gpointer übergeben??
											// TODO: g_hash_table_insert(_hashtable[anzFiguren], spielbrett, 0 ); 
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



	return spielbretter;
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
	
	return EXIT_SUCCESS;
	
}





