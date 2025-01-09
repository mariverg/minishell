/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:30:42 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/09 11:52:25 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <stdio.h>

#define HISTORY_FILE ".minishell_history"

void	init_history(void)
{
	using_history();
	read_history(HISTORY_FILE);
}

void	save_history_to_file(void)
{
	write_history(HISTORY_FILE);
}

void	add_to_history(const char *command)
{
	if (command && *command)
		add_history(command);
}
