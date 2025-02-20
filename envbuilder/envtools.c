/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:10:03 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:10:07 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envbuilder.h"

char	*targetspaced(char *c)
{
	char	*res;
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] == ' ' || c[i] == '\"' || c[i] == '\'' || c[i] == '|')
			break ;
		i++;
	}
	res = ft_substr(c, 0, i);
	return (res);
}

int	addmienv(t_env *te, char *target, char *value)
{
	int		newsize;
	char	**newenv;
	char	*aux;
	int		index;

	index = getmienvindex(te, target);
	if (index >= 0)
		return (setmienv(te, target, value));
	newsize = strxsize(te->env) + 1;
	newenv = malloc(sizeof(char *) * (newsize + 1));
	if (!newenv)
		return (0);
	newenv[newsize] = 0;
	newsize--;
	aux = ft_strjoin(target, "=");
	newenv[newsize] = ft_strjoin(aux, value);
	free(aux);
	while (newsize > 0)
	{
		newsize--;
		newenv[newsize] = te->env[newsize];
	}
	free(te->env);
	te->env = newenv;
	return (0);
}

int	plusmienv(t_env *te, char *target, char *newenvvar)
{
	char	*aux;
	int		objetivo;

	objetivo = getmienvindex(te, target);
	aux = te->env[objetivo];
	te->env[objetivo] = ft_strjoin(te->env[objetivo], newenvvar);
	free(aux);
	return (0);
}

int	summienv(t_env *te, char *target, char *value)
{
	int		newsize;
	char	**newenv;
	char	*aux;
	int		index;

	index = getmienvindex(te, target);
	if (index >= 0)
		plusmienv(te, target, value);
	else
		addmienv(te, target, value);
	return (0);
}
