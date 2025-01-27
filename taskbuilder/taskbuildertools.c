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

#include "taskbuilder.h"

////genera el t_com que usara forker para havecer las ejecuciones y pipes
t_task *newtask(char *c, char **cc, t_env *env, int i)
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
	res->position = i;

	return (res);
}

t_task *lastcom(t_task *tc)
{
	while(tc->next)
		tc = tc->next;
	return(tc);
}



int stractin(t_command *tc, t_task *tt)
{
	while(tc)
	{
		if (tc->infile)
		{
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
			tt->co = ft_strdup(tc->outfile);
			tt->outtype = tc->out_type;
		}
		tc = tc->next;
	}
	return (0);
}
