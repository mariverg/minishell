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

	res = malloc(sizeof(char) * 1000);
	res = getcwd(res, 1000);
	write(STDOUT_FILENO, res, ft_strlen(res));
	write(STDOUT_FILENO, " > ", 3);
	free(res);
	return (0);
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

	(void)argc;
	(void)argv;
	blockaction();
	te = newenv(argenv);
	while (1)
	{
		input = readline(prntpwdline());
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
