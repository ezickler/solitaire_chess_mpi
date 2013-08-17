#import "spielfiguren.h"


/**
 * Prüft welche möglichen Züge ein Bauer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneBauer(int pos)
{
	// Zu überprüfende Position bekommt man aus dem Speilbrett durch Division durch (8 * pos)
	// Es soll das Feld recht unterhalb von pos überprüft werden
	// also muss +1 für den schrit nach recht und + Spielbrettbreite gerechnet werden
	// um die zuz Prüfende Position zu erreichen.
	// Anschließend wir Modulo 8 gerechnet um die Belegung dieser Position zu bestimmen.
	if((_startSpielbrett/((pos+1+SpielbrettBreite)*8))%8 != 0 ){
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
void _berechneTurm(int pos)
{
	//TODO Turm 
}

/**
 * Prüft welche möglichen Züge ein Läufer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneLaeufer(int pos)
{
	//TODO Läufer
}

/**
 * Prüft welche möglichen Züge ein Springer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneSpringer(int pos)
{
	//TODO Springer
}

/**
 * Prüft welche möglichen Züge ein König auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneKoenig(int pos)
{
	//TODO König
}

/**
 * Prüft welche möglichen Züge eine Dame auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneDame(int pos)
{
	//TODO Dame
}






