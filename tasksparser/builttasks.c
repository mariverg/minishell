#include "taskparser.h" 

int	getexit(t_task *tt)
{
	int	res;

	res = 0;
	if (tt->cc[1])
	{
		if (tt->cc[2])
		{
			errormsg(" too many arguments\n", 0);
			return (1);
		}
		res = ft_atoi(tt->cc[1]);
		if (!res)
		{
			errormsg(" numeric argument required\n", 0);
			return (2);
		}
	}
	return (res);
}

int	changedir(t_task *tt)
{
	int	i;

	if (tt->cc[2])
	{
		write(STDERR_FILENO, " too many arguments\n", 19);
		switchexit(1, tt->env, 0);
		return (0);
	}
	i = chdir(tt->cc[1]);
	if (i == -1)
	{
		write(STDERR_FILENO, " No such file or directory\n", 26);
		switchexit(1, tt->env, 0);
	}
	fillpwd(tt->env);
	return (0);
}

int	echobuilt(t_task *tt)
{
	int	n;
	int	i;

	n = 0;
	if (tt->cc[1] == 0)
		return (0);
	if (ft_strncmp("-n", tt->cc[1], 3) == 0)
		n = 1;
	i = 1 + n;
	while (tt->cc[i])
	{
		if (i > (1 + n))
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tt->cc[i], ft_strlen(tt->cc[i]));
		i++;
	}
	if (!n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

void	prinworkingd(void)
{
	char	*wd;

	wd = getcwd(0, 0);
	write(STDOUT_FILENO, wd, ft_strlen(wd));
	write(STDOUT_FILENO, "\n", 1);
}

int	execbuilt(t_task *tt)
{
	if (ft_strncmp("cd", tt->c, 3) == 0)
		return (changedir(tt));
	else if (ft_strncmp("pwd", tt->c, 4) == 0)
		prinworkingd();
	else if (ft_strncmp("env", tt->c, 4) == 0)
		prntstrs(tt->env->env, STDOUT_FILENO);
	else if (ft_strncmp("export", tt->c, 4) == 0)
	{
		if (tt->cc[1])
			daemonenv(tt);
		else
			printalphabetical(tt, 0, 0);
	}
	else if (ft_strncmp("unset", tt->c, 4) == 0)
		delmienv(tt->env, tt->cc[1]);
	else if (ft_strncmp("echo", tt->c, 4) == 0)
		echobuilt(tt);
	else if (ft_strncmp("exit", tt->c, 4) == 0)
		exit(getexit(tt));
	return (0);
}
