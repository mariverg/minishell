#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "minishell.h"

//// crea un nuevo tcomand, los chars son punteros que ahora apuntan a memoria en el stack de main (o donde quiera que se crearan), tal vez sea necesario duplicarlos y malloc aumenta la complejidad, tal y como estan pueden desaparecer, podria dar a errores dificiles de captar, o no.
/// por lo demas lo unco que hace es poner los valores en ; 

t_comand *newcom(char *c, char **cc, char **env)
{
	t_comand *res;

	res = malloc(sizeof(t_comand));
	res->c = c;
	res->cc = cc;
	res->env = env;
	res->operator = 0;
	res->in = 0;
	res->out = 0;

	return (res);
}
