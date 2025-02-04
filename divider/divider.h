#include "../minishell.h"



t_list *getchunks(char *c);
t_comand *getcom(char *c);
int getspacer(char *c, char *comp);
int istruncker(char c, char *comp);

// t_list *addchunk(t_list *onepiece, char *c, int start, int end);
// void prntchunks(t_list *tl);

int delcomas(t_comand *tc);
