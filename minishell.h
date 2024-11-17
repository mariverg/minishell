#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_entorno {
	int lstret;
} t_entorno;

typedef struct s_comand {
	char *c;
	char **cc;
	char **env;
	int operator;
	int in;
	int out;
} t_comand;

t_comand *newcom(char *c, char **cc, char **env);

pid_t forkea(t_comand *tc, pid_t entrada, t_entorno *te);

void copitofile(t_comand *tc);
void readfromfile(t_comand *tc);

void execver(t_comand *tc);

void blockaction();
void allowaction();

#endif