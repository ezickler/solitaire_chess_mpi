#include "spielbretter.h"
#include "spielfiguren.h"
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>


/**

Spielbrett:

Links-Oben 0:0 nach x:y

  0, 1, 2, 3
  4, 5, 6, 7
  8, 9,10,11
 12,13,14,15
g_direct_equal

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
static inline bool feldFrei(int* position, long long* spielbrett)
{
	return (((*spielbrett >> (*position * 3)) % 8) == DarstellungLeer);
}

/**
 * Hilfsmethode um  Spielbretter mit einer Figur als loebar zu initialisieren.
 * Sigantur nach GHfunc glib 
 */
static void setzeLoesbar(gpointer key, gpointer value, gpointer hash_table)
{
    g_hash_table_replace((GHashTable*) hash_table, key,(gpointer) 1);
}

/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
static inline void erzeugeHashtables(spielbretter_t *bretter){
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
	free(bretter);
}

/**
 * Alloziert das Array zum Zwischenspeichern des Brettes.
 */
static inline char** spielbretterArrayCreate(int breite, int hoehe )
{
	int n;
	char** tmp_array;
	tmp_array = calloc(breite, sizeof(char*));
	for(n = 0; n < breite; n++)
	{
		tmp_array[n] = calloc(hoehe, sizeof(char));
	}
	return tmp_array;
}

/**
 * Gibt den Speicher des zweidimensionalen Arrays frei.
 */
static inline void spielbretterArrayDestruct(char** array, int breite)
{
	int n;
	for(n = 0 ;n < breite;n ++)
	{
	 free(array[n]);
	}
	free(array);
}

/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * für eine variable Spielbrettgröße.
 * Hierbei wird figurenweise vorgegangen. Die Figuren werden auf die 
 * Felder gesetzt. Dabei kommt es zur Mehrfacherzeugung von gleichen
 * Brettern, wenn es mehr als 10 Felder auf dem Spielbrett gibt. 
 */
//~ spielbretter_t* spielbretter_create_felderweise()
//~ {
    //~ /* Anzahl der Felder, über die iteriert werden muss */
	//~ //int anzFelder = SpielbrettBreite * SpielbrettHoehe;
    //~ 
    //~ /* hält das Array von Pointern auf die verschiedenen Hashtables sowie die Anzahl der Figuren */
	//~ spielbretter_t *bretter;
    //~ 
    //~ 
    //~ return bretter;
//~ }

/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * für eine variable Spielbrettgröße.
 * Hierbei wird figurenweise vorgegangen. Die Figuren werden auf die 
 * Felder gesetzt. Dabei kommt es zur Mehrfacherzeugung von gleichen
 * Brettern, wenn es mehr als 10 Felder auf dem Spielbrett gibt. 
 */
spielbretter_t* spielbretter_create_figurenweise()
{
    
    /*Zähler für die anzahl der generierten Spielbretter*/
    long zaehler_bretter = 0;
    long zaehler_bretter_zwischenstand = 0;
    
    /*Zähler für die anzahl der verschiedenen Bretter in den Hashtabellen*/
    long summe_anzahl_vergleich = 0;
    long summe_anzahl = 0;
    
    
    /* time measurement variables */
    struct timeval start_time;       /* time when program started                      */
    struct timeval comp_time;        /* time when calculation completed                */
    struct timeval comp_time_1;      /* zeit vom letzten zwischenstand */
    struct timeval comp_time_2;      /* vergleichszeit beim aktuellen zwischenstand */
    
    
    gettimeofday(&start_time, NULL);
    gettimeofday(&comp_time_1, NULL); 
      
	

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



	/* Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;
	spielbrett_Leer = 0;
	bretter = malloc(sizeof(spielbretter_t));
	anzFiguren_Start = 0;
	spielbrett_Bauer2 = 0;
	
	erzeugeHashtables(bretter);
	
    
	
	
	/* Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
	 * für alle anderen Figuren analog!*/
	for(posDame=0; posDame<=anzFelder; posDame++)
	{	
		anzFiguren_Dame = anzFiguren_Start;
        spielbrett_Dame = spielbrett_Leer;
		
		if(posDame<anzFelder)
		{
            /* posDame * 3, da die Figurenrepräsentation Oktal erfolgt und 3 Binärstellen eine Oktalstelle sind*/
            spielbrett_Dame +=  (DarstellungDame << posDame*3);
            anzFiguren_Dame ++; 
        }
        /* Iteration für den König */
        for(posKoenig=0; posKoenig<=anzFelder; posKoenig++)
        {	
            anzFiguren_Koenig = anzFiguren_Dame;
            spielbrett_Koenig = spielbrett_Dame;
            if(feldFrei(&posKoenig, &spielbrett_Dame))
            {
                if(posKoenig<anzFelder)
                {
                    spielbrett_Koenig += (DarstellungKoenig << posKoenig*3);
                    anzFiguren_Koenig ++; 
                }
                
                /* Iteration für den Springer */
                for(posSpringer1=0; posSpringer1<=anzFelder; posSpringer1++)
                {
                    anzFiguren_Springer1 = anzFiguren_Koenig;
                    spielbrett_Springer1 = spielbrett_Koenig;
                    if(feldFrei(&posSpringer1, &spielbrett_Koenig))
                    {
                        if(posSpringer1<anzFelder)
                        {
                            spielbrett_Springer1 += (DarstellungSpringer << posSpringer1*3); 
                            anzFiguren_Springer1 ++;
                        }
                        
                        /* Iteration für den Springer2 
                         * geänderte Startposition, um Duplikate zu vermeiden
                         * analog für andere doppelte Figuren */
                        for(posSpringer2=posSpringer1; posSpringer2<=anzFelder; posSpringer2++)
                        {
                            anzFiguren_Springer2 = anzFiguren_Springer1;
                            spielbrett_Springer2 = spielbrett_Springer1;
                            if(feldFrei(&posSpringer2, &spielbrett_Springer1))
                            {
                                if(posSpringer2<anzFelder)
                                {
                                    spielbrett_Springer2 += (DarstellungSpringer << posSpringer2*3);
                                    anzFiguren_Springer2 ++;
                                }
                                
                                /* Iteration für den Läufer1 */
                                for(posLaeufer1=0; posLaeufer1<=anzFelder; posLaeufer1++)
                                {
                                    anzFiguren_Laeufer1 = anzFiguren_Springer2;
                                    spielbrett_Laeufer1 = spielbrett_Springer2;
                                    if(feldFrei(&posLaeufer1, &spielbrett_Springer2))
                                    {
                                        if(posLaeufer1<anzFelder)
                                        {
                                            spielbrett_Laeufer1 += (DarstellungLaeufer << posLaeufer1*3);
                                            anzFiguren_Laeufer1++;
                                        }

                                        /* Iteration für den Läufer2 */
                                        for(posLaeufer2=posLaeufer1; posLaeufer2<=anzFelder; posLaeufer2++)
                                        {
                                            anzFiguren_Laeufer2 = anzFiguren_Laeufer1;
                                            spielbrett_Laeufer2 = spielbrett_Laeufer1;
                                            if(feldFrei(&posLaeufer2, &spielbrett_Laeufer1))
                                            {
                                                if(posLaeufer2<anzFelder)
                                                {    
                                                    spielbrett_Laeufer2 += (DarstellungLaeufer << posLaeufer2*3);
                                                    anzFiguren_Laeufer2++;
                                                }

                                                /* Iteration für den Turm1 */
                                                for(posTurm1=0; posTurm1<=anzFelder; posTurm1++)
                                                {
                                                    
                                                    anzFiguren_Turm1 = anzFiguren_Laeufer2;
                                                    spielbrett_Turm1 = spielbrett_Laeufer2;
                                                    if(feldFrei(&posTurm1, &spielbrett_Laeufer2))
                                                    {
                                                        if(posTurm1<anzFelder)
                                                        {
                                                            spielbrett_Turm1 += (DarstellungTurm << posTurm1*3);
                                                            anzFiguren_Turm1++;
                                                        }
                                                        
                                                        /* Iteration für den Turm2 */
                                                        for(posTurm2=posTurm1; posTurm2<=anzFelder; posTurm2++)
                                                        {
                                                            anzFiguren_Turm2 = anzFiguren_Turm1;
                                                            spielbrett_Turm2 = spielbrett_Turm1;
                                                            if(feldFrei(&posTurm2, &spielbrett_Turm1))
                                                            {
                                                                if(posTurm2<anzFelder){
                                                                    spielbrett_Turm2 += (DarstellungTurm << posTurm2*3);
                                                                    anzFiguren_Turm2++;
                                                                }
                                                                
                                                                /* Iteration für den Bauer1 */
                                                                for(posBauer1=0; posBauer1<=anzFelder; posBauer1++)
                                                                {
                                                                    anzFiguren_Bauer1 = anzFiguren_Turm2;
                                                                    spielbrett_Bauer1 = spielbrett_Turm2;
                                                                    if(feldFrei(&posBauer1, &spielbrett_Turm2))
                                                                    {
                                                                        if(posBauer1<anzFelder)
                                                                        {
                                                                            spielbrett_Bauer1 += (DarstellungBauer << posBauer1*3);
                                                                            anzFiguren_Bauer1++;
                                                                        }
                                                                    
                                                                        // Spart die innere Schleife bei zu wenigen Figuren, 
                                                                        // es können aber trotzdem Bretter mit einer Figur erstellt

                                                                        /* Iteration für den Bauer2 */
                                                                        for(posBauer2=posBauer1; posBauer2<=anzFelder; posBauer2++)
                                                                        {
                                                                            anzFiguren_Bauer2 = anzFiguren_Bauer1;
                                                                            spielbrett_Bauer2 = spielbrett_Bauer1;
                                                                            if(feldFrei(&posBauer2, &spielbrett_Bauer1))
                                                                            {
                                                                                if(posBauer2<anzFelder)
                                                                                {
                                                                                    spielbrett_Bauer2 += (DarstellungBauer << posBauer2*3);
                                                                                    anzFiguren_Bauer2++;
                                                                                }
                                                                                
                                                                                // Bretter mit einer Figur in Hashtable speichern und nachher löschen besser als if-Abfrage?
                                                                                // Mischung, die if Abfrage kommt früher und spart Schleifendurchgaenge, es enstehen
                                                                                // aber trotzdem Bretter mit nur einer Figur.
                                                                                g_hash_table_insert(bretter->spielbretterHashtables[anzFiguren_Bauer2], (gpointer) spielbrett_Bauer2,(gpointer) 0 );
                                                                                
                                                                                /* Zähler für die Statistik*/
                                                                                zaehler_bretter++;
                                                                                //Debugcode um jedes spielbrett auszugenben. Achtung macht vielllllll lansamer!
                                                                                //printf("Zuletzt hinzugefügtes Spielbrett: %016llo \n", (unsigned long long) spielbrett_Bauer2);
                                                                            }
                                                                        } /* Schleife Bauer2 */
                                                                    }
                                                                } /* Schleife Bauer1 */
                                                            }
                                                        } /* Schleife Turm2 */
                                                    }
                                                } /* Schleife Turm1 */
                                            }
                                        } /* Schleife Läufer2 */
                                    }
                                }/* Schleife Läufer1 */
                            }
                        } /* Schleife Springer2 */
                        
                        /* Debug und Geschwindigkeitsmesseung */
                        
                        printf("\n====================================================================== \n");
                        
                        printf("posDame: %d \t posKoenig: %d \t posSpringer1: %d \n", posDame, posKoenig, posSpringer1);
                        gettimeofday(&comp_time_2, NULL);
                        double time_zwischenstand = (comp_time_2.tv_sec - comp_time_1.tv_sec) + (comp_time_2.tv_usec - comp_time_1.tv_usec) * 1e-6 ;
                        printf("Aktuelle Laufzeit: %f \n",(comp_time_2.tv_sec - start_time.tv_sec) + (comp_time_2.tv_usec - start_time.tv_usec) * 1e-6 );
                        printf("Berechnungszeit für den letzten Springer1:    %f s \n", time_zwischenstand);
                        printf("Errechnete Spielbretter seit letztem Springer1: %ld \n", (zaehler_bretter - zaehler_bretter_zwischenstand));
                        printf("Bretter / Sekunde: %f \n", ((zaehler_bretter - zaehler_bretter_zwischenstand)/time_zwischenstand) );
                        
                        summe_anzahl = 0;
                        for(int tala = 0; tala <= 10; tala++)
                        {
                            printf("Hashtablegröße für Anzahl: %2d = %d \n",tala,g_hash_table_size(bretter->spielbretterHashtables[tala]));
                            summe_anzahl += g_hash_table_size(bretter->spielbretterHashtables[tala]);
                        }
                        
                        printf("Neue Spielbretter in den Hashtabellen: %ld \n", summe_anzahl - summe_anzahl_vergleich);
                        printf("Anteil der doppelt errechneten Bretter in Prozent : %f \n", ((((zaehler_bretter - zaehler_bretter_zwischenstand)-(summe_anzahl - summe_anzahl_vergleich))*100.0)/(zaehler_bretter - zaehler_bretter_zwischenstand)));
                        summe_anzahl_vergleich = summe_anzahl;
                        
                        gettimeofday(&comp_time_1, NULL);
                        zaehler_bretter_zwischenstand = zaehler_bretter;
                        
                        printf("Zuletzt hinzugefügtes Spielbrett: %016llo \n", (unsigned long long) spielbrett_Bauer2);
                    
                        printf("====================================================================== \n \n");
                        
                        /*  End Debug und Geschwindigkeitsmesseung */
                    }
                } /* Schleife Springer1 */
            }
        } /* Schleife König */
	} /* Schleife Dame */
    
    
    /* Setzen der Spielbrett mit einer Figur auf lösbar */
    g_hash_table_foreach(bretter->spielbretterHashtables[1], setzeLoesbar, bretter->spielbretterHashtables[1]);
    
    
    gettimeofday(&comp_time, NULL);
    double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
	printf("Berechnungszeit:    %f s \n", time);
    printf("Errechnete Spielbretter: %ld \n", zaehler_bretter);
    printf("Bretter / Sekunde: %f \n", (zaehler_bretter / time) );
    
    summe_anzahl = 0;
	for(int tala=0; tala <= 10; tala++)
	{
        printf("Hashtablegröße für Anzahl: %2d = %d \n",tala,g_hash_table_size(bretter->spielbretterHashtables[tala]));
        summe_anzahl += g_hash_table_size(bretter->spielbretterHashtables[tala]);
	}
    
    bretter->anzahlBretterGesamt = summe_anzahl;
    
    printf("Summe aller Bretter in den Hashtabellen: %ld\n",summe_anzahl);
    printf("Anteil der doppelt errechneten Bretter in Prozent : %f\n", (((zaehler_bretter-summe_anzahl)*100.0)/zaehler_bretter));
    
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
static void spielbrettBerechne(gpointer spielbrett_ptr, gpointer loesbar_ptr, gpointer bretter_ptr )
{
    
    /* Casten des values aus der Hashtabelle auf den Richtigen Typen */
	long loesbar = (long) loesbar_ptr;
    
    /* Casten des Spielbretts aus der Hashtabelle auf den Richtigen Typen */
    long long spielbrett;
    spielbrett = ((long long) spielbrett_ptr);
    
    /* Casten auf den richtigen Typen */
    spielbretter_t *bretter = (spielbretter_t*) bretter_ptr;
    
    /* Param Stuct für den Aufruf der Spielfigurenberechnung */
    figuren_param_t param;
    /* Kopieren des Spielbretter Arrays */
    memcpy(param.spielbretterHashtables, bretter->spielbretterHashtables, sizeof(GHashTable*)*11);
    /* Kopiere anzahlfiguren von bretter nach param */
    param.anzahlFiguren = bretter->anzahlFiguren;
    /* Pointer auf spielbrett in prama speichern */
    param.spielbrett = &spielbrett;
    
    
    /* Zähler Variablen für die for-Scheifen */
    int x, y;
    
    
    /* Speicher allozieren für die Arraydarstellung des Spielbrettes */
    param.spielbrett_array = spielbretterArrayCreate(SpielbrettBreite, SpielbrettHoehe);
    

  
	/* Berechnung der Arraydarstellung aus Oktaldarstellung
	 * einfacher für die Überprüfung der Spielbrettgrenzen*/
    for(x=0; x < SpielbrettBreite; x++)
    {
        for(y=0; y < SpielbrettHoehe; y++)
        {   
			param.spielbrett_array[x][y] = (spielbrett >> ((x+(y*SpielbrettBreite)) * 3)) % 8;
        }
    }
    
	/* Berechnet, ob die Figuren an der jeweiligen Position schlagen können und daraus
	 * ein lösbares neues Spielbrett entsteht */
     for(x=0; x < SpielbrettBreite && loesbar == 0; x++){
		for(y=0; y < SpielbrettHoehe && loesbar == 0; y++){   
			switch(param.spielbrett_array[x][y]){
				case DarstellungBauer:
					loesbar= berechneBauer(&param, x, y);
					break;
				case DarstellungTurm:
					loesbar = berechneTurm(&param, x, y);
					break;
				case DarstellungLaeufer:
					loesbar = berechneLaeufer(&param, x, y);
					break;
				case DarstellungSpringer:
					loesbar = berechneSpringer(&param, x, y);
					break;
				case DarstellungKoenig:
					loesbar = berechneKoenig(&param, x, y);
					break;
				case DarstellungDame:
					loesbar = berechneDame(&param, x, y);
					break;
			}
		}
	}
    
    /* In der Hashtabelle speicher, wenn ein Spielbrett loesbar ist */
    if(loesbar==1)
    {
        g_hash_table_replace(bretter->spielbretterHashtables[bretter->anzahlFiguren], (gpointer) spielbrett, (gpointer) loesbar);
        bretter->loesbareBretterGesamt ++;
    }
    
	/*Spielbrett Array wird wieder freigegeben*/
	spielbretterArrayDestruct(param.spielbrett_array, SpielbrettBreite);
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne(spielbretter_t *bretter)
{
    /* time measurement variables */
    struct timeval start_time;       /* time when program started                      */
    struct timeval comp_time;        /* time when calculation completed                */
    struct timeval comp_time_1;      /* zeit vom letzten zwischenstand */
    struct timeval comp_time_2;      /* vergleichszeit beim aktuellen zwischenstand */
    
    gettimeofday(&start_time, NULL); /* Starte Zeitmessung */
    gettimeofday(&comp_time_1, NULL); 
    
    
    printf("Beginn spielbretter_berechne\n");
    
    int anzahlFiguren;
    bretter->loesbareBretterGesamt = 0;
    long loesbareBretterTmp =0;
    /* Reihenfolge der zu berechnenden Spielbretter nach Anzahl der Figuren (aufsteigend)*/
    for(anzahlFiguren = 2; anzahlFiguren <= 10; anzahlFiguren++)
    {
        printf("\n====================================================================== \n");
        printf("Berechne Spielbretter mit %2d Figuren \n", anzahlFiguren);
        
		bretter->anzahlFiguren = anzahlFiguren;
        loesbareBretterTmp = bretter->loesbareBretterGesamt;
        g_hash_table_foreach(bretter->spielbretterHashtables[anzahlFiguren], spielbrettBerechne, bretter);
        
        gettimeofday(&comp_time_2, NULL);
        double time_zwischenstand = (comp_time_2.tv_sec - comp_time_1.tv_sec) + (comp_time_2.tv_usec - comp_time_1.tv_usec) * 1e-6 ;
        printf("Aktuelle Laufzeit: %f \n",(comp_time_2.tv_sec - start_time.tv_sec) + (comp_time_2.tv_usec - start_time.tv_usec) * 1e-6 );
        printf("Berechnungszeit:    %f s \n", time_zwischenstand);
        printf("Lösbare Bretter: %ld von %d\n", (bretter->loesbareBretterGesamt-loesbareBretterTmp), g_hash_table_size(bretter->spielbretterHashtables[anzahlFiguren]));
        gettimeofday(&comp_time_1, NULL);
        
         printf("====================================================================== \n \n");
    }
    
    gettimeofday(&comp_time, NULL); /* Stoppe Zeitmessung */
    double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
	printf("Berechnungszeit:    %f s \n", time);

}
