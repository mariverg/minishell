MAINFILES = main comander ejecuter filer forker actioner printer
PARFILES = ./parseo/lexer ./parseo/parser ./parseo/utils
ENVFILES = ./envbuilder/envbuilder ./envbuilder/envtools
COMFILES = ./combuilder/combuilder
PRECHECKFILES = ./prechecker/prechecker
FILES = $(MAINFILES) $(PARFILES) $(ENVFILES) $(PRECHECKFILES) $(COMFILES)

OBJS = $(addsuffix .o, $(FILES))
SRCS = $(addsuffix .c, $(FILES))
CFILES = $(addsuffix .c , $(FILES))

LIBS = -Llibs/libft -lreadline -lft
# LIBS = -Llibs/libtxttools -Llibs/libft -lreadline -lft -ltxttools
INCLUDES = -I. -I./parseo 
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES)

%.o: %.c
	$(CC) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	
clean: libclean
	rm -f $(OBJS)

libclean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

 

#all: $(OBJS)
#	$(CC) -c $< -o $@ $(LIBFT) $(LIBS) $(INCLUDES)
# gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

#%.o: %.c
#	$(CC) -c $< -o $@

# $(NAME): $(LIBFT)
#	 gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)	

#$(LIBFT):
#	make -C $(LIBFT_DIR) 