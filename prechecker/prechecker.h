/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prechecker.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomez-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:12:20 by ggomez-m          #+#    #+#             */
/*   Updated: 2025/01/08 12:12:24 by ggomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRECHECKER_H
# define PRECHECKER_H

# include "../minishell.h"

struct s_sxtracker
{
	int	apipe;
	int	aminus;
	int	amore;
};

int	validchar(char c);
int	hasstxerrcomp(char *c);

#endif
