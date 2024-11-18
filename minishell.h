#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>		///mallocs
#include <signal.h>

typedef struct s_entorn {
	int lstret;
	char **env;
} t_entorn;

typedef struct s_comand {
	char *c;
	char **cc;
	char **env;
	int operator;
	int in;
	int out;
} t_comand;

t_comand *newcom(char *c, char **cc, char **env);

int forkea(t_comand *tc, int entrada, t_entorn *te);

void copitofile(t_comand *tc);
void readfromfile(t_comand *tc);

void execver(t_comand *tc);

void blockaction();
void allowaction();

#endif