/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasksparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:37 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:37 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "taskparser.h"

int	runtask(t_task *tt)
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
	return (0);
}

int	operatereadfile(t_task *tt)
{
	int			filefd;
	t_filedir	*tf;

	tf = tt->filesin;
	if (!tf)
		return (0);
	if (!tf->content)
		return (0);
	while (tf)
	{
		filefd = readfrmfile(tf, tt->env);
		dup2(filefd, STDIN_FILENO);
		close(filefd);
		tf = tf->next;
	}
	return (1);
}

int	operatewritefile(t_task *tt)
{
	int			filefd;
	t_filedir	*tf;

	tf = tt->filesout;
	if (!tf)
		return (0);
	if (!tf->content)
		return (0);
	while (tf)
	{
		filefd = copitfile(tf, tt->env);
		dup2(filefd, STDOUT_FILENO);
		close(filefd);
		tf = tf->next;
	}
	return (1);
}

int	exectasks(t_task *tt, t_list *pipelst)
{
	int	pid;

	while (tt)
	{
		pid = fork();
		tt->pid = pid;
		if (pid == 0)
		{
			dup2(tt->in, STDIN_FILENO);
			dup2(tt->out, STDOUT_FILENO);
			operatereadfile(tt);
			operatewritefile(tt);
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

int	inittp(t_task *tt)
{
	t_list	*pipes;

	if (tt == 0)
		return (0);
	if (tt->next == 0 && tt->operator == 21)
	{
		execbuilt(tt);
		return (0);
	}
	pipes = dopipelst(tt);
	setpipes(tt, pipes);
	exectasks(tt, pipes);
	clearpipes(pipes);
	waittasks(tt);
	return (0);
}
