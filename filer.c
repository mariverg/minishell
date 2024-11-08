#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "minishell.h"

/////	leen de outtext.txt y escriben a mitext.txt
////	puesto que reciben tc pueden renobrar los files, pero por simplicidad de testeo y claridad, por el momento funcionan asi
void copitofile(t_comand *tc)
{
	char c[1];
	int i = read(STDIN_FILENO, c, 1);
	int arch = open("mitext.txt", O_CREAT | O_RDWR, 0777);
	while(i > 0)
	{
		write(arch, c, i);
		i = read(STDIN_FILENO, c, 1);
	}
	exit(0);
}

void readfromfile(t_comand *tc)
{
	char c[1];
	int arch = open("outtext.txt", O_RDONLY);
	int i = read(arch, c, 1);
	while(i > 0)
	{
		write(STDOUT_FILENO, c, i);
		i = read(arch, c, 1);
	}
	exit(0);
}

/*void abrefile()
{
	int arch = open("mitxt.txt", O_CREAT | O_RDWR, 0777);
	write(arch, "un txxto", 8);
	close (arch);
}*/

