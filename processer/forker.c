/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:11:14 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:11:20 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../minishell.h"

/// esta funcion es fundamental y se llama forkea por que la principal accion de la funcion es crear el fork que ejecutara los programas desde un nuevo proceso para no interrumpir el shell
int forkea(t_task *tc, int entrada, t_env *te)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		////										HIJO
		// cierra la entrada recien creada pues la entrada que deberia usar es siempre 'entrada'
		close(fd[0]);
		if (tc->in)
		{
			dup2(entrada, STDIN_FILENO);
			// aqui cierra la entrada anterior que viene de la salida de parent... en las prubas me funciona sin ello pero creo que es necesario podria fallar
			close(entrada);
		}
		if (tc->out && tc->operator != 4)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		
		if(tc->operator == 11)
			execver(tc);
		if(tc->operator == 12)
		{
			execbuiltin(tc);
			exit(0);
		}
		else if (tc->operator == 1)
			copitofile(tc);
		else if (tc->operator == 2)
			readfromfile(tc);
		else if (tc->operator == 3)
			sumtofile(tc);
		else if (tc->operator == 4)
			readfromterm(tc);
		///cierra la salida, despues de probablemente haberla redirigido al stdout.
		close(fd[1]);
	}
	else
	{
		////									PADRE
		//// parent cierra la salida ya que nunca redirige nada
		close(fd[1]);
		if(tc->out == 0)
		{
			/// y si esta instruccion viene sin redireccion, tambien cierra la entrada que el siguiente ciclo usaria
			close(fd[0]);
		}
		wait(&te->lastreturn);
		if (WIFEXITED(te->lastreturn)) {
            te->lastreturn = WEXITSTATUS(te->lastreturn);
            //printf("Proceso hijo terminó con código de salida %d\n", te->lstret);
        } else {
            //printf("El proceso hijo no terminó normalmente\n");
        }
	}
	//// cierra devolviendo la entrada para leer en el proximo ciclo si es que la hay
	if(fd[0])
		return(fd[0]);
	else
		return(0);
}

