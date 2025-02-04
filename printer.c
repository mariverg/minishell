/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:08:01 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:08:05 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

#include "minishell.h"

void printline(char *c, int out)
{
	while(*c)
	{
		write(out, c, 1);
		c++;
	}
}

int hasvalue(char *c)
{
	int i;

	i = 0;
	while(*c)
	{
		if(i == 1)
			return (1);
		if(*c == '=')
			i = 1;
		c++;
	}
	return (0);
}

void prntstrs(char **c, int out)
{
	int i;

	i = 0;
	while(c[i])
	{
		
		if(hasvalue(c[i]))
		{
			printline(c[i], out);
			printline("\n", out);
		}
		i++;
	}
}


int comparealpha(char *ca, char *cb)
{
	if(!ca && cb)
		return (1);
	if(ca && !cb)
		return (-1);
	while(*ca || *cb)
	{
		if (*ca < *cb)
			return (1);
		if (*ca > *cb)
			return (-1);
		if (*ca == '=' && *cb == '=')
			return (0);
		ca++;
		cb++;
	}
	return (0);
}

char *firstafter(t_env *te, char *c)
{
	int i;
	int lines;
	char *res;

	lines = strxsize(te->env); 
	i = 0;
	res = "~~~";
	while (i < lines)
	{
		if (comparealpha(te->env[i], res) == 1 && comparealpha(te->env[i], c) == -1)
			res = te->env[i];
		i++;
	}
	return (res);
}

char *addcomi(char *c)
{
	char *res;
	char *ca;
	char *cb;
	char *aux;
	int cut;

	cut = 0;
	while (c[cut] != '=')
		cut++;
	ca = ft_substr(c, 0, cut + 1);
	aux = ca;
	ca = ft_strjoin(ca,"\"");
	free (aux);
	cb = ft_substr(c, cut + 1, (ft_strlen(c) - cut));
	if (!(*cb))
	{
		free(ca);
		return(ft_substr(c, 0, cut));
	}
	aux = cb;
	cb = ft_strjoin(cb,"\"");
	free (aux);
	res = ft_strjoin(ca,cb);
	free(ca);
	free(cb);
	return (res);
}

int printalphabetical(t_task *te, char *toprint, char *max)
{
	int i;
	int lines;
	char *c;
	char *mod;

	(void) toprint;
	(void) max;
	c = 0;
	lines = strxsize(te->env->env); 
	i = 0;
	while (i < lines)
	{
		c = firstafter(te->env,c);
		printline("declare -x ", STDOUT_FILENO);
		mod = addcomi(c);
		printline(mod, STDOUT_FILENO);
		free (mod);
		printline("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
