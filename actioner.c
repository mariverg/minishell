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

#include <signal.h>
#include <stdio.h>

void accion(int i, siginfo_t *si, void *v)
{
	if (i == SIGINT)
		printf("\n>");
	else if (i == SIGTSTP) {
        // No hacer nada para SIGTSTP (Ctrl+Z)
    }
}

///bloquea acciones 
void blockaction()
{
	struct sigaction sac;
	sac.sa_sigaction = accion;
	sigemptyset(&sac.sa_mask);
	sac.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sac, 0);
	sigaction(SIGINT, &sac, 0);
}

///permite acciones
void allowaction()
{
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}
