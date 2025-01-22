/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:07:42 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:07:46 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char *ci;
	char *co;
	int intype;
	int outtype;
	struct s_env *env;
	int operator;
	int in;
	int out;
	struct s_task *next;
} t_task;

int strxsize(char **c);

t_task *newcom(char *c, char **cc, t_env *env);
t_env *newenv(char **env);

void init_readline_customization(void);

char *getmienv(t_env *te, char *target);
int setmienv(t_env *te, char *target, char *newenvvar);
int addmienv (t_env *te, char *target, char *value);
int delmienv(t_env *te, char *target);
int actualicepwd(t_env *te);
int addstrenv(t_env *te, char *c);
int daemonenv(t_task *tt);
void freeenv(t_env *te);
void freestrs(char **c);

int command_cdcheck(t_command *c, t_env *te);

int numcoms(t_command *tc);
t_task *dotaskslist(t_command *tc, t_env *te);

char *execinenv(t_env *te, char *target);

void blockaction();
void allowaction();

void printcmmm(t_command *current);
void printcm(t_task *tc);
void prntstrs(char **c, int out);
void printline(char *c, int out);
int printalphabetical(t_task *te, char *toprint, char *max);

char *expanddollars(t_env *te, char *c);

int inittp(t_task *tt);

int errormsg(char *msg, char *info);
int switchexit(int i, t_env *te, char *info);
int exitrtrn(int i, t_env *te, char *msg, char *info);

#endif
