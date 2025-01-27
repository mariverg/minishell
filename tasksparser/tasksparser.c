#include "../minishell.h"
#include "taskparser.h"

int runtask(t_task *tt)
{
	if (tt->operator == 12 || tt->operator == 21)
	{
		execbuilt(tt);
		exit(0);
	}
	else if (tt->operator == 11)
	{
		execve(tt->c, tt->cc, tt->env->env);
	}
}

int exectasks(t_task *tt,  t_list *pipelst)
{
	int pid;
	int filefd;

	while(tt)
	{
		pid = fork();
		tt->pid = pid;
		if(pid == 0)
		{
			if (tt->ci)
			{
				filefd = readfrmfile(tt);
				dup2(filefd, STDIN_FILENO);
				close(filefd);
			}
			else
			{
				dup2(tt->in, STDIN_FILENO);
			}
			if (tt->co)
			{
				filefd = copitfile(tt);
				dup2(filefd, STDOUT_FILENO);
				close(filefd);
			}
			else
			{
				dup2(tt->out, STDOUT_FILENO);
			}
			clearpipes(pipelst);
			if (tt->c)
				runtask(tt);
			else
				exit (0);
			errormsg(" command not found", 0);
			// printf("error ejecutando %s\n", tt->c);
			exit(127);
		}
		
		tt = tt->next;
	}
	return (0);
}

int waittasks(t_task *tt)
{
	int i;
	int pid;
	int status;
	
	i = 0;
	while(tt)
	{
		pid = wait(&status);
		if (pid == tt->pid)
		{
			if (WIFEXITED(status) && tt->position > i) 
			{
				i = tt->position;
				switchexit(WEXITSTATUS(status), tt->env, 0);
			}
		}
		tt = tt->next;
	}
}

int waittasks2(t_task *tt)
{
	int i;
	int status; // Variable para almacenar el estado del proceso
    int exit_code; // Variable para el código de salida
	int combinedexit;

	i = 0;
	exit_code = 0;
	while(tt)
	{
		// printf("esperando al proceso en pos %i instruccion %s\n", tt->position, tt->c);
		if (wait(&status) == -1)
        {
            perror("wait"); // Manejar errores en caso de fallo
            return -1;
        }
        if (WIFEXITED(status) && tt->position > i) // Verificar si el proceso terminó normalmente
        {
			i = tt->position;
			exit_code = WEXITSTATUS(status); // Extraer el código de salida
			// printf("toma el valor del proceso en pos %i codigo %i instruccion %s\n", tt->position, exit_code, tt->c);
			switchexit(exit_code, tt->env, 0);
        }
        else if (WIFSIGNALED(status)) 
        {
            // printf("Proceso terminado por señal: %d\n", WTERMSIG(status));
			// switchexit(WTERMSIG(status), tt->env, "saliendo de wait por senhal");
        }

        tt = tt->next;
	}
}

int inittp(t_task *tt)
{
	t_list *pipes;

	if(tt == 0)
		return(0);
	/////				ESTA SOLO FUNCIONA CON EXIT CD  ISSET Y EXPORT
	if (tt->next == 0 && tt->operator == 21)
	{
		execbuilt(tt);
		return(0);
	}
	// printcm(tt);
	pipes = dopipelst(tt);
	setpipes(tt, pipes);
	exectasks(tt, pipes);
	// write(1, "\nCLEANING PIPES\n", 16);
	clearpipes(pipes);
	waittasks(tt);
	return (0);
}