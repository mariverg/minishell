MAINFILES = main actioner printer memtools
PARFILES = ./parseo/lexer ./parseo/parser ./parseo/utils
ENVFILES = ./envbuilder/envbuilder ./envbuilder/envtools ./envbuilder/envexer
COMFILES = ./taskbuilder/taskbuilder
PRECHECKFILES = ./prechecker/prechecker ./prechecker/expandvars
PROCESSFILES = ./processer/forker ./processer/executer ./processer/filer
FILES = $(MAINFILES) $(PARFILES) $(ENVFILES) $(PRECHECKFILES) $(COMFILES) $(PROCESSFILES)

OBJS = $(addsuffix .o, $(FILES))

LIBS = -Llibs/libft -lreadline -lft
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus
	
clean: libclean
	rm -f $(OBJS)

libclean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

 
val: $(OBJS) $(LIBFT)
	$(CC) -g -o $(NAME) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES)

memtest:
	valgrind ./$(NAME)
#all: $(OBJS)
#	$(CC) -c $< -o $@ $(LIBFT) $(LIBS) $(INCLUDES)
# gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

#%.o: %.c
#	$(CC) -c $< -o $@

# $(NAME): $(LIBFT)
#	 gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)	

#$(LIBFT):
#	make -C $(LIBFT_DIR) 