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

#include "libs/libft/libft.h"
#include "minishell.h"
#include "divider/divider.h"

char	*prntpwdline(void)
{
	char	*directorio;
	char	*prompt;
	size_t	dir_len;

	directorio = getcwd(0, 0);
	if (directorio)
	{
		dir_len = ft_strlen(directorio);
		prompt = malloc(dir_len + 4);
		if (!prompt)
		{
			free(directorio);
			return (ft_strdup("error_generating_prompt > "));
		}
		ft_memcpy(prompt, directorio, dir_len);
		prompt[dir_len] = ' ';
		prompt[dir_len + 1] = '>';
		prompt[dir_len + 2] = ' ';
		prompt[dir_len + 3] = '\0';
		free(directorio);
		return (prompt);
	}
	return (ft_strdup("unknown_directory > "));
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
