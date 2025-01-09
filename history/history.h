/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:31:37 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/09 11:51:24 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <readline/history.h>
# include <readline/readline.h>

void	init_history(void);
void	save_history_to_file(void);
void	add_to_history(const char *command);

#endif
