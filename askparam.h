#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef ASKPARAMS_H_
#define ASKPARAMS_H_

struct options
{
	int     num;            /* Anzahl der Threads                             */
	int     method;         /* Sequentiell / MPI                              */
    int     spielbrettBreite;/* SpielbrettBreite                              */
    int     spielbrettHoehe;/* SpielbrettHoehe                                */
} options;

void AskParams( struct options*, int, char** );

#endif
