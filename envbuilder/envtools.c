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
	target = ft_strjoin(target,"=");
	while(c[i])
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

///anhade variable a entorno
int addmienv (t_env *te, char *target, char *value)
{
	int newsize;
	char **newenv;
	char *aux;
	int index;

	index = getmienvindex(te, target);
	if (index >= 0)
		return (setmienv(te, target, value));
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
	newsize = strxsize(te->env);
	newenv = malloc(sizeof(char *) * newsize);
	j = 0;
	oldenv = te->env;
	while(*oldenv)
	{
		if(i == j)
		{
			free(*oldenv);
			i = -1;
		} 
		else
		{
			newenv[j] = *oldenv;
			j++;
		}
		oldenv++;
	}
	newenv[j] = 0;
	free(te->env);
	te->env = newenv;
	return(0);
}

int delmienv2(t_env *te, char *target)
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
		//// el j++ debe entrar dentro del if
		if (i != j)
		{
			newenv[j] = ft_strdup("yj");
			// newenv[j] = *oldenv;
			j++;
			i = -1;
		}
		oldenv++;
	}
	// printf("borrado finalizado\n");
	prntstrs(newenv);
	// printf("termina impresion\n");
	/// esta linea no esta testeada
	// free(te->env[i]);
	// free(te->env);
	// te->env = newenv;
	// printf("nuevo env asignado\n");
	return(0);
}