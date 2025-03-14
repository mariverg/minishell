/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builttasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:05 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:05 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskparser.h" 

int	getexit(t_task *tt)
{
	int	res;

	res = 0;
	if (tt->cc[1])
	{
		if (tt->cc[2])
		{
			errormsg(" too many arguments", 0);
			switchexit(1, tt->env, 0);
			return (1);
		}
		res = ft_atoi(tt->cc[1]);
		if (!res)
		{
			errormsg(" numeric argument required\n", 0);
			freeandclose(tt->env);
			exit (2);
		}
	}
	freeandclose(tt->env);
	exit (res);
	return (0);
}

void	prinworkingd(void)
{
	char	*wd;

	wd = getcwd(0, 0);
	write(STDOUT_FILENO, wd, ft_strlen(wd));
	write(STDOUT_FILENO, "\n", 1);
	free(wd);
}

int	execbuilt(t_task *tt)
{
	if (ft_strncmp("cd", tt->c, 3) == 0)
		return (changedir(tt));
	else if (ft_strncmp("pwd", tt->c, 4) == 0)
		prinworkingd();
	else if (ft_strncmp("env", tt->c, 4) == 0)
		prntstrs(tt->env->env, STDOUT_FILENO);
	else if (ft_strncmp("export", tt->c, 4) == 0)
	{
		if (tt->cc[1])
			daemonenv(tt);
		else
			printalphabetical(tt, 0, 0);
	}
	else if (ft_strncmp("unset", tt->c, 4) == 0)
		delenvs(tt);
	else if (ft_strncmp("echo", tt->c, 4) == 0)
		echobuilt(tt);
	else if (ft_strncmp("exit", tt->c, 4) == 0)
	{
		getexit(tt);
	}
	return (0);
}
