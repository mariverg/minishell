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

int getequalposplus(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if(c[i] == '=')
			return (i + 1);
		else if (c[i] == ' ' || c[i] == 0)
			return (-1);
		i++;
	}
	return (-1);
}

char *getmienv(t_env *te, char *target)
{
	char *res;
	char *aux;
	int i;

	res = 0;
	if (*target == 0 || *target == ' ')
	{
		return(ft_strdup("$"));
	}
	if (ft_strncmp(target, "?", 1) == 0)
		return(ft_itoa(te->lastreturn));
	i = getmienvindex(te, target);
	if (i == -1)
		return (0);
	aux = ft_strdup(te->env[i]);
	i = getequalposplus(aux);
	if (i > 0)
		res = ft_substr(aux, i, ft_strlen(aux) - i);
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
