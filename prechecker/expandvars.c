/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:11:53 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:11:55 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "prechecker.h"

/// en concreto los caracteres que pueden formar parte de la variable
int charforvar(char c)
{
	if (ft_isalnum(c) || c == '?' || c == '_')
	{
		return (1);
	}
	// if (ft_isalnum(c) || c == '_')
	// {
	// 	return (1);
	// }
	return (0);
}

int coutexpandalbe(char *c)
{
	int res;

	res = 1;
	if (c[1] == '?')
		return (2);
	while(charforvar(c[res]))
	{
		res++;
	}
	return(res);
}

char *extractvar(t_env *te, char *c)
{
	char *res;
	char *varname;
	int i;

	i = 1;
	while (charforvar(c[i]))
	{
		i++;
	}
	varname = ft_substr(c, 0, i);
	res = getmienv(te, (varname + 1));
	free(varname);
	
	return (res);
}

///recibe el input del user y lo transforma en una cadena expandida donde los $variables han sido sustituidos por su valor o borrados si no tienen valor
char *expanddollars(t_env *te, char *c)
{
	t_list *piece;
	t_list *aux;
	char *res;
	char *slot;
	int i;
	int scoma;
	int dcoma;

	res = 0;
	piece = ft_lstnew(0);
	scoma = -1;
	dcoma = -1;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'' && dcoma == -1)
			scoma = -scoma;
		if (c[i] == '\"' && scoma == -1)
			dcoma = -dcoma;
		if (c[i] == '$' && scoma == -1)
		{
			slot = ft_substr(c, 0, i);
			if (slot)
				ft_lstadd_back(&piece, ft_lstnew(slot));
			slot = extractvar(te, &c[i]);
			if (slot)
				ft_lstadd_back(&piece, ft_lstnew(slot));
			c = c + i + coutexpandalbe(c + i);
			// c = c + i + 1;
			// while(charforvar(*c))
			// 	c++;
			i = 0;
		}
		else
		{
			i++;
		}
		
	}
	slot = ft_strdup(c);
	if (slot)
		ft_lstadd_back(&piece, ft_lstnew(slot));
	while(piece)
	{
		aux = piece;
		if (piece->content)
		{
			slot = res;
			res = ft_strjoin(res, piece->content);
			free(piece->content);
			free(slot);
		}
		piece = piece->next;
		free(aux);
	}
	return (res);
}
