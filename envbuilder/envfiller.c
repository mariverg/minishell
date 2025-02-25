/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envfiller.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:18:20 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:18:20 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envbuilder.h"

void	updateshlvl(t_env *res)
{
	int		level;
	char	*aux;

	aux = getmienv(res, "SHLVL");
	if (!aux)
		return ;
	level = ft_atoi(aux) + 1;
	free(aux);
	aux = ft_itoa(level);
	setmienv(res, "SHLVL", aux);
	free(aux);
}

void	fillenv(t_env *res, char **env)
{
	int		i;

	if (!env)
	{
		res->env = malloc(sizeof(char *));
		res->env[0] = 0;
		return ;
	}
	res->env = malloc(sizeof(char *) * (strxsize(env) + 1));
	i = 0;
	while (*env)
	{
		res->env[i] = ft_strdup(*env);
		env++;
		i++;
	}
	res->env[i] = 0;
}
