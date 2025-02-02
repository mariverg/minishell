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

int operatereadfile(t_filedir *tf, t_env *te)
{
	int filefd;

	if(!tf)
		return(0);
	if(!tf->content)
		return(0);
	while(tf)
	{
		filefd = readfrmfile(tf, te);
		dup2(filefd, STDIN_FILENO);
		close(filefd);
		tf = tf->next;
	}
	return(1);
}

int operatewritefile(t_filedir *tf, t_env *te)
{
	int filefd;

	if(!tf)
		return(0);
	if(!tf->content)
		return(0);
	while(tf)
	{
		filefd = copitfile(tf, te);
		dup2(filefd, STDOUT_FILENO);
		close(filefd);
		tf = tf->next;
	}
	return(1);
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
			if (!operatereadfile(tt->filesin, tt->env))
				dup2(tt->in, STDIN_FILENO);
			if (!operatewritefile(tt->filesout, tt->env))
				dup2(tt->out, STDOUT_FILENO);
			clearpipes(pipelst);
			if (tt->c)
				runtask(tt);
			else
				exit (0);
			errormsg(" command not found", 0);
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
	
	i = -1;
	while(tt)
	{
		pid = waitpid(tt->pid, &status, 0);
		if (pid == tt->pid)
		{
			if (WIFEXITED(status) && tt->position > i) 
			{
				i = tt->position;
				switchexit(WEXITSTATUS(status), tt->env, 0);
			}
			else if (WIFSIGNALED(status)  && tt->position > i) 
			{
				i = tt->position;
				switchexit(WTERMSIG(status), tt->env, 0);
			}
			else 
			{
				i = tt->position;
				switchexit(WTERMSIG(status), tt->env, 0);
			}
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