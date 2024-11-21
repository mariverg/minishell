#include "minishell.h"
#include "libs/libtxttools.h"


t_env newenv(char **env)
{
	t_env res;
	int i = 0;

	res.env = malloc(sizeof(char *) * (strxsize(env) + 1));
	while(res.env[i])
	{
		res.env[i] = dupstr(env[i]);
		i++;
	}
	return (res);
}



char *migetenv(char *c, t_env *e)
{
	return (0);
}