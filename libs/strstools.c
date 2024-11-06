#include "libtxttools.h"

char **strdivide(char *c, char *ca)
{
	int i;
	int j;
	char **res;

	if (!c || !ca)
		return (0);
	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (charamount(c, ca) + 2));
	while ((i = charpos(c, ca)) != -1)
	{
		res[j] = cutstr(c, i);
		c = c + i + 1;
		j++;
	}
	if(*c)
		res[j++] = dupstr(c);
	res[j] = 0;
	return (res);
}

char **strxplode(char *c, char *ca)
{
	int		i;
	int		index;
	char	*tmpres[255];
	char	**res;

	if(!c || !ca || !*c || !*ca)
		return(0);
	index = 0;
	while ((i = charpos(c, ca)) != -1)
	{
		if (i == 0)
			tmpres[index++] = cutstr(c++, 1);
		else
		{
			tmpres[index++] = cutstr(c, i);
			c += i;
		}
	}
	if (*c)
		tmpres[index++] = dupstr(c);
	res = malloc(sizeof(char *) * (index + 1));
	res[index] = 0;
	while(index > 0)
	{
		index--;
		res[index] = tmpres[index];
	}
	return (res);
}

char **strdisolve(char *c, char *ca)
{
	int		i;
	int		index;
	char	*tmpres[255];
	char	**res;

	if(!c || !ca || !*c || !*ca)
		return(0);
	index = 0;
	while ((i = charpos(c, ca)) != -1)
	{
		if (i == 0)
			c++;
		else
		{
			tmpres[index++] = cutstr(c, i);
			c += i;
		}
	}
	if (*c)
		tmpres[index++] = dupstr(c);
	res = malloc(sizeof(char *) * (index + 1));
	res[index] = 0;
	while(index > 0)
	{
		index--;
		res[index] = tmpres[index];
	}
	return (res);
}

void freestrs(char **c)
{
	int i;

	i = 0;
	while(c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}

void prntstrs(char **c)
{
	while(*c)
	{
		write(1,">",1);
		write(1,*c,strsize(*c));
		write(1,"\n",1);
		c++;
	}
}