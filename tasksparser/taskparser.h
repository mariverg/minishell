#include <sys/wait.h>

void clearpipes(t_list *tl);
t_list *dopipelst(t_task *tt);
int setpipes(t_task *tt, t_list *pipelst);

int execbuilt(t_task *tt);

int copitfile(t_filedir *tc, t_env *te);
int readfrmfile(t_filedir *tc, t_env *te);
