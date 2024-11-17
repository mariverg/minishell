FILES = main comander ejecuter filer forker actioner
CFILES = $(addsuffix .c , $(FILES))
#esta linea añade las librerias externas. -L* apunta al directorio -l* al .a, ademas hay que incluir la ruta completa del .h en el main.
LIBS = -Llibs -ltxttools

all:
	gcc $(CFILES) $(LIBS)

exe:
	gcc execs.c comander.c

otro:
	gcc -o b.out otromain.c