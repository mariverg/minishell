#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void accion(int i, siginfo_t *si, void *v)
{
	printf("\naccion\n");
}

void blockaction()
{
	struct sigaction sa;
	sa.sa_sigaction = accion;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	// sigaction(SIGTSTP, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}
int main()
{
	blockaction();
	printf("soy otro main\n");
	while (1)
	{
		printf("soy otro main\n");
		sleep(1);
	}
	return (12);
}