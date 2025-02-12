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

char	*prntpwdline(t_env *te)
{
	char	*directorio;
	char	*prompt;
	size_t	dir_len;

	actualicepwd(te);
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

int	main(int argc, char **argv, char **argenv)
{
	t_env		*te;
	char		*input;
	t_comand	*comands;
	t_task		*tt;

	(void)argc;
	(void)argv;
	blockaction();
	te = newenv(argenv);
	while (1)
	{
		input = readline(prntpwdline(te));
		if (!input)
			break ;
		add_history(input);
		input = extractdollars(te, input);
		if (!cancontinue(input))
			continue ;
		comands = makecomands(input);
		tt = dotaskslist(comands, te);
		inittp(tt);
		clearcicle(input, comands, tt);
	}
	freeandclose(te);
	return (0);
}
