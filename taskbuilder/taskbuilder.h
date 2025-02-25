/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taskbuilder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:19:45 by mariverg          #+#    #+#             */
/*   Updated: 2025/02/25 12:19:47 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKBUILDER_H
# define TASKBUILDER_H
# include "../minishell.h"

t_task	*newtask(char *c, char **cc, t_env *env, int i);
t_task	*lastcom(t_task *tc);
char	**getargs(t_list *tl);
char	*execinenv(t_env *te, char *target);
#endif
