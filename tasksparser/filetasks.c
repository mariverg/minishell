#include <fcntl.h>
#include "../minishell.h" 

void copitfile(t_task *tc)
{
	// printf("copitfile\n");
	char c[1];
	
	close(tc->lstout);
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

	close(tc->lstout);
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

void readfrmfile(t_task *tc)
{
	char c[1];
	int arch = open(tc->c, O_RDONLY);
	if (arch == -1)
	{
		write(STDERR_FILENO, " No such file or directory\0", 27);
		return;
	}
	while(read(arch, c, 1))
	{
		if (tc->out != STDOUT_FILENO)
			write(tc->out, c, 1);
	}
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