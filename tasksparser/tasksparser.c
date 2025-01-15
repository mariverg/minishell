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
	else if (tt->operator == 1)
	{
		copitfile(tt);
		exit(0);
	}
	else if (tt->operator == 3)
	{
		sumtfile(tt);
		exit(0);
	}
	else if (tt->operator == 2)
	{
		readfrmfile(tt);
		exit(0);
	}
	else if (tt->operator == 4)
	{
		readfrmfile(tt);
		exit(0);
	}
}

int exectasks(t_task *tt,  t_list *pipelst)
{
	int pid;
	while(tt)
	{
		if (tt->operator == 4)
		{
			readfrmterm(tt);
		} 
		else
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(tt->in, STDIN_FILENO);
				dup2(tt->out, STDOUT_FILENO);
				clearpipes(pipelst);
				runtask(tt);
				printf("error ejecutando %s\n", tt->c);
				exit(127);
			}
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
	clearpipes(pipes);
	waittasks(tt);
	return (0);
}