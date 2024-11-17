
#include "parseo.h"

// Función principal para dividir una entrada en tokens
t_token *tokenize(char *input)
{
    t_token *tokens = NULL; // Lista de tokens generados
    int i = 0;             // Índice para recorrer la entrada
    char *value;           // Valor temporal para almacenar los tokens

    // Recorremos la entrada carácter por carácter
    while (input[i])
    {
        if (is_space(input[i])) // Si es un espacio, simplemente lo saltamos
            i++;
        else if (is_operator(input[i])) // Si es un operador (como |, <, >, etc.)
        {
            value = get_operator(input, &i); // Obtenemos el operador como string
            if (value) // Si se obtuvo un operador válido
            {
                // Creamos un token basado en el tipo de operador y lo añadimos a la lista
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
                free(value); // Liberamos la memoria del operador temporal
            }
        }
        else if (input[i] == '\'' || input[i] == '"') // Si es una comilla simple o doble
        {
            char quote = input[i]; // Determinamos el tipo de comilla
            value = get_quoted_string(input, &i, quote); // Extraemos el contenido entre comillas
            if (value) // Si se obtuvo un valor válido
                add_token(&tokens, create_token(value, quote == '"' ? TOKEN_DQUOTE : TOKEN_SQUOTE));
        }
        else if (input[i] == '$') // Si encuentra una variable de entorno
        {
            value = get_env_var(input, &i); // Extraemos el nombre de la variable
            if (value) // Si la variable es válida
                add_token(&tokens, create_token(value, TOKEN_ENV_VAR));
        }
        else // Si es una palabra (comando o argumento)
        {
            value = get_word(input, &i); // Extraemos la palabra
            if (value) // Si se obtuvo un valor
                add_token(&tokens, create_token(value, TOKEN_WORD));
        }
    }
    return tokens; // Devolvemos la lista de tokens generados
}

// Extrae una palabra desde la entrada
char *get_word(char *input, int *i)
{
    int start = *i; // Posición inicial de la palabra
    int len = 0;    // Longitud de la palabra

    // Avanzamos mientras el carácter no sea un espacio, operador, comilla o $
    while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]) && 
           input[*i] != '\'' && input[*i] != '"' && input[*i] != '$')
    {
        (*i)++; // Avanzamos el índice
        len++;  // Incrementamos la longitud
    }
    return ft_substr(input, start, len); // Retornamos la palabra extraída
}

// Extrae un operador desde la entrada
char *get_operator(char *input, int *i)
{
    if (input[*i] == '|') // Si es una tubería
    {
        (*i)++;
        return ft_strdup("|"); // Retornamos el operador como cadena
    }
    else if (input[*i] == '<') // Si es una redirección de entrada
    {
        if (input[*i + 1] == '<') // Si es un heredoc
        {
            (*i) += 2; // Avanzamos dos posiciones
            return ft_strdup("<<");
        }
        (*i)++;
        return ft_strdup("<");
    }
    else if (input[*i] == '>') // Si es una redirección de salida
    {
        if (input[*i + 1] == '>') // Si es una redirección con append
        {
            (*i) += 2; // Avanzamos dos posiciones
            return ft_strdup(">>");
        }
        (*i)++;
        return ft_strdup(">");
    }
    return NULL; // Retornamos NULL si no es un operador válido
}

// Extrae una cadena entre comillas
char *get_quoted_string(char *input, int *i, char quote)
{
    int start = ++(*i);  // Saltamos la comilla inicial
    int len = 0;         // Longitud de la cadena

    while (input[*i] && input[*i] != quote) // Avanzamos hasta la comilla de cierre
    {
        (*i)++;
        len++;
    }
    if (input[*i] == quote) // Si encontramos la comilla de cierre
    {
        (*i)++; // Saltamos la comilla de cierre
        return ft_substr(input, start, len); // Retornamos la cadena extraída
    }
    return NULL; // Si la comilla no cierra, retornamos NULL
}

// Extrae una variable de entorno desde la entrada
char *get_env_var(char *input, int *i)
{
    (*i)++;  // Saltamos el carácter '$'
    int start = *i; // Posición inicial del nombre de la variable
    int len = 0;    // Longitud de la variable

    // Avanzamos mientras el carácter sea alfanumérico o un guion bajo
    while (input[*i] && (isalnum(input[*i]) || input[*i] == '_'))
    {
        (*i)++;
        len++;
    }
    return ft_substr(input, start, len); // Retornamos el nombre de la variable
}
