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

////funciones de utilidad para consultar datos durante los tests, en principio no estaran en la version final
void printline(char *c, int out)
{
	while(*c)
	{
		write(out, c, 1);
		c++;
	}
}

void prntstrs(char **c, int out)
{
	int i;

	i = 0;
	while(c[i])
	{
		printline(c[i], out);
		printline("\n", out);
		i++;
	}
	/*				esta la dejo como ejemplo de borrar todo el array
	printf("printando env\n\n");
	char **c = cc;
	while(*c)
	{
		printline(*c);
		write(STDOUT_FILENO, "\n", 1);
		while(**c)
		{
			write(STDOUT_FILENO, *c, 1);
			(*c)++;
		}
		c++;
	}*/
}

void printcmmm(t_command *current)
{
	int i;

	while (current)
    {
		i = 0;
		while(current->args[i])
		{
			printf("El arg %i vale %s\n", i, current->args[i]);	
			i++;
		}
		printf("infile %s\n", current->infile);
		printf("outfile %s\n", current->outfile);
		printf("in_type %i\n", current->in_type);
		printf("out_type %i\n", current->out_type);	
        current = current->next;
    }
}

void printcm(t_task *tc)
{
	while(tc)
	{
		printf("UN COM :c es %s operator %i\n", tc->c, tc->operator);
		tc = tc->next;
	}
}

char *firstafter(t_env *te, char *c)
{
	int i;
	int lucky;
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
int printalphabetical(t_env *te, char *toprint, char *max)
{
	int i;
	int lucky;
	int lines;
	char *c;

	c = 0;
	lines = strxsize(te->env); 
	i = 0;
	while (i < lines)
	{
		c = firstafter(te,c);
		printline("declare -x ", 1);
		printline(c, 1);
		printline("\n", 1);
		i++;
	}
	return (0);
}