#include "divider.h"


char *concatlst(t_list *tl)
{
	char *res;
	char *aux;

	res = 0;
	while(tl)
	{
		if (tl->content)
		{
			aux = res;
			res = ft_strjoin(res, tl->content);
			if(aux)
				free(aux);
		}
		tl = tl->next;
	}
	return(res);
}

char *deletecoma(char *c)
{
	char *res;
	int i;
	int simp;
	int doble;
	t_list *empty;
	t_list *pointer;

	i = 0;
	simp = -1;
	doble = -1;
	empty = malloc(sizeof(t_list));
	empty->content = 0;
	empty->next = 0;
	pointer = empty;
	while (c[i])
	{
		if (c[i] == '\'' && doble == -1)
		{
			if (i > 0)
			{
				pointer->next = malloc(sizeof(t_list));
				pointer = pointer->next;
				pointer->next = 0;
				pointer->content = ft_substr(c, 0, i);
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
				pointer->next = malloc(sizeof(t_list));
				pointer = pointer->next;
				pointer->next = 0;
				pointer->content = ft_substr(c, 0, i);
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
	{
		pointer->next = malloc(sizeof(t_list));
		pointer = pointer->next;
		pointer->next = 0;
		pointer->content = ft_substr(c, 0, i);
	}
	res = concatlst(empty->next);
	freelst(empty);
	return (res);
}

int delcomas(t_comand *tc)
{
	t_list *tl;
	t_filedir *tf;
	char *eraser;

	tl = tc->argslst;
	while(tl)
	{
		eraser = tl->content;
		tl->content = deletecoma(tl->content);
		tl = tl->next;
		free(eraser);
	}
	tf = tc->infile;
	while(tf)
	{
		eraser = tf->content;
		tf->content = deletecoma(tf->content);
		tf = tf->next;
		free(eraser);
	}
	tf = tc->outfile;
	while(tf)
	{
		eraser = tf->content;
		tf->content = deletecoma(tf->content);
		tf = tf->next;
		free(eraser);
	}
	return (0);
}