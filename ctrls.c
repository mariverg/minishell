#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void accion(int i, siginfo_t *si, void *v)
{
    if (i == SIGINT)
    {
        // Para SIGINT (Ctrl+C) simplemente muestra un salto de línea y el prompt.
        printf("\n>");
    }
    else if (i == SIGTSTP)
    {
        // Para SIGTSTP (Ctrl+Z), no hacer nada, solo ignorarlo.
        // Aun imprime ^Z
        return;
    }
}

// Bloquea las acciones y configura los manejadores de señales.
void blockaction()
{
    struct sigaction sac;

    // Asignar manejador para SIGINT (Ctrl+C)
    sac.sa_sigaction = accion;
    sigemptyset(&sac.sa_mask);
    sac.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sac, 0);

    // Asignar manejador para SIGTSTP (Ctrl+Z) sin hacer nada.
    sac.sa_sigaction = accion;
    sigaction(SIGTSTP, &sac, 0);
}

int main()
{
    // Configura el bloqueo de señales.
    blockaction();

    // Simulamos el programa principal.
    while (1)
    {
        // Imprime un prompt y espera entrada.
        printf(">");
        fflush(stdout);  // Asegúrate de que se imprima el prompt correctamente.

        // Aquí iría el código para leer y procesar la entrada.
        // sleep(1);  // Solo un simulacro de espera.
    }

    return 0;
}
