#include "libs/libtxttools.h"
#include "minishell.h"
#include <stdio.h>
#include <signal.h>



int main(int argc, char **argv, char **env)
{
	t_entorno te;
	te.lstret = -1;

	blockaction();

	t_comand *tct = newcom(0, 0, env);
	tct->operator = 66;

	char *ca = "./b.out";
	char *cca[] = {ca, 0};
	t_comand *tca = newcom(ca, cca, env);
	tca->operator = 0;

	printf("miintgralahora %i\n", te.lstret);
	int i = forkea(tca, 0, &te);
	while (1)
	{
		printf("miintgralahora %i \n", te.lstret);
		sleep(1);
	}
	return (10);
}

/*
// en main lo fundamental es la struct t_comant, definida en el .h
// creo varios para testear
// la final ejecuto las que quiera manualmente,
int main(int argc, char **argv, char **env)
{
	extern char **environ;

											//// EL PARSER
	//// La funcion del parser esta aqui, debe leer de readline e identificar que datos iran en:
	//// el struct t_comand
	//// *c seria el comando o instruccion ej: 'ls', 'cd', 'echo' etc
	//// **cc ej caso de ser un ejecutable, el array con las intrucciones terminado en 0, ej: {"ls", 0} o {"ls", "-a", "-l", 0} o {"echo", "hola como estas", 0}
	//// el operador, in y oun, dependen de la intruccion "ls | grep > mitexto", el parser debe identificarlos junto a la instruccion. En esta linea:
	//// ls |- es la primera instruccion, la clasificara otra parte del codigo, pero es especial y debe identificarse como tal, dejando el operador indeterminado -1?. Por otro lado a la derecha de 'ls' '|' fuerza out = 1
	//// | grep >- iria con | a la izquierda lo que implica operador = 0 (execve) e in = 1 y sabiendo que > a la derecha fuerza out = 1
	//// > mitexto- operador a la izquierda implica redireccion de input = 1, y que sea > es por que el operador = 1 (escribir a mitext.txt)
											///// FIN DEL PARSER
	
	// cada uno de estos bloques define un tcomand. en principio los valores estan en cero
	// pero para hacer test los cambio manualmente
	// out define si el comando debe redirigir el output , in hace lo mismo con el input,
	// en principio valdran 1 todos menos el 'in' del primero y el 'out' del ultimo, no se sipuede darse alguna excepcion.
	// Los operadores tambien son muy importantes, 
	// 0 hace execve: |
	// 1 write >
	// 2 read  <
	// >> y << actualmente no estan, ni cd u otras instrucciones

	///este comando tiene mucho data de test que no hace nada, la clave es el operador 2. este hace que su unica funcion sea leer de outtext.txt, y dado que out es 1 , redirige stdout
	char *ct = "/usr/bin/ls";
	char *cct[] = {ct, "-a", "-l", 0};
	t_comand *tct = newcom(ct, cct, env);
	tct->out = 1;
	tct->operator = 2;

	/// ls con redireccion de salida
	char *ca = "/usr/bin/ls";
	char *cca[] = {ca, "-a", "-l", 0};
	t_comand *tca = newcom(ca, cca, env);
	tca->out = 1;
	tca->operator = 0;

	/// grep con ambas redirecciones, coge 'a'
	char *cb = "/usr/bin/grep";
	char *ccb[] = {cb, "a", 0};
	t_comand *tcb = newcom(cb, ccb, env);
	tcb->in = 1;
	tcb->out = 1;
	tcb->operator = 0;

	// y un wc que tampoco funciona como tal, operador 1 lo transforma en un escritor a mitext.txt
	char *cd = "/usr/bin/wc";
	char *ccd[] = {cd, 0};
	t_comand *tcd = newcom(cd, ccd, env);
	tcd->in = 1;
	tcd->operator = 1;

	/// aqui ejecuto 1 el read, 3 el grep y, 4 el write
	int i = ejecuta(tct, 0);
	i = ejecuta(tcb, i);
	i = ejecuta(tcd, i);

	printf("terminando\n");

	return (10);
}
*/

/*
///anterior funcion con los test de la libreria de texto
int main()
{
	char *c;
	char **cc;

	c =  getenv("PATH");
	printf("\nORIGINAL\n%s\n", c);
	cc = strxplode(c,":");
	printf("\nEXPLODE\n");
	prntstrs(cc);
	cc = strdisolve(c, ":");
	printf("\nDISOLVE\n");
	prntstrs(cc);
	cc = strdivide(c, ":");
	printf("\nDIVIDE\n");
	prntstrs(cc);
}*/