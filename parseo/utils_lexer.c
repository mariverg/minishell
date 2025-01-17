#include "parseo.h"

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


char	*get_quoted_string(char *input, int *i, char quote)
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
	// ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
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
