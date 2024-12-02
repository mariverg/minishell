#include "envbuilder.h"

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

//// devuelve el indice de una varialbe de entorno si existe, si no -1;
int getmienvindex(t_env *te, char *target)
{
	int i;
	int j;
	char **c;

	i = 0;
	j = -1;
	c = te->env;
	while(c[i])
	{
		if (!ft_strncmp(c[i], target, ft_strlen(target)))
		{
			j = i;
		}
		i++;
	}
	return (j);
}

///anhade variable a entorno
int addmienv (t_env *te, char *target, char *value)
{
	int newsize;
	char **newenv;
	char *aux;

	newsize = strxsize(te->env) + 1;
	newenv = malloc(sizeof(char *) * (newsize + 1));
	newenv[newsize] = 0;
	newsize--;
	aux = ft_strjoin(target, "=");
	newenv[newsize] = ft_strjoin(aux, value);
	free(aux);
	while(newsize > 0)
	{
		newsize--;
		newenv[newsize] = te->env[newsize];
	}
	free(te->env);
	te->env = newenv;
	return(0);
}

///borra la varialbe de entorno
int delmienv(t_env *te, char *target)
{
	int i;
	int j;
	int newsize;
	char **newenv;
	char **oldenv;

	i = getmienvindex(te, target);
	if (i == -1)
		return (1);
	newsize = strxsize(te->env) - 1;
	newenv = malloc(sizeof(char *) * (newsize + 1));
	newenv[newsize] = 0;
	j = 0;
	oldenv = te->env;
	while(*oldenv)
	{
		if (i != j)
			newenv[j] = *oldenv;
		j++;
		oldenv ++;
	}
	free(te->env);
	te->env = newenv;
	return(0);
}