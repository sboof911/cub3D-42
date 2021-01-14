# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 14:50:01 by amaach            #+#    #+#              #
#    Updated: 2021/01/14 10:19:33 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a

FLAGS =  -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit


EXEC = cub3D

SRCS =  ./outils/ft_isdigit.c ./outils/ft_putstr_fd.c ./outils/ft_strchr.c \
		./outils/ft_strjoin.c ./outils/ft_strrev.c ./outils/get_next_line.c \
		./other_outils/wall_projecting.c ./outils/ft_atoi.c ./outils/ft_putchar_fd.c \
		./outils/ft_split.c ./outils/ft_strdup.c ./outils/ft_strlen.c \
		./outils/ft_substr.c main.c ./read_map/read_maps.c ./read_map/help_map.c \
		./read_map/help_config.c ./read_map/help_error.c ./read_map/help_paco.c \
		./read_map/help_spaces.c ./raycasting/ray_casting.c ./raycasting/help_casting.c \
		./helpcub/cub3d.c ./helpcub/help_cub.c ./helpcub/otherhelp.c ./other_outils/sprite.c \
		./other_outils/save.c

$(NAME): all

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRCS) $(MLX) $(FRAMEWORKS) -o $(EXEC)

clean:
	rm -f $(EXEC)

fclean: clean

re: fclean all