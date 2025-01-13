/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:11:03 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:11:06 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#include "../minishell.h"

/// abren copian y leen de archivos de texto
void copitofile(t_task *tc)
{
	char c[1];
	int arch = open(tc->c, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	int i = read(tc->in, c, 1);
	while(i > 0)
	{
		write(arch, c, i);
		i = read(tc->in, c, 1);
	}
	write(arch, "\n", 1);
	close(arch);
	tc->env->lastreturn = 0;
}

void sumtofile(t_task *tc)
{
	char c[1];
	int arch = open(tc->c, O_CREAT | O_APPEND | O_WRONLY, 0777);
	int i = read(tc->in, c, 1);
	while(i > 0)
	{
		write(arch, c, i);
		i = read(tc->in, c, 1);
	}
	write(arch, "\n", 1);
	close(arch);
	tc->env->lastreturn = 0;
}

void readfromfile(t_task *tc)
{
	char c[1];
	int arch = open(tc->c, O_RDONLY);
	int i = read(arch, c, 1);
	while(i > 0)
	{
		write(tc->out, c, i);
		i = read(arch, c, 1);
	}
	close(arch);
	tc->env->lastreturn = 0;
}

void readfromterm(t_task *tc)
{
	char *miin;

	while (1)
	{
		miin = readline(">");
		if (ft_strncmp(miin, tc->c, ft_strlen(tc->c)) == 0 && ft_strlen(miin) == ft_strlen(tc->c))
			break;
		else
		{
			write(tc->out,miin,ft_strlen(miin));
			write(tc->out,"\n",1);
		}
	}
	tc->env->lastreturn = 0;
}


