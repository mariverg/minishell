#include "parseo.h"

int main(void)
{
    char *input = "echo \"Hello $USER\" | grep Hello > output.txt";
	input = "/mecho hola > como < estas";
    t_command *commands = parse(input);
    int i;
    // Procesar los comandos
    t_command *current = commands;
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
    
    // Liberar memoria
    free_commands(commands);
    return (0);
}