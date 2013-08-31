#include "spielfiguren.h"


/**
Spielbrett:

Links-Oben 0:0 nach x:y

  0, 1, 2, 3
  4, 5, 6, 7
  8, 9,10,11
 12,13,14,15
 */
 
 long long einser_Bitmaske = 0xffffffffffffffffLL;
 
 
 /**
  * Hilfsmethode zum Setzen einer Figur von pos auf neue_pos 
  */
 void schlageFigur(long long* spielbrett, long long* neues_spielbrett, int DarstellungFigur, int pos, int neue_pos){
	/* Spielfiguren, geschlagene und schlagende, von Spielbrett löschen */
	/* Von der Bitmaske wird "(7 << pos*3)" abgezogen, um an dieser Stelle 0 zu erzeugen */
	*neues_spielbrett = *spielbrett & ( einser_Bitmaske - (7 << pos*3) - (7 << neue_pos*3));
	/* nach Schlagen Spielfigur neu  setzen */
	*neues_spielbrett += (DarstellungFigur << neue_pos*3);
 }
 

/**
 * Prüft, ob ein Zug mit diesem Bauer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 *
 */
//TODO array übergabe korrekt ?
int berechneBauer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren){

	
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	
	
	/*
	 * Bauer schlägt nach links oben
	 */
	 //TODO: Stimmt die Ifabfrage? Müsste nicht sowas 0<(x-1)<SpielbrettBreite && 0<(y-1)<SpielbrettHoehe richtig sein?
	 // für alle anderen Überprüfungen natürlich ebenso
	if((x-1)>0 && (y-1)>0 && (spielbrett_array[x-1][y-1] != 0)){
		
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach links unten
	 */	
	if((x-1)>0 && (y+1)>0 && (spielbrett_array[x-1][y+1] != 0)){
		
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach rechts oben
	 */
	if((x+1)>0 && (y-1)>0 && (spielbrett_array[x+1][y-1] != 0)){
	
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach rechts unten
	 */
	if((x+1)>0 && (y+1)>0 && (spielbrett_array[x+1][y+1] != 0)){
		
		neue_pos = (x+1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	return 0;    
}

/**
 * Prüft, ob ein Zug mit diesem Turm möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneTurm(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int n;

	/*Turm schlägt nach rechts */
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	// for-schleife mit mehreren if-abfragen möglich? 	for(n = 1; 0<(x-n)<4 && (spielbrett_array[x-n][y] != 0); n++)
	for(n = 1; 0<(x+n)<4 ; n++)
	{
		if(spielbrett_array[x+n][y] != 0)
		{	
			neue_pos = (x+1)+((y)*SpielbrettBreite);
			schlageFigur(spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
			if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1)
			{
				return 1;
			}
		}
	}
	
	/*Turm schlägt nach links*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(x-n)<4 && (spielbrett_array[x-n][y] != 0); n++)
	{
		neue_pos = (x+1)+((y)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	/*Turm schlägt nach unten */
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(y+n)<4 && (spielbrett_array[x][y+n] != 0); n++)
	{
		neue_pos = (x+1)+((y)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	/*Turm schlägt nach oben*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(y-n)<4 && (spielbrett_array[x][y-n] != 0); n++)
	{
		neue_pos = (x+1)+((y)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	return 0;
}

/**
 * Prüft, ob ein Zug mit diesem Läufer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneLaeufer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int n;
	
	/*Läufer schlägt nach links oben*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(x-n)<4 && 0<(y-n)<4 && (spielbrett_array[x-n][y-n] != 0); n++)
	{
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	/*Läufer schlägt nach links unten*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(x-n)<4 && 0<(y+n)<4 && (spielbrett_array[x-n][y+n] != 0); n++)
	{
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	/*Läufer schlägt nach rechts oben*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(x+n)<4 && 0<(y-n)<4 && (spielbrett_array[x+n][y-n] != 0); n++)
	{
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	/*Läufer schlägt nach rechts unten*/
	//TODO: 4 durch SpielbrettBreite / SpielbrettHoehe ersetzen
	for(n = 1; 0<(x+n)<4 && 0<(+-n)<4 && (spielbrett_array[x+n][y+n] != 0); n++)
	{
		neue_pos = (x+1)+((y+1)*SpielbrettBreite);
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	return 0;
}

/**
 * Prüft, ob ein Zug mit diesem Springer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneSpringer(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Springer
	return 0;
}

/**
 * Prüft, ob ein Zug mit dem König an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneKoenig(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO König
	return 0;
}

/**
 * Prüft, ob ein Zug mit der Dame an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param spielbrett_array Arraydarstellung des aktuellen Spielbrettes
 * @param spielbrett Oktaldarstellung des aktuellen Spielbrettes
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @param anzahlFiguren Anzahl der noch vorhandenen Figuren auf dem Brett
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneDame(char **spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Dame
	return 0;
}

