/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envbuilder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:09:00 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:09:03 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envbuilder.h"

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

char *getmienv(t_env *te, char *target)
{
	char *res;
	char *aux;
	int i;

	res = 0;
	//// parser elimina $
	// printf("checking  -%s-\n", target);
	if (*target == 0 || *target == ' ')
	{
		// printf("devolviendo $\n");
		return(ft_strdup("$"));
	}
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

int actualicepwd(t_env *te)
{
	char buff[256];
	char *toerase;
	int i;

	setmienv(te, "OLDPWD", getmienv(te, "PWD"));
	setmienv(te, "PWD", getcwd(buff,256));
	return (0);
}

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
