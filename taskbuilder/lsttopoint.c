/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttopoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:34 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:34 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**getargs(t_list *tl)
{
	char	**res;
	int		i;
	int		j;
	t_list	*copy;

	i = 0;
	copy = tl;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	j = 0;
	copy = tl;
	while (j < i)
	{
		res[j] = copy->content;
		copy = copy->next;
		j++;
	}
	res[j] = 0;
	return (res);
}
