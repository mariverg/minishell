# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mariverg <mariverg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/28 08:25:00 by mariverg          #+#    #+#              #
#    Updated: 2025/01/17 15:25:42 by mariverg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= 	libft.a
SRCS 	= 	ft_bzero.c\
 			ft_isalnum.c\
  			ft_isalpha.c\
			ft_isascii.c \
			ft_isdigit.c\
			ft_isprint.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strncmp.c\
			ft_memchr.c\
			ft_strnstr.c\
			ft_memcmp.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strcmp.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putnbr_fd.c\
			ft_putendl_fd.c\
			
BONUS_SRCS = ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\
			
CC		= 	gcc
FLAGS 	=
INCLUDE =   libft.h

OBJS 	= 	${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

all: ${NAME}

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS) $(INCLUDE)

${NAME}: ${OBJS}
	ar rcs $(NAME) $(OBJS) $(INCLUDE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus