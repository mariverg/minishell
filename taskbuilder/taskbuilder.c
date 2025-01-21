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

////genera el t_com que usara forker para havecer las ejecuciones y pipes
t_task *newtask(char *c, char **cc, t_env *env)
{
	t_task *res;

	res = malloc(sizeof(t_task));
	res->c = c;
	res->cc = cc;
	res->ci = 0;
	res->co = 0;
	res->env = env;
	res->operator = 0;
	res->in = STDIN_FILENO;
	res->out = STDOUT_FILENO;
	res->next = 0;

	return (res);
}

t_task *lastcom(t_task *tc)
{
	while(tc->next)
		tc = tc->next;
	return(tc);
}

int builtins(t_command *tc)
{
	char *c = tc->args[0];
	if (ft_strnstr(c, "=", ft_strlen(c)))
	{
		return (13);
	}
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


int stractin(t_command *tc, t_task *tt)
{
	while(tc)
	{
		if (tc->infile)
		{
			// printf("file in encontrada\n");
			tt->ci = ft_strdup(tc->infile);
			tt->intype = tc->in_type;
		}
		tc = tc->next;
	}
	return (0);
}
int stractout(t_command *tc, t_task *tt)
{
	while(tc)
	{
		if (tc->outfile)
		{
			// printf("file out encontrada\n");
			tt->co = ft_strdup(tc->outfile);
			tt->outtype = tc->out_type;
		}
		tc = tc->next;
	}
	return (0);
}


////calcula los tcoms primero in, luego todos los ejecutables, y finalmente si existe out
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
		if (!tc->args)
		{
			lastcom(res)->next = newtask(0, 0, te);
			break;
		}
		i = builtins(tc);
		if (i)
		{
			lastcom(res)->next = newtask(tc->args[0], tc->args, te);
			lastcom(res)->operator = i;
		}
		else
		{
			c = execinenv(te, tc->args[0]);
			if (c)
			{
				lastcom(res)->next = newtask(c, tc->args, te);
				lastcom(res)->operator = 11;
			}
			else
			{
				///// SI ha llegado aqui no es builtin ni ejecuyable ni en path ni acceso. es command not found
				printf("%s: command not found\n", tc->args[0]);
				te->lastreturn = 127;
				return(0);
			}
		}
		tc = tc->next;
	}
	stractin(tcc, res->next);
	stractout(tcc, lastcom(res));
	// lastcom(res)->next = 0;
	copy = res;
	res = res->next;
	free(copy);
	return (res);
}
