/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:08:28 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:08:33 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	freestrs(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
	return (0);
}

int	freelst(t_list *tl)
{
	t_list	*chain;

	while (tl)
	{
		chain = tl;
		tl = tl->next;
		if (chain->content)
			free(chain->content);
		free(chain);
	}
	return (0);
}

int	freefilelist(t_filedir *tl)
{
	t_filedir	*chain;

	while (tl)
	{
		chain = tl;
		tl = tl->next;
		if (chain->content)
			free(chain->content);
		free(chain);
	}
	return (0);
}

int	freecomand(t_comand *cmd)
{
	if (!cmd)
		return (0);
	freelst(cmd->argslst);
	freefilelist(cmd->infile);
	freefilelist(cmd->outfile);
	free(cmd);
	return (0);
}

int	freecomands(t_comand *tc)
{
	t_comand	*copy;

	while (tc)
	{
		copy = tc;
		tc = tc->next;
		freecomand(copy);
	}
	return (0);
}
