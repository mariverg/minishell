#include"libtxttools.h"

char *dupstr(char *c)
{
	int		i;
	char	*res;

	if (!c)
		return (0);
	i = 0;
	res = malloc(sizeof(char) * (strsize(c) + 1));
	while(c[i])
	{
		res[i] = c[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char *sumstrs(char *ca, char *cb)
{
	int		i;
	char	*res;

	if (!ca && !cb)
		return (0);
	if (!ca)
		return (dupstr(cb));
	if (!cb)
		return (dupstr(ca));
	i = 0;
	res = malloc(sizeof(char) * (strsize(ca) + strsize(cb) + 1));
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

char *trimstr(char *c, int left, int right)
{
	int		i;
	char	*res;

	if (!c || left < 0 || right < 0)
		return (0);
	i = strsize(c) - left - right;
	if (i < 0)
		return (0);
	res = malloc(sizeof(char) * (i + 1));
	res[i] = 0;
	while (i > 0)
	{
		i--;
		res[i] = c[left + i];
	}
	return (res);
}

char *cutstr(char *c, int i)
{
	char *res;

	if (!c)
		return (0);
	if (strsize(c) <= i)
		return (dupstr(c));
	res = malloc(sizeof(char) * (i + 1));
	res[i] = 0;
	while(i > 0)
	{
		i--;
		res[i] = c[i];
	}
	return (res);
}