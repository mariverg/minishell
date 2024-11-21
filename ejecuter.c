#include <sys/stat.h>

#include "minishell.h"
// #include "libs/libtxttools/libtxttools.h"
#include "libs/libft/libft.h"

void execver(t_com *tc)
{
	execve(tc->c,tc->cc,tc->env);
}

// char **mipaths(char **env)
// {
// 	int mispaths = findstrrow(env, "PATH");
// 	char *pathfiltrados = trimstr(env[mispaths], 5, 0);
// 	char *pathsfiltrados = trimstr(env[mispaths], 5, 0);
// 	char **allpaths = strdisolve(pathsfiltrados,":");
// 	free(pathsfiltrados);
// 	return(allpaths);
// }

char *runnable(char *target, char **env)
{
	//printf("entra en runnable con %s\n", target);
	struct stat mistat;
	char *totest;
	// char *ttarget = ft_strjoin("/", target);
	// char **allpaths = mipaths(env);
	
	int willrun = stat(target, &mistat);
	if (willrun == 0)
		return (target);
	/*while(*allpaths)
	{

		totest = sumstrs(*allpaths, ttarget);
		willrun = stat(totest, &mistat);
		// printf("comprueba con %s\n", totest);
		if (willrun == 0)
			return (totest);
		allpaths++;
	}*/
	// printf("comando %s no reconocido\n", target);
	return (0);
}

