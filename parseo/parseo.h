/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:57:58 by mariverg          #+#    #+#             */
/*   Updated: 2025/01/13 15:43:40 by mariverg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEO_H
# define PARSEO_H

# include "../libs/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Definición de los diferentes tipos de tokens que se usarán
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_ENV_VAR,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
	TOKEN_EOF
}						t_token_type;

// Estructura que representa un token
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

// Estructura que representa un comando completo
typedef struct s_command
{
	char				**args;
	char				*infile;
	char				*outfile;
	int					in_type;
	int					out_type;
	struct s_command	*next;
}						t_command;

// Estructura que representa el estado del parser
typedef struct s_parser
{
	char				*input;
	int					pos;
	t_token				*current_token;
	t_token				*tokens;
}						t_parser;

// Prototipos de funciones para el lexer (generador de tokens)
t_token					*tokenize(char *input);
t_token					*create_token(char *value, t_token_type type);
void					add_token(t_token **tokens, t_token *new_token);
char					*get_word(char *input, int *i);
char					*get_operator(char *input, int *i);
char					*get_quoted_string(char *input, int *i, char quote);
char					*get_env_var(char *input, int *i);

// Prototipos de funciones para el parser (analizador de comandos)
t_command				*parse(char *input);
t_command				*create_command(void);
void					add_command(t_command **commands, t_command *new_cmd);
bool					parse_redirections(t_parser *parser, t_command *cmd);
bool					parse_pipe(t_parser *parser);
char					**add_argument(char **args, char *new_arg);

// Prototipos de funciones de utilidad
void					free_tokens(t_token *tokens);
void					free_commands(t_command *commands);
bool					is_space(char c);
bool					is_operator(char c);
bool					is_quote(char c);
bool is_valid_token_sequence(t_token *current, t_token *next);
void print_syntax_error(t_token *token);
bool validate_syntax(t_token *tokens);
#endif
