#ifndef DIVIDER_H
# define DIVIDER_H
# include "../minishell.h"

typedef struct s_switcher
{
	int	simple;
	int	duble;
}	t_switcher;

t_list		*getchunks(char *c);
t_comand	*getcom(char *c);
int			getspacer(char *c, char *comp);
int			istruncker(char c, char *comp);
int			delcomas(t_comand *tc);
void		filllsts(t_list *empty, char *c);
t_filedir	*getredir(char *c, char *ch);
char		*estractclean(char *c);
#endif