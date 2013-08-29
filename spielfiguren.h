#ifndef SPIELFIGUREN_H_
#define SPIELFIGUREN_H_

#define DarstellungLeer	    0
#define DarstellungBauer    1
#define	DarstellungTurm	    2
#define DarstellungLaeufer  3
#define DarstellungSpringer 4
#define DarstellungKoenig   5
#define DarstellungDame     6


int berechneBauer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneTurm(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneLaeufer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneSpringer(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneKoenig(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);

int berechneDame(char*** spielbrett_array, long long* spielbrett, int x, int y, int* anzahlFiguren);


#endif
