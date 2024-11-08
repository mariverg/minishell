#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "minishell.h"

/// ejecuta execve con los valores tc.
/// c y cc son los comandos a ejecutar, y env ahora mismo apunta a char **env en main
void execver(t_comand *tc)
{
	execve(tc->c,tc->cc,tc->env);
}


