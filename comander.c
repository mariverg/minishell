#include <stdlib.h>

#include "minishell.h"

////genera el t_com que usara forker para havecer las ejecuciones y pipes
t_com *newcom(char *c, char **cc, char **env)
{
	t_com *res;

	res = malloc(sizeof(t_com));
	res->c = c;
	res->cc = cc;
	res->env = env;
	res->operator = 0;
	res->in = 0;
	res->out = 0;
	res->next = 0;

	return (res);
}
