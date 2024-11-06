int strsize(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (*c)
	{
		c++;
		i++;
	}
	return (i);
}

int ischar(char c, char *ca)
{
	if (!ca)
		return (0);
	while(*ca)
	{
		if (*ca == c)
			return(1);
		ca++;
	}
	return(0);
}

int charpos(char *c, char *ca)
{
	int	i;

	if(!c || !ca)
		return (-1);
	i = 0;
	while(c[i])
	{
		if (ischar(c[i], ca))
			return (i);
		i++;
	}
	return (-1);
}

int charamount(char *c, char *ca)
{
	int	i;

	if(!c || !ca)
		return (-1);
	i = 0;
	while(*c)
	{
		if (ischar(*c, ca))
			i++;
		c++;
	}
	return (i);
}

int strscmp(char *orig, char *comparer)
{
	if (!orig || !comparer)
		return (0);
	while(*comparer)
	{
		if(*orig != *comparer)
			return (0);
		comparer++;
		orig++;
	}
	return (1);
}
