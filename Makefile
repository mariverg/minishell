FILES = main comander ejecuter filer forker actioner printer enviromenter ./parseo/lexer ./parseo/parser ./parseo/utils
OBJS = $(addsuffix .o, $(FILES))
SRCS = $(addsuffix .c, $(FILES))
CFILES = $(addsuffix .c , $(FILES))

LIBS = -Llibs -Lparseo/libft
INCLUDES = -I. -I./parseo -lreadline -lft -ltxttools
LIBFT_DIR = ./parseo/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) 

#all: $(OBJS)
#	$(CC) -c $< -o $@ $(LIBFT) $(LIBS) $(INCLUDES)
# gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

#%.o: %.c
#	$(CC) -c $< -o $@

# $(NAME): $(LIBFT)
#	 gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)	

#$(LIBFT):
#	make -C $(LIBFT_DIR) 