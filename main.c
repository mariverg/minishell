
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "libs/libft/libft.h"
#include <fcntl.h>

/// esta funcion busca la variable de entorno pwd y la imprime en pantalla antes del >
void prntpwdline(t_env *te)
{
	char	*directorio;
	
	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	printf("%s",directorio);
	free (directorio);
}

int main(int argc, char **argv, char **argenv)
{
	t_env		*mientorno;
	char		*input;
    t_command	*commands;
    int			i;
	int			miport;
	char		*c;
	t_com	*uncomando;
	char *directorio;

	blockaction();
	mientorno = newenv(argenv);
	while (1)
	{
		prntpwdline(mientorno);
		input = readline(">");
		if (!input)
			break;
		input = expanddollars(mientorno, input);
		commands = parse(input);
		miport = 0;
		t_com *miscomandos = getcomslist(commands, mientorno);
		printf("comandos hechos\n");
		if (miscomandos == 0)
		{
			printf("no caomando\n");
		}
		else if (miscomandos->operator == 21 && miscomandos->next == 0)
		{
			execbuiltin(miscomandos);
		} 
		else 
		{
			while (miscomandos)
			{
				if (miscomandos->next)
					miscomandos->out = 1;
				if (miport)
					miscomandos->in = 1;
				if (miscomandos->operator == 21)
				{
					char car[1];
					int fd = open("/dev/null", O_RDWR);
					int ii = read(miport, car, 1);
					while(ii)
					{
						write(fd, car, 1);
						ii = read(miport, car, 1);
					}
				}
				else
				{
					miport = forkea(miscomandos, miport, mientorno);
				}
				miscomandos = miscomandos->next;
			}
		}
		free(input);
	}
	freeenv(mientorno);
	return (0);
}

