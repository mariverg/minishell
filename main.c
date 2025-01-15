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
	if(directorio)
	{
		write(STDOUT_FILENO, directorio, ft_strlen(directorio));
		free (directorio);
	}
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
	// init_readline_customization();
    while (1)
    {
        prntpwdline(te);
        input = readline(">");
        if (!input)
            break;
        add_to_history(input); // Agrega el comando al historial
        input = expanddollars(te, input);
        commands = parse(input);
        tc = dotaskslist(commands, te);
		/// aqui he pasado todos los nuevos procesos a una nueva carpeta, taskparser para que funcionen cosas como cat | cat | ls, he cambiado sustancialmente la estructura de procesos inittp en la carpeta taskparset, funcion inicio taskparser
		inittp(tc);
        free(input);
    }
    save_history_to_file(); // Guarda el historial en un archivo
    freeenv(te);
    return (0);
}


