/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:57:37 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/13 15:46:24 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parseo.h"
t_token *tokenize(char *input)
{
    t_token *tokens;
    int     i;
    char    *value;
    char    quote;

    tokens = NULL;
    i = 0;
    while (input[i])
    {
        if (is_space(input[i]))
            i++;
        else if (is_operator(input[i]))
        {
            value = get_operator(input, &i);
            if (value)
            {
                if (strcmp(value, "|") == 0)
                    add_token(&tokens, create_token(value, TOKEN_PIPE));
                else if (strcmp(value, "<") == 0)
                    add_token(&tokens, create_token(value, TOKEN_REDIR_IN));
                else if (strcmp(value, ">") == 0)
                    add_token(&tokens, create_token(value, TOKEN_REDIR_OUT));
                else if (strcmp(value, "<<") == 0)
                    add_token(&tokens, create_token(value, TOKEN_HEREDOC));
                else if (strcmp(value, ">>") == 0)
                    add_token(&tokens, create_token(value, TOKEN_APPEND));
                free(value);
            }
        }
        else if (input[i] == '\'' || input[i] == '"')
        {
            quote = input[i];
            value = get_quoted_string(input, &i, quote);
            if (!value) // Error de comilla sin cerrar
            {
                free_tokens(tokens);
                return (NULL);
            }
            add_token(&tokens, create_token(value, 
                    quote == '"' ? TOKEN_DQUOTE : TOKEN_SQUOTE));
            free(value);
        }
        else if (input[i] == '$')
        {
            value = get_env_var(input, &i);
            if (value)
            {
                add_token(&tokens, create_token(value, TOKEN_ENV_VAR));
                free(value);
            }
        }
        else
        {
            value = get_word(input, &i);
            if (value)
            {
                add_token(&tokens, create_token(value, TOKEN_WORD));
                free(value);
            }
        }
    }
    return (tokens);
}

char	*get_word(char *input, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '\'' && input[*i] != '"' && input[*i] != '$')
	{
		(*i)++;
		len++;
	}
	return (ft_substr(input, start, len));
}

char	*get_operator(char *input, int *i)
{
	if (input[*i] == '|')
	{
		(*i)++;
		return (ft_strdup("|"));
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			(*i) += 2;
			return (ft_strdup("<<"));
		}
		(*i)++;
		return (ft_strdup("<"));
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			(*i) += 2;
			return (ft_strdup(">>"));
		}
		(*i)++;
		return (ft_strdup(">"));
	}
	return (NULL);
}

/* char	*get_quoted_string(char *input, int *i, char quote)
{
	int	start;
	int	len;

	start = ++(*i);
	len = 0;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == quote)
	{
		(*i)++;
		return (ft_substr(input, start, len));
	}
	return (NULL);
} */

char *get_quoted_string(char *input, int *i, char quote)
{
    int start;
    int len;

    start = ++(*i);
    len = 0;
    while (input[*i] && input[*i] != quote)
    {
        (*i)++;
        len++;
    }
    if (input[*i] == quote)
    {
        (*i)++;
        return (ft_substr(input, start, len));
    }
    // Si llegamos aquí, la comilla no se cerró
    ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
    ft_putstr_fd("minishell: syntax error: unclosed quote `", 2);
    ft_putchar_fd(quote, 2);
    ft_putstr_fd("'\n", 2);
    return (NULL);
}

char	*get_env_var(char *input, int *i)
{
	int	start;
	int	len;

	(*i)++;
	start = *i;
	len = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	return (ft_substr(input, start, len));
}
