/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:17:45 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:17:45 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divider.h"

int	istruncker(char c, char *comp)
{
	while (*comp)
	{
		if (c == *comp)
			return (1);
		comp++;
	}
	return (0);
}

int	getspacer(char *c, char *comp)
{
	int	one;
	int	two;
	int	i;

	i = 0;
	one = -1;
	two = -1;
	while (c[i])
	{
		if (c[i] == '\'' && two == -1)
		{
			one = -one;
		}
		if (c[i] == '\"' && one == -1)
		{
			two = -two;
		}
		if (istruncker(c[i], comp) && one == -1 && two == -1)
		{
			return (i);
		}
		i++;
	}
	return (i);
}
