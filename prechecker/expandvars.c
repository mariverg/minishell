#include  "prechecker.h"

/// en concreto los caracteres que pueden formar parte de la variable
int charforvar(char c)
{
	if (ft_isalnum(c) || c == '?' || c == '_')
	{
		return (1);
	}
	return (0);
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
	// printf("ha extraido de %s el valor %s\n", varname, res);
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
	int swich;

	res = 0;
	piece = ft_lstnew(0);
	swich = 1;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
		{
			if (swich)
				swich = 0;
			else
				swich = 1;
		}
		if (c[i] == '$' && swich)
		{
			slot = ft_substr(c, 0, i);
			ft_lstadd_back(&piece, ft_lstnew(slot));
			slot = extractvar(te, &c[i]);
			ft_lstadd_back(&piece, ft_lstnew(slot));
			c = c + i + 1;
			while(charforvar(*c))
				c++;
			i = 0;
		}
		i++;
	}
	slot = ft_strdup(c);
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