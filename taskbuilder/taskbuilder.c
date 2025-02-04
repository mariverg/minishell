/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:12:45 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:12:49 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "taskbuilder.h"

int builtins(char *c)
{
	// char *c = tc->args->content;
	// if (ft_strnstr(c, "=", ft_strlen(c)))
	// {
	// 	return (13);
	// }
	if (ft_strncmp("echo", c, 5) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("pwd", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("env", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("export", c, 7) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("cd", c, 3) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("unset", c, 6) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("exit", c, 5) == 0)
	{
		return (21);
	}
	return (0);
}


int filloperator(t_task *tt)
{
	int i;
	char *c;

	if (!tt->cc)
	{
		tt->c = 0;
		tt->operator = 0;
		return (0);
	}
	if (!tt->cc[0])
	{
		tt->c = 0;
		tt->operator = 0;
		return (0);
	}
	i = builtins(tt->cc[0]);
	if (i)
	{
		tt->c = ft_strdup(tt->cc[0]);
		tt->operator = i;
		return (0);
	}
	c = execinenv(tt->env, tt->cc[0]);
	if(c)
	{
		tt->c = c;
		tt->operator = 11;
		return (0);
	}
	errormsg(" command not found", 0);
	switchexit(127, tt->env, 0);
	return(0);
}

t_task *extractfromcomand(t_comand *tc, t_env *te, int i)
{
	t_task *res;
	char **args;

	res = malloc(sizeof(t_task));
	res->cc = getargs(tc->argslst);
	res->env = te;
	filloperator(res);
	res->filesin = tc->infile;
	res->filesout = tc->outfile;
	res->position = i;
	res->next = 0;
	return(res);
}

t_task *dotaskslist(t_comand *tc, t_env *te)
{
	int i;
	t_task *empty;
	t_task *tp;

	empty = malloc(sizeof(t_task));
	empty->next = 0;
	tp = empty;
	i = 0;
	while (tc)
	{
		i++;
		tp->next = extractfromcomand(tc, te, i);
		tp = tp->next;
		tc = tc->next;
	}
	tp = empty->next;
	free(empty);
	return (tp);
}

void freetask(t_task *tt)
{
	free(tt->c);
	free(tt->cc);
	free(tt);
}

int freetasklist(t_task *tt)
{
	t_task *copy;

	while(tt)
	{
		copy = tt;
		tt = tt->next;
		freetask(copy);
	}
	return(0);
}