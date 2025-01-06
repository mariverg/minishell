#include <sys/stat.h>
#include <sys/wait.h>

#include "../minishell.h"
// #include "libs/libtxttools/libtxttools.h"
// #include "libs/libft/libft.h"

///ejecuta la funcion execve
void execver(t_task *tc)
{
	int pid;

	pid = fork();
	if (pid == 0)
		execve(tc->c,tc->cc,tc->env->env);
	else
	{
		wait(0);
	}
}

//// ejecuta los builtins
int execbuiltin(t_task *tc)
{
	////si el input es cd, hace el cambio de dir
	if (ft_strncmp("cd", tc->c, 3) == 0)
	{
		int i = chdir(tc->cc[1]);
		return (1);
	}
	else if (ft_strncmp("env", tc->c, 4) == 0)
	{
		prntstrs(tc->env->env);
		return(1);
	}
	else if (ft_strncmp("export", tc->c, 4) == 0)
	{
		printalphabetical(tc->env, 0, 0);
		return(1);
	}
	else if (ft_strncmp("unset", tc->c, 4) == 0)
	{
		delmienv(tc->env, tc->cc[1]);
		return (1);
	}
	else if (ft_strncmp("echo", tc->c, 4) == 0)
	{
		int i = 1;
		while(tc->cc[i])
		{
			if (i > 1)
				printline(" ");
			printline(tc->cc[i]);
			i++;
		}
		printline("\n");
		return(1);
	}
	////si el input es exit, cierra el programa
	else if (ft_strncmp("exit", tc->c, 4) == 0)
	{
		if(tc->cc[1])
			exit(ft_atoi(tc->cc[1]));
		exit(0);
	}
	return (1);
}


