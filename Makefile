# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 15:48:04 by mariverg          #+#    #+#              #
#    Updated: 2025/01/13 15:48:04 by mariverg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MAINFILES = main actioner memtools printer printenv

MANAGERFILES = ./manager/manager

PFILES = ./divider/divider\
			./divider/docom\
			./divider/divtools\
			./divider/clearcoma\
			./divider/divfilllst\
			./divider/divredirs

ENVFILES = ./envbuilder/envbuilder\
 			./envbuilder/envtools\
 			./envbuilder/envexer\
			./envbuilder/envtoolsb\
			./envbuilder/envdeleter\
			./envbuilder/envfiller\
			./envbuilder/envstr

COMFILES = ./taskbuilder/taskbuilder\
			./taskbuilder/lsttopoint\
			./taskbuilder/tbtools

TASKPARFILES = ./tasksparser/tasksparser\
				./tasksparser/filetasks\
				./tasksparser/builttasks\
				./tasksparser/pipetasks\
				./tasksparser/taskwaiter\
				./tasksparser/builttbis

PRECHECKFILES = ./prechecker/expandvars\
				./prechecker/syntaxerr\
				./prechecker/csintaxerr\
				./prechecker/expandirtxt
				
FILES = $(MAINFILES) $(ENVFILES) $(PRECHECKFILES) $(COMFILES) $(HISTORYFILES) $(TASKPARFILES) $(MANAGERFILES) $(PFILES)

OBJS = $(addsuffix .o, $(FILES))

LIBS = -Llibs/libft -lreadline -lft
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFLAGS2 =

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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

re:
	make fclean
	make

 
val: $(OBJS) $(LIBFT)
	$(CC) -g -o $(NAME) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES)

memtest:
	valgrind ./$(NAME)

fmemtest:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

#all: $(OBJS)
#	$(CC) -c $< -o $@ $(LIBFT) $(LIBS) $(INCLUDES)
# gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

#%.o: %.c
#	$(CC) -c $< -o $@

# $(NAME): $(LIBFT)
#	 gcc $(CFILES) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)	

#$(LIBFT):
#	make -C $(LIBFT_DIR) 