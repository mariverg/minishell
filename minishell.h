#ifndef MINISHELL_H
# define MINISHELL_H

#include "parseo/parseo.h"

// #include <stdlib.h>		///mallocs
// #include <signal.h>

typedef struct s_env {
	int lastreturn;
	char **env;
} t_env;

typedef struct s_task {
	char *c;
	char **cc;
	// char **env;
	struct s_env *env;
	int operator;
	int fd[2];
	int in;
	int out;
	struct s_task *next;
} t_task;

int strxsize(char **c);

t_task *newcom(char *c, char **cc, t_env *env);
t_env *newenv(char **env);

char *getmienv(t_env *te, char *target);
int setmienv(t_env *te, char *target, char *newenvvar);
int addmienv (t_env *te, char *target, char *value);
int delmienv(t_env *te, char *target);
int actualicepwd(t_env *te);
void freeenv(t_env *te);
void freestrs(char **c);

int command_cdcheck(t_command *c, t_env *te);

int numcoms(t_command *tc);
t_task *gettaskslist(t_command *tc, t_env *te);

char *execinenv(t_env *te, char *target);

int forkea(t_task *tc, int entrada, t_env *te);

void copitofile(t_task *tc);
void readfromfile(t_task *tc);
void readfromterm(t_task *tc, int fd);
void sumtofile(t_task *tc);

// char **mipaths(char **env);
// char *runnable(char *target, char **env);
void execver(t_task *tc);

void blockaction();
void allowaction();

void printcmmm(t_command *current);
void printcm(t_task *tc);
void prntstrs(char **c);
void printline(char *c);
int printalphabetical(t_env *te, char *toprint, char *max);
int execbuiltin(t_task *tc);

char *expanddollars(t_env *te, char *c);



#endif