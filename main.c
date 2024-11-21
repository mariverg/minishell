
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
// #include "libs/libtxttools/libtxttools.h"
#include "libs/libft/libft.h"

int main(int argc, char **argv, char **env)
{
	t_env		*mientorno;
	char		*input;
    t_command	*commands;
    int			i;
	int			miport;
	char		*c;
	t_com	*uncomando;

	// mientorn->env = env;
	mientorno = newenv(env);
	// char *cc = execinenv(mientorno, "ls");
	// printf("fin\n");
	// printf("el envvar vale %s\n", cc);
	// prntstrs(mientorn->env);
	// exit (0);
	while (1)
	{
		// newenv();
		miport = 0;
		input = readline("C>");
		commands = parse(input);
		while (commands)
		{
			// c = runnable(commands->args[0], mientorno->env);
			c = execinenv(mientorno, commands->args[0]);
			if (c)
			{
				uncomando = newcom(c, commands->args, mientorno->env);
				if (commands->next)
					uncomando->out = 1;
				if (miport)
					uncomando->in = 1;
				printf("va a ejecutar %s\n", c);
				miport = forkea(uncomando, miport, mientorno);
			}
			//printcmmm(commands);
			commands = commands->next;
		}
		
	}
	return (0);
}
