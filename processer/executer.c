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

int execbuiltin(t_task *tc)
{
	if (tc->operator == 13)
	{
		/// para crear variable sin export
		// int i = addstrenv(tc->env, tc->c);
		return (1);
	}
	else if (ft_strncmp("cd", tc->c, 3) == 0)
	{
		int i = chdir(tc->cc[1]);
		return (1);
	}
	else if (ft_strncmp("pwd", tc->c, 4) == 0)
	{
		char *wd = getmienv(tc->env, "PWD");
		write(tc->out, wd, ft_strlen(wd));
		write(tc->out, "\n", 1);
		return(1);
	}
	else if (ft_strncmp("env", tc->c, 4) == 0)
	{
		prntstrs(tc->env->env, tc->out);
		return(1);
	}
	else if (ft_strncmp("export", tc->c, 4) == 0)
	{
		// int i = 0;
		// while (tc->cc[i])
		// {
		// 	printf("el valor en %i es %s\n", i, tc->cc[i]);
		// 	i++;
		// }
		// if(tc->cc[2])
		// 	addstrenv(tc->env, tc->cc[2]);
		if(tc->cc[1])
			addstrenv(tc->env, tc->cc[1]);
		else
			printalphabetical(tc, 0, 0);
		return(1);
	}
	else if (ft_strncmp("unset", tc->c, 4) == 0)
	{
		delmienv(tc->env, tc->cc[1]);
		return (1);
	}
	else if (ft_strncmp("echo", tc->c, 4) == 0)
	{
		int i = 1;
		while(tc->cc[i])
		{
			if (i > 1)
				write(tc->out," ",1);
			write(tc->out, tc->cc[i], ft_strlen(tc->cc[i]));
			i++;
		}
		if (tc->cc[1])
			printline("\n", tc->out);
		return(1);
	}
	else if (ft_strncmp("exit", tc->c, 4) == 0)
	{
		if(tc->cc[1])
			exit(ft_atoi(tc->cc[1]));
		exit(0);
	}
	return (1);
}


