#include "envbuilder.h"

int	returnerror(t_env *te, char *c)
{
	write(STDERR_FILENO, " not a valid identifier\n", 24);
	switchexit(1, te, 0);
	return (0);
}

int	findoperator(char *c)
{
	int	i;
	int	hasalpha;

	i = 0;
	hasalpha = 0;
	while (c[i])
	{
		if (ft_isalpha(c[i]))
			hasalpha = 1;
		if (c[i] == '=')
		{
			if (i > 0)
				return (i);
			else
				return (-1);
		}
		else if (c[i] == '+' && c[i + 1] == '=')
			break ;
		else if (c[i] == '-' || c[i] == '+')
			return (-1);
		i++;
	}
	if (hasalpha)
		return (i);
	return (-1);
}

int	addstrenv(t_env *te, char *c)
{
	char	*piece[2];
	int		i;

	i = findoperator(c);
	if (i == -1)
		return (returnerror(te, c));
	piece[0] = ft_substr(c, 0, i);
	c = c + i;
	if (*c == '+')
	{
		piece[1] = ft_substr(c, 2, ft_strlen(c) - 2);
		summienv (te, piece[0], piece[1]);
		free(piece[1]);
	}
	else if (*c == '=')
	{
		piece[1] = ft_substr(c, 1, ft_strlen(c) - 1);
		addmienv (te, piece[0], piece[1]);
		free(piece[1]);
	}
	else
		addmienv (te, piece[0], 0);
	free(piece[0]);
	return (0);
}
