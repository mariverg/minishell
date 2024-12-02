#include  "prechecker.h"

int command_cdcheck(t_command *c)
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
	////si el input es exit, cierra el programa
	if (ft_strncmp("exit", cc, 4) == 0)
	{
		exit(0);
	}
	return (0);
}


