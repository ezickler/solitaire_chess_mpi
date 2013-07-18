#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef ASKPARAMS_H_
#define ASKPARAMS_H_

struct options
{
	int     num;            /* Anzahl der Threads                             */
	int     method;         /* Gauss Seidel or Jacobi method of iteration     */
};

void AskParams( struct options*, int, char** );

#endif
