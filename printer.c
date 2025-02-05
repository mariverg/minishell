/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:08:01 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:08:05 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printline(char *c, int out)
{
	while (*c)
	{
		write(out, c, 1);
		c++;
	}
}

int	hasvalue(char *c)
{
	int	i;

	i = 0;
	while (*c)
	{
		if (i == 1)
			return (1);
		if (*c == '=')
			i = 1;
		c++;
	}
	return (0);
}

void	prntstrs(char **c, int out)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (hasvalue(c[i]))
		{
			printline(c[i], out);
			printline("\n", out);
		}
		i++;
	}
}
