#include "minishell.h"

int	chalpha(char *ca, char *cb)
{
	if (!ca && cb)
		return (1);
	if (ca && !cb)
		return (-1);
	while (*ca || *cb)
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

char	*firstafter(t_env *te, char *c)
{
	int		i;
	int		lines;
	char	*res;

	lines = strxsize(te->env);
	i = 0;
	res = "~~~";
	while (i < lines)
	{
		if (chalpha(te->env[i], res) == 1 && chalpha(te->env[i], c) == -1)
			res = te->env[i];
		i++;
	}
	return (res);
}

char	*fandcollapse(t_list *tl)
{
	char	*res;
	char	*caux;
	t_list	*laux;

	res = 0;
	while (tl)
	{
		laux = tl;
		caux = res;
		tl = tl->next;
		res = ft_strjoin(res, laux->content);
		if (caux)
			free(caux);
		if (laux->content)
			free(laux->content);
		free(laux);
	}
	return (res);
}

char	*addcomi(char *c)
{
	t_list	*tl;
	int		i;

	while (c[i] != 0 && c[i] != '=')
		i++;
	tl = ft_lstnew(ft_substr(c, 0, i + 1));
	ft_lstlast(tl)->next = ft_lstnew(ft_strdup("\""));
	ft_lstlast(tl)->next = ft_lstnew(ft_substr(c, i + 1, (ft_strlen(c) - i)));
	ft_lstlast(tl)->next = ft_lstnew(ft_strdup("\""));
	return (fandcollapse(tl));
}

int	printalphabetical(t_task *te, char *toprint, char *max)
{
	int		i;
	int		lines;
	char	*c;
	char	*mod;

	(void) toprint;
	(void) max;
	c = 0;
	lines = strxsize(te->env->env);
	i = 0;
	while (i < lines)
	{
		c = firstafter(te->env, c);
		printline("declare -x ", STDOUT_FILENO);
		mod = addcomi(c);
		printline(mod, STDOUT_FILENO);
		free (mod);
		printline("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
