/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbtools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:53 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:53 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskbuilder.h"

void	freetask(t_task *tt)
{
	if (tt->c)
		free(tt->c);
	if (tt->cc)
		free(tt->cc);
	free(tt);
}

int	freetasklist(t_task *tt)
{
	t_task	*copy;

	while (tt)
	{
		copy = tt;
		tt = tt->next;
		freetask(copy);
	}
	return (0);
}
