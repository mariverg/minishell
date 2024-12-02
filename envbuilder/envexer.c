#include "envbuilder.h"


/// en este file estan todas las funciones usadas para el manejo de la variable struct t_env que almacena el entorno, por el momento solo contiene el estado de return y las variables de getenv(), no se si requerira mas. las funciones basicamente manejan las variables de entorno, las modifican y consultan

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