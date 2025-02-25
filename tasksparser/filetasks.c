/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetasks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:17 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:17 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../minishell.h" 

int	copitfile(t_filedir *tc, t_env *env)
{
	char	*errmsg;
	int		res;

	if (tc->type == 0)
		res = open(tc->content, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		res = open(tc->content, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (res == -1)
	{
		errmsg = ft_strjoin(" ", strerror(errno));
		errormsg(errmsg, 0);
		switchexit(1, env, 0);
		exit(1);
	}
	return (res);
}

void	addcero(char c[1024])
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\n')
		{
			c[i] = 0;
			return ;
		}
		i++;
	}
}

int	stallprocess(t_filedir *tc, t_env *env)
{
	char	c[1024];
	char	*comp;
	int		fd[2];
	size_t	l;

	pipe (fd);
	l = ft_strlen(tc->content);
	while (1)
	{
		write(1, "> ", 2);
		read(1, c, 1024);
		addcero(c);
		if (*c == 0)
			write(fd[1], "\n", 1);
		else if (ft_strncmp(c, tc->content, l) == 0 && c[l] == 0)
			break ;
		else
		{
			comp = extractalldollars(env, c);
			write(fd[1], comp, ft_strlen(comp));
			write(fd[1], "\n", 1);
		}
	}
	close (fd[1]);
	return (fd[0]);
}

int	readfrmfile(t_filedir *tc, t_env *env)
{
	char	*errmsg;
	int		res;

	if (tc->type == 0)
		res = open(tc->content, O_RDONLY);
	else
	{
		res = stallprocess(tc, env);
	}
	if (res == -1)
	{
		errmsg = ft_strjoin(" ", strerror(errno));
		errormsg(errmsg, 0);
		switchexit(1, env, 0);
		exit(1);
	}
	return (res);
}
