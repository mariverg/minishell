
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
// #include "libs/libtxttools/libtxttools.h"
#include "libs/libft/libft.h"

///gestiona palabras clave, ahora exit y cd
int command_precheck(t_command *c)
{
	char *cc = c->args[0];
	if (ft_strncmp("cd", cc, 2) == 0)
	{
		int i = chdir(c->args[1]);
		return (0);
	}
	if (ft_strncmp("exit", cc, 4) == 0)
	{
		exit(0);
	}
	return (0);
}

///todo main es provisional
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
		///ejecurata los comandos, en principio es uno por operacion
		while (commands)
		{
			///lo primero que hace es buscar palabras clave, actulmente cd y exit
			///esta operacion deberia estar en otro lugar probablemente.... pero bueno, ahora esta auqui
			if (command_precheck(commands) == 1)
			{
				// printf("palabra clave\n");
				break;
			}
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
