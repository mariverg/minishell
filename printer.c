
#include <stdio.h>

#include "minishell.h"

////funciones de utilidad para consultar datos durante los tests, en principio no estaran en la version final
void prntstrs(char **c)
{
	while(*c)
	{
		printf("%s\n",*c);
		c++;
	}
}

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

