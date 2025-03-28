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
#include <termios.h>

void	accion(int i, siginfo_t *si, void *v)
{
	(void)si;
	(void)v;
	if (i == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (i == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	accioncero(int i, siginfo_t *si, void *v)
{
	(void)si;
	(void)v;
	if (i == SIGQUIT)
		write(1, "Quit: 3\n", 9);
}

void	blockaction(void)
{
	struct sigaction	sac;

	sac.sa_sigaction = accion;
	sigemptyset(&sac.sa_mask);
	sac.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sac, 0);
	sigaction(SIGINT, &sac, 0);
	sigaction(SIGTERM, &sac, 0);
}

void	nullaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = accioncero;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGTERM, &sa, 0);
}

void	allowaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGTERM, &sa, 0);
}
