#include "libs/libtxttools.h"
#include <stdio.h>

int main()
{
	char *c;
	char **cc;

	c =  getenv("PATH");
	printf("\nORIGINAL\n%s\n", c);
	cc = strxplode(c,":");
	printf("\nEXPLODE\n");
	prntstrs(cc);
	cc = strdisolve(c, ":");
	printf("\nDISOLVE\n");
	prntstrs(cc);
	cc = strdivide(c, ":");
	printf("\nDIVIDE\n");
	prntstrs(cc);
}