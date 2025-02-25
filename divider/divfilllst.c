/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divfilllst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:17:16 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:17:16 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divider.h"

int	filllststep(t_list *empty, char **c, int i, t_switcher *comainfo)
{
	if ((*c)[i] == '\'' && comainfo->duble == -1)
	{
		if (i > 0)
		{
			ft_lstlast(empty)->next = ft_lstnew(ft_substr(*c, 0, i));
			(*c) = (*c) + i;
		}
		(*c)++;
		comainfo->simple = -(comainfo->simple);
		return (0);
	}
	else if ((*c)[i] == '\"' && comainfo->simple == -1)
	{
		if (i > 0)
		{
			ft_lstlast(empty)->next = ft_lstnew(ft_substr(*c, 0, i));
			(*c) = (*c) + i;
		}
		(*c)++;
		comainfo->duble = -comainfo->duble;
		return (0);
	}
	return (i + 1);
}

void	filllsts(t_list *empty, char *c)
{
	int			i;
	t_switcher	*comainfo;

	i = 0;
	comainfo = malloc(sizeof(t_switcher));
	comainfo->simple = -1;
	comainfo->duble = -1;
	if (!comainfo)
		return ;
	while (c[i])
		i = filllststep(empty, &c, i, comainfo);
	if (i > 0)
		ft_lstlast(empty)->next = ft_lstnew(ft_substr(c, 0, i));
	free(comainfo);
}
