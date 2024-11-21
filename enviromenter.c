#include "minishell.h"
#include "libs/libft/libft.h"
// #include "libs/libtxttools/libtxttools.h"

int strxsize(char **c)
{
	int i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

t_env newenv(char **env)
{
	t_env res;
	int i = 0;

	res.env = malloc(sizeof(char *) * (strxsize(env) + 1));
	while(res.env[i])
	{
		// res.env[i] = dupstr(env[i]);
		i++;
	}
	return (res);
}



char *migetenv(char *c, t_env *e)
{
	return (0);
}