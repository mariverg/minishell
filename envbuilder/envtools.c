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

int	addfromcut(t_env *te, char *c, int cut)
{
	char	*ca;
	char	*cb;

	ca = ft_substr(c, 0, cut);
	cb = ft_substr(c, cut + 1, (ft_strlen(c) - cut));
	addmienv (te, ca, cb);
	free(ca);
	if (cb)
		free(cb);
	return (0);
}

int	addstrenv(t_env *te, char *c)
{
	int		cut;

	cut = 0;
	if (ft_isdigit(c[0]) || c[0] == '=')
	{
		write(STDERR_FILENO, " not a valid identifier", 23);
		switchexit(1, te, 0);
		return (0);
	}
	while (c[cut] != '=' && c[cut] != '\0')
	{
		if (c[cut] == '-')
		{
			write(STDERR_FILENO, " not a valid identifier", 23);
			switchexit(1, te, 0);
			return (0);
		}
		cut++;
	}
	addfromcut(te, c, cut);
	return (0);
}
