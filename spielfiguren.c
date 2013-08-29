#import "spielfiguren.h"
/**
Spielbrett:

Links-Oben 0:0 nach x:y

  0, 1, 2, 3
  4, 5, 6, 7
  8, 9,10,11
 12,13,14,15
 */
 
 long long einser_Bitmaske >> 64;
 
 /**
  * Hilfsmethode zum Setzen einer Figur von pos auf neue_pos 
  */
 void schlageFigur(long long* spielbrett, long long* neues_spielbrett, int DarstellungFigur, int* pos, int* neue_pos){
	/* Spielfiguren, geschlagene und schlagende, von Spielbrett löschen */
	/* Von der Bitmaske wird "(7 << pos*3)" abgezogen, um an dieser Stelle 0 zu erzeugen */
	neues_spielbrett = *spielbrett & ( einser_Bitmaske - (7 << pos*3) - (7 << neue_pos*3));
	/* nach Schlagen Spielfigur neu  setzen */
	neues_spielbrett += (DarstellungBauer << neue_pos*3);
 }
 

/**
 * Prüft, ob ein Zug mit dieser Figur möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param pos Die Position der zu ermittelnden Figur.
 * 
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 *
 */
//TODO array übergabe korrekt ?
int berechneBauer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)

	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	
	
	/*
	 * Bauer schlägt nach links oben
	 */
	if((x-1)>0 && (y-1)>0 && (spielbrett[x-1][y-1] != 0)){
		
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, &pos, &neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach links unten
	 */	
	if((x-1)>0 && (y+1)>0 && (spielbrett[x-1][y+1] != 0)){
		
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, &pos, &neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach rechts oben
	 */
	if((x+1)>0 && (y-1)>0 && (spielbrett[x+1][y-1] != 0)){
	
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, &pos, &neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	/*
	 * Bauer schlägt nach rechts unten
	 */
	if((x+1)>0 && (y+1)>0 && (spielbrett[x+1][y+1] != 0)){
		
		neue_pos = (x+1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(spielbrett, &neues_spielbrett, DarstellungBauer, &pos, &neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if((int) *(g_hash_table_lookup (_spielbretterHashtables[*anzahlFiguren-1], &neues_spielbrett)) == 1){
			return 1;
		}
	}
	
	
	return 0;    
}

/**
 * Prüft welche möglichen Züge ein Turm auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneTurm(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Turm 
	
	return 0;
}

/**
 * Prüft welche möglichen Züge ein Läufer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneLaeufer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Läufer0
	return 0;
}

/**
 * Prüft welche möglichen Züge ein Springer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneSpringer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Springer
	return 0;
}

/**
 * Prüft welche möglichen Züge ein König auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneKoenig(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
	//TODO König
	return 0;
}

/**
 * Prüft welche möglichen Züge eine Dame auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneDame(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren)
{
	//TODO Dame
	return 0;
}

