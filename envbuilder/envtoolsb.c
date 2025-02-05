#include "envbuilder.h"

int	strxsize(char **c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

int	getmienvindex(t_env *te, char *target)
{
	int		i;
	int		j;
	char	**c;
	char	*aux;

	i = 0;
	j = -1;
	c = te->env;
	aux = targetspaced(target);
	target = ft_strjoin(aux, "=");
	free(aux);
	while (c[i])
	{
		if (!ft_strncmp(c[i], target, ft_strlen(target)))
		{
			j = i;
		}
		i++;
	}
	free(target);
	return (j);
}

void	freeenv(t_env *te)
{
	int	i;

	i = 0;
	while (te->env[i])
	{
		free(te->env[i]);
		i++;
	}
	free(te->env);
	free(te);
}

int	daemonenv(t_task *tt)
{
	char	*aux;
	char	*c;
	int		i;

	i = 1;
	c = 0;
	while (tt->cc[i])
	{
		aux = c;
		c = ft_strjoin(c, tt->cc[i]);
		free (aux);
		i++;
	}
	addstrenv(tt->env, c);
	free(c);
	return (0);
}
