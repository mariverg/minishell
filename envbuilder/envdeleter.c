#include "envbuilder.h"

int	deleterow(t_env *te, char **newenv, int delindex)
{
	int		i;
	char	**oldenv;

	oldenv = te->env;
	i = 0;
	while (*oldenv)
	{
		if (i == delindex)
		{
			free(*oldenv);
			delindex--;
		}
		else
		{
			newenv[i] = *oldenv;
			i++;
		}
		oldenv++;
	}
	newenv[i] = 0;
	free(te->env);
	te->env = newenv;
	return (0);
}

int	delmienv(t_env *te, char *target)
{
	int		i;
	char	**newenv;

	if (!target)
		return (1);
	i = getmienvindex(te, target);
	if (i == -1)
		return (1);
	newenv = malloc(sizeof(char *) * strxsize(te->env));
	deleterow(te, newenv, i);
	return (0);
}
