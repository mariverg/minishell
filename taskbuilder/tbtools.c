#include "taskbuilder.h"

void	freetask(t_task *tt)
{
	free(tt->c);
	free(tt->cc);
	free(tt);
}

int	freetasklist(t_task *tt)
{
	t_task	*copy;

	while (tt)
	{
		copy = tt;
		tt = tt->next;
		freetask(copy);
	}
	return (0);
}
