#include "../minishell.h"

//// cuenta comandos, ahora no la estoy usando, esta obsoleta
int numcoms(t_command *tc)
{
	t_command *tcopy;
	int numcoms;

	tcopy = tc;
	numcoms = 1;
	while (tcopy->next)
	{
		tcopy = tcopy->next;
		numcoms++;
	}
	if (tcopy->infile)
	{
		tc->infile = tcopy->infile;
		tc->in_type = tcopy->in_type;
		tcopy->infile = 0;
		numcoms++;
	}
	if (tcopy->outfile)
	{
		numcoms++;
	}	
	return(numcoms);
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
			res = newcom(tc->infile, 0, te->env);
			if (tc->in_type == 0)
				res->operator = 2;
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
			res = newcom(tc->outfile, 0, te->env);
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
	copy = res;

	copy->next = extractin(tc, te);
	if (copy->next)
		copy = copy->next;
	while(tc)
	{
		c = execinenv(te, tc->args[0]);
		if (c)
		{
			copy->next = newcom(c, tc->args, te->env);
			copy = copy->next;
		}
		tc = tc->next;
	}
	copy->next = extractout(tcc, te);
	copy = res;
	res = res->next;
	free(copy);
	return (res);
}