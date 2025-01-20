#include <fcntl.h>
#include "../minishell.h" 

int copitfile(t_task *tc)
{
	int res;

	if (tc->outtype == 0)
	{
		printf("sobreescribiendo\n");
		res = open(tc->co, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else
	{
		printf("sumando\n");
		res = open(tc->co, O_CREAT | O_APPEND | O_WRONLY, 0777);
	}
	if (res == -1)
	{
		printf("error creando archivo\n");
		exit(-1);
	}
	return(res);
}

int readfrmfile(t_task *tc)
{
	int res;
	char *c;

	if(tc->intype == 0)
		res = open(tc->ci, O_RDONLY);
	else
	{
		while (1)
		{
			c = readline(">");
			if (ft_strncmp(c, tc->ci, ft_strlen(tc->ci)) == 0 && ft_strlen(c) == ft_strlen(tc->ci))
				break;
			// else
			// {
			// 	if (tc->out != STDOUT_FILENO)
			// 	{
			// 		write(tc->out,miin,ft_strlen(miin));
			// 		write(tc->out,"\n",1);
			// 	}
			// }
		}
	}
	if (res == -1)
	{
		printf("error creando archivo\n");
		exit(-1);
	}
	return(res);
}
/*
void copitfile2(t_task *tc)
{
	printf("copitfile\n");
	char c[1];
	
	int arch = open(tc->c, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (arch == -1)
	{
		write(STDERR_FILENO, " No such file or directory\0", 27);
		return;
	}
	while(read(tc->in, c, 1))
	{
		write(arch, c, 1);
	}
	write(arch, "\n", 1);
	close(arch);
	tc->env->lastreturn = 0;
}

void sumtfile(t_task *tc)
{
	char c[1];

	int arch = open(tc->c, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (arch == -1)
	{
		write(STDERR_FILENO, " No such file or directory\0", 27);
		return;
	}
	while(read(tc->in, c, 1))
	{
		write(arch, c, 1);
	}
	write(arch, "\n", 1);
	close(arch);
	tc->env->lastreturn = 0;
}



void readfrmfile2(t_task *tc)
{
	int i;
	char c[250000];
	int arch;

	arch = open(tc->c, O_RDONLY);
	if (arch == -1)
	{
		write(STDERR_FILENO, " No such file or directory\0", 27);
		tc->env->lastreturn = 1;
		return;
	}
	while((i = read(arch, c, 250000)) > 0)
	{
		write(1, c, i);
		if (tc->out != STDOUT_FILENO)
		{
			write(tc->out , c, i);
		}
	}
	close (tc->out);
	close(arch);
	tc->env->lastreturn = 0;
}

void readfrmterm(t_task *tc)
{
	char *miin;

	while (1)
	{
		miin = readline(">");
		if (ft_strncmp(miin, tc->c, ft_strlen(tc->c)) == 0 && ft_strlen(miin) == ft_strlen(tc->c))
			break;
		else
		{
			if (tc->out != STDOUT_FILENO)
			{
				write(tc->out,miin,ft_strlen(miin));
				write(tc->out,"\n",1);
			}
		}
	}
	tc->env->lastreturn = 0;
}

*/