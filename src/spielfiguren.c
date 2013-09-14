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
int berechneBauer(figuren_param_t *param, int x, int y)
{
	//printf("Beginn berechneBauer x = %d y = %d \n",x,y);

	
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int anzahlFiguren;
	anzahlFiguren = param->anzahlFiguren;
	
	
	/*
	 * Bauer schlägt nach links oben
	 */
	if((x-1)>0 && (y-1)>0 && (param->spielbrett_array[x-1][y-1] != 0))
    {
		
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	

	/*
	 * Bauer schlägt nach links unten
	 */	
	if((x-1)>0 && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x-1][y+1] != 0))
    {
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	/*
	 * Bauer schlägt nach rechts oben
	 */
	if((x+1)<SpielbrettBreite && (y-1)>0 && (param->spielbrett_array[x+1][y-1] != 0))
    {
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	/*
	 * Bauer schlägt nach rechts unten
	 */
	if((x+1)<SpielbrettBreite && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x+1][y+1] != 0))
    {
		neue_pos = (x+1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {

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
int berechneTurm(figuren_param_t *param, int x, int y)
{
	//printf("Beginn berechneTurm x = %d y = %d\n",x,y);
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int n;
	int anzahlFiguren; 
	anzahlFiguren = param->anzahlFiguren;

	

	/*Turm schlägt nach rechts */
	for(n = 1; (x+n) < SpielbrettBreite ; n++)
	{
		if(param->spielbrett_array[x+n][y] != 0)
		{	
            
			neue_pos = (x+n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Turm schlägt nach links*/
	for(n = 1; (x-n) > 0 ; n++)
	{	
        if (param->spielbrett_array[x-n][y] != 0)
		{
			neue_pos = (x-n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Turm schlägt nach unten */
	for(n = 1; (y+n) < SpielbrettHoehe ; n++)
	{
		if(param->spielbrett_array[x][y+n] != 0)
		{
			neue_pos = (x)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Turm schlägt nach oben*/
	for(n = 1; (y-n) > 0; n++)
	{
		if(param->spielbrett_array[x][y-n] != 0)
		{
			neue_pos = (x)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	//printf("Ende berechneTurm x = %d y = %d\n",x,y);
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
int berechneLaeufer(figuren_param_t *param, int x, int y)
{
	//printf("Beginn berechneLäufer x = %d y = %d\n",x,y);
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int n;
	int anzahlFiguren;
	anzahlFiguren = param->anzahlFiguren;
	
	
	/*Läufer schlägt nach links oben*/
	for(n = 1; ((x-n) > 0) && ((y-n) > 0); n++)
	{	
        if(param->spielbrett_array[x-n][y-n] != 0)
        {
			neue_pos = (x-n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Läufer schlägt nach links unten*/
	for(n = 1; ((x-n) > 0) && ((y+n) < SpielbrettHoehe) ; n++)
	{	
        if(param->spielbrett_array[x-n][y+n] != 0)
        {
			neue_pos = (x-n)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Läufer schlägt nach rechts oben*/
	for(n = 1; ((x+n) < SpielbrettBreite) && ((y-n) > 0); n++)
	{	
        if(param->spielbrett_array[x+n][y-n] != 0)
        {
			neue_pos = (x+n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	/*Läufer schlägt nach rechts unten*/
	for(n = 1; ((x+n) < SpielbrettBreite) && ((y+n) < SpielbrettHoehe) ; n++)
	{	
        if(param->spielbrett_array[x+n][y+n] != 0)
        {
			neue_pos = (x+n)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
            {
                return 1;
            }
		}
	}
	
	//printf("Ende berechneLäufer x = %d y = %d\n",x,y);
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
int berechneSpringer(figuren_param_t *param, int x, int y)
{
	//printf("Beginn berechneSpringer x = %d y = %d\n",x,y);
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int anzahlFiguren;
	anzahlFiguren = param->anzahlFiguren;
	
    
    	/*
	 * Springer schlägt nach erst oben dann rechts
	 */
	if((x+1)<SpielbrettBreite && (y-2)>0 && (param->spielbrett_array[x+1][y-2] != 0))
    {
		
		neue_pos = (x+1)+((y-2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
    
	/*
	 * Springer schlägt nach erst oben  dann links
	 */
	if((x-1)>0 && (y-2)>0 && (param->spielbrett_array[x-1][y-2] != 0))
    {
		
		neue_pos = (x-1)+((y-2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
        if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
            return 1;
        }
	}
	
	
	/*
	 * Springer schlägt nach erst links dann oben
	 */	
	if((x-2)>0 && (y-1)>0 && (param->spielbrett_array[x-2][y-1] != 0))
    {
		
		neue_pos = (x-2)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach links unten
	 */	
	if((x-2)>0 && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x-2][y+1] != 0))
    {
		
		neue_pos = (x-2)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach unten links
	 */
	if((x-1)>0 && (y+2)<SpielbrettHoehe && (param->spielbrett_array[x-1][y+2] != 0))
    {
	
		neue_pos = (x-1)+((y+2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	/*
	 * Springer schlägt nach unten rechts
	 */
	if((x+1)<SpielbrettBreite && (y+2)<SpielbrettHoehe && (param->spielbrett_array[x+1][y+2] != 0))
    {
	
		neue_pos = (x+1)+((y+2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach rechts unten
	 */
	if((x+2)<SpielbrettBreite && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x+2][y+1] != 0))
    {
		
		neue_pos = (x+2)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach rechts oben
	 */
	if((x+2)<SpielbrettBreite && (y-1)>0 && (param->spielbrett_array[x+2][y-1] != 0))
    {
		
		neue_pos = (x+2)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
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
int berechneKoenig(figuren_param_t *param, int x, int y)
{

	//printf("Beginn berechneKönig x = %d y = %d\n",x,y);
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	long long neues_spielbrett;
	int anzahlFiguren;
	anzahlFiguren = param->anzahlFiguren;



	// Der König kann die 4 Züge des Bauerns auch ausführen
	if(berechneBauer(param, x, y) == 1)
    {
		return 1;
	}

	
	/*
	 * König schlägt nach oben
	 */
	if((y-1)>0 && (param->spielbrett_array[x][y-1] != 0))
    {
		
		neue_pos = (x)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * König schlägt nach links
	 */	
	if((x-1)>0 && (param->spielbrett_array[x-1][y] != 0))
    {
		
		neue_pos = (x-1)+((y)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * König schlägt nach unten
	 */
	if((y+1)<SpielbrettHoehe && (param->spielbrett_array[x][y+1] != 0))
    {
	
		neue_pos = (x)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	
	
	/*
	 * König schlägt nach rechts 
	 */
	if((x+1)<SpielbrettBreite && (param->spielbrett_array[x+1][y] != 0))
    {
		
		neue_pos = (x+1)+((y)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( ((int)g_hash_table_lookup (param->spielbretterHashtables[anzahlFiguren-1], neues_spielbrett)) == 1 )
        {
			return 1;
		}
	}
	

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
int berechneDame(figuren_param_t *param, int x, int y)
{
	//printf("Beginn berechneDame x = %d y = %d\n",x,y);
	
	// Die Dame kann die gleichen Züge wie ein Turm ausführen
	if(berechneTurm(param, x, y) == 1)
    {
		return 1;
	}
	
	// Die Dame kann die gleichen Züge wie ein Läufer ausführen
	if(berechneLaeufer(param, x, y) == 1)
    {
		return 1;
	}
	
	return 0;
}
