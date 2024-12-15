#include <sys/stat.h>

#include "../minishell.h"
// #include "libs/libtxttools/libtxttools.h"
// #include "libs/libft/libft.h"

///ejecuta la funcion execve
void execver(t_com *tc)
{
	execve(tc->c,tc->cc,tc->env->env);
}

int execbuiltin(t_com *tc)
{
	if (!tc)
		return(1);
	char *cc = tc->c;
	////si el input es cd, hace el cambio de dir
	if (ft_strncmp("cd", cc, 2) == 0)
	{
		int i = chdir(tc->cc[1]);
		return (1);
	}
	if (ft_strncmp("env", cc, 4) == 0)
	{
		prntstrs(tc->env->env);
		return(1);
	}
	if (ft_strncmp("export", cc, 4) == 0)
	{
		printalphabetical(tc->env, 0, 0);
		return(1);
	}
	if (ft_strncmp("unset", cc, 4) == 0)
	{
		delmienv(tc->env, tc->cc[1]);
		return (1);
	}
	if (ft_strncmp("echo", cc, 4) == 0)
	{
		int i = 1;
		while(tc->cc[i])
		{
			if (i > 1)
				printline(" ");
			printline(tc->cc[i]);
			// printf("%s", c->args[i]);
			i++;
		}
		printline("\n");
		return(1);
	}
	////si el input es exit, cierra el programa
	if (ft_strncmp("exit", cc, 4) == 0)
	{
		if(tc->cc[1])
			exit(ft_atoi(tc->cc[1]));
		exit(0);
	}
	return (1);
}


