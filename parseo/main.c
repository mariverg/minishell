#include "parseo.h"

int main(void)
{
    char *input;
    int i;
    // Procesar los comandos
    t_command *commands;
    t_command *current;
    while (1)
    {
		input = readline("Minishell> ");
		if (!ft_strncmp("exit", input))
			return (0);
		i = 0;
		commands = parse(input);
		current = commands;
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
    
    // Liberar memoria
    free_commands(commands);
    return (0);
}