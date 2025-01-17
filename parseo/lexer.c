/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:57:37 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/17 15:26:58 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseo.h"

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_operator(input[i]))
			handle_operator(input, &i, &tokens);
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (!handle_quote(input, &i, &tokens))
				return (NULL);
		}
		else if (input[i] == '$')
			handle_env_var(input, &i, &tokens);
		else
			handle_word(input, &i, &tokens);
	}
	return (tokens);
}

void	handle_operator(char *input, int *i, t_token **tokens)
{
	char	*value;

	value = get_operator(input, i);
	if (value)
	{
		if (ft_strcmp(value, "|") == 0)
			add_token(tokens, create_token(value, TOKEN_PIPE));
		else if (ft_strcmp(value, "<") == 0)
			add_token(tokens, create_token(value, TOKEN_REDIR_IN));
		else if (ft_strcmp(value, ">") == 0)
			add_token(tokens, create_token(value, TOKEN_REDIR_OUT));
		else if (ft_strcmp(value, "<<") == 0)
			add_token(tokens, create_token(value, TOKEN_HEREDOC));
		else if (ft_strcmp(value, ">>") == 0)
			add_token(tokens, create_token(value, TOKEN_APPEND));
		free(value);
	}
}

int	handle_quote(char *input, int *i, t_token **tokens)
{
	char	quote;
	char	*value;

	quote = input[*i];
	value = get_quoted_string(input, i, quote);
	if (!value)
	{
		free_tokens(*tokens);
		return (0);
	}
	if (quote == '"')
		add_token(tokens, create_token(value, TOKEN_DQUOTE));
	else
		add_token(tokens, create_token(value, TOKEN_SQUOTE));
	free(value);
	return (1);
}

void	handle_env_var(char *input, int *i, t_token **tokens)
{
	char	*value;

	value = get_env_var(input, i);
	if (value)
	{
		add_token(tokens, create_token(value, TOKEN_ENV_VAR));
		free(value);
	}
}

void	handle_word(char *input, int *i, t_token **tokens)
{
	char	*value;

	value = get_word(input, i);
	if (value)
	{
		add_token(tokens, create_token(value, TOKEN_WORD));
		free(value);
	}
}
