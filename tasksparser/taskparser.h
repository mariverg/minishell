/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:32 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:32 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKPARSER_H
# define TASKPARSER_H
# include "../minishell.h"

void	clearpipes(t_list *tl);
t_list	*dopipelst(t_task *tt);
int		setpipes(t_task *tt, t_list *pipelst);

int		execbuilt(t_task *tt);
int		changedir(t_task *tt);
int		echobuilt(t_task *tt);

int		copitfile(t_filedir *tc, t_env *te);
int		readfrmfile(t_filedir *tc, t_env *te);
int		waittasks(t_task *tt);
#endif
