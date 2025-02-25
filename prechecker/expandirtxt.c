/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandirtxt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:14 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:14 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prechecker.h"

int	getalldollar(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '$')
			return (i);
		i++;
	}
	if (i == 0)
		return (-1);
	return (i);
}

char	*extractalldollars(t_env *te, char *c)
{
	int		i;
	char	*res;
	t_list	*firstnode;

	if (!c)
		return (0);
	firstnode = ft_lstnew(0);
	while (1)
	{
		i = getalldollar(c);
		if (i >= 0)
			c += extractswap(te, firstnode, c, i);
		else
			break ;
	}
	res = concattlst(firstnode->next);
	freelst(firstnode);
	return (res);
}
