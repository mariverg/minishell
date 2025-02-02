#include  "prechecker.h"

int cancontinue(char *c)
{
	if(!c)
		return (0);
	while (*c == ' ' || *c == '\t')
		c++;
	if (*c == 0)
		return (0);
	if (*c == '|')
		return(0);
	return (1);
}
