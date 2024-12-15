#include "minishell.h"

void freestrs(char **c)
{
	int i;

	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}