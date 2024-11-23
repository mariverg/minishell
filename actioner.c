#include <signal.h>
#include <stdio.h>

void accion(int i, siginfo_t *si, void *v)
{
	printf("\n>");
}

///bloquea acciones
void blockaction()
{
	struct sigaction sa;
	sa.sa_sigaction = accion;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}

///permite acciones
void allowaction()
{
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}