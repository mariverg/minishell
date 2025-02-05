#include "prechecker.h"

int	cancontinue(char *c)
{
	if (!c)
		return (0);
	while (*c == ' ' || *c == '\t')
		c++;
	if (*c == 0)
		return (0);
	if (*c == '|')
		return (0);
	return (1);
}

int	validchar(char c)
{
	int		i;
	char	*taboos;

	if (c == 0)
		return (0);
	i = 0;
	taboos = " \"\'|<>";
	while (taboos[i])
	{
		if (taboos[i] == c)
			return (0);
		i++;
	}
	return (1);
}
