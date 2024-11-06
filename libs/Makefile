FILES = spltools strtools strstools strsstools strfinders cplxtools
OBJS = $(addsuffix .o, $(FILES))
SRCS = $(addsuffix .c, $(FILES))
CFILES = $(addsuffix .c, $(FILES))
NAME = libtxttools.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	gcc main.c -L. -ltxttools