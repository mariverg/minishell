/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:11:53 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:11:55 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prechecker.h"

char	*concattlst(t_list *tl)
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

int	getrealdollar(char *c)
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
			one = -one;
		if (c[i] == '\"' && one == -1)
			two = -two;
		if (c[i] == '$' && one == -1)
			return (i);
		i++;
	}
	if (i == 0)
		return (-1);
	return (i);
}

int	getvarsize(char *c)
{
	int	i;

	i = 0;
	if (c[0] == '?')
		return (1);
	while (validchar(c[i]))
		i++;
	return (i);
}

int	extractswap(t_env *te, t_list *tl, char *c, int i)
{
	int		varsize;
	char	*varname;

	ft_lstlast(tl)->next = ft_lstnew(ft_substr(c, 0, i));
	c = c + i;
	if (*c == '$')
	{
		c++;
		i++;
		varsize = getvarsize(c);
		varname = ft_substr(c, 0, varsize);
		ft_lstlast(tl)->next = ft_lstnew(getmienv(te, varname));
		free(varname);
		c = c + varsize;
		i = i + varsize;
	}
	return (i);
}

char	*extractdollars(t_env *te, char *c)
{
	int		i;
	char	*res;
	t_list	*firstnode;

	if (!c)
		return (0);
	firstnode = ft_lstnew(0);
	while (1)
	{
		i = getrealdollar(c);
		if (i >= 0)
			c += extractswap(te, firstnode, c, i);
		else
			break ;
	}
	res = concattlst(firstnode->next);
	freelst(firstnode);
	return (res);
}
