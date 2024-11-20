NAME = minishell
FILES = main comander ejecuter filer forker actioner ./parseo/lexer ./parseo/parser ./parseo/utils
CFILES = $(addsuffix .c , $(FILES))
LIBS = -Llibs -Lparseo/libft
INCLUDES = -I. -I./parseo -lreadline -lft -ltxttools
LIBFT_DIR = ./parseo/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)
	gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

$(NAME): $(LIBFT)
	gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)	

$(LIBFT):
	make -C $(LIBFT_DIR) 