/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:26 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:26 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prechecker.h"

int	validchar(char c)
{
	int		i;
	char	*taboos;

	if (c == 0)
		return (0);
	i = 0;
	taboos = " \"\'|<>$";
	while (taboos[i])
	{
		if (taboos[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	stxerrchar(char c)
{
	int		i;
	char	*taboos;

	if (c == 0)
		return (0);
	i = 0;
	taboos = ";\\";
	while (taboos[i])
	{
		if (taboos[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	hasstxerr(char *c)
{
	int	simple;
	int	doble;

	simple = -1;
	doble = -1;
	while (*c)
	{
		if (*c == '\'' && doble == -1)
			simple = -simple;
		if (*c == '"' && simple == -1)
			doble = -doble;
		if (simple == -1 && doble == -1 && stxerrchar(*c) == 0)
			return (1);
		c++;
	}
	if (simple == 1 || doble == 1)
		return (1);
	return (0);
}

int	cancontinue(char *c, t_env *te)
{
	if (!c)
		return (0);
	if (hasstxerr(c))
	{
		errormsg(" syntax error", 0);
		switchexit(2, te, 0);
		return (0);
	}
	if (hasstxerrcomp(c))
	{
		errormsg(" syntax error", 0);
		switchexit(2, te, 0);
		return (0);
	}
	return (1);
}
