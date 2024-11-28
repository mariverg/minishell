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
	struct s_com *next;
} t_com;

int strxsize(char **c);

t_com *newcom(char *c, char **cc, char **env);
t_env *newenv(char **env);

char *getmienv(t_env *te, char *target);
char *setmienv(t_env *te, char *target, char *newenvvar);
int addmienv (t_env *te, char *target, char *value);
int delmienv(t_env *te, char *target);
void actualicepwd(t_env *te);

int command_cdcheck(t_command *c);

int numcoms(t_command *tc);
t_com *getcomslist(t_command *tc, t_env *te);

char *execinenv(t_env *te, char *target);

int forkea(t_com *tc, int entrada, t_env *te);

void copitofile(t_com *tc);
void readfromfile(t_com *tc);
void sumtofile(t_com *tc);

// char **mipaths(char **env);
// char *runnable(char *target, char **env);
void execver(t_com *tc);

void blockaction();
void allowaction();

void printcmmm(t_command *current);
void printcm(t_com *tc);
void prntstrs(char **c);



#endif