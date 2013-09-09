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
	Dez			Binär	
	0 Frei		000
	1 Bauer		001
	2 Turm		010
	3 Läufer	011
	4 Springer	100
	5 König		101
	6 Dame		110
*/



/**
 * Hilfsfunktion, die bestimmt, ob auf auf einem übergebenen Brett an einer übergeben Posistion eine Figur steht.
 *
 * @param position *int 
 * @param spielbrett *long long
 * @return bool
 */
bool feldFrei(int* position, long long* spielbrett)
{
	return (((*spielbrett >> (*position * 3)) % 8) == DarstellungLeer);
}

/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
 void erzeugeHashtables(spielbretter_t *bretter){
	 printf("Beginn erzeugeHashtables\n");
	int figurenAnzahl;
	for(figurenAnzahl=0; figurenAnzahl<=10; figurenAnzahl++){
		bretter->spielbretterHashtables[figurenAnzahl] = g_hash_table_new(g_direct_hash, g_direct_equal);
	}
}

/**
 * Gibt den Speicher des Parameters frei.
 */
void spielbretter_destruct(spielbretter_t* bretter)
{
	printf("Beginn spielbretter_destruct\n");
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
	
	//TODO: Spielbretter mit einer Figur in Hashtable als gelöst abspeichern!
	printf("Beginn spielbretter_create\n");
	/* Spielbrettvariablen, für die verschiedenen Ebenen der for-Schleifen, 
	 * da jede Schleife eigene lokale Variablen braucht, um Überschreiben zu verhindern
	 * Alternative: Zurückrechnen, am Ende der jeweiligen Schleife - aufwendiger */
	long long spielbrett_Leer,
			  spielbrett_Dame,
			  spielbrett_Koenig,
			  spielbrett_Springer1, spielbrett_Springer2,
			  spielbrett_Laeufer1, spielbrett_Laeufer2,
			  spielbrett_Turm1, spielbrett_Turm2,
			  spielbrett_Bauer1, spielbrett_Bauer2;
			  
	/*Anzahl der maximal noch setzbaren Figuren
	 * verschiedene Ebenen der for-Schleifen brauchen eigene lokale Variablen, um Überschreiben zu verhindern */
	int anzFiguren_Start,
		anzFiguren_Dame,
		anzFiguren_Koenig,
		anzFiguren_Springer1, anzFiguren_Springer2,
		anzFiguren_Laeufer1, anzFiguren_Laeufer2,
		anzFiguren_Turm1, anzFiguren_Turm2,
		anzFiguren_Bauer1, anzFiguren_Bauer2;
		
	/* Position der jeweiligen Figuren*/
	int posDame,
		posKoenig, 
		posSpringer1, posSpringer2, 
		posLaeufer1, posLaeufer2,
		posTurm1, posTurm2,
		posBauer1, posBauer2;
		
	/* hält das Array von Pointern auf die verschiedenen Hashtables sowie die Anzahl der Figuren */
	spielbretter_t *bretter;



	/** Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;
	spielbrett_Leer = 0;
	bretter = malloc(sizeof(spielbretter_t));
	anzFiguren_Start=10;
	
	erzeugeHashtables(bretter);
	
	
	
	/* Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
	 * für alle anderen Figuren analog!*/
	for(posDame=0; posDame<=anzFelder; posDame++)
	{	
		printf("setze Spielfiguren \n");
		anzFiguren_Dame = anzFiguren_Start;
		/* posDame * 3, da die Figurenrepräsentation Oktal erfolgt und 3 Binärstellen eine Oktalstelle sind*/
		if(posDame<anzFelder)
		{
			printf("setzeDame %d \n",posDame);
			spielbrett_Dame = spielbrett_Leer +  (DarstellungDame << posDame*3); 
		}
		/* Keine Dame gesetzt worden*/
		else
		{
			anzFiguren_Dame --;
		}
		printf("debug g_hash_table_insert Dame: %d AnzahlFiguren: %d\n", posDame, anzFiguren_Dame);

		/* Iteration für den König */
		for(posKoenig=0; posKoenig<=anzFelder; posKoenig++)
		{	
			anzFiguren_Koenig = anzFiguren_Dame;
			if(posKoenig<anzFelder && feldFrei(&posKoenig, &spielbrett_Dame))
			{
				printf("setzeKönig %d \n", posKoenig);
				spielbrett_Koenig = spielbrett_Dame + (DarstellungKoenig << posKoenig*3); 
			}
			else
			{
				anzFiguren_Koenig --;
			}
			printf("debug g_hash_table_insert König: %d AnzahlFiguren: %d\n", posKoenig, anzFiguren_Koenig);
			
			/* Iteration für den Springer */
			for(posSpringer1=0; posSpringer1<=anzFelder; posSpringer1++)
			{
				anzFiguren_Springer1 = anzFiguren_Koenig;
				if(posSpringer1<anzFelder && feldFrei(&posSpringer1, &spielbrett_Koenig))
				{
					spielbrett_Springer1 = spielbrett_Koenig + (DarstellungSpringer << posSpringer1*3); 
				}
				else
				{
					anzFiguren_Springer1 --;
				}
				printf("debug g_hash_table_insert Springer1: %d AnzahlFiguren: %d\n", posSpringer1, anzFiguren_Springer1);
				
				/* Iteration für den Springer2 
				 * geänderte Startposition, um Duplikate zu vermeiden
				 * analog für andere doppelte Figuren */
				for(posSpringer2=posSpringer1+1; posSpringer2<=anzFelder; posSpringer2++)
				{
					anzFiguren_Springer2 = anzFiguren_Springer1;
					if(posSpringer2<anzFelder && feldFrei(&posSpringer2, &spielbrett_Springer1))
					{
						spielbrett_Springer2 = spielbrett_Springer1 + (DarstellungSpringer << posSpringer2*3);
					}
					else
					{
						anzFiguren_Springer2 --;
					}
					//printf("debug g_hash_table_insert Springer2: %d AnzahlFiguren: %d\n", posSpringer2, anzFiguren_Springer2); 
					
					/* Iteration für den Läufer1 */
					for(posLaeufer1=0; posLaeufer1<=anzFelder; posLaeufer1++)
					{
						anzFiguren_Laeufer1 = anzFiguren_Springer2;
						if(posLaeufer1<anzFelder && feldFrei(&posLaeufer1, &spielbrett_Springer2))
						{
							spielbrett_Laeufer1 = spielbrett_Springer2 + (DarstellungLaeufer << posLaeufer1*3);
							//printf("debug g_hash_table_insert Läufer1: %d AnzahlFiguren: %d\n", posLaeufer1, anzFiguren_Laeufer1);
						}
						else
						{
							anzFiguren_Laeufer1--;
						}

						/* Iteration für den Läufer2 */
						for(posLaeufer2=posLaeufer1+1; posLaeufer2<=anzFelder; posLaeufer2++)
						{
							anzFiguren_Laeufer2 = anzFiguren_Laeufer1;
							if(posLaeufer2<anzFelder && feldFrei(&posLaeufer2, &spielbrett_Laeufer1))
							{
								spielbrett_Laeufer2 = spielbrett_Laeufer1 + (DarstellungLaeufer << posLaeufer2*3);
								//printf("debug g_hash_table_insert Läufer2: %d AnzahlFiguren: %d\n", posLaeufer2, anzFiguren_Laeufer2);
							}
							else
							{
								anzFiguren_Laeufer2--;
							}

							/* Iteration für den Turm1 */
							for(posTurm1=0; posTurm1<=anzFelder; posTurm1++)
							{
								anzFiguren_Turm1 = anzFiguren_Laeufer2;
								if(posTurm1<anzFelder && feldFrei(&posTurm1, &spielbrett_Laeufer2))
								{
									spielbrett_Turm1 = spielbrett_Laeufer2 + (DarstellungTurm << posTurm1+3);
									//printf("debug g_hash_table_insert Turm1: %d AnzahlFiguren: %d\n", posTurm1, anzFiguren_Turm1);
								}
								else
								{
									anzFiguren_Turm1--;
								}
								
								/* Iteration für den Turm2 */
								for(posTurm2=posTurm1+1; posTurm2<=anzFelder; posTurm2++)
								{
									anzFiguren_Turm2 = anzFiguren_Turm1;
									if(posTurm2<anzFelder && feldFrei(&posTurm2, &spielbrett_Turm1))
									{
										spielbrett_Turm2 = spielbrett_Turm1 + (DarstellungTurm << posTurm2*3);
										}
									else
									{
										anzFiguren_Turm2--;
									}
									//printf("debug g_hash_table_insert Turm2: %d AnzahlFiguren: %d\n", posTurm2, anzFiguren_Turm2);
									
									/* Iteration für den Bauer1 */
									for(posBauer1=0; posBauer1<=anzFelder; posBauer1++)
									{
										anzFiguren_Bauer1 = anzFiguren_Turm2;
										if(posBauer1<anzFelder && feldFrei(&posBauer1, &spielbrett_Turm2))
										{
											spielbrett_Bauer1 = spielbrett_Turm2 + (DarstellungBauer << posBauer1*3);
										}
										else
										{
											anzFiguren_Bauer1--;
										}
										//printf("debug g_hash_table_insert Bauer1: %d AnzahlFiguren: %d\n", posBauer1, anzFiguren_Bauer1);
                                        // Spart die innere Schleife bei zu wenigen Figuren, 
                                        // es können aber trotzdem Bretter mit einer Figur erstellt
                                        if(anzFiguren_Bauer1 > 0)
                                        {

										    /* Iteration für den Bauer2 */
										    for(posBauer2=posBauer1+1; posBauer2<=anzFelder; posBauer2++)
										    {
												anzFiguren_Bauer2 = anzFiguren_Bauer1;
											    if(posBauer2<anzFelder  && feldFrei(&posBauer2, &spielbrett_Bauer1))
											    {
												    spielbrett_Bauer2 = spielbrett_Bauer1 + (DarstellungBauer << posBauer2*3);
												}
											    else
											    {
												    anzFiguren_Bauer2--;
											    }

											    // Bretter mit einer Figur in Hashtable speichern und nachher löschen besser als if-Abfrage?
											    // Mischung, die if Abfrage kommt früher und spart Schleifendurchgaenge, es enstehen
											    // aber trotzdem Bretter mit nur einer Figur.
											   // printf("debug g_hash_table_insert Bauer2: %d AnzahlFiguren: %d\n", posBauer2, anzFiguren_Bauer2);
											    g_hash_table_insert(bretter->spielbretterHashtables[anzFiguren_Bauer2], (gpointer) &spielbrett_Bauer2, (gpointer) 0 );
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
    
    /*Kopieren des Arrays */
    memcpy(param.spielbretterHashtables, bretter->spielbretterHashtables, sizeof(GHashTable*)*11);
    
    param.spielbrett_array = spielbretterArrayCreate(SpielbrettHoehe, SpielbrettBreite);
  
	/* Berechnung der Arraydarstellung aus Oktaldarstellung
	 * einfacher für die Überprüfung der Spielbrettgrenzen*/
    for(x=0; x<4; x++){
        for(y=0; y<4; y++){
            param.spielbrett_array[x][y] = ((*((long long*) spielbrett) >> (x+(y*SpielbrettBreite) * 3)) % 8);
        }
    }
      
	
	/* Berechnet, ob die Figuren an der jeweiligen Position schlagen können und daraus
	 * ein lösbares neues Spielbrett entsteht */
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
	
	//Spielbrett Array wird wieder freigegeben
	spielbretterArrayDestruct(param.spielbrett_array, SpielbrettHoehe);
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne(spielbretter_t *bretter){
	printf("Beginn spielbretter_berechne\n");
    int anzahlFiguren;
    /* Reihenfolge der zu berechnenden Spielbretter nach Anzahl der Figuren (aufsteigend)*/
    for(anzahlFiguren = 2; anzahlFiguren <= 10; anzahlFiguren++){
		printf("Berechnet Spielbretter mit %d Spielfiguren \n", anzahlFiguren);
		bretter->anzahlFiguren = anzahlFiguren;
        g_hash_table_foreach(bretter->spielbretterHashtables[anzahlFiguren], spielbrettBerechne, bretter);
    }
}
