/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:18:53 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:18:53 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	errormsg(char *msg, char *info)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (info)
		write(STDERR_FILENO, info, ft_strlen(info));
	return (0);
}

int	switchexit(int i, t_env *te, char *info)
{
	te->lastreturn = i;
	if (info)
		write(STDERR_FILENO, info, ft_strlen(info));
	return (0);
}
