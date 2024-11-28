#include "../minishell.h"
# include "../libs/libft/libft.h"

int command_cdcheck(t_command *c)
{
	char *cc = c->args[0];
	if (ft_strncmp("cd", cc, 2) == 0)
	{
		int i = chdir(c->args[1]);
		return (1);
	}
	if (ft_strncmp("exit", cc, 4) == 0)
	{
		exit(0);
	}
	return (0);
}


