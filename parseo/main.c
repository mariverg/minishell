#include "parseo.h"

int main(void)
{
    char *input = "echo \"Hello $USER\" | grep Hello > output.txt";
    t_command *commands = parse(input);
    
    // Procesar los comandos
    t_command *current = commands;
    while (current)
    {
        // Acceder a los argumentos, redirecciones, etc.
        printf("Command: %s\n", current->args[0]);
        current = current->next;
    }
    
    // Liberar memoria
    free_commands(commands);
    return (0);
}