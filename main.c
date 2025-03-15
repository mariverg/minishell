/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/08 12:05:33 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:05:59 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "divider/divider.h"

char	*prntpwdline(void)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * 1000);
	if (!res)
		return (0);
	res = getcwd(res, 1000);
	i = ft_strlen(res);
	res[i++] = ' ';
	res[i++] = '>';
	res[i++] = ' ';
	res[i] = 0;
	return (res);
}

void	clearcicle(char *input, t_comand *comands, t_task *tt)
{
	freetasklist(tt);
	freecomands(comands);
	free(input);
}

void	freeandclose(t_env *te)
{
	rl_clear_history();
	freeenv(te);
}

int	maincicle(char *input, t_env *te)
{
	t_comand	*tc;
	t_task		*tt;

	tc = makecomands(input);
	tt = dotaskslist(tc, te);
	if (tc && tt)
	{
		inittp(tt);
	}
	clearcicle(input, tc, tt);
	return (0);
}

int	main(int argc, char **argv, char **argenv)
{
	t_env		*te;
	char		*input;
	char		*aux;

	(void)argc, (void)argv;
	blockaction();
	te = newenv(argenv);
	while (1)
	{
		aux = prntpwdline();
		input = readline(aux);
		free(aux);
		if (!input)
			break ;
		add_history(input);
		input = extractdollars(te, input);
		if (!cancontinue(input, te))
		{
			free(input);
			continue ;
		}
		maincicle(input, te);
	}
	freeandclose(te);
	return (0);
}
