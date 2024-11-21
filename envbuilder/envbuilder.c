#include "../minishell.h"
#include "../libs/libft/libft.h"

#include <stdio.h>
#include <sys/stat.h>

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
		// printf("%s\n", *env);
		env++;
		i++;
	}
	res->env[i] = 0;
	return (res);
}

char *getenvvar(t_env *te, char *target)
{
	char *res;
	char **base = te->env;
	while(*base)
	{
		if (!ft_strncmp(*base, target, ft_strlen(target)))
		{
			// printf("\nuna variable acierta\n %s\n\n", *base);
			return(ft_strdup(*base));
		}
		else
		{
			// printf("una variable falla\n %s\n", *base);
		}
		base ++;
	}
	return (res);
}

char *isexec(char **paths, char *target)
{
	struct stat mistat;
	int i;
	char *res;
	char *tmp;


	while(*paths)
	{
		res = ft_strjoin("/", target);
		res = ft_strjoin(*paths, res);
		i = stat(res, &mistat);
		if (i == 0)
		{
			printf("acerto con %s\n", res);
			return (res);
		}
		else
		{
			printf("fallo con %s\n", res);
		}
		paths++;
	}
	printf("noencontro ningun ejecutable con %s\n", target);
	return (0);
}

char *execinenv(t_env *te, char *target)
{
	char *mipath = getenvvar(te, "PATH");
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