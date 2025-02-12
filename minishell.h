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

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libs/libft/libft.h"

typedef struct s_env
{
	int		lastreturn;
	char	**env;
}	t_env;

typedef struct s_filedir
{
	char				*content;
	int					type;
	struct s_filedir	*next;
}	t_filedir;

typedef struct s_comand
{
	t_list			*argslst;
	t_filedir		*infile;
	t_filedir		*outfile;
	struct s_comand	*next;
}						t_comand;

typedef struct s_task
{
	char			*c;
	char			**cc;
	t_filedir		*filesin;
	t_filedir		*filesout;
	int				position;
	int				pid;
	int				operator;
	int				in;
	int				out;
	struct s_env	*env;
	struct s_task	*next;
}	t_task;

int			strxsize(char **c);
// char		*prntpwdline(t_env *te);
void		blockaction(void);

t_env		*newenv(char **env);
int			actualicepwd(t_env *te);
char		*getmienv(t_env *te, char *target);
int			delmienv(t_env *te, char *target);
int			daemonenv(t_task *tt);
void		fillpwd(t_env *te);

char		*extractdollars(t_env *te, char *c);
int			cancontinue(char *c);

t_comand	*makecomands(char *c);
t_task		*dotaskslist(t_comand *tc, t_env *te);

void		prntstrs(char **c, int out);
void		printline(char *c, int out);
int			printalphabetical(t_task *te, char *toprint, char *max);

int			inittp(t_task *tt);

int			errormsg(char *msg, char *info);
int			switchexit(int i, t_env *te, char *info);

void		freeenv(t_env *te);
int			freestrs(char **c);
int			freelst(t_list *tl);
int			freecomands(t_comand *tc);
int			freetasklist(t_task *tt);

#endif
