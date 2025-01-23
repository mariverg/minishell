/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:12:45 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:12:49 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "taskbuilder.h"

int builtins(t_command *tc)
{
	char *c = tc->args[0];
	// if (ft_strnstr(c, "=", ft_strlen(c)))
	// {
	// 	return (13);
	// }
	if (ft_strncmp("echo", c, 5) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("pwd", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("env", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("export", c, 7) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("cd", c, 3) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("unset", c, 6) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("exit", c, 5) == 0)
	{
		return (21);
	}
	return (0);
}

int *extractone(t_task *tt, t_command *tc, t_env *te)
{
	int i;
	char *c;

	if (!tc->args)
	{
		lastcom(tt)->next = newtask(0, 0, te);
		return (0);
	} 
	else 
	{
		i = builtins(tc);
		if (i)
		{
			lastcom(tt)->next = newtask(tc->args[0], tc->args, te);
			lastcom(tt)->operator = i;
		}
		else
		{
			c = execinenv(te, tc->args[0]);
			if (c)
			{
				lastcom(tt)->next = newtask(c, tc->args, te);
				lastcom(tt)->operator = 11;
			}
			else
			{
				errormsg(" command not found", 0);
				// perror("%s: command not found\n", tc->args[0]);
				switchexit(127, te, 0);
				return(0);
			}
		}
	}
	if (tc->infile)
	{
		lastcom(tt)->ci = ft_strdup(tc->infile);
		lastcom(tt)->intype = tc->in_type;
	}
	if (tc->outfile)
	{
		lastcom(tt)->co = ft_strdup(tc->outfile);
		lastcom(tt)->outtype = tc->out_type;
	}
	return (0);
}

t_task *dotaskslist(t_command *tc, t_env *te)
{
	int i = 0;
	t_task *res;
	t_task *copy;
	char *c;
	int miport = 0;
	t_command *tcc;
	
	tcc = tc;
	res = newtask(0,0,0);

	while(tc)
	{
		extractone(res, tc, te);
		tc = tc->next;
	}
	// stractin(tcc, res->next);
	// stractout(tcc, lastcom(res));
	copy = res;
	res = res->next;
	free(copy);
	return (res);
}
