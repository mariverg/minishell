#include "taskparser.h"

int	correctexit(int i)
{
	int	res;

	res = i;
	if (res == 2)
		res = 130;
	return (res);
}

int	waittasks(t_task *tt)
{
	int	pid;
	int	status;

	nullaction();
	while (tt)
	{
		pid = waitpid(tt->pid, &status, 0);
		if (pid == tt->pid)
		{
			if (WIFEXITED(status))
				switchexit(WEXITSTATUS(status), tt->env, 0);
			else
				switchexit(correctexit(WTERMSIG(status)), tt->env, 0);
		}
		tt = tt->next;
	}
	blockaction();
	return (0);
}
