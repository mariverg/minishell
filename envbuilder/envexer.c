/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:09:45 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:09:49 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envbuilder.h"

char *statcero(char *target, struct stat *mistat)
{
	if (S_ISREG(mistat->st_mode)) 
		return (ft_strdup(target));
	else if (S_ISDIR(mistat->st_mode))
	{
		printf("%s: is a directory\n", target);
		return(0);
	}
	else if (S_ISLNK(mistat->st_mode)) 
	{
		printf("Es un link.\n");
		return(0);
	}
	return (0);
}

char *isexec(t_env *te, char **paths, char *target)
{
	struct stat mistat;
	int i;
	char *res;
	char *tmp;

	i = stat(target, &mistat);
	if (i == 0)
		return (statcero(target, &mistat));
	if (paths == 0)
		return (0);
	while(*paths)
	{
		tmp = ft_strjoin("/", target);
		res = ft_strjoin(*paths, tmp);
		free(tmp);
		i = stat(res, &mistat);
		if (i == 0)
			return (res);
		else
			free(res);
		paths++;
	}
	// printf("%s: command not found\n", target);
	// te->lastreturn = 127;
	return (0);
}

char *execinenv(t_env *te, char *target)
{
	char *mipath = getmienv(te, "PATH");
	char *torun;

	torun = 0;
	if(mipath == 0)
	{
		torun = isexec(te, 0, target);
	} 
	else 
	{
		char *aux = mipath; 
		mipath = ft_substr(mipath, 5, ft_strlen(mipath) - 5);
		free(aux);
		char **mispaths = ft_split(mipath, ':');
		free(mipath);
		torun = isexec(te, mispaths, target);
		freestrs(mispaths);
	}
	return (torun);
}
