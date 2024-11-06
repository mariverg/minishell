#include "libtxttools.h"
#include <stdio.h>

typedef struct mistruct{
	int x;
	int y;
} ms;

int main()
{
	char *c = "hola como estas";
	printf("%s\n", c);
	char *ca = delchars(c, " ", 0); 
	printf("%s\n", ca);
}