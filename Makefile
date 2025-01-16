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
PARFILES = ./parseo/lexer ./parseo/parser ./parseo/utils ./parseo/utils_parser
ENVFILES = ./envbuilder/envbuilder ./envbuilder/envtools ./envbuilder/envexer
COMFILES = ./taskbuilder/taskbuilder
TASKPARFILES = ./tasksparser/tasksparser ./tasksparser/filetasks ./tasksparser/builttasks ./tasksparser/pipetasks
HISTORYFILES = ./history/history 
PRECHECKFILES = ./prechecker/expandvars
PROCESSFILES = ./processer/forker ./processer/executer ./processer/filer
FILES = $(MAINFILES) $(PARFILES) $(ENVFILES) $(PRECHECKFILES) $(COMFILES) $(HISTORYFILES) $(TASKPARFILES)

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