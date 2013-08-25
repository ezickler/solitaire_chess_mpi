#import "spielfiguren.h"
/**
Spielbrett:

Links-Oben 0:0 nach x:y

  0, 1, 2, 3
  4, 5, 6, 7
  8, 9,10,11
 12,13,14,15
 */

/**
 * Prüft welche möglichen Züge ein Bauer auf einer bestimmten Position hat.
 *  
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneBauer(int pos)
{
    /*
	// Zu überprüfende Position bekommt man aus dem Speilbrett durch Division durch (8 * pos)
	// Es soll das Feld recht unterhalb von pos überprüft werden
	// also muss +1 für den schrit nach recht und + Spielbrettbreite gerechnet werden
	// um die zuz Prüfende Position zu erreichen.
	// Anschließend wir Modulo 8 gerechnet um die Belegung dieser Position zu bestimmen.
    */
	int new_pos;
		
		
	// ICH ARBEITE NOCH DRAN (Enno)	
	new_pos = ((pos+SpielbrettBreite+1));
	if((new_pos > (((pos/4)*4)+SpielbretBreite) && new_pos < ((pos%4)) && ((_startSpielbrett/(new_pos*8))%8 != 0)){
		//TODO add folge spielbretter
	}
	
	// Analog für unten links
	if((_startSpielbrett/((pos-1+SpielbrettBreite)*8))%8 != 0 ){
		//TODO add folge spielbretter
	}
	
	// Analog für oben Recht
	if((_startSpielbrett/((pos+1-SpielbrettBreite)*8))%8 != 0 ){
		//TODO add folge spielbretter
	}
	
	//Analogo für oben Link
	if((_startSpielbrett/((pos-1-SpielbrettBreite)*8))%8 != 0 ){
		//TODO add folge spielbretter
	}
}

/**
 * Prüft welche möglichen Züge ein Turm auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneTurm(int pos)
{
	//TODO Turm 
}

/**
 * Prüft welche möglichen Züge ein Läufer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneLaeufer(int pos)
{
	//TODO Läufer0
}

/**
 * Prüft welche möglichen Züge ein Springer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneSpringer(int pos)
{
	//TODO Springer
}

/**
 * Prüft welche möglichen Züge ein König auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneKoenig(int pos)
{
	//TODO König
}

/**
 * Prüft welche möglichen Züge eine Dame auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
int berechneDame(int pos)
{
	//TODO Dame
}

