#include "divider.h"

char	*estractclean(char *c)
{
	int	i;

	while (*c)
	{
		while (*c == ' ' || *c == '>' || *c == '<' || *c == '\t')
			c++;
		i = getspacer(c, " <>");
		return (ft_substr(c, 0, i));
	}
	return (0);
}

int	getsearch(char *c, t_list *empty, int searching)
{
	if (c[0] == '>' || c[0] == '<')
	{
		if (c[1] == ' ' || c[2] == ' ')
			return (0);
		else
			return (1);
	}
	else if (searching)
	{
		ft_lstlast(empty)->next = ft_lstnew(estractclean(c));
		return (1);
	}
	return (1);
}

t_list	*getparameters(char *c)
{
	int		i;
	t_list	*empty;
	t_list	*pointer;
	int		searching;

	empty = ft_lstnew(0);
	searching = 1;
	while (*c)
	{
		i = getspacer(c, " ");
		if (i > 0)
		{
			searching = getsearch(c, empty, searching);
			c += i;
		}
		else
			c++;
	}
	pointer = empty->next;
	free(empty);
	return (pointer);
}

t_comand	*getcom(char *c)
{
	t_comand	*res;

	res = malloc(sizeof(t_comand));
	if (!res)
		return (0);
	res->argslst = getparameters(c);
	res->infile = getredir(c, "<");
	res->outfile = getredir(c, ">");
	delcomas(res);
	return (res);
}
