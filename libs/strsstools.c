#include "libtxttools.h"

int strxsize(char **c)
{
	int i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

int inmap(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (strxsize(map) <= y)
		return (0);
	if (strsize(map[y]) <= x)
		return (0);
	return (1);
}

char **dupxstrs(char **c)
{
	char **res;
	int i;

	if (!c)
		return (0);
	res = malloc(sizeof(char *) * (strxsize(c) + 1));
	i = 0;
	while(c[i]){
		res[i] = c[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char **sumxstrs(char **ca, char **cb)
{
	char **res;
	int i;

	if (!ca && !cb)
		return (0);
	if (!ca)
		return (dupxstrs(cb));
	if (!cb)
		return (dupxstrs(ca));
	res = malloc(sizeof(char *) * (strxsize(ca) + strxsize(cb) + 1));
	i = 0;
	while(*ca)
	{
		res[i] = *ca;
		ca++;
		i++;
	}
	while(*cb)
	{
		res[i] = *cb;
		cb++;
		i++;
	}
	res[i] = 0;
	return (res);

}
// char **excludeliteral(char *c, char *exclusor)
// {
	// char	**res;
	// int		i;
	// int		j;

	// i = charamount(c, exclusor);
	// printf("hay %i de %s\n", i , exclusor);
	// int tam = (i / 2) + 1;
	// printf("por tanto hay %i cadenas\n", tam);
	// res = malloc(sizeof(char *) * (tam +1));
	// j = 0;
	// while (j < tam)
	// {
	// 	i = charpos(c, exclusor);

	// 	j++;
	// }

// 	return (0);
// }