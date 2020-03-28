# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 19:18:03 by amaach            #+#    #+#              #
#    Updated: 2019/10/25 23:04:37 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -c

SRCS = ft_strlen.c ft_tolower.c ft_isdigit.c ft_isascii.c ft_isalpha.c \
	   ft_isalnum.c ft_calloc.c ft_atoi.c ft_bzero.c ft_isprint.c \
	   ft_toupper.c ft_strncmp.c ft_strlcat.c ft_strlcpy.c ft_strnstr.c \
	   ft_strdup.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memset.c \
	   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memcmp.c ft_split.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strrev.c \
	   get_next_line.c

$(NAME): all

all:
	gcc $(FLAGS) $(SRCS)
	ar -rc $(NAME) *.o
	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	make all
