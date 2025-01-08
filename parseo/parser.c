#include "parseo.h"

// Función principal para analizar la entrada y convertirla en una lista de comandos
t_command *parse(char *input)
{
    t_parser parser;           // Estructura del parser que mantiene el estado durante el análisis
    t_command *commands = NULL; // Lista enlazada de comandos generados
    t_command *current_cmd = NULL; // Puntero al comando que se está procesando actualmente

    // Inicialización del parser
    if (!input)
    {
        printf("No input\n");
        return (NULL);
    }
    parser.input = input;
    parser.pos = 0;
    parser.tokens = tokenize(input);           // Se genera la lista de tokens a partir de la entrada
    parser.current_token = parser.tokens;      // Inicializamos el token actual con el primero de la lista

    // Mientras haya tokens para procesar
    while (parser.current_token)
    {
        if (!current_cmd) // Si no hay un comando actual, creamos uno nuevo
        {
            current_cmd = create_command(); // Creamos un nuevo comando vacío
            add_command(&commands, current_cmd); // Lo añadimos a la lista de comandos
        }

        // Si el token actual es una palabra, una comilla o una variable de entorno
        if (parser.current_token->type  == TOKEN_WORD||
            parser.current_token->type == TOKEN_DQUOTE ||
            parser.current_token->type == TOKEN_SQUOTE ||
            parser.current_token->type == TOKEN_ENV_VAR)
        {
            // Añadimos el valor del token como un argumento del comando actual
            current_cmd->args = add_argument(current_cmd->args, parser.current_token->value);
            parser.current_token = parser.current_token->next; // Avanzamos al siguiente token
        }
        // Si el token actual es una tubería "|"
        else if (parser.current_token->type == TOKEN_PIPE)
        {
            if (!parse_pipe(&parser)) // Validamos que la tubería sea válida
                break; // Si no es válida, salimos del bucle
            current_cmd = create_command(); // Creamos un nuevo comando para la próxima sección
            add_command(&commands, current_cmd); // Lo añadimos a la lista de comandos
        }
        // Si el token actual es una redirección (<, >, <<, >>)
        else if (parser.current_token->type >= TOKEN_REDIR_IN && 
                 parser.current_token->type <= TOKEN_APPEND)
        {
            if (!parse_redirections(&parser, current_cmd)) // Procesamos la redirección
                break; // Si la redirección no es válida, salimos del bucle
        }
        else // Si el token no corresponde a ninguno de los casos anteriores
        {
            parser.current_token = parser.current_token->next; // Lo ignoramos y avanzamos al siguiente
        }
    }

    free_tokens(parser.tokens); // Liberamos la memoria de la lista de tokens
    return commands; // Retornamos la lista de comandos generados
}

bool parse_redirections(t_parser *parser, t_command *cmd)
{
    t_token_type redir_type = parser->current_token->type; // Tipo de redirección
    parser->current_token = parser->current_token->next;  // Avanzamos al siguiente token

    // Si no hay más tokens o el siguiente no es una palabra o cadena, es un error
    if (!parser->current_token || 
        (parser->current_token->type != TOKEN_WORD &&
         parser->current_token->type != TOKEN_DQUOTE &&
         parser->current_token->type != TOKEN_SQUOTE))
    {
        return false;
    }

    // Procesamos el tipo de redirección: entrada o salida
    if (redir_type == TOKEN_REDIR_IN || redir_type == TOKEN_HEREDOC) // Redirección de entrada
    {
        cmd->infile = ft_strdup(parser->current_token->value); // Guardamos el archivo de entrada
        if (redir_type == TOKEN_HEREDOC)
            cmd->in_type = 1; // Tipo heredoc
        else
            cmd->in_type = 0; // Tipo normal
    }
    else // Redirección de salida
    {
        cmd->outfile = ft_strdup(parser->current_token->value); // Guardamos el archivo de salida
        if (redir_type == TOKEN_APPEND)
            cmd->out_type = 1; // Tipo append
        else
            cmd->out_type = 0; // Tipo normal
    }

    parser->current_token = parser->current_token->next; // Avanzamos al siguiente token
    return true; // Redirección procesada con éxito
}


// Función para procesar una tubería "|"
bool parse_pipe(t_parser *parser)
{
    if (!parser->current_token->next) // Si no hay más tokens después de la tubería, es un error
        return false;
    parser->current_token = parser->current_token->next; // Avanzamos al siguiente token
    return true; // Tubería válida
}

