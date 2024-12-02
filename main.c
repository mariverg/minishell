
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
		if (command_cdcheck(commands) == 1)
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
	///libera la memoria de entorno, pero aun hay mucha que limpiar dentro de algunas funciones
	freeenv(mientorno);
	return (0);
}


/*
int main(int argc, char **argv, char **env)
{
	t_env		*mientorno;
	char		*input;
    t_command	*commands;
    int			i;
	int			miport;
	char		*c;
	t_com	*uncomando;
	char *directorio;

	/// bloquea ctrl + c y ctrl + z/ para salir se usa exit, definida arriba en int command_precheck(t_command *c)
	blockaction();
	/// crea el t_env que se mueve entre procesos con los datos de entorno y los actualiza
	mientorno = newenv(env);

	
	//// tests de sumar y restar env variables
	addmienv(mientorno, "pru", "esto es una pru");
	printf("la var vale %s\n",getmienv(mientorno, "PATH"));
	printf("la var vale %s\n",getmienv(mientorno, "pru"));
	delmienv(mientorno, "pru");
	printf("la var vale %s\n",getmienv(mientorno, "PATH"));
	printf("la var vale %s\n",getmienv(mientorno, "pru"));
	addmienv(mientorno, "pru", "esto es una pru 2");
	printf("la var vale %s\n",getmienv(mientorno, "PATH"));
	printf("la var vale %s\n",getmienv(mientorno, "pru"));
	
	while (1)
	{
		//// actualiza en t_env el PWD para imprimirlo en la linea
		actualicepwd(mientorno);
		char *directorio = getmienv(mientorno, "PWD");
		//// guarda un int para pasar como puerto entre procesos de ser necesario
		miport = 0;
		////imprime la linea C/desktop> con la ruta PWD
		printf("%s",directorio);
		input = readline(">");
		////aqui activa el parser. Si el 'input' tiene algun valor parser se poblara y la funcion continuara dentro del proximo while
		commands = parse(input);
		///lo primero que hace es buscar palabras clave, actulmente cd y exit
		///esta operacion deberia estar en otro lugar probablemente.... pero bueno, ahoraesta auqui
		if (command_cdcheck(commands) == 1)
		{
			// printf("palabra clave\n");
			continue;
		}
		t_com *miscomandos = getcomslist(commands, mientorno);
		printcmmm(commands);
		continue;
		///ejecurata los comandos, en principio es uno por operacion
		while (commands)
		{
			// printcmmm(commands);
			// break;
			///aqui c toma el valor retornado de execinenv (ejecutable in enviroment) que es 0 si no es ejecutable, o la ruta complata si lo es por tanto...
			c = execinenv(mientorno, commands->args[0]);
			/// ... si c vale algo hay que ejecutarlo
			if (c)
			{
				///lo prepara para la ejecucion
				uncomando = newcom(c, commands->args, mientorno->env);
				//si hay next (se ejecutara otra operacion tras esta) significa que tiene que abrir el puerto
				if (commands->next)
					uncomando->out = 1;
				/// si miport no vale 0 es por que hay datos que leer por lo que prepara el t_com para recibir datos cuando se ejecute
				if (miport)
					uncomando->in = 1;
				/// finalmente lanza forkea, que devuelve la direccion del puerto de salida para la entrada de la proxima tarea
				miport = forkea(uncomando, miport, mientorno);
			}
			commands = commands->next;
		}
		/////esto es provisional, la organizacion es compleja e ineficiente ademas de dificil de expandir, pero en condiciones ideales funciona
		
	}
	return (0);
}
*/