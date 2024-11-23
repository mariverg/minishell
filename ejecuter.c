#include <sys/stat.h>

#include "minishell.h"
// #include "libs/libtxttools/libtxttools.h"
#include "libs/libft/libft.h"

///ejecuta la funcion execve
void execver(t_com *tc)
{
	execve(tc->c,tc->cc,tc->env);
}


