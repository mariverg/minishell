FILES = main comander ejecuter filer forker actioner ./parseo/lexer ./parseo/parser ./parseo/utils
CFILES = $(addsuffix .c , $(FILES))
LIBS = -Llibs -ltxttools
INCLUDES = -I. -I./parseo -lreadline


all:
	gcc $(CFILES) $(LIBS) $(INCLUDES) 
