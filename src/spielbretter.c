#include "spielbretter.h"
#include "spielfiguren.h"
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include <omp.h>
#include <mpi.h>


/**
 * 
 * Spielbrett:
 * Links-Oben 0:0 nach x:y
 * 
 * 0, 1, 2, 3
 * 4, 5, 6, 7
 * 8, 9,10,11
 * 12,13,14,15
 * 
 * 
 * Repräsentation des Spielbrettbelegung in einem long long (64bit-integer)
 * Pro Figur werden drei Bit benötigt.
 * Beginnend mit dem Spielfeld "15" werden die Belegungen der einzelnen Felder von vorn nach hinten im 
 * long long codiert. 
 * 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 * Die Dreierbitblöcke werden von links nach rechts ausgewertet.
 * z.B.: 000....000010 bedeutet ein Turm auf Feld 0 (also links oben).
 * 
 * 
 * Repräsentation der Spielfiguren auf dem Brett:
 * 	    Dez			Binär	
 * 	    0 Frei		000
 * 	    1 Bauer		001
 * 	    2 Turm		010
 * 	    3 Läufer	011
 * 	    4 Springer	100
 * 	    5 König		101
 * 	    6 Dame		110
*/



/**
 * Hilfsfunktion, die bestimmt, ob auf auf einem übergebenen Brett an einer übergeben Posistion eine Figur steht.
 *
 * @param position *int 
 * @param spielbrett *long long
 * @return bool
 */
static inline bool feldFrei(int* position, sp_okt_t* spielbrett)
{
	return (((*spielbrett >> (*position * 3)) % 8) == DarstellungLeer);
}


/**
 * Erzeugt die Hashtabellen zur Speicherung der Spielbretter.
 */
static inline void erzeugeHashtables(spielbretter_t *bretter)
{
	int figurenAnzahl;
	for(figurenAnzahl=0; figurenAnzahl<=10; figurenAnzahl++){
		bretter->spielbretterHashtables[figurenAnzahl] = g_hash_table_new(g_direct_hash, g_direct_equal);
	}
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
 * Erzeugt alle Spielbretter mit einer Figur und intialisiert diese mit
 * dem Value 1 (lösbar).
 * 
 */
static void spielbretterErzeugung1Figur(spielbretter_t *bretter)
{
    sp_okt_t spielbrett;
    for(int pos = 0; pos < SpielfelderAnzahl; pos++)
    {
        for(int figur = 1; figur <7; figur++)
        {
            spielbrett = (figur << pos*3);
            g_hash_table_insert(bretter->spielbretterHashtables[1], (gpointer) spielbrett ,(gpointer) 1 );
            /* Zähler für Statistik */
            (bretter->anzahlBretter[1])++;
            (bretter->loesbareBretter[1])++;
            (bretter->anzahlBretterGesamt)++;
        }
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
static void spielbrettBerechne(sp_okt_t spielbrett, spielbretter_t *bretter, int anzahlFiguren )
{
    
    /* Zwischenspeicherung ob das Spielbrett bereits gelöst ist */
	long loesbar = 0;
    
    
    /* Param Stuct für den Aufruf der Spielfigurenberechnung */
    figuren_param_t param;
    /* Kopieren des Spielbretter Arrays */
    memcpy(param.spielbretterHashtables, bretter->spielbretterHashtables, sizeof(GHashTable*)*11);
    /* Kopiere anzahlfiguren von bretter nach param */
    param.anzahlFiguren = anzahlFiguren;
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
     
     /* Verlust des Abbruchkriterium durch Parallelisierung */
     
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
    
    //TODO brett umdrehen
    
    
    /* In der Hashtabelle speicher, wenn ein Spielbrett loesbar ist */
    if(loesbar==1)
    {
        //TODO umgedrehtes brett in der hastabelle nachgucken
        
        // Kritischerbereich für omp
        #pragma omp critical (spielbrett_berechne_g_hash_add)
        {
            g_hash_table_add(bretter->spielbretterHashtables[anzahlFiguren], (gpointer) spielbrett );
            bretter->loesbareBretter[anzahlFiguren]++;
            bretter->loesbareBretterGesamt ++;
        }
    }
    
	/*Spielbrett Array wird wieder freigegeben*/
	spielbretterArrayDestruct(param.spielbrett_array, SpielbrettBreite);
}


/**
 * Erzeugt alle möglichen Spielbretter mit zwei bis zu 10 Spielfiguren
 * für eine variable Spielbrettgröße.
 * Hierbei wird figurenweise vorgegangen. Die Figuren werden auf die 
 * Felder gesetzt. Dabei kommt es zur Mehrfacherzeugung von gleichen
 * Brettern, wenn es mehr als 10 Felder auf dem Spielbrett gibt. 
 */
void spielbretter_berechne(spielbretter_t *bretter)
{
    
    /*Zähler für die anzahl der generierten Spielbretter*/
    long zaehler_bretter_gesamt = 0;
    long zaehler_bretter_figuren; /* Zaehlt wie viel spielbretter für eine bestimmte figuren anzahl erstellt werden */
    

    /* time measurement variables */
    struct timeval start_time;       /* time when program started                      */
    struct timeval comp_time;        /* time when calculation completed                */
    struct timeval start_time_figur;      /* start zeit figuren durchlauf */
    struct timeval comp_time_figur;      /* endzeit vom figurenduchlauf */
    
    //if(bretter->prozessNummer == 0)
    {
        gettimeofday(&start_time, NULL);
        gettimeofday(&start_time_figur, NULL); 
    }
	

	/* Spielbrettvariablen, für die verschiedenen Ebenen der for-Schleifen, 
	 * da jede Schleife eigene lokale Variablen braucht, um Überschreiben zu verhindern
	 * Alternative: Zurückrechnen, am Ende der jeweiligen Schleife - aufwendiger */
	sp_okt_t spielbrett_Leer,
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
		




	/* Anzahl der Felder, über die iteriert werden muss */
	int anzFelder = SpielbrettBreite * SpielbrettHoehe;
	spielbrett_Leer = 0;
	anzFiguren_Start = 0;
	spielbrett_Bauer2 = 0;
	
    
    /* erzeuge Hashtabellen */
	erzeugeHashtables(bretter);
    
    /* Spielbretter mit einer figur erzeugen */
	spielbretterErzeugung1Figur(bretter);
        
    
	for(int maxFiguren=2; maxFiguren <= 10; maxFiguren++)
    {
        zaehler_bretter_figuren = 0;
    
        /* Iteration für die Dame über alle Felder und ein zusätzlicher Durchlauf für den Fall: keine Dame
         * für alle anderen Figuren analog!*/
         
         
         //TODO MPI aufteilung
         
        for(int posDame=0; posDame<=anzFelder; posDame++)
        {	
            /* MPI zuweisung der schleifen zu den Prozessen. */
            if(bretter->prozessNummer == ((bretter->anzahlProzesse/anzFelder) * posDame))
            {
                //printf(" Prozess %d berechnet posDame %d\n",bretter->prozessNummer, posDame );
                anzFiguren_Dame = anzFiguren_Start;
                spielbrett_Dame = spielbrett_Leer;
                
                if(posDame<anzFelder)
                {
                    /* posDame * 3, da die Figurenrepräsentation Oktal erfolgt und 3 Binärstellen eine Oktalstelle sind*/
                    spielbrett_Dame +=  (DarstellungDame << posDame*3);
                    anzFiguren_Dame ++; 
                }
                
                /* Iteration für den König */
                #pragma omp parallel for \
                    private(anzFiguren_Koenig, anzFiguren_Springer1, anzFiguren_Springer2, anzFiguren_Laeufer1, anzFiguren_Laeufer2, anzFiguren_Turm1, anzFiguren_Turm2, anzFiguren_Bauer1, anzFiguren_Bauer2, spielbrett_Koenig, spielbrett_Springer1, spielbrett_Springer2, spielbrett_Laeufer1, spielbrett_Laeufer2, spielbrett_Turm1, spielbrett_Turm2, spielbrett_Bauer1, spielbrett_Bauer2) \
                    schedule(dynamic)\
                    reduction (+: zaehler_bretter_gesamt, zaehler_bretter_figuren)
                    
                for(int posKoenig=0; posKoenig<=anzFelder; posKoenig++)
                {	
                    anzFiguren_Koenig = anzFiguren_Dame;
                    spielbrett_Koenig = spielbrett_Dame;
                    
                    if(!(anzFiguren_Koenig < maxFiguren))
                    {
                        posKoenig = anzFelder;
                    }
                    
                    
                    if(feldFrei(&posKoenig, &spielbrett_Dame))
                    {
                        if(posKoenig<anzFelder)
                        {
                            spielbrett_Koenig += (DarstellungKoenig << posKoenig*3);
                            anzFiguren_Koenig ++; 
                        }
                        
                        
                        /* Iteration für den Springer */
                        for(int posSpringer1=0; posSpringer1<=anzFelder; posSpringer1++)
                        {
                            anzFiguren_Springer1 = anzFiguren_Koenig;
                            spielbrett_Springer1 = spielbrett_Koenig;
                            
                            if(!(anzFiguren_Springer1 < maxFiguren))
                            {
                                posSpringer1 = anzFelder;
                            }
                            
                            
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
                                for(int posSpringer2=posSpringer1; posSpringer2<=anzFelder; posSpringer2++)
                                {
                                    anzFiguren_Springer2 = anzFiguren_Springer1;
                                    spielbrett_Springer2 = spielbrett_Springer1;
                                    
                                    if(!(anzFiguren_Springer2 < maxFiguren))
                                    {
                                        posSpringer2 = anzFelder;
                                    }
                                    
                                    if(feldFrei(&posSpringer2, &spielbrett_Springer1))
                                    {
                                        if(posSpringer2<anzFelder)
                                        {
                                            spielbrett_Springer2 += (DarstellungSpringer << posSpringer2*3);
                                            anzFiguren_Springer2 ++;
                                        }
                                        
                                        /* Iteration für den Läufer1 */
                                        for(int posLaeufer1=0; posLaeufer1<=anzFelder; posLaeufer1++)
                                        {
                                            anzFiguren_Laeufer1 = anzFiguren_Springer2;
                                            spielbrett_Laeufer1 = spielbrett_Springer2;
                                            
                                            if(!(anzFiguren_Laeufer1 < maxFiguren))
                                            {
                                                posLaeufer1 = anzFelder;
                                            }
                                            
                                            
                                            if(feldFrei(&posLaeufer1, &spielbrett_Springer2))
                                            {
                                                if(posLaeufer1<anzFelder)
                                                {
                                                    spielbrett_Laeufer1 += (DarstellungLaeufer << posLaeufer1*3);
                                                    anzFiguren_Laeufer1++;
                                                }

                                                /* Iteration für den Läufer2 */
                                                for(int posLaeufer2=posLaeufer1; posLaeufer2<=anzFelder; posLaeufer2++)
                                                {
                                                    anzFiguren_Laeufer2 = anzFiguren_Laeufer1;
                                                    spielbrett_Laeufer2 = spielbrett_Laeufer1;
                                                    
                                                    if(!(anzFiguren_Laeufer2 < maxFiguren))
                                                    {
                                                        posLaeufer2 = anzFelder;
                                                    }
                                                    
                                                    if(feldFrei(&posLaeufer2, &spielbrett_Laeufer1))
                                                    {
                                                        if(posLaeufer2<anzFelder)
                                                        {    
                                                            spielbrett_Laeufer2 += (DarstellungLaeufer << posLaeufer2*3);
                                                            anzFiguren_Laeufer2++;
                                                        }

                                                        /* Iteration für den Turm1 */
                                                        for(int posTurm1=0; posTurm1<=anzFelder; posTurm1++)
                                                        {
                                                            anzFiguren_Turm1 = anzFiguren_Laeufer2;
                                                            spielbrett_Turm1 = spielbrett_Laeufer2;
                                                            
                                                            if(!(anzFiguren_Turm1 < maxFiguren))
                                                            {
                                                                posTurm1 = anzFelder;
                                                            }
                                                            
                                                            if(feldFrei(&posTurm1, &spielbrett_Laeufer2))
                                                            {
                                                                if(posTurm1<anzFelder)
                                                                {
                                                                    spielbrett_Turm1 += (DarstellungTurm << posTurm1*3);
                                                                    anzFiguren_Turm1++;
                                                                }
                                                                
                                                                /* Iteration für den Turm2 */
                                                                for(int posTurm2=posTurm1; posTurm2<=anzFelder; posTurm2++)
                                                                {
                                                                    anzFiguren_Turm2 = anzFiguren_Turm1;
                                                                    spielbrett_Turm2 = spielbrett_Turm1;
                                                                    
                                                                    if(!(anzFiguren_Turm2 < maxFiguren))
                                                                    {
                                                                        posTurm2 = anzFelder;
                                                                    }
                                                    
                                                                    if(feldFrei(&posTurm2, &spielbrett_Turm1))
                                                                    {
                                                                        if(posTurm2<anzFelder){
                                                                            spielbrett_Turm2 += (DarstellungTurm << posTurm2*3);
                                                                            anzFiguren_Turm2++;
                                                                        }
                                                                        
                                                                        /* Iteration für den Bauer1 */
                                                                        for(int posBauer1=0; posBauer1<=anzFelder; posBauer1++)
                                                                        {
                                                                            anzFiguren_Bauer1 = anzFiguren_Turm2;
                                                                            spielbrett_Bauer1 = spielbrett_Turm2;
                                                                            
                                                                            if(!(anzFiguren_Bauer1 < maxFiguren))
                                                                            {
                                                                                posBauer1 = anzFelder;
                                                                            }
                                                    
                                                                            if(feldFrei(&posBauer1, &spielbrett_Turm2))
                                                                            {
                                                                                if(posBauer1<anzFelder)
                                                                                {
                                                                                    spielbrett_Bauer1 += (DarstellungBauer << posBauer1*3);
                                                                                    anzFiguren_Bauer1++;
                                                                                }
                                                                                
                                                                                /* Iteration für den Bauer2 */
                                                                                for(int posBauer2=posBauer1; posBauer2<=anzFelder; posBauer2++)
                                                                                {
                                                                                    anzFiguren_Bauer2 = anzFiguren_Bauer1;
                                                                                    spielbrett_Bauer2 = spielbrett_Bauer1;
                                                                                    
                                                                                    if(!(anzFiguren_Bauer2 < maxFiguren))
                                                                                    {
                                                                                        posBauer2 = anzFelder;
                                                                                    }
                                                    
                                                                                    if(feldFrei(&posBauer2, &spielbrett_Bauer1))
                                                                                    {
                                                                                        if(posBauer2<anzFelder)
                                                                                        {
                                                                                            spielbrett_Bauer2 += (DarstellungBauer << posBauer2*3);
                                                                                            anzFiguren_Bauer2++;
                                                                                        }
                                                                                        
                                                                                        
                                                                                        if(anzFiguren_Bauer2 == maxFiguren)
                                                                                        {
                                                                                            // Bretter mit einer Figur in Hashtable speichern und nachher löschen besser als if-Abfrage?
                                                                                            // Mischung, die if Abfrage kommt früher und spart Schleifendurchgaenge, es enstehen
                                                                                            // aber trotzdem Bretter mit nur einer Figur
                                                                                            // g_hash_table_insert(bretter->spielbretterHashtables[anzFiguren_Bauer2], (gpointer) spielbrett_Bauer2,(gpointer) 0 );
                                                                                            spielbrettBerechne(spielbrett_Bauer2, bretter, maxFiguren);
                                                                                            
                                                                                            
                                                                                            
                                                                                            /* Zähler für die Statistik*/
                                                                                            zaehler_bretter_gesamt++;
                                                                                            zaehler_bretter_figuren++;
                                                            
                                                                                        }
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
                            }
                        } /* Schleife Springer1 */
                    }
                } /* Schleife König */
            }
        } /* Schleife Dame */
     
        bretter->anzahlBretter[maxFiguren] = zaehler_bretter_figuren;
    
        //TODO MPI kommunikation
        //TODO löschen der nicht mehr benötigten hashtabellen
        /* Statistikwert speichern */
        
        if(bretter->prozessNummer == 0)
        {
            printf("========== %d Figuren===============",maxFiguren );
        }
        //if(bretter->prozessNummer == 0)
        {
            gettimeofday(&comp_time_figur, NULL);
            bretter->berechnungsZeit[maxFiguren] = (comp_time_figur.tv_sec - start_time_figur.tv_sec) + (comp_time_figur.tv_usec - start_time_figur.tv_usec) * 1e-6;
            gettimeofday(&start_time_figur, NULL);
            printf("Pozess %d fertig in %f sec. \n",bretter->prozessNummer bretter->berechnungsZeit[maxFiguren]);
        }
        

        
        MPI_Barrier(MPI_COMM_WORLD); 
        
        //MPI_Allgather (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_COMM_WORLD);
        
        /* nicht mehr benötigte Hashtabellen freigeben */
        g_hash_table_destroy( bretter->spielbretterHashtables[maxFiguren-1]);
        
        if(bretter->prozessNummer == 0)
        {
            printf("====================================");
        }
       
        
    }
    
    /* Statistikwert speichern */
    if(bretter->prozessNummer == 0)
    {
        bretter->anzahlBretterGesamt = zaehler_bretter_gesamt;
        gettimeofday(&comp_time, NULL);
        bretter->berechnungsZeitGesamt = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
    }
}


/**
 * Berechnet alle Spielbretter aus den Hashtabellen der übergeben struct.
 *
 */
void spielbretter_berechne_alt(spielbretter_t *bretter)
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
        
        
        
        //TODO openMP paralelisierung omp task
        /*
        GHashTableIter iter;
        gpointer key, value;

        g_hash_table_iter_init (&iter, hash_table);
        while (g_hash_table_iter_next (&iter, &key, &value))
        {
            // do something with key and value
        }
         
        #pragma omp parallel
        {
        #pragma omp single private(p)
        {
        p = listhead ;
        Spawn call to process(p)
        while (p) {
        #pragma omp task
        process (p)
        p=next (p) ;
        }
        }
        }
        */
        
		//bretter->anzahlFiguren = anzahlFiguren;
        loesbareBretterTmp = bretter->loesbareBretterGesamt;
        //g_hash_table_foreach(bretter->spielbretterHashtables[anzahlFiguren], spielbrettBerechne,(gpointer) bretter);
        
        
        
        gettimeofday(&comp_time_2, NULL);
        double time_zwischenstand = (comp_time_2.tv_sec - comp_time_1.tv_sec) + (comp_time_2.tv_usec - comp_time_1.tv_usec) * 1e-6 ;
        printf("Aktuelle Laufzeit: %f \n",(comp_time_2.tv_sec - start_time.tv_sec) + (comp_time_2.tv_usec - start_time.tv_usec) * 1e-6 );
        printf("Berechnungszeit:    %f s \n", time_zwischenstand);
        printf("Lösbare Bretter: %ld von %d\n", (bretter->loesbareBretterGesamt-loesbareBretterTmp), g_hash_table_size(bretter->spielbretterHashtables[anzahlFiguren]));
        printf("Löabare Bretter in Prozent: %f\n", ((bretter->loesbareBretterGesamt-loesbareBretterTmp)*100.0 /g_hash_table_size(bretter->spielbretterHashtables[anzahlFiguren])));
        gettimeofday(&comp_time_1, NULL);
        printf("====================================================================== \n \n");
    }
    
    gettimeofday(&comp_time, NULL); /* Stoppe Zeitmessung */
    double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
	printf("Berechnungszeit:    %f s \n", time);

}
