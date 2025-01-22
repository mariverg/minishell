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

//// devuelve el indice de una varialbe de entorno si existe, si no -1;
int getmienvindex(t_env *te, char *target)
{
	int i;
	int j;
	char **c;

	i = 0;
	j = -1;
	c = te->env;
	target = ft_strjoin(target,"=");
	while(c[i])
	{
		if (!ft_strncmp(c[i], target, ft_strlen(target)))
		{
			j = i;
		}
		i++;
	}
	free(target);
	return (j);
}

///anhade variable a entorno   NO ESTA EN USO, PROBABLEMENTE MIDA 1 MAS DE LO QUE DEBE O TAL VEZ NO
int addmienv (t_env *te, char *target, char *value)
{
	int newsize;
	char **newenv;
	char *aux;
	int index;

	index = getmienvindex(te, target);
	if (index >= 0)
		return (setmienv(te, target, value));
	newsize = strxsize(te->env) + 1;
	newenv = malloc(sizeof(char *) * (newsize + 1));
	newenv[newsize] = 0;
	newsize--;
	aux = ft_strjoin(target, "=");
	newenv[newsize] = ft_strjoin(aux, value);
	free(aux);
	while(newsize > 0)
	{
		newsize--;
		newenv[newsize] = te->env[newsize];
	}
	free(te->env);
	te->env = newenv;
	return(0);
}

///borra la varialbe de entorno
int delmienv(t_env *te, char *target)
{
	int i;
	int j;
	int newsize;
	char **newenv;
	char **oldenv;

	i = getmienvindex(te, target);
	if (i == -1)
		return (1);
	newsize = strxsize(te->env);
	newenv = malloc(sizeof(char *) * newsize);
	j = 0;
	oldenv = te->env;
	while(*oldenv)
	{
		if(i == j)
		{
			free(*oldenv);
			i = -1;
		} 
		else
		{
			newenv[j] = *oldenv;
			j++;
		}
		oldenv++;
	}
	newenv[j] = 0;
	free(te->env);
	te->env = newenv;
	return(0);
}

int addstrenv(t_env *te, char *c)
{
	char *ca;
	char *cb;
	int cut;

	cut = 0;
	if (ft_isdigit(c[0]) || c[0] == '=')
	{
		write(STDERR_FILENO, " not a valid identifier", 23);
		te->lastreturn = 1;
		return(0);
	}
	while (c[cut] != '=' && c[cut] != '\0')
	{
		// write(1, c + cut, 1);
		if(c[cut] == '-')
		{
			write(STDERR_FILENO, " not a valid identifier", 23);
			te->lastreturn = 1;
			return(0);
		}
		cut++;
	}
	ca = ft_substr(c, 0, cut);
	cb = ft_substr(c, cut + 1, (ft_strlen(c) - cut));
	addmienv (te, ca, cb);
	free(ca);
	if(cb)
		free(cb);
	return(0);
}

int daemonenv(t_task *tt)
{
	char *left;
	char *aux;
	char *c;
	int i;

	i = 1;
	c = 0;
	while (tt->cc[i])
	{
		aux = c;
		c = ft_strjoin(c, tt->cc[i]);
		free (aux);
		i++;
	}
	
	// while (tt->cc[i])
	// {
	// 	printf("gestionando %s\n", tt->cc[i]);
	// 	addstrenv(tt->env, tt->cc[i]);	
	// 	i++;
	// }
	addstrenv(tt->env, c);
	free(c);
	return (0);
}