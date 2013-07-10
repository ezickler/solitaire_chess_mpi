#include "main.h"

#define SpielbrettBreite	4
#define SpielbrettHoehe		4


/**
 * Erzeugt alle möglichen Spielbretter mit bis zu 10 Spielfiguren
 *
 */

long long *erzeugeSpielbretter(){

	long long *spielbretter;


	// Anzhl der Felder über die Iteriert werden muss
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;

	// Iteration für die Dame über alle Felder und eine zusätzlicher durchlauf für keine Dame
	for(int dame=0; dame<=anzFelder; dame++){
		int *spielbrett;
		// Im Letzten Iterationsschtritt keine Dame setzen
		if(dame<anzFelder && spielbrett[dame]==0){
			//TODO Dame auf Positon dame setzen z.B spielbrett[dame] = 6
		}

		// Iteration für den König
		for(int koenig=0; koenig<=anzFelder; koenig++){
			if(koenig<anzFelder && spielbrett[koenig]==0){
				//TODO König auf Positon koenig setzen z.B spielbrett[koenig] = 5
			}

			// Iteration für den Springer
			for(int springer1=0; springer1<=anzFelder; springer1++){
				if(springer1<anzFelder && spielbrett[springer1]==0){
					//TODO Springer1 auf Positon springer1 setzen z.B spielbrett[springer1] = 4
				}
				// Iteration für den Springer
				for(int springer2=0; springer2<=anzFelder; springer2++){
					if(springer1<anzFelder && spielbrett[springer1]==0){
						//TODO Springer2 auf Positon springe2 setzen z.B spielbrett[springer2] = 4
					}

					for(int laeufer1=0; laeufer1<=anzFelder; laeufer1++){
						if(laeufer1<anzFelder && spielbrett[laeufer1]==0){
							//TODO Läufer1 auf Positon laeufer1 setzen z.B spielbrett[laeufer1] = 3
						}

						for(int laeufer2=0; laeufer2<=anzFelder; laeufer2++){
							if(laeufer2<anzFelder && spielbrett[laeufer2]==0){
								//TODO Läufer2 auf Positon laeufer2 setzen z.B spielbrett[laeufer2] = 3
							}

							for(int turm1=0; turm1<=anzFelder; turm1++){
								if(turm1<anzFelder && spielbrett[turm1]==0){
									//TODO Läufer2 auf Positon turm1 setzen z.B spielbrett[turm1] = 2
								}

								for(int turm2=0; turm2<=anzFelder; turm2++){
									if(turm2<anzFelder && spielbrett[turm2]==0){
										//TODO Turm2 auf Positon turm2 setzen z.B spielbrett[turm2] = 2
									}

									for(int bauer1=0; bauer1<=anzFelder; bauer1++){
										if(bauer1<anzFelder){
											//TODO Bauer1 auf Positon bauer1 setzen z.B spielbrett[bauer1] = 1
										}

										for(int bauer2=0; bauer2<=anzFelder; bauer2++){
											if(bauer2<anzFelder){
												//TODO Bauer2 auf Positon bauer2 setzen z.B spielbrett[bauer2] = 1
											}


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
	
	return EXIT_SUCCESS;
	
}
