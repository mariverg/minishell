#include "divider.h"

char *estractclean(char *c)
{
	char *res;
	int i;

	while(*c)
	{
		while (*c == ' ' || *c == '>' || *c == '<' || *c == '\t')
			c++;
		i = getspacer(c, " <>");
			return (ft_substr(c, 0, i));
		break;
	}
	return(0);
}

t_list *getparameters(char *c)
{
	int i;
	t_list *empty;
	t_list *pointer;
	int searching;

	empty = malloc(sizeof(t_list));
	pointer = empty;
	empty->next = 0;
	empty->content = 0;
	searching = 1;
	while(*c)
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
				pointer->next = malloc(sizeof(t_list));
				pointer = pointer->next;
				pointer->next = 0;
				pointer->content = estractclean(c);
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
	return(pointer);
}

t_filedir *getredir(char *c, char ch)
{
	t_filedir *empty;
	t_filedir *pointer;
	char ctwo[2];
	int i;

	ctwo[0] = ch;
	ctwo[1] = 0;
	empty = malloc(sizeof(t_filedir));
	empty->next = 0;
	empty->content = 0;
	pointer = empty;
	while (*c)
	{
		i = getspacer(c, ctwo);
		if(c[i] == ch)
		{
			pointer->next = malloc(sizeof(t_filedir));
			pointer = pointer->next;
			pointer->next = 0;
			if (c[i + 1] == ch)
			{
				pointer->type = 1;
				i++;
			}
			else
				pointer->type = 0;
			c = c + i + 1;
			i = 0;
			pointer->content = estractclean(c);
		}
		else
			break;
	}
	pointer = empty->next;
	free(empty);
	return(pointer);
}

t_comand *getcom(char *c)
{
	t_comand *res;

	res = malloc(sizeof(t_comand));
	res->argslst = getparameters(c);
	res->infile = getredir(c, '<');
	res->outfile = getredir(c, '>');
	delcomas(res);
	// prt(res);
	return (res);
}