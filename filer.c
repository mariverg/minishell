#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "minishell.h"

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
	int i = read(arch, c, 1);
	while(i > 0)
	{
		write(STDOUT_FILENO, c, i);
		i = read(arch, c, 1);
	}
	close(arch);
	exit(0);
}

/*void abrefile()
{
	int arch = open("mitxt.txt", O_CREAT | O_RDWR, 0777);
	write(arch, "un txxto", 8);
	close (arch);
}*/

