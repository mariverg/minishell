/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actioner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:07:25 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:07:28 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	accion(int i, siginfo_t *si, void *v)
{
	(void)si;
	(void)v;
	if (i == SIGINT)
		printf("\n>");
	else if (i == SIGTSTP)
	{
		return ;
	}
}

void	blockaction(void)
{
	struct sigaction	sac;

	sac.sa_sigaction = accion;
	sigemptyset(&sac.sa_mask);
	sac.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sac, 0);
	sigaction(SIGINT, &sac, 0);
}

void	allowaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}
