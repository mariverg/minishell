
#include <stdio.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "libs/libtxttools.h"

///// hay que mirar la funcion de parser a la que le puse la libreria
///// si empieza con |  > < segmentation fault

void printcmmm(t_command *current)
{
	int i;

	while (current)
    {
		i = 0;
		while(current->args[i])
		{
			printf("El arg %i vale %s\n", i, current->args[i]);	
			i++;
		}
		printf("infile %s\n", current->infile);
		printf("outfile %s\n", current->outfile);
		printf("in_type %i\n", current->in_type);
		printf("out_type %i\n", current->out_type);	
        current = current->next;
    }
}

char **mipaths(char **env)
{
	int mispaths = findstrrow(env, "PATH");
	char *pathsfiltrados = trimstr(env[mispaths], 5, 0);
	char **allpaths = strdisolve(pathsfiltrados,":");
	free(pathsfiltrados);
	return(allpaths);
}

char *runnable(char *target, char **env)
{
	struct stat mistat;
	char *totest;
	char *ttarget = sumstrs("/", target);
	char **allpaths = mipaths(env);
	int willrun = stat(target, &mistat);
	if (willrun == 0)
		return (target);
	while(*allpaths)
	{
		totest = sumstrs(*allpaths, ttarget);
		willrun = stat(totest, &mistat);
		if (willrun == 0)
			return (totest);
		allpaths++;
	}
	printf("comando %s no reconocido\n", target);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_entorn	mientorn;
	char		*input;
    t_command	*commands;
    int			i;
	int			miport;
	char		*c;
	t_comand	*uncomando;

	mientorn.env = env;
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
			// printcmmm(commands);
			commands = commands->next;
		}
		
	}
    /*while (1)
	{
		input = readline("C>");
		commands = parse(input);
		if (commands)
		{
			c = runnable(commands->args[0], mientorn.env);
			if (c)
			{
				t_comand *uncomando = newcom(c, commands->args, mientorn.env);
				forkea(uncomando, 0, &mientorn);
			}
			printcmmm(commands);
		}
		else
		{
			printf("nada que hacer");
		}
	}*/
	return (0);
}
