#include "envbuilder.h"


/// en este file estan todas las funciones usadas para el manejo de la variable struct t_env que almacena el entorno, por el momento solo contiene el estado de return y las variables de getenv(), no se si requerira mas. las funciones basicamente manejan las variables de entorno, las modifican y consultan
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

char *setmienv(t_env *te, char *target, char *newenvvar)
{
	char *res;
	char *aux;
	int i;
	int objetivo;
	char **base = te->env;
	res = 0;
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
	return (res);
}

void actualicepwd(t_env *te)
{
	char buff[256];
	// buff = getcwd(buff,256);
	setmienv(te, "PWD", getcwd(buff,256));
}

char *isexec(char **paths, char *target)
{
	struct stat mistat;
	int i;
	char *res;
	char *tmp;

	i = stat(target, &mistat);
	if (i == 0)
	{
		// printf("acerto con %s\n", target);
		return (ft_strdup(target));
	}
	while(*paths)
	{
		tmp = ft_strjoin("/", target);
		res = ft_strjoin(*paths, tmp);
		/// aqui res vale la ruta completa a testeas
		free(tmp);
		i = stat(res, &mistat);
		if (i == 0)
		{
			// printf("acerto con %s\n", res);
			return (res);
		}
		else
		{
			// printf("fallo con %s\n", res);
			free(res);
		}
		paths++;
	}
	printf("%s: command not found\n", target);
	return (0);
}

/// esta funcion organiza y trabaja con las superiores para comprobar si la cadena es ejecutable, devuelve la ruta coompleta de el ejecutable si lo es, o 0 si no
char *execinenv(t_env *te, char *target)
{
	char *mipath = getmienv(te, "PATH");
	char *aux = mipath; 
	// printf("mipath es %s\n", mipath);
	mipath = ft_substr(mipath, 5, ft_strlen(mipath) - 5);
	free(aux);
	// printf("mipath es %s\n", mipath);
	char **mispaths = ft_split(mipath, ':');
	free(mipath);

	char *torun = isexec(mispaths, target);
	
	return (torun);
}