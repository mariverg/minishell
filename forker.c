#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "minishell.h"

/*
esta funcion tiene complejidad
crea los pipes y los forks
en principio en cada funcion hay un pipe que se duplica al hacer fork, es decir, hay 4 extremos
mas puede llegar uno de la funcion anterior en 'entrada' es decir, 5.
ademas de eso, una vez creadas las pipes y redirigidas, manda el tc al operador correspondiente.
*/
pid_t forkea(t_comand *tc, pid_t entrada, t_entorno *te)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		// allowaction();
		// struct sigaction sa;
		// sa.sa_handler = SIG_DFL;
		// sigemptyset(&sa.sa_mask);
		// sigaction(SIGTSTP, &sa, 0);
		///el hijo
		// cierra la entrada recien creada pues la entrada que deberia usar es siempre 'entrada'
		close(fd[0]);
		if (tc->in)
		{
			dup2(entrada, STDIN_FILENO);
			// aqui cierra la entrada anterior que viene de la salida de parent... en las prubas me funciona sin ello pero creo que es necesario podria fallar
			close(entrada);
		}
		if (tc->out)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		///cierra la salida, despues de probablemente haberla redirigido al stdout.
		close(fd[1]);
		//// lanza la aplicacion correspondiente
		if(tc->operator == 0)
			execver(tc);
		else if (tc->operator == 1)
			copitofile(tc);
		else if (tc->operator == 2)
			readfromfile(tc);
		else if (tc->operator == 66)
		{
			while(1)
			{
				printf("soy el hijo estancado\n");
				sleep(1);
			}
		}
	}
	else
	{
		//// parent cierra la salida ya que nunca redirige nada
		close(fd[1]);
		if(tc->out == 0)
		{
			/// y si esta instruccion viene sin redireccion, tambien cierra la entrada que el siguiente ciclo usaria
			close(fd[0]);
		}
		// wait(0);
		wait(&te->lstret);
		if (WIFEXITED(te->lstret)) {
            te->lstret = WEXITSTATUS(te->lstret);
            printf("Proceso hijo terminó con código de salida %d\n", te->lstret);
        } else {
            printf("El proceso hijo no terminó normalmente\n");
        }
	}
	//// cierra devolviendo la entrada para leer en el proximo ciclo si es que la hay
	if(fd[0])
		return(fd[0]);
	else
		return(0);
}

