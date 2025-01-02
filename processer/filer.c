#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#include "../minishell.h"

/// abren copian y leen de archivos de texto
void copitofile(t_com *tc)
{
	char c[1];
	int arch = open(tc->c, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	int i = read(STDIN_FILENO, c, 1);
	while(i > 0)
	{
		write(arch, c, i);
		i = read(STDIN_FILENO, c, 1);
	}
	close(arch);
	exit(0);
}

void sumtofile(t_com *tc)
{
	char c[1];
	int arch = open(tc->c, O_CREAT | O_APPEND | O_WRONLY, 0777);
	int i = read(STDIN_FILENO, c, 1);
	while(i > 0)
	{
		write(arch, c, i);
		i = read(STDIN_FILENO, c, 1);
	}
	close(arch);
	exit(0);
}

void readfromfile(t_com *tc)
{
	char c[1];
	int arch = open(tc->c, O_RDONLY);
	printf("se ha abierto en archovo con id %i\n", arch);
	int i = read(arch, c, 1);
	while(i > 0)
	{
		write(STDOUT_FILENO, c, i);
		i = read(arch, c, 1);
	}
	close(arch);
	exit(0);
}

void readfromterm(t_com *tc, int fd)
{
	char *miin;

	printf("leyendodeterm hacia %i\n", fd);
	while (1)
	{
		miin = readline(">");
		if (ft_strncmp(miin, tc->c, ft_strlen(tc->c)) == 0 && ft_strlen(miin) == ft_strlen(tc->c))
			break;
		else
		{
			write(fd,miin,ft_strlen(miin));
			write(fd,"\n",1);
		}
	}
	exit(0);
}


