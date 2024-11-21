#ifndef MINISHELL_H
# define MINISHELL_H

#include "parseo/parseo.h"

// #include <stdlib.h>		///mallocs
// #include <signal.h>

typedef struct s_env {
	int lastreturn;
	char **env;
} t_env;

typedef struct s_com {
	char *c;
	char **cc;
	char **env;
	int operator;
	int in;
	int out;
} t_com;

t_com *newcom(char *c, char **cc, char **env);
t_env *newenv(char **env);

char *getenvvar(t_env *te, char *target);
char *execinenv(t_env *te, char *target);

int forkea(t_com *tc, int entrada, t_env *te);

void copitofile(t_com *tc);
void readfromfile(t_com *tc);

char **mipaths(char **env);
char *runnable(char *target, char **env);
void execver(t_com *tc);

void blockaction();
void allowaction();

void printcmmm(t_command *current);
void prntstrs(char **c);



#endif