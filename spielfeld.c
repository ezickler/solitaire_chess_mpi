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
**/

#import "spielfeld.h"




