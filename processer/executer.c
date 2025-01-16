/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:10:52 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:10:56 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/wait.h>

#include "../minishell.h"

///ejecuta la funcion execve
void execver(t_task *tc)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (tc->in != STDIN_FILENO)
		{
			dup2(tc->in, STDIN_FILENO);
			close(tc->in);
		}
		if (tc->out != STDOUT_FILENO)
		{
			dup2(tc->out, STDOUT_FILENO);
			close(tc->out);
		}
		execve(tc->c,tc->cc,tc->env->env);
	}
	else
	{
		wait(&tc->env->lastreturn);
		if (WIFEXITED(tc->env->lastreturn)) {
            tc->env->lastreturn = WEXITSTATUS(tc->env->lastreturn);
        } else {
        }
	}
}

int execbuiltin(t_task *tt)
{
	if (tt->operator == 13)
	{
		/// para crear variable sin export
		// int i = addstrenv(tt->env, tt->c);
		return (1);
	}
	else if (ft_strncmp("cd", tt->c, 3) == 0)
	{
		int i = chdir(tt->cc[1]);
		return (1);
	}
	else if (ft_strncmp("pwd", tt->c, 4) == 0)
	{
		char *wd = getmienv(tt->env, "PWD");
		write(tt->out, wd, ft_strlen(wd));
		write(tt->out, "\n", 1);
		return(1);
	}
	else if (ft_strncmp("env", tt->c, 4) == 0)
	{
		prntstrs(tt->env->env, tt->out);
		return(1);
	}
	else if (ft_strncmp("export", tt->c, 4) == 0)
	{
		if(tt->cc[1])
		{
			daemonenv(tt);
		}
		else
			printalphabetical(tt, 0, 0);
		return(1);
	}
	else if (ft_strncmp("unset", tt->c, 4) == 0)
	{
		delmienv(tt->env, tt->cc[1]);
		return (1);
	}
	else if (ft_strncmp("echo", tt->c, 4) == 0)
	{
		int n;
		int i;

		n = 0;
		if (ft_strncmp("-n", tt->cc[1], 3) == 0)
			n = 1;
		i = 1 + n;
		while(tt->cc[i])
		{
			if (i > (1 + n))
				write(tt->out," ",1);
			write(tt->out, tt->cc[i], ft_strlen(tt->cc[i]));
			i++;
		}
		if (!n)
			write(tt->out, "\n", 1);
		return(1);
	}
	else if (ft_strncmp("exit", tt->c, 4) == 0)
	{
		if(tt->cc[1])
			exit(ft_atoi(tt->cc[1]));
		exit(0);
	}
	return (1);
}


