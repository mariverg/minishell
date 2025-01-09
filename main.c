/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:05:33 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:05:59 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "history/history.h"
#include "libs/libft/libft.h"
#include <fcntl.h>

void prntpwdline(t_env *te)
{
	char	*directorio;
	
	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	// printf("%s",directorio);
	write(STDOUT_FILENO, directorio, ft_strlen(directorio));
	free (directorio);
	// directorio = getmienv(te->env, "PWD");
	// write(te->out, wd, ft_strlen(wd));
	// write(te->out, "\n", 1);
	// free (directorio);
}

int docom(t_task *tc, t_env *te)
{
	if(tc->operator == 11)
		execver(tc);
	if(tc->operator == 12)
		execbuiltin(tc);
	if(tc->operator == 21)
		execbuiltin(tc);
	else if (tc->operator == 1)
		copitofile(tc);
	else if (tc->operator == 2)
		readfromfile(tc);
	else if (tc->operator == 3)
		sumtofile(tc);
	else if (tc->operator == 4)
		readfromterm(tc);
	return (0);
}

int proccoms(t_task *tt, t_env *te)
{
	int fd[2];
	while (tt)
	{
		if (tt->next)
		{
			pipe(fd);
			tt->out = fd[1];
			tt->next->in = fd[0];
		}
		docom(tt, te);
		if (tt->in >= 0 && tt->in != STDIN_FILENO)
		{
			// printf("cerrando in %i el std es %i\n", tt->in, STDIN_FILENO);
			close(tt->in);
		}
		if (tt->out >= 0 && tt->out != STDOUT_FILENO)
		{
			// printf("cerrando out %i el std es %i\n", tt->out, STDOUT_FILENO);
			close(tt->out);
		}
		tt = tt->next;
	}
	return (0);
}

int main(int argc, char **argv, char **argenv)
{
    t_env       *te;
    char        *input;
    t_command   *commands;
    t_task      *tc;

    blockaction();
    te = newenv(argenv);
    init_history(); // Inicializa el historial
    while (1)
    {
        prntpwdline(te);
        input = readline(">");
        if (!input)
            break;
        add_to_history(input); // Agrega el comando al historial
        input = expanddollars(te, input);
        commands = parse(input);
        tc = gettaskslist(commands, te);
        if (tc)
            proccoms(tc, te);
        free(input);
    }
    save_history_to_file(); // Guarda el historial en un archivo
    freeenv(te);
    return (0);
}


