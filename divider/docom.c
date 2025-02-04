#include "divider.h"

char	*estractclean(char *c)
{
	int	i;

	while(*c)
	{
		while (*c == ' ' || *c == '>' || *c == '<' || *c == '\t')
			c++;
		i = getspacer(c, " <>");
		return (ft_substr(c, 0, i));
	}
	return(0);
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
			if (c[0] == '>' || c[0] == '<')
			{
				if (c[1] == ' ' || c[2] == ' ')
					searching = 0;
			}
			else if (searching)
			{
				ft_lstlast(empty)->next = ft_lstnew(estractclean(c));
			}
			else
				searching = 1;
			c += i;
		}
		else
			c++;
	}
	pointer = empty->next;
	free(empty);
	return (pointer);
}

t_filedir *getonered(t_filedir *pointer, char *c, char ch)
{
	pointer->next = malloc(sizeof(t_filedir));
	if (pointer->next == 0)
		return (0);
	pointer = pointer->next;
	pointer->next = 0;
	if (c[1] == ch)
		pointer->type = 1;
	else
		pointer->type = 0;
	pointer->content = estractclean(c);
	return (pointer);
}

t_filedir	*getredir(char *c, char *ch)
{
	t_filedir	*empty;
	t_filedir	*pointer;
	int			i;

	empty = malloc(sizeof(t_filedir));
	if(empty == 0)
		return (0);
	empty->next = 0;
	pointer = empty;
	while (*c)
	{
		i = getspacer(c, ch);
		if (c[i] == *ch)
		{
			pointer = getonered(pointer, &c[i], *ch);
			if (c[i + 1] == *ch)
				i++;
			c = c + i + 1;
			i = 0;
		}
		else
			break;
	}
	pointer = empty->next;
	free(empty);
	return(pointer);
}

t_comand	*getcom(char *c)
{
	t_comand	*res;

	res = malloc(sizeof(t_comand));
	res->argslst = getparameters(c);
	res->infile = getredir(c, "<");
	res->outfile = getredir(c, ">");
	delcomas(res);
	return (res);
}