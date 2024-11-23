#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "minishell.h"

/// abre copia y lee de archivos de texto, actualmente no estan implementadas en ninguna parte del codigo, utilizan el struct t_com para saber el nombre del file y el puerto de entrada o salida
void copitofile(t_com *tc)
{
	char c[1];
	int arch = open("mitext.txt", O_CREAT | O_RDWR, 0777);
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
	int arch = open("outtext.txt", O_RDONLY);
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

