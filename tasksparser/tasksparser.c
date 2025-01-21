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
			printf("error ejecutando %s\n", tt->c);
			exit(127);
		}
		
		tt = tt->next;
	}
	return (0);
}

int waittasks(t_task *tt)
{
	while(tt)
	{
		wait(0);
		tt = tt->next;
	}
}

int inittp(t_task *tt)
{
	t_list *pipes;

	if(tt == 0)
		return(0);
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