#include "../minishell.h" 
#include "taskparser.h" 

int getexit(t_task *tt)
{
	char *c;
	int i;
	int sz;
	int res;

	// printcm(tt);
	sz = 0;
	res = 0;
	i = 1;

	while(tt->cc[i])
	{
		
		res = ft_atoi(tt->cc[i]); 
		sz++;
		i++;
	}
	// if (sz > 1)
	// {

	// }
	return(res);
}

int execbuilt(t_task *tt)
{
	if (ft_strncmp("cd", tt->c, 3) == 0)
	{
		if (tt->cc[2])
		{
			write(STDERR_FILENO, " too many arguments", 19);
			switchexit(1, tt->env, 0);
			return(0);
		}
		int i = chdir(tt->cc[1]);
		if (i == -1)
		{
			write(STDERR_FILENO, " No such file or directory", 26);
			switchexit(1, tt->env, 0);
			return(0);
		}
	}
	else if (ft_strncmp("pwd", tt->c, 4) == 0)
	{
		char *wd = getmienv(tt->env, "PWD");
		write(STDOUT_FILENO, wd, ft_strlen(wd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (ft_strncmp("env", tt->c, 4) == 0)
	{
		prntstrs(tt->env->env, STDOUT_FILENO);
	}
	else if (ft_strncmp("export", tt->c, 4) == 0)
	{
		if(tt->cc[1])
		{
			daemonenv(tt);
		}
		else
			printalphabetical(tt, 0, 0);
	}
	else if (ft_strncmp("unset", tt->c, 4) == 0)
	{
		delmienv(tt->env, tt->cc[1]);
	}
	else if (ft_strncmp("echo", tt->c, 4) == 0)
	{
		int n;
		int i;

		n = 0;
		if (ft_strncmp("-n", tt->cc[1], 3) == 0)
			n = 1;
		i = 1 + n;
		while(tt->cc[i])
		{
			if (i > (1 + n))
				write(STDOUT_FILENO," ",1);
			write(STDOUT_FILENO, tt->cc[i], ft_strlen(tt->cc[i]));
			i++;
		}
		if (!n)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (ft_strncmp("exit", tt->c, 4) == 0)
	{
		// int i;

		// i = 1;
		// printf(" tasks vale>\n");
		// printcm(tt);
		// printf(" tasks over>\n");
		// while(*(tt->cc[i]) == '+')
		// {
		// 	printf("pasa a 2 \n");
		// 	i++;
		// }
			// printf("	tasks vale>\n");
			// printcm(tt);
			// printf("	tasks over>\n");
		// if(tt->cc[i])
		// 	exit(ft_atoi(tt->cc[1]));
		exit(getexit(tt));
	}
	return (1);
}