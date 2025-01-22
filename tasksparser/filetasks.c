#include <fcntl.h>
#include "../minishell.h" 

int copitfile(t_task *tc)
{
	int res;

	if (tc->outtype == 0)
	{
		res = open(tc->co, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
	{
		res = open(tc->co, O_CREAT | O_APPEND | O_WRONLY, 0777);
	}
	if (res == -1)
	{
		write(STDERR_FILENO, " Permission denied", 18);
		exit(126);
	}
	return(res);
}

int readfrmfile(t_task *tc)
{
	int fd[2];
	int res;
	char *c;

	if(tc->intype == 0)
		res = open(tc->ci, O_RDONLY);
	else
	{
		pipe (fd);
		while (1)
		{
			c = readline(">");
			if (ft_strncmp(c, tc->ci, ft_strlen(tc->ci)) == 0 && ft_strlen(c) == ft_strlen(tc->ci))
				break;
			else
			{
				c = expanddollars(tc->env, c);
				write(fd[1],c,ft_strlen(c));
				write(fd[1],"\n",1);
			}
		}
		close (fd[1]);
		return(fd[0]);
	}
	if (res == -1)
	{

		write(STDERR_FILENO, " No such file or directory", 26);
		exit(1);
	}
	return(res);
}
