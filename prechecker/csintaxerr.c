#include "prechecker.h"

struct sxtracker
{
	int	apipe;
	int	aminus;
	int	amore;
};

struct sxtracker *newst()
{
	struct sxtracker *res;

	res = malloc(sizeof(struct sxtracker));
	if(!res)
		return (0);
	res->apipe = 1;
	res->aminus = 0;
	res->amore = 0;
	return (res);
}

int updatest(char c, struct sxtracker *st)
{
	if (c == ' ' || c == '\t')
		return (1);
	else if (c == '|')
		st->apipe++;
	else if (c == '<')
		st->aminus++;
	else if (c == '>')
		st->amore++;
	else
	{
		st->apipe = 0;
		st->aminus = 0;
		st->amore = 0;
	}
	if ((st->aminus + st->amore) >= 3)
		return (0);
	if (st->apipe >= 2)
		return (0);
	return (1);
}

int hasstxerrcomp(char *c)
{
	int simple;
	int doble;
	struct sxtracker *st;
	
	simple = -1;
	doble = -1;
	st = newst();
	while (*c)
	{
		if(*c == '\'' && doble == -1)
			simple = -simple;
		if(*c == '"' && simple == -1)
			doble = -doble;
		if (simple == -1 && doble == -1 && !updatest(*c, st))
		{
			free(st);
			return (1);
		}
		c++;
	}
	free(st);
	return (0);
}