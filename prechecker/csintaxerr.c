/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csintaxerr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:04 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:04 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prechecker.h"

struct s_sxtracker	*newst(void)
{
	struct s_sxtracker	*res;

	res = malloc(sizeof(struct s_sxtracker));
	if (!res)
		return (0);
	res->apipe = 1;
	res->aminus = 0;
	res->amore = 0;
	return (res);
}

int	updatest(char c, struct s_sxtracker *st)
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

int	hasstxerrcomp(char *c)
{
	int					simple;
	int					doble;
	struct s_sxtracker	*st;

	simple = -1;
	doble = -1;
	st = newst();
	while (*c)
	{
		if (*c == '\'' && doble == -1)
			simple = -simple;
		if (*c == '"' && simple == -1)
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
