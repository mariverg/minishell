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
	res->lstout = -1;
	res->lstin = -1;
	res->in = STDIN_FILENO;
	res->out = STDOUT_FILENO;
	res->next = 0;
	// res->fd[0] = STDIN_FILENO;
	// res->fd[1] = STDOUT_FILENO;

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



/// saca el infile de texto, que pondre al inicio de la lista de t_com
t_task *extractin(t_command *tc, t_env *te)
{
	t_task *res;

	res = 0;
	while(tc)
	{
		if (tc->infile)
		{
			res = newtask(tc->infile, 0, te);
			if (tc->in_type == 0)
				res->operator = 2;
			else
				res->operator = 4;
		}
		tc = tc->next;
	}
	return (res);
}

/// y el out que ira al final
t_task *extractout(t_command *tc, t_env *te)
{
	t_task *res;
	
	res = 0;
	while(tc)
	{
		if (tc->outfile)
		{
			res = newtask(tc->outfile, 0, te);
			if (tc->out_type == 0)
				res->operator = 1;
			else 
				res->operator = 3;
		}
		tc = tc->next;
	}
	return (res);
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

	lastcom(res)->next = extractin(tc, te);

	while(tc)
	{
		if (!tc->args)
			break;
		i = builtins(tc);
		if (i)
		{
			///// i 12 opera en fork, i 21 ha de operar en el proceso principal
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
	lastcom(res)->next = extractout(tcc, te);
	copy = res;
	res = res->next;
	free(copy);
	return (res);
}
