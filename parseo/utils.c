#include "parseo.h"

// Crea un nuevo token con un valor y tipo específicos
t_token *create_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token)); // Reserva memoria para el token
    if (!token)
        return NULL; // Retorna NULL si la memoria no se pudo asignar
    token->value = ft_strdup(value); // Copia el valor proporcionado
    token->type = type; // Asigna el tipo del token
    token->next = NULL; // Inicializa el puntero al siguiente token como NULL
    return token; // Retorna el token creado
}

// Añade un nuevo token a la lista enlazada de tokens
void add_token(t_token **tokens, t_token *new_token)
{
    t_token *current;

    if (!*tokens) // Si la lista de tokens está vacía
        *tokens = new_token; // El nuevo token es el primero
    else
    {
        current = *tokens; // Comienza desde el primer token
        while (current->next) // Avanza hasta el último token
            current = current->next;
        current->next = new_token; // Conecta el nuevo token al final
    }
}

// Crea un nuevo comando con todos sus campos inicializados
t_command *create_command(void)
{
    t_command *cmd = malloc(sizeof(t_command)); // Reserva memoria para el comando
    if (!cmd)
        return NULL; // Retorna NULL si la memoria no se pudo asignar
    cmd->args = NULL;      // Inicializa la lista de argumentos como vacía
    cmd->infile = NULL;    // No hay archivo de entrada inicial
    cmd->outfile = NULL;   // No hay archivo de salida inicial
    cmd->in_type = 0;      // Tipo de entrada por defecto
    cmd->out_type = 0;     // Tipo de salida por defecto
    cmd->next = NULL;      // No hay próximo comando inicial
    return cmd; // Retorna el comando creado
}

// Añade un nuevo comando a la lista enlazada de comandos
void add_command(t_command **commands, t_command *new_cmd)
{
    t_command *current;

    if (!*commands) // Si la lista de comandos está vacía
        *commands = new_cmd; // El nuevo comando es el primero
    else
    {
        current = *commands; // Comienza desde el primer comando
        while (current->next) // Avanza hasta el último comando
            current = current->next;
        current->next = new_cmd; // Conecta el nuevo comando al final
    }
}

// Añade un nuevo argumento a la lista de argumentos de un comando
char **add_argument(char **args, char *new_arg)
{
    int i = 0;
    char **new_args;

    // Cuenta la cantidad de argumentos actuales
    if (args)
        while (args[i])
            i++;

    // Reserva espacio para un array más grande (incluye el nuevo argumento y NULL)
    new_args = malloc(sizeof(char *) * (i + 2));
    if (!new_args)
        return NULL; // Retorna NULL si la memoria no se pudo asignar

    // Copia los argumentos existentes al nuevo array
    i = 0;
    if (args)
    {
        while (args[i])
        {
            new_args[i] = args[i]; // Copia el puntero del argumento existente
            i++;
        }
    }

    // Añade el nuevo argumento al final
    new_args[i] = ft_strdup(new_arg); // Copia el valor del nuevo argumento
    new_args[i + 1] = NULL; // Finaliza el array con un NULL

    // Libera el array antiguo (pero no los contenidos)
    free(args);

    return new_args; // Retorna el nuevo array de argumentos
}

// Libera la memoria de una lista enlazada de tokens
void free_tokens(t_token *tokens)
{
    t_token *temp;

    while (tokens) // Itera por cada token en la lista
    {
        temp = tokens; // Almacena el token actual temporalmente
        tokens = tokens->next; // Avanza al siguiente token
        free(temp->value); // Libera el valor del token
        free(temp); // Libera la estructura del token
    }
}

// Libera la memoria de una lista enlazada de comandos
void free_commands(t_command *commands)
{
    t_command *temp;
    int i;

    while (commands) // Itera por cada comando en la lista
    {
        temp = commands; // Almacena el comando actual temporalmente
        commands = commands->next; // Avanza al siguiente comando

        // Libera los argumentos del comando
        if (temp->args)
        {
            i = 0;
            while (temp->args[i])
                free(temp->args[i++]); // Libera cada argumento
            free(temp->args); // Libera el array de argumentos
        }
        free(temp->infile); // Libera el archivo de entrada
        free(temp->outfile); // Libera el archivo de salida
        free(temp); // Libera la estructura del comando
    }
}

// Comprueba si un carácter es un espacio en blanco
bool is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Comprueba si un carácter es un operador válido
bool is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

// Comprueba si un carácter es una comilla
bool is_quote(char c)
{
    return (c == '\'' || c == '"');
}


