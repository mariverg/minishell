/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:58:07 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/09 11:22:03 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseo.h"

t_command	*parse(char *input)
{
	t_parser	parser;
	t_command	*commands;
	t_command	*current_cmd;

	commands = NULL;
	current_cmd = NULL;
	if (!input)
	{
		printf("No input\n");
		return (NULL);
	}
	parser.input = input;
	parser.pos = 0;
	parser.tokens = tokenize(input);
	parser.current_token = parser.tokens;
	while (parser.current_token)
	{
		if (!current_cmd)
		{
			current_cmd = create_command();
			add_command(&commands, current_cmd);
		}
		if (parser.current_token->type == TOKEN_WORD
			|| parser.current_token->type == TOKEN_DQUOTE
			|| parser.current_token->type == TOKEN_SQUOTE
			|| parser.current_token->type == TOKEN_ENV_VAR)
		{
			current_cmd->args = add_argument(current_cmd->args,
					parser.current_token->value);
			parser.current_token = parser.current_token->next;
		}
		else if (parser.current_token->type == TOKEN_PIPE)
		{
			if (!parse_pipe(&parser))
				break ;
			current_cmd = create_command();
			add_command(&commands, current_cmd);
		}
		else if (parser.current_token->type >= TOKEN_REDIR_IN
			&& parser.current_token->type <= TOKEN_APPEND)
		{
			if (!parse_redirections(&parser, current_cmd))
				break ;
		}
		else
		{
			parser.current_token = parser.current_token->next;
		}
	}
	free_tokens(parser.tokens);
	return (commands);
}

bool	parse_redirections(t_parser *parser, t_command *cmd)
{
	t_token_type	redir_type;

	redir_type = parser->current_token->type;
	parser->current_token = parser->current_token->next;
	if (!parser->current_token || (parser->current_token->type != TOKEN_WORD
			&& parser->current_token->type != TOKEN_DQUOTE
			&& parser->current_token->type != TOKEN_SQUOTE))
	{
		return (false);
	}
	if (redir_type == TOKEN_REDIR_IN || redir_type == TOKEN_HEREDOC)
	{
		cmd->infile = ft_strdup(parser->current_token->value);
		if (redir_type == TOKEN_HEREDOC)
			cmd->in_type = 1;
		else
			cmd->in_type = 0;
	}
	else
	{
		cmd->outfile = ft_strdup(parser->current_token->value);
		if (redir_type == TOKEN_APPEND)
			cmd->out_type = 1;
		else
			cmd->out_type = 0;
	}
	parser->current_token = parser->current_token->next;
	return (true);
}

bool	parse_pipe(t_parser *parser)
{
	if (!parser->current_token->next)
		return (false);
	parser->current_token = parser->current_token->next;
	return (true);
}
