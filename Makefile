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


MAINFILES = main actioner printer memtools

MANAGERFILES = ./manager/manager

PFILES = ./divider/divider\
			./divider/docom\
			./divider/divtools\
			./divider/clearcoma

PARFILES = ./parseo/lexer\
			./parseo/parser\
			./parseo/utils\
			./parseo/utils_parser\
			./parseo/utils_lexer\
			./parseo/utils_utils

ENVFILES = ./envbuilder/envbuilder\
 			./envbuilder/envtools\
 			./envbuilder/envexer

COMFILES = ./taskbuilder/taskbuilder\
			./taskbuilder/lsttopoint

TASKPARFILES = ./tasksparser/tasksparser\
				./tasksparser/filetasks\
				./tasksparser/builttasks\
				./tasksparser/pipetasks

PRECHECKFILES = ./prechecker/expandvars\
				./prechecker/syntaxerr
				
FILES = $(MAINFILES) $(PARFILES) $(ENVFILES) $(PRECHECKFILES) $(COMFILES) $(HISTORYFILES) $(TASKPARFILES) $(MANAGERFILES) $(PFILES)

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