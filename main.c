
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "libs/libtxttools.h"
#include "parseo/libft/libft.h"

int main(int argc, char **argv, char **env)
{
	t_env		mientorn;
	char		*input;
    t_command	*commands;
    int			i;
	int			miport;
	char		*c;
	t_com	*uncomando;

	mientorn.env = env;
	// mientorn = newenv(env);
	// prntstrs(mientorn.env);
	// exit (0);
	while (1)
	{
		miport = 0;
		input = readline("C>");
		commands = parse(input);
		while (commands)
		{
			c = runnable(commands->args[0], mientorn.env);
			if (c)
			{
				uncomando = newcom(c, commands->args, mientorn.env);
				if (commands->next)
					uncomando->out = 1;
				if (miport)
					uncomando->in = 1;
				miport = forkea(uncomando, miport, &mientorn);
			}
			//printcmmm(commands);
			commands = commands->next;
		}
		
	}
	return (0);
}
