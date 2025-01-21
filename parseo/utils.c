/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:58:20 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/21 14:17:18 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseo.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->in_type = 0;
	cmd->out_type = 0;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **commands, t_command *new_cmd)
{
	t_command	*current;

	if (!*commands)
		*commands = new_cmd;
	else
	{
		current = *commands;
		while (current->next)
			current = current->next;
		current->next = new_cmd;
	}
}

char	**add_argument(char **args, char *new_arg)
{
	int		i;
	char	**new_args;

	i = 0;
	if (args)
		while (args[i])
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	if (args)
	{
		while (args[i])
		{
			new_args[i] = args[i];
			i++;
		}
	}
	new_args[i] = ft_strdup(new_arg);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

