#include <sys/wait.h>

void clearpipes(t_list *tl);
t_list *dopipelst(t_task *tt);
int setpipes(t_task *tt, t_list *pipelst);

int execbuilt(t_task *tt);

int copitfile(t_task *tc);
// void sumtfile(t_task *tc);
int readfrmfile(t_task *tc);
// void readfrmterm(t_task *tc);