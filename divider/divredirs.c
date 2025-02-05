#include "divider.h"

t_filedir	*newfd(char *content, int type)
{
	t_filedir	*res;

	res = malloc(sizeof(t_filedir));
	if (!res)
		return (0);
	res->content = content;
	res->type = type;
	res->next = 0;
	return (res);
}

t_filedir	*lastfd(t_filedir *init)
{
	t_filedir	*res;

	res = init;
	while (res->next)
		res = res->next;
	return (res);
}

t_filedir	*getonered(char *c, char ch)
{
	t_filedir	*res;

	res = newfd(0, 0);
	if (c[1] == ch)
		res->type = 1;
	else
		res->type = 0;
	res->content = estractclean(c);
	return (res);
}

t_filedir	*getredir(char *c, char *ch)
{
	t_filedir	*empty;
	t_filedir	*pointer;
	int			i;

	empty = newfd(0, 0);
	while (*c)
	{
		i = getspacer(c, ch);
		if (c[i] == *ch)
		{
			lastfd(empty)->next = getonered(&c[i], *ch);
			if (c[i + 1] == *ch)
				i++;
			c = c + i + 1;
			i = 0;
		}
		else
			break ;
	}
	pointer = empty->next;
	free(empty);
	return (pointer);
}
