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
	close(arch);
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
	close(arch);
}

void readfromfile(t_task *tc)
{
	char c[1];
	int arch = open(tc->c, O_RDONLY);
	printf("se ha abierto en archovo con id %i\n", arch);
	int i = read(arch, c, 1);
	while(i > 0)
	{
		write(tc->out, c, i);
		i = read(arch, c, 1);
	}
	close(arch);
}

void readfromterm(t_task *tc)
{
	char *miin;

	// printf("leyendodeterm hacia %i\n", fd);
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
}


