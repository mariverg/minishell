
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

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

//// procesa los comandos, basicamente hace forker a no ser que lo unico que tenga sea un builtin, esto lo hago asi tratando de imitar el comportamiento de una linea tipo ls | cd .. | cat, que se comporta de forma inesperada. esta parte con las pipes y los fork es lo que hay que reflexionar en formas de hacerlo mejor, mas claro.


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
		readfromterm(tc, 0);
	return (0);
}

int proccoms(t_task *tt, t_env *te)
{
	// printf("haciendo comandos con operador %i\n", tc->operator);
	while (tt)
	{
		if (tt->next)
		{
			printf("redirige\n");
		}
		docom(tt, te);
		tt = tt->next;
	}
	return (0);
}

/*int proccoms2(t_task *tc, t_env *te)
{
	int	miport;

	miport = 0;
	if (tc->operator == 21 && tc->next == 0)
	{
		execbuiltin(tc);
	} 
	else 
	{
		while (tc)
		{
			if (tc->next)
				tc->out = 1;
			if (miport)
				tc->in = 1;
			//// aqui recibe un cd, exit o unset, que borran la info. lo que hago es copiarla en dev/null que tiene linux para borrar datos
			if (tc->operator == 21)
			{
				if (miport)
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
				
			}
			else
			{
				miport = forkea(tc, miport, te);
			}
			tc = tc->next;
		}
	}
	return (0);
}*/

int main(int argc, char **argv, char **argenv)
{
	t_env		*te;
	char		*input;
    t_command	*commands;
	t_task		*tc;
    int			i;
	char		*c;

	/// bloquea las anciones genera el enviroment y empieza el ciclo c>
	blockaction();
	te = newenv(argenv);
	while (1)
	{
		prntpwdline(te);
		input = readline(">");
		if (!input)
			break;
		input = expanddollars(te, input);
		commands = parse(input);
		///despues de parsear crea comandos, en esa creacion, si detecta un comando que no se puede ejecutar devuelve null e imprime error, si no es que la gramatica es correcta y  procesa los comandos
		tc = gettaskslist(commands, te);
		if (tc)
			proccoms(tc, te);
		free(input);
	}
	freeenv(te);
	return (0);
}

