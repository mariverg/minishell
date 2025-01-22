#include "../minishell.h"

int errormsg(char *msg, char *info)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (info)
		write(STDERR_FILENO, info, ft_strlen(info));
	return (0);
}

int switchexit(int i, t_env *te, char *info)
{
	te->lastreturn = i;
	if (info)
		write(STDERR_FILENO, info, ft_strlen(info));
	return (0);
}

int exitrtrn(int i, t_env *te, char *msg, char *info)
{
	errormsg(msg, 0);
	switchexit(i, te, info);
	return (0);
}