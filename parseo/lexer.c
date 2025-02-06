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

/* int	handle_quote(char *input, int *i, t_token **tokens)
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
} */
int	handle_quote(char *input, int *i, t_token **tokens)
{
	char	quote;
	char	*value;
	char	*temp;
	char	*final_value;

	quote = input[*i];
	final_value = ft_strdup("");  // Inicializamos con una cadena vacía
	if (!final_value)
		return (0);

	while (input[*i] == quote)  // Mientras haya comillas seguidas
	{
		value = get_quoted_string(input, i, quote);
		if (!value)  // Si hay error en las comillas, limpiamos y salimos
		{
			free(final_value);
			free_tokens(*tokens);
			return (0);
		}
		temp = ft_strjoin(final_value, value);  // Concatenamos
		free(final_value);
		free(value);
		final_value = temp;
	}
	// Guardamos el token final con todas las partes fusionadas
	add_token(tokens, create_token(final_value, (quote == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE));
	free(final_value);
	return (1);
}


/* void	handle_env_var(char *input, int *i, t_token **tokens)
{
	char	*value;

	value = get_env_var(input, i);
	if (value)
	{
		add_token(tokens, create_token(value, TOKEN_ENV_VAR));
		free(value);
	}
} */
void handle_env_var(char *input, int *i, t_token **tokens)
{
    char *value;

    // Special case for lone $ or $ followed by non-alphanumeric
    if (input[*i + 1] == '\0' || 
        (!ft_isalnum(input[*i + 1]) && input[*i + 1] != '?'))
    {
        add_token(tokens, create_token("$", TOKEN_ENV_VAR));
        (*i)++;
        return;
    }

    value = get_env_var(input, i);
    if (value)
    {
        add_token(tokens, create_token(value, TOKEN_ENV_VAR));
        free(value);
    }
}


/* void	handle_word(char *input, int *i, t_token **tokens)
{
	char	*value;

	value = get_word(input, i);
	if (value)
	{
		add_token(tokens, create_token(value, TOKEN_WORD));
		free(value);
	}
} */

void	handle_word(char *input, int *i, t_token **tokens)
{
	char	*value;
	char	*temp;
	char	*final_value;

	final_value = ft_strdup("");  // Inicializamos cadena vacía
	if (!final_value)
		return;

	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))  
	{
		if (input[*i] == '\'' || input[*i] == '"')  // Si es comilla, llamar a `get_quoted_string`
		{
			char quote = input[*i];
			value = get_quoted_string(input, i, quote);
		}
		else  // Si es palabra normal, llamar a `get_word`
		{
			value = get_word(input, i);
		}
		if (!value)  // Si hubo error en comillas, liberar memoria y salir
		{
			free(final_value);
			return;
		}
		// Concatenamos la nueva parte al resultado final
		temp = ft_strjoin(final_value, value);
		free(final_value);
		free(value);
		final_value = temp;
	}
	// Finalmente, agregamos un solo token con el string fusionado
	add_token(tokens, create_token(final_value, TOKEN_WORD));
	free(final_value);
}

