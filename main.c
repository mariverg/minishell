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
#include "parseo/parseo.h"
#include "divider/divider.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>

char	*prntpwdline(t_env *te)
{
	char	*directorio;
	char	*prompt;
	size_t	dir_len;

	actualicepwd(te);
	// directorio = getmienv(te, "PWD");
	// char *getcwd(char *buf, size_t size);
	directorio = getcwd(0,0);
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
	return (0);
}

int	main(int argc, char **argv, char **argenv)
{
	t_env		*te;
	char		*input;
	t_comand	*comands;
	t_task		*tt;

	blockaction();
	te = newenv(argenv);
	comands = 0;
	while (1)
	{
		// input = 0;
		// input = "ls  | grep o | cat > asd";
		input = readline(prntpwdline(te));
		if (!input)
			break ;
		if (*input)
			add_history(input);

		input = extractdollars(te, input);
		if (!cancontinue(input))
			continue;
			// printf("	tras expanddollars input vale>\n %s\n", input);
		comands = makecomands(input);
			// prt(comands);
		tt = dotaskslist(comands, te);
			// printf("	tasks vale>\n");
			// printcm(tc);
			// printf("	tasks over>\n");
		inittp(tt);

		freetasklist(tt);
		freecomands(comands);
		free(input);
		// break;
	}
	rl_clear_history();
	freeenv(te);
	return(0);
}
