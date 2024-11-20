#ifndef PARSEO_H
# define PARSEO_H

// Incluye las librerías estándar necesarias para el programa
# include <stdio.h>   // Para funciones de entrada y salida
# include <stdlib.h>  // Para gestión de memoria (malloc, free, etc.)
# include <string.h>  // Para funciones de manipulación de cadenas
# include <unistd.h>  // Para funciones del sistema como close, write
# include <stdbool.h> // Para manejar valores booleanos (true, false)
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// Definición de los diferentes tipos de tokens que se usarán
typedef enum e_token_type {
    TOKEN_WORD,       // Palabra ordinaria (comando o argumento)
    TOKEN_PIPE,       // Operador de tubería '|'
    TOKEN_REDIR_IN,   // Redirección de entrada '<'
    TOKEN_REDIR_OUT,  // Redirección de salida '>'
    TOKEN_HEREDOC,    // Redirección heredoc '<<'
    TOKEN_APPEND,     // Redirección de salida en modo append '>>'
    TOKEN_ENV_VAR,    // Variable de entorno (ej. $HOME)
    TOKEN_DQUOTE,     // Cadena entre comillas dobles
    TOKEN_SQUOTE,     // Cadena entre comillas simples
    TOKEN_EOF         // Fin de entrada
} t_token_type;

// Estructura que representa un token
typedef struct s_token {
    char            *value;          // El contenido del token (ej. "ls", "|")
    t_token_type    type;            // Tipo de token (ej. TOKEN_WORD, TOKEN_PIPE)
    struct s_token  *next;           // Puntero al siguiente token en la lista
} t_token;

// Estructura que representa un comando completo
typedef struct s_command {
    char                **args;      // Lista de argumentos del comando
    char                *infile;    // Archivo de entrada (si se especifica)
    char                *outfile;   // Archivo de salida (si se especifica)
    int                 in_type;    // Tipo de entrada: 0 (normal), 1 (heredoc)
    int                 out_type;   // Tipo de salida: 0 (normal), 1 (append)
    struct s_command    *next;      // Puntero al siguiente comando en la lista
} t_command;

// Estructura que representa el estado del parser
typedef struct s_parser {
    char        *input;         // La cadena de entrada completa
    int         pos;            // Posición actual en la cadena de entrada
    t_token     *current_token; // Token que se está procesando actualmente
    t_token     *tokens;        // Lista enlazada de todos los tokens generados
} t_parser;

// Prototipos de funciones para el lexer (generador de tokens)
t_token     *tokenize(char *input);                               // Tokeniza la entrada
t_token     *create_token(char *value, t_token_type type);        // Crea un nuevo token
void        add_token(t_token **tokens, t_token *new_token);      // Añade un token a la lista
char        *get_word(char *input, int *i);                       // Extrae una palabra de la entrada
char        *get_operator(char *input, int *i);                   // Extrae un operador (|, <, >)
char        *get_quoted_string(char *input, int *i, char quote);  // Extrae una cadena entre comillas
char        *get_env_var(char *input, int *i);                    // Extrae una variable de entorno

// Prototipos de funciones para el parser (analizador de comandos)
t_command   *parse(char *input);                                  // Parsea la entrada para generar comandos
t_command   *create_command(void);                                // Crea una nueva estructura de comando
void        add_command(t_command **commands, t_command *new_cmd);// Añade un comando a la lista
bool        parse_redirections(t_parser *parser, t_command *cmd);// Procesa redirecciones en el comando
bool        parse_pipe(t_parser *parser);                         // Procesa operadores de tubería
char        **add_argument(char **args, char *new_arg);           // Añade un argumento al comando

// Prototipos de funciones de utilidad
void        free_tokens(t_token *tokens);                         // Libera memoria de los tokens
void        free_commands(t_command *commands);                   // Libera memoria de los comandos
bool        is_space(char c);                                     // Comprueba si un carácter es un espacio
bool        is_operator(char c);                                  // Comprueba si un carácter es un operador
bool        is_quote(char c);                                     // Comprueba si un carácter es una comilla
#endif
