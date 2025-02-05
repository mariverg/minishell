#include "divider.h"

char	*concatlst(t_list *tl)
{
	char	*res;
	char	*aux;

	res = 0;
	while (tl)
	{
		if (tl->content)
		{
			aux = res;
			res = ft_strjoin(res, tl->content);
			if (aux)
				free(aux);
		}
		tl = tl->next;
	}
	return (res);
}

/*void	filllsts(t_list *empty, char *c)
{
	int	i;
	int	simp;
	int	doble;

	i = 0;
	simp = -1;
	doble = -1;
	while (c[i])
	{
		if (c[i] == '\'' && doble == -1)
		{
			if (i > 0)
			{
				ft_lstlast(empty)->next = ft_lstnew(ft_substr(c, 0, i));
				c = c + i;
				i = 0;
			}
			c++;
			simp = -simp;
		}
		else if (c[i] == '\"' && simp == -1)
		{
			if (i > 0)
			{
				ft_lstlast(empty)->next = ft_lstnew(ft_substr(c, 0, i));
				c = c + i;
				i = 0;
			}
			c++;
			doble = -doble;
		}
		else
			i++;
	}
	if (i > 0)
		ft_lstlast(empty)->next = ft_lstnew(ft_substr(c, 0, i));
}*/

char	*deletecoma(char *c)
{
	char	*res;
	t_list	*empty;

	empty = ft_lstnew(0);
	filllsts(empty, c);
	res = concatlst(empty->next);
	freelst(empty);
	return (res);
}

void	process_flist(t_filedir *list)
{
	t_filedir	*tf;
	char		*eraser;

	tf = (t_filedir *)list;
	while (tf)
	{
		eraser = tf->content;
		tf->content = deletecoma(tf->content);
		tf = tf->next;
		free(eraser);
	}
}

int	delcomas(t_comand *tc)
{
	t_list		*tl;
	char		*eraser;

	tl = tc->argslst;
	while (tl)
	{
		eraser = tl->content;
		tl->content = deletecoma(tl->content);
		tl = tl->next;
		free(eraser);
	}
	process_flist(tc->infile);
	process_flist(tc->outfile);
	return (0);
}
