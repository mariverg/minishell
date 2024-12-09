
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "libs/libft/libft.h"

/// esta funcion busca la variable de entorno pwd y la imprime en pantalla antes del >
void prntpwdline(t_env *te)
{
	char	*directorio;
	
	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	printf("%s",directorio);
	free (directorio);
}

///que decir de main...
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

	////// esta linea para la gestion de los signals ctrl + c....
	blockaction();
	/////fundamental, puebla la variable mientorno con los contenidos del argenv
	mientorno = newenv(argenv);
	// prntstrs(mientorno->env);
	while (1)
	{
		////imprime la limea con la direccion
		prntpwdline(mientorno);
		input = readline(">");
		////al recibir  input verifica que haya contenido, si no lo hay es por un ctrld que sale de la funcion libera mem y cierra programa
		if (!input)
			break;
		///expanddollars coge el texto y tranforma las $PWD $ENV y de mas, en su valor segun este asignado en en mientorno->env
		input = expanddollars(mientorno, input);
		/// el parseo se produce despues del cambio, asi una variable con acciones se ejecutara ej mivar="ls"
		commands = parse(input);
		///	este es un pequenho check que mira si hay exit o cd para cambio dir o salir del progrma
		if (command_cdcheck(commands, mientorno) == 1)
		{
			continue;
		}
		miport = 0;
		////esta funcion coge los t_commands y los separa y ordena para ejecuciones sucesivas y ordenada, el puntoro miscomandos apunta a una cadena de t_coms terminada en 0, y los ejecuta todos
		t_com *miscomandos = getcomslist(commands, mientorno);
		while (miscomandos)
		{
			if (miscomandos->next)
				miscomandos->out = 1;
			if (miport)
				miscomandos->in = 1;
			miport = forkea(miscomandos, miport, mientorno);
			miscomandos = miscomandos->next;
		}
	}
	freeenv(mientorno);
	return (0);
}

