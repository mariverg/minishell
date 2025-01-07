
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#include "minishell.h"
#include "parseo/parseo.h"
#include "libs/libft/libft.h"
#include <fcntl.h>

void prntpwdline(t_env *te)
{
	char	*directorio;
	
	actualicepwd(te);
	directorio = getmienv(te, "PWD");
	printf("%s",directorio);
	free (directorio);
}

int docom(t_task *tc, t_env *te)
{
	if(tc->operator == 11)
		execver(tc);
	if(tc->operator == 12)
		execbuiltin(tc);
	if(tc->operator == 21)
		execbuiltin(tc);
	else if (tc->operator == 1)
		copitofile(tc);
	else if (tc->operator == 2)
		readfromfile(tc);
	else if (tc->operator == 3)
		sumtofile(tc);
	else if (tc->operator == 4)
		readfromterm(tc);
	return (0);
}

int proccoms(t_task *tt, t_env *te)
{
	int fd[2];
	while (tt)
	{
		if (tt->next)
		{
			pipe(fd);
			tt->out = fd[1];
			tt->next->in = fd[0];
		}
		// else
		// {
		// 	tt->out = STDOUT_FILENO;
		// }
		docom(tt, te);
		if (tt->in >= 0 && tt->in != STDIN_FILENO)
		{
			// printf("cerrando in %i el std es %i\n", tt->in, STDIN_FILENO);
			close(tt->in);
		}
		if (tt->out >= 0 && tt->out != STDOUT_FILENO)
		{
			// printf("cerrando out %i el std es %i\n", tt->out, STDOUT_FILENO);
			close(tt->out);
		}
		tt = tt->next;
	}
	return (0);
}

int main(int argc, char **argv, char **argenv)
{
	t_env		*te;
	char		*input;
    t_command	*commands;
	t_task		*tc;
    int			i;
	char		*c;

	blockaction();
	te = newenv(argenv);
	while (1)
	{
		prntpwdline(te);
		input = readline(">");
		if (!input)
			break;
		input = expanddollars(te, input);
		commands = parse(input);
		tc = gettaskslist(commands, te);
		if (tc)
			proccoms(tc, te);
		free(input);
	}
	freeenv(te);
	return (0);
}

