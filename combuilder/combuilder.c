#include "../minishell.h"

////genera el t_com que usara forker para havecer las ejecuciones y pipes
t_com *newcom(char *c, char **cc, t_env *env)
{
	t_com *res;

	res = malloc(sizeof(t_com));
	res->c = c;
	res->cc = cc;
	res->env = env;
	res->operator = 0;
	res->in = 0;
	res->out = 0;
	res->next = 0;

	return (res);
}

int builtins(t_command *tc)
{
	char *c = tc->args[0];
	if (ft_strncmp("echo", c, 2) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("env", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("export", c, 4) == 0)
	{
		return (12);
	}
	else if (ft_strncmp("cd", c, 4) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("unset", c, 4) == 0)
	{
		return (21);
	}
	else if (ft_strncmp("exit", c, 4) == 0)
	{
		return (21);
	}
	return (0);
}

t_com *lastcom(t_com *tc)
{
	while(tc->next)
		tc = tc->next;
	return(tc);
}

/// saca el infile de texto, que pondre al inicio de la lista de t_com
t_com *extractin(t_command *tc, t_env *te)
{
	t_com *res;

	res = 0;
	while(tc)
	{
		if (tc->infile)
		{
			res = newcom(tc->infile, 0, te);
			if (tc->in_type == 0)
				res->operator = 2;
			else
				res->operator = 4;
		}
		tc = tc->next;
	}
	return (res);
}

/// y el out que ira al final
t_com *extractout(t_command *tc, t_env *te)
{
	t_com *res;
	
	res = 0;
	while(tc)
	{
		if (tc->outfile)
		{
			res = newcom(tc->outfile, 0, te);
			if (tc->out_type == 0)
				res->operator = 1;
			else 
				res->operator = 3;
		}
		tc = tc->next;
	}
	return (res);
}

////calcula los tcoms primero in, luego todos los ejecutables, y finalmente si existe out
t_com *getcomslist(t_command *tc, t_env *te)
{
	int i = 0;
	t_com *res;
	t_com *copy;
	char *c;
	int miport = 0;
	t_command *tcc;
	
	tcc = tc;
	res = newcom(0,0,0);

	lastcom(res)->next = extractin(tc, te);

	while(tc)
	{
		i = builtins(tc);
		if (i)
		{
			///// i 12 opera en fork, i 21 ha de operar en el proceso principal
			lastcom(res)->next = newcom(tc->args[0], tc->args, te);
			lastcom(res)->operator = i;
		}
		else
		{
			c = execinenv(te, tc->args[0]);
			if (c)
			{
				lastcom(res)->next = newcom(c, tc->args, te);
				lastcom(res)->operator = 11;
			}
			else
			{
				///// SI ha llegado aqui no es builtin ni ejecuyable ni en path ni acceso. es command not found
				printf("%s: command not found\n", tc->args[0]);
				te->lastreturn = 127;
				return(0);
			}
		}
		tc = tc->next;
	}
	lastcom(res)->next = extractout(tcc, te);
	copy = res;
	res = res->next;
	free(copy);
	return (res);
}