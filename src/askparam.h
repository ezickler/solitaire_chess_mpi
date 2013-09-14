#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef ASKPARAMS_H_
#define ASKPARAMS_H_

typedef struct options
{
	int     num;            /* Anzahl der Threads                             */
	int     method;         /* Sequentiell / MPI                              */
    int     spielbrettBreite;/* SpielbrettBreite                              */
    int     spielbrettHoehe;/* SpielbrettHoehe                                */
} options_t;


options_t option;

void AskParams(options_t*, int, char** );

#endif
