#include "libtxttools.h"

int findstr(char *c, char *target)
{
	int i;
	int j;
	char aux[2];

	i = 0;
	aux[0] = target[0];
	aux[1] = 0;
	while((j = charpos(c, aux)) > -1)
	{
		c += j;
		i += j;
		if(strscmp(c, target))
			return (i);
		c++;
		i++;
	}
	return (-1);
}

int findstrrow(char **c, char *target)
{
	int i;

	i = 0;
	while(*c)
	{
		if (findstr(*c,target) != -1)
			return (i);
		c++;
		i++;
	}
	return (-1);
}