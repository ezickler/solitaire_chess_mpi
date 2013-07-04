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
	Dez			Code	
	0 Frei		000
	1 Bauer		001
	2 Turm		010
	3 Läufer	011
	4 Springer	100
	5 König		101
	6 Dame		110
*/

#import "spielfeld.h"



//macht es sinn diese beiden Variable als global zu definieren?

long long _startSpielbrett;

long long * _folgeSpielbretter; // wie groß muss der allocierte Speicher sein?


/**
 * Wird auf gerufen um die möglichen Nachfolgebretter eines Spielbrettes zu errechnen
 *
 * @param spielbrett  ein Spielbrett in dem oben beschrieben Format
 * 
 * @return gibt eine Array der nachfolgenden Spielbretter zurück
 */
long long * _berechneSpielbrett(long long spielbrett)
{
	_startSpielbrett = spielbrett;
	
	
	//TODO berechnung der möglichen Züge und ablage der daraus Entstehenden spielbretter in _folgeSpielbretter
	
	
	
	return _folgeSpielbretter;
}


/**
 * Prüft welche möglichen Züge ein Bauer auf einer bestimmten Position hat.
 *
 * @param pos Die Position der zu ermittelnden Figur.
 *
 */
void _berechneBauer(int pos)
{
	//TODO Bauer
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






