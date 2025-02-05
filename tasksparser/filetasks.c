#include <errno.h>
#include "../minishell.h" 

int	copitfile(t_filedir *tc, t_env *env)
{
	char	*errmsg;
	int		res;

	if (tc->type == 0)
		res = open(tc->content, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		res = open(tc->content, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (res == -1)
	{
		errmsg = ft_strjoin(" ", strerror(errno));
		errormsg(errmsg, 0);
		switchexit(1, env, 0);
		exit(1);
	}
	return (res);
}

int	stallprocess(t_filedir *tc, t_env *env)
{
	char	*c;
	int		fd[2];
	size_t	l;

	pipe (fd);
	l = ft_strlen(tc->content);
	while (1)
	{
		c = readline(">");
		if (!c)
			write(fd[1], "\n", 1);
		else if (*c == 0)
			write(fd[1], "\n", 1);
		else if (ft_strncmp(c, tc->content, l) == 0 && ft_strlen(c) == l)
			break ;
		else
		{
			c = extractdollars(env, c);
			write(fd[1], c, ft_strlen(c));
			write(fd[1], "\n", 1);
		}
	}
	close (fd[1]);
	return (fd[0]);
}

int	readfrmfile(t_filedir *tc, t_env *env)
{
	char	*errmsg;
	int		res;

	if (tc->type == 0)
		res = open(tc->content, O_RDONLY);
	else
	{
		return (stallprocess(tc, env));
	}
	if (res == -1)
	{
		errmsg = ft_strjoin(" ", strerror(errno));
		errormsg(errmsg, 0);
		switchexit(1, env, 0);
		exit(1);
	}
	return (res);
}
