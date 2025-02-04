#include "../minishell.h"

t_task *newtask(char *c, char **cc, t_env *env, int i);
t_task *lastcom(t_task *tc);
char **getargs(t_list *tl);
char *execinenv(t_env *te, char *target);

