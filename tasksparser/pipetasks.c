#include "../minishell.h"

void printpipes(t_list *tl)
{
	int *fd;
	while(tl)
	{
		fd = tl->content;
		printf("un pipe con %i - %i como direcciones\n", fd[0], fd[1]);
		tl = tl->next;
	}
}

void clearpipes(t_list *tl)
{
	t_list *tll;
	int *fd;

	while(tl)
	{
		fd = tl->content;
		close(fd[0]);
		close(fd[1]);
		tll = tl;
		tl = tl->next;
		free(fd);
		free(tll);
	}
}

t_list *dopipelst(t_task *tt)
{
	int *fd;
	t_list *pipes;
	t_list *empty;

	empty = ft_lstnew(0);
	pipes = empty;
	while(tt->next)
	{
		fd = malloc(sizeof(int) * 2);
		pipe(fd);
		pipes->next = ft_lstnew(fd);
		pipes = pipes->next;
		tt = tt->next;
	}
	pipes = empty->next;
	free(empty);
	return(pipes);
}

int setpipes(t_task *tt, t_list *pipelst)
{
	int *fd;
	int in;

	in = STDIN_FILENO;
	while(tt)
	{
		tt->in = in;
		if(pipelst)
		{
			fd = (int *)pipelst->content;
			tt->out = fd[1];
			in = fd[0];
			pipelst =  pipelst->next;
		} 
		else
			tt->out = STDOUT_FILENO;
		tt = tt->next;
	}
	// 
	return(0);
}