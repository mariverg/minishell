#include "envbuilder.h"


/// en este file estan todas las funciones usadas para el manejo de la variable struct t_env que almacena el entorno, por el momento solo contiene el estado de return y las variables de getenv(), no se si requerira mas. las funciones basicamente manejan las variables de entorno, las modifican y consultan

t_env *newenv(char **env)
{
	t_env *res;
	char *aux;
	int level;
	int i;

	res =  malloc(sizeof(t_env));
	res->lastreturn = 0;
	res->env = malloc(sizeof(char *) * (strxsize(env) + 1));
	i = 0;
	while (*env)
	{
		res->env[i] = ft_strdup(*env);
		env++;
		i++;
	}
	res->env[i] = 0;
	aux = getmienv(res, "SHLVL");
	level = ft_atoi(aux) + 1;
	free(aux);
	aux = ft_itoa(level);
	setmienv(res, "SHLVL", aux);
	free(aux);
	return (res);
}

///devuelve el contenido de la variable de entorno target en el entorno te
char *getmienv(t_env *te, char *target)
{
	char *res;
	char *aux;
	int i;

	if (ft_strncmp(target, "?", 1) == 0)
		return(ft_itoa(te->lastreturn));
	i = getmienvindex(te, target);
	if (i == -1)
		return (0);
	aux = ft_strdup(te->env[i]);
	res = ft_substr(aux, ft_strlen(target) + 1, ft_strlen(aux) - (ft_strlen(target) + 1));
	free(aux);
	return (res);
}

////modifica el valor de una variable, principalmente usada actualmente para modificar target = "PWD", pero vale con todas
int setmienv(t_env *te, char *target, char *newenvvar)
{
	char *aux;
	int i;
	int objetivo;

	aux = 0;
	i = 0;
	objetivo = getmienvindex(te, target);
	if (objetivo >= 0)
	{
		aux = ft_strjoin(target, "=");
		newenvvar = ft_strjoin(aux, newenvvar);
		free(aux);
		free(te->env[objetivo]);
		te->env[objetivo] = newenvvar;
	}
	return (0);
}

////autopmatizacion de setmienv para que guarde el pwd devuelto por getcwd, que es el correcto en mis tests
int actualicepwd(t_env *te)
{
	char buff[256];
	char *toerase;
	int i;

	setmienv(te, "OLDPWD", getmienv(te, "PWD"));
	setmienv(te, "PWD", getcwd(buff,256));
	return (0);
}

///simple liberacion de memoria a saco, si encuentra dato lo borra
void freeenv(t_env *te)
{
	int i;

	i = 0;
	while(te->env[i])
	{
		free(te->env[i]);
		i++;
	}
	free(te->env);
	free(te);
}