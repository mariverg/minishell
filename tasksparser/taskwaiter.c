#include "taskparser.h"

int	waittasks(t_task *tt)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	while (tt)
	{
		pid = waitpid(tt->pid, &status, 0);
		if (pid == tt->pid && tt->position > i)
		{
			i = tt->position;
			if (WIFEXITED(status))
				switchexit(WEXITSTATUS(status), tt->env, 0);
			else
				switchexit(WTERMSIG(status), tt->env, 0);
		}
		tt = tt->next;
	}
	return (0);
}
