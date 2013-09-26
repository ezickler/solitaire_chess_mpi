#include "spielfiguren.h"

/**
 * Diese Datei stellt Funktionen bereit, um zu entscheiden, ob eine 
 * bestimmte Figur an einer bestimmten Stelle auf einem gegebenen Feld
 * irgendeine andere Figur schlagen kann. Ist eine Zug möglich, so wird 
 * dies zurück gegeben, ohne weitere Möglichkeiten zu berechnen.
 * 
 * 
 * Spielbrett:
 * Links-Oben 0:0 nach x:y
 * 
 * 0, 1, 2, 3
 * 4, 5, 6, 7
 * 8, 9,10,11
 * 12,13,14,15
 */
 
sp_okt_t einser_Bitmaske = 0xffffffffffffffffLL;

//TODO  zähler wie häufig bei andere prozessen nachgeguckt werden müsste
 
 
 /**
  * Hilfsmethode zum Setzen einer Figur von pos auf neue_pos 
  */
static inline void schlageFigur(sp_okt_t* spielbrett, sp_okt_t* neues_spielbrett, int DarstellungFigur, int pos, int neue_pos)
{
	/* Spielfiguren, geschlagene und schlagende, von Spielbrett löschen */
	/* Von der Bitmaske wird "(7 << pos*3)" abgezogen, um an dieser Stelle 0 zu erzeugen */
	*neues_spielbrett = *spielbrett & ( einser_Bitmaske - (7 << pos*3) - (7 << neue_pos*3));
	/* nach Schlagen Spielfigur neu  setzen */
	*neues_spielbrett += (DarstellungFigur << neue_pos*3);
    //~ if(DarstellungFigur == DarstellungKoenig)
    //~ {
        //~ //printf("%0*lo => %0*lo \n",SpielfelderAnzahl, *spielbrett, SpielfelderAnzahl, *neues_spielbrett);
    //~ }
}


static inline int neuesSpielbrettLoesbar(figuren_param_t *param,sp_okt_t neues_spielbrett)
{
    return g_hash_table_contains(param->spielbretterHashtables[param->vorgaengerSpielbretter],(gpointer) neues_spielbrett);
}
 

/**
 * Prüft, ob ein Zug mit diesem Bauer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 *
 */
int berechneBauer(figuren_param_t *param, int x, int y)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;
	
	
	/*
	 * Bauer schlägt nach links oben
	 */
	if((x-1)>=0 && (y-1)>=0 && (param->spielbrett_array[x-1][y-1] != 0))
    {
		
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	

	/*
	 * Bauer schlägt nach links unten
	 */	
	if((x-1)>=0 && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x-1][y+1] != 0))
    {
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	/*
	 * Bauer schlägt nach rechts oben
	 */
	if((x+1)<SpielbrettBreite && (y-1)>=0 && (param->spielbrett_array[x+1][y-1] != 0))
    {
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungBauer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {

			return 1;
		}
	}

	return 0;    
}

/**
 * Prüft, ob ein Zug mit diesem Turm möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneTurm(figuren_param_t *param, int x, int y)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;
	int n;

	

	/*Turm schlägt nach rechts */
	for(n = 1; (x+n) < SpielbrettBreite ; n++)
	{
		if(param->spielbrett_array[x+n][y] != 0)
		{	
            
			neue_pos = (x+n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Turm schlägt nach links*/
	for(n = 1; (x-n) >= 0 ; n++)
	{	
        if (param->spielbrett_array[x-n][y] != 0)
		{
			neue_pos = (x-n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Turm schlägt nach oben*/
	for(n = 1; (y-n) >= 0; n++)
	{
		if(param->spielbrett_array[x][y-n] != 0)
		{
			neue_pos = (x)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungTurm, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	return 0;
}

/**
 * Prüft, ob ein Zug mit diesem Läufer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneLaeufer(figuren_param_t *param, int x, int y)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;
	int n;
	
	
	/*Läufer schlägt nach links oben*/
	for(n = 1; ((x-n)>=0) && ((y-n)>=0); n++)
	{	
        if(param->spielbrett_array[x-n][y-n] != 0)
        {
			neue_pos = (x-n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Läufer schlägt nach links unten*/
	for(n = 1; ((x-n)>=0) && ((y+n) < SpielbrettHoehe) ; n++)
	{	
        if(param->spielbrett_array[x-n][y+n] != 0)
        {
			neue_pos = (x-n)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Läufer schlägt nach rechts oben*/
	for(n = 1; ((x+n) < SpielbrettBreite) && ((y-n)>=0); n++)
	{	
        if(param->spielbrett_array[x+n][y-n] != 0)
        {
			neue_pos = (x+n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungLaeufer, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	return 0;
}

/**
 * Prüft, ob ein Zug mit diesem Springer an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneSpringer(figuren_param_t *param, int x, int y)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;
	
    
    	/*
	 * Springer schlägt nach erst oben dann rechts
	 */
	if((x+1)<SpielbrettBreite && (y-2)>=0 && (param->spielbrett_array[x+1][y-2] != 0))
    {
		
		neue_pos = (x+1)+((y-2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
    
	/*
	 * Springer schlägt nach erst oben  dann links
	 */
	if((x-1)>=0 && (y-2)>=0 && (param->spielbrett_array[x-1][y-2] != 0))
    {
		
		neue_pos = (x-1)+((y-2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
        if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
            return 1;
        }
	}
	
	
	/*
	 * Springer schlägt nach erst links dann oben
	 */	
	if((x-2)>=0 && (y-1)>=0 && (param->spielbrett_array[x-2][y-1] != 0))
    {
		
		neue_pos = (x-2)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach links unten
	 */	
	if((x-2)>=0 && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x-2][y+1] != 0))
    {
		
		neue_pos = (x-2)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach unten links
	 */
	if((x-1)>=0 && (y+2)<SpielbrettHoehe && (param->spielbrett_array[x-1][y+2] != 0))
    {
	
		neue_pos = (x-1)+((y+2)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	
	/*
	 * Springer schlägt nach rechts oben
	 */
	if((x+2)<SpielbrettBreite && (y-1)>=0 && (param->spielbrett_array[x+2][y-1] != 0))
    {
		
		neue_pos = (x+2)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungSpringer, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	return 0;    
}

/**
 * Prüft, ob ein Zug mit dem König an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneKoenig(figuren_param_t *param, int x, int y)
{
	int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;

/*
	 * König schlägt nach links oben
	 */
	if((x-1)>=0 && (y-1)>=0 && (param->spielbrett_array[x-1][y-1] != 0))
    {
		
		neue_pos = (x-1)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	

	/*
	 * König schlägt nach links unten
	 */	
	if((x-1)>=0 && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x-1][y+1] != 0))
    {
		neue_pos = (x-1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	/*
	 * König schlägt nach rechts oben
	 */
	if((x+1)<SpielbrettBreite && (y-1)>=0 && (param->spielbrett_array[x+1][y-1] != 0))
    {
		neue_pos = (x+1)+((y-1)*SpielbrettBreite);
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	/*
	 * König schlägt nach rechts unten
	 */
	if((x+1)<SpielbrettBreite && (y+1)<SpielbrettHoehe && (param->spielbrett_array[x+1][y+1] != 0))
    {
		neue_pos = (x+1)+((y+1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {

			return 1;
		}
	}

	
	/*
	 * König schlägt nach oben
	 */
	if((y-1)>=0 && (param->spielbrett_array[x][y-1] != 0))
    {
		
		neue_pos = (x)+((y-1)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	
	/*
	 * König schlägt nach links
	 */	
	if((x-1)>=0 && (param->spielbrett_array[x-1][y] != 0))
    {
		
		neue_pos = (x-1)+((y)*SpielbrettBreite);
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Ueberpruefen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
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
		
		schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungKoenig, pos, neue_pos);
		
		/* Überprüfen, ob das neue Spielbrett loesbar ist*/
		if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
        {
			return 1;
		}
	}
	
	return 0; 
}

/**
 * Prüft, ob ein Zug mit der Dame an Position(x,y) möglich ist und ein lösbares Spielbrett entsteht.
 *  
 * @param *param Pointer auf den struct mit allen Information über das Spielbrett
 * @param x x-Wert der Position der betrachteten Figur
 * @param y y-Wert der Position der betrachteten Figur
 * @return gibt 1 zurück, wenn ein lösbares Spielbrett ensteht, sonst 0
 */
int berechneDame(figuren_param_t *param, int x, int y)
{
    int pos = x+(y*SpielbrettBreite);
	int neue_pos;
	sp_okt_t neues_spielbrett;
    int n;
    
    
	/*Dame schlägt nach rechts */
	for(n = 1; (x+n) < SpielbrettBreite ; n++)
	{
		if(param->spielbrett_array[x+n][y] != 0)
		{	
            
			neue_pos = (x+n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach links*/
	for(n = 1; (x-n)>=0 ; n++)
	{	
        if (param->spielbrett_array[x-n][y] != 0)
		{
			neue_pos = (x-n)+((y)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach unten */
	for(n = 1; (y+n) < SpielbrettHoehe ; n++)
	{
		if(param->spielbrett_array[x][y+n] != 0)
		{
			neue_pos = (x)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach oben*/
	for(n = 1; (y-n)>=0; n++)
	{
		if(param->spielbrett_array[x][y-n] != 0)
		{
			neue_pos = (x)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
    
    /*Dame schlägt nach links oben*/
	for(n = 1; ((x-n)>=0) && ((y-n)>=0); n++)
	{	
        if(param->spielbrett_array[x-n][y-n] != 0)
        {
			neue_pos = (x-n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach links unten*/
	for(n = 1; ((x-n)>=0) && ((y+n) < SpielbrettHoehe) ; n++)
	{	
        if(param->spielbrett_array[x-n][y+n] != 0)
        {
			neue_pos = (x-n)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach rechts oben*/
	for(n = 1; ((x+n) < SpielbrettBreite) && ((y-n)>=0); n++)
	{	
        if(param->spielbrett_array[x+n][y-n] != 0)
        {
			neue_pos = (x+n)+((y-n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	/*Dame schlägt nach rechts unten*/
	for(n = 1; ((x+n) < SpielbrettBreite) && ((y+n) < SpielbrettHoehe) ; n++)
	{	
        if(param->spielbrett_array[x+n][y+n] != 0)
        {
			neue_pos = (x+n)+((y+n)*SpielbrettBreite);
			schlageFigur(param->spielbrett, &neues_spielbrett, DarstellungDame, pos, neue_pos);
			/* Überprüfen, ob das neue Spielbrett loesbar ist*/
            if( neuesSpielbrettLoesbar(param, neues_spielbrett) )
            {
                return 1;
            }
		}
	}
	
	return 0;
}
