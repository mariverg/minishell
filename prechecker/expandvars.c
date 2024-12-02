#include  "prechecker.h"

/// devuelve el contenido tras $ para checkear si existe tal variable ej "$PATH sadasd" devuelve "PATH"
char *extractvar(t_env *te, char *c)
{
	char *res;
	char *varname;
	int i;

	i = 1;
	while (ft_isalnum(c[i]))
	{
		i++;
	}
	varname = ft_substr(c, 0, i);
	res = getmienv(te, (varname + 1));
	free(varname);
	// printf("la var vale %s\n", res);
	return (res);
}

///recibe el input del user y lo transforma en una cadena expandida donde los $variables han sido sustituidos por su valor o borrados si no tienen valor
char *expanddollars(t_env *te, char *c)
{
	t_list *trozo;
	char *res;
	char *prev;
	char *next;
	int i;
	int swich;

	res = "";
	trozo = ft_lstnew(0);
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
		else if (c[i] == '$')
		{
			prev = ft_substr(c, 0, i);
			ft_lstadd_back(&trozo, ft_lstnew(prev));
			next = extractvar(te, &c[i]);
			ft_lstadd_back(&trozo, ft_lstnew(next));
			c = c + i + 1;
			while(ft_isalnum(*c))
				c++;
			i = 0;
		}
		i++;
	}
	char *final = ft_strdup(c);
	ft_lstadd_back(&trozo, ft_lstnew(final));
	while(trozo)
	{
		if (trozo->content)
			res = ft_strjoin(res, trozo->content);
		trozo = trozo->next;
	}
	return (res);
}