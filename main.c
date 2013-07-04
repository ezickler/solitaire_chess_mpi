#include "main.h"

int main (int argc, char ** argv){
	
	struct options options;
	
	AskParams(&options, argc, argv);
	
	return EXIT_SUCCESS;
	
}