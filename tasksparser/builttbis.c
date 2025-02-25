/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builttbis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:11 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:11 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "taskparser.h"

int	gohome(t_task *tt)
{
	int		i;
	char	*c;

	c = getmienv(tt->env, "HOME");
	i = chdir(c);
	if (c)
		free(c);
	return (i);
}

int	changedir(t_task *tt)
{
	int	i;

	if (!(tt->cc[1]))
		i = gohome(tt);
	else if (!(tt->cc[2]))
		i = chdir(tt->cc[1]);
	else
	{
		write(STDERR_FILENO, " too many arguments\n", 19);
		switchexit(1, tt->env, 0);
		return (0);
	}
	if (i == -1)
	{
		write(STDERR_FILENO, " No such file or directory\n", 27);
		switchexit(1, tt->env, 0);
	}
	else
		fillpwd(tt->env);
	return (0);
}

int	validflag(char *c)
{
	int	i;

	i = 0;
	if (c[i] != '-')
		return (0);
	i++;
	while (c[i])
	{
		if (c[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	excludeflags(t_task *tt)
{
	int	i;

	if (!tt->cc[1])
		return (1);
	i = 1;
	while (validflag(tt->cc[i]))
	{
		i++;
	}
	return (i);
}

int	echobuilt(t_task *tt)
{
	int	i;
	int	firstw;
	int	finalreturn;

	i = excludeflags(tt);
	finalreturn = 1;
	if (i > 1)
		finalreturn = 0;
	firstw = 0;
	while (tt->cc[i])
	{
		if (firstw)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tt->cc[i], ft_strlen(tt->cc[i]));
		firstw++;
		i++;
	}
	if (finalreturn)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
