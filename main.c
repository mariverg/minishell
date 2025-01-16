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

#include "history/history.h"
#include "libs/libft/libft.h"
#include "minishell.h"
#include "parseo/parseo.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>


/* void prntpwdline(t_env *te)
{
	char	*directorio;

	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	if(directorio)
	{
		write(STDOUT_FILENO, directorio, ft_strlen(directorio));
		free (directorio);
	}
} */

char	*prntpwdline(t_env *te)
{
	char *directorio;
	char *prompt;
	size_t dir_len;

	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	if (directorio)
	{
		dir_len = ft_strlen(directorio);//calculo la longuitud del directorio
		prompt = malloc(dir_len + 4);// Espacio para el directorio + " > "
		if (!prompt)
		{
			free(directorio);
			return (strdup("error_generating_prompt > "));
		}
		ft_memcpy(prompt, directorio, dir_len);//copio el directorio
		prompt[dir_len] = ' ';
		prompt[dir_len + 1] = '>';
		prompt[dir_len + 2] = ' ';
		prompt[dir_len + 3] = '\0';
		free(directorio);// Libero la memoria del directorio
		return (prompt);
	}
	return (ft_strdup("unknown_directory > "));
}

int	main(int argc, char **argv, char **argenv)
{
	t_env *te;
	char *input;
	t_command *commands;
	t_task *tc;

=======
	blockaction();
	te = newenv(argenv);
	while (1)
	{
		input = readline(prntpwdline(te));//Obtengo el prompt directamente dentro de readline
		if (!input)
			break ;
		if (*input) // Si no está vacío, agrégo al historial
			add_history(input);
    
		input = expanddollars(te, input);
		commands = parse(input);
		tc = dotaskslist(commands, te);
		inittp(tc);
		free(input);
	}
}
