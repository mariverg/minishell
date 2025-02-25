/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:17:23 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:17:23 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divider.h"

t_list	*getchunks(char *c)
{
	int		i;
	int		startpoint;
	int		endpoint;
	t_list	*pointer;
	t_list	*firstnode;

	firstnode = ft_lstnew(0);
	pointer = firstnode;
	startpoint = 0;
	endpoint = ft_strlen(c);
	i = 0;
	while (i < endpoint)
	{
		i += getspacer(&c[i], "|");
		pointer->next = ft_lstnew(0);
		pointer = pointer->next;
		pointer->content = ft_substr(c, startpoint, i - startpoint);
		i++;
		startpoint = i;
	}
	pointer = firstnode->next;
	free(firstnode);
	return (pointer);
}

t_comand	*makecomands(char *c)
{
	t_comand	*firstnode;
	t_comand	*pointer;
	t_list		*rawproceses;
	t_list		*trash;

	if (!c)
		return (0);
	firstnode = malloc(sizeof(t_comand));
	if (!(firstnode))
		return (0);
	firstnode->next = 0;
	pointer = firstnode;
	rawproceses = getchunks(c);
	trash = rawproceses;
	while (rawproceses)
	{
		pointer->next = getcom(rawproceses->content);
		rawproceses = rawproceses->next;
		pointer = pointer->next;
		pointer->next = 0;
	}
	pointer = firstnode->next;
	free(firstnode);
	freelst(trash);
	return (pointer);
}
