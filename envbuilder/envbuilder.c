#include "envbuilder.h"


/// en este file estan todas las funciones usadas para el manejo de la variable struct t_env que almacena el entorno, por el momento solo contiene el estado de return y las variables de getenv(), no se si requerira mas. las funciones basicamente manejan las variables de entorno, las modifican y consultan

t_env *newenv(char **env)
{
	t_env *res;
	res =  malloc(sizeof(t_env));
	res->lastreturn = 0;
	res->env = malloc(sizeof(char *) * (strxsize(env) + 1));
	int i = 0;
	while (*env)
	{
		res->env[i] = ft_strdup(*env);
		env++;
		i++;
	}
	res->env[i] = 0;
	return (res);
}

///devuelve el contenido de la variable de entorno target en el entorno te
char *getmienv(t_env *te, char *target)
{
	char *res;
	char *aux;
	char **base = te->env;
	res = 0;
	aux = 0;
	while(*base)
	{
		if (!ft_strncmp(*base, target, ft_strlen(target)))
			aux = ft_strdup(*base);
		base ++;
	}
	if (aux)
	{
		res = ft_substr(aux, ft_strlen(target) + 1, ft_strlen(aux) - ft_strlen(target) - 1);
		free(aux);
	}
	return (res);
}

////modifica el valor de una variable, principalmente usada actualmente para modificar target = "PWD", pero vale con todas
void setmienv(t_env *te, char *target, char *newenvvar)
{
	char *aux;
	int i;
	int objetivo;
	char **base = te->env;
	aux = 0;
	i = 0;
	objetivo = -1;

	while(te->env[i])
	{
		if (!ft_strncmp(te->env[i], target, ft_strlen(target)))
		{
			objetivo = i;
			break;
		}
		i ++;
	}
	if (objetivo >= 0)
	{
		aux = ft_strjoin(target, "=");
		newenvvar = ft_strjoin(aux, newenvvar);
		free(aux);
		free(te->env[objetivo]);
		te->env[objetivo] = newenvvar;
	}
}

////autopmatizacion de setmienv para que guarde el pwd devuelto por getcwd, que es el correcto en mis tests
void actualicepwd(t_env *te)
{
	char buff[256];
	// buff = getcwd(buff,256);
	setmienv(te, "PWD", getcwd(buff,256));
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