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
	struct termios	term;

	(void)si;
	(void)v;
	if (i == SIGINT)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		write(STDOUT_FILENO, "\n>", 2);
	}
	else if (i == SIGQUIT)
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	blockaction(void)
{
	struct sigaction	sac;

	sac.sa_sigaction = accion;
	sigemptyset(&sac.sa_mask);
	sac.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sac, 0);
	sigaction(SIGINT, &sac, 0);
}

void	allowaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}

/*void	accion(int i, siginfo_t *si, void *v)
{
	struct termios	term;
	char			*c;

	(void)si;
	(void)v;
	tcgetattr(STDIN_FILENO, &term);
	if (i == SIGINT)
	{
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		write(STDOUT_FILENO, "\n>", 2);
	}
	else if (i == SIGQUIT)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		c = prntpwdline(0);
		write(STDOUT_FILENO, c, ft_strlen(c));
	}
}*/

/*void	accion(int i, siginfo_t *si, void *v)
{
	struct termios	term;

	(void)si;
	(void)v;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (i == SIGINT)
	{
		write(STDOUT_FILENO, "\n>", 2);
	}
	else if (i == SIGQUIT)
	{
		return ;
	}
}*/
