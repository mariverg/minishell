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

#include "taskbuilder.h"

int	builtins(char *c)
{
	if (ft_strncmp("echo", c, 5) == 0)
		return (12);
	else if (ft_strncmp("pwd", c, 4) == 0)
		return (12);
	else if (ft_strncmp("env", c, 4) == 0)
		return (12);
	else if (ft_strncmp("export", c, 7) == 0)
		return (21);
	else if (ft_strncmp("cd", c, 3) == 0)
		return (21);
	else if (ft_strncmp("unset", c, 6) == 0)
		return (21);
	else if (ft_strncmp("exit", c, 5) == 0)
		return (21);
	return (0);
}

int	validtask(t_task *tt)
{
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
	return (1);
}

int	filloperator(t_task *tt)
{
	int		i;
	char	*c;

	if (!validtask(tt))
		return (0);
	i = builtins(tt->cc[0]);
	if (i)
	{
		tt->c = ft_strdup(tt->cc[0]);
		tt->operator = i;
		return (1);
	}
	c = execinenv(tt->env, tt->cc[0]);
	if (c)
	{
		tt->c = c;
		tt->operator = 11;
		return (1);
	}
	errormsg(" command not found", 0);
	switchexit(127, tt->env, 0);
	return (-1);
}

t_task	*extractfromcomand(t_comand *tc, t_env *te, int i)
{
	t_task	*res;

	res = malloc(sizeof(t_task));
	if (!res)
		return (0);
	res->cc = getargs(tc->argslst);
	res->env = te;
	if (filloperator(res) == -1)
		return (0);
	res->filesin = tc->infile;
	res->filesout = tc->outfile;
	res->position = i;
	res->next = 0;
	return (res);
}

t_task	*dotaskslist(t_comand *tc, t_env *te)
{
	int		i;
	t_task	*empty;
	t_task	*tp;

	empty = malloc(sizeof(t_task));
	if (!empty)
		return (0);
	empty->next = 0;
	tp = empty;
	i = 0;
	while (tc)
	{
		i++;
		tp->next = extractfromcomand(tc, te, i);
		if (!tp->next)
			break ;
		tp = tp->next;
		tc = tc->next;
	}
	tp = empty->next;
	free(empty);
	return (tp);
}
