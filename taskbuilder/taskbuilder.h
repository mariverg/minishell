#include "../minishell.h"

t_task *newtask(char *c, char **cc, t_env *env, int i);
t_task *lastcom(t_task *tc);
int stractin(t_command *tc, t_task *tt);
int stractout(t_command *tc, t_task *tt);
char **getargs(t_list *tl);

