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
typedef struct s_filedir
{
	char	*content;
	int		type;
	struct s_filedir	*next;
}	t_filedir;

typedef struct s_comand
{
	char				**args;
	// char				*infile;
	// char				*outfile;
	int					in_type;
	int					out_type;
	// struct s_command	*next;

	t_list				*argslst;
	t_filedir			*infile;
	t_filedir			*outfile;
	struct s_comand	*next;
}						t_comand;

typedef struct s_env {
	int lastreturn;
	char **env;
} t_env;

typedef struct s_task {
	char *c;
	char **cc;
	t_filedir *filesin;
	t_filedir *filesout;
	char *ci;
	char *co;
	int intype;
	int outtype;
	int position;
	int pid;
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
int freestrs(char **c);
int freefilelist(t_filedir *tl);
int freelst(t_list *tl);

int command_cdcheck(t_command *c, t_env *te);

int numcoms(t_command *tc);
t_task *dotaskslist(t_comand *tc, t_env *te);

char *execinenv(t_env *te, char *target);

void blockaction();
void allowaction();

void printcmmm(t_command *current);
void printcm(t_task *tc);
void prntstrs(char **c, int out);
void printline(char *c, int out);
int printalphabetical(t_task *te, char *toprint, char *max);

// char *expanddollars(t_env *te, char *c);

int inittp(t_task *tt);

int errormsg(char *msg, char *info);
int switchexit(int i, t_env *te, char *info);
int exitrtrn(int i, t_env *te, char *msg, char *info);

t_comand *makecomands(char *c);
void prt(t_comand *tc);

char *extractdollars(t_env *te, char *c);
void prntstrss(char **c, int out);
int cancontinue(char *c);

#endif
