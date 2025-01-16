/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envbuilder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:09:25 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:09:29 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVBUILDER_H
# define ENVBUILDER_H
#include "../minishell.h"
#include "../libs/libft/libft.h"

#include <sys/stat.h>

int getmienvindex(t_env *te, char *target);
int daemonenv(t_task *tt);
#endif
