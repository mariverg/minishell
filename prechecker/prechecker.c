#include  "prechecker.h"

int comparealpha(char *ca, char *cb)
{
	if(!ca && cb)
		return (1);
	if(ca && !cb)
		return (-1);
	while(*ca || *cb)
	{
		if (*ca < *cb)
			return (1);
		if (*ca > *cb)
			return (-1);
		if (*ca == '=' && *cb == '=')
			return (0);
		ca++;
		cb++;
	}
	return (0);
}
char *firstafter(t_env *te, char *c)
{
	int i;
	int lucky;
	int lines;
	char *res;

	lines = strxsize(te->env); 
	i = 0;
	res = "~~~";
	while (i < lines)
	{
		if (comparealpha(te->env[i], res) == 1 && comparealpha(te->env[i], c) == -1)
			res = te->env[i];
		i++;
	}
	return (res);
}
int printalphabetical(t_env *te, char *toprint, char *max)
{
	int i;
	int lucky;
	int lines;
	char *c;

	c = 0;
	lines = strxsize(te->env); 
	i = 0;
	while (i < lines)
	{
		c = firstafter(te,c);
		printline("declare -x ");
		printline(c);
		printline("\n");
		i++;
	}
	return (0);
}

int command_cdcheck(t_command *c, t_env *te)
{
	if (!c)
		return(1);
	char *cc = c->args[0];
	////si el input es cd, hace el cambio de dir
	if (ft_strncmp("cd", cc, 2) == 0)
	{
		int i = chdir(c->args[1]);
		return (1);
	}
	if (ft_strncmp("env", cc, 4) == 0)
	{
		prntstrs(te->env);
		return(1);
	}
	if (ft_strncmp("export", cc, 4) == 0)
	{
		printalphabetical(te, 0, 0);
		return(1);
	}
	if (ft_strncmp("echo", cc, 4) == 0)
	{
		int i = 1;
		while(c->args[i])
		{
			if (i > 1)
				printline(" ");
			printline(c->args[i]);
			// printf("%s", c->args[i]);
			i++;
		}
		printline("\n");
		return(1);
	}
	////si el input es exit, cierra el programa
	if (ft_strncmp("exit", cc, 4) == 0)
	{
		if(c->args[1])
			exit(ft_atoi(c->args[1]));
		exit(0);
	}
	return (0);
}


