#include "main.h"
#include <glib.h>

#define SpielbrettBreite	4
#define SpielbrettHoehe		4

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

/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 *
 */
void erzeugeSpielbretter(){

	long long *spielbretter;

	int *spielbrett;

	int anzFiguren;


	/** Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;

	/*Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
	/* für alle anderen Figuren analog!*/
	for(int dame=0; dame<=anzFelder; dame++){
		anzFiguren=10;
		/* Im Letzten Iterationsschtritt keine Dame setzen*/
		if(dame<anzFelder && spielbrett[dame]==0){
			//Hier steht Pseudocode! Gearbeitet wird eigentlich mit Repräsentation über long long
			//TODO Dame auf Position dame setzen z.B spielbrett[dame] = 6
		}
		else{
			anzFiguren--;
		}

		/* Iteration für den König */
		for(int koenig=0; koenig<=anzFelder; koenig++){
			if(koenig<anzFelder && spielbrett[koenig]==0){
				//TODO König auf Position koenig setzen z.B spielbrett[koenig] = 5
			}
			else{
				anzFiguren--;
			}
			/* Iteration für den Springer */
			for(int springer1=0; springer1<=anzFelder; springer1++){
				if(springer1<anzFelder && spielbrett[springer1]==0){
					//TODO Springer1 auf Position springer1 setzen z.B spielbrett[springer1] = 4
				}
				else{
					anzFiguren--;
				}
				/* Iteration für den Springer2 
				/* geänderte Startposition, um Duplikate zu vermeiden
				/* analog für andere doppelte Figuren */
				for(int springer2=springer1+1; springer2<=anzFelder; springer2++){
					if(springer1<anzFelder && spielbrett[springer1]==0){
						//TODO Springer2 auf Position springe2 setzen z.B spielbrett[springer2] = 4
					}
					else{
						anzFiguren--;
					}

					for(int laeufer1=0; laeufer1<=anzFelder; laeufer1++){
						if(laeufer1<anzFelder && spielbrett[laeufer1]==0){
							//TODO Läufer1 auf Position laeufer1 setzen z.B spielbrett[laeufer1] = 3
						}
						else{
							anzFiguren--;
						}

						for(int laeufer2=laeufer1+1; laeufer2<=anzFelder; laeufer2++){
							if(laeufer2<anzFelder && spielbrett[laeufer2]==0){
								//TODO Läufer2 auf Position laeufer2 setzen z.B spielbrett[laeufer2] = 3
							}
							else{
								anzFiguren--;
							}

							for(int turm1=0; turm1<=anzFelder; turm1++){
								if(turm1<anzFelder && spielbrett[turm1]==0){
									//TODO Läufer2 auf Position turm1 setzen z.B spielbrett[turm1] = 2
								}
								else{
									anzFiguren--;
								}

								for(int turm2=turm1+1; turm2<=anzFelder; turm2++){
									if(turm2<anzFelder && spielbrett[turm2]==0){
										//TODO Turm2 auf Position turm2 setzen z.B spielbrett[turm2] = 2
									}
									else{
										anzFiguren--;
									}

									for(int bauer1=0; bauer1<=anzFelder; bauer1++){
										if(bauer1<anzFelder && spielbrett[bauer1]==0){
											//TODO Bauer1 auf Position bauer1 setzen z.B spielbrett[bauer1] = 1
										}
										else{
											anzFiguren--;
										}

										for(int bauer2=bauer1+1; bauer2<=anzFelder; bauer2++){
											if(bauer2<anzFelder  && spielbrett[bauer2]==0){
												//TODO Bauer2 auf Position bauer2 setzen z.B spielbrett[bauer2] = 1
											}
											else{
												anzFiguren--;
											}

											if (anzFiguren > 1){
												//TODO Füge spielbrett zu spielbretter hinzu.
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





