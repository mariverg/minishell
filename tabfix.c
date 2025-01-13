#include <readline/readline.h>
#include <readline/history.h>

// Manejador vacío para deshabilitar el autocompletado
char *dummy_completion(const char *text, int state) {
    return NULL;
}

void init_readline_customization(void) {
    rl_bind_key('\t', rl_complete); // Asigna la tecla Tab a la función de autocompletado
    rl_attempted_completion_function = NULL; // Deshabilita el autocompletado
}